#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 105
#define maxm 10005
#define INF 0x7ffffffff
using namespace std;
inline int qread(){
	int x=0,sign=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') sign=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*sign;
}
int n,m,s,t;
long long flow[maxm];
long long incf[maxm];
int pre[maxn];
int vis[maxn];

struct edge{
	int from;
	int to;
	int next;
}E[maxm];
int head[maxn];
int sz=1;
void add_edge(int u,int v,int w){
	sz++;
	E[sz].from=u;
	E[sz].to=v;
	E[sz].next=head[u];
	head[u]=sz;
	flow[sz]=w;
}

queue<int>q;
int bfs(int s,int t){
	while(!q.empty()) q.pop();
	q.push(s);
	memset(vis,0,sizeof(vis));
	vis[s]=1;
	incf[s]=INF;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=E[i].next){
			int y=E[i].to;
			if(!vis[y]&&flow[i]){
				vis[y]=1;
				incf[y]=min(incf[x],flow[i]);
				pre[y]=i;
				if(y==t) return 1;
				q.push(y);
			}
		}
	}
	return 0;
}

void update(int s,int t){
	int x=t;
	while(x!=s){
		int i=pre[x];
		flow[i]-=incf[t];
		flow[i^1]+=incf[t];
		x=E[i^1].to;
	}
}

long long EK(int s,int t){
	long long ans=0;
	while(bfs(s,t)){
		ans+=incf[t];
		update(s,t);
	}
	return ans;
}

int main(){
	int u,v,w;
	scanf("%d %d %d %d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++){
		u=qread();
		v=qread();
		w=qread();
		add_edge(u,v,w);
		add_edge(v,u,0);
	}
	printf("%lld\n",EK(s,t));
}
