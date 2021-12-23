#include "FunctionsForEdit.h"
int isSpace(vector<string> &file,stack<int> &error_line)
{
    int counter = 0 ;
size_t found  ;
    for  (int i = 0 ; i <file.size() ;  i++)
        {
         found =file[i].find_first_not_of(" ") ;
         if (found == string::npos)
            {
                error_line.push(i);
                file[i]="";counter++;
            }
        }

return counter ;

}


void delting (vector<string> &file ,int Blanksnum)
{
for (int i = 0; i < Blanksnum; i++)
    {
        file.pop_back();
    }


}
int numberofblanks(vector<string> file)
{
int counter =  0 ;
for (int i = 0 ;i<file.size();i++)
    {
    if  (file[i] == "\0" )
    counter ++ ;
    }
return  counter ;
}


void shiftting(vector<string> &file_lines , int start , int end , int blank)
{
    for (int i = start; i < end; i++)
    {
        if (file_lines[i] == "\0" && file_lines[i + 1] == "\0")
          {
            shiftting( file_lines , i+1 , end , blank);
          }

        if (file_lines[i] == "\0" && file_lines[i + 1] != "\0")
          {
            for (int j = i; j < end; j++)
             {
                file_lines[j] = file_lines[j + 1];
             }
          }
    }



}

 int  check_Corr_closedtags (vector<string> &file , stack<string> &openedtags ,stack<string> &closedtags ,stack< int> &error_line, int index ,  int lineindex  , int i )
 {
 if ( openedtags.empty() == 1 )                 //   ERROR! due to closing the tag without opening
    {
            if (error_line.empty() !=1){if(lineindex!=error_line.top()) error_line.push(lineindex) ;}
            else error_line.push(lineindex);

      int s = (closedtags.top().size()+3) ;
      file[lineindex].erase(index,s) ;            // we should delete this tag
      closedtags.pop() ;
      return( i-s);
    }
    else if (closedtags.top() != openedtags.top() )         // ERROR! due to unmatched tags
    {
            if (error_line.empty() !=1){if(lineindex!=error_line.top()) error_line.push(lineindex) ;}   //     saving  this error ;
            else error_line.push(lineindex);

    int opensize   =  openedtags.top().size() ;
    int closesize  =  closedtags.top().size() ;
            /* ****** we need to remove this closing tag and add the right one ******  */

    file[lineindex].erase(index+2,closesize) ;
    file[lineindex].insert(index+2,openedtags.top());
    i= i+(opensize-closesize);
    closedtags.pop();
    openedtags.pop();
return i ;
    }


    else  // no error ;
    {
        openedtags.pop();
        closedtags.pop();
        return i  ;

    }


 }
int  checking_opendtags(vector<string> &file , stack<string> &openedtags ,stack<string> closedtags ,stack<int> &error_line, int index ,  int &lineindex  , int i ,vector<string> tempfile)
{
string  data= "</"+openedtags.top()+">" ; ;
bool flag = false ;  bool flagdata = false;
int row_data , row ,  col_data , col ;
string temp = file[lineindex] ;
temp =  temp.erase(0,i);
tempfile[lineindex]=temp ;

size_t found ; size_t ft;

int j = lineindex ;

// search for <

while (j<file.size())
    {
       found =tempfile[j].find("<");
       if (found != string::npos)
        {
            if ( tempfile[j][found+1]!='/')
             {  flag = true ;
                row = j ;
                col = found ;
                break ;
             }
             else break  ;

        }
        j++ ;
    }

    j=lineindex;
    while (j<file.size())
    {
       ft =tempfile[j].find_first_not_of(" ") ;
       if (ft != string::npos)
        {

                flagdata = true ;
                row_data = j ;
                col_data = ft;
                break ;
        }
             j++ ;

    }


    if ( flagdata&&flag )
    {
            if ((row_data<row) ||  (row_data==row && (col_data<col)) )
        {

        if (error_line.empty() !=1){if(row!=error_line.top()) error_line.push(lineindex) ;}
            else error_line.push(row);



            if (lineindex!=row)
                {       if (row > row_data && row_data==lineindex){file[row-1].append(data) ;lineindex=row ;openedtags.pop()  ; return 0 ; }
                        else  if (row>row_data && row!=lineindex){file.insert(file.begin()+row , data ) ; lineindex = row+1 ;openedtags.pop();return 0;}
                       else {
                       openedtags.pop() ;
                       file[row].insert(col,data)  ;
                       lineindex  = row ;
                       return col+data.size() ;
                            }
                }

                else                // row =  line index
                {
                    openedtags.pop();
                    file[row].insert(i+col,data) ;
                    return i  + col+data.size() ;
                }
        }
    }
return i  ;


}

