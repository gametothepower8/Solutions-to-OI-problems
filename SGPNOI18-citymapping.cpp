//reuse the idea of complexity prove of link-cut tree (similar to JOI spring camp 18 Construction of Highway). Add nodes one by one and update the tree. However, randomization has to be used to deal with constants
#include "citymapping.h"
#include<iostream>
#include<chrono>
#include<random>
#include<algorithm>
using namespace std;
typedef long long ll;
int n;
int p[2001];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int par[2001];
int lc[2001],rc[2001];
int ps[2001];
ll dis[2001];
ll d1[2001],d2[2001];
int real[2001];
int ptr=0;
void dfs(int id,int* a,int* b,int* w){
	if(lc[id]!=0){
		a[ptr]=real[id];
		b[ptr]=real[lc[id]];
		w[ptr]=dis[lc[id]]-dis[id];
		ptr++;
		dfs(lc[id],a,b,w);
	}
	if(rc[id]!=0){
		a[ptr]=real[id];
		b[ptr]=real[rc[id]];
		w[ptr]=dis[rc[id]]-dis[id];
		ptr++;
		dfs(rc[id],a,b,w);
	}
}
void find_roads(int N, int Q, int A[], int B[], int W[]) {
	n=N;
	for(int i=1; i<=2*n ;i++) lc[i]=rc[i]=ps[i]=dis[i]=d1[i]=d2[i]=real[i]=par[i]=p[i]=0;
	ptr=0;
	for(int i=1; i<=n ;i++) p[i]=i;
	for(int i=1; i<=n ;i++) swap(p[i],p[uniform_int_distribution<int>(i,n)(rng)]);
	int rt1=p[1];
	int rt2=1+(rt1==1);
	for(int i=1; i<=n ;i++){
		if(i==rt1) continue;
		d1[i]=get_distance(rt1,i);
		if(d1[rt2]>d1[i]) rt2=i;
	}
	for(int i=1; i<=n ;i++){
		if(i==rt1 || i==rt2) continue;
		d2[i]=get_distance(rt2,i);
	}
	ps[rt1]=rt1;ps[rt2]=rt2;
	real[rt1]=rt1;real[rt2]=rt2;
	for(int i=1; i<=n ;i++){
		int id=p[i];
		if(id==rt1 || id==rt2) continue;
		int cur;
		if(d1[id]<d2[id]) cur=rt1,dis[id]=d1[id];
		else cur=rt2,dis[id]=d2[id];
		bool add=true;
		while(true){
			int newi=ps[cur];//some leaf
			ll tmp=get_distance(id,newi);
			ll num=(dis[id]+dis[newi]-tmp)/2;//lca depth
			while(lc[cur]!=0 && dis[lc[cur]]<=num) cur=lc[cur];//move to lca
			if(dis[cur]<num){
				par[lc[cur]]=n+i;
				par[n+i]=cur;
				ps[n+i]=ps[cur];
				if(lc[cur]==0) ps[n+i]=n+i;
				lc[n+i]=lc[cur];
				lc[cur]=n+i;
				dis[n+i]=num;
				cur=n+i;
			}
			if(dis[cur]==dis[id]){
				real[cur]=id;
				add=false;
				break;
			}
			swap(lc[cur],rc[cur]);
			if(lc[cur]==0){
				lc[cur]=id;
				real[id]=id;
				par[id]=cur;
				ps[id]=id;
				cur=id;
				break;
			}
			ps[cur]=ps[lc[cur]];
		}
		while(cur!=rt1 && cur!=rt2){
			cur=par[cur];
			ps[cur]=ps[lc[cur]];
		}
	}
	dfs(rt1,A,B,W);
	dfs(rt2,A,B,W);
	A[ptr]=rt1;
	B[ptr]=rt2;
	W[ptr]=d1[rt2];
	return;
}
