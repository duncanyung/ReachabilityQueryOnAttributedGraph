#include "QueryGenerator.h"


int QueryGenerator::getAttributeInfo(char* attrInfoFileName, vector<int>& attrDomain){
	int numAttr = 0, temp = 0;
	char s[10];

	FILE* attrInfoFile = fopen(attrInfoFileName,"r");
	fscanf(attrInfoFile,"%s %d\n",s,&numAttr);

	for(int i=0; i<numAttr; i++){
		fscanf(attrInfoFile,"%d ",&temp);
		attrDomain.push_back(temp);
	}
	fclose(attrInfoFile);

	return numAttr;
}

void QueryGenerator::generateQuery(vector<query>& queries,int numQuery,const char* attrFolderName,vector<vector<pair<int,int> > >& topology){

	char vertexAttrFileName[200],edgeAttrFileName[200],vertexAttrInfoFileName[200],edgeAttrInfoFileName[200];
	sprintf(vertexAttrFileName,"%s/VertexAttr.txt",attrFolderName);
	sprintf(edgeAttrFileName,"%s/EdgeAttr.txt",attrFolderName);
	sprintf(vertexAttrInfoFileName,"%s/VertexAttrInfo.txt",attrFolderName);
	sprintf(edgeAttrInfoFileName,"%s/EdgeAttrInfo.txt",attrFolderName);

	vector<int> vertexAttrDomain;	vector<int> edgeAttrDomain;
	int numVAttr = 0,numEAttr = 0;

	numVAttr = getAttributeInfo(vertexAttrInfoFileName,vertexAttrDomain);
	numEAttr = getAttributeInfo(edgeAttrInfoFileName,edgeAttrDomain);

	srand(time(NULL));
	for(int i=0; i<numQuery; i++){
		query q;
//		printf("topology.size() + 1=%d\n",topology.size() + 1);
		q.src = rand()%topology.size() + 1;
		q.dest = rand()%topology.size() + 1;


		for(int j=0; j<numVAttr; j++){
			int numCon = vertexAttrDomain[j];//rand()%vertexAttrDomain[j] + 1;
//			int numCon = rand()%vertexAttrDomain[j] + 1;
			unordered_map<int,bool> existC;
			vector<int> con;
//			printf("DomainSize=%d\n",numCon);
//			printf("Constraint of vertex Attr %d: ",j+1);
			for(int k=0; k<numCon; k++){
				int c = rand()%vertexAttrDomain[j] + 1;
				if(existC.find(c)==existC.end()){
					existC.insert(make_pair(c,true));
					con.push_back(c);
//					printf("%d ",c);
				}else
					k--;
			}
//			printf("\n");
			q.vertexAttrCon.push_back(con);
		}

		for(int j=0; j<numEAttr; j++){
			int numCon = edgeAttrDomain[j];//rand()%edgeAttrDomain[j] + 1;
//			int numCon = rand()%edgeAttrDomain[j] + 1;
			unordered_map<int,bool> existC;
			vector<int> con;
//			printf("DomainSize=%d\n",numCon);
//			printf("Constraint of edge Attr %d: ",j+1);
			for(int k=0; k<numCon; k++){
				int c = rand()%edgeAttrDomain[j] + 1;
				if(existC.find(c)==existC.end()){
					existC.insert(make_pair(c,true));
					con.push_back(c);
//					printf("%d ",c);
				}else
					k--;
			}
//			printf("\n");
			q.edgeAttrCon.push_back(con);
		}

		if(i%1000 == 0)
			printf("Generating Query %d\n",i);

		queries.push_back(q);
	}
}