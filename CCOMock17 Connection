//maintain a forest, connect small tree to large tree, compress the enitre cycle into one node if adding edge creates cycle
//do parallel binary search by the standard DSU with undos
#include<iostream>
#include<queue>
#include<set>
using namespace std;
#define fi first
#define se second
int n,m,q;
vector<int>adj[300001];
int p[300001];
int sz[300001];
int tree[300001],bcc[300001];
int rnk[300001];
int csz=0;
int news[300001];
bool in[300001];
vector<pair<int,int> >adde[300001];
vector<pair<int,int> >edt[1048576];
vector<pair<int,int> >edt2[1048576];
vector<pair<pair<int,int>,int> >qr[1048576];
int ans[300001];
inline int find(int* par,int x){
	if(par[x]!=x) par[x]=find(par,par[x]);
	return par[x];
}
inline int finds(int* par,int x){
	if(par[x]!=x) return find(par,par[x]);
	return par[x];
}
void joins(int* par,int u,int v,int id){
	u=finds(par,u);v=finds(par,v);
	if(u==v) return;
	if(rnk[u]<rnk[v]) swap(rnk[u],rnk[v]);
	edt[id].push_back({v,par[v]});
	par[v]=u;
	if(rnk[u]==rnk[v]){
		edt2[id].push_back({u,rnk[u]});
		rnk[u]++;
	}
}
inline void dfs(int u){
	for(auto c:adj[u]){
		c=find(bcc,c);
		if(c==u) continue;
		if(c==p[u]) continue;
		p[c]=u;
		dfs(c);
	}
}
int lca(int u,int v){
	int top=0;
	int tu=u,tv=v;
	csz=0;
	while(tu!=0 || tv!=0){
		if(tu!=0){
			if(in[tu]){
				top=tu;
				break;
			}
			news[++csz]=tu;
			in[tu]=true;
			tu=p[tu];
		}
		if(tv!=0){
			if(in[tv]){
				top=tv;
				break;
			}
			news[++csz]=tv;
			in[tv]=true;
			tv=p[tv];
		}
	}
	for(int i=1; i<=csz ;i++) in[news[i]]=false;
	if(top==0) while(true);
	return top;
}
void solve(int id,int l,int r){
	if(l==r){
		for(auto cur:qr[id]) ans[cur.se]=l;
		return; 
	}
	int mid=(l+r)/2;
	for(int j=l; j<=mid ;j++){
		for(auto cur:adde[j]) joins(bcc,cur.fi,cur.se,id); 
	}
	for(auto cur:qr[id]){
		if(finds(bcc,cur.fi.fi)==finds(bcc,cur.fi.se)) qr[id*2].push_back(cur);
		else qr[id*2+1].push_back(cur);
	}
	qr[id].clear();
	qr[id].shrink_to_fit();
	solve(id*2+1,mid+1,r);
	for(int i=edt[id].size()-1; i>=0 ;i--) bcc[edt[id][i].fi]=edt[id][i].se;
	for(int i=edt2[id].size()-1; i>=0 ;i--) rnk[edt2[id][i].fi]=edt2[id][i].se;
	edt[id].clear();edt2[id].clear();
	edt[id].shrink_to_fit();edt2[id].shrink_to_fit();
	solve(id*2,l,mid);
}
int main(){
	ios::sync_with_stdio(false);
	cin >> n >> m >> q;
	for(int i=1; i<=n ;i++){
		sz[i]=1;
		tree[i]=bcc[i]=i;
	}
	for(int i=1; i<=m ;i++){
		int u,v;
		cin >> u >> v;
		u++;v++;
		if(find(bcc,u)==find(bcc,v)) continue;//worthless edge
		u=find(bcc,u);v=find(bcc,v);
		if(find(tree,u)==find(tree,v)){//make new bcc
			int top=lca(u,v);
			csz=0;
			while(u!=top){
				news[++csz]=u;
				u=p[u];
			}
			while(v!=top){
				news[++csz]=v;
				v=p[v];
			}
			news[++csz]=top;
			for(int j=1; j<=csz ;j++) in[news[j]]=true;
			int cur=1;
			for(int j=2; j<=csz ;j++) if(adj[news[cur]].size()<adj[news[j]].size()) cur=j;
			for(int j=1; j<=csz ;j++){
				if(j!=cur){
					bcc[news[j]]=news[cur];
					adde[i].push_back({news[cur],news[j]});
					for(auto k:adj[news[j]]){
						k=find(bcc,k);
						if(!in[k]) adj[news[cur]].push_back(k);
						if(!in[k] && k!=p[top]) p[k]=news[cur];
					}
					adj[news[j]].clear();
					adj[news[j]].shrink_to_fit();
				}
			}
			p[news[cur]]=p[top];
			sz[find(tree,news[cur])]-=csz-1;
			for(int j=1; j<=csz ;j++) in[news[j]]=false;
		}
		else{//join two tree
			adj[u].push_back(v);
			adj[v].push_back(u);
			if(sz[find(tree,u)]>sz[find(tree,v)]) swap(u,v);
			sz[find(tree,v)]+=sz[find(tree,u)];
			tree[find(tree,u)]=find(tree,v);
			p[u]=v;
			dfs(u);
		}
	}
	for(int i=1; i<=q ;i++){
		int u,v;
		cin >> u >> v;
		u++;v++;
		qr[1].push_back({{u,v},i});
	}
	for(int i=1; i<=n ;i++) bcc[i]=i;
	solve(1,0,m+1);
	for(int i=1; i<=q ;i++){
		if(ans[i]==m+1) cout << "-1\n";
		else cout << max(ans[i]-1,0) << '\n';
	}
}
