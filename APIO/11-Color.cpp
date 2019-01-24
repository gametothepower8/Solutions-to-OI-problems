/*Exhaust top left corner, consider all cells with x=1 or y=1 as nodes, each with a value 0 or 1
  then each fixed cell is a relation of f(u)^f(v)=(0 or 1)
  Then dfs through each component to see whether it is valid
*/
#include<iostream>
#include<queue>
using namespace std;
typedef long long ll;
const ll mod=1e9;
#define fi first
#define se second
int n,m,k;
bool can[2];
bool vis[200001];
bool ok=true;
int val[200001];
ll ans0,ans1;
vector<pair<int,int> >adj[200001];
void dfs(int id,int e){
	vis[id]=true;
    for(auto cur:adj[id]){
        if(vis[cur.fi]){
        	if(cur.se^e^val[cur.fi]^val[id]) ok=false;
		}
		else{
			val[cur.fi]=val[id]^cur.se^e;
			dfs(cur.fi,e);
		}
    }
}
void solve(int s,ll& ans){
    for(int i=0; i<=n+m ;i++) vis[i]=false,val[i]=0;
    vis[1]=true;vis[n+1]=true;
    for(int i=0; i<=n+m ;i++){
        if(vis[i]) continue;
        ok=true;
        dfs(i,(i==0)&s);
        if(!ok) ans=0;
        if(i!=0) ans=ans*2%mod;
    }
}
void addedge(int x,int y,int c){
	adj[x].push_back({y,c});
	adj[y].push_back({x,c});
}
int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    can[0]=can[1]=true;
    for(int i=1; i<=k ;i++){
        int x,y,c;
        cin >> x >> y >> c;
        if(x==1 && y==1) can[c^1]=false;
        else if(y==1) addedge(0,x,c);
        else if(x==1) addedge(0,n+y,c);
        else addedge(x,n+y,c^((x%2==0 && y%2==0)));
    }
    if(can[0]){
        ans0=1;
        solve(0,ans0);
    }
    if(can[1]){
        ans1=1;
        solve(1,ans1);
    }
    cout << (ans0+ans1)%mod << '\n';
}
