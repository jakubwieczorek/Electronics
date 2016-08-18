#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include "cdiodeitem.h"
#include "ftransistoritem.h"
#include "ui_mainwindow.h"
#include <dokument.h>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QColorDialog>
#include <QVector>

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

    Dokument container;
    QGraphicsItem *itm;
    QElem *actualElem;
    QVector<QElem*>QContainer;

    Factory factory;

    QLabel *spin;
    QLineEdit *espin;
    QPushButton *lineColorButton;
    QPushButton *interiorColorButton;

    QColor lineColor;
    QColor interiorColor;

    QString mCurrentPath;

private slots:
    void addElem(QListWidgetItem *);
    void modElem(QGraphicsItem *);
    void whichSelected();
    void paintElem();
    void lineButtonClicked();
    void interiorButtonClicked();
    void actionZapisz();
    void actionOtworz();
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
