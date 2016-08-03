#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName ("UTF-8"));
    ui->setupUi(this);

    ui->listWidget->addItem("Capacity Diode");
    ui->listWidget->item(0)->setIcon(QIcon("../Electronic/pojemnosciowa.jpg"));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    cdiode = new CdiodeItem*;
    cdiodectr = 0;

    connect(ui->listWidget, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(addCdiode(QListWidgetItem*)));
    connect(ui->actionZako_cz, SIGNAL(triggered(bool)), qApp, SLOT(quit()));

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
    qDebug()<<itm->text() + " " + QString::number(cdiodectr);
}
