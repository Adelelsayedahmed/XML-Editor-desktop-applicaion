#include "tree.h"


xml_tree::xml_tree()
{
	root = NULL;
}


	Node* xml_tree::add_node(string name, string att)
	{
		Node* n;
		n = new Node(name, att);
		return n;
	}
	void xml_tree::add_data(Node* n, string text)
	{
		n->data += text;
	}
	void xml_tree::add_child(Node* parent, Node* child)
	{
		parent->children.push_back(child);
		child->Parent = parent;
	}
	bool xml_tree::have_children(Node* n)
	{
		if (n->children.size() == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	Node* xml_tree::get_root()
	{
		return root;
	}
	void xml_tree::add_root(Node* r)
	{
		root = r;
	}
	vector<Node*> xml_tree::get_children(Node* n)
	{
		return n->children;
	}
	string xml_tree::get_attributes(Node* n)
	{
		return n->att;
	}
	string xml_tree::get_data(Node* n)
	{
		return n->data;
	}
	string xml_tree::get_tag(Node* n)
	{
		return n->tag_name;
	}
	

void xml_tree_implemetation(vector<string> file_lines, vector<Node*>& nodes, xml_tree& tree, stack<int>& tags) 
{


	for (int i = 0; i < file_lines.size(); i++)
	{
		// opening tags
		if (file_lines[i][0] == '<' && file_lines[i][1] != '/')
		{
			int index;

			// get tag and att
			for (int j = 1; j < file_lines[i].length(); j++)
			{
				index = j;
				if (file_lines[i][j] == ' ')
				{
					//First white space in the tag
					break;
				}
			}
			string tag = file_lines[i].substr(1, index - 1);
			string att = file_lines[i].substr(index + 1, (file_lines[i].length() - index - 2));
			nodes.push_back(tree.add_node(tag, att));//decalre a new tag 
			if (tags.size() == 0) {
				tree.add_root(nodes[nodes.size() - 1]);//add thre root to the tree
			}
			else {
				tree.add_child(nodes[tags.top()], nodes[nodes.size() - 1]);//add a child to the last opened tag
			}
			tags.push(nodes.size() - 1);
			//self closing tag 
			if (file_lines[i][file_lines[i].length() - 2] == '/')
				tags.pop();
		}
		//Closing tag
		else if (file_lines[i][0] == '<' && file_lines[i][1] == '/')
		{
			tags.pop();//remove the last opend tag (closed) to deal with the next tag to it 
		}
		//Data
		else
		{
			tree.add_data(nodes[tags.top()], file_lines[i]);//add data to the last opened tag

		}
	}

}

// function to sort children
void sort_children(vector<Node*>& children) {
	Node* temp_ptr;
	for (int i = 0; i < children.size(); i++) {
		for (int j = i + 1; j < children.size(); j++) {
			if ((children[j]->tag_name) < (children[i]->tag_name))
			{
				temp_ptr = children[j];
				children[j] = children[i];
				children[i] = temp_ptr;
			}
		}
	}
}