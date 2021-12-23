#ifndef TREE_H
#define TREE_H
#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
using namespace std;


struct Node
{
	string data, att, tag_name;
	vector<Node*>children;
	Node* Parent;


	//Public Constructor
	Node(string Name, string attr, string Data = "")
	{
		Parent = NULL;
		data = Data;
		att = attr;
		tag_name = Name;
		children = {};

	}
};

class xml_tree
{
	Node* root;
public:
	xml_tree();
	Node* add_node(string name, string at);
	void add_data(Node* n, string text);
	void add_child(Node* parent, Node* child);
	bool have_children(Node* n);
	Node* get_root();
	void add_root(Node* r);
	vector<Node*> get_children(Node* n);
	string get_attributes(Node* n);
	string get_data(Node* n);
	string get_tag(Node* n);

};

void xml_tree_implemetation(vector<string> file_lines, vector<Node*>& nodes, xml_tree& tree, stack<int>& tags);
void sort_children(vector<Node*>& children);

#endif