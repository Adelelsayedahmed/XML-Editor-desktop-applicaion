#include "Readfromfile.h "
vector <string> ReadFromFile(string filepath)
{
    vector <string> filelines;
    string line;
    ifstream myfile;
    myfile.open(filepath);

    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            filelines.push_back(line);
        }
    }
    else {
        cout << "unable to open";
    }

    return filelines;
}
