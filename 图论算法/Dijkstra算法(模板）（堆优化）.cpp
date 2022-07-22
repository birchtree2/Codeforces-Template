struct edge{
	int from;
	int to;
	int next;
	int len;
	int type;
}E[maxm*2+5];
int head[maxn+5];
int esz=1;
void add_edge(int u,int v,int w,int t){
	esz++;
	E[esz].from=u;
	E[esz].to=v;
	E[esz].next=head[u];
	E[esz].len=w;
	E[esz].type=t;
	head[u]=esz;
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
	memset(vis,0,sizeof(vis));
	memset(dist,0x3f,sizeof(dist));
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
				if(!vis[y]) q.push(node(y,dist[y]));
			}
		}
	}
}

