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
			const char* sFileName = argv[8];
			const char* vSynopsisFileName = argv[9];
			const char* eSynopsisFileName = argv[10];
			const char* vToSNMapFileName = argv[11];

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
							vToSNMapFileName,topology,synopsisSize);

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
	int hashOpt = atoi(argv[11]);
	int sySize = atoi(argv[12]);
	int syRowSize = sySize*
	const char* sFileName = argv[13];
	const char* vSynopsisFileName = argv[14];
	const char* eSynopsisFileName = argv[15];

	//read graph topology into memory
	utility ut;
	vector<vector<pair<int,int> > > topology,stopology;
	int numEdge = ut.readTopology(fileName,topology);
//	int numEdge = ut.readSuperGraphTopoloy(sFileName,stopology);

	vector<double> vSynopsis,eSynopsis;
//	ut.readSynopsis(vSynopsisFileName,vSynopsis);
//	ut.readSynopsis(eSynopsisFileName,eSynopsis);

	vector<int> S;
//	ut.readVertexToSuperNodeMapping(superNodeMappingFileName,S);

	//read hash values into memory
	vector<unsigned long long> vertexHashValues,edgeHashValues;
	ut.readAttrHash(hashFolderName,vertexHashValues,false);
	ut.readAttrHash(hashFolderName,edgeHashValues,true);

	//query generator
	vector<query> queries;
	QueryGenerator qg;
	qg.generateQuery(queries,numQuery,attrFolderName,topology);

	//Start Timer HERE!
	//query algorithm
	printf("topology size=%ld  vertexHashValues size=%ld edgeHashValue size=%ld\n",topology.size(),vertexHashValues.size(),edgeHashValues.size());
	QueryHandler qh;
	
	int notReachableCount = 0;

	clock_t start = clock();
	double duration;
	pair<bool,int> ans;

	for(int i=0; i<queries.size(); i++){
		ans = qh.CReachabilityQuery(topology,vertexHashValues,edgeHashValues,queries[i],attrFolderName,vRowSize,eRowSize,useConstraint,hashOpt,
									stopology,vSynopsis,eSynopsis,S,vSynopsisFileName,eSynopsisFileName,syRowSize);//S is the vertex to supernode mapping vector
		if(ans.first==false)
			notReachableCount++;
		printf("Query %d Reachable = %d\n",i,ans.first);
		printf("src %d dest %d topology.size()=%ld\n",queries[i].src,queries[i].dest,topology.size());
	}
	duration = (clock() - start) / (double) CLOCKS_PER_SEC;

	printf("Execution Time per query=%f ,IOCount=%d\n",duration/(double)queries.size(),ans.second);
	printf("Num of Not Reachable=%d\n",notReachableCount);
	//End Timer HERE!

	notReachableCount = 0;

	start= clock();

	for(int i=0; i<queries.size(); i++){
//		ans = qh.CReachabilityQuery(topology,vertexHashValues,edgeHashValues,queries[i],attrFolderName,vRowSize,eRowSize,useConstraint,0,
//									stopology,vSynopsis,eSynopsis);
		if(ans.first==false)
			notReachableCount++;
		printf("Query %d Reachable = %d\n",i,ans.first);
		printf("src %d dest %d topology.size()=%ld\n",queries[i].src,queries[i].dest,topology.size());
	}
	duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	
	printf("Execution Time per query=%f ,IOCount=%d\n",duration/(double)queries.size(),ans.second);
	printf("Num of Not Reachable=%d\n",notReachableCount);
}

int main(int argc, char const *argv[]){
	
	printf("***Reachability Query on Attributed Graph***\n");
	const int function = atoi(argv[1]);

	if(function<5)
		Preprocessing(argv);
	else
		Query(argv);


	return 0;
}



