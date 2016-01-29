#include "QueryGenerator.h"


void QueryGenerator::generateQuery(vector<query>& queries,int numQuery,int numEAttr,int numVAttr,const char* attrFolderName){
	char vertexAttrFileName[200],edgeAttrFileName[200];
	sprintf(vertexAttrFileName,"%s/VertexAttr.txt",attrFolderName);
	sprintf(edgeAttrFileName,"%s/EdgeAttr.txt",attrFolderName);

	for(int i=0; i<numQuery; i++){
		query q;

	}
}