#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100005
#define lson tree[p].l
#define rson tree[p].r
#define INF 0x7fffffff
using namespace std;
int n;
inline int frandom() {
	static int seed=131;
	return seed=int(seed*48271LL%2147483647);
}


struct node {
	int l;
	int r;
	int val;
	int dat;
	int cnt;
	int size;
} tree[maxn];
int tot=0;
int root;
void update(int p) {
	tree[p].size=tree[lson].size+tree[rson].size+tree[p].cnt;
}

void zig(int &p) {
	int q=tree[p].l;
	tree[p].l=tree[q].r;
	tree[q].r=p;
	p=q;
	update(tree[p].r);
	update(p);
}

void zag(int &p) {
	int q=tree[p].r;
	tree[p].r=tree[q].l;
	tree[q].l=p;
	p=q;
	update(tree[p].l);
	update(p);
}

int New(int val) {
	tree[++tot].val=val;
	tree[tot].dat=frandom();
	tree[tot].cnt=1;
	tree[tot].size=1;
	return tot;
}

void build() {
	New(-INF);
	New(INF);
	root=1;
	tree[1].r=2;
	update(root);
}

void insert(int &p,int val) {
	if(p==0) {
		p=New(val);
		return;
	}
	if(val==tree[p].val) {
		tree[p].cnt++;
		update(p);
		return;
	}
	if(val<tree[p].val) {
		insert(lson,val);
		if(tree[lson].dat>tree[p].dat) zig(p);
	} else {
		insert(rson,val);
		if(tree[rson].dat>tree[p].dat) zag(p);
	}
	update(p);
}

int get_rank_by_val(int p,int val) {
	if(p==0) return 0;
	if(val==tree[p].val) {
		return tree[lson].size+1;
	}
	if(val<tree[p].val) {
		return get_rank_by_val(lson,val);
	}
	return get_rank_by_val(rson,val)+tree[lson].size+tree[p].cnt;
}

int get_val_by_rank(int p,int rank) {
	if(p==0) return INF;
	if(tree[lson].size>=rank) {
		return get_val_by_rank(lson,rank);
	}
	if(tree[lson].size+tree[p].cnt>=rank) return tree[p].val;
	return get_val_by_rank(rson,rank-tree[p].cnt-tree[lson].size);
}

int get_pre(int val) {
	int ans=1;
	int p=root;
	while(p) {
		if(val==tree[p].val) {
			if(tree[p].l>0) {
				p=tree[p].l;
				while(tree[p].r>0) p=tree[p].r;
				ans=p;
			}
			break;
		}
		if(tree[p].val<val&&tree[p].val>tree[ans].val) ans=p;
		if(val<tree[p].val) p=lson;
		else p=rson;
	}
	return tree[ans].val;
}

int get_next(int val) {
	int ans=2;
	int p=root;
	while(p) {
		if(val==tree[p].val) {
			if(tree[p].r>0) {
				p=tree[p].r;
				while(tree[p].l>0) p=tree[p].l;
				ans=p;
			}
			break;
		}
		if(tree[p].val>val&&tree[p].val<tree[ans].val) ans=p;
		if(val<tree[p].val) p=lson;
		else p=rson;
	}
	return tree[ans].val;
}

void del(int &p,int val) {
	if(p==0) return;
	if(val==tree[p].val) {
		if(tree[p].cnt>1) {
			tree[p].cnt--;
			update(p);
			return;
		}
		if(tree[p].l||tree[p].r) {
			if(tree[p].r==0||tree[lson].dat>tree[rson].dat) {
				zig(p);
				del(rson,val);
			} else {
				zag(p);
				del(lson,val);
			}
			update(p);
		} else p=0;
		return;

	}
	if(val<tree[p].val) del(lson,val);
	else del(rson,val);
	update(p);
}

int main() {
//	freopen("7.in","r",stdin);
	build();
	scanf("%d",&n);
	int opt,x;
	while(n--) {
		scanf("%d %d",&opt,&x);
//		if(opt>=3)printf("opt=%d ",opt);
		switch(opt) {
			case(1): {
				insert(root,x);
				break;
			}
			case(2): {
				del(root,x);
				break;
			}
			case(3): {
				printf("%d\n",get_rank_by_val(root,x)-1);
				break;
			}
			case(4): {
				printf("%d\n",get_val_by_rank(root,x+1));
				break;
			}
			case(5): {
				printf("%d\n",get_pre(x));
				break;
			}
			case(6): {
				printf("%d\n",get_next(x));
				break;
			}
			default: {
				break;
			}
		}
	}
}
