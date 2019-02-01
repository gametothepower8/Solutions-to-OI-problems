/*
Maintain segtree on rows. Store dp[up][down] in each node as cost
Meging can be done in O(C^2logC) using d&c optimization for dp
Cannot store answer of too small range of row or else memory would be too much.
We recalculate everytime for the range we can't branch
*/
#include "wombats.h"
#include<iostream>
using namespace std;
const int tmw=7;
const int M=5001,N=201,S=1501;
int m,n;
int dp[S][N][N];
int dp2[16][N][N];
int lc[S],rc[S];
int h[M][N],v[M][N];
void cal(int id,int st,int l,int r,int optl,int optr){
	if(l>r) return;
	int opt=0,mid=(l+r)/2;
	dp[id][st][mid]=1e9;
	for(int i=optl; i<=optr ;i++)
		if(dp[id][st][mid]>dp[lc[id]][st][i]+dp[rc[id]][i][mid])
			dp[id][st][mid]=dp[lc[id]][st][i]+dp[rc[id]][i][mid],opt=i;
	cal(id,st,l,mid-1,optl,opt);
	cal(id,st,mid+1,r,opt,optr);
}
void cal2(int id,int st,int l,int r,int optl,int optr){
	if(l>r) return;
	int opt=0,mid=(l+r)/2;
	dp2[id][st][mid]=1e9;
	for(int i=optl; i<=optr ;i++)
		if(dp2[id][st][mid]>dp2[id*2][st][i]+dp2[id*2+1][i][mid])
			dp2[id][st][mid]=dp2[id*2][st][i]+dp2[id*2+1][i][mid],opt=i;
	cal2(id,st,l,mid-1,optl,opt);
	cal2(id,st,mid+1,r,opt,optr);
}
void upd2(int id,int l,int r){
	if(l==r){
		for(int i=1; i<=n ;i++){
			dp2[id][i][i]=v[l][i];
			for(int j=i+1; j<=n ;j++)
				dp2[id][i][j]=dp2[id][i][j-1]-v[l][j-1]+v[l][j]+h[l][j-1];
			for(int j=i-1; j>=1 ;j--)
				dp2[id][i][j]=dp2[id][i][j+1]-v[l][j+1]+v[l][j]+h[l][j];
			for(int j=1+1; j<=n ;j++) dp2[id][i][j]=min(dp2[id][i][j],dp2[id][i][j-1]+h[l+1][j-1]);
			for(int j=n-1; j>=1 ;j--) dp2[id][i][j]=min(dp2[id][i][j],dp2[id][i][j+1]+h[l+1][j]);
			//cout << id << ' ' << l << ' ' << i << ": ";
			//for(int j=1; j<=n ;j++) cout << dp2[id][i][j] << ' ';
			//cout << endl;
		}
		return;
	}
	int mid=(l+r)/2;
	upd2(id*2,l,mid);upd2(id*2+1,mid+1,r);
	for(int i=1; i<=n ;i++) cal2(id,i,1,n,1,n);
}
void upd(int id,int l,int r,int x,int y){
	if((l>x || x>r) && (l>y || y>r)) return;
	if(r-l<tmw){
		upd2(1,l,r);
		for(int i=1; i<=n ;i++) for(int j=1; j<=n ;j++) dp[id][i][j]=dp2[1][i][j];
		return;
	}
	int mid=(l+r)/2;
	mid+=(tmw-mid%tmw)%tmw;
	upd(lc[id],l,mid,x,y);
	upd(rc[id],mid+1,r,x,y);
	for(int i=1; i<=n ;i++) cal(id,i,1,n,1,n);
}
int ptr=1;
void build(int id,int l,int r){
	if(r-l<tmw){
		upd2(1,l,r);
		for(int i=1; i<=n ;i++) for(int j=1; j<=n ;j++) dp[id][i][j]=dp2[1][i][j];
		return;
	}
	lc[id]=++ptr;rc[id]=++ptr;
	int mid=(l+r)/2;
	mid+=(tmw-mid%tmw)%tmw;
	build(lc[id],l,mid);build(rc[id],mid+1,r);
	for(int i=1; i<=n ;i++) cal(id,i,1,n,1,n);
}
void init(int R, int C, int H[5000][200], int V[5000][200]){
	m=R;n=C;
	for(int i=0; i<m ;i++)
		for(int j=0; j<n ;j++)
			h[i+1][j+1]=H[i][j],v[i+1][j+1]=V[i][j];
	build(1,1,m-1);
}
void changeH(int P, int Q, int W){
	int p=P+1,q=Q+1,w=W;
    h[p][q]=w;
    upd(1,1,m-1,p-1,p);
}
void changeV(int P, int Q, int W){
	int p=P+1,q=Q+1,w=W;
    v[p][q]=w;
    upd(1,1,m-1,p,p);
}
int escape(int V1, int V2){
    int p=V1+1,q=V2+1;
    return dp[1][p][q];
}
