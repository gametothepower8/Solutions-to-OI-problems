/*
Do both sides seperately. Make some observation like "if i is better than j here, i will be better than j forever". Maintain monotone queue and compute values using persistent BIT.
*/
#include<cstdio>
#include"holiday.h"
#include"holiday.h"
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long ll;
#define fi first
#define se second
int m,boss;
vector<pair<int,pair<ll,int> > >hbit[100001];
pair<ll,int>bit[100001];
ll a[100001];
pair<ll,int>b[100001];
int p[100001];
int st;
ll ans1[300001],ans2[300001],ans3[300001],ans4[300001];
vector<pair<int,int> >good;
ll sch(int v){
	ll res=0;
	int fnd=0;
	for(int i=16; i>=0 ;i--){
		if((fnd|(1<<i))<=m && bit[fnd|(1<<i)].se<=v){
			fnd|=(1<<i);
			v-=bit[fnd].se;
			res+=bit[fnd].fi;
		}
	}
	return res;
}
int getc(int x,int y,int d,int dx){
	int cur=0;
	int res=d*abs(x-st);
	ll val=0;
	for(int i=16; i>=0 ;i--){
		if((cur|(1<<i))>m) continue;
		auto tmp=*--lower_bound(hbit[cur|(1<<i)].begin(),hbit[cur|(1<<i)].end(),make_pair(x*dx+1,make_pair(0LL,0)));
		int newi=res+tmp.se.se;
		ll newv=val+tmp.se.fi;
		if(newi<d*abs(y-st)){cur|=(1<<i);res=newi;val=newv;continue;}
		ll myv=sch(newi-d*abs(y-st));
		if(myv<newv){cur|=(1<<i);res=newi;val=newv;}
	}
	return res+1;
}
void upd(int id,int pos,ll v,int dx){
	for(int i=pos; i<=m ;i+=i&-i){
		bit[i]={bit[i].fi+v,bit[i].se+1};
		hbit[i].push_back({id*dx,bit[i]});
	}
}
void add(int id,int d,int dx){
	upd(id,p[id],a[id],dx);
	if(good.empty()){
		good.push_back({id,0});
		return;
	}
	int last=getc(good.back().fi,id,d,dx);
	while(good.size()>1 && good.back().se>=last){
		good.pop_back();
		last=getc(good.back().fi,id,d,dx);
	}
	good.push_back({id,last}); 
}
bool debug=false;
void cal(ll* ans,int d,int en,int s,int e,int dx){
	for(int i=1; i<=m ;i++){
		hbit[i].clear();
		hbit[i].push_back({st*dx,{0LL,0}});
		bit[i]={0LL,0};
	}
	for(int i=s; i!=e+dx ;i+=dx) add(i,d,dx);
	for(int i=1; i<=m ;i++){
		hbit[i].clear();
		hbit[i].push_back({st*dx,{0LL,0}});
		bit[i]={0LL,0};
	}
	if(good.empty()) return;
	int ptr=-1;
	int cur=s-dx;
	for(int i=0; i<=en ;i++){
		if(ptr<(int)good.size()-1 && good[ptr+1].se==i){
			ptr++;
			while(cur!=good[ptr].fi){
				cur+=dx;
				upd(cur,p[cur],a[cur],dx);
			}
		}
		ans[i]=sch(i-abs(cur-st)*d);
		if(i!=0) ans[i]=max(ans[i],ans[i-1]);
	}
	good.clear();
}
ll findMaxAttraction(int n, int start, int d, int attraction[]) {
	m=n;boss=d;
    st=start+1;
    for(int i=1; i<=n ;i++){
    	a[i]=attraction[i-1];
    	b[i]={a[i],i};
	}
    sort(b+1,b+n+1);
    for(int i=1; i<=n ;i++) p[b[i].se]=n+1-i;
    cal(ans1,2,d,st,n,1);
    cal(ans2,1,d,st-1,1,-1);
    cal(ans3,2,d,st-1,1,-1);
    cal(ans4,1,d,st,n,1);
    ll fans=0;
    for(int i=0; i<=d ;i++){
    	fans=max(fans,ans1[i]+ans2[d-i]);
    	fans=max(fans,ans3[i]+ans4[d-i]);
	}
    return fans;
}
