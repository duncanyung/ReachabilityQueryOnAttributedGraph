#include "AttrGenerator.h"


int AttrGenerator::countIntDigit(int x){
	int length = 1;
	while ( x /= 10 )
	   length++;

	return length;
}

void AttrGenerator::_generateAttribute(const char* attrFolderName,vector<vector<pair<int,int> > >& topology,int numAttr,int maxDomainSize,bool isEdge,int numEdge = 0){
	srand(time(NULL));

	char fileName[200];
	if(isEdge==true)
		sprintf(fileName,"%s/EdgeAttr.txt",attrFolderName);
	else
		sprintf(fileName,"%s/VertexAttr.txt",attrFolderName);

	FILE * outFile = fopen(fileName,"w");
	fprintf(outFile,"Num_Attr %d\n",numAttr);

	vector<int> attrDomainSize;
	for(int i=0; i<numAttr; i++){
		int d = max(rand()%maxDomainSize,1);
		attrDomainSize.push_back(d);
	}

	int numRow = 0;
	int numDigit1 = countIntDigit(maxDomainSize);
	int numDigit2;
	if(isEdge == true) 
		numDigit2 = countIntDigit(numEdge);
	else
		numDigit2 = countIntDigit(topology.size());

	if(isEdge==true)
		numRow = numEdge;
	else
		numRow = topology.size();

	for(int i=1;i<=numRow;i++){
		string attr=to_string(i);
		attr.append(",");
		for(int j=0; j<numAttr; j++){
			int temp=rand()%attrDomainSize[j];
			attr.append(to_string(temp));
			attr.append(",");
		}

		int extraSpace = numDigit2 + (numAttr*numDigit1+numAttr+1) - attr.length();

		for(int j=0; j<extraSpace; j++)
			attr.append(" ");

		fprintf(outFile,"%s\n",attr.c_str());
		if(i%10000==0 && isEdge==false)
			printf("Generating Vertex Attr %d\n",i);
		else if (i%10000==0 && isEdge==true)
			printf("Generating Edge Attr %d\n",i);
	}

	fclose(outFile);
}


void AttrGenerator::generateAttribute(const char* attrFolderName,vector<vector<pair<int,int> > >& topology,int numVAttr,int numEAttr,int maxDomainSize,int numEdge){

	_generateAttribute(attrFolderName,topology,numVAttr,maxDomainSize,false);
	_generateAttribute(attrFolderName,topology,numEAttr,maxDomainSize,true,numEdge);

}
