#ifndef READFROMFILE_H
#define READFROMFILE_H
#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

string vectortostring(vector<string>v);
void FileWithoutComments(vector <string>& file_lines_without_comments, vector <string>file_lines);

#endif