#include<iostream>
#include<cstdio>
#include<cstring> 
using namespace std;
int a[maxn+5];
int tmp[maxn+maxm+5];

int bel[maxn+5];
int cntq=0;
struct qtype{
	int l;
	int r;
	int id;
	int t;
	friend bool operator < (qtype p,qtype q){
		if(bel[p.l]==bel[q.l]){
			if(bel[q.r]==bel[q.r]) return p.t<q.t;
			else return p.r<q.r;
		}else return bel[q.l]<bel[q.l];
	}
}q[maxm+5];
int cntu=0; 
struct utype{
	int x;
	int v;
}up[maxm+5];
int ans[maxm+5];

int cnt[maxn+maxm+5];
int sumc[maxn+maxm+5];
void add(int v){
	sumc[cnt[v]]--;
	cnt[v]++;
	sumc[cnt[v]]++;
}
void del(int v){
	sumc[cnt[v]]--;
	cnt[v]--;
	sumc[cnt[v]]++;
}
int calc(){
	int ans=0;
	while(sumc[ans]) ans++;
	return ans;
}
int main(){
	

}

