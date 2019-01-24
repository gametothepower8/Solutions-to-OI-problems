/*
Change the subject to counting the number of "middle" nodes
Calculate the count by transfering into several updates of "add 1 to all points with distance exactly k to node x"
Count by centroid decomposition, handling each update recursively
*/
#include<iostream>
#include<queue>
using namespace std;
const int N=7e5+1;
#define fi first
#define se second
int n;
bool die[N];
vector<int>adj[N];

int ans[N];
int d[N],boss[N],sz[N];
int tsz;
int val[N];
vector<pair<int,int> >yerin[N];//depth,value
vector<pair<int,int> >upd[N];
int usz;
pair<int,int>cupd[N];//node,dist

void dfs4(int id,int p){
	sz[id]=1;++tsz;
	for(auto cur:adj[id]){
		if(cur==p || die[cur]) continue;
		dfs4(cur,id);
		sz[id]+=sz[cur];
	}
}
int get_mid(int id,int p){
	if(sz[id]*2<tsz) return 0;
	bool ok=true;
	int res=0;
	for(auto cur:adj[id]){
		if(cur==p || die[cur]) continue;
		if(res==0) res=get_mid(cur,id);
		if(sz[cur]*2>tsz) ok=false;
	}
	if(ok) res=id;
	return res;
}
void dfs3(int id,int p,int t){
	boss[id]=t;
	d[id]=d[p]+1;
	for(auto cur:adj[id]){
		if(cur==p || die[cur]) continue;
		if(t==0) dfs3(cur,id,cur);
		else dfs3(cur,id,t);
	}
}
void upd_ans(int id,int p){
	for(auto cur:yerin[id]) val[cur.fi]+=cur.se;
	ans[id]+=val[d[id]];
	for(auto cur:adj[id]){
		if(cur==p || die[cur]) continue;
		upd_ans(cur,id);
	}
	for(auto cur:yerin[id]) val[cur.fi]-=cur.se;
	yerin[id].clear();yerin[id].shrink_to_fit();
}
void solve(int id){
	usz=0;
	for(auto cur:upd[id]) cupd[++usz]=cur;
	upd[id].clear();upd[id].shrink_to_fit();
	tsz=0;
	dfs4(id,0);
	int mid=get_mid(id,0);
	dfs3(mid,0,0);
	for(int i=1; i<=usz ;i++){
		auto cur=cupd[i];
		if(cur.fi==mid) yerin[mid].push_back({cur.se+1,1});
		else if(d[cur.fi]<=cur.se+1){
			yerin[mid].push_back({cur.se-d[cur.fi]+2,1});
			yerin[boss[cur.fi]].push_back({cur.se-d[cur.fi]+2,-1});
			upd[boss[cur.fi]].push_back(cur);
		}
		else upd[boss[cur.fi]].push_back(cur);
	}
	upd_ans(mid,0);
	die[mid]=true;
	for(auto cur:adj[mid])
		if(!die[cur]) solve(cur);
}
struct leaf{
	int b,dis;
};
leaf trans(int id,int cur,leaf u){
	u.b=cur;
	u.dis++;
	return u;
}
bool operator<(leaf u,leaf v){
	return u.dis>v.dis;
}
leaf max(leaf u,leaf v){
	if(u<v) return v;
	else return u;
}
leaf zero={0,1e9};
leaf d1[N],d2[N];
void dfs1(int id,int p){
	d1[id]=d2[id]=zero;
	d[id]=d[p]+1;
	if(adj[id].size()==1) d1[id]={0,0};
	for(auto cur:adj[id]){
		if(cur==p) continue;
		dfs1(cur,id);
		d2[id]=max(d2[id],trans(id,cur,d1[cur]));
		if(d1[id]<d2[id]) swap(d1[id],d2[id]);
	}
}
void dfs2(int id,int p){
	if(p!=0){
		leaf newi=d1[p];
		if(newi.b==id) newi=d2[p];
		d2[id]=max(d2[id],trans(id,p,newi));
		if(d1[id]<d2[id]) swap(d1[id],d2[id]);
	}
	//cout << id << ' ' << d1[id].b << ' ' << d2[id].b << endl;
	for(auto cur:adj[id]){
		if(cur==p) continue;
		dfs2(cur,id);
	}
}
void dfs5(int id,int p){
	for(auto cur:adj[id]){
		if(cur==p) continue;
		dfs5(cur,id);
		int cd=d1[id].dis;
		int pd=d1[cur].dis;
		int lb=cd,ub=pd;
		for(int i=lb; i<=ub ;i++){
			yerin[cur].push_back({d[id]+i,1});
		}
	}
	if(p!=0){
		int cd=d1[id].dis;
		int pd=d1[p].dis;
		int lb=cd,ub=pd;
		for(int i=lb; i<=ub ;i++){
			upd[1].push_back({id,i});
			yerin[id].push_back({d[id]+i,-1});
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	//freopen("atlarge.in","r",stdin);
	//freopen("atlarge.out","w",stdout);
	cin >> n;
	for(int i=1; i<n ;i++){
		int u,v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,0);
	dfs5(1,0);
	upd_ans(1,0);
	solve(1);
	for(int i=1; i<=n ;i++){
		if(adj[i].size()==1) ans[i]=1;
		cout << ans[i] << '\n';
	}
}
