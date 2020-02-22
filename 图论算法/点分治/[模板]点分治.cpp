#include<iostream>
#include<cstdio>
#include<cstring> 
#define maxn 100005
#define maxv 10000000 
using namespace std;
int n,m;
struct edge{
	int from;
	int to;
	int next;
	int len;
}E[maxn<<1];
int head[maxn];
int ec=1;
void add_edge(int u,int v,int w){
	ec++;
	E[ec].from=u;
	E[ec].to=v;
	E[ec].next=head[u];
	E[ec].len=w;
	head[u]=ec;
}

int root=0,sum;
int vis[maxn];
int sz[maxn];
int f[maxn];
void get_root(int x,int fa){
	sz[x]=1;
	f[x]=0;
	for(int i=head[x];i;i=E[i].next){
		int y=E[i].to;
		if(y!=fa&&!vis[y]){
			get_root(y,x);
			sz[x]+=sz[y];
			f[x]=max(sz[y],f[x]);
		}
	}
	f[x]=max(f[x],sum-sz[x]);
	if(f[root]>f[x]) root=x;
} 

int cnt=0;
int deep[maxn];
int res[maxv+5];
void get_deep(int x,int fa){
	res[++cnt]=deep[x];
	for(int i=head[x];i;i=E[i].next){
		int y=E[i].to;
		if(y!=fa&&!vis[y]){
			deep[y]=deep[x]+E[i].len;
			get_deep(y,x);
		}
	}
}

int mark[maxv+5];
void calc(int x,int d0,int tag){
	cnt=0;
	deep[x]=d0;
	get_deep(x,0);
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=cnt;j++){
			if(i!=j&&res[i]+res[j]<=maxv){
				mark[res[i]+res[j]]+=tag;
			}
		}
	}
}

void solve(int x){
	calc(x,0,1);
	vis[x]=1;
	for(int i=head[x];i;i=E[i].next){
		int y=E[i].to;
		if(!vis[y]){
			calc(y,E[i].len,-1);
			sum=sz[y];
			root=0;
			get_root(y,0);
			solve(root);
		}
	}
}

int main(){
	int u,v,w;
	scanf("%d %d",&n,&m);
	for(int i=1;i<n;i++){
		scanf("%d %d %d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	root=0;
	f[0]=n;
	sum=n;
	get_root(1,0);
	solve(root);
	for(int i=1;i<=m;i++){
		scanf("%d",&w);
		if(mark[w]) printf("AYE\n");
		else printf("NAY\n");
	}
}

