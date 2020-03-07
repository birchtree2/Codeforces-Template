#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100000 
using namespace std;
struct memory_pool {//内存池 
	int tot=0;
	int p[maxn+5];
	void ini(int n) {
		tot=0;
		for(int i=n; i>=1; i--) p[++tot]=i;
	}
	inline void Free(int x) {
		p[++tot]=x;
	}
	inline int New() {
		return p[tot--];
	}
} pool;

struct SGT {
#define lson(x) (tree[x].ls)
#define rson(x) (tree[x].rs)
#define alpha 0.75
	struct node {
		int ls;
		int rs;
		int exist;//是否存在 
		int val;
		int sz;//包括已被删除节点的大小
		int asz;//真实大小
	} tree[maxn+5];
	int root;
	void push_up(int x) {
		tree[x].sz=tree[lson(x)].sz+tree[rson(x)].sz+1;
		tree[x].asz=tree[lson(x)].asz+tree[rson(x)].asz+tree[x].exist;
	}
	bool is_balance(int x){
		return (double)tree[x].asz*alpha>max(tree[lson(x)].asz,tree[rson(x)].asz);
	}
	
	int cnt=0;
	int seq[maxn+5];
	void get_seq(int x){//得到中序遍历 
		if(x==0) return;
		get_seq(lson(x));
		if(tree[x].exist) seq[++cnt]=x;
		else pool.Free(x);
		get_seq(rson(x));
	}
	void _build(int &x,int l,int r){
		int mid=(l+r)>>1;
		x=seq[mid];
		if(l==r){
			tree[x].ls=tree[x].rs=0;
			tree[x].sz=tree[x].asz=1;
			return;
		}
		if(l<mid)_build(tree[x].ls,l,mid-1);//注意是[l,mid-1]而不是[l,mid] 
		else tree[x].ls=0;
		if(mid<r) _build(tree[x].rs,mid+1,r);
		else tree[x].rs=0;
		push_up(x);
	}
	void rebuild(int &x){
		cnt=0;
		get_seq(x);
		if(cnt!=0) _build(x,1,cnt);
		else x=0;
	}
	
	void _insert(int &x,int val) {
		if(x==0) {//相同的数会被分成两个节点储存 
			x=pool.New();
			tree[x].ls=tree[x].rs=0;
			tree[x].val=val;
			tree[x].exist=1;
			tree[x].sz=tree[x].asz=1;
			return;
		}
//		tree[x].sz++;
//		tree[x].asz++;
		if(val<=tree[x].val) _insert(tree[x].ls,val);
		else _insert(tree[x].rs,val);
		push_up(x);
	}
	void check(int x,int val){//沿着插入节点的路径，检查插入节点后的树是否平衡 
		while(1){
			if(val<=tree[x].val){
				if(lson(x)==0) break;
				if(!is_balance(lson(x))){
					rebuild(lson(x));
					break;
				}
				x=lson(x);
			}else{
				if(rson(x)==0) break;
				if(!is_balance(rson(x))){
					rebuild(rson(x));
					break;
				}
				x=rson(x);
			}
		}
	}
	void insert(int val){
		int tmp=root;
		_insert(root,val);
		check(tmp,val);
	}
	
	int get_rank(int val){
		int x=root;
		int ans=1;
		while(x){
			if(val<=tree[x].val) x=lson(x);
			else{
				ans+=tree[lson(x)].asz+tree[x].exist;
				x=rson(x);
			}
		}
		return ans;
	}
	int get_val(int rank){
		int x=root;
		while(x){
			if(rank<=tree[lson(x)].asz) x=lson(x);
			else if(tree[x].exist&&tree[lson(x)].asz+tree[x].exist==rank) return tree[x].val;
			else{
				 rank-=tree[lson(x)].asz+tree[x].exist;
				 x=rson(x);
			}
		}
		return 0;
	}
	int get_pre(int val){
//		printf("%d\n",get_rank(val)-1);
		return get_val(get_rank(val)-1);
	}
	int get_nex(int val){
		return get_val(get_rank(val+1));
		//因为x可能有多个，不能写get_rank(val)+1 
	}
	
	void _del(int &x,int rank){
		if(tree[x].exist&&tree[lson(x)].asz+tree[x].exist==rank){
			tree[x].exist=0;
			tree[x].asz--;
			return;
		}
//		tree[x].asz--;
		if(rank<=tree[lson(x)].asz+tree[x].exist) _del(tree[x].ls,rank);
		else _del(tree[x].rs,rank-(tree[lson(x)].asz+tree[x].exist));
		push_up(x);
	}
	void del(int val){
		_del(root,get_rank(val));
		if((double)tree[root].sz*alpha>(double)tree[root].asz) rebuild(root);
	}
#undef lson
#undef rson
#undef alpha
}T;

int n;
int main() {
	int op,x;
	scanf("%d",&n);
	pool.ini(n);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&op,&x);
		if(op==1){
			T.insert(x);
		}else if(op==2){
			T.del(x);
		}else if(op==3){
			printf("%d\n",T.get_rank(x));
		}else if(op==4){
			printf("%d\n",T.get_val(x));
		}else if(op==5){
			printf("%d\n",T.get_pre(x));
		}else{
			printf("%d\n",T.get_nex(x));
		}
	}
}

