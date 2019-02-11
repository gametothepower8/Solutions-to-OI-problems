/*
A technique called "unrolled link list"(?)
*/
#include "elephants.h"
#include<iostream>
#include<queue>
using namespace std;
const int bs=400;
int bc;
int x[150000];
int n,l;
vector<int>bl[400];
vector<int>dp[400];
vector<int>en[400];
int z[150000];
int rnd=0;
void yena(int pos){
	dp[pos].resize(bl[pos].size()); dp[pos].shrink_to_fit();
	en[pos].resize(bl[pos].size()); en[pos].shrink_to_fit();
	if(bl[pos].empty()) return;
	int ptr=bl[pos].size();
	for(int i=(int)bl[pos].size()-1; i>=0 ;i--){
		while(ptr!=0 && bl[pos][ptr-1]>l+bl[pos][i]) --ptr;
		if(ptr==bl[pos].size()) dp[pos][i]=1,en[pos][i]=bl[pos][i]+l+1;
		else dp[pos][i]=1+dp[pos][ptr],en[pos][i]=en[pos][ptr];
	}
}
int sakura(){
	int ans=0,cur=0;
	for(int i=0; i<bc ;i++){
		if(bl[i].empty() || bl[i].back()<cur) continue;
		int pos=lower_bound(bl[i].begin(),bl[i].end(),cur)-bl[i].begin();
		ans+=dp[i][pos],cur=en[i][pos];
	}
	return ans;
}
void iu(){
	int tzuyu=0;
	for(int i=0; i<bc ;i++){
		for(auto cur:bl[i]) z[tzuyu++]=cur;
		bl[i].clear();
	}
	for(int i=0; i<n ;i++) bl[i/bs].push_back(z[i]);
	for(int i=0; i<bc ;i++){
		bl[i].shrink_to_fit();
		yena(i);
	}
}
int find(int x){
	for(int i=0; i<bc ;i++) if(!bl[i].empty() && bl[i].back()>=x) return i;
	return bc-1;
}
void init(int N, int L, int X[]){
	n=N;l=L;
	bc=(n-1)/bs+1;
	for(int i=0; i<n ;i++){
		x[i]=X[i];
		bl[i/bs].push_back(x[i]);
	}
	for(int i=0; i<bc ;i++) yena(i);
}
int update(int i, int y){
	if(++rnd==bs){
		rnd=0;
		iu();
	}
	int pos=find(x[i]);
	for(auto& cur:bl[pos]){
		if(cur==x[i]){
			cur=2e9;break;
		}
	}
	for(int i=1; i<bl[pos].size() ;i++) if(bl[pos][i]<bl[pos][i-1]) swap(bl[pos][i-1],bl[pos][i]);
	bl[pos].pop_back();yena(pos);
	x[i]=y;
	pos=find(x[i]);
	bl[pos].push_back(x[i]);
	for(int i=bl[pos].size()-1; i>=1 ;i--) if(bl[pos][i]<bl[pos][i-1]) swap(bl[pos][i-1],bl[pos][i]);
	yena(pos);
	return sakura();
}
