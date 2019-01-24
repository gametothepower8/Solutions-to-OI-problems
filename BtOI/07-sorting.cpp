/*Consider the minimum element K in the array
1. Either we move it to the back immediately and solve recursively
2. Or we sort all the elemtents in front of K and then move all elements behind K from left to right in order
It can produce an optimal solution
Costs and solution can be maintained by DP with backtracking
*/
#include<iostream>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1001;
#define fi first
#define se second
int n;
pair<int,int>b[1001];
int a[1001];
int p[1001];
int x[1001];
bool hv[1001];
ll pf[1001][1001];
ll pc[1001][1001];
ll dp[1001][1001];
bool way[1001][1001];
vector<pair<int,int> >d;
void track(int i,int j){
	if(i==0 || j==0) return;
	if(p[i]>=j){
		track(i-1,j);
		return;
	}
	int pos=pc[i][p[i]],tot=pc[i][j];
	if(way[i][j]){
		track(i-1,p[i]-1);
		for(int k=p[i]+1; k<=j ;k++){
			if(a[k]<=i) d.push_back({++pos,x[k]});
		}
	}
	else{
		d.push_back({pos,tot});
		track(i-1,j);
	}
}
int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i=1; i<=n ;i++){
    	cin >> b[i].fi;
    	b[i].se=i;b[i].fi*=-1;
	}
	sort(b+1,b+n+1);
	for(int i=1; i<=n ;i++) a[b[i].se]=i,p[i]=b[i].se;
	for(int i=1; i<=n ;i++){
		x[i]=1;
		for(int j=1; j<a[i] ;j++) x[i]+=hv[j];
		hv[a[i]]=true;
	}
	for(int i=1; i<=n ;i++){
		for(int j=1; j<=n ;j++){
			pf[i][j]=pf[i][j-1]+x[j]*(a[j]<=i);
			pc[i][j]=pc[i][j-1]+(a[j]<=i);
			if(p[i]>=j){
				dp[i][j]=dp[i-1][j];
				continue;
			}
			int pos=pc[i][p[i]],tot=pc[i][j];
			ll c1=dp[i-1][j]+pos+tot;
			ll c2=dp[i-1][p[i]-1]+1LL*(pos+tot+1)*(tot-pos)/2+pf[i][j]-pf[i][p[i]];
			if(c1>c2) way[i][j]=true;
			dp[i][j]=min(c1,c2);
		}
	}
	track(n,n);
	cout << d.size() << '\n';
	for(auto cur:d) cout << cur.fi << ' ' << cur.se << '\n';
}
