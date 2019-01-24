#include<iostream>
#include<set>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long ll;
#define fi first
#define se second
const int N=3e5+1,Q=3e5+1,K=3e5+1;
int n,k,q;
struct pt{
	ll x,tp,t;//<0: add, =0: qry, >0: rmv
};
bool operator<(pt x,pt y){
	return x.t<y.t;
}
pt a[2*N];
multiset<ll>s[K];
int mptr=0;
vector<int>bin[3*N];
map<pair<ll,ll>,int>mp;//should clear after inserting all stores :)
struct upd{
	ll x,l,r,pos;
};
bool operator<(upd x,upd y){
	return x.pos<y.pos;
}
vector<upd>pve,nve;
string f(ll x){
	string ret;
	if(x<=-1e8) return "-inf";
	if(x>=1e8) return "inf";
	if(x==0) ret+='0';
	while(x>0){
		char c=x%10+48;
		x/=10;
		ret=c+ret;
	}
	return ret;
}
void add(ll xl,ll xr,ll t){
	int num=mp[{xl,xr}];
	if(num==0) mp[{xl,xr}]=num=++mptr;
	bin[num].push_back(t);
}
void rmv(ll xl,ll xr,ll t){
	int cur=mp[{xl,xr}];
	ll p=bin[cur].back();
	bin[cur].pop_back();
	if(p==t) return;t--;
	upd pl={-xl,p,t,-(xl+xr)/2};
	upd nl={xr,p,t,(xl+xr+1)/2};
	pve.push_back(pl);nve.push_back(nl);
}
ll ans[Q];
pair<pair<ll,ll>,int>b[Q];
pair<ll,ll>c[Q];
ll st[1<<20];
void init(int id,int l,int r){
	st[id]=-1e9;
	if(l==r) return;
	int mid=(l+r)/2;
	init(id*2,l,mid);init(id*2+1,mid+1,r);
}
void upd(int id,int l,int r,int ql,int qr,ll v){
	if(st[id]>=v) return;
	if(l>qr || r<ql) return;
	if(ql<=l && r<=qr){
		st[id]=max(st[id],v);
		return;
	}
	int mid=(l+r)/2;
	upd(id*2,l,mid,ql,qr,v);
	upd(id*2+1,mid+1,r,ql,qr,v);
}
ll qry(int id,int l,int r,int p){
	if(l==r) return st[id];
	int mid=(l+r)/2;
	if(p<=mid) return max(st[id],qry(id*2,l,mid,p));
	else return max(st[id],qry(id*2+1,mid+1,r,p));
}
void in(int& x){
	char c=getchar();
	while(c<48 || c>57) c=getchar();
	x=0;
	while(c>=48 && c<=57){
		x=x*10+c-48;
		c=getchar();
	}
}
void in(ll& x){
	char c=getchar();
	while(c<48 || c>57) c=getchar();
	x=0;
	while(c>=48 && c<=57){
		x=x*10+c-48;
		c=getchar();
	}
}
int main(){
	ios::sync_with_stdio(false);
	in(n);in(k);in(q);
	for(int i=1; i<=n ;i++){
		ll x,tp,u,v;in(x);in(tp);in(u);in(v);
		a[i*2-1]={x,-tp,u};
		a[i*2]={x,tp,v+1};
	}
	mptr=1;
	for(int i=1; i<=k ;i++){
		s[i].insert(-1e9);
		s[i].insert(1e9);
		mp[{(ll)-1e9,(ll)1e9}]=mptr;
		bin[mptr].push_back(1);
	}
	sort(a+1,a+2*n+1);
	for(int i=1; i<=2*n ;i++){
		ll x=a[i].x,tp=a[i].tp,t=a[i].t;
		if(tp<0){
			tp=-tp;
			auto it=s[tp].lower_bound(x);
			auto it2=it;--it2;
			rmv(*it2,*it,t);add(*it2,x,t);add(x,*it,t);
			s[tp].insert(x);
		}
		else{
			auto it3=s[tp].lower_bound(x);
			auto it=it3;++it;
			auto it2=it3;--it2;
			rmv(*it2,x,t);rmv(x,*it,t);add(*it2,*it,t);
			s[tp].erase(it3);
		}
	}
	for(int i=1; i<=k ;i++) rmv(-1e9,1e9,1e9);
	sort(nve.begin(),nve.end());
	sort(pve.begin(),pve.end());
	for(int i=1; i<=q ;i++){
		in(b[i].fi.fi);in(b[i].fi.se);
		b[i].se=i;
		c[i]={b[i].fi.se,i};
	}
	sort(c+1,c+q+1);
	for(int i=1; i<=q ;i++) b[c[i].se].fi.se=i;
	sort(b+1,b+q+1);
	int ptr=0;
	init(1,1,q);
	for(int i=1; i<=q ;i++){
		while(ptr<nve.size() && nve[ptr].pos<=b[i].fi.fi){
			int l=lower_bound(c+1,c+q+1,(pair<ll,ll>){nve[ptr].l,0LL})-c;
			int r=lower_bound(c+1,c+q+1,(pair<ll,ll>){nve[ptr].r+1,0LL})-c-1;
			if(l<=r) upd(1,1,q,l,r,nve[ptr].x);
			ptr++;
		}
		ans[b[i].se]=max(ans[b[i].se],qry(1,1,q,b[i].fi.se)-b[i].fi.fi);
	}
	init(1,1,q);
	reverse(b+1,b+q+1);
	for(int i=1; i<=q ;i++) b[i].fi.fi=-b[i].fi.fi;
	ptr=0;
	for(int i=1; i<=q ;i++){
		while(ptr<pve.size() && pve[ptr].pos<=b[i].fi.fi){
			int l=lower_bound(c+1,c+q+1,(pair<ll,ll>){pve[ptr].l,0LL})-c;
			int r=lower_bound(c+1,c+q+1,(pair<ll,ll>){pve[ptr].r+1,0LL})-c-1;
			if(l<=r) upd(1,1,q,l,r,pve[ptr].x);
			ptr++;
		}
		ans[b[i].se]=max(ans[b[i].se],qry(1,1,q,b[i].fi.se)-b[i].fi.fi);
	}
	for(int i=1; i<=q ;i++){
		if(ans[i]>=(ll)1e8) cout << "-1\n";
		else cout << ans[i] << '\n';
	}
}
