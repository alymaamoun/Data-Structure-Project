#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include <string>
#include "xml-consistency.h"
#include "minifying.h"
#include "compression.h"
#include "xml2json.h"
#include "xml_formatter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    string error;
    string  XML[1000];
    string conc;
    string nospace;
    int size;
    struct Huffman_node* root;
    string coded;
    int trials=0;

    bool missedtags=false;

private slots:
    void on_Openfile_clicked();

    void on_About_clicked();

    void on_Fix_clicked();



    void on_Minify_clicked();

    void on_Compress_clicked();

    void on_Decompress_clicked();

    void on_XMLtoJSON_clicked();

    void on_Format_clicked();

private:
    Ui::MainWindow *ui;
     QString currentFile;
};

#endif // MAINWINDOW_H
