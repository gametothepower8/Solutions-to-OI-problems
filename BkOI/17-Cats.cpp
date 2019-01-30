/*
Consider the subsequence consisting of elements that doesnt move
Handle edge cases (no 0,1,or 2)
If both 0,1 exists, we can move other 0 next to some 0 in the sequence, and similar for 1
We can formulate dp:
- for prefix i
- where j 2s are needed for the subsequence to be valid (including 2s that doesnt move),
- k is the last element
- l is the bitmask on whether 0 and 1 exists in the sequence
- use rolling
Otherwise, we move all 0 or all 1
- we check whether we have to move another 2
*/
#include<iostream>
using namespace std;
int n;
int a[5001];//Nm8t6g2u
int dp[2][5001][3][4];
int c[3];
int d[2];
int f[3],e[3];
void solve(){
	cin >> n;
	int c2=0;
	c[0]=c[1]=c[2]=0;
	d[0]=d[1]=1;
	f[0]=f[1]=f[2]=1e9;
	e[0]=e[1]=e[2]=0;
	for(int i=1; i<=n ;i++){
		cin >> a[i]; c2+=(a[i]==2);c[a[i]]++;
		f[a[i]]=min(f[a[i]],i);e[a[i]]=i;
		for(int p=0; p<3 ;p++) for(int q=0; q<4 ;q++) dp[0][i][p][q]=-1e9;
	}
	if(c[0]==0 || c[1]==0){
		cout << "0\n";return;
	}
	if(c[2]==0){
		cout << "-1\n";return;
	}
	if(f[0]>f[2] || e[0]<e[2]) d[1]=0;
	if(f[1]>f[2] || e[1]<e[2]) d[0]=0;
	for(int p=0; p<3 ;p++) for(int q=0; q<4 ;q++) dp[0][0][p][q]=-1e9;
	dp[0][0][2][0]=0;
	for(int i=1; i<=n ;i++){
		int c=i&1;
		int p=c^1;
		for(int j=0; j<=n ;j++) for(int p=0; p<3 ;p++) for(int q=0; q<4 ;q++) dp[c][j][p][q]=-1e9;
		for(int j=0; j<=i ;j++){
			for(int k=0; k<3 ;k++){
				for(int l=0; l<4 ;l++){
					dp[c][j][k][l]=max(dp[c][j][k][l],dp[p][j][k][l]);
					int nj=j+(a[i]==2 || k+a[i]==1),nk=a[i],nl=(l|(1<<a[i]))&3;
					dp[c][nj][nk][nl]=max(dp[c][nj][nk][nl],dp[p][j][k][l]+1);
				}
			}
		}
	}
	int ans=max(dp[n&1][c2][0][3],max(dp[n&1][c2][1][3],dp[n&1][c2][2][3]));
	ans=n-ans;
	ans=min(ans,min(c[0]+d[0],c[1]+d[1]));
	cout << ans << '\n';
}
int main(){
	ios::sync_with_stdio(false);
	//cin.tie(0);
	int t;cin >> t;
	while(t--) solve();
}
