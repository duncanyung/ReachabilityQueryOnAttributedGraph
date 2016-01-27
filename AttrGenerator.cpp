#include "AttrGenerator.h"



void AttrGenerator::generateVertexAttr(const char* attrFolderName,vector<vector<int> >& topology,int numVAttr,int maxDomainSize){
	srand(time(NULL));

	char fileName[200];
	sprintf(fileName,"%s/VertexAttr.txt",attrFolderName);
	FILE * outFile = fopen(fileName,"w");
	fprintf(outFile,"Num_Attr %d\n",numVAttr);
//	fprintf(outFile,"Domain_Size ");

	vector<int> attrDomainSize;
	for(int i=0; i<numVAttr; i++){
		int d = max(rand()%maxDomainSize,1);
		attrDomainSize.push_back(d);
//		fprintf(outFile,"%d ",d);
	}
//	fprintf(outFile,"\n");

	for(int i=1;i<=topology.size();i++){
		string attr=to_string(i);
		attr.append(",");
		for(int j=0; j<numVAttr; j++){
			int temp=rand()%attrDomainSize[j];
			attr.append(to_string(temp));
			attr.append(",");
		}

		fprintf(outFile,"%s\n",attr.c_str());
		if(i%10000==0)
			printf("Generating Vertex Attr %d\n",i);
	}

	fclose(outFile);
}

void AttrGenerator::generateEdgeAttr(const char* attrFolderName,vector<vector<int> >& topology,int numEAttr,int maxDomainSize){
	srand(time(NULL));

	char fileName[200];
	sprintf(fileName,"%s/EdgeAttr.txt",attrFolderName);
	FILE * outFile = fopen(fileName,"w");
	fprintf(outFile,"Num_Attr %d\n",numEAttr);
//	fprintf(outFile,"Domain Size ");

	vector<int> attrDomainSize;
	for(int i=0; i<numEAttr; i++){
		int d = max(rand()%maxDomainSize,1);
		attrDomainSize.push_back(d);
//		fprintf(outFile,"%d ",d);
	}
//	fprintf(outFile,"\n");

	int edgeCount=0;
	for(int i=1;i<=topology.size();i++){
		for(int j=0;j<topology[i].size();j++){
			string attr=to_string(i);
			attr.append(",");
			attr.append(to_string(topology[i][j]));
			attr.append(",");

			for(int k=0; k<numEAttr; k++){
				int temp=rand()%attrDomainSize[k];
				attr.append(to_string(temp));
				attr.append(" ");
			}

			fprintf(outFile,"%s\n",attr.c_str());
			if(edgeCount%10000==0)
				printf("Generating Edge Attr %d\n",edgeCount);

			edgeCount++;
		}
	}

	fclose(outFile);
}

void AttrGenerator::generateAttribute(const char* attrFolderName,vector<vector<int> >& topology,int numVAttr,int numEAttr,int maxDomainSize){

	generateVertexAttr(attrFolderName,topology,numVAttr,maxDomainSize);
	generateEdgeAttr(attrFolderName,topology,numEAttr,maxDomainSize);
}


