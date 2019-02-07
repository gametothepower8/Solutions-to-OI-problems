/*
Consider any subsegment of the supply plan. No matter how other elements change, only 5 path have to be considered.
For each pair of nodes, greedily (by weight) find 5 paths such that no 3 use the same road as start and no 3 use the same road as end.
Some dijkstra with special care can handle this.
We can do divide and conquer and merge them by computing all 5*5 possibilities and eliminate until 5 paths.
A simple segtree can handle updates.
Prove of correctness = ???
*/
#include<iostream>
#include<queue>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
#define fi first
#define se second
#define pb push_back
int n,m,q,k;
vector<int>adj[2001];
int u[4001],v[4001],w[4001];
int f(int x){return ((x-1)^1)+1;}
 
ll dis[4001];
int cnt[4001];
bool vis[4001];
priority_queue<pli,vector<pli>,greater<pli> >pq;
 
struct path{
	int s,e;ll w;
};
path inf={0,0,(ll)1e18};
vector<path>tae[2001][2001];
vector<path>tzu;
 
void elim(vector<path>&e){
	tzu.clear();tzu.shrink_to_fit();
	for(int i=0; i<5 ;i++){
		path res=inf;
		for(auto newi:e){
			int sx=0,ex=0,px=0;
			for(auto cur:tzu) sx+=(newi.s==cur.s),ex+=(newi.e==cur.e),px+=(newi.s==cur.s && newi.e==cur.e);
			if(sx>=2 || ex>=2 || px>=1) continue;
			if(res.w>newi.w) res=newi; 
		}
		tzu.push_back(res);
	}
	e=tzu;
	e.shrink_to_fit();
}
int x[100001];
vector<path>rv[400001];
void pull(int id){
	rv[id].clear();
	for(int i=0; i<5 ;i++){
		for(int j=0; j<5 ;j++){
			if(rv[id*2][i].e!=rv[id*2+1][j].s){
				rv[id].push_back({rv[id*2][i].s,rv[id*2+1][j].e,rv[id*2][i].w+rv[id*2+1][j].w});
			}
		}
	}
	elim(rv[id]);
}
void build(int id,int l,int r){
	if(l+1==r){
		rv[id]=tae[x[l]][x[r]];
		return;
	}
	int mid=(l+r)/2;
	build(id*2,l,mid);build(id*2+1,mid,r);
	pull(id);
}
void upd(int id,int l,int r,int y){
	if(r<y || l>y) return;
	if(l+1==r){
		rv[id]=tae[x[l]][x[r]];
		return;
	}
	int mid=(l+r)/2;
	upd(id*2,l,mid,y);upd(id*2+1,mid,r,y);
	pull(id);
}
void out(vector<path>&v){
	for(auto cur:v){
		cout << cur.s << ' ' << cur.e << ' ' << cur.w << endl;
	}
}
int main(){
	ios::sync_with_stdio(false);
	tzu.resize(5);
	cin >> n >> m >> q >> k;
	for(int i=1; i<=m ;i++){
		cin >> u[i*2] >> v[i*2] >> w[i*2];
		u[i*2-1]=v[i*2],v[i*2-1]=u[i*2];w[i*2-1]=w[i*2];
		adj[u[i*2]].push_back(i*2);adj[v[i*2]].push_back(i*2-1);
	}
	for(int i=1; i<=n ;i++){
		for(auto kirino:adj[i]){
			for(int j=1; j<=2*m ;j++) cnt[j]=0,vis[j]=false,dis[j]=1e18;
			dis[kirino]=w[kirino];
			pq.push({dis[kirino],kirino});
			while(!pq.empty()){
				int cur=pq.top().se;pq.pop();
				int id=u[cur];
				if(vis[cur] || cnt[id]>=2) continue;
				vis[cur]=true;cnt[id]++;
				for(auto newi:adj[id]){
					if(cur==newi) continue;
					newi=f(newi);//1 based :(
					if(dis[newi]>dis[cur]+w[newi]){
						dis[newi]=dis[cur]+w[newi];
						pq.push({dis[newi],newi});
					}
				}
			}
			for(int j=1; j<=2*m ;j++){
				tae[v[kirino]][u[j]].push_back({f(kirino),j,dis[j]});
			}
		}
	}
	for(int i=1; i<=n ;i++){
		for(int j=1; j<=n ;j++){
			elim(tae[i][j]);
		}
	}
	for(int i=1; i<=k ;i++) cin >> x[i];
	build(1,1,k);
	for(int i=1; i<=q ;i++){
		int u,v;cin >> u >> v;
		x[u]=v;upd(1,1,k,u);
		ll ans=rv[1][0].w;
		if(ans>=1e18) cout << "-1\n";
		else cout << ans << '\n';
	}
	
}
