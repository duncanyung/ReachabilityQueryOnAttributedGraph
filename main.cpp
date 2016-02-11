#include "AttrGenerator.h"
#include "ComputeHashValue.h"
#include "utility.h"
//#include "query.h"
//#include "QueryHandler.h"
#include "QueryGenerator.h"
#include "ConstructSuperGraph.h"

#include <ctime>

void Preprocessing(char const *argv[]){
	printf("Do Preprocessing\n");
	/*Pre-processing Functions*/
	int function = atoi(argv[1]);
	switch(function +'0'){
		case '1':{//attribute generator
			printf("Attribute Generator\n");

			//prase parameters
			const char* fileName = argv[2];
			const char* attrFolderName = argv[3];
			int numVAttr = atoi(argv[4]);
			int numEAttr = atoi(argv[5]);
			int maxDomainSize = atoi(argv[6]);
			printf("%s %s %d %d %d\n",fileName,attrFolderName,numVAttr,numEAttr,maxDomainSize);
			
			
			//read topology
			utility ut;
			vector<vector<pair<int,int> > > topology;
			int numEdge = ut.readTopology(fileName,topology);

			//generate attribute on the topology
			AttrGenerator genAttr;
			genAttr.generateAttribute(attrFolderName,topology,numVAttr,numEAttr,maxDomainSize,numEdge);

			break;
		}case '2':{//pre-processing real data attributes
			printf("pre-processing real data attributes\n");
			
			//One vertex/edge attribute 1 file. Is that correct?
				//read attribute and put them into individual files
				//different data have different format

			break;
		}case '3':{//hash scheme index construction
			printf("hash scheme index construction\n");

			//prase parameters
			const char* attrFolderName = argv[3];
			const char* hashFolderName = argv[4];

			//Compute and store Hash Value to File
			ComputeHashValue ch;
			ch.computeHashValue(hashFolderName,attrFolderName);

			break;
		}case '4':{//super-graph construction [not to use super graph first]
			printf("super-graph construction\n");

			const char* fileName = argv[2];
			const char* attrFolderName = argv[3];
			int numVAttr = atoi(argv[4]);
			int numEAttr = atoi(argv[5]);
			int numSuperNode = atoi(argv[6]);
			int synopsisSize = atoi(argv[7]);
			int vRowSize = atoi(argv[8]);
			const char* sFileName = argv[9];
			const char* vSynopsisFileName = argv[10];
			const char* eSynopsisFileName = argv[11];
			const char* vToSNMapFileName = argv[12];

			printf("fileName=%s\n",fileName);
			printf("attrFolderName=%s\n",attrFolderName);
			printf("%d,%d,%d,%d\n",numVAttr,numEAttr,numSuperNode,synopsisSize);
			printf("sFileName=%s\n",sFileName);
			printf("vSynopsisFileName=%s\n",vSynopsisFileName);


			//read topology
			utility ut;
			vector<vector<pair<int,int> > > topology;
			int numEdge = ut.readTopology(fileName,topology);
			int numVertex = topology.size();

			ConstructSuperGraph csg;
			csg.construct(numSuperNode,numVertex,numVAttr,numEAttr,attrFolderName,sFileName,vSynopsisFileName,eSynopsisFileName,
							vToSNMapFileName,topology,synopsisSize,vRowSize);

			break;
		}case '5':{
			printf("Generate Query\n");
			const char* fileName = argv[2];
			int numQuery = atoi(argv[3]);
			const char* attrFolderName = argv[4];
			const char* queryFileName = argv[5];

			utility ut;
			vector<vector<pair<int,int> > > topology;
			int numEdge = ut.readTopology(fileName,topology);

			vector<query> queries;
			QueryGenerator qg;
			qg.generateQuery(queries,numQuery,attrFolderName,topology);
			qg.writeQueries(queries,queryFileName);
			break;
		}default:{
			printf("No Such Function....\n");
		}
	}
}

void Query(char const *argv[]){
	printf("Do Query\n");
	/*Query Time Functions*/
	const char* fileName = argv[2];
	const char* attrFolderName = argv[3];
	const char* hashFolderName = argv[4];
	int numEAttr = atoi(argv[5]);
	int numVAttr = atoi(argv[6]);
	int vRowSize = atoi(argv[7]);
	int eRowSize = atoi(argv[8]);
	int numQuery = atoi(argv[9]);
	int useConstraint = atoi(argv[10]);
	int numSuperNode = atoi(argv[11]);
	int vSySize = atoi(argv[12]);
//	int vSyRowSize = (vSySize+1)*10 + vSySize + 1 + 1 + 1;//sySize*(10+1+1)+1;
	int vSyRowSize = vRowSize*vSySize + vSySize;//sySize*(10+1+1)+1;
	const char* sFileName = argv[13];
	const char* vSynopsisFileName = argv[14];
	const char* eSynopsisFileName = argv[15];
	const char* superNodeMappingFileName = argv[16];
	const char* queriesFileName = argv[17];

	//read graph topology into memory
	utility ut;
	vector<vector<pair<int,int> > > topology,stopology;
	int numEdge = ut.readTopology(fileName,topology);
	int numSEdge = ut.readTopology(sFileName,stopology,numSuperNode+1);

	vector<double> vSynopsis,eSynopsis;

	vector<int> S;
	vector<int> partitionSize;
	partitionSize.assign(stopology.size(),0);
	ut.readVertexToSuperNodeMapping(superNodeMappingFileName,S,partitionSize);

	//read hash values into memory
	vector<unsigned long long> vertexHashValues,edgeHashValues;
	ut.readAttrHash(hashFolderName,vertexHashValues,false);
	ut.readAttrHash(hashFolderName,edgeHashValues,true);

	//query generator
	vector<query> queries;
	QueryGenerator qg;
//	qg.generateQuery(queries,numQuery,attrFolderName,topology);
	qg.readQueries(queriesFileName,queries,numQuery,numVAttr,numEAttr);

	//query algorithm
	printf("topology size=%ld  vertexHashValues size=%ld edgeHashValue size=%ld\n\n",topology.size(),vertexHashValues.size(),edgeHashValues.size());
	QueryHandler qh;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	int hashOptList[3] =   {1,1,0};
	int heuristicList[3] = {1,0,0};
	for(int i=0; i<1; i++){//CAUTION: set 1 HERE!!!!!!
		int hashOpt = hashOptList[i];
		int heuristic = heuristicList[i];
		int notReachableCount = 0;
		int totalIO = 0, totalNodeVisited = 0;
		double maxTime = 0; 
		int maxIOCount = 0, maxNodeVisisted = 0;
		double totalDuration = 0, duration;
		pair<bool,pair<int,int> > ans;


//		if(heuristic == 1){
//			char attrFileName[200];
//			sprintf(attrFileName,"%s/VertexAttr.txt",attrFolderName);
//			qh.computeAllSynopsis(queries[i],vSynopsis,vSynopsisFileName,vSyRowSize,attrFileName,vRowSize,queries[i].vertexAttrCon);
//		}

		for(int i=0; i<queries.size(); i++){
			vSynopsis.assign(stopology.size(),-1);//reset synopsis
			eSynopsis.assign(numSEdge,-1);
			
			printf("Query %d src=%d dest=%d\n",i+1,queries[i].src,queries[i].dest);

			//Start Timer HERE!
			clock_t start = clock();
			ans = qh.CReachabilityQuery(topology,vertexHashValues,edgeHashValues,queries[i],attrFolderName,vRowSize,eRowSize,useConstraint,hashOpt,
										stopology,vSynopsis,eSynopsis,S,vSynopsisFileName,eSynopsisFileName,vSyRowSize,heuristic,partitionSize);//S is the vertex to supernode mapping vector
			//End Timer HERE!
			duration = (clock() - start) / (double) CLOCKS_PER_SEC;
			totalIO = totalIO + ans.second.first;
			totalNodeVisited = totalNodeVisited + ans.second.second;

			totalDuration = totalDuration + duration;
			if(ans.first==false)
				notReachableCount++;
			if(maxTime < duration)
				maxTime = duration;
			if(maxIOCount < ans.second.first)
				maxIOCount = ans.second.first;
			if(maxNodeVisisted < ans.second.second)
				maxNodeVisisted = ans.second.second;

			printf("Reachable=%d Time=%f IOCount=%d NodeVisisted=%d\n",ans.first,duration,ans.second.first,ans.second.second);
		}

		printf("\navg.query time=%fsec avg.IOCount=%f avg.NodeVisisted=%f\n",totalDuration/(double)queries.size(),(double)totalIO/(double)queries.size(),(double)totalNodeVisited/(double)queries.size());
		printf("maxTime=%f maxIOCount=%d maxNodeVisisted=%d\n",maxTime,maxIOCount,maxNodeVisisted);
		printf("Num of Not Reachable=%d\n\n\n",notReachableCount);
	}
}

int main(int argc, char const *argv[]){
	
	printf("***Reachability Query on Attributed Graph***\n");
	const int function = atoi(argv[1]);

	if(function<6)
		Preprocessing(argv);
	else
		Query(argv);


	return 0;
}



