//Transfer into a tree problem and becomes ez to solve
#include<iostream>
#include<queue>
#include<algorithm>
#include<map>
using namespace std;
#define fi first
#define se second
int n;
map<pair<int,int>,vector<int> >m;
vector<int>adj[100001];
vector<int>st[100001];
vector<int>link[100001];
int a[3];
int d[100001];
int par[100001];
bool col[100001];
int bon[100001];
int ans=0;
int find(int x){
	if(par[x]!=x) par[x]=find(par[x]);
	return par[x];
}
void join(int x,int y){
	par[find(x)]=find(y);
}
void dfs(int id,int p){
	par[id]=id;
	for(auto cur:adj[id]){
		if(cur==p) continue;
		dfs(cur,id);
		join(cur,id);
	}
	col[id]=true;
	for(auto cur:link[id]){
		if(!col[cur]) continue;
		int lca=find(cur);
		bon[id]++;bon[cur]++;bon[lca]-=2;
	}
}
void dfs2(int id,int p){
	for(auto cur:adj[id]){
		if(cur==p) continue;
		dfs2(cur,id);
		bon[id]+=bon[cur];
	}
	if(bon[id]==0 && id!=1) ans++;
}
int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i=1; i<=n-2 ;i++){
        for(int j=0; j<3 ;j++) cin >> a[j];
        cin >> d[i];
        st[d[i]].push_back(i);
        for(int j=0; j<3 ;j++){
            int k=(j+1)%3;
            m[{min(a[j],a[k]),max(a[j],a[k])}].push_back(i);
        }
    }
    for(int i=1; i<=n ;i++){
    	for(int j=1; j<st[i].size() ;j++){
    		link[st[i][j-1]].push_back(st[i][j]);
    		link[st[i][j]].push_back(st[i][j-1]);
		}
	}
    for(auto tmp:m){
        auto cur=tmp.se;
        if(cur.size()==2){
            adj[cur[0]].push_back(cur[1]);
            adj[cur[1]].push_back(cur[0]);
        }
    }
    n-=2;
    dfs(1,0);
    dfs2(1,0);
    cout << ans << endl;
}
