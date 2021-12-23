
#include "consistance.h"
bool check_consistency(vector <string>file)
{
stack<int> consistance ;
consistance = edit(file);
return consistance.empty();
}
