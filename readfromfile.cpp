#include "readfromfile.h"



string vectortostring(vector<string>v)
{
	string s = "";
	for (int i = 0; i < v.size(); i++)
	{
		s = s + v[i] + "\n";
	}
	return s;
}

void FileWithoutComments(vector <string>& file_lines_without_comments, vector <string>file_lines) {
	for (int i = 0; i < file_lines.size(); i++)
	{
		if (file_lines[i][0] == '<' && file_lines[i][1] == '?')
		{
			continue;
		}
		if (file_lines[i][0] == '<' && file_lines[i][1] == '!')
		{
			continue;
		}
		else
		{
			file_lines_without_comments.push_back(file_lines[i]);
		}
	}
}