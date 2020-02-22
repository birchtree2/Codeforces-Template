//https://www.luogu.com.cn/problem/P5357
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define maxc 26
#define maxn 2000000
using namespace std;
typedef long long ll;
struct AC_automaton{
	int ch[maxn+5][maxc];
	int fail[maxn+5];
	ll sum[maxn+5];
	int endp[maxn+5];
	int ptr;
	void insert(char *s,int id){
		int n=strlen(s+1);
		int x=0;
		for(int i=1;i<=n;i++){
			int c=s[i]-'a';
			if(!ch[x][c]) ch[x][c]=++ptr;
			x=ch[x][c];
		}
		endp[id]=x;
	} 
	void get_fail(){
		queue<int>q;
		for(int i=0;i<maxc;i++){
			if(ch[0][i]) q.push(ch[0][i]);
		}
		while(!q.empty()){
			int x=q.front();
			q.pop();
			for(int i=0;i<maxc;i++){
				if(ch[x][i]){
					q.push(ch[x][i]);
					fail[ch[x][i]]=ch[fail[x]][i];
				}else{
					ch[x][i]=ch[fail[x]][i];
				}
			}
		}
	}
	
	vector<int>tree[maxn+5];
	void dfs(int x){
		for(int i=0;i<tree[x].size();i++){
			int y=tree[x][i];
			dfs(y);
			sum[x]+=sum[y];
		}
	}
	
	void query(char *s){
		int n=strlen(s+1);
		int x=0;
		for(int i=1;i<=n;i++){
			int c=s[i]-'a';
			x=ch[x][c];
			sum[x]++;
		}
		for(int i=1;i<=ptr;i++) tree[fail[i]].push_back(i);
		dfs(0); 
	}
}T;

int n;
char s[maxn+5];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		T.insert(s,i);
	}
	T.get_fail();
	scanf("%s",s+1);
	T.query(s);
	for(int i=1;i<=n;i++) printf("%lld\n",T.sum[T.endp[i]]);
}


