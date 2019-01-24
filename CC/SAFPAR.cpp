//same to https://codeforces.com/blog/entry/60982/#comment-454544, but i used segtree with extra log instead of simple data structures
#include<iostream>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
const int N=5e5+1;
int n;
int a[N];
int f[N];
int lc[N],rc[N];
int rt=-1;
int l[N],r[N];
deque<int>qmin;
stack<int>s;
vector<int>spc[N];
int dead=0;
void dfs(int id){
	l[id]=r[id]=id;
	if(lc[id]!=0){
		dfs(lc[id]);
		l[id]=l[lc[id]];
	}
	if(rc[id]!=0){
		dfs(rc[id]);
		r[id]=r[rc[id]];
	}
}
ll sum[1<<20],lazy[1<<20];
void push(int id,int l,int r){
	int mid=(l+r)/2;
	sum[id*2]+=lazy[id]*(mid-l+1);
	sum[id*2]%=mod;
	sum[id*2+1]+=lazy[id]*(r-mid);
	sum[id*2+1]%=mod;
	lazy[id*2]+=lazy[id];
	lazy[id*2+1]+=lazy[id];
	if(lazy[id*2]>=mod) lazy[id*2]-=mod;
	if(lazy[id*2+1]>=mod) lazy[id*2+1]-=mod;
	lazy[id]=0;
}
void upd(int id,int l,int r,int ql,int qr,ll v){
	if(ql>r || qr<l) return;
	if(ql<=l && r<=qr){
		lazy[id]+=v;
		if(lazy[id]>=mod) lazy[id]-=mod;
		sum[id]+=v*(r-l+1);
		sum[id]%=mod;
		return;
	}
	push(id,l,r);
	int mid=(l+r)/2;
	upd(id*2,l,mid,ql,qr,v);
	upd(id*2+1,mid+1,r,ql,qr,v);
	sum[id]=sum[id*2]+sum[id*2+1];
	if(sum[id]>=mod) sum[id]-=mod;
}
ll qry(int id,int l,int r,int ql,int qr){
	if(ql>r || qr<l) return 0;
	if(ql<=l && r<=qr) return sum[id];
	push(id,l,r);
	int mid=(l+r)/2;
	ll sm=qry(id*2,l,mid,ql,qr)+qry(id*2+1,mid+1,r,ql,qr);
	if(sm>=mod) sm-=mod;
	return sm;
}
int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i=1; i<=n ;i++){
		cin >> a[i];
		f[i]=f[i-1];
		while(!qmin.empty() && a[qmin.back()]>a[i]) qmin.pop_back();
		qmin.push_back(i);
		while(f[i]<=i && a[qmin.front()]<=i-f[i]+1){
			if(qmin.front()==f[i]) qmin.pop_front();
			f[i]++;
		}
		int last=0;
		while(!s.empty() && a[s.top()]<a[i]){
			last=s.top();
			s.pop();
		}
		if(!s.empty()) rc[s.top()]=i;
		else rt=i;
		lc[i]=last;
		s.push(i);
	}
	dfs(rt);
	upd(1,0,n,0,0,1);
	for(int i=1; i<=n ;i++){
		//handle updates of [l[i],i] to [i,r[i]]
		while(dead<r[i] && f[dead+1]<=i){
			dead++;
			if(dead<i) continue;
			ll val=0;
			if(max(l[i]-1,dead-a[i])<=f[dead]-2) val=qry(1,0,n,max(l[i]-1,dead-a[i]),f[dead]-2);
			if(val!=0) upd(1,0,n,dead,dead,val);
		}
		if(r[i]-i<=i-l[i]){//right child is smaller
			for(int j=dead+1; j<=r[i] ;j++){
				ll val=0;
				if(max(l[i]-1,j-a[i])<=i-1) val=qry(1,0,n,max(l[i]-1,j-a[i]),i-1);
				if(val!=0) upd(1,0,n,j,j,val);
			}
		}
		else{
			int yerin=min(l[i]+a[i]-1,r[i]);
			if(dead+1<=yerin && yerin>=i){
				ll val=qry(1,0,n,l[i]-1,i-1);
				if(val!=0) upd(1,0,n,dead+1,yerin,val);
			}
			for(int j=l[i]+1; j<=i ;j++){
				ll val=0;
				yerin++;
				if(dead>=yerin) continue;
				if(yerin<=r[i] && yerin>=i) val=qry(1,0,n,j-1,i-1);
				if(val!=0) upd(1,0,n,yerin,yerin,val);
			}
		}
	}
	cout << qry(1,0,n,n,n) << endl;
}
