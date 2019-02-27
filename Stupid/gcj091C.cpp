//implementation
#include<iostream>
using namespace std;
typedef double dd;
dd dp[41];
dd f[41];
dd C[41][41];
int c,n;
double solve(){
	cin >> c >> n;
	dp[c]=0;
	for(int i=c-1; i>=0 ;i--){
		dp[i]=0;
		for(int j=0; j<n ;j++){
			if(i<j || c-i<n-j) continue;
			dp[i]+=C[i][j]*C[c-i][n-j]*dp[i+n-j];
		}
		dp[i]/=C[c][n];
		dp[i]+=1;
		if(i>=n) dp[i]/=(1-C[i][n]/C[c][n]);
	}
	return dp[0];
}
int main(){
	ios::sync_with_stdio(false);
	freopen("C-large-practice.in","r",stdin);
	freopen("outfie31.txt","w",stdout);
	int t;cin >> t;
	f[0]=1;
	for(int i=1; i<=40 ;i++) f[i]=f[i-1]*i;
	for(int i=0; i<=40 ;i++){
		for(int j=0; j<=40 ;j++) C[i][j]=f[i]/f[j]/f[i-j];
	}
	for(int i=1; i<=t ;i++){
		dd ans=solve();
		printf("Case #%d: %.10lf\n",i,ans);
	}
}
