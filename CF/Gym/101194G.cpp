/*
Build kruskal tree(not sure about name actually) and do small to large to find out answer after each merge.
Build persistent segtree to store answer and query.
Prepare to stress test.
*/
#include<iostream>
#include<algorithm>
using namespace std;
typedef pair<int,pair<int,int> > edge;
#define fi first
#define se second
int n,m,q;
int c[100001];
edge e[200001];
int par[300001];//dsu
int lc[300001],rc[300001];
int sz[300001];//tree
int nid[300001];
int lb[300001],rb[300001];
int ans[300001];
int ptr=0;
int find(int x){
	if(par[x]!=x) par[x]=find(par[x]);
	return par[x];
}
void join(int id,int x,int y){
	x=find(x);y=find(y);
	if(x==y) return;
	par[x]=par[y]=par[id]=id;
	lc[id]=x,rc[id]=y;
}
void dfs(int id){
	if(lc[id]==0) lb[id]=rb[id]=nid[id]=++ptr;
	else dfs(lc[id]);
	if(rc[id]!=0) dfs(rc[id]);
	sz[id]=1+sz[lc[id]]+sz[rc[id]];
	if(lc[id]!=0) lb[id]=lb[lc[id]],rb[id]=rb[rc[id]];
	if(sz[lc[id]]<sz[rc[id]]) swap(lc[id],rc[id]);
}
int f[100001];
int cp=0;
int pl[300001];
pair<int,int>maxi;
void addf(int cl){
	pl[++cp]=cl;
	f[cl]++;
	maxi=max(maxi,{f[cl],-cl});
}
void dfs2(int id,int k){//0 = cal, not put, 1 = cal, put, 2 = not cal,put
	if(rc[id]!=0 && k!=2) dfs2(rc[id],0);
	if(lc[id]!=0) dfs2(lc[id],1+(k==2));
	if(rc[id]!=0) dfs2(rc[id],2);
	if(lc[id]==0) addf(c[id]);
	if(k!=2) ans[id]=-maxi.se;
	if(k!=0) return;
	for(int i=1; i<=cp ;i++) f[pl[i]]=0;
	maxi={0,0};cp=0;
}
int rt[300001];
const int ts=6e6;
int tsz=0;
pair<int,int>tmw[ts];
int tlc[ts],trc[ts];
int upd(int id,int l,int r,int ql,int qr,pair<int,int> x){
	if(l>qr || r<ql) return id;
	if(ql<=l && r<=qr){
		int nw=++tsz;
		tmw[nw]=max(tmw[id],x);
		tlc[nw]=tlc[id],trc[nw]=trc[id];
		return nw;
	}
	int mid=(l+r)/2;
	int clc=upd(tlc[id],l,mid,ql,qr,x);
	int crc=upd(trc[id],mid+1,r,ql,qr,x);
	int nw=++tsz;
	tmw[nw]=tmw[id];
	tlc[nw]=clc,trc[nw]=crc;
	return nw;
}
void init(){
	tsz=1;tmw[1]={0,0},tlc[1]=trc[1]=0;
	maxi={0,0};
	ptr=0;
	for(int i=1; i<=n+m ;i++){
		par[i]=lc[i]=rc[i]=0;
	}
	for(int i=1; i<=n ;i++){
		par[i]=i;
	}
}
pair<int,int> qry(int id,int l,int r,int pos){
	if(l==r) return tmw[id];
	int mid=(l+r)/2;
	if(pos<=mid) return max(tmw[id],qry(tlc[id],l,mid,pos));
	else return max(tmw[id],qry(trc[id],mid+1,r,pos)); 
} 
void solve(){
	cin >> n >> m;
	for(int i=1; i<=n ;i++) cin >> c[i];
	for(int i=1; i<=m ;i++){
		cin >> e[i].se.fi >> e[i].se.se >> e[i].fi;
	}
	sort(e+1,e+m+1);
	init();
	for(int i=1; i<=m ;i++){
		join(n+i,e[i].se.fi,e[i].se.se);
	}
	for(int i=1; i<=n+m ;i++){
		if(par[i]==i){//exist & root
			dfs(i);dfs2(i,0);
		}
	}
	rt[0]=1;
	for(int i=1; i<=n ;i++){
		rt[0]=upd(rt[0],1,n,lb[i],rb[i],{i,ans[i]});
	}
	for(int i=n+1; i<=n+m ;i++){
		rt[i-n]=rt[i-n-1];
		if(par[i]!=0) rt[i-n]=upd(rt[i-n],1,n,lb[i],rb[i],{i,ans[i]});
	}
	cin >> q;
	int ans=0;
	for(int i=1; i<=q ;i++){
		int x,w;
		cin >> x >> w;
		x^=ans;w^=ans;
		w=lower_bound(e+1,e+m+1,make_pair(w+1,make_pair(0,0)))-e-1;
		ans=qry(rt[w],1,n,nid[x]).se;
		cout << ans << '\n';
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);
	int t;cin >> t;
	for(int i=1; i<=t ;i++){
		cout << "Case #" << i << ":\n";
		solve();
	}
}
