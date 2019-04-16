/*
Move all coins inside the 2*N rectangle first.
Do sweepline, while sweeping to pr we ensure that all coins in the rectangle [1,pr]*[1,2]
  -are either in their final position
  -Moved out of the rectangle
We can determine how they move by some greedy supported with some replacement argument.
*/
#include<iostream>
using namespace std;
typedef long long ll;
const int N=1e5+2;
int n;
ll ans=0;
int fu[N],fd[N];
int plu,pld;
int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i=1; i<=2*n ;i++){
		ll x,y;cin >> x >> y;
		ans+=max(0LL,1-x)+max(0LL,x-n);
		ans+=max(0LL,1-y)+max(0LL,y-2);
		x=min((ll)n,max(1LL,x));
		y=min(2LL,max(1LL,y));
		if(y==1) fd[x]++;
		else fu[x]++;
	}
	plu=pld=1;
	for(int pr=1; pr<=n ;pr++){
		while(plu<=pr && fu[pr]>0) ans+=pr-plu++,fu[pr]--;
		while(pld<=pr && fd[pr]>0) ans+=pr-pld++,fd[pr]--;
		while(plu>pr && pld<=pr && fu[pr]>0) ans+=pr+1-pld++,fu[pr]--;
		while(pld>pr && plu<=pr && fd[pr]>0) ans+=pr+1-plu++,fd[pr]--;
		ans+=fu[pr];fu[pr+1]+=fu[pr];fu[pr]=0;
		ans+=fd[pr];fd[pr+1]+=fd[pr];fd[pr]=0;
	}
	cout << ans << endl;
}
