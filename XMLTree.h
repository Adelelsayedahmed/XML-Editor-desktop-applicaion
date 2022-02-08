#ifndef _XMLTree_
#define _XMLTree_

#include<vector>
#include<string>
#include<stack>
#include<sstream>
using namespace std;


// Node for XML tag containing a vector its children nodes
// Children represents the inner tags encapsulated by tag that the node represents
// Name is the tag name and if the node doesn't have children then represents the text data of the tag
class node
{
private:

    vector<node* > children;
    string name;

public:
    node(string tagName = "") {
        name = tagName;
    }

    bool hasChildren() {
        return numberOfChilds() != 0;
    }

    int numberOfChilds() {
        return children.size();
    }

    node* getChild(int child) {
        return children[child];
    }
    void addChild(node* newChild) {
        children.push_back(newChild);
    }

    string getName() {
        return name;
    }

};

// Constructing a tree from XML
class XMLTree
{

private:
    node* root;
    string body;
    int currentOpeningTag = -1;
    int currentClosingTag;

public:
    XMLTree(const string& xmlContent);

    // Returns string with XML inorder
    string inorderXML();


    node* getRoot() {
        return root;
    }

    ~XMLTree();

private:
    int getNextOpening() {
        currentOpeningTag++;
        return currentOpeningTag = body.find_first_of("<", currentOpeningTag);
    }
    int getClosing() {
        return currentClosingTag = body.find_first_of(">", currentOpeningTag);
    }
    bool isClosingTag() {
        return body[currentOpeningTag + 1] == '/';
    }

    void inorderXML(node* tag, stringstream& str);

    void deleteTree(node* node);
};




#endif
