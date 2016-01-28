#include "QueryHandler.h"



bool QueryHandler::CReachabilityQuery(vector<vector<pair<int,int> > >& topology,vector<unsigned long long>& vertexHashValues,
											vector<unsigned long long>& edgeHashValues,query& q,const char* attrFolderName){

	queue<pair<int,int> > qu;
	vector<bool> visited;
	visited.assign(topology.size(),false);
	while(!qu.empty()){
		pair<int,int> h = qu.front();
		qu.pop();

		if(visited[h.first]==true)
			continue;
		visited[h.first]=true;

		bool result = DFS_C(h.first,topology,vertexHashValues,edgeHashValues,q,qu,visited);
//		qu.push(make_pair());
	}


	return false;
}


bool QueryHandler::DFS_C(int cur, vector<vector<pair<int,int> > >& topology,vector<unsigned long long>& vertexHashValues,
						vector<unsigned long long>& edgeHashValues,query& q,queue<pair<int,int> >& qu,vector<bool>& visited){

	for(int i=0; i<topology[cur].size(); i++){
		if(topology[cur][i].first == q.dest)
			return true;
		if(visited[topology[cur][i].first]==false){
//			if(!CheckConstraint())//check Edge constraint
//				continue;
//			if(!CheckConstraint())//check vertex constraint
//				continue;
			
			visited[topology[cur][i].first] = true;
			bool result = DFS_C(topology[cur][i].first,topology,vertexHashValues,edgeHashValues,q,qu,visited);
			if(result == true)
				return true;
		}
	}

	return false;
}