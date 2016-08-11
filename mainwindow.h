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
#include <QColorDialog>

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

    Dokument container;
    QGraphicsItem *itm;

    QLabel *spin;
    QLineEdit *espin;
    QPushButton *lineColorButton;
    QPushButton *interiorColorButton;

    QColor lineColor;
    QColor interiorColor;

private slots:
    void addElem(QListWidgetItem *);
    void modElem(QGraphicsItem *);
    void whichSelected();
    void paintElem();
    void lineButtonClicked();
    void interiorButtonClicked();
};

#endif // MAINWINDOW_H
