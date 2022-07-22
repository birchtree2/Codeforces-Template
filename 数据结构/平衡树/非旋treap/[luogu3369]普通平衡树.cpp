#include<iostream>
#include<cstdio>
#include<cstdlib>
#define maxn 100000
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
	} tree[maxn+5];
	int ptr;
	int root=0;
	int New(int val) {
		ptr++;
		tree[ptr].sz=1;
		tree[ptr].val=val;
		tree[ptr].dat=rand();
		return ptr;
	}
	void push_up(int x) {
		tree[x].sz=tree[lson(x)].sz+1+tree[rson(x)].sz;
	}
	int merge(int x,int y) {
		if(!x||!y) return x+y;
		if(tree[x].dat<tree[y].dat) {
			lson(y)=merge(x,lson(y));
			push_up(y);
			return y;
		} else {
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
			x=now;
			split(rson(now),k,rson(x),y);
		} else {
			y=now;
			split(lson(now),k,x,lson(y));
		}
		push_up(now);
	}
	int get_kth(int x,int k) {
		if(tree[lson(x)].sz+1==k) return x;
		else if(k<=tree[lson(x)].sz) return get_kth(lson(x),k);
		else return get_kth(rson(x),k-tree[lson(x)].sz-1);
	}
	void insert(int val) {
		int x,y;
		split(root,val,x,y);
		root=merge(merge(x,New(val)),y);
	}
	void del(int val) {
		int x,y,z;
		split(root,val,y,z);
		split(y,val-1,x,y);
//		root=merge(merge(x,y)); 这样会删除全部值为val的
		y=merge(lson(y),rson(y));//这样只删除一个
		root=merge(merge(x,y),z);
	}
	int get_rank(int val) {
		int x,y;
		split(root,val-1,x,y);
		int ans=tree[x].sz+1;
		root=merge(x,y);
		return ans;
	}
	int get_val(int rk) {
		return tree[get_kth(root,rk)].val;
	}
	int get_pre(int val) {
		int x,y;
		split(root,val-1,x,y);
		int ans=tree[get_kth(x,tree[x].sz)].val;
		root=merge(x,y);
		return ans;
	}
	int get_nex(int val) {
		int x,y;
		split(root,val,x,y);
		int ans=tree[get_kth(y,1)].val;
		root=merge(x,y);
		return ans;
	}
} T;

int n,m;
int main() {
	int opt,x;
	qread(m);
	for(int i=1; i<=m; i++) {
		qread(opt);
		qread(x);
		if(opt==1) {
			T.insert(x);
		} else if(opt==2) {
			T.del(x);
		} else if(opt==3) {
			qprint(T.get_rank(x));
			putchar('\n');
		} else if(opt==4) {
			qprint(T.get_val(x));
			putchar('\n');
		} else if(opt==5) {
			qprint(T.get_pre(x));
			putchar('\n');
		} else {
			qprint(T.get_nex(x));
			putchar('\n');
		}
//		printf("ok %d\n",opt);
	}
}

