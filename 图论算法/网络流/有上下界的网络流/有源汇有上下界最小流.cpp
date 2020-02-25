//https://www.cnblogs.com/liu-runda/p/6262832.html
//https://loj.ac/problem/117 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 50005
#define maxm 125005
#define maxv 100005
#define maxe 500005
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
int n,m,s,t;
struct edge {
	int from;
	int to;
	int next;
	long long flow;
} E[maxe<<1];
int head[maxv];
int sz=1;
void add_edge(int u,int v,long long w) {
//	 printf("%d->%d %d\n",u,v,w);
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
int cur[maxv];//当前弧优化 
//不加当前弧优化会T一个点 
bool bfs(int s,int t) {
	memset(deep,0,sizeof(deep));
	memcpy(cur,head,sizeof(head));
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
long long dfs(int x,int t,long long minf) {
	if(x==t) return minf;
	long long rest=minf,k;
	for(int i=cur[x]; i; i=E[i].next) {
		int y=E[i].to;
		cur[x]=i;
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
long long dinic(int s,int t) {
	long long ans=0,now=0;
	while(bfs(s,t)) {
		while(now=dfs(s,t,INF)) ans+=now;
	}
	return ans;
}

int from[maxm],to[maxm];
long long lower[maxm],upper[maxm];
long long dflow[maxn];//入流-出流 
int hash_id[maxm];//原图中的边i在新图中的反向边编号
int main(){
	int u,v;
	scanf("%d %d %d %d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++) scanf("%d %d %lld %lld",&from[i],&to[i],&lower[i],&upper[i]);
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
	long long sum=0;
	for(int i=1;i<=n;i++){
		if(dflow[i]<0){
			add_edge(i,tt,-dflow[i]);
		}else if(dflow[i]>0){
			add_edge(ss,i,dflow[i]);
			sum+=dflow[i];
		}
	}
	if(dinic(ss,tt)==sum){//满流 
		long long nowflow=E[hash_id[m+1]].flow;
		E[hash_id[m+1]].flow=E[hash_id[m+1]^1].flow=0; 
		long long minflow=-dinic(t,s)+nowflow;
		printf("%lld\n",minflow);
//		for(int i=1;i<=m;i++){
//			printf("%d\n",E[hash_id[i]].flow+lower[i]);
//		}
	}else{
		printf("please go home to sleep\n");
	} 
} 

