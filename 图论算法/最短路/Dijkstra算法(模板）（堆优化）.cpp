#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 10005
#define maxm 500005 
#define INF 2147483647
using namespace std;
int n,m,s;
struct edge {
	int from;
	int to;
	int len;
	int next;
} graph[maxm];
int head[maxn];
int size;
void ini() {
	memset(graph,0,sizeof(graph));
	memset(head,0,sizeof(head));
	size=0;
}
void add_edge(int u,int v,int w) {
	graph[size++].from=u;
	graph[size].to=v;
	graph[size].len=w;
	graph[size].next=head[u];
	head[u]=size;
}

struct heap_node {
	int d;
	int u;
	friend bool operator <(heap_node x,heap_node y) {
		return x.d>y.d;
	}
	heap_node(int dis,int no) {
		d=dis;
		u=no;
	}
};
int dis[maxn],used[maxn];
void dijkstra(int s) {
	priority_queue<heap_node>heap;
	for(int i=1; i<=n; i++) dis[i]=INF;
	dis[s]=0;
	memset(used,0,sizeof(used));
	heap.push(heap_node(0,s));
	while(!heap.empty()) {
		heap_node x=heap.top();
		heap.pop();
		int u=x.u;
		if(used[u]) continue;
		used[u]=1;
		for(int i=head[u];i!=0;i=graph[i].next){
			if(dis[graph[i].to]>dis[u]+graph[i].len) dis[graph[i].to]=dis[u]+graph[i].len;
			heap.push(heap_node(dis[graph[i].to],graph[i].to));
		}
   }
}
int main(){
	int u,v,w;
	scanf("%d %d %d",&n,&m,&s);
	while(m--){
		scanf("%d %d %d",&u,&v,&w);
		add_edge(u,v,w);
	}
	dijkstra(s);
	for(int i=1;i<=n;i++) printf("%d ",dis[i]);
}
