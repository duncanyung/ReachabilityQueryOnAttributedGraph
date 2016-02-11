#include "QueryGenerator.h"
#include "utility.h"

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

void QueryGenerator::generateQuery(vector<query>& queries,int numQuery,const char* attrFolderName,vector<vector<pair<int,int> > >& topology,int numConstraint,int numVAttr,int numEAttr){

	char vertexAttrFileName[200],edgeAttrFileName[200],vertexAttrInfoFileName[200],edgeAttrInfoFileName[200];
	sprintf(vertexAttrFileName,"%s/%dVertexAttr.txt",attrFolderName,numVAttr);
	sprintf(edgeAttrFileName,"%s/%dEdgeAttr.txt",attrFolderName,numEAttr);
	sprintf(vertexAttrInfoFileName,"%s/%dVertexAttrInfo.txt",attrFolderName,numVAttr);
	sprintf(edgeAttrInfoFileName,"%s/%dEdgeAttrInfo.txt",attrFolderName,numEAttr);

	vector<int> vertexAttrDomain;	vector<int> edgeAttrDomain;
//	int numVAttr = 0,numEAttr = 0;

//	numVAttr = 
	getAttributeInfo(vertexAttrInfoFileName,vertexAttrDomain);
//	numEAttr = 
	getAttributeInfo(edgeAttrInfoFileName,edgeAttrDomain);

	srand(time(NULL));
	for(int i=0; i<numQuery; i++){
		query q;
//		printf("topology.size() + 1=%d\n",topology.size() + 1);
		q.src = rand()%topology.size() + 1;
		q.dest = rand()%topology.size() + 1;


		for(int j=0; j<numVAttr; j++){
			int numCon = vertexAttrDomain[j];//rand()%vertexAttrDomain[j] + 1;
//			int numCon = rand()%vertexAttrDomain[j] + 1;
			unordered_set<int> existC;
			vector<int> con;
//			printf("DomainSize=%d\n",numCon);
//			printf("Constraint of vertex Attr %d: ",j+1);
			for(int k=0; k<numCon; k++){
				int c = rand()%vertexAttrDomain[j] + 1;
				if(existC.find(c)==existC.end()){
					existC.insert(c);
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
			unordered_set<int> existC;
			vector<int> con;
//			printf("DomainSize=%d\n",numCon);
//			printf("Constraint of edge Attr %d: ",j+1);
			for(int k=0; k<numCon; k++){
				int c = rand()%edgeAttrDomain[j] + 1;
				if(existC.find(c)==existC.end()){
					existC.insert(c);
					con.push_back(c);
//					printf("%d ",c);
				}else
					k--;
			}
//			printf("\n");
			q.edgeAttrCon.push_back(con);
		}

		if(i%10 == 0)
			printf("Generating Query %d\n",i);

		queries.push_back(q);
	}
}


void QueryGenerator::writeQueries(vector<query>& queries,const char* queryFileName){
	
	FILE* outFile = fopen(queryFileName,"w");

	for(int i=0; i<queries.size(); i++){
		fprintf(outFile,"%d,%d\n",queries[i].src,queries[i].dest);
		for(int j=0; j<queries[i].vertexAttrCon.size(); j++){
			for(int k=0; k<queries[i].vertexAttrCon[j].size(); k++){
				fprintf(outFile,"%d,",queries[i].vertexAttrCon[j][k]);
			}
			fprintf(outFile,"\n");
		}

		for(int j=0; j<queries[i].edgeAttrCon.size(); j++){
			for(int k=0; k<queries[i].edgeAttrCon[j].size(); k++){
				fprintf(outFile,"%d,",queries[i].edgeAttrCon[j][k]);
			}
			fprintf(outFile,"\n");
		}
	}

	fclose(outFile);
}

void QueryGenerator::readSrcDest(query& q,ifstream& inf){
	//read src and dest
	string strData;
	getline(inf,strData);
	vector<int> elems;
	utility::split(strData,',',elems,false);
	int src,dest;
	q.src = elems[0];
	q.dest = elems[1];
}

void QueryGenerator::readAttrCon(vector<vector<int> >& attrCon,ifstream& inf,int numAttr){

	for(int i=0; i<numAttr; i++){
		string strData;
		getline(inf,strData);
		vector<int> elems;
		utility::split(strData,',',elems,false);
		attrCon.push_back(elems);
	}
}

void QueryGenerator::readQueries(const char* queryFileName,vector<query>& queries,int numQueries,int numVertexAttr,
				int numEdgeAttr){
	ifstream inf(queryFileName);

	for(int i=0; i<numQueries; i++){
		query q;
		readSrcDest(q,inf);
		readAttrCon(q.vertexAttrCon,inf,numVertexAttr);
		readAttrCon(q.edgeAttrCon,inf,numEdgeAttr);
		queries.push_back(q);
	}

	inf.close();
}


