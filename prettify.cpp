#include "prettify.h"
//make one opening  and one closing tag per line  atmost
void pretty(vector<string>& file_lines)
{
	for (int i = 1; i < file_lines.size(); i++)
	{
		if (file_lines[i][0] == '<' && file_lines[i][1] == '/' && file_lines[i - 1][0] != '<')
		{
			file_lines[i - 1].append(file_lines[i]);
			file_lines.erase(file_lines.begin() + i, file_lines.begin() + i + 1);
		}

	}
	for (int i = 1; i < file_lines.size(); i++)
	{
		if (file_lines[i][0] != '<')
		{
			file_lines[i - 1].append(file_lines[i]);
			file_lines.erase(file_lines.begin() + i, file_lines.begin() + i + 1);
		}
	}

}
// XML formatting
void XML_pretify(vector<string> XML_Prettified, vector<int>& lines_indent)
{
	lines_indent[0] = 0;
	for (int i = 1; i < XML_Prettified.size(); i++)
	{
		if (XML_Prettified[i].find('<') != -1 && XML_Prettified[i - 1].find('<') != -1)
		{
			if (XML_Prettified[i - 1][XML_Prettified[i - 1].find_last_of('<') + 1] != '/' && XML_Prettified[i - 1][XML_Prettified[i - 1].find_last_of('>') - 1] != '/' && XML_Prettified[i][XML_Prettified[i].find('<') + 1] != '/' && XML_Prettified[i][XML_Prettified[i].find('>') - 1] != '/') {
				lines_indent[i] = lines_indent[i - 1] + 1;
			}
			else if (XML_Prettified[i - 1][XML_Prettified[i - 1].find_last_of('<') + 1] == '/' && XML_Prettified[i][XML_Prettified[i].find('<') + 1] == '/') {
				lines_indent[i] = lines_indent[i - 1] - 1;
			}
			else if (XML_Prettified[i - 1][XML_Prettified[i - 1].find_last_of('<') + 1] == '/' && XML_Prettified[i][XML_Prettified[i].find('<') + 1] != '/') {
				lines_indent[i] = lines_indent[i - 1];
			}

			//self closing tag
			else if (XML_Prettified[i - 1][XML_Prettified[i - 1].find_last_of('>') - 1] == '/' && XML_Prettified[i][XML_Prettified[i].find('>') - 1] == '/') {
				lines_indent[i] = lines_indent[i - 1];
			}
			else if (XML_Prettified[i - 1][XML_Prettified[i - 1].find_last_of('>') - 1] == '/' && XML_Prettified[i][XML_Prettified[i].find('<') + 1] != '/') {
				lines_indent[i] = lines_indent[i - 1];
			}
			else if (XML_Prettified[i - 1][XML_Prettified[i - 1].find_last_of('<') + 1] == '/' && XML_Prettified[i][XML_Prettified[i].find('>') - 1] == '/') {
				lines_indent[i] = lines_indent[i - 1];
			}
			else if (XML_Prettified[i - 1][XML_Prettified[i - 1].find_last_of('>') - 1] == '/' && XML_Prettified[i][XML_Prettified[i].find('<') + 1] == '/') {
				lines_indent[i] = lines_indent[i - 1] - 1;
			}
			else
			{
				lines_indent[i] = lines_indent[i - 1];
			}
		}
	}
}

void indent(vector<string>& XML_Prettified, vector <int> lines_indent)
{
	for (int i = 0; i < XML_Prettified.size(); i++)
	{
		for (int j = 0; j < lines_indent[i]; j++)
		{
			XML_Prettified[i] = "\t" + XML_Prettified[i];
		}
	}
}