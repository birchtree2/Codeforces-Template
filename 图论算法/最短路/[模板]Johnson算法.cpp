#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 1000
#define maxm 5000 
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
int n,m;
struct edge{
	int from;
	int to;
	int next;
	int len;
}E[maxm*3+5];
int sz=1;
int head[maxn+5];
void add_edge(int u,int v,int w){
	sz++;
	E[sz].from=u;
	E[sz].to=v;
	E[sz].next=head[u];
	E[sz].len=w;
	head[u]=sz;
}

ll h[maxn+5];
bool inq[maxn+5];
void spfa(int s){
	queue<int>q;
	for(int i=1;i<=n;i++){
		h[i]=INF;
		inq[i]=0;
	}
	h[s]=0;
	q.push(s);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		inq[x]=0;
		for(int i=head[x];i;i=E[i].next){
			int y=E[i].to;
			if(h[y]>h[x]+E[i].len){
				h[y]=h[x]+E[i].len;
				if(!inq[y]){
					q.push(y);
					inq[y]=1; 
				}
			}
		}
	}
}

struct node{
	int id;
	ll dist;
	node(){
		
	}
	node(int _id,ll _dist){
		id=_id;
		dist=_dist;
	}
	friend bool operator < (node p,node q){
		return p.dist>q.dist;
	}
};
bool vis[maxn+5];
ll dist[maxn+5];
void dijkstra(int s){
	priority_queue<node>q;
	for(int i=1;i<=n;i++){
		dist[i]=INF;
		vis[i]=0;
	}
	dist[s]=0;
	q.push(node(s,0));
	while(!q.empty()){
		int x=q.top().id;
		q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x];i;i=E[i].next){
			int y=E[i].to;
			if(dist[y]>dist[x]+E[i].len){
				dist[y]=dist[x]+E[i].len;
				q.push(node(y,dist[y]));
			}
		}
	}
}

void johnson(){
	for(int i=1;i<=n;i++) add_edge(0,i,0);
	spfa(0);
	for(int i=2;i<=sz;i+=2){
		E[i].len=E[i].len+h[E[i].from]-h[E[i].to];
//		if(E[i].len<0) printf("fffffff\n");
	}
	for(int i=1;i<=n;i++){
		dijkstra(i);
		for(int j=1;j<=n;j++){
			ll ans=dist[j]-h[i]+h[j];
			if(ans==INF) printf("-1 ");
			else printf("%lld ",ans);
		}
		printf("\n");
	}
}

int main(){
	int u,v,w;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d %d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w); 
	}
	johnson();
}

