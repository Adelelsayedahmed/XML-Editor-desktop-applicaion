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
        xml_tree tree;
        stack <int> tags;
        xml_tree_implemetation(file_lines, nodes ,tree , tags);
        string ss = xml_to_json(tree);
        QString text = QString::fromStdString(ss);
        ui->plainTextEdit->setPlainText(text);
}

void MainWindow::on_pushButton_4_clicked()   //Minify

{
    vector <string> v = ReadFromFile(FilePath);
        string minifystring = minifying(v);
        QString text = QString::fromStdString(minifystring);
        ui->plainTextEdit->setPlainText(text);
}



void MainWindow::on_pushButton_5_clicked()   //Compress
{
    vector <int> v = compress(FilePath);
        string xx = xmltostring(FilePath);
        string xmll = "xmlcompressed.xml";
            string newfilepath =  FilePath.substr(0, FilePath.find_last_of("/")+1)+xmll;

        savingcompressfile(xx , v , FilePath );
       string compress = vectortostring(ReadFromFile(newfilepath));
            QString text = QString::fromStdString(compress);
            ui->plainTextEdit->setPlainText(text);


}


void MainWindow::on_pushButton_6_clicked()  //Decompress
{
     vector <int> v = compress(FilePath);
    string s = decompress(v);
    QString text = QString::fromStdString(s);
        ui->plainTextEdit->setPlainText(text);
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



void MainWindow::on_pushButton_8_clicked()   // consistency
{
    vector <string> file = ReadFromFile(FilePath);
        if (check_consistency(file) == 1)
        {

            QString text = QString::fromStdString("The file is balanced ");
            ui->plainTextEdit->setPlainText(text);
        }
        else
        {
            QString text = QString::fromStdString("ERROR! the file is not balanced use correct button");
            ui->plainTextEdit->setPlainText(text);
        }
}






void MainWindow::on_pushButton_9_clicked()  //to show graph
{
    XMLTree tree(OriginalData);
    SocialGraph Graph(tree);
    Graphfile(Graph);
    system("dot -Tpng -O graph.dot");
    QPixmap p("graph.dot.png");
    ui->label->setPixmap(p);
}

