#ifndef FUNCTIONSFOREDIT_H_INCLUDED
#define FUNCTIONSFOREDIT_H_INCLUDED

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include <cstddef>

using namespace std;



int isSpace(vector<string> &file,stack<int> &error_line) ;
void delting (vector<string> &file ,int Blanksnum) ;
int numberofblanks(vector<string> file) ;
void shiftting(vector<string> &file_lines , int start , int end , int blank) ;
int  check_Corr_closedtags (vector<string> &file , stack<string> &openedtags ,stack<string> &closedtags ,stack<int> &error_line, int index ,  int lineindex  , int i );
int  checking_opendtags(vector<string> &file , stack<string> &openedtags ,stack<string> closedtags ,stack<int> &error_line, int index ,  int &lineindex  , int i ,vector<string> tempfile);




#endif // FUNCTIONSFOREDIT_H_INCLUDED
