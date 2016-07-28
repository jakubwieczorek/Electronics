#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i = 1; i<10; i++)
    {
        ui->listWidget->addItem(QString::number(i) + ". Element");
    }

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    square = new MySquare;

    scene->addItem(square);
}

MainWindow::~MainWindow()
{
    delete ui;
}
