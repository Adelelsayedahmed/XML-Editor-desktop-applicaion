#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.cpp"
 string FilePath;
 string OriginalData;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()  //open
{
    QString filter = "All Files (.) ;; XML Files (*.xml)";
            QString filename = QFileDialog::getOpenFileName(this,"Open File","C://",filter);
            QFile file(filename);

            if(!file.open(QIODevice::ReadOnly | QFile::Text))
            {
                QMessageBox::warning(this,"Warning" , "Cannot Open File : " + file.errorString());
            }
            setWindowTitle(filename);
            QTextStream in(&file);
            QString text = in.readAll();

            ui->plainTextEdit->setPlainText(text);
            OriginalData = text.toStdString();
            file.close();
            //FilePath = QMessageBox:: information(this,tr("filename"),filename);
            FilePath =  filename.toStdString() ;
}


void MainWindow::on_pushButton_2_clicked() //format
{

    vector <string> file_lines = xml_cutter(FilePath);
        vector <string> file_lines_without_comments;
        FileWithoutComments(file_lines_without_comments, file_lines);
        file_lines = file_lines_without_comments;
        pretty(file_lines_without_comments);
        vector <string> XML_Prettified;
        XML_Prettified = file_lines_without_comments;
        vector <int> lines_indent(XML_Prettified.size());
        XML_pretify(XML_Prettified, lines_indent);
        indent(XML_Prettified, lines_indent);
        string s =  vectortostring(XML_Prettified);
     //string s =  vectortostring(xml_cutter(FilePath));
    QString text = QString::fromStdString(s);
    ui->plainTextEdit->setPlainText(text);
}


void MainWindow::on_pushButton_3_clicked()   //JSON
{

    vector <string> file_lines = xml_cutter(FilePath);
        vector <string> file_lines_without_comments;
        FileWithoutComments(file_lines_without_comments, file_lines);
        file_lines = file_lines_without_comments;
        vector <Node*> nodes;
        stack <int> tags;
        xml_tree tree;
        xml_tree_implemetation(file_lines, nodes, tree, tags);
        vector <string> XML_Json;
        int x = 0;
        stack <int> tabs;
        string json = "{\n";
        XML_json(json, tree, tree.get_root(), x, 0, 0, 0);
        string ss = json;
            QString text = QString::fromStdString(ss);
            ui->plainTextEdit->setPlainText(text);
}

void MainWindow::on_pushButton_4_clicked()   //Minify

{

}


vector <int> v = compress(FilePath);
void MainWindow::on_pushButton_5_clicked()   //Compress
{

        string xx = xmltostring(FilePath);
        savingcompressfile(xx , v , FilePath);
}


void MainWindow::on_pushButton_6_clicked()  //Decompress
{
    string s = decompress(v);
        ofstream fillle;
        fillle.open(FilePath);
        fillle << s;
        fillle.close();
}


void MainWindow::on_pushButton_7_clicked()  //Correct
{
    vector <string> file = ReadFromFile(FilePath);
    stack <int> y =edit(file);
    string s =  vectortostring (file);



    if (y.empty() == 1)
        {
            string ss = "\n No errors found \n " + s;
            QString text = QString::fromStdString(ss);
            ui->plainTextEdit->setPlainText(text);
        }
    else {
        string ss;
        for (int i = 0; i <= y.size(); i++)
            {
                ss += "Error in line " + to_string((y.top()) + 1) + "\n";

                y.pop();
            }

            s = s + ss;
            QString text = QString::fromStdString(s);
            ui->plainTextEdit->setPlainText(text);
        }

}
