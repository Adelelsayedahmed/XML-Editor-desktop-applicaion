#ifndef COMPRESSION_H
#define COMPRESSION_H
#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
using namespace std;

string xmltostring(string filepath);
vector<int> compress(string filepath);
void savingcompressfile(string input, vector <int> outputcode);
string decompress(vector<int> codes);


#endif