#include "QueryHandler.h"



bool QueryHandler::CReachabilityQuery(vector<vector<pair<int,int> > >& topology,vector<unsigned long long>& vertexHashValues,
											vector<unsigned long long>& edgeHashValues,query& q,const char* attrFolderName,
											int vRowSize,int eRowSize){

	queue<pair<int,int> > qu;
	vector<bool> visited;
	visited.assign(topology.size(),false);
	unordered_map<unsigned long long,bool> satTableE,satTableV;

	char vertexAttrFileName[200],edgeAttrFileName[200];
	sprintf(vertexAttrFileName,"%s/VertexAttr.txt",attrFolderName);
	sprintf(edgeAttrFileName,"%s/EdgeAttr.txt",attrFolderName);
	ifstream infV(vertexAttrFileName);
	ifstream infE(edgeAttrFileName);

	while(!qu.empty()){
		pair<int,int> h = qu.front();
		qu.pop();

		if(visited[h.first]==true)
			continue;
		visited[h.first]=true;

		bool result = DFS_C(h.first,topology,vertexHashValues,edgeHashValues,q,qu,visited,satTableE,satTableV,
							vertexAttrFileName,edgeAttrFileName,infV,infE,vRowSize,eRowSize);
//		qu.push(make_pair());
	}

	infV.close();
	infE.close();
	return false;
}

bool QueryHandler::DFS_C(int cur, vector<vector<pair<int,int> > >& topology,vector<unsigned long long>& vertexHashValues,
						vector<unsigned long long>& edgeHashValues,query& q,queue<pair<int,int> >& qu,vector<bool>& visited,
						unordered_map<unsigned long long,bool>& satTableE,unordered_map<unsigned long long,bool>& satTableV,
						const char* vertexAttrFileName,const char* edgeAttrFileName,ifstream& infV,ifstream& infE,int vRowSize,int eRowSize){

	for(int i=0; i<topology[cur].size(); i++){
		if(topology[cur][i].first == q.dest)
			return true;
		if(visited[topology[cur][i].first]==false){
			if(!CheckConstraint(topology[cur][i].second,edgeHashValues,q.edgeAttrCon,satTableE,edgeAttrFileName,infE,eRowSize))//check Edge constraint
				continue;
//			if(!CheckConstraint())//check vertex constraint
//				continue;
			
			visited[topology[cur][i].first] = true;
			bool result = DFS_C(topology[cur][i].first,topology,vertexHashValues,edgeHashValues,q,qu,visited,satTableE,satTableV,
								vertexAttrFileName,edgeAttrFileName,infV,infE,vRowSize,eRowSize);
			if(result == true)
				return true;
		}
	}

	return false;
}



bool QueryHandler::CheckConstraint(int id, vector<unsigned long long>& hashValues,vector<vector<int> >& con,
									unordered_map<unsigned long long,bool>& satTable,const char* attrFileName,ifstream& inf,int rowSize){

	unordered_map<unsigned long long,bool>::const_iterator got = satTable.find(hashValues[id]);
	if(got!=satTable.end()){
		return got->second; 
	}else{
		vector<int> attr;
		IOAttr(id,attrFileName,attr,inf,rowSize);
		if(CheckAttr(attr,con)){
			satTable.insert(make_pair(hashValues[id],true));
			return true;
		}else{
			satTable.insert(make_pair(hashValues[id],false));
			return false;
		}
	}
	return false;
}

void QueryHandler::split(const string &s, char delim, vector<int> &elems,bool skipFirst){
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
    	if(item.compare("")==0)
    		break;

    	if(skipFirst == false)
        	elems.push_back(stoi(item));
        skipFirst = false;
    }
}

void QueryHandler::IOAttr(int id,const char* attrFileName,vector<int>& attr,ifstream& inf,int rowSize){
	//use fseek here!

	//get the id^th row in attrFileName
	string strData;
	int addr = id*rowSize;
	inf.seekg(addr);
	getline(inf,strData);

	split(strData,',',attr,true);

}

bool QueryHandler::CheckAttr(vector<int>& attr,vector<vector<int> >& con){
	for(int i=0; i<attr.size(); i++){
		bool sat = false;
		for(int j=0; j<con[i].size(); j++){
			if(attr[i]==con[i][j]){
				sat=true;
				break;
			}
		}
		if(sat == false)
			return false;
	}
	return true;
}

