//Basic idea is to add buildings one by one and store the current form as an unordered list of chains. 
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
int n,l;
ll dp[2][1001][101][4];
int a[101];
int main(){
    ios::sync_with_stdio(false);
    cin >> n >> l;
    if(n==1){
    	cout << "1\n";
    	return 0;
	}
    for(int i=1; i<=n ;i++) cin >> a[i];
    sort(a+1,a+n+1);
    dp[0][0][0][0]=1;
    for(int i=1; i<=n ;i++){
    	int c=i&1;
    	int p=c^1;
    	for(int j=0; j<=l ;j++)
    		for(int k=0; k<=i ;k++)
    			for(int r=0; r<=2 ;r++)
    				dp[c][j][k][r]=0;
    	for(int j=0; j<=l ;j++)
    		for(int k=0; k<i ;k++)
    			for(int r=0; r<=2 ;r++){
    				int nj=j+(a[i]-a[i-1])*(2*k-r);
	    			if(nj>l || dp[p][j][k][r]==0) continue;
	    			//new set
	    			dp[c][nj][k+1][r]=(dp[c][nj][k+1][r]+dp[p][j][k][r])%mod;
	    			dp[c][nj][k+1][r+1]=(dp[c][nj][k+1][r+1]+dp[p][j][k][r]*(2-r))%mod;
	    			//stick in ends
	    			dp[c][nj][k][r]=(dp[c][nj][k][r]+dp[p][j][k][r]*(2*k-r))%mod;
	    			dp[c][nj][k][r+1]=(dp[c][nj][k][r+1]+dp[p][j][k][r]*(k-r+(i==n && r==1 && k==1))*(2-r))%mod;
	    			//join
	    			int w=r*(k-r)+(k-r)*(k-r-1)+(i==n && r==2 && k==2);
	    			dp[c][nj][k-1][r]=(dp[c][nj][k-1][r]+dp[p][j][k][r]*w)%mod;
				}
	}
	ll ans=0;
	for(int i=0; i<=l ;i++) ans=(ans+dp[n&1][i][1][2])%mod;
	cout << ans << '\n';
}
