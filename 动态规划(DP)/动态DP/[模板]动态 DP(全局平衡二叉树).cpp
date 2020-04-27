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

struct matrix {
	ll a[2][2];
	matrix() {
		a[0][0]=a[0][1]=a[1][0]=a[1][1]=-INF;
	}
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
	ll* operator [](int i) {
		return a[i];
	}
} mat[maxn+5];
ll val[maxn+5];
ll f[maxn+5][2],g[maxn+5][2];
int sz[maxn+5],lsz[maxn+5],son[maxn+5];

void dfs1(int x,int fa) {
	sz[x]=lsz[x]=1;
	f[x][0]=0;
	f[x][1]=val[x];
	for(int i=head[x]; i; i=E[i].next) {
		int y=E[i].to;
		if(y!=fa) {
			dfs1(y,x);
			f[x][0]+=max(f[y][0],f[y][1]);
			f[x][1]+=f[y][0];
			sz[x]+=sz[y];
			if(sz[son[x]]<sz[y]) son[x]=y;
		}
	}
	g[x][0]=0,g[x][1]=val[x];
	for(int i=head[x]; i; i=E[i].next) {
		int y=E[i].to;
		if(y!=fa&&y!=son[x]) {
			g[x][0]+=max(f[y][0],f[y][1]);
			g[x][1]+=f[y][0];
			lsz[x]+=sz[y];
		}
	}
	mat[x].a[0][0]=g[x][0];
	mat[x].a[0][1]=g[x][0];
	mat[x].a[1][0]=g[x][1];
	mat[x].a[1][1]=-INF;
}

struct BST {
#define fa(x) (tree[x].fa)
#define lson(x) (tree[x].ch[0])
#define rson(x) (tree[x].ch[1])
	int root;
	int tot;
	int stk[maxn+5];//存储当前重链
	int sumsz[maxn+5];//存储重链上点的lsz之和
	struct node {
		int fa;//全局平衡二叉树上的父亲
		int ch[2];
		matrix v;
	} tree[maxn+5];
	inline bool is_root(int x) { //注意合并顺序
		return !(lson(fa(x))==x||rson(fa(x))==x);
	}
	void push_up(int x) {//很多函数和LCT是一样的
		tree[x].v=mat[x];
		if(lson(x)) tree[x].v=tree[lson(x)].v*tree[x].v;
		if(rson(x)) tree[x].v=tree[x].v*tree[rson(x)].v;
	}

	int get_bst(int l,int r) {
		if(l>r) return 0;
		int mid=lower_bound(sumsz+l,sumsz+r+1,(sumsz[l-1]+sumsz[r])/2)-sumsz;//求带权重心
		int x=stk[mid];
		lson(x)=get_bst(l,mid-1);
		rson(x)=get_bst(mid+1,r);//递归建树,这样的二叉树是平衡的
		if(lson(x)) fa(lson(x))=x;//类似LCT,初始化fa和son 
		if(rson(x)) fa(rson(x))=x;
		push_up(x);
		return x;
	}
	int build(int x,int f) {
		int rt=0;
		stk[++tot]=x;
		sumsz[tot]+=lsz[x];
		if(son[x]) { //继续dfs重链
			sumsz[tot+1]+=sumsz[tot];
			rt=build(son[x],x);
		} else { //到了重链底部,可以建二叉树了
			rt=get_bst(1,tot);
			for(int i=1; i<=tot; i++) sumsz[i]=0;
			tot=0;
			return rt;
		}
		for(int i=head[x]; i; i=E[i].next) {
			int y=E[i].to;
			if(y!=f&&y!=son[x]) fa(build(y,x))=x;//对于轻链,递归下去建树,再用fa把它们连起来
		}
		return rt;
	}
	void update(int x) {
		while(x) { //这一部分和树剖跳重链类似
			int f=fa(x);
			if(f&&is_root(x)) {//只有到了BST根的时候，说明已经处理完了整条重链，跳轻链到fa(x)更新上一条重链 
				mat[f][0][0]-=max(tree[x].v[0][0],tree[x].v[1][0]);
				mat[f][0][1]-=max(tree[x].v[0][0],tree[x].v[1][0]);
				mat[f][1][0]-=tree[x].v[0][0];
			}
			push_up(x);
			if(f&&is_root(x)) {
				mat[f][0][0]+=max(tree[x].v[0][0],tree[x].v[1][0]);
				mat[f][0][1]+=max(tree[x].v[0][0],tree[x].v[1][0]);
				mat[f][1][0]+=tree[x].v[0][0];
			}
			x=fa(x);
		}
	}
	void ini(){
		dfs1(1,0);
		root=build(1,0);
	}
	void change(int x,int v) {
		mat[x][1][0]+=v-val[x];
		val[x]=v;
		update(x);
	}
	ll query(){
		return max(tree[root].v[0][0],tree[root].v[1][0]);
	}
	void debug(){ 
		printf("root=%d\n",root); 
		for(int i=1;i<=n;i++) printf("%d ",fa(i));
		printf("\n");
	}
} T;


int main() {
	int u,v;
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%lld",&val[i]);
	for(int i=1; i<n; i++) {
		scanf("%d %d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	T.ini();
//	T.debug();
	for(int i=1; i<=m; i++) {
		scanf("%d %d",&u,&v);
		T.change(u,v);
		printf("%lld\n",T.query());
	}
}



