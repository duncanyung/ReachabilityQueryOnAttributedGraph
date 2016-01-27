#include "ComputeHashValue.h"
#include "utility.h"

void ComputeHashValue::_computeHashValue(char* vertexAttrHashFileName, char* vertexAttrFileName, bool isNode){
	FILE * attrFile = fopen(vertexAttrFileName,"r");
	FILE * hashFile = fopen(vertexAttrHashFileName,"w");

	char s[10];
	int numAttr = 0,ID = 0, ID2 = 0,count = 0;
	fscanf(attrFile,"%s %d\n",s,&numAttr);

	utility ut;
	const unsigned long long _prime = ut.prime;

	while(fscanf(attrFile,"%d,",&ID)!=EOF){
		if(isNode==false)
			fscanf(attrFile,"%d,",&ID2);

		unsigned long long hashValue = 0;
		unsigned long long c = ut.constant;
		for(int i=0; i<numAttr; i++){
			int temp=0;
			fscanf(attrFile,"%d,",&temp);
			hashValue = hashValue + temp*c;
			c = c*c;
		}
		fscanf(attrFile,"\n");
		hashValue=hashValue%_prime;
		if(isNode==true)
			fprintf(hashFile,"%d %lld\n",ID,hashValue);
		else
			fprintf(hashFile,"%d %d %lld\n",ID,ID2,hashValue);

		count++;
		if(count%10000==0 && isNode==true)
			printf("Generating Hash for Vertex %d\n",count);
		else if(count%10000==0 && isNode==false)
			printf("Generating Hash for Edge %d\n",count);
	}

	fclose(attrFile);
	fclose(hashFile);
}

void ComputeHashValue::computeHashValue(const char* hashFolderName,const char* attrFolderName){

	char vertexAttrFileName[200],edgeAttrFileName[200],vertexAttrHashFileName[200],edgeAttrHashFileName[200];
	sprintf(vertexAttrHashFileName,"%s/VertexAttrHash.txt",hashFolderName);
	sprintf(edgeAttrHashFileName,"%s/EdgeAttrHash.txt",hashFolderName);
	sprintf(vertexAttrFileName,"%s/VertexAttr.txt",hashFolderName);
	sprintf(edgeAttrFileName,"%s/EdgeAttr.txt",hashFolderName);

	//////////////////////////////////////////////////////////////////////////
	_computeHashValue(vertexAttrHashFileName,vertexAttrFileName,true);
	_computeHashValue(edgeAttrHashFileName,edgeAttrFileName,false);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//for computing edge attribute hash
/*	FILE * eAttrFile = fopen(edgeAttrFileName,"r");
	FILE * eHashFile = fopen(edgeAttrHashFileName,"w");

	char s2[10];
	int numEAttr=0,eID=0,eCount=0,n1=0,n2=0;
	fscanf(eAttrFile,"%s %d\n",s2,&numEAttr);
	vector<int> eAttr;

	while(fscanf(eAttrFile,"%d,%d,",&n1,&n2)!=0){
		for(int i=0;i<numEAttr;i++){
			int temp2=0;
			fscanf(eAttrFile,"%d,",&temp2);
			eAttr.push_back(temp2);
		}
		fscanf(eAttrFile,"\n");
		unsigned long long eHashValue = ut.hashFunction(eAttr);
		fprintf(eHashFile,"%d %d %lld\n",n1,n2,eHashValue);
//		printf("eHashValue=%lld\n",eHashValue);

		eCount++;
		if(eCount%10000==0)
			printf("Generating Hash for Edge %d\n",eCount);
	}

	fclose(eAttrFile);
	fclose(eHashFile);*/

	//////////////////////////////////////////////////////////////////////////
}


