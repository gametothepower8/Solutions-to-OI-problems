//define e(x) as expected value where x is the longest prefix which match suffix of current state. all e(x) can be written in terms of e(0). ans(x) is e(0)-e(x)
#include<iostream>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
const int M=1e6+1;
int m;
int n;
int a[M];
int f[M];
ll x[M],y[M];
ll e[M];
ll pw(ll x,ll y){
	if(y==0) return 1;
	if(y%2) return x*pw(x,y-1)%mod;
	ll res=pw(x,y/2);
	return res*res%mod;
}
int main(){
	ios::sync_with_stdio(false);
	cin >> n >> m;
	f[0]=-1;
	for(int i=1; i<=m ;i++){
		cin >> a[i];
		int cur=f[i-1];
		while(cur>=0 && a[cur+1]!=a[i]) cur=f[cur];
		f[i]=cur+1;
	}
	x[0]=1;y[0]=0;
	x[1]=1;y[1]=n;
	for(int i=2; i<=m ;i++){
		x[i]=(n*x[i-1]+(mod-n)*x[f[i-1]]+x[f[i]])%mod;
		y[i]=(n*y[i-1]+(mod-n)*y[f[i-1]]+y[f[i]])%mod;
	}
	e[0]=y[n]*pw(x[n],mod-2)%mod;
	for(int i=1; i<=m ;i++){
		e[i]=(x[i]*e[0]+mod-y[i])%mod;
		cout << (e[0]-e[i]+mod)%mod << '\n';
	}
}
