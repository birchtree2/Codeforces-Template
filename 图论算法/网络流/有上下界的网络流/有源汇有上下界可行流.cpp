//https://www.cnblogs.com/liu-runda/p/6262832.html
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 205
#define maxm 10205
#define maxv 205
#define maxe 20005
#define INF 0x3f3f3f3f
using namespace std;
struct edge {
	int from;
	int to;
	int next;
	int flow;
} E[maxe<<1];
int head[maxv];
int sz=1;
void add_edge(int u,int v,int w) {
	 printf("%d->%d %d\n",u,v,w);
	sz++;
	E[sz].from=u;
	E[sz].to=v;
	E[sz].flow=w;
	E[sz].next=head[u];
	head[u]=sz;
	sz++;
	E[sz].from=v;
	E[sz].to=u;
	E[sz].flow=0;
	E[sz].next=head[v];
	head[v]=sz;
}
int deep[maxv];
bool bfs(int s,int t) {
	memset(deep,0,sizeof(deep));
	deep[s]=1;
	queue<int>q;
	q.push(s);
	while(!q.empty()) {
		int x=q.front();
		q.pop();
		for(int i=head[x]; i; i=E[i].next) {
			int y=E[i].to;
			if(E[i].flow&&!deep[y]) {
				deep[y]=deep[x]+1;
				q.push(y);
			}
		}
	}
	if(deep[t]!=0) return 1;
	else return 0;
}
int dfs(int x,int t,int minf) {
	if(x==t) return minf;
	int rest=minf,k;
	for(int i=head[x]; i; i=E[i].next) {
		int y=E[i].to;
		if(deep[y]==deep[x]+1&&E[i].flow) {
			k=dfs(y,t,min(rest,E[i].flow));
			rest-=k;
			E[i].flow-=k;
			E[i^1].flow+=k;
			if(rest==0) break;
			if(k==0) deep[y]=0;
		}
	}
	return minf-rest;
}
int dinic(int s,int t) {
	int ans=0,now=0;
	while(bfs(s,t)) {
		while(now=dfs(s,t,INF)) ans+=now;
	}
	return ans;
}

int n,m,s,t;
int from[maxm],to[maxm];
int lower[maxm],upper[maxm];
int dflow[maxn];//入流-出流 
int hash_id[maxm];//原图中的边i在新图中的反向边编号 
int main(){
	int u,v;
	scanf("%d %d %d %d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++) scanf("%d %d %d %d",&from[i],&to[i],&lower[i],&upper[i]);
	int ss=0,tt=n+1;
	//边t->s的流量（反向边的残量）即为全图的最大流 
	from[m+1]=t;
	to[m+1]=s; 
	upper[m+1]=INF;
	lower[m+1]=0;
	for(int i=1;i<=m+1;i++){
		add_edge(from[i],to[i],upper[i]-lower[i]);
		hash_id[i]=sz;
		dflow[from[i]]-=lower[i];
		dflow[to[i]]+=lower[i]; 
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		if(dflow[i]<0){
			add_edge(i,tt,-dflow[i]);
		}else{
			add_edge(ss,i,dflow[i]);
			sum+=dflow[i];
		}
	}
	if(dinic(ss,tt)==sum){//满流 
		printf("YES\n");
		printf("%d\n",E[hash_id[m+1]].flow+lower[m+1]);
		for(int i=1;i<=m;i++){
			printf("%d\n",E[hash_id[i]].flow+lower[i]);
		}
	}else{
		printf("NO\n");
	} 
} 
/*
input:
3 3 1 3
1 2 2 3
2 3 3 3
1 3 1 4

output:
YES
4
3
3
1

----------
input:
3 3 1 3
1 2 2 2
2 3 3 3
1 3 1 4

output:
NO
*/
