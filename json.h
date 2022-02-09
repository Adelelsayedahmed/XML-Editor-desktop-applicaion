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
void print_node(Node* node_ptr, int& tab, string& json, int repeated);
vector <int> sortchildren(vector<Node*>& children);
vector <int> firstrepeats(vector <int> repeated);
vector <int> isrepeated(vector <int> repeated);
string xml_to_json(xml_tree tree);


#endif
