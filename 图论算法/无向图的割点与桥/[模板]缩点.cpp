#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 10005
#define maxm 50005
using namespace std;
int n,m;
int dfn[maxn];
int low[maxn];
int is_bridge[maxn];
struct edge{
	int from;
	int to;
	int next;
}G[maxm*2],E[maxn*2]; 
int head1[maxn];
int head2[maxn];
int size1=1;//一定要从2,3开始存,这样i的重边就可以存储在i^1 
void add_edge1(int u,int v){
	size1++;
	G[size1].from=u;
	G[size1].to=v;
	G[size1].next=head1[u];
	head1[u]=size1;
}
int size2=0;
void add_edge2(int u,int v){
	size2++;
	E[size2].from=u;
	E[size2].to=v;
	E[size2].next=head2[u];
	head2[u]=size2;
}
int tim=0;
int bridge_cnt=0;
void tarjan(int x,int last_edge){
	dfn[x]=++tim;
	low[x]=dfn[x];
	for(int i=head1[x];i;i=G[i].next){
		int y=G[i].to;
		if(!dfn[y]){
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<low[y]){
				is_bridge[i]=is_bridge[i^1]=1;
			}
		}else if(i!=(last_edge^1)) low[x]=min(low[x],dfn[y]);
	} 
}
int c[maxn];
int dcc=0; 
void e_dcc(int x){
	c[x]=dcc;
	for(int i=head1[x];i;i=G[i].next){
		int y=G[i].to;
		if(c[y]||is_bridge[i]) continue;
		e_dcc(y); 
	}
}
int main(){
	int u,v;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d",&u,&v);
		add_edge1(u,v);
		add_edge1(v,u); 
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i,0); 
		} 
	}
	for(int i=1;i<=n;i++){
		if(!c[i]){
			dcc++;
			e_dcc(i);
		}
	}
	for(int i=2;i<=size1;i++){
		int x=G[i].from;
		int y=G[i].to;
		if(c[x]==c[y]) continue;
		else{
			add_edge2(c[x],c[y]);
//			add_edge2(c[y],c[x]);
		} 
	}
	return 0;
} 
