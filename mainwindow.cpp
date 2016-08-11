#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //coding
    QTextCodec::setCodecForLocale(QTextCodec::codecForName ("UTF-8"));
    ui->setupUi(this);

    //items
    ui->listWidget->addItem("Capacity Diode");
    ui->listWidget->item(0)->setIcon(QIcon("../Electronic/pojemnosciowa.jpg"));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    //counters of item
    cdiode = new CdiodeItem*;

    spin = new QLabel;
    espin = new QLineEdit;
    lineColorButton = new QPushButton;
    interiorColorButton = new QPushButton;

    //connections
    connect(ui->listWidget, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(addElem(QListWidgetItem*)));
    connect(ui->actionZako_cz, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(whichSelected()));
    connect(espin, SIGNAL(editingFinished()), this, SLOT(paintElem()));
    connect(lineColorButton, SIGNAL(released()), this, SLOT(lineButtonClicked()));
    connect(interiorColorButton, SIGNAL(released()), this, SLOT(interiorButtonClicked()));

    gboxLayout = new QGridLayout;
    ui->groupBox->setLayout(gboxLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    for(int i=0; i<container.container.size(); i++)
    {
        delete cdiode[i];
    }
    delete cdiode;
    delete spin;
    delete espin;
    delete lineColorButton;
    delete interiorColorButton;
    delete gboxLayout;
}

void MainWindow::addElem(QListWidgetItem *itm)
{
    if(itm == ui->listWidget->item(0))
    {
        try
        {
            cdiode[container.container.size()] = new CdiodeItem;
            container+cdiode[container.container.size()];
        }
        catch(std::bad_alloc& msg)
        {
            qDebug()<<"bad_alloc caught: "<<msg.what();
            return;
        }

        scene->addItem(cdiode[container.container.size()-1]);
    }
}

void MainWindow::modElem(QGraphicsItem *itm)
{
    spin->setText(tr("spin"));
    espin->setMaximumSize(QSize(10000,25));

    gboxLayout->addWidget(spin, 1,1);
    gboxLayout->addWidget(espin,1,2);

    interiorColorButton->setText(tr("interior color"));
    lineColorButton->setText(tr("line color"));

    gboxLayout->addWidget(interiorColorButton, 2, 1);
    gboxLayout->addWidget(lineColorButton, 3, 1);

    CdiodeItem *citm;

    if((citm = dynamic_cast<CdiodeItem*>(itm))!=NULL)
    {
        ui->groupBox->setTitle(tr("&Capacity Diode"));

        espin->setText(QString::number(citm->getSpin()));
    }
}

void MainWindow::whichSelected()
{
    QList <QGraphicsItem*>itemsList = scene->selectedItems();

    for(int i=0; i<itemsList.count(); i++)
    {
        itm = itemsList.at(i);
        if(itm->isSelected() == true) break;
    }

    modElem(itm);

    for(int i=0; i<itemsList.count(); i++)
    {
        itemsList.at(i)->setSelected(false);
    }
}

void MainWindow::paintElem()
{
    CdiodeItem *citm;
    if(((citm = dynamic_cast<CdiodeItem*>(itm))!=NULL))
    {
        citm->setInteriorRed(interiorColor.red());
        citm->setInteriorGreen(interiorColor.green());
        citm->setInteriorBlue(interiorColor.blue());

        qDebug()<<"Line blue: "<<QString::number(citm->getLineBlue());
        qDebug()<<"Line red: "<<QString::number(citm->getLineRed());
        qDebug()<<"Line green: "<<QString::number(citm->getLineGreen());

        qDebug()<<"Line blue color: "<<QString::number(lineColor.blue());
        qDebug()<<"Line red color: "<<QString::number(lineColor.red());
        qDebug()<<"Line green color: "<<QString::number(lineColor.green());

        citm->setLineRed(lineColor.red());
        citm->setLineGreen(lineColor.green());
        citm->setLineBlue(lineColor.blue());

        qDebug()<<"Line blue: "<<QString::number(citm->getLineBlue());
        qDebug()<<"Line red: "<<QString::number(citm->getLineRed());
        qDebug()<<"Line green: "<<QString::number(citm->getLineGreen());

        citm->setSpin(espin->text().toShort());

        citm->setRotation(citm->getSpin());

        citm->update();
    }
}

void MainWindow::lineButtonClicked()
{
    lineColor = QColorDialog::getColor(Qt::blue, this, QString("Set line color"));

    paintElem();
}

void MainWindow::interiorButtonClicked()
{
    interiorColor = QColorDialog::getColor(Qt::green, this, QString("Set interior color"));
    paintElem();
}
