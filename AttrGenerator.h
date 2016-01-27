
//#include "utility.h"

#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <climits>
#include <time.h>
#include <stdlib.h>

using namespace std;

class AttrGenerator{

public:
	void generateVertexAttr(const char*,vector<vector<int> >&,int,int);
	void generateEdgeAttr(const char*,vector<vector<int> >&,int,int);
	void generateAttribute(const char*,vector<vector<int> >&,int,int,int);

};