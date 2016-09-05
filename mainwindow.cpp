#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QKeyEvent>
#include <QSvgGenerator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), factory(Factory::getInstance())
{
    //factory = Factory::getInstance();
    Ftransistor::ID = factory.registerElement(Ftransistor::CreateFtransistor);
    Cdiode::ID = factory.registerElement(Cdiode::CreateCdiode);
    FlashingCdiode::ID = factory.registerElement(FlashingCdiode::CreateFlashingCdiode);
    FlashingFtransistor::ID = factory.registerElement(FlashingFtransistor::CreateFlashingFtransistor);

    //coding
    QTextCodec::setCodecForLocale(QTextCodec::codecForName ("UTF-8"));
    ui->setupUi(this);

    //items
    ui->listWidget->addItem("Capacity Diode");
    ui->listWidget->item(0)->setIcon(QIcon("../Electronic/pojemnosciowa.jpg"));

    ui->listWidget->addItem("Photo Transistor");
    ui->listWidget->item(1)->setIcon(QIcon("../Electronic/fototransistor.png"));

    ui->listWidget->addItem("Flashing Capacity Diode");
    ui->listWidget->item(2)->setIcon(QIcon("../Electronic/pojemnosciowa.jpg"));

    ui->listWidget->addItem("Flashing Photo Transistor");
    ui->listWidget->item(3)->setIcon(QIcon("../Electronic/fototransistor.png"));

    itm = NULL;

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    spin = new QLabel;
    espin = new QLineEdit;
    lineColorButton = new QPushButton;
    interiorColorButton = new QPushButton;
    time = new QLabel;
    etime = new QLineEdit;

    //connections
    connect(ui->listWidget, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(addElem(QListWidgetItem*)));
    connect(ui->actionQuit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(whichSelected()));
    connect(espin, SIGNAL(editingFinished()), this, SLOT(paintElem()));
    connect(lineColorButton, SIGNAL(released()), this, SLOT(lineButtonClicked()));
    connect(interiorColorButton, SIGNAL(released()), this, SLOT(interiorButtonClicked()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(actionSave()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(actionOpen()));
    connect(etime, SIGNAL(editingFinished()), this, SLOT(paintElem()));

    gboxLayout = new QGridLayout;
    ui->groupBox->setLayout(gboxLayout);

    //toolBar

    ui->mainToolBar->addAction(QIcon("../Electronic/horizontal.png"), "Horizontal");
    ui->mainToolBar->addAction(QIcon("../Electronic/vertical.png"), "Vertical");

    connect(ui->mainToolBar, SIGNAL(actionTriggered(QAction*)), this, SLOT(actionMenuBar(QAction*)));
    connect(ui->menuTools, SIGNAL(triggered(QAction*)), this, SLOT(actionMenuBar(QAction*)));
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
    delete itm;
    delete actualElem;
    delete etime;
    delete time;
}

enum {widgetCdiode, widgetFtransistor, widgetFlashingCdiode, widgetFlashingFtransistor};

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
    else
    if(itm == ui->listWidget->item(widgetFlashingCdiode))
    {
        QContainer.append(new FlashingCdiodeItem);
    }else
    if(itm == ui->listWidget->item(widgetFlashingFtransistor))
    {
        QContainer.append(new FlashingFtransistorItem);
    }

    container+QContainer.last();

    scene->addItem(QContainer.at(QContainer.size() - 1));
}

void MainWindow::modElem(QGraphicsItem *itm)
{
    spin->setText(tr("spin"));
    espin->setMaximumSize(QSize(10000, 25));

    gboxLayout->addWidget(spin, 1, 1);
    gboxLayout->addWidget(espin,1, 2);

    interiorColorButton->setText(tr("interior color"));
    lineColorButton->setText(tr("line color"));

    gboxLayout->addWidget(interiorColorButton, 2, 1);
    gboxLayout->addWidget(lineColorButton, 3, 1);

    time->setText(tr("time"));
    etime->setMaximumSize(QSize(10000, 25));

    CdiodeItem *citm;
    FtransistorItem *fitm;
    FlashingCdiodeItem *fcitm;
    FlashingFtransistorItem *ffitm;

    if((actualElem = dynamic_cast<QElem*>(itm))!=NULL)
    {
        lineColor.setRed(actualElem->getLineRed());
        lineColor.setGreen(actualElem->getLineGreen());
        lineColor.setBlue(actualElem->getLineBlue());

        interiorColor.setRed(actualElem->getInteriorRed());
        interiorColor.setGreen(actualElem->getInteriorGreen());
        interiorColor.setBlue(actualElem->getInteriorBlue());

        espin->setText(QString::number(actualElem->getSpin()));

        time->hide();
        etime->hide();
    }

    actualElem->setBacklight(true);

    if((citm = dynamic_cast<CdiodeItem*>(actualElem))!=NULL)
    {
        ui->groupBox->setTitle(tr("&Capacity Diode"));
    }else
    if((fitm = dynamic_cast<FtransistorItem*>(actualElem))!=NULL)
    {
        ui->groupBox->setTitle(tr("&Photo Transistor"));
    }else
    if((fcitm = dynamic_cast<FlashingCdiodeItem*>(actualElem))!=NULL)
    {
        ui->groupBox->setTitle(tr("&Flashing Capacity Diode"));
        gboxLayout->addWidget(time, 4, 1);
        gboxLayout->addWidget(etime, 4, 2);
        etime->setText(QString::number(fcitm->getTime()));
        time->show();
        etime->show();
    }else
    if((ffitm = dynamic_cast<FlashingFtransistorItem*>(actualElem))!=NULL)
    {
        ui->groupBox->setTitle(tr("&Flashing Photo Transistor"));
        gboxLayout->addWidget(time, 4, 1);
        gboxLayout->addWidget(etime, 4, 2);
        etime->setText(QString::number(ffitm->getTime()));
        time->show();
        etime->show();
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

        FlashingCdiodeItem *fcitm = dynamic_cast<FlashingCdiodeItem*>(actualElem);
        FlashingFtransistorItem *ffitm = dynamic_cast<FlashingFtransistorItem*>(actualElem);

        if(fcitm != NULL)
        {
            fcitm->setTime(etime->text().toFloat());
        }else
        if(ffitm != NULL)
        {
            ffitm->setTime(etime->text().toFloat());
        }

        actualElem->update();
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

void MainWindow::actionSave()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save file"),
            mCurrentPath, "SVG files (*.svg)");
    if(fileName.isEmpty()) return;

    int shiftX = 0;
    int shiftY = 0;

    for(int i = 0; i < QContainer.size(); i++)
    {
        if(QContainer.at(i)->x() < shiftX)
        {
            shiftX = QContainer.at(i)->x();
        }

        if(QContainer.at(i)->y() < shiftY)
        {
            shiftY = QContainer.at(i)->y();
        }
    }

    qDebug()<<QString::number(shiftX)<<QString::number(shiftY);

    for(int i = 0; i < QContainer.size(); i++)
    {
        container.container.at(i)->setX(QContainer.at(i)->x() - shiftX);
        container.container.at(i)->setY(QContainer.at(i)->y() - shiftY);
    }

    actualElem->setBacklight(false);
    actualElem->update();

    if(!fileName.isEmpty())
    {
        QSvgGenerator svgGen;

        svgGen.setFileName(fileName);
        svgGen.setSize(QSize(200, 200));
        svgGen.setViewBox(QRect(0, 0, 200, 200));

        QPainter painter(&svgGen);
        scene->render(&painter);
        std::string stdFileName = fileName.toStdString();

        QFileInfo info(fileName);
        QString txtFileName = info.path() + QDir::separator() + info.completeBaseName() + ".txt";
        stdFileName = txtFileName.toStdString();
        container.expToTxt(stdFileName);
    }

    actualElem->setBacklight(true);
    actualElem->update();
}

void MainWindow::actionOpen()
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
        actualElem = NULL;

        std::string stdFileName = fileName.toStdString();
        container.impFromTxt(stdFileName, factory);

        for(int i=0; i < (int)container.container.size(); i++)
        {
            if(dynamic_cast<FlashingCdiode*>(container.container.at(i)) != NULL)
            {
                QContainer.append(new FlashingCdiodeItem);
            }else
            if(dynamic_cast<FlashingFtransistor*>(container.container.at(i)) != NULL)
            {
                QContainer.append(new FlashingFtransistorItem);
            }else
            if(dynamic_cast<Cdiode*>(container.container.at(i)) != NULL)
            {
                QContainer.append(new CdiodeItem);
            }else
            if(dynamic_cast<Ftransistor*>(container.container.at(i)) != NULL)
            {
                QContainer.append(new FtransistorItem);
            }

            QContainer.last()->setPos(QPointF(container.container.at(i)->getX(),
                                              container.container.at(i)->getY()));

            QContainer.last()->setInteriorRed(container.container.at(i)->getInteriorRed());
            QContainer.last()->setInteriorGreen(container.container.at(i)->getInteriorGreen());
            QContainer.last()->setInteriorBlue(container.container.at(i)->getInteriorBlue());

            QContainer.last()->setLineRed(container.container.at(i)->getLineRed());
            QContainer.last()->setLineGreen(container.container.at(i)->getLineGreen());
            QContainer.last()->setLineBlue(container.container.at(i)->getLineBlue());

            QContainer.last()->setSpin(container.container.at(i)->getSpin());
            QContainer.last()->setRotation(container.container.at(i)->getSpin());

            scene->addItem(QContainer.at(i));
        }
    }
}

void MainWindow::actionHorizontal()
{
    int shiftY = 0;
    int multipleX = 100;

    int i;
    int z;
    int j;

    for(i = 0; i < cList.size(); i++)
    {
        cList.at(i)->setPos(QPointF(i * multipleX, shiftY));
    }

    for(z = 0; z < fcList.size(); z++)
    {
        fcList.at(z)->setPos(QPointF((z + i) * multipleX, shiftY));
    }

    for(j = 0; j < fList.size(); j++)
    {
        fList.at(j)->setPos(QPointF((i + z + j) * multipleX, 0));
    }

    for(int k = 0; k < ffList.size(); k++)
    {
        ffList.at(k)->setPos(QPointF((z + i + j + k) * multipleX, 0));
    }//ustawienie lokalizacji

}

void MainWindow::actionVertical()
{
    int shiftX = 0;
    int multipleY = 100;

    int i;
    int z;
    int j;

    for(i = 0; i < cList.size(); i++)
    {
        cList.at(i)->setPos(QPointF(shiftX, i * multipleY));
    }

    for(z = 0; z < fcList.size(); z++)
    {
        fcList.at(z)->setPos(QPointF(shiftX, (z + i) * multipleY));
    }

    for(j = 0; j < fList.size(); j++)
    {
        fList.at(j)->setPos(QPointF(0, (i + j + z) * multipleY));
    }

    for(int k = 0; k < ffList.size(); k++)
    {
        ffList.at(k)->setPos(QPointF(0, (z + i + j + k) * multipleY));
    }//ustawienie lokalizacji
}

void MainWindow::actionMenuBar(QAction *action)
{
    cList.clear();
    fcList.clear();
    fList.clear();
    ffList.clear();
    //wyczyszczenie list

    for(int i = 0; i < QContainer.size(); i++)
    {
        if(dynamic_cast<CdiodeItem*>(QContainer.at(i)) != NULL)
        {
            cList.append(dynamic_cast<CdiodeItem*>(QContainer.at(i)));
        }else
        if(dynamic_cast<FlashingCdiodeItem*>(QContainer.at(i)) != NULL)
        {
            fcList.append(dynamic_cast<FlashingCdiodeItem*>(QContainer.at(i)));
        }else
        if(dynamic_cast<FlashingFtransistorItem*>(QContainer.at(i)) != NULL)
        {
            ffList.append(dynamic_cast<FlashingFtransistorItem*>(QContainer.at(i)));
        }
        else
        {
            fList.append(dynamic_cast<FtransistorItem*>(QContainer.at(i)));
        }
    } // zapisanie kontenera do list

    QList<QAction*>menuBarActions = ui->mainToolBar->actions();
    QList<QAction*>menuToolsActions = ui->menuTools->actions();

    if(menuBarActions.at(0) == action || menuToolsActions.at(0) == action)
    {
        actionHorizontal();
    }else
    if(menuBarActions.at(1) == action || menuToolsActions.at(1) == action)
    {
        actionVertical();
    }

    for(int i = 0; i < QContainer.size(); i++)
    {
        container.container.at(i)->setX(QContainer.at(i)->x());
        container.container.at(i)->setY(QContainer.at(i)->y());

        QContainer.at(i)->update();
    }//zczytanie do kontenera z dokumentu

    //sa posortwane na scenie
}
