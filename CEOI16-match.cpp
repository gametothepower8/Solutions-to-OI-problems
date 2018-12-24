//For each L, find the first R such that [L,R) can form a BRS
//By DSU(or someother method) link all L,R and put equal labels for all x,y st [x,y) can form a BRS
//For each character, greedily find the last occurence inside the current segment of the same type such that [x,y] can form a BRS, using method above
#include<iostream>
#include<stack>
#include<set>
using namespace std;
string s,b;
int n;
int f[100001];
stack<char>st;
stack<int>cut;
set<pair<int,int> >g[226];
int par[100001];
int find(int x){
	if(par[x]!=x) par[x]=find(par[x]);
	return par[x];
}
void join(int u,int v){
	u=find(u);v=find(v);
	par[u]=v;
}
int main(){
	ios::sync_with_stdio(false);
	cin >> s;
	b=s;
	n=s.size();
	par[n]=n;
	for(int i=0; i<n ;i++){
		par[i]=i;
		if(st.empty() || st.top()!=s[i]) st.push(s[i]);
		else st.pop();
	}
	if(!st.empty()){
		cout << "-1\n";
		return 0;
	}
	for(int i=n-1; i>=0 ;i--){
		f[i]=-1;
		int en=i+1;
		while(en<n && en>=0){
			if(s[i]==s[en]){
				f[i]=en+1;
				break;
			}
			en=f[en];
		}
	}
	for(int i=0; i<n ;i++){
		if(f[i]!=-1) join(i,f[i]);
	}
	for(int i=0; i<n ;i++){
		g[s[i]].insert({find(i+1),i});
	}
	cut.push(n);
	for(int i=0; i<n ;i++){
		if(i==cut.top()){
			cut.pop();
			continue;
		}
		pair<int,int>tmp={find(i),cut.top()};
		auto it=g[s[i]].lower_bound(tmp);
		--it;
		b[i]='(';
		b[it->second]=')';
		cut.push(it->second);
		g[s[i]].erase(it);
	}
	cout << b << endl;
}
