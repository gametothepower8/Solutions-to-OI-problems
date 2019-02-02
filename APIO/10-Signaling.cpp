/*
Count sum and divide by nC3.
For each 3-tuple, we count the original 3 points. From now on we ignore these
For each 4-tuple, consider number of points in its convex hull.
- 3: contributes 1 to sum
- 4: contributes 2 to sum
There would be exactly 2 tangents from a point to a triangle iff the point isnt inside the triangle
For convinience, we only consider tangents of 1 direction.
Fix each point as origin, sort vectors by angle and do some 2 pointers and some math to compute the sum.
*/
#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pt;
#define x first
#define y second
pt operator-(pt u,pt v){return {u.x-v.x,u.y-v.y};};
ll operator^(pt u,pt v){return u.x*v.y-u.y*v.x;}
int q(pt u){return (u.y<0)*2+((u.x<0)^(u.y<0));}
bool cmp(pt u,pt v){
	if(q(u)!=q(v)) return q(u)<q(v);
	return (u^v)>=0;
}
bool leqpi(pt u,pt v){
	return (u^v)>=0;
}
const pt one={1,0};
int n;
pt a[1501];
pt b[3001];
int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i=1; i<=n ;i++) cin >> a[i].x >> a[i].y;
	ll ans=3LL*n*(n-1)*(n-2)/6-2LL*n*(n-1)*(n-2)*(n-3)/24;
	ll cnt=0;
	for(int i=1; i<=n ;i++){
		for(int j=1; j<=n ;j++) if(j!=i) b[j-(j>i)]=a[j]-a[i];
		sort(b+1,b+n,cmp);
		int ptr=1;
		while(ptr<=n-1 && (one^b[ptr])>=0){
			b[n-1+ptr]=b[ptr];ptr++;
		}
		int pl=1;
		ll tot=0;
		for(int j=ptr; j<ptr+n-1 ;j++){
			while(pl<=j-n+1) pl++;
			while(pl<j && !leqpi(b[pl],b[j])) pl++;
			tot+=1LL*(j-pl)*(j-pl-1)/2;
		}
		cnt+=tot;
	}
	ans+=cnt;
	ll yerin=1LL*n*(n-1)*(n-2)/6;
	long double fans=ans;
	cout << fixed << setprecision(10) << fans/yerin << endl;
}
