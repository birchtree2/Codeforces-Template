#include<iostream>
#include<cstdio> 
#include<cstring>
#include<vector>
#include<stack>
#define maxn 10005
#define maxm 200005 
using namespace std;
int n,m;
struct edge{
	int from;
	int to;
	int next;
}E[maxm];
int head[maxn];
int sz=0;
void add_edge(int u,int v){
	sz++;
	E[sz].from=u;
	E[sz].to=v;
	E[sz].next=head[u];
	head[u]=sz;
} 

stack<int>s;
vector<int>scc[maxn];
int ins[maxn];//是否在栈内 
int dfn[maxn];//时间戳 
int low[maxn];//追溯值
int id[maxn];//点的连通分量编号 
int num=0;
int cnt=0;//SCC数量 
void tarjan(int x){
	ins[x]=1;
	s.push(x);
	low[x]=dfn[x]=++num;
	for(int i=head[x];i;i=E[i].next){
		int y=E[i].to;
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(ins[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		cnt++;
		int y;
		do{
			y=s.top();
			ins[y]=0;
			s.pop();
			id[y]=cnt;
			scc[cnt].push_back(y); 
		}while(x!=y);
	}
}

int main(){
	int u,v;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d",&u,&v);
		add_edge(u,v); 
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) tarjan(i);
	}
	for(int i=1;i<=cnt;i++){
		printf("scc %d: ",i);
		for(int j=0;j<scc[i].size();j++){
			printf("%d ",scc[i][j]);
		}
		printf("\n");
	}
}
