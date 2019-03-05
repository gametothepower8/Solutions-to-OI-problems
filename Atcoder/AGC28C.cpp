/*
Consider it as you choose N values out of 2*N values.
It would be valid if there is an element, you choose both A and B, or you choose A for all elements.
Just check [1,N], [1,N)+{N+1}, [1,N)+{N+2}, and [1,N-1)+{N}+{N+1}
*/
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
#define fi first
#define se second
int n;
pair<ll,pair<int,int> >c[200001];
int ch[100001][2];
int cnt[4];
int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i=1; i<=n ;i++){
		int a,b;cin >> a >> b;
		c[i*2-1]={a,{i,0}};
		c[i*2]={b,{i,1}};
	}
	sort(c+1,c+2*n+1);
	ll sum=0;
	for(int i=1; i<=n ;i++){
		ch[c[i].se.fi][c[i].se.se]=1;
		sum+=c[i].fi;
	}
	for(int i=1; i<=n ;i++){
		cnt[ch[i][0]*2+ch[i][1]]++;
	}
	if(cnt[3]!=0 || cnt[2]==n || cnt[2]==0) return cout << sum << endl,0;
	ch[c[n].se.fi][c[n].se.se]=0;ch[c[n+1].se.fi][c[n+1].se.se]=1;
	cnt[0]=cnt[1]=cnt[2]=cnt[3]=0;
	for(int i=1; i<=n ;i++){
		cnt[ch[i][0]*2+ch[i][1]]++;
	}
	if(cnt[3]!=0 || cnt[2]==n || cnt[2]==0) cout << sum-c[n].fi+c[n+1].fi << endl;
	else cout << min(sum-c[n].fi+c[n+2].fi,sum-c[n-1].fi+c[n+1].fi) << endl;
}
