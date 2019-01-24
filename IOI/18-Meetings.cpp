/*uh, https://ioi2018.jp/wp-content/tasks/contest2/meetings-review.pdf
Used segtree instead of some weird small-to-large, because its too complicated for me
Might not pass in official contest, as the large constraints seems to be set to block segtree sols
*/
#include "meetings.h"
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
typedef long long ll;
bool debug=false;
const int N=750001,Q=750001;
int n,q;
ll h[N];
int ql[Q],qr[Q];
int rt=0;
int lc[N],rc[N];
int l[N],r[N];
int rmq[Q];
//build tree + rmq
vector<int>qp[N];
stack<int>s;
int par[N];
bool col[N];
int find(int x){
	if(par[x]!=x) par[x]=find(par[x]);
	return par[x];
}
void join(int x,int y){
	par[find(x)]=find(y);
}
void dfs(int id){
	l[id]=r[id]=id;
	par[id]=id;
	if(lc[id]!=0){
		dfs(lc[id]);
		l[id]=l[lc[id]];
		join(lc[id],id);
	}
	if(rc[id]!=0){
		dfs(rc[id]);
		r[id]=r[rc[id]];
		join(rc[id],id);
	}
	col[id]=true;
	for(auto cur:qp[id]){
		int newi=ql[cur]^qr[cur]^id;
		if(col[newi]) rmq[cur]=find(newi);
	}
}
//segtree
const int ts=1<<21;
bool llz[ts],rlz[ts];
ll tlonl[ts],tronl[ts];
ll tlc[ts],tlx[ts],trc[ts],trx[ts],tla[ts],tra[ts];
bool *lz;
ll *c,*x,*onl,*add;
void setl(){lz=llz,c=tlc,x=tlx,onl=tlonl;add=tla;};
void setr(){lz=rlz,c=trc,x=trx,onl=tronl;add=tra;};
void push(int id,int l,int r){
	if(add[id]>0){
		if(lz[id*2]) c[id*2]+=add[id];
		else add[id*2]+=add[id];
		if(lz[id*2+1]) c[id*2+1]+=add[id];
		else add[id*2+1]+=add[id];
		onl[id*2]+=add[id];
		onl[id*2+1]+=add[id];
		add[id]=0;
		return;
	}
	if(!lz[id]) return;
	int mid=(l+r)/2;
	c[id*2]=c[id];
	c[id*2+1]=c[id]+(mid-l+1)*x[id];
	x[id*2]=x[id*2+1]=x[id];
	onl[id*2]=c[id*2],onl[id*2+1]=c[id*2+1];
	add[id*2]=add[id*2+1]=0;
	lz[id*2]=lz[id*2+1]=true;
	lz[id]=false;
}
void pull(int id,int l,int r){
	onl[id]=onl[id*2];
}
void upd(int id,int l,int r,int ql,int qr,ll x0,ll x1){
	if(l>qr || r<ql) return;
	if(ql<=l && r<=qr){
		lz[id]=true;
		onl[id]=c[id]=x0+l*x1;
		add[id]=0;
		x[id]=x1;
		return;
	}
	push(id,l,r);
	int mid=(l+r)/2;
	upd(id*2,l,mid,ql,qr,x0,x1);
	upd(id*2+1,mid+1,r,ql,qr,x0,x1);
	pull(id,l,r);
}
void radd(int id,int l,int r,int ql,int qr,ll x){
	if(l>qr || r<ql) return;
	if(ql<=l && r<=qr){
		if(lz[id]) c[id]+=x;
		else add[id]+=x;
		onl[id]+=x;
		return;
	}
	push(id,l,r);
	int mid=(l+r)/2;
	radd(id*2,l,mid,ql,qr,x);
	radd(id*2+1,mid+1,r,ql,qr,x);
	pull(id,l,r);
}
ll getv(int id,int l,int r,int p){
	if(l==p) return onl[id];
	push(id,l,r);
	int mid=(l+r)/2;
	if(p<=mid) return getv(id*2,l,mid,p);
	else return getv(id*2+1,mid+1,r,p);
}
int findl(int id,int l,int r,int ql,int qr,ll x0,ll x1){
	if(l==r) return l+1;
	push(id,l,r);
	int mid=(l+r)/2;
	int cur=mid+1;
	if(cur>qr) return findl(id*2,l,mid,ql,qr,x0,x1);
	else if(cur<ql) return findl(id*2+1,cur,r,ql,qr,x0,x1);
	ll val=x0+x1*cur;
	if(val<=onl[id*2+1]) return findl(id*2,l,mid,ql,qr,x0,x1);
	else return findl(id*2+1,cur,r,ql,qr,x0,x1);
}
int findr(int id,int l,int r,int ql,int qr,ll x0,ll x1){
	if(l==r) return l;
	push(id,l,r);
	int mid=(l+r)/2;
	int cur=mid+1;
	if(cur>qr) return findr(id*2,l,mid,ql,qr,x0,x1);
	else if(cur<ql) return findr(id*2+1,cur,r,ql,qr,x0,x1);
	ll val=x0+x1*cur;
	if(val>onl[id*2+1]) return findr(id*2,l,mid,ql,qr,x0,x1);
	else return findr(id*2+1,cur,r,ql,qr,x0,x1);
}
//solve
vector<int>get[N];
ll ans[Q],ans2[Q];
ll fk(ll temp){
	if(temp>=(ll)1e18) return -1;
	else return temp;
}
int rnd;
void solve(int id){
	if(lc[id]!=0) solve(lc[id]);
	if(rc[id]!=0) solve(rc[id]);
	for(auto cur:get[id]){
		ans[cur]=h[id]*(qr[cur]-ql[cur]+1);//x==id
		if(qr[cur]!=id){//x<id
			setl();
			ans[cur]=min(ans[cur],h[id]*(id-ql[cur]+1)+getv(1,0,n,qr[cur]));
		}
		if(ql[cur]!=id){//x>id
			setr();
			ans[cur]=min(ans[cur],h[id]*(qr[cur]-id+1)+getv(1,0,n,ql[cur]));
		}
	}
	ll val,x0,x1;
	setl();
	if(l[id]!=id) val=getv(1,0,n,id-1)+h[id];
	else val=h[id];
	x1=h[id];
	x0=val-id*x1;
	radd(1,0,n,id,r[id],h[id]*(id-l[id]+1));
	int pos=findr(1,0,n,id,r[id],x0,x1);
	upd(1,0,n,id,pos,x0,x1);
	setr();
	if(r[id]!=id) val=getv(1,0,n,id+1)+h[id];
	else val=h[id];
	x1=-h[id];
	x0=val-id*x1;
	radd(1,0,n,l[id],id,h[id]*(r[id]-id+1));
	pos=findl(1,0,n,l[id],id,x0,x1);
	upd(1,0,n,pos,id,x0,x1);
	
}
vector<ll> minimum_costs(vector<int> H,vector<int> L,vector<int> R) {
	n=H.size(),q=L.size();
	for(int i=1; i<=n ;i++) h[i]=H[i-1];
	for(int i=1; i<=q ;i++) ql[i]=L[i-1]+1,qr[i]=R[i-1]+1;
	for(int i=1; i<=n ;i++){
		int last=0;
		while(!s.empty() && h[s.top()]<h[i]){
			last=s.top();
			s.pop();
		}
		if(!s.empty()) rc[s.top()]=i;
		else rt=i;
		lc[i]=last;
		s.push(i);
	}
	for(int i=1; i<=q ;i++){
		qp[ql[i]].push_back(i);
		qp[qr[i]].push_back(i);
	}
	dfs(rt);
	for(int i=1; i<=q ;i++) get[rmq[i]].push_back(i);
	setl();
	upd(1,0,n,1,n,1e18,0);
	setr();
	upd(1,0,n,1,n,1e18,0);
	solve(rt);
	vector<ll>ret(q);
	for(int i=1; i<=q ;i++) ret[i-1]=ans[i];
	return ret;
}
