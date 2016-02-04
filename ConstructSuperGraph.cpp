#include "ConstructSuperGraph.h"
#include "utility.h"



void ConstructSuperGraph::construct(int numSuperNode,int numVertex,int numVAttr,int numEAttr,const char* attrFolderName,const char* sFileName,
									const char* vSynopsisFileName,const char*  eSynopsisFileName,const char* vToSNMapFileName,
									vector<vector<pair<int,int> > >& topology,int synopsisSize){


	vector<int> S;//to store vertex to super node mapping
	S.assign(numVertex,-1);

	//1. GraphClustering
		//partition vertices into k clusters based on vertex and edge attribute similarity
	clustering(attrFolderName,S,topology,numSuperNode);//has to be O(n+m) or O((n+m)log(n+m)) I/O

	FILE* outFile = fopen(vToSNMapFileName,"w");

	for(int i=0; i<S.size(); i++)
		fprintf(outFile,"%d\t%d\n",i,S[i]);

	fclose(outFile);


	//2. build and save super graph
		//assign edge into super Edge
	buildSuperGraph(sFileName,S,topology,numSuperNode);

	//3. build synopsis for super node
		//draw sample and compute stat (a tree? do linear scan to compute stat first) from sample
	bool isEdge = false;
	buildSynopsis(vSynopsisFileName,S,isEdge,numSuperNode,synopsisSize);

	//4. build synopsis for super edge
		//draw sample and compute stat (a tree? do linear scan to compute stat first) from sample
	isEdge = true;
//	buildSynopsis(eSynopsisFileName,S,isEdge,numSuperNode,synopsisSize);

}

void ConstructSuperGraph::buildSynopsis(const char* synopsisFileName,vector<int>& S,bool isEdge,int numSuperNode,int synopsisSize){
	srand(time(NULL));

	vector<vector<int> > superNodes;
	vector<int> superNode;
	superNodes.assign(numSuperNode,superNode);

	for(int i=0; i<S.size(); i++)
		superNodes[S[i]].push_back(i);

	FILE* outFile = fopen(synopsisFileName,"w");

	for(int i=0; i<numSuperNode; i++){
		string row="";
		int numDigit = 0;
		numDigit = numDigit + utility::countIntDigit(i+1);

//		fprintf(outFile,"%d,",i+1);
		row.append(to_string(i+1));
		row.append(",");
		for(int j=0; j<synopsisSize; j++){
			int s = rand()%superNodes[i].size();
			numDigit = numDigit + utility::countIntDigit(s);
// 			fprintf(outFile,"%d,",superNodes[i][s]);
			row.append(to_string(superNodes[i][s]));
			row.append(",");
		}
		row.append(",");
		int extraSpace = synopsisSize*(10+1+1)+1 - numDigit;//assume maximum 10 digits per sample id
		for(int j=0; j<extraSpace; j++)
			row.append(" ");
		row.append("\n");

		fprintf(outFile,"%s\n",row.c_str());
	}

	fclose(outFile);
}

void ConstructSuperGraph::buildSuperGraph(const char* sFileName,vector<int>& S,vector<vector<pair<int,int> > >& topology,int numSuperNode){

	vector<unordered_set<int> > stopology;
	unordered_set<int> adjList;
	stopology.assign(numSuperNode,adjList);

	for(int i=0; i<topology.size(); i++){
		for(int j=0; j<topology[i].size(); j++){
			int adjVertex = topology[i][j].first;

			if(stopology[S[i]].find(S[adjVertex]) == stopology[S[i]].end()){
				//insert
				stopology[S[i]].insert(S[adjVertex]);
			}
		}
	}

	FILE* outFile = fopen(sFileName,"w");

	for(int i=0; i<stopology.size(); i++){
		for(unordered_set<int>::iterator itr = stopology[i].begin(); itr != stopology[i].end(); itr++){
			fprintf(outFile,"%d\t%d\n",i,(*itr));
		}
	}

	fclose(outFile);
}

void ConstructSuperGraph::clustering(const char* attrFolderName,vector<int>& S,vector<vector<pair<int,int> > >& topology,int numSuperNode){

	//just try a simple version of clustering //make another one later
	int partitionSize = S.size()/(numSuperNode-1);

	int count = 0, p = 0;
	for(int i=0; i<S.size(); i++){
		S[i] = p;
		count++;

		if(count == partitionSize){
			p++;
			count = 0;
		}
	}
}






