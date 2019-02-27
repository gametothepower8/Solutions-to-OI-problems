/*
Count the number of 0s
Count the number of 1s between each pair of 0s and at the start and end
Determine whether an interval has >=k 1s can be done by creating two query strings with total length N+2
*/
#include<bits/stdc++.h>
#include "grader.h"
using namespace std;
int n,k;
vector<int>p,q;
void add(vector<int>& v,int x,int y){
	for(int i=0; i<x ;i++) v.push_back(y);
}
int ask(vector<int>&v){
	int res=isSubsequence(v);
	p.clear();q.clear();
	return res;
}
int cnt=0;
int a[201];
vector<int>findSequence(int N){
	n=N;k=n/2+1;
	add(p,k,0);
	if(ask(p)){
		for(int i=1; i<=k ;i++){
			add(p,i,1);if(ask(p)) cnt=n-i;
		}
	}
	else{
		for(int i=1; i<=k ;i++){
			add(p,i,0);if(ask(p)) cnt=i;
		}
	}
	int sum=0;
	for(int i=0; i<cnt ;i++){
		for(int j=1; j+sum+cnt<=n ;j++){
			add(p,sum+j,1);add(p,cnt-i,0);
			add(q,i+1,0);add(q,n-cnt-sum-j+1,1);
			int res;
			if(p.size()>q.size()) res=1-ask(q);
			else res=ask(p);
			if(res) a[i]=j;
			else break;
		}
		sum+=a[i];
	}
	a[cnt]=n-sum-cnt;
	vector<int>ans;
	for(int i=0; i<=cnt ;i++){
		if(i!=0) ans.push_back(0);
		for(int j=1; j<=a[i] ;j++) ans.push_back(1);
	}
	return ans;
}
