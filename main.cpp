#include "AttrGenerator.h"


void Preprocessing(char const *argv[]){
	printf("Do Preprocessing\n");
	/*Pre-processing Functions*/
	int function = atoi(argv[1]);
	switch(function +'0'){
		case '1':{//attribute generator
			printf("Attribute Generator\n");
			const char* fileName = argv[2];
			const char* attrFolderName = argv[3];
			int numVAttr = atoi(argv[4]);
			int numEAttr = atoi(argv[5]);
			int maxDomainSize = atoi(argv[6]);
			int minDomainSize = atoi(argv[7]);
			printf("%s %s %d %d %d %d\n",fileName,attrFolderName,numVAttr,numEAttr,maxDomainSize,minDomainSize);
			vector<vector<int> > topology;
			
			utility ut;
			ut.readTopolgy(fileName,topology);
			AttrGenerator genAttr;
		//	genAttr.generatorAttribute(folderName,topology);
			break;
		}case '2':{//pre-processing attributes to individual files 
			printf("pre-processing attributes to individual files\n");
			
			//One vertex/edge attribute 1 file. Is that correct?
				//read attribute and put them into individual files
				//different data have different format

			break;
		}case '3':{//hash scheme index construction
			printf("hash scheme index construction\n");

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
		//query generator

		//read graph topology


		//query algorithm	
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



