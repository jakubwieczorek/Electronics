#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSvgGenerator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Factory factory = Factory::getInstance();
    Ftransistor::ID = factory.registerElement(Ftransistor::CreateFtransistor);
    Cdiode::ID = factory.registerElement(Cdiode::CreateCdiode);
    //coding
    QTextCodec::setCodecForLocale(QTextCodec::codecForName ("UTF-8"));
    ui->setupUi(this);

    //items
    ui->listWidget->addItem("Capacity Diode");
    ui->listWidget->item(0)->setIcon(QIcon("../Electronic/pojemnosciowa.jpg"));

    ui->listWidget->addItem("Photo Transistor");
    ui->listWidget->item(1)->setIcon(QIcon("../Electronic/fototransistor.png"));

    itm = NULL;

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    //counters of Cdiode and ftransistor
    elements = new QElem*;

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
    connect(ui->actionZapisz, SIGNAL(triggered(bool)), this, SLOT(actionZapisz()));

    gboxLayout = new QGridLayout;
    ui->groupBox->setLayout(gboxLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    for(int i=0; i<container.container.size(); i++)
    {
        delete elements[i];
    }
    delete elements;
    delete spin;
    delete espin;
    delete lineColorButton;
    delete interiorColorButton;
    delete gboxLayout;
}

enum {widgetCdiode, widgetFtransistor};

void MainWindow::addElem(QListWidgetItem *itm)
{
    if(itm == ui->listWidget->item(widgetCdiode))
    {
        elements[container.container.size()] = new CdiodeItem;
    }else
    if(itm == ui->listWidget->item(widgetFtransistor))
    {
        elements[container.container.size()] = new FtransistorItem;
    }

    container+elements[container.container.size()];
    scene->addItem(elements[container.container.size()-1]);
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
    FtransistorItem *fitm;

    QElem *elem;

    if((elem = dynamic_cast<QElem*>(itm))!=NULL)
    {
        ui->groupBox->setTitle(tr("&Capacity Diode"));

        lineColor.setRed(elem->getLineRed());
        lineColor.setGreen(elem->getLineGreen());
        lineColor.setBlue(elem->getLineBlue());

        interiorColor.setRed(elem->getInteriorRed());
        interiorColor.setGreen(elem->getInteriorGreen());
        interiorColor.setBlue(elem->getInteriorBlue());

        espin->setText(QString::number(elem->getSpin()));
    }

    elem->setBacklight(true);

    if((citm = dynamic_cast<CdiodeItem*>(elem))!=NULL)
    {
        ui->groupBox->setTitle(tr("&Capacity Diode"));
    }else
    if((fitm = dynamic_cast<FtransistorItem*>(elem))!=NULL)
    {
        ui->groupBox->setTitle(tr("&Photo Transistor"));
    }
}

void MainWindow::whichSelected()
{
    if(itm!=NULL)
    {
        QElem *elem = dynamic_cast<QElem*>(itm);
        elem->setBacklight(false);
    }

    QList <QGraphicsItem*>itemsList = scene->selectedItems();

    for(int i=0; i<itemsList.count(); i++)
    {
        itm = itemsList.at(i);
        if(itm->isSelected() == true) break;
    }

    modElem(itm);

    itm->setSelected(false);
}

void MainWindow::paintElem()
{
    QElem *elem;

    if(((elem = dynamic_cast<QElem*>(itm))!=NULL))
    {
        elem->setInteriorRed(interiorColor.red());
        elem->setInteriorGreen(interiorColor.green());
        elem->setInteriorBlue(interiorColor.blue());

        elem->setLineRed(lineColor.red());
        elem->setLineGreen(lineColor.green());
        elem->setLineBlue(lineColor.blue());

        elem->setSpin(espin->text().toShort());
        elem->setRotation(elem->getSpin());
    }

    elem->update();
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

void MainWindow::actionZapisz()
{
    QList <QGraphicsItem*>items = scene->items();
    QElem *elem;
    int shiftX = 0; //trzeba przesunac uklad wspolrzednych
    int shiftY = 0;

    for(int i=0; i<container.container.size(); i++)
    {
        elem = dynamic_cast<QElem*>(items.at(i));

        shiftX = elem->x();
        if(elem->x()<shiftX) shiftX = elem->x();

        shiftY = elem->y();
        if(elem->y()<shiftY) shiftY = elem->y();
    }

    qDebug()<<QString::number(shiftX)<<QString::number(shiftY);

    for(int i=0; i<container.container.size(); i++)
    {
        elem = dynamic_cast<QElem*>(items.at(i));
        qDebug()<<QString::number(elem->x())<<QString::number(elem->y());

        container.container.at(i)->setX(static_cast<unsigned short>(elem->x() - shiftX));
        container.container.at(i)->setY(static_cast<unsigned short>(elem->y() - shiftY));
    }

    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save file"),
            mCurrentPath, "SVG files (*.svg)");


    if (!fileName.isEmpty())
    {
        container>>(fileName.toStdString());

        QFileInfo info(fileName);
        QString txtFileName = info.path() + QDir::separator() + info.completeBaseName() + ".txt";
        std::string stdTxtNameFile = txtFileName.toStdString();
        container.expToTxt(stdTxtNameFile);
    }

    // example from QT
    /*
    if (!fileName.isEmpty())
    {
        QString qtFileName = "qt.svg";

        QSvgGenerator generator;
        generator.setFileName(qtFileName);
        generator.setSize(QSize(200, 200));
        generator.setViewBox(QRect(0, 0, 200, 200));
        generator.setTitle(tr("SVG Generator Example Drawing"));
        generator.setDescription(tr("An SVG drawing created by the SVG Generator "
                                    "Example provided with Qt."));
        QPainter painter;
        painter.begin(&generator);

        CdiodeItem *citm = dynamic_cast<CdiodeItem*>(elem);

        FtransistorItem *fitm = dynamic_cast<FtransistorItem*>(elem);

        if(citm!=NULL)
        {
            citm->paint(&painter);
            painter.end();
        }else
        if(fitm!=NULL)
        {
            fitm->paint(&painter);
            painter.end();
        }
    }
    */
}
