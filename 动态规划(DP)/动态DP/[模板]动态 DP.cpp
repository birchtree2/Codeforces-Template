#include<iostream>
#include<cstdio>
#include<cstring>
#define INF 0x3f3f3f3f
#define maxn 200000
using namespace std;
typedef long long ll;
int n,m;
struct edge {
	int from;
	int to;
	int next;
} E[maxn*2+5];
int head[maxn+5];
int esz=1;
void add_edge(int u,int v) {
	esz++;
	E[esz].from=u;
	E[esz].to=v;
	E[esz].next=head[u];
	head[u]=esz;
}
int fa[maxn+5],son[maxn+5],sz[maxn+5],top[maxn+5],btm[maxn+5]/*所在重链最底端*/,dfn[maxn+5],hash_dfn[maxn+5];
void dfs1(int x,int f) {
	sz[x]=1;
	fa[x]=f;
	for(int i=head[x]; i; i=E[i].next) {
		int y=E[i].to;
		if(y!=f) {
			dfs1(y,x);
			sz[x]+=sz[y];
			if(sz[y]>sz[son[x]]) son[x]=y;
		}
	}
}
int tim=0;
void dfs2(int x,int t) {
	top[x]=t;
	dfn[x]=++tim;
	hash_dfn[dfn[x]]=x;
	if(son[x]) {
		dfs2(son[x],t);
		btm[x]=btm[son[x]];//维护重链最底端节点
	} else btm[x]=x;
	for(int i=head[x]; i; i=E[i].next) {
		int y=E[i].to;
		if(y!=fa[x]&&y!=son[x]) {
			dfs2(y,y);
		}
	}
}


struct matrix {
	ll a[2][2];
	inline void set(int x) {
		for(int i=0; i<2; i++) {
			for(int j=0; j<2; j++) a[i][j]=x;
		}
	}
	friend matrix operator * (matrix p,matrix q) {
		matrix ans;
		ans.set(-INF);
		for(int i=0; i<2; i++) {
			for(int j=0; j<2; j++) {
				for(int k=0; k<2; k++) {
					ans.a[i][j]=max(ans.a[i][j],p.a[i][k]+q.a[k][j]);
				}
			}
		}
		return ans;
	}
} mat[maxn+5];
ll val[maxn+5];
ll f[maxn+5][2],g[maxn+5][2];
void dfs3(int x) {
	f[x][0]=0;
	f[x][1]=val[x];
	for(int i=head[x]; i; i=E[i].next) {
		int y=E[i].to;
		if(y!=fa[x]) {
			dfs3(y);
			f[x][0]+=max(f[y][0],f[y][1]);
			f[x][1]+=f[y][0];
		}
	}
	g[x][0]=0,g[x][1]=val[x];
	for(int i=head[x]; i; i=E[i].next) {
		int y=E[i].to;
		if(y!=fa[x]&&y!=son[x]) {
			g[x][0]+=max(f[y][0],f[y][1]);
			g[x][1]+=f[y][0];
		}
	}
	mat[x].a[0][0]=g[x][0];
	mat[x].a[0][1]=g[x][0];
	mat[x].a[1][0]=g[x][1];
	mat[x].a[1][1]=-INF;
}

struct segment_tree {
	struct node {
		int l;
		int r;
		matrix v;
	} tree[maxn*4+5];
	void push_up(int pos) {
		tree[pos].v=tree[pos<<1].v*tree[pos<<1|1].v;
	}
	void build(int l,int r,int pos) {
		tree[pos].l=l;
		tree[pos].r=r;
		if(l==r) {
			tree[pos].v=mat[hash_dfn[l]];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,pos<<1);
		build(mid+1,r,pos<<1|1);
		push_up(pos);
	}
	void update(int upos,matrix &uval,int pos) {
		if(tree[pos].l==tree[pos].r) {
			tree[pos].v=uval;
			return;
		}
		int mid=(tree[pos].l+tree[pos].r)>>1;
		if(upos<=mid) update(upos,uval,pos<<1);
		else update(upos,uval,pos<<1|1);
		push_up(pos);
	}
	matrix query(int L,int R,int pos) {
		if(L<=tree[pos].l&&R>=tree[pos].r) return tree[pos].v;
		int mid=(tree[pos].l+tree[pos].r)>>1;
		matrix ans;
		ans.a[0][0]=ans.a[1][1]=0;
		ans.a[0][1]=ans.a[1][0]=-INF;
		if(L<=mid) ans=ans*query(L,R,pos<<1);
		if(R>mid) ans=ans*query(L,R,pos<<1|1);
		return ans;
	}
} T;
ll get_f(int x,int k) {
	//f[x]需要从x所在重链底端推上来,变成区间矩阵乘法
	return T.query(dfn[x],dfn[btm[x]],1).a[k][0];
}
void change(int x,int v) {
	g[x][1]+=v-val[x];
	val[x]=v;
	while(x) {
		mat[x].a[0][0]=g[x][0];
		mat[x].a[0][1]=g[x][0];
		mat[x].a[1][0]=g[x][1];
		mat[x].a[1][1]=-INF;
		T.update(dfn[x],mat[x],1);
		x=top[x];
		g[fa[x]][0]-=max(f[x][0],f[x][1]);
		g[fa[x]][1]-=f[x][0];
		f[x][0]=get_f(x,0);
		f[x][1]=get_f(x,1);
		g[fa[x]][0]+=max(f[x][0],f[x][1]);
		g[fa[x]][1]+=f[x][0];
		x=fa[x];
	}
}

int main() {
	int u,v;
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%lld",&val[i]);
	for(int i=1; i<n; i++) {
		scanf("%d %d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	dfs3(1);
	T.build(1,n,1);
	for(int i=1; i<=m; i++) {
		scanf("%d %d",&u,&v);
		change(u,v);
		printf("%lld\n",max(get_f(1,0),get_f(1,1)));
	}
}
