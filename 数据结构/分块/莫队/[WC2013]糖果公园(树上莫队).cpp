#include<iostream>
#include<cstdio>
#include<cstring> 
#include<algorithm>
#include<cmath>
#define maxn 100000
#define maxv 1000000
#define maxm 1000000
#define maxlogn 20
using namespace std;
typedef long long ll;
inline void qread(int &x) {
	x=0;
	int sign=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-') sign=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=x*10+c-'0';
		c=getchar();
	}
	x=x*sign;
}
inline void qprint(long long x) {
	if(x<0) {
		putchar('-');
		qprint(-x);
	} else if(x==0) {
		putchar('0');
		return;
	} else {
		if(x>=10) qprint(x/10);
		putchar('0'+x%10);
	}
}

int n,kn,m;
int v[maxn+5],w[maxn+5];
int c[maxn+5];

struct edge{
	int from;
	int to;
	int next;
}E[maxn*2+5];
int head[maxn*2+5];
int sz=1;
void add_edge(int u,int v){
	sz++;
	E[sz].from=u;
	E[sz].to=v;
	E[sz].next=head[u];
	head[u]=sz;
} 

int log2n;
int tim;
int st[maxn+5],ed[maxn+5];
int hash_dfn[maxn*2+5];
int deep[maxn+5];
int anc[maxn+5][maxlogn+5]; 
void dfs(int x,int fa){
	st[x]=++tim;
	hash_dfn[tim]=x;
	deep[x]=deep[fa]+1;
	anc[x][0]=fa;
	for(int i=1;i<=log2n;i++) anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=head[x];i;i=E[i].next){
		int y=E[i].to;
		if(y!=fa){
			dfs(y,x);
		}
	} 
	ed[x]=++tim;
	hash_dfn[tim]=x;
}
int lca(int x,int y){
	if(deep[x]<deep[y]) swap(x,y);
	for(int i=log2n;i>=0;i--){
		if(deep[anc[x][i]]>=deep[y]){
			x=anc[x][i];
		}
	}
	if(x==y) return x;
	for(int i=log2n;i>=0;i--){
		if(anc[x][i]!=anc[y][i]){
			x=anc[x][i];
			y=anc[y][i];
		}
	}
	return anc[x][0];
}

int bsz;
int belong[maxn*2+5];
int l,r,t;
int cntq;
struct que{
	int l;
	int r;
	int lc;
	int tim;
	int id;
	friend bool operator < (que x,que y){
		return (belong[x.l] ^ belong[y.l]) ? belong[x.l] < belong[y.l] :((belong[x.r] ^ belong[y.r]) ? belong[x.r] < belong[y.r] : x.tim < y.tim);
	}
}q[maxm+5];
int cntu;
struct upd{
	int pos;
	int val;
}up[maxm+5];
bool vis[maxn+5];
ll cnt[maxv+5];
ll sum=0;
void add(int val){
	cnt[val]++;
	sum+=(ll)v[val]*w[cnt[val]];
}
void del(int val){
	sum-=(ll)v[val]*w[cnt[val]];
	cnt[val]--;
}
void calc(int x){
	if(vis[x]) del(c[x]);
	else add(c[x]);
	vis[x]^=1;
}
void update(upd &p){
	int x=p.pos;
	if(vis[x]){
		del(c[x]);//先去掉原来的，
		swap(c[x],p.val);
		add(c[x]);//再加上新的的，
	}else swap(c[x],p.val);
}
ll ans[maxm+5];

int main(){
	int cmd,x,y;
	qread(n);
	qread(kn);
	qread(m);
	for(int i=1;i<=kn;i++) qread(v[i]);
	for(int i=1;i<=n;i++) qread(w[i]);
	for(int i=1;i<n;i++){
		qread(x);
		qread(y);
		add_edge(x,y);
		add_edge(y,x);
	} 
	for(int i=1;i<=n;i++) qread(c[i]);
	log2n=log2(n); 
	dfs(1,0);
	bsz=pow(n*2,2.0/3.0);
	for(int i=1;i<=n*2;i++) belong[i]=i/bsz+1;
	for(int i=1;i<=m;i++){
		qread(cmd);
		qread(x);
		qread(y);
		if(cmd==0){
			cntu++;
			up[cntu].pos=x;
			up[cntu].val=y;
		}else{
			cntq++;
			int lc=lca(x,y);
			if(st[x]>st[y]) swap(x,y);
			if(lc==x){
				q[cntq].l=st[x];
				q[cntq].r=st[y];
				q[cntq].lc=0;
				q[cntq].tim=cntu;
				q[cntq].id=cntq;
			}else{
				q[cntq].l=ed[x];
				q[cntq].r=st[y];
				q[cntq].lc=lc;
				q[cntq].tim=cntu;
				q[cntq].id=cntq;
			}
		}
	}
	sort(q+1,q+1+cntq);
	l=1,r=0,t=0;
	for(int i=1;i<=cntq;i++){
		while(l<q[i].l) calc(hash_dfn[l++]);
		while(l>q[i].l) calc(hash_dfn[--l]);
		while(r<q[i].r) calc(hash_dfn[++r]);
		while(r>q[i].r) calc(hash_dfn[r--]);
		while(t<q[i].tim) update(up[++t]);
		while(t>q[i].tim) update(up[t--]);
		if(q[i].lc) calc(q[i].lc);
		ans[q[i].id]=sum;
		if(q[i].lc) calc(q[i].lc);
	}
	for(int i=1;i<=cntq;i++){
		qprint(ans[i]);
		putchar('\n');
	}
}
