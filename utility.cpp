#include "utility.h"


/*void utility::readSynopsis(const char* synopsisFileName,vector<double>& synopsis){
	FILE* syFile = fopen(synopsisFileName,"r");



	fclose(syFile);
}*/

void utility::readVertexToSuperNodeMapping(const char* superNodeMappingFileName,vector<int>& S){
	FILE* inFile = fopen(superNodeMappingFileName,"r");

	int id,SN;
	while(fscanf(inFile,"%d\t%d\n",&id,&SN)!=EOF){
		S.push_back(SN);
	}

	fclose(inFile);
}

int utility::countIntDigit(int x){
	int length = 1;
	while ( x /= 10 )
	   length++;

	return length;
}

int utility::readTopology(const char* fileName,vector<vector<pair<int,int> > >& topology){
	printf("Read Topology\n");

	int numEdge = 0;

	string sFileName(fileName);
	if(sFileName.find("soc-pokec-relationships")!=string::npos)
		numEdge = readTopologyFormat1(fileName,topology,soc_pokec_vertex_size);
	if(sFileName.find("graph_dblp")!=string::npos)
		numEdge = readTopologyFormat1(fileName,topology,dblp_vertex_size);
	if(sFileName.find("roadNet-PA")!=string::npos)
		numEdge = readTopologyFormat1(fileName,topology,PA_road_network);

	return numEdge;
}

int utility::scanTopologyFormat1(const char* fileName,vector<vector<pair<int,int> > >& topology){
	string line;
	char split_char='\t';
	int maxID=0;
	int minID=INT_MAX;
	int lineCount=0,edgeIDCount=1;

	unordered_map<pair<int,int>,int,pairHash> edgeMap;

//	printf("before open stream\n");
	ifstream inFile(fileName);
//	printf("after open stream\n");
	while(getline(inFile,line)){
		istringstream s(line);
		vector<int> tokens;
		for(string each; getline(s,each,split_char); ){
			tokens.push_back(stoi(each));
			maxID=max(stoi(each),maxID);
			minID=min(stoi(each),minID);
		}
		lineCount++;
		if(lineCount%100000==0)
			printf("Reading line %d\n",lineCount);

		int eID = 0;

		pair<int,int> p = make_pair(min(tokens[0],tokens[1]),max(tokens[0],tokens[1]));
		unordered_map<pair<int,int>,int,pairHash>::const_iterator got = edgeMap.find(p);

		if(got==edgeMap.end()){
			edgeMap.insert(make_pair(p,edgeIDCount));
			eID = edgeIDCount;
			edgeIDCount++;
		}else{
			eID = got->second;
		}

		topology[tokens[0]].push_back(pair<int,int>(tokens[1],eID));
	}
	inFile.close();

	printf("min Vertex ID=%d max Vertex ID=%d lineCount=%d EdgeCount=%d\n",minID,maxID,lineCount,edgeIDCount);

	return edgeIDCount;
}

int  utility::readTopologyFormat1(const char* fileName,vector<vector<pair<int,int> > >& topology,int numVertex){

//	scanTopologyFormat1(fileName,topology,true); //collect info only
	vector<pair<int,int> > adj;
	topology.assign(numVertex,adj);
	return scanTopologyFormat1(fileName,topology); //put tings into topology

}

void utility::readAttrHash(const char* attrFolderName,vector<unsigned long long>& hashValues,bool isEdge){
	char fileName[200];
	if(isEdge==true)
		sprintf(fileName,"%s/EdgeAttrHash.txt",attrFolderName);
	else
		sprintf(fileName,"%s/VertexAttrHash.txt",attrFolderName);

	FILE* inFile = fopen(fileName,"r");

	int id = 0;
	unsigned long long hashValue = 0;
	int count = 0;
	while(fscanf(inFile,"%d %lld\n",&id,&hashValue)!=EOF){
		hashValues.push_back(hashValue);

		if(count%10000 == 0 && isEdge == true)
			printf("Reading Edge Hash Value %d\n",count);
		else if(count%10000 == 0 && isEdge == false)
			printf("Reading Vertex Hash Value %d\n",count);

		count++;
	}

	fclose(inFile);
}


