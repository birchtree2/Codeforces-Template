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
	matrix(){
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
} mat[maxn+5];
ll val[maxn+5];
ll f[maxn+5][2],g[maxn+5][2];

struct LCT {
#define lson(x) (tree[x].ch[0])
#define rson(x) (tree[x].ch[1])
#define fa(x) (tree[x].fa)
	struct node {
		int ch[2];
		int fa;
		matrix v;
	} tree[maxn+5];
	inline bool is_root(int x) { //注意合并顺序
		return !(lson(fa(x))==x||rson(fa(x))==x);
	}
	inline int check(int x) {
		return rson(fa(x))==x;
	}
	void push_up(int x) {
		tree[x].v=mat[x];
		if(lson(x)) tree[x].v=tree[lson(x)].v*tree[x].v;
		if(rson(x)) tree[x].v=tree[x].v*tree[rson(x)].v;
	}
	void rotate(int x) {
		int y=tree[x].fa,z=tree[y].fa,k=check(x),w=tree[x].ch[k^1];
		tree[y].ch[k]=w;
		tree[w].fa=y;
		if(!is_root(y)) tree[z].ch[check(y)]=x;
		tree[x].fa=z;
		tree[x].ch[k^1]=y;
		tree[y].fa=x;
		push_up(y);
		push_up(x);
	}
	void splay(int x) {
		while(!is_root(x)) {
			int y=fa(x);
			if(!is_root(y)) {
				if(check(x)==check(y)) rotate(y);
				else rotate(x);
			}
			rotate(x);
		}
	}
	void access(int x) {
		//access的时候可能由实变虚,或由虚变实,因此要更新f,g,方法类似LCT维护虚子树信息
		//这里和树剖向上跳重链更新是类似的
		if(x==2){
			x=2;
		}
		for(int y=0; x; y=x,x=fa(x)) {
			splay(x);
			//原来的rson(x)由实变虚
			if(rson(x)){
				mat[x].a[0][0]+=max(tree[rson(x)].v.a[0][0],tree[rson(x)].v.a[1][0]);//这里也可以不用f和g,直接写对应矩阵里的值 
				mat[x].a[1][0]+=tree[rson(x)].v.a[0][0];
			} 
			rson(x)=y;
			if(rson(x)){
				mat[x].a[0][0]-=max(tree[rson(x)].v.a[0][0],tree[rson(x)].v.a[1][0]);
				mat[x].a[1][0]-=tree[rson(x)].v.a[0][0];
			}
			mat[x].a[0][1]=mat[x].a[0][0];
			push_up(x);
		}
	}
	void change(int x,int v) {
		access(x);
		splay(x);
		mat[x].a[1][0]+=v-val[x];
		push_up(x);
		val[x]=v;
	}
	ll query(int x) {
		splay(1);//查询前记得splay到根 
		return max(tree[1].v.a[0][0],tree[1].v.a[1][0]);
	}
} T;

void dfs(int x,int fa) {
	f[x][0]=0;
	f[x][1]=val[x];
	for(int i=head[x]; i; i=E[i].next) {
		int y=E[i].to;
		if(y!=fa) {
			dfs(y,x);
			f[x][0]+=max(f[y][0],f[y][1]);
			f[x][1]+=f[y][0];
		}
	}
	mat[x].a[0][0]=mat[x].a[0][1]=f[x][0];//一开始全是轻边,f=g 
	mat[x].a[1][0]=f[x][1];
	mat[x].a[1][1]=-INF;
	T.tree[x].v=mat[x];//初始化LCT
	T.tree[x].fa=fa; //记得初始化fa
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
	dfs(1,0);
	for(int i=1; i<=m; i++) {
		scanf("%d %d",&u,&v);
		T.change(u,v);
		printf("%lld\n",T.query(1));
	}
}
