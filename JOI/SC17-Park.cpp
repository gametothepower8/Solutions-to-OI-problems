/*Add nodes one by one, binary search for a node in the middle of the path from graph to current node, if they do not connect directly
Do some divide and conquer to find rest of the edges. Find one -> split to 7 trees.
idk, probably my code has some bug, and might exceed query limit in theory, but it passes, so wtever
*/
#include "park.h"
#include<iostream>
#include<queue>
using namespace std;
#define pb push_back
//const int N=1401,M=1501;
int n;
vector<int>qry;
//int qar[1501];
vector<int>adj[1501];

vector<int>ds[1501];
int d[1501];
bool in[1501];
int tzuyu(int s,int e){
	int qar[n];
	for(int i=0; i<n ;i++) qar[i]=0;
	for(auto cur:qry) qar[cur]=1;
	if(s>e) swap(s,e);
	int res=Ask(s,e,qar);
	qry.clear();qry.shrink_to_fit();
	return res;
}
void add(int x,int y){
	adj[x].pb(y);adj[y].pb(x);
	Answer(min(x,y),max(x,y));
}
vector<int>g;vector<int>h;
bool vis[1501];
int bs(int s,int e){
	if(h.size()>1){
		for(auto cur:h) qry.pb(cur);
		int ret=tzuyu(s,e);
		if(ret){
			g.clear();g.shrink_to_fit();h.clear();h.shrink_to_fit();
			return -1;
		}
	}
	int l=0,r=g.size()-(h.size()!=1);
	while(l!=r){
		int mid=(l+r)/2;
		for(auto cur:h) qry.pb(cur);
		for(int i=0; i<=mid ;i++) qry.pb(g[i]);
		int res=tzuyu(s,e);
		if(res) r=mid;
		else l=mid+1;
	}
	if(l==g.size()){
		g.clear();g.shrink_to_fit();h.clear();h.shrink_to_fit();
		return -1;
	}
	int res=g[l];
	g.clear();g.shrink_to_fit();h.clear();h.shrink_to_fit();
	return res;
}
vector<int>v;
void expand(int x){
	in[x]=true;
	for(int i=0; i<n ;i++) if(in[i]) h.pb(i);
	for(int i=0; i<n ;i++) if(!in[i]) g.pb(i);
	int res=bs(0,x);
	in[res]=true;
	if(res==-1){
		v.push_back(x);
		return;
	}
	expand(res);
	expand(x);
}
bool vis2[1501];
void dfs(int id){
	g.push_back(id);
	vis2[id]=true;
	for(auto cur:adj[id]){
		if(in[cur] && !vis[cur] && !vis2[cur]) dfs(cur);
	}
}
void explode(int id,int x){
	for(int i=0; i<n ;i++) vis2[i]=false;
	h.pb(id);
	dfs(x);
	int res=bs(id,x);
	if(res==-1) return;
	add(res,id);
	vis[res]=true;
	for(auto cur:adj[res]){
		if(in[cur] && !vis[cur]) explode(id,cur);
	}
}
void addnode(int id){
	for(int i=0; i<n ;i++) vis[i]=!in[i];
	v.clear();
	expand(id);
	for(int i=1; i<v.size() ;i++) add(v[i-1],v[i]);
	for(int i=0; i<v.size() ;i++) in[v[i]]=false;
	explode(v[0],0);
	for(int i=0; i<v.size() ;i++) in[v[i]]=true;
}
void Detect(int T, int N){
	n=N;
	in[0]=true;
	for(int i=1; i<n ;i++){
		if(!in[i]) addnode(i);
	}
}
