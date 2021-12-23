#ifndef PRETTIFY_H
#define PRETTIFY_H
#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void pretty(vector<string>& file_lines);
void XML_pretify(vector<string> XML_Prettified, vector<int>& lines_indent);
void indent(vector<string>& XML_Prettified, vector <int> lines_indent);

#endif