#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include "cdiodeitem.h"
#include "ui_mainwindow.h"
#include <dokument.h>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGridLayout *gboxLayout;
    CdiodeItem **cdiode;
    int cdiodectr;
    Dokument container;
    QGraphicsItem *itm;

    QLabel *width;
    QLineEdit *ewidth;
    QLabel *spin;
    QLineEdit *espin;
    QPushButton *colorButton;

private slots:
    void addCdiode(QListWidgetItem *);
    void modCdiode(QGraphicsItem *);
    void whichSelected();
    void paintCdiode();
};

#endif // MAINWINDOW_H
