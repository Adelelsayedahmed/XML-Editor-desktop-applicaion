#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "compression.h"
#include"consistance.h"
#include "editing.h"
#include "json.h"
#include"minify.h"
#include"prettify.h"
#include"readfromfile.h"
#include"tree.h"
#include"xmlcutter.h"
#include <QMainWindow>
#include<string>
#include<stack>
#include<sstream>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>

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

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_horizontalScrollBar_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
