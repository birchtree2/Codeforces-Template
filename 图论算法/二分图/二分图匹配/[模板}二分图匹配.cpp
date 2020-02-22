#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 1005
#define maxm 1005
#define maxe 500005 
using namespace std;
int n,m,e;
struct edge{
	int from;
	int to;
	int next;
}E[maxe<<1];
int sz=0;
int head[maxn];
void add_edge(int u,int v){
	sz++;
	E[sz].from=u;
	E[sz].to=v;
	E[sz].next=head[u];
	head[u]=sz;
}

int vis[maxn];
int match[maxn];
int dfs(int x){
	for(int i=head[x];i;i=E[i].next){
		int y=E[i].to;
		if(!vis[y]){
			vis[y]=1;
			if(!match[y]||dfs(match[y])){
				match[y]=x;
				return 1;
			}
		}
	}
	return 0;
}
int main(){
	int u,v;
	scanf("%d %d %d",&n,&m,&e);
	for(int i=1;i<=e;i++){
		scanf("%d %d",&u,&v);
		if(u>n||v>m) continue;
		add_edge(u,v);//注意，只用加单向边 
		add_edge(v,u); 
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		if(dfs(i)) ans++;
	} 
	printf("%d\n",ans);
} 
