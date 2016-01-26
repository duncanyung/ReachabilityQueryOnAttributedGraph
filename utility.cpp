#include "utility.h"



void utility::readTopolgy(const char* fileName,vector<vector<int> >& topology){
	printf("Read Topology\n");
	string sFileName(fileName);
	if(sFileName.find("soc-pokec-relationships")!=string::npos)
		readTopologyFormat1(fileName,topology);
}

void utility::scanTopologyFormat1(const char* fileName,vector<vector<int> >& topology,bool collectInfo){
	string line;
	char split_char=' ';
	int maxID=0;
	int minID=INT_MAX;
	int lineCount=0,edgeCount=0;

	ifstream inFile(fileName);
	while(getline(inFile,line)){
		istringstream s(line);
		vector<int> tokens;
		for(string each; getline(s,each,split_char); ){
			tokens.push_back(stoi(each));
			maxID=max(stoi(each),maxID);
			minID=min(stoi(each),minID);

			edgeCount++;
		}
		lineCount++;
		if(lineCount%100000==0)
			printf("Reading line %d\n",lineCount);

		if(collectInfo==false){
			topology[tokens[0]].push_back(tokens[1]);
		}
	}
	inFile.close();

	printf("min Vertex ID=%d max Vertex ID=%d lineCount=%d EdgeCount=%d\n",minID,maxID,lineCount,edgeCount);

	if(collectInfo==true){
		vector<int> adj;
		topology.assign(maxID,adj);
	}
}

void utility::readTopologyFormat1(const char* fileName,vector<vector<int> >& topology){

	scanTopologyFormat1(fileName,topology,true); //collect info only
	scanTopologyFormat1(fileName,topology,false); //put tings into topology

}




