#include "json.h"

//to determine type of data
bool is_digits(const std::string& str)
{
	return str.find_first_not_of("0123456789.") == std::string::npos;
}

//function used to split attr 
vector <string> split(string s, string delimiter)
{
	vector<string> v;
	int pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {

		token = s.substr(0, pos);
		v.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	v.push_back(s);
	return v;
}

string tab(int n)
{
	string s = "";
	if (n < 0)
		return s;
	for (int i = 0; i < n; i++)
	{
		s += "\t";
	}

	return s;
}

void XML_json(string &json , xml_tree tree, Node* temp_ptr, int& x, bool firstrepeated, bool inbetweenrepeated, bool lastrepeated)
{


	// has attr  and has data
	if (temp_ptr->att != "" && temp_ptr->data != "")
	{
		x++;
		

		json = json + tab(x) + "\"" + tree.get_tag(temp_ptr) + "\": {" + "\n";
		vector <string> attr = split(temp_ptr->att, " ");
		for (auto it = attr.begin(); it != attr.end(); /* NOTHING */)
		{
			if ((*it).find('=') == -1)
				it = attr.erase(it);
			else
				++it;
		}

		x++;

		for (int i = 0; i < attr.size(); i++)
		{
			json = json + tab(x) + "\"@" + split(attr[i], "=")[0] + "\": " + split(attr[i], "=")[1] + "," + "\n";
		}
		json = json + tab(x);
		if (is_digits(temp_ptr->data))
		{
			json = json + temp_ptr->data;
		}
		else
		{
			json = json + "\"" + temp_ptr->data + "\"";
		}
		json = json + "\n";
		x--;
		json = json + tab(x) + "}";
		vector < Node*> v = tree.get_children(temp_ptr->Parent);
		sort_children(v);
		if (temp_ptr == v[v.size() - 1])
		{
			json = json + "\n";
		}
		else
		{
			json = json + "," + "\n";
		}
		vector <Node*>w = tree.get_children(temp_ptr->Parent);
		sort_children(w);
		if (temp_ptr == w[w.size()-1])
		{
			x--;
		}


	}
	//has data only
	else if (temp_ptr->data != "" && temp_ptr->att == "")
	{
		
		if (temp_ptr->Parent->att != "")
		{
			x--;

		}
		x++;
		json = json + tab(x) + "\"" + temp_ptr->tag_name + "\": ";
		if (is_digits(temp_ptr->data))
		{
			json = json + temp_ptr->data;
		}
		else
		{
			json = json + "\"" + temp_ptr->data + "\"";
		}
		vector < Node*> v = tree.get_children(temp_ptr->Parent);
		sort_children(v);
		if (temp_ptr == v[v.size() - 1])
		{
			json = json + "\n";
		}
		else
		{
			json = json + "," + "\n";
		}
	}
	// has attr only and dont have any child or data
	else if (temp_ptr->att != "" && temp_ptr->data == "" && !tree.have_children(temp_ptr))
	{
		x++;
		json = json + tab(x) + "\"" + tree.get_tag(temp_ptr) + "\": {" + "\n";
		vector <string> attr = split(temp_ptr->att, " ");
		x++;

		for (int i = 0; i < attr.size(); i++)
		{
			json = json + tab(x) + "\"@" + split(attr[i], "=")[0] + "\": " + split(attr[i], "=")[1];
			if (i = attr.size() - 1)
			{
				json = json + "\n";
			}
			else
			{
				json = json + ","  + "\n";
			}
		}
		x--;
		json = json + tab(x) + "}";
		vector < Node*> v = tree.get_children(temp_ptr->Parent);
		sort_children(v);
		if (temp_ptr == v[v.size() - 1])
		{
			json = json  + "\n";
		}
		else
		{
			json = json + "," + "\n";
		}
		vector <Node*> w = tree.get_children(temp_ptr->Parent);
		sort_children(w);
		if (temp_ptr == w[w.size() - 1])
		{
			x--;
		}
	}
	// have children 
	else if (tree.have_children(temp_ptr))
	{
		if (temp_ptr != tree.get_root())
		{
			vector < Node*> w = tree.get_children(temp_ptr->Parent);
			sort_children(w);
			if (temp_ptr == w[w.size()-1])
			{
				x--;
			}
		}
		else
		{
			x++;
		}
		x++;
		json = json + tab(x) + "\"" + tree.get_tag(temp_ptr) + "\": {"  + "\n";

		if (temp_ptr->att != "")
		{

			vector <string> attr = split(temp_ptr->att, " ");
			x++;
			for (int i = 0; i < attr.size(); i++)
			{
				json = json + tab(x) + "\"@" + split(attr[i], "=")[0] + "\": " + split(attr[i], "=")[1] + "," +"\n";
			}

		}

		vector < Node*> n = tree.get_children(temp_ptr);
		sort_children(n);
		for (int i = 0; i < n.size(); i++)
		{
			
			if (i > 0 && i != n.size() - 1)
			{
				if (n[i]->tag_name != n[i - 1]->tag_name && n[i]->tag_name != n[i + 1]->tag_name)
				{
					if (n[i]->att != "")
					{
						x--;

					}
					XML_json(json, tree, n[i], x, 0, 0, 0);

				}
				else if (n[i]->tag_name != n[i - 1]->tag_name && n[i]->tag_name == n[i + 1]->tag_name)
				{
					if (n[i]->att != "")
					{
						x--;
					}
					XML_json(json, tree, n[i], x, 1, 0, 0);
				}
				else if (n[i]->tag_name == n[i - 1]->tag_name && n[i]->tag_name != n[i + 1]->tag_name)
				{
					if (n[i]->att != "")
					{
						x--;
					}
					XML_json(json, tree, n[i], x, 0, 0, 1);
				}
				else if (n[i]->tag_name == n[i - 1]->tag_name && n[i]->tag_name == n[i + 1]->tag_name)
				{
					if (n[i]->att != "")
					{
						x--;
					}
					XML_json(json, tree, n[i], x, 0, 1, 0);
				}
			}
			else if (i == n.size() - 1)
			{
				if (n[i]->tag_name == n[i - 1]->tag_name)
				{
					if (n[i]->att != "")
					{
						x--;
					}
					XML_json(json, tree, n[i],x , 0, 0, 1);
					json = json + tab(x--) + "}"  +  "\n";
					x++;
				}
				else
				{
					if (n[i]->att != "")
					{
						x--;
					}
					XML_json(json, tree, n[i], x, 0, 0, 1);
					json = json + tab(x--) + "}" + "\n";
					x++;
				}
			}
			else if (i == 0)
			{
				if (n[i]->tag_name == n[i + 1]->tag_name)
				{
					if (n[i]->att != "")
					{
						x--;
					}
					XML_json(json, tree, n[i], x, 1, 0, 0);
				}
				else if (n[i]->tag_name != n[i + 1]->tag_name)
				{
					if (n[i]->att != "")
					{
						x--;

					}
					XML_json(json, tree, n[i], x, 0, 0, 0);
				}
			}
		}
	}


}
