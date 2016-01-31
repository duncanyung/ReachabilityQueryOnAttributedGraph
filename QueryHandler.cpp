#include "QueryHandler.h"


int IOCount = 0;

pair<bool,int> QueryHandler::CReachabilityQuery(vector<vector<pair<int,int> > >& topology,vector<unsigned long long>& vertexHashValues,
											vector<unsigned long long>& edgeHashValues,query& q,const char* attrFolderName,
											int vRowSize,int eRowSize,bool useConstraint,bool hashOpt){

	IOCount = 0;

	queue<pair<int,int> > qu;
	vector<bool> visited;
	visited.assign(topology.size()+1,false);
	unordered_map<unsigned long long,bool> satTableE,satTableV;

	char vertexAttrFileName[200],edgeAttrFileName[200];
	sprintf(vertexAttrFileName,"%s/VertexAttr.txt",attrFolderName);
	sprintf(edgeAttrFileName,"%s/EdgeAttr.txt",attrFolderName);
	ifstream infV(vertexAttrFileName);
	ifstream infE(edgeAttrFileName);

	qu.push(make_pair(q.src,-1));
	while(!qu.empty()){
		pair<int,int> h = qu.front();
		qu.pop();

		if(visited[h.first]==true)
			continue;
		visited[h.first]=true;

		bool result = BFS_C(h.first,topology,vertexHashValues,edgeHashValues,q,qu,visited,satTableE,satTableV,
							vertexAttrFileName,edgeAttrFileName,infV,infE,vRowSize,eRowSize,useConstraint,hashOpt);

//		printf("src %d dest %d topology.size()=%d\n",q.src,q.dest,topology.size());

		if(result == true)
			return make_pair(true,IOCount);
//		qu.push(make_pair());
	}

	infV.close();
	infE.close();

	return make_pair(false,IOCount);
}

bool QueryHandler::BFS_C(int cur,vector<vector<pair<int,int> > >& topology,vector<unsigned long long>& vertexHashValues,
						vector<unsigned long long>& edgeHashValues,query& q,queue<pair<int,int> >& quGlobal,vector<bool>& visited,
						unordered_map<unsigned long long,bool>& satTableE,unordered_map<unsigned long long,bool>& satTableV,
						const char* vertexAttrFileName,const char* edgeAttrFileName,ifstream& infV,ifstream& infE,int vRowSize,
						int eRowSize,bool useConstraint,bool hashOpt){

	queue<pair<int,int> > qu;
	qu.push(make_pair(cur,-1));
	while(!qu.empty()){
		pair<int,int> h = qu.front();
		qu.pop();

		int cur = h.first;
		if(cur==q.dest)
			return true;

		for(int i=0; i<topology[cur].size();i++){
			int adjVertex = topology[cur][i].first;
			if(visited[adjVertex]==true)
				continue;
			visited[adjVertex]=true;

			//check Edge constraint
			int adjEdgeID = topology[cur][i].second;
			if(useConstraint && (!CheckConstraint(adjEdgeID,edgeHashValues,q.edgeAttrCon,satTableE,edgeAttrFileName,infE,eRowSize,hashOpt)))
				continue;
			//check Vertex constraint
			if(useConstraint && (!CheckConstraint(adjVertex,vertexHashValues,q.vertexAttrCon,satTableV,vertexAttrFileName,infV,vRowSize,hashOpt)))
				continue;
			
			qu.push(make_pair(adjVertex,-1));
		}
	}
	return false;
}

bool QueryHandler::CheckConstraint(int id, vector<unsigned long long>& hashValues,vector<vector<int> >& con,
									unordered_map<unsigned long long,bool>& satTable,const char* attrFileName,ifstream& inf,int rowSize,
									bool hashOpt){

	unordered_map<unsigned long long,bool>::const_iterator got = satTable.find(hashValues[id]);
	if(hashOpt && (got!=satTable.end())){
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

    	if(skipFirst == false){
        	elems.push_back(stoi(item));
//        	printf("%d ",stoi(item));
        }
        skipFirst = false;
    }
//   printf("\n");
}

void QueryHandler::IOAttr(int id,const char* attrFileName,vector<int>& attr,ifstream& inf,int rowSize){
	//use fseek here!

	//get the id^th row in attrFileName
	string strData;
	int addr = id*rowSize;
	inf.seekg(addr);
	getline(inf,strData);

	IOCount++;
//	printf("Row=%d Attr= %s\n",id,strData.c_str());
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

bool QueryHandler::SimpleBFS(query& q,vector<vector<pair<int,int> > >& topology){
	//Really Not Reachable? Yes as 
	//In PA dataset:
	//47922 and 47923 is an island!!!!
	//946588 and 946589 is an island!!!
	//606555 and 606556 is an island!!!

	queue<pair<int,int> > qu;
	vector<bool> visited;
	visited.assign(topology.size()+1,false);

	qu.push(make_pair(q.src,-1));
	while(!qu.empty()){
		pair<int,int> h = qu.front();
		qu.pop();

		int cur = h.first;
		if(cur==q.dest)
			return true;
		for(int i=0; i<topology[h.first].size();i++){
			int adjVertex = topology[cur][i].first;
			if(visited[adjVertex]==true)
				continue;
			visited[adjVertex]=true;
			qu.push(make_pair(adjVertex,-1));
		}
	}

	return false;
}

bool QueryHandler::DFS(int cur, vector<vector<pair<int,int> > >& topology,query& q,vector<bool>& visited){
	for(int i=0; i<topology[cur].size(); i++){
		int adjVertex = topology[cur][i].first;

		if(adjVertex == q.dest)//No need to check attr of dest.
			return true;

		if(visited[adjVertex] == false){
			visited[adjVertex] = true;
			bool result = QueryHandler::DFS(adjVertex,topology,q,visited);
			if(result == true)
				return true;
		}
	}
	return false;
}

bool QueryHandler::DFS_C(int cur,vector<vector<pair<int,int> > >& topology,vector<unsigned long long>& vertexHashValues,
						vector<unsigned long long>& edgeHashValues,query& q,queue<pair<int,int> >& qu,vector<bool>& visited,
						unordered_map<unsigned long long,bool>& satTableE,unordered_map<unsigned long long,bool>& satTableV,
						const char* vertexAttrFileName,const char* edgeAttrFileName,/*ifstream& infV,ifstream& infE,*/int vRowSize,
						int eRowSize,bool useConstraint){

//	printf("cur=%d\n",cur);
	for(int i=0; i<topology[cur].size(); i++){
		int adjVertex = topology[cur][i].first;
		if(adjVertex == q.dest)//No need to check attr of dest.
			return true;
		if(visited[adjVertex] == false){
			//check Edge constraint
/*			int adjEdgeID = topology[cur][i].second;
			if(useConstraint && (!CheckConstraint(adjEdgeID,edgeHashValues,q.edgeAttrCon,satTableE,edgeAttrFileName,infE,eRowSize)))
				continue;
			//check Vertex constraint
			if(useConstraint && (!CheckConstraint(adjVertex,vertexHashValues,q.vertexAttrCon,satTableV,vertexAttrFileName,infV,vRowSize)))
				continue;
*/			
			visited[adjVertex] = true;
			bool result = DFS_C(adjVertex,topology,vertexHashValues,edgeHashValues,q,qu,visited,satTableE,satTableV,
								vertexAttrFileName,edgeAttrFileName,/*infV,infE,*/vRowSize,eRowSize,useConstraint);
			if(result == true)
				return true;
		}
	}

	return false;
}


