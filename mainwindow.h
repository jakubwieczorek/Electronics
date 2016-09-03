#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include "flashingcdiodeitem.h"
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

    QList<CdiodeItem*>cList;
    QList<FtransistorItem*>fList;
    QList<FlashingCdiodeItem*>fcList;

    Factory factory;

    QLabel *spin;
    QLineEdit *espin;
    QPushButton *lineColorButton;
    QPushButton *interiorColorButton;
    QLabel *time;
    QLineEdit *etime;

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
    void actionSave();
    void actionOpen();
    void actionHorizontal();
    void actionVertical();
    void actionMenuBar(QAction *action);
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
