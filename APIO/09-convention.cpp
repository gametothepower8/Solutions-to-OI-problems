/*
Compute answer(value) for all prefices by dp.
We construct a DAG. 
Build edge between i-1,i if dp[i-1]==dp[i]
Build edge between s[i],e[i] if dp[s[i]]+1==dp[e[i]]
After this, we can now ignore the constraints of renting to maximum number of companies.
We just choose edges one by one, and see if there are suitable paths.
If the subproblem is to done on arbitary DAG, maybe some care is needed.
But we can make use of properties of the graph to ease implementation.
Its hard to explain, basically, use some topological sort style stuff.
*/
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
#define fi first
#define se second
int n;
int s[200001],e[200001];
pair<int,pair<int,int> >a[400001];
int dp[400001];

vector<pair<int,int> >adj[400001],rev[400001];
bool ept[400001];
bool die[200001];
bool tmw[400001];

int in[400001],out[400001];
vector<int>tzuyu[200001];
stack<int>kirino;
vector<int>ans;
void adde(int u,int v,int id){
	adj[u].push_back({v,id});
	rev[v].push_back({u,id});
	out[u]++;in[v]++;
}
void check(int id){
	if(!tmw[id] && !ept[id] && (in[id]==0 || out[id]==0) ) tmw[id]=true,kirino.push(id);
}
void rmv(int id){
	for(auto cur:adj[id]){
		if(cur.se!=0 && die[cur.se]) continue;
		die[cur.se]=true;in[cur.fi]--;
		check(cur.fi);
	}
	for(auto cur:rev[id]){
		if(cur.se!=0 && die[cur.se]) continue;
		die[cur.se]=true;out[cur.fi]--;
		check(cur.fi);
	}
}
void rmve(int id){
	out[s[id]]--;in[e[id]]--;die[id]=true;
	check(s[id]);check(e[id]);
}
void flush(){
	while(!kirino.empty()){
		int cur=kirino.top();
		kirino.pop();
		rmv(cur);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i=1; i<=n ;i++){
		cin >> s[i] >> e[i];
		a[2*i-1]={s[i],{0,i}};
		a[2*i]={e[i],{1,i}};
	}
	sort(a+1,a+2*n+1);
	for(int i=1; i<=2*n ;i++){
		if(a[i].se.fi) e[a[i].se.se]=i;
		else s[a[i].se.se]=i;
	}
	for(int i=1; i<=2*n ;i++){//compute dp
		dp[i]=dp[i-1];
		if(a[i].se.fi) dp[i]=max(dp[i],dp[s[a[i].se.se]]+1);
	}
	ept[1]=ept[2*n]=true;
	for(int i=2; i<=2*n ;i++) if(dp[i]==dp[i-1]) adde(i-1,i,0);
	for(int i=1; i<=n ;i++){
		if(dp[s[i]]+1==dp[e[i]]) adde(s[i],e[i],i),tzuyu[dp[e[i]]].push_back(i);
		else die[i]=true;
	}
	for(int i=1; i<=2*n ;i++){
		if(!ept[i] && (in[i]==0 || out[i]==0)) tmw[i]=true,kirino.push(i);
	}
	for(int i=1; i<=n ;i++){
		flush();
		if(die[i]) continue;
		ans.push_back(i);
		ept[s[i]]=ept[e[i]]=true;
		for(auto cur:tzuyu[dp[e[i]]]) if(!die[cur]) rmve(cur);
		for(int j=s[i]+1; j<e[i] ;j++) tmw[j]=true,kirino.push(j);
	}
	cout << ans.size() << '\n';
	for(int i=0; i<ans.size() ;i++){
		cout << ans[i] << " \n"[i==ans.size()-1];
	}
}
