#include<iostream>
#include<cstdio>
#include<cstdlib>
#define maxn 500000
#define maxlogn 30
#define INF 0x7fffffff 
using namespace std;
template<typename T> inline void qread(T &x) {
	x=0;
	T sign=1;
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
template<typename T> void qprint(T x) {
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

struct fhq_treap {
#define lson(x) (tree[x].ls)
#define rson(x) (tree[x].rs)
	struct node {
		int ls;
		int rs;
		int sz;
		int val;
		int dat;
	} tree[maxn*maxlogn+5];
	int ptr;
	int root=0;
	int New(int val) {
		ptr++;
		tree[ptr].sz=1;
		tree[ptr].val=val;
		tree[ptr].dat=rand();
		return ptr;
	}
	int copy(int last){
		int x=++ptr;
		tree[x]=tree[last];
		return x;
	}
	void push_up(int x) {
		tree[x].sz=tree[lson(x)].sz+1+tree[rson(x)].sz;
	}
	int merge(int x,int y) {
		if(!x||!y) return x+y;
		if(tree[x].dat<tree[y].dat) {
//			y=copy(y);
			lson(y)=merge(x,lson(y));
			push_up(y);
			return y;
		} else {
//			x=copy(x);
			rson(x)=merge(rson(x),y);
			push_up(x);
			return x;
		}
	}
	void split(int now,int k,int &x,int &y) { //按值域split
		if(now==0) {
			x=y=0;
			return;
		}
		if(tree[now].val<=k) {
			x=copy(now);
			split(rson(now),k,rson(x),y);
			push_up(x);
		} else {
			y=copy(now);
			split(lson(now),k,x,lson(y));
			push_up(y);//小心这里不能push_up(now),要分开pushup新的节点 
		}
	}
	int get_kth(int x,int k) {
		if(tree[lson(x)].sz+1==k) return x;
		else if(k<=tree[lson(x)].sz) return get_kth(lson(x),k);
		else return get_kth(rson(x),k-tree[lson(x)].sz-1);
	}
	void insert(int &root,int val) {
		int x,y;
		split(root,val,x,y);
		root=merge(merge(x,New(val)),y);
	}
	void del(int &root,int val) {
		int x,y,z;
		split(root,val,y,z);
		split(y,val-1,x,y);
		y=merge(lson(y),rson(y));
		root=merge(merge(x,y),z);
	}
	//注意查询操作split会导致树节点的复制,
	//虽然split和merge之后形态不变, 但是节点编号变成新的了,所以要返回新的节点 
	int get_rank(int &root,int val) {
		int x,y;
		split(root,val-1,x,y);
		int ans=tree[x].sz+1;
		root=merge(x,y);
		return ans;
	}
	int get_val(int &root,int rk) {
		return tree[get_kth(root,rk)].val;
	}
	int get_pre(int &root,int val) {
		int x,y,ans;
		split(root,val-1,x,y);
		if(x==0) ans=-INF;
		else ans=tree[get_kth(x,tree[x].sz)].val;
		root=merge(x,y);
		return ans;
	}
	int get_nex(int &root,int val) {//
		int x,y,ans;
		split(root,val,x,y);
		if(y==0) ans=INF;
		else ans=tree[get_kth(y,1)].val;
		root=merge(x,y);
		return ans;
	}
} T;

int m;
int root[maxn+5];
int main() {
	int ver,opt,x;
	int last;
	qread(m);
	for(int i=1; i<=m; i++) {
		qread(ver);
		qread(opt);
		qread(x);
		root[i]=root[ver];
		if(opt==1) {
			T.insert(root[i],x);
		} else if(opt==2) {
			T.del(root[i],x);
		} else if(opt==3) {
			last=T.get_rank(root[i],x);
			qprint(last);
			putchar('\n');
		} else if(opt==4) {
			last=T.get_val(root[i],x);
			qprint(last);
			putchar('\n');
		} else if(opt==5) {
			last=T.get_pre(root[i],x);
			qprint(last);
			putchar('\n');
		} else {
			last=T.get_nex(root[i],x);
			qprint(last);
			putchar('\n');
		}
	}
}

