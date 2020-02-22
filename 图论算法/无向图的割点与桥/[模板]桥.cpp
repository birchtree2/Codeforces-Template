#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100005
using namespace std;
int n,m;
int dfn[maxn];
int low[maxn];
int is_bridge[maxn];
struct edge{
	int from;
	int to;
	int next;
}E[maxn*2]; 
int head[maxn];
int size=1;//一定要从2,3开始存,这样i的重边就可以存储在i^1 
void add_edge(int u,int v){
	size++;
	E[size].from=u;
	E[size].to=v;
	E[size].next=head[u];
	head[u]=size;
}

int tim=0;
int bridge_cnt=0;
void tarjan(int x,int last_edge){
	dfn[x]=++tim;
	low[x]=dfn[x];
	for(int i=head[x];i;i=E[i].next){
		int y=E[i].to;
		if(!dfn[y]){
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<low[y]){
				is_bridge[i]=is_bridge[i^1]=1;
			}
		}
		else if(i!=(last_edge^1)) low[x]=min(low[x],dfn[y]);
	}
}
int main(){
	int u,v;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d",&u,&v);
		add_edge(u,v);
		add_edge(v,u); 
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i,0); 
		} 
	}
	for(int i=2;i<size;i+=2){
		if(is_bridge[i]) printf("%d %d\n",E[i].from,E[i].to);
	}
} 
/*
6 7
1 2
1 3
2 3
2 4
4 5
4 6
5 6

*/
