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

class utility{

public:
	static const unsigned long long prime = 9223372036854775783;
	static const unsigned long long constant = 13;

	unsigned long long hashFunction(vector<int>&);
	void readTopolgy(const char*,vector<vector<int> >&);
	void readTopologyFormat1(const char*,vector<vector<int> >&);
	void scanTopologyFormat1(const char*,vector<vector<int> >&,bool);
};

