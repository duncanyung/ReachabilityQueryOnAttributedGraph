

#ifndef __READTOPOLOGY_H_INCLUDED__
//#define __READTOPOLOGY_H_INCLUDED__
#include "ReadTopology.h"
#endif

#include "utility.h"
#include "AttrGenerator.h"

//#include "ReadTopology.h"
//using namespace std;

int main(int argc, char const *argv[]){
	
	printf("Reachability Query on Attributed Graph\n");

/*Pre-processing Functions*/
	//attribute generator
	AttrGenerator genAttr;
	genAttr.hello();

	//pre-processing attributes to individual files 
	//One vertex/edge attribute 1 file. Is that correct?
		//read attribute and put them into individual files
		//different data have different format

	//hash scheme index construction

	//super-graph construction [not to use super graph first]


/*Query Time Functions*/
	//query generator

	//read graph topology
	ReadTopology readTopo;
	readTopo.readTopo();

	//query algorithm


	return 0;
}



