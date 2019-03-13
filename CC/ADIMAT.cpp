/*
assume n<=m. we realise that n<=23
Each transformation can be represented by two permutations for [1,n] and [1,m] respectively.
Consider Burnside lemma. We find out that the number of ways to partition n identical elements into identical sets are very small (around 1300)
We exhuast all possible ways to do that, and run a dp to calculate the sum by making use of the fact that
total number of cycles = 
for cycle A in permutation of [1,n]
for cycle B in permutation of [1,m]
count+=gcd(|A|,|B|)
Rest is some details of handling nCr and factorials etc
*/
#include<iostream>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
const int k=2;//soooo sad
int n,m;
int g[551][551];
ll f[551],inf[551],inv[551];
ll pk[551];
ll ans=0;
ll pw(ll x,ll y){
	if(y==0) return 1;
	if(y%2) return x*pw(x,y-1)%mod;
	ll res=pw(x,y/2);
	return res*res%mod;
}
void tzuyu(){
	f[0]=1;inf[0]=1;
	pk[0]=1;
	for(int i=1; i<=n*m ;i++){
		pk[i]=pk[i-1]*k%mod;
		g[i][i]=i;
		for(int j=i+1; j<=n*m ;j++) g[i][j]=g[j][i]=g[i][j-i];
		f[i]=f[i-1]*i%mod;inf[i]=pw(f[i],mod-2);inv[i]=f[i-1]*inf[i]%mod;
	}
}
int t[24];
int numb[551];
ll dp[2][551];//taken -> sum k^cycle count
ll solve(){
	for(int i=0; i<=m ;i++) dp[0][i]=0;
	dp[0][0]=1;
	for(int gs=1; gs<=m ;gs++){
		int add=0;
		for(int j=1; j<=n ;j++) add+=t[j]*g[gs][j];
		for(int j=0; j<=m ;j++) dp[1][j]=0;
		for(int rem=0; rem<=m ;rem++){
			ll nw=1;
			for(int i=0; i*gs<=rem ;i++){
				if(i>0) nw=nw*f[rem-(i-1)*gs]%mod*inf[rem-i*gs]%mod*inv[gs]%mod*inv[i]%mod*pk[add]%mod;
				//cout << gs << ' ' << rem << ' ' << i << ' ' << m-rem+i*gs << ' ' << m-rem << ' ' << nw << endl;
				dp[1][m-rem+i*gs]=(dp[1][m-rem+i*gs]+dp[0][m-rem]*nw)%mod;
			}
		}
		for(int j=0; j<=m ;j++) dp[0][j]=dp[1][j];
	}
	return dp[0][m];
}
void explode(int rem,int gs,ll way){
	if(gs==0){
		if(rem!=0) return;
		ans=(ans+way*solve())%mod;
		return;
	}
	ll nw=way;
	for(int i=0; i*gs<=rem ;i++){
		t[gs]=i;
		if(i>0) nw=nw*f[rem-(i-1)*gs]%mod*inf[rem-i*gs]%mod*inv[gs]%mod*inv[i]%mod;
		explode(rem-i*gs,gs-1,nw);
	}
	t[gs]=0;
}
int main(){
	ios::sync_with_stdio(false);
	cin >> n >> m;if(n>m) swap(n,m); tzuyu();
	explode(n,n,1);
	ans=ans*inf[n]%mod*inf[m]%mod;
	cout << ans << endl;
}
