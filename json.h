#ifndef JSON_H
#define JSON_H
#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>

#include <vector>
#include <string>
#include <stack>
#include "tree.h"
using namespace std;


bool is_digits(const std::string& str);
vector <string> split(string s, string delimiter);
string tab(int n);
void XML_json(string &json, xml_tree tree, Node* temp_ptr, int& x, bool firstrepeated, bool inbetweenrepeated, bool lastrepeated);


#endif
