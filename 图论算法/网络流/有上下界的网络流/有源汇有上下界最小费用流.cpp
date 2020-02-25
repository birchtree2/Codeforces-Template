//https://www.cnblogs.com/liu-runda/p/6262832.html
//https://loj.ac/problem/116 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 205
#define maxm 10205
#define maxv 205
#define maxe 20005
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
int n,m,s,t;
struct edge{
    int from;
    int to;
    int next;
    long long flow;
    long long cost;
}E[maxm<<1];
int head[maxn];
int sz=1;
void add_edge(int u,int v,int w,int c){
//	printf("%d->%d vol=%d cost=%d\n",u,v,w,c);
    sz++;
    E[sz].from=u;
    E[sz].to=v;
    E[sz].next=head[u];
    E[sz].flow=w;
    E[sz].cost=c; 
    head[u]=sz;
    sz++;
    E[sz].from=v;
    E[sz].to=u;
    E[sz].next=head[v];
    E[sz].flow=0;
    E[sz].cost=-c; 
    head[v]=sz;
} 
long long dist[maxn];
long long minf[maxn];
int pre[maxn];
int inq[maxn]; 
bool spfa(int s,int t){
    memset(dist,0x3f,sizeof(dist));
    memset(inq,0,sizeof(inq));
    queue<int>q;
    q.push(s);
    inq[s]=1;
    dist[s]=0;
    while(!q.empty()){
        int x=q.front();
        q.pop();
        inq[x]=0; 
        for(int i=head[x];i;i=E[i].next){
            int y=E[i].to;
            if(E[i].flow){
                if(dist[y]>dist[x]+E[i].cost){
                    dist[y]=dist[x]+E[i].cost;
                    minf[y]=min(minf[x],E[i].flow);
                    pre[y]=i;
                    if(!inq[y]){
                        inq[y]=1;
                        q.push(y);
                    } 
                }
            }
        }
    } 
    if(dist[t]==INF) return 0;
    else return 1;
}
void update(int s,int t){
    int x=t;
    while(x!=s){
        int i=pre[x];
        E[i].flow-=minf[t];
        E[i^1].flow+=minf[t];
        x=E[i^1].to;
    }
}
pair<long long,long long> mcmf(int s,int t){
    memset(minf,0x3f,sizeof(minf));
    long long mincost=0;
    long long maxflow=0;
    while(spfa(s,t)){
        update(s,t);
        mincost+=dist[t]*minf[t];
        maxflow+=minf[t];
    }
    return make_pair(mincost,maxflow);
}

int from[maxm],to[maxm];
long long lower[maxm],upper[maxm];
long long cost[maxm];
long long dflow[maxn];//入流-出流 
int hash_id[maxm];//原图中的边i在新图中的反向边编号
void solve(){
	long long ans=0;
	int ss=0,tt=n+1;
	//边t->s的流量（反向边的残量）即为全图的最大流 
	from[m+1]=t;
	to[m+1]=s; 
	upper[m+1]=INF;
	lower[m+1]=0;
	for(int i=1;i<=m+1;i++){
		add_edge(from[i],to[i],upper[i]-lower[i],cost[i]);
		hash_id[i]=sz;
		dflow[from[i]]-=lower[i];
		dflow[to[i]]+=lower[i]; 
		ans+=cost[i]*lower[i];
	}
	long long sum=0;
	for(int i=1;i<=n;i++){
		if(dflow[i]<0){
			add_edge(i,tt,-dflow[i],0);
		}else if(dflow[i]>0){
			add_edge(ss,i,dflow[i],0);
			sum+=dflow[i];
		}
	}
	pair<long long,long long> p=mcmf(ss,tt);
	if(p.second==sum){//满流 
		ans+=p.first;
		printf("%lld\n",ans); 
	}else{
		printf("please go home to sleep\n");
	} 
}
int main(){
	scanf("%d %d %d %d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++) scanf("%d %d %lld %lld %lld",&from[i],&to[i],&lower[i],&upper[i],&cost[i]);
	solve();
} 
/*
3 3 1 3
1 2 1 2 4
2 3 2 3 1
1 3 4 5 2
*/

