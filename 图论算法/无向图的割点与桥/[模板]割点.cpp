#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100005
using namespace std;
int n,m;
int dfn[maxn];
int low[maxn];
int is_cut[maxn];
struct edge{
	int from;
	int to;
	int next;
}E[maxn*2]; 
int head[maxn];
int size=0;
void add_edge(int u,int v){
	size++;
	E[size].from=u;
	E[size].to=v;
	E[size].next=head[u];
	head[u]=size;
}

int tim=0;
int root=0;
int cutcnt=0;
void tarjan(int x){
	dfn[x]=++tim;
	low[x]=dfn[x];
	int vcnt=0;
	for(int i=head[x];i;i=E[i].next){
		int y=E[i].to;
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<=low[y]){
				vcnt++;
				if(vcnt>1||x!=root){
					if(is_cut[x]==0) cutcnt++;
					is_cut[x]=1;
				} 
			}
		}else low[x]=min(low[x],dfn[y]);
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
			root=i;
			tarjan(i); 
		} 
	}
	printf("%d\n",cutcnt);
	for(int i=1;i<=n;i++){
		if(is_cut[i]) printf("%d ",i);
	}
} 
