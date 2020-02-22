
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x3f3f3f3f
#define maxn 5005
#define maxm 50005
using namespace std;
inline void qread(int &x){
	x=0;
	int sign=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') sign=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	x=x*sign;
}
int n,m;
struct edge {
	int from;
	int to;
	int next;
	int flow;
	int cost;
} E[maxm<<1];
int sz=1;
int head[maxn];
int pre[maxn];
int minf[maxn];
int dist[maxn];
int inq[maxn];
void add_edge(int u,int v,int w,int c) {
	sz++;
	E[sz].from=u;
	E[sz].to=v;
	E[sz].flow=w;
	E[sz].cost=c;
	E[sz].next=head[u];
	head[u]=sz;
}

int spfa(int s,int t){
	queue<int>q;
	memset(dist,0x3f,sizeof(dist));
	memset(inq,0,sizeof(q));
	q.push(s);
	dist[s]=0;
	inq[s]=1;
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


int main() {
	int s,t,u,v,w,f;
	qread(n);
	qread(m);
	qread(s);
	qread(t);
	for(int i=1;i<=m;i++){
		qread(u);
		qread(v);
		qread(w);
		qread(f);
		add_edge(u,v,w,f);
		add_edge(v,u,0,-f);
	}
	memset(minf,0x3f,sizeof(minf));
	int maxflow,mincost;
	maxflow=0;
	mincost=0;
	while(spfa(s,t)){
		update(s,t);
		maxflow+=minf[t];
		mincost+=minf[t]*dist[t];
	}
	printf("%d %d\n",maxflow,mincost);
}
