#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <climits>
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <unordered_map>
#include <string.h>

#include "QueryHandler.h"


class QueryGenerator{


	public:
		int getAttributeInfo(char*,vector<int>&);
		void generateQuery(vector<query>&,int,const char*,vector<vector<pair<int,int> > >&);
};