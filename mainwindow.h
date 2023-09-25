#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "administradora.h"
#include "neurona.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void llenarTabla();

    void buscarPorNeurona();

private:
    Ui::MainWindow *ui;
    Neurona n;
    administradora administrarNeuronas;
};
#endif // MAINWINDOW_H
