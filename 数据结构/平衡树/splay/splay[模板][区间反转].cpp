#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100005
#define INF 0x3f3f3f3f
using namespace std;
int n,m;
struct Splay {
#define lson(x) (tree[x].ch[0]) 
#define rson(x) (tree[x].ch[1])
	struct node {
		int fa;
		int ch[2];
		int val;
		int sz;
		int cnt;
		int mark;
	} tree[maxn];
	int ptr;
	int root;
	void push_up(int x) {
		tree[x].sz=tree[x].cnt+tree[lson(x)].sz+tree[rson(x)].sz;
	}
	void push_down(int x) {
		if(x&&tree[x].mark) {
//			printf("yes\n");
			tree[lson(x)].mark^=1;
			tree[rson(x)].mark^=1;
			swap(lson(x),rson(x));
			tree[x].mark=0;
		}
	}
	int chk(int x) { //判断x是左儿子还是右儿子
		return rson(tree[x].fa)==x;
	}
	int New(int val) {
		ptr++;
		tree[ptr].ch[0]=tree[ptr].ch[1]=0;
		tree[ptr].val=val;
		tree[ptr].cnt=tree[ptr].sz=1;
		return ptr;
	}
	void rotate(int x) { //把x旋转到父节点
		int y=tree[x].fa,z=tree[y].fa,k=chk(x),w=tree[x].ch[k^1];
		push_down(x);
		push_down(y);
		tree[y].ch[k]=w;
		tree[w].fa=y;
		tree[z].ch[chk(y)]=x;
		tree[x].fa=z;
		tree[x].ch[k^1]=y;
		tree[y].fa=x;
		push_up(y);
		push_up(x);
	}
	void splay(int x,int goal=0) { //把x转到goal的子节点，goal默认=0的时候转到根
		while(tree[x].fa!=goal) {
			int y=tree[x].fa;
			int z=tree[y].fa;
			if(z!=goal) {
				if(chk(x)==chk(y)) rotate(y);
				else rotate(x);
			}
			rotate(x);
		}
		if(!goal) root=x;
	}

	int get_val(int k) { //splay上按照树结构查询的第k大就是序列第k个节点
		int cur=root;
		while(1) {
			push_down(cur);
			if(k<=tree[lson(cur)].sz) cur=lson(cur);
			else if(k<=tree[lson(cur)].sz+tree[cur].cnt) return cur;//注意这里不能加cur!=0 
			else {
				k-=tree[lson(cur)].sz+tree[cur].cnt;
				cur=rson(cur);
			}
		}
	}

	void insert(int val) {
		int cur=root;
		int f=0;
		while(cur&&tree[cur].val!=val) {
			f=cur;
			cur=tree[cur].ch[val>tree[cur].val];
		}
		if(cur!=0) {
			tree[cur].cnt++;//不用push_up因为splay中已经pushup过了
		} else {
			cur=New(val);
			if(f) tree[f].ch[val>tree[f].val]=cur;
			tree[cur].fa=f;
		}
		splay(cur);
	}

	void reverse(int x,int y) {
		int l=x-1,r=y+1;
		l=get_val(l);
		r=get_val(r);
		splay(r);
		splay(l,r);
//		print(root);
//		printf("\n");
		tree[rson(lson(root))].mark^=1;//lson,rson别写反 
	}

	void print(int x) {
		push_down(x);
		if(x==0) return;
		print(lson(x));
		if(tree[x].val>=1&&tree[x].val<=n) printf("%d ",tree[x].val);
//		printf("%d ",tree[x].val);
		print(rson(x));
	}

} T;


int main() {
	int l,r;
	scanf("%d %d",&n,&m);
	T.insert(-INF);
	T.insert(INF);
	for(int i=1; i<=n; i++) {
		T.insert(i);
//		T.print(T.root);
//		printf("\n");
	}
//	T.print(T.root);
//		printf("\n");
	for(int i=1; i<=m; i++) {
		scanf("%d %d",&l,&r);
		T.reverse(l+1,r+1);
//		T.print(T.root);
//		printf("\n");
	}
	T.print(T.root);
}

