#include "xmlcutter.h"


//make one tag per line atmost
vector<string> xml_cutter(string filepath)
{
	vector <string> xmlcutted;
	ifstream inputfile;
	int startindex, endindex;
	string input;
	string line;

	inputfile.open(filepath);
	
	while (getline(inputfile, input)) {
		for (int i = 0; i < input.length(); i++) {
			if (input[i] == '<') {
				startindex = i;
				for (i; i < input.length(); i++) {
					if (input[i] == '>') {
						endindex = i;
						break;
					}
					else
					{
						endindex = i;
					}


				}
			}
			else { // Ascii value of horizontal tab = 9
				if (int(input[i]) == 9)
				{
					continue;
				}
				else
				{
					startindex = i;
					for (i; i < input.length(); i++) {
						if (input[i] == '<') {
							endindex = i - 1;
							i--;
							break;
						}
						else
						{
							endindex = i;
						}

					}
				}

			}
			line = input.substr(startindex, (endindex - startindex + 1));
			if (line[0] != '<')
				for (int i = 0; i < line.length(); i++) {
					if (line[i] == '"')
						line.replace(i, 1, " ");
				}
			// to avoid multi lines comments
			if (line[0] != ' ' || line[1] != ' ' || line[2] != ' ')
			{
				if (line.find_first_not_of(' ') != -1)
				{
					if (int(line[line.find_first_not_of(' ')]) != 9)
					{
						xmlcutted.push_back(line);
					}
				}
			}
		}
	}
	inputfile.close();
	return xmlcutted;
}