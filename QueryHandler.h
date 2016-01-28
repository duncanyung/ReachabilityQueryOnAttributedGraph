
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

#include "query.h"

using namespace std;

class QueryHandler{

	public:
		bool CReachabilityQuery(vector<vector<pair<int,int> > >&,vector<unsigned long long>&,vector<unsigned long long>&,query&,const char*);
		bool DFS_C(int,vector<vector<pair<int,int> > >&,vector<unsigned long long>&,vector<unsigned long long>&,query&,queue<pair<int,int> >&,
			vector<bool>&,unordered_map<unsigned long long,bool>&,unordered_map<unsigned long long,bool>&,const char*,const char* );
		bool CheckConstraint(int,vector<unsigned long long>&,vector<vector<int> > &,unordered_map<unsigned long long,bool>&,const char*);
		void IOAttr(int,const char*,vector<int>&);
		bool CheckAttr(vector<int>&,vector<vector<int> >&);
};


