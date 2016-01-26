#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <climits>


using namespace std;

class utility{

public:
	void readTopolgy(const char*,vector<vector<int> >&);
	void readTopologyFormat1(const char*,vector<vector<int> >&);
	void scanTopologyFormat1(const char*,vector<vector<int> >&,bool);
};

