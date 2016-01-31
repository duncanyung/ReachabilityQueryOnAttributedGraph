
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
#include <unistd.h>

#include "query.h"

using namespace std;

class QueryHandler{

	public:
		bool SimpleBFS(query&,vector<vector<pair<int,int> > >&);
		bool DFS(int,vector<vector<pair<int,int> > >&,query&,vector<bool>&);
		pair<bool,int> CReachabilityQuery(vector<vector<pair<int,int> > >&,vector<unsigned long long>&,vector<unsigned long long>&,query&,const char*,int,int,bool,bool);
		bool BFS_C(int,vector<vector<pair<int,int> > >&,vector<unsigned long long>&,vector<unsigned long long>&,query&,queue<pair<int,int> >&,
					vector<bool>&,unordered_map<unsigned long long,bool>&,unordered_map<unsigned long long,bool>&,const char*,const char*,
					ifstream&,ifstream&,int,int,bool,bool);
		bool DFS_C(int,vector<vector<pair<int,int> > >&,vector<unsigned long long>&,vector<unsigned long long>&,query&,queue<pair<int,int> >&,
					vector<bool>&,unordered_map<unsigned long long,bool>&,unordered_map<unsigned long long,bool>&,const char*,const char*,
					/*ifstream&,ifstream&,*/int,int,bool);
		bool CheckConstraint(int,vector<unsigned long long>&,vector<vector<int> > &,unordered_map<unsigned long long,bool>&,const char*,ifstream&,int,bool);
		void split(const string&,char,vector<int>&,bool);
		void IOAttr(int,const char*,vector<int>&,ifstream&,int);
		bool CheckAttr(vector<int>&,vector<vector<int> >&);
};


