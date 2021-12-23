#include "editing.h"
stack<int> edit (vector <string> &file )
{
stack<string> openedtags ;
stack<string> closedtags ;
stack<int> error_line ;
string line ;
string temp ;
int lineindex = 0 ;
int i = 0;
int index ;
string pushing  ;

int Blanksnum =numberofblanks(file) ;
shiftting(file, 0 , file.size()-1, Blanksnum );
delting(file,Blanksnum );
int spaces = isSpace(file , error_line) ;
shiftting(file, 0 , file.size()-1, spaces );
delting(file,spaces );


while ( lineindex<file.size() )
    {
    line = file[lineindex] ;
    temp = "";
        while (i<file[lineindex].size() )
        {
          if (line[i]=='<')
            {   index = i ;
              while( line[i] != '>' && i<line.size() && line[i]!=' ' )
                {
                  temp.push_back(line[i]) ;
                  i++ ;
                }

                if ( i==line.size() )               //  there is an error the tag must be close by '>'
                    {

                                 // save the line of the  error
                        if (error_line.empty() !=1){if(lineindex!=error_line.top()) error_line.push(lineindex) ;}     // save the line of the  error
                    else error_line.push(lineindex);

                        file[lineindex].insert(i,">");      // correcting the error

                        if (line[i-1] =='<' )
                            {
                        file[lineindex].erase(i-1,1);
                        i-- ;
                        temp.pop_back();
                           }
                           i++ ;
                        if (line[index+1] == '/')
                           {
                           temp.erase(0,2) ;
                           closedtags.push(temp) ;
                           temp="";
                          i = check_Corr_closedtags (file , openedtags ,closedtags , error_line,  index , lineindex ,i) ;
                         line = file[lineindex] ;

                           }
                        else    // this  is opening tags
                           {
                            temp.erase(0,1) ;
                            if(temp[temp.size()-1]!='/')
                            {
                            openedtags.push(temp);
                            i= checking_opendtags(file , openedtags ,closedtags , error_line,  index , lineindex ,i ,file) ;

                            line = file[lineindex] ;
                            }
                                temp="";
                           }
                    }
                else if (line[i]==' ')               //  there is an error the tag must be close by '>'
                    {
                    file[lineindex].erase(i,1);
                    file[lineindex].insert(i,">");  // correcting the error
                   i++;
                    if (error_line.empty() !=1){if(lineindex!=error_line.top()) error_line.push(lineindex) ;}     // save the line of the  error
                    else error_line.push(lineindex);

                    /* check  is this tag after correction is opening or closing */
                        if (line[index+1] == '/')
                           {

                            temp.erase(0,2) ;
                            closedtags.push(temp) ;
                            temp="";
                            i = check_Corr_closedtags (file , openedtags ,closedtags , error_line,  index , lineindex ,i ) ;
                            line = file[lineindex] ;

                           }
                        else
                           {
                            temp.erase(0,1) ;           // this is opening  tag
                           if(temp[temp.size()-1]!='/')
                            {
                            openedtags.push(temp);
                            i= checking_opendtags(file , openedtags ,closedtags , error_line,  index , lineindex ,i ,file) ;
                            temp = "" ;
                            line = file[lineindex] ;
                            }
                            temp  = ""  ;
                           }

                    }


                else if (line[i]=='>')                     // there is no error
                    {   i++ ;
                        if (temp[1]!='/')                     // this is opening tag
                        {
                        temp.erase(0,1) ;
                       if(temp[temp.size()-1]!='/')
                            {
                            openedtags.push(temp);
                            i= checking_opendtags(file , openedtags ,closedtags , error_line,  index , lineindex ,i ,file) ;
                            temp = "" ;
                            line = file[lineindex] ;
                            }
                        temp=""  ;
                        }
                        else                                // this is closing tag
                        {
                        temp.erase(0,2);
                        closedtags.push(temp) ;
                       i =check_Corr_closedtags (file , openedtags ,closedtags , error_line,  index , lineindex , i) ;
                       line = file[lineindex] ;
                       temp = "" ;
                        }
                    }
            }
        else i++ ;

        }
            i=0 ;
            lineindex++;

    }


        /* PUSHING THE UNCLOSED TAGS  */
    while (openedtags.empty()==0)
        {
        pushing = "</"+ openedtags.top()+">";
        file.push_back(pushing);
       error_line.push(file.size()-1);
        openedtags.pop() ;
        }



return error_line ;


}

