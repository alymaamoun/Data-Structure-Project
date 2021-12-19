#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xml-consistency.h"
#include <string>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Openfile_clicked()
{
        QString filter = "All Files (*.*) ;; XML Files (*.xml)";
        QString filename = QFileDialog::getOpenFileName(this,"Open File","C://",filter);
        QFile file(filename);
        error.clear();
        conc.clear();

        size=0;

        currentFile = filename;
        if(!file.open(QIODevice::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this,"Warning" , "Cannot Open File : " + file.errorString());
        }

        QTextStream in(&file);
        QString text = in.readAll();
        size= FileParser(filename.toStdString(),XML);
       // ui->Edited_File_plainTextEdit->setPlainText(QString::fromStdString(IsConsistentFile(XML,size,&error) ));

        conc=text.toStdString();
        ui->Original_File_plainTextEdit->setPlainText(text);
        ui->Edited_File_plainTextEdit->setPlainText(" ");
        trials=0;

        file.close();

}

void MainWindow::on_About_clicked()
{
    QMessageBox::information(this,"About Project","This project is to : \n 1-Check consistency and fix errors \n 2-pretiffy \n 3- Convert to Json \n 4- compress \n 5-decompress");
}

void MainWindow::on_Fix_clicked()
{

     if(trials==0)
     {
     conc=IsConsistentFile(XML,size,&error);

     ui->Edited_File_plainTextEdit->setPlainText(QString::fromStdString(conc ));
     QMessageBox::information(this,"Errors",QString::fromStdString(error));
     if(error.find("tag") != -1)
     {
         missedtags=true;

     }
     else
     {
        missedtags=false;
     }
     trials++;
     }
     else
     {
         QMessageBox::information(this,"Errors","Already fixed!");
         QMessageBox::information(this,"Errors",QString::fromStdString(error));
     }


}


void MainWindow::on_Minify_clicked()
{
    Minify(&conc);
    ui->Edited_File_plainTextEdit->setPlainText(QString::fromStdString(conc ));

}

void MainWindow::on_Compress_clicked()
{

    root =encoding(conc,calcFreq(conc),conc.length());
    coded= encode(root,conc,conc.length());
   // ui->Edited_File_plainTextEdit->setPlainText(QString::fromStdString(coded ));
    long long codedlength = coded.length();
        string redundantBitsNum = one_byte_to_bitstring(8 - (codedlength % 8));
        int num_of_zeros = 8 - (codedlength % 8);
        string addedZeros = "";
        string appended;
        for (int i = 0; i < num_of_zeros; i++)
        {
            addedZeros = addedZeros + "0";
        }
        appended = redundantBitsNum + coded + addedZeros;
        vector<unsigned char> outByteArr = bitstring_to_bytes(appended);
        fstream encodedFile;
        QString filter = "All Files (*.*) ;; XML Files (*.txt)";
        QString filename1 = QFileDialog::getOpenFileName(this,"Open File","C://",filter);
        QFile file(filename1);
        currentFile = filename1;
        encodedFile.open(filename1.toStdString(), ios::out);
        if (encodedFile.is_open())
        {
            long long size_of_vect = outByteArr.size();
            for (int i = 0; i < size_of_vect; i++)
        {
                encodedFile << outByteArr[i];
            }
        }
        if(!file.open(QIODevice::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this,"Warning" , "Cannot Open File : " + file.errorString());
        }
        QTextStream in(&file);
        QString text1 = in.readAll();
        ui->Edited_File_plainTextEdit->setPlainText(text1);
        file.close();




}

void MainWindow::on_Decompress_clicked()
{
    string decoded=decode_file(root,coded);
    ui->Edited_File_plainTextEdit->setPlainText(QString::fromStdString(decoded ));
}

void MainWindow::on_XMLtoJSON_clicked()
{
    if(trials)
    {
        if(missedtags)
        {
            QMessageBox::information(this,"Errors","Your code contained fatal error,using this function in this case will lead the program to crash!");
        }
        else{
            Minify(&conc);
            ui->Edited_File_plainTextEdit->setPlainText(QString::fromStdString(x2json(conc,0) ));
        }
    }
    else
        QMessageBox::information(this,"Errors","Fix errors in your code first");
}

void MainWindow::on_Format_clicked()
{

    if(trials)
        if(missedtags)
        {
            QMessageBox::information(this,"Errors","Your code contained fatal error,using this function in this case will lead the program to crash!");
        }
    else
        {

            ui->Edited_File_plainTextEdit->setPlainText(QString::fromStdString(Formatter(conc,0) ));
        }
    else
        QMessageBox::information(this,"Errors","Fix errors in your code first");
}
