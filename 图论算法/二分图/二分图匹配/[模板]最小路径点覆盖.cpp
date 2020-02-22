//luogu 2764 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define maxn 155
#define maxm 6005
using namespace std;
int n,m;
struct edge{
	int from;
	int to;
	int next;
}E[maxm];
int sz=0;
int head[maxn];
void add_edge(int u,int v){
	sz++;
	E[sz].from=u;
	E[sz].to=v;
	E[sz].next=head[u];
	head[u]=sz;
}

int vis[maxn*2];
int match[maxn*2];
int dfs(int x){
	for(int i=head[x];i;i=E[i].next){
		int y=E[i].to;
		if(!vis[y]){
			vis[y]=1;
			if(!match[y]||dfs(match[y])){
				match[y]=x;
				match[x]=y;
				return 1;
			}
		}
	}
	return 0;
}

void print(int x){
	x+=n;
	do{
		x-=n;
		printf("%d ",x);
		vis[x]=1;
		x=match[x];
	}while(x!=0);
	printf("\n"); 
}
int main(){
	int x,y;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d",&x,&y);
		add_edge(x,y+n); 
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		if(dfs(i)) ans++;
	}
	memset(vis,0,sizeof(vis)); 
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			print(i);
		}
	}
	printf("%d\n",n-ans);
} 
