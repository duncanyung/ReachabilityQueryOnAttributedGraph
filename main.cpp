#include "AttrGenerator.h"
#include "ComputeHashValue.h"
#include "utility.h"
//#include "query.h"
#include "QueryHandler.h"

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
			//vector<vector<int> > topology2;
			vector<vector<pair<int,int> > > topology;
			
			//read topology
			utility ut;
			int numEdge = ut.readTopolgy(fileName,topology);

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
			const char* attrFolderName = argv[2];
			const char* hashFolderName = argv[3];

			//Compute and store Hash Value to File
			ComputeHashValue ch;
			ch.computeHashValue(hashFolderName,attrFolderName);

			break;
		}case '4':{//super-graph construction [not to use super graph first]
			printf("super-graph construction\n");

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


	//read graph topology into memory
	utility ut;
	vector<vector<pair<int,int> > > topology;
	int numEdge = ut.readTopolgy(fileName,topology);

	//read hash values into memory
	vector<unsigned long long> vertexHashValues,edgeHashValues;
	ut.readAttrHash(hashFolderName,vertexHashValues,false);
	ut.readAttrHash(hashFolderName,edgeHashValues,true);

	//query generator
	vector<query> queries;
//	QueryGenerator qg;
//	gg.generateQuery();

	//Start Timer HERE!
	//query algorithm
	printf("topology size=%ld  vertexHashValues size=%ld edgeHashValue size=%ld\n",topology.size(),vertexHashValues.size(),edgeHashValues.size());
	QueryHandler qh;
	int vRowSize = 7 + 20 + 11 + 1;//[hard code here first]
	int eRowSize = 7 + 20 + 11 + 1;//[hard code here first]
	for(int i=0; i<queries.size(); i++){
		bool ans = qh.CReachabilityQuery(topology,vertexHashValues,edgeHashValues,queries[i],attrFolderName,vRowSize,eRowSize);
		printf("Reachable = %d\n",ans);
	}
	//End Timer HERE!
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



