#ifndef _SOCIALGRAPH_
#define _SOCIALGRAPH_

#include "XMLTree.h"
#include <vector>
#include <string>



class SocialNode {
public:
    std::string name;
    std::vector<int> followers;
    int id;
    vector<vector<std::string>> posts;
};

class SocialGraph
{
public:
    std::vector<SocialNode* > usersSocialNodes;
    SocialGraph(XMLTree& tree);
    ~SocialGraph();
};

#endif
