//https://www.luogu.com.cn/problem/P5829
#include<iostream>
#include<cstdio>
#include<cstring> 
#include<vector> 
#define maxn 1000000
#define maxlogn 20
using namespace std;
char s[maxn+5];
void get_nex(char *t,int m,int *nex){
	nex[1]=0;
	for(int i=2,j=0;i<=m;i++){
		while(j&&t[j+1]!=t[i]) j=nex[j];
		if(t[j+1]==t[i]) j++;
		nex[i]=j;
	}
} 

int fail[maxn+5];
int n,m;
//vector<int>E[maxn+5];
//inline void add_edge(int u,int v){
//	E[u].push_back(v);
//}
int anc[maxn+5][maxlogn+1];
int deep[maxn+5];
//void dfs(int x,int fa){
//	deep[x]=deep[fa]+1;
//	anc[x][0]=fa;
//	for(int i=1;i<=maxlogn;i++) anc[x][i]=anc[anc[x][i-1]][i-1];
//	for(int i=0;i<E[x].size();i++){
//		int y=E[x][i];
//		if(y!=fa){
//			dfs(y,x);
//		}
//	}
//}
int lca(int x,int y){
	if(deep[x]<deep[y]) swap(x,y);
	for(int i=maxlogn;i>=0;i--){
		if((deep[x]-deep[y])&(1<<i)) x=anc[x][i];
	}
	if(x==y) return x;
	for(int i=maxlogn;i>=0;i--){
		if(anc[x][i]!=anc[y][i]){
			x=anc[x][i];
			y=anc[y][i]; 
		}
	}
	return anc[x][0];
}




int main(){
	int x,y;
	scanf("%s",s+1);
	n=strlen(s+1);
	get_nex(s,n,fail);
	for(int i=1;i<=n;i++){
		anc[i][0]=fail[i];
		deep[i]=deep[fail[i]]+1;
	}
//	dfs(0,0);不实际建边，节省内存
	for(int i=1;i<=n;i++){
		for(int j=1;(1<<j)<=deep[i];j++) anc[i][j]=anc[anc[i][j-1]][j-1];
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d",&x,&y);
		int lc=lca(x,y);
		if(lc==x||lc==y) printf("%d\n",anc[lc][0]);
		else printf("%d\n",lc);
	}
}

