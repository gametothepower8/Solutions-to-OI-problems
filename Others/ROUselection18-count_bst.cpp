/*
Number of BST of size N = Nth catalan number.
Count the number of possible highest node on the path.
Answer mutliply a bunch of catalan number with the count.
*/
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int iu=6e6,K=2e5+2;
const ll mod=1e9+7;
ll pw(ll x,ll y){
	if(y==0) return 1;
	if(y%2) return x*pw(x,y-1)%mod;
	ll res=pw(x,y/2);
	return res*res%mod;
}
ll f[6000001];
ll inf[6000001];
ll c[3000001];
void tmw(){
	f[0]=1;
	for(int i=1; i<=iu ;i++) f[i]=f[i-1]*i%mod;
	inf[iu]=pw(f[iu],mod-2);
	for(int i=iu-1; i>=0 ;i--) inf[i]=inf[i+1]*(i+1)%mod;
	for(int i=0; i<=iu/2 ;i++) c[i]=f[i*2]*inf[i]%mod*inf[i+1]%mod;
}
int n,k;
int a[K];
int maxp[K],maxs[K];
int minp[K],mins[K];
int cp[K],cs[K];
void solve(){
	cin >> n >> k;
	if(k==0){
		cout << c[n] << '\n';
		return;
	}
	maxp[0]=maxs[k+1]=0;
	minp[0]=mins[k+1]=n+1;
	cp[0]=cs[k+1]=true;
	for(int i=1; i<=k ;i++){
		cin >> a[i];
		cp[i]=cp[i-1]&(a[i]>maxp[i-1] || a[i]<minp[i-1]);
		maxp[i]=max(maxp[i-1],a[i]);
		minp[i]=min(minp[i-1],a[i]);
	}
	for(int i=k; i>=1 ;i--){
		cs[i]=cs[i+1]&(a[i]>maxs[i+1] || a[i]<mins[i+1]);
		maxs[i]=max(maxs[i+1],a[i]);
		mins[i]=min(mins[i+1],a[i]);
	}
	int can=0;
	for(int i=1; i<=k ;i++){
		if(cp[i-1] && cs[i+1] && ((a[i]>maxp[i-1] && a[i]<mins[i+1]) || (a[i]<minp[i-1] && a[i]>maxs[i+1]))) can++;
	}
	sort(a+1,a+k+1);
	ll tzu=can*c[n-a[k]+a[1]]%mod;
	for(int i=2; i<=k ;i++){
		tzu=tzu*c[a[i]-a[i-1]-1]%mod;
	}
	cout << tzu << '\n';
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);
	tmw();
	int t;cin >> t;while(t--) solve();
}
