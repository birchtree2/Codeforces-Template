#include<iostream>
#include<cstdio>
#include<cstring> 
#include<algorithm>
#define maxn 200005
#define maxm 200005
#define maxlogn 18
using namespace std;
int n,q;
struct node{
	int ls;
	int rs;
	int cnt;
}tree[maxm*maxlogn];
int root[maxn];
int ptr;
void push_up(int x){
	tree[x].cnt=tree[tree[x].ls].cnt+tree[tree[x].rs].cnt;
}
void build(int &x,int l,int r){
	if(!x) x=++ptr;
	if(l==r){
		tree[x].cnt=0;
		return;
	}
	int mid=(l+r)>>1;
	build(tree[x].ls,l,mid);
	build(tree[x].rs,mid+1,r);
	push_up(x);
//	printf("%d [%d,%d] cnt=%d ls=%d rs=%d\n",x,l,r,tree[x].cnt,tree[x].ls,tree[x].rs);
} 
void update(int &x,int upos,int last,int l,int r){
	x=++ptr;//每一次都要新建一个副本！！！ 
	tree[x]=tree[last];
	if(l==r){
		tree[x].cnt++;
		return;
	}	
	int mid=(l+r)>>1;
	if(upos<=mid) update(tree[x].ls,upos,tree[last].ls,l,mid);
	else update(tree[x].rs,upos,tree[last].rs,mid+1,r);
	push_up(x);
//	printf("%d [%d,%d] cnt=%d ls=%d rs=%d\n",x,l,r,tree[x].cnt,tree[x].ls,tree[x].rs);
}
int query(int p,int q,int qk,int l,int r){
	if(l==r) return l;
	int mid=(l+r)>>1;
	int lcnt=tree[tree[p].ls].cnt-tree[tree[q].ls].cnt;
	if(qk<=lcnt) return query(tree[p].ls,tree[q].ls,qk,l,mid);
	else return query(tree[p].rs,tree[q].rs,qk-lcnt,mid+1,r);
}

int a[maxn];
int b[maxn]; 
int dn;
int da[maxn];

int main(){
	int l,r,k;
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	dn=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+dn,a[i])-b;
	build(root[0],1,dn);
	for(int i=1;i<=n;i++){
		update(root[i],a[i],root[i-1],1,dn);
	}
	for(int i=1;i<=q;i++){
		scanf("%d %d %d",&l,&r,&k);
		printf("%d\n",b[query(root[r],root[l-1],k,1,dn)]);
	}
}

