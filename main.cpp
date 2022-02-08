#include "mainwindow.h"
#include "GRAPH.h"
#include "XMLTree.h"
#include <ostream>
#include <QApplication>


using namespace std;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

void Graphfile(SocialGraph& Graph){

      ofstream myfile("graph.dot");
//    string Colors[] = {"[color=blue]\n","[color=red]\n","[color=green]\n"};

      myfile<<"digraph{\n";
      myfile<<"bgcolor=\"lightyellow\"\n";

      for(int i =1; i<Graph.usersSocialNodes.size(); i++){
          SocialNode* user = Graph.usersSocialNodes[i];
                  myfile << user->id ; // << Colors[i-1];
                  myfile << user->id<<"-> {";
            for(int k = 0; k<user->followers.size(); k++){
                myfile<<user->followers[k]<<" ";
            }
            myfile<<"}\n";
      }
      myfile<<"}";

      myfile.close();
}
