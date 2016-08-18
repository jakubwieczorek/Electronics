#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), factory(Factory::getInstance())
{
    //factory = Factory::getInstance();
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
    connect(ui->actionOtw_rz, SIGNAL(triggered(bool)), this, SLOT(actionOtworz()));

    gboxLayout = new QGridLayout;
    ui->groupBox->setLayout(gboxLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
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
        QContainer.append(new CdiodeItem);
    }else
    if(itm == ui->listWidget->item(widgetFtransistor))
    {
        QContainer.append(new FtransistorItem);
    }

    container+QContainer.last();

    scene->addItem(QContainer.at(QContainer.size() - 1));
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

    if((actualElem = dynamic_cast<QElem*>(itm))!=NULL)
    {
        ui->groupBox->setTitle(tr("&Capacity Diode"));

        lineColor.setRed(actualElem->getLineRed());
        lineColor.setGreen(actualElem->getLineGreen());
        lineColor.setBlue(actualElem->getLineBlue());

        interiorColor.setRed(actualElem->getInteriorRed());
        interiorColor.setGreen(actualElem->getInteriorGreen());
        interiorColor.setBlue(actualElem->getInteriorBlue());

        espin->setText(QString::number(actualElem->getSpin()));
    }

    actualElem->setBacklight(true);

    if((citm = dynamic_cast<CdiodeItem*>(actualElem))!=NULL)
    {
        ui->groupBox->setTitle(tr("&Capacity Diode"));
    }else
    if((fitm = dynamic_cast<FtransistorItem*>(actualElem))!=NULL)
    {
        ui->groupBox->setTitle(tr("&Photo Transistor"));
    }
}

void MainWindow::whichSelected()
{
    if(itm!=NULL)
    {
        actualElem = dynamic_cast<QElem*>(itm);
        actualElem->setBacklight(false);
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
    if(((actualElem = dynamic_cast<QElem*>(itm))!=NULL))
    {
        actualElem->setInteriorRed(interiorColor.red());
        actualElem->setInteriorGreen(interiorColor.green());
        actualElem->setInteriorBlue(interiorColor.blue());

        actualElem->setLineRed(lineColor.red());
        actualElem->setLineGreen(lineColor.green());
        actualElem->setLineBlue(lineColor.blue());

        actualElem->setSpin(espin->text().toShort());
        actualElem->setRotation(actualElem->getSpin());
    }

    actualElem->update();
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

    int shiftX = 0; //trzeba przesunac uklad wspolrzednych
    int shiftY = 0;

    for(int i=0; i<container.container.size(); i++)
    {
        actualElem = dynamic_cast<QElem*>(items.at(i));

        if(actualElem->x() < shiftX)
            shiftX = actualElem->x();

        if(actualElem->y() < shiftY)
            shiftY = actualElem->y();
    }

    qDebug()<<QString::number(shiftX)<<QString::number(shiftY);

    for(int i=0; i < container.container.size(); i++)
    {
        actualElem = dynamic_cast<QElem*>(items.at(i));
        qDebug()<<QString::number(actualElem->x())<<QString::number(actualElem->y());
        //gdy shiftX lub shiftY < 0 to neutralizujemy do 0 najbardziej przesuniety actualElement

        //container.container.at(i)->setX(static_cast<unsigned short>(actualElem->x() - shiftX));
        //container.container.at(i)->setY(static_cast<unsigned short>(actualElem->y() - shiftY));

        container.container.at(i)->setY(container.container.at(i)->getY() - shiftY);
        container.container.at(i)->setX(container.container.at(i)->getX() - shiftX);
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

void MainWindow::actionOtworz()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open file"),
            mCurrentPath, "TxT files (*.txt)");

    if(!fileName.isEmpty())
    {
        QContainer.clear();
        container.container.clear();
        scene->clear();
        itm = NULL;

        std::string stdFileName = fileName.toStdString();
        container.impFromTxt(stdFileName, factory);

        for(int i=0; i < container.container.size(); i++)
        {
            if(dynamic_cast<Cdiode*>(container.container.at(i)) != NULL)
            {
                QContainer.append(new CdiodeItem);
            }else
            if(dynamic_cast<Ftransistor*>(container.container.at(i)) != NULL)
            {
                QContainer.append(new FtransistorItem);
            }

            scene->addItem(QContainer.at(i));
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

}
