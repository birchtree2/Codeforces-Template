#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100000
#define maxm 100000
#define maxlogn 20
using namespace std;
int n,m,dn;
int a[maxn+5];
int tmp[maxn+maxm+5];
struct qtype{
	int op;
	int l;
	int r;
	int k;
}q[maxm+5];

struct persist_segment_tree{
#define lson(x) (tree[x].ls)
#define rson(x) (tree[x].rs)
	struct node{
		int ls;
		int rs;
		int cnt;
	}tree[maxn*maxlogn*maxlogn+5];
	int ptr;
	inline void push_up(int x){
		tree[x].cnt=tree[lson(x)].cnt+tree[rson(x)].cnt;
	}
	void update(int &x,int last,int upos,int uval,int l,int r){
		x=++ptr;
		tree[x]=tree[last];
		if(l==r){
			tree[x].cnt+=uval;
			return;
		}
		int mid=(l+r)>>1;
		if(upos<=mid) update(lson(x),lson(last),upos,uval,l,mid);
		else update(rson(x),rson(last),upos,uval,mid+1,r);
		push_up(x);
	}
	int query(int *lt,int lcnt,int *rt,int rcnt,int k,int l,int r){
		if(l==r) return l;
		int mid=(l+r)>>1;
		int cnt=0;
		for(int i=1;i<=lcnt;i++) cnt-=tree[lson(lt[i])].cnt;
		for(int i=1;i<=rcnt;i++) cnt+=tree[lson(rt[i])].cnt;
		if(k<=cnt){
			for(int i=1;i<=lcnt;i++) lt[i]=lson(lt[i]);
			for(int i=1;i<=rcnt;i++) rt[i]=lson(rt[i]);
			return query(lt,lcnt,rt,rcnt,k,l,mid);
		}else{
			for(int i=1;i<=lcnt;i++) lt[i]=rson(lt[i]);
			for(int i=1;i<=rcnt;i++) rt[i]=rson(rt[i]);
			return query(lt,lcnt,rt,rcnt,k-cnt,mid+1,r);
		}
	}
}T;
int root[maxn+5];
inline int lowbit(int x){
	return x&(-x);
}
void update(int pos,int val,int type){
	for(int i=pos;i<=n;i+=lowbit(i)) T.update(root[i],root[i],val,type,1,dn);
}
int query(int l,int r,int k){
	static int lt[maxn+5],rt[maxn+5];
	int lcnt=0,rcnt=0;
	for(int i=l-1;i;i-=lowbit(i)) lt[++lcnt]=root[i];
	for(int i=r;i;i-=lowbit(i)) rt[++rcnt]=root[i];
	int id=T.query(lt,lcnt,rt,rcnt,k,1,dn);
	return tmp[id];
}
int main(){
	char cmd[10];
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		tmp[++dn]=a[i];
	}
	for(int i=1;i<=m;i++){
		scanf("%s",cmd);
		if(cmd[0]=='Q'){
			q[i].op=1;
			scanf("%d %d %d",&q[i].l,&q[i].r,&q[i].k);
		}else{
			q[i].op=2;
			scanf("%d %d",&q[i].l,&q[i].r);
			tmp[++dn]=q[i].r;
		}
	}
	sort(tmp+1,tmp+1+dn);
	dn=unique(tmp+1,tmp+1+dn)-tmp-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(tmp+1,tmp+1+dn,a[i])-tmp;
	for(int i=1;i<=m;i++){
		if(q[i].op==2) q[i].r=lower_bound(tmp+1,tmp+1+dn,q[i].r)-tmp;
	}
	for(int i=1;i<=n;i++) update(i,a[i],1);
	for(int i=1;i<=m;i++){
		if(q[i].op==1) printf("%d\n",query(q[i].l,q[i].r,q[i].k));
		else{
			int x=q[i].l,y=q[i].r;
			update(x,a[x],-1);
			a[x]=y;
			update(x,a[x],1);
		}
	}
}
