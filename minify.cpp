#include "minify.h"
string minifying(vector <string> file)
{

size_t found ;
string minified ="" ;

    for (int i = 0  ; i <file.size() ;i++)
     {
       found =file[i].find_first_not_of("\t") ;
       if (found != string::npos) {file[i].erase(0,found) ;}
     }

    for (int i = 0 ; i<file.size();i++)
     {
       found =file[i].find_first_not_of(" ") ;
       if (found != string::npos) {file[i].erase(0,found) ;}
     }

    for(int i=0 ; i <file.size();i++)
      minified+= file[i] ;

return minified ;
}
