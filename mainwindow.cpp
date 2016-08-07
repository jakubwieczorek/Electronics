#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

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
    cdiodectr = 0;

    width = new QLabel;
    ewidth = new QLineEdit;
    spin = new QLabel;
    espin = new QLineEdit;
    colorButton = new QPushButton;

    //connections
    connect(ui->listWidget, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(addCdiode(QListWidgetItem*)));
    connect(ui->actionZako_cz, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(whichSelected()));
    connect(ewidth, SIGNAL(editingFinished()), this, SLOT(paintCdiode()));

    gboxLayout = new QGridLayout;
    ui->groupBox->setLayout(gboxLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    for(int i=0; i<cdiodectr; i++)
    {
        delete cdiode[i];
    }
    delete cdiode;
    delete width;
    delete ewidth;
    delete spin;
    delete colorButton;
    delete gboxLayout;
}

void MainWindow::addCdiode(QListWidgetItem *itm)
{
    if(itm == ui->listWidget->item(0))
    {
        try
        {
            cdiode[cdiodectr] = new CdiodeItem;
        }
        catch (std::bad_alloc& msg)
        {
            qDebug()<<"bad_alloc caught: "<<msg.what();
            return;
        }

        scene->addItem(cdiode[cdiodectr++]);
    }
    //qDebug()<<itm->text() + " " + QString::number(cdiodectr);
}

void MainWindow::modCdiode(QGraphicsItem *itm)
{
    CdiodeItem *citm = dynamic_cast<CdiodeItem*>(itm);
    ui->groupBox->setTitle(tr("&Capacity Diode"));

    width->setText(tr("width"));
    ewidth->setText(tr("100"));

    gboxLayout->addWidget(width,1,1);
    gboxLayout->addWidget(ewidth,1,2);

    spin->setText(tr("spin"));
    espin->setText(tr("0"));
    espin->setMaximumSize(QSize(10000,25));

    gboxLayout->addWidget(spin, 2,1);
    gboxLayout->addWidget(espin,2,2);

    colorButton->setText(tr("interior color"));

    gboxLayout->addWidget(colorButton, 3, 1);
}

void MainWindow::whichSelected()
{
    QList <QGraphicsItem*>itemsList = scene->selectedItems();

    for(int i=0; i<itemsList.count(); i++)
    {
        itm = itemsList.at(i);
        if(itm->isSelected() == true) break;
    }

    modCdiode(itm);

    for(int i=0; i<itemsList.count(); i++)
    {
        itemsList.at(i)->setSelected(false);
    }
}

void MainWindow::paintCdiode()
{
    CdiodeItem *citm = dynamic_cast<CdiodeItem*>(itm);
    citm->setRotation(90);
    itm->update();
}
