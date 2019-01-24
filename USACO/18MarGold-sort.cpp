//Count the number of moves to make the set of numbers 1~i appear in the first i cells for each i
#include<iostream>
#include<algorithm>
using namespace std;
#define fi first
#define se second
int n;
pair<int,int>a[100001];
int p[100001];
int bit[100001];
void upd(int id){
	for(int i=id; i<=n ;i+=i&-i) bit[i]++;
}
int qry(int id){
	int res=0;
	for(int i=id; i>=1 ;i-=i&-i) res+=bit[i];
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	//freopen("sort.in","r",stdin);
	//freopen("sort.out","w",stdout);
	cin >> n;
	for(int i=1; i<=n ;i++){
		cin >> a[i].fi;
		a[i].se=i;
	}
	sort(a+1,a+n+1);
	for(int i=1; i<=n ;i++)p[a[i].se]=i;
	int ans=1;
	for(int i=1; i<=n ;i++){
		upd(p[i]);
		ans=max(i-qry(i),ans);
	}
	cout << ans << endl;
}
