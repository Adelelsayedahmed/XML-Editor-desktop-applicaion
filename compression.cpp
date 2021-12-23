#include "compression.h"

string xmltostring(string filepath)
{
	fstream f(filepath, fstream::in);
	string s;
	getline(f, s, '\0');
	f.close();
	return s;
}
vector<int> compress(string filepath)
{
	string input = xmltostring(filepath);
	vector <int> outputcode;
	unordered_map<string, int > table;
	//all ascii values
	for (int i = 0; i < 255; i++)
	{
		string c = "";
		c += char(i);
		table[c] = i;
	}
	string next = "";
	string current = "";
	current += input[0];
	int code = 256;
	for (int i = 0; i < input.length(); i++)
	{
		if (i != input.length() - 1)
		{
			next += input[i + 1];
		}
		if (table.find(current + next) != table.end())
		{
			current += next;

		}
		else
		{
			outputcode.push_back(table[current]);
			table[current + next] = code;
			code++;
			current = next;
		}
		next = "";
	}
	outputcode.push_back(table[current]);
	return outputcode;
}
void savingcompressfile(string input, vector <int> outputcode)
{
	ofstream ff(input, ios::binary | ios::out);
	ff.open("xmlcompressed.txt");
	for (unsigned int i = 0; i < outputcode.size(); i++)
	{
		int j = outputcode[i];
		ff.write((char*)&j, sizeof(int));
	}
	ff.close();
}

string decompress(vector<int> codes)
{
	unordered_map<int, string> table;
	for (int i = 0; i <= 255; i++) {
		std::string c = "";
		c += char(i);
		table[i] = c;
	}
	string output = "";
	int old = codes[0], x;
	string s = table[old];
	string ss = "";
	ss += s[0];
	output += s;
	int count = 256;
	for (int i = 0; i < codes.size() - 1; i++)
	{
		x = codes[i + 1];
		if (table.find(x) == table.end()) {
			s = table[old];
			s += ss;
		}
		else {
			s = table[x];
		}
		output += s;
		ss = "";
		ss += s[0];
		table[count] = table[old] + ss;
		count++;
		old = x;
	}
	return output;

}
