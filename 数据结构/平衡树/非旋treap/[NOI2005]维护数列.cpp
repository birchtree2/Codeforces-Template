#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib> 
#define maxn 500000
using namespace std;
inline void qread(int &x){
	x=0;
	int sign=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') sign=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar(); 
	}
	x=x*sign;
} 
inline void qprint(int x){
	if(x<0){
		putchar('-');
		qprint(-x);
	}else if(x==0){
		putchar('0');
		return;
	}else{
		if(x>=10) qprint(x/10);
		putchar(x%10+'0');
	}
}

struct mem_pool{
	int top;
	int stk[maxn+5];
	int New(){
		return stk[top--];	
	}
	void Del(int x){
		stk[++top]=x;
	}
	void ini(int n){
		top=n;
		for(int i=1;i<=n;i++) stk[n-i+1]=i;
	}
}pool;

inline int frandom() {
	static int seed=131;
	seed=int(seed*48271LL%2147483647);
	return seed;
}
struct fhq_treap{
#define lson(x) (tree[x].ls)
#define rson(x) (tree[x].rs) 
//protected:
	struct node{
		int ls;
		int rs;
		int sz;
		int dat;
		int val;
		int sum;
		int lsum;
		int rsum;
		int maxsum;
		bool revm;
		bool is_set;//是否被赋值,因为setm可能为0 
		int setm;
	}tree[maxn+5];
	int root;
	int New(int val){
		int ptr=pool.New();
		tree[ptr].ls=tree[ptr].rs=0;
		tree[ptr].sz=1;
		tree[ptr].val=val;
		tree[ptr].dat=rand();
//		tree[ptr].dat=frandom();
		tree[ptr].sum=val;
		tree[ptr].lsum=tree[ptr].rsum=max(0,val);
		tree[ptr].maxsum=val;//子段不能为空 
		tree[ptr].revm=0;
		tree[ptr].is_set=0;
		tree[ptr].setm=0;
		return ptr;
	}
	void push_up(int x){
//		if(x==0) return;
		tree[x].sz=tree[lson(x)].sz+tree[rson(x)].sz+1;
		tree[x].sum=tree[lson(x)].sum+tree[rson(x)].sum+tree[x].val;
		tree[x].lsum=max(max(tree[lson(x)].lsum,tree[lson(x)].sum+tree[x].val+tree[rson(x)].lsum),0);
		tree[x].rsum=max(max(tree[rson(x)].rsum,tree[rson(x)].sum+tree[x].val+tree[lson(x)].rsum),0);
		tree[x].maxsum=max(tree[x].val,tree[lson(x)].rsum+tree[x].val+tree[rson(x)].lsum);
		if(lson(x)) tree[x].maxsum=max(tree[x].maxsum,tree[lson(x)].maxsum);//防止lson(x)=0时和0取max，导致取的子段是空的
		if(rson(x)) tree[x].maxsum=max(tree[x].maxsum,tree[rson(x)].maxsum); 
	}
	void reverse(int x){
		swap(tree[x].lsum,tree[x].rsum);//交换子段
		swap(tree[x].ls,tree[x].rs); 
		tree[x].revm^=1;
	}
	void set_val(int x,int val){
		tree[x].val=val;
		tree[x].setm=val;
		tree[x].is_set=1;
		tree[x].sum=val*tree[x].sz;
		tree[x].lsum=tree[x].rsum=max(0,tree[x].sz*val);
		tree[x].maxsum=max(val,tree[x].sz*val);//不能为空，必须选1个 
	}
	void push_down(int x){
//		if(x==0) return;
		if(tree[x].revm){
			reverse(lson(x));
			reverse(rson(x));
			tree[x].revm=0;
		}
		if(tree[x].is_set){
			set_val(lson(x),tree[x].setm);
			set_val(rson(x),tree[x].setm);
			tree[x].is_set=0;
			tree[x].setm=0;
		}
	}
	int merge(int x,int y){
		push_down(x);
		push_down(y);
		if(!x||!y) return x+y;
		if(tree[x].dat<tree[y].dat){
			tree[x].rs=merge(tree[x].rs,y);
			push_up(x);
			return x;
		}else{
			tree[y].ls=merge(x,tree[y].ls);
			push_up(y);
			return y;
		}
	}
	void split(int now,int k,int &x,int &y){
		if(now==0){
			x=y=0;
			return;
		}
		push_down(now);
		if(k<=tree[lson(now)].sz){
			y=now;
			split(lson(now),k,x,lson(y));
		}else{
			x=now;
			split(rson(now),k-tree[lson(now)].sz-1,rson(x),y);
		}
		push_up(now);
	}
	int build_tree(int l,int r,int *a){
		if(l==r){
			return New(a[l]);
		}
		int mid=(l+r)>>1;
		int ls=build_tree(l,mid,a);
		int rs=build_tree(mid+1,r,a);
		int x=merge(ls,rs);
//		push_up(x);
		return x;
	} 
	void del_tree(int x){
		if(x==0) return;
		pool.Del(x);
		del_tree(lson(x));
		del_tree(rson(x));
	}
//public:
	void Insert(int pos,int tot,int *c){
		int x,y,z;
		split(root,pos,x,y);
		z=build_tree(1,tot,c);
		root=merge(merge(x,z),y);
	} 
	void Delete(int pos,int tot){
		int x,y,z;
		split(root,pos+tot-1,y,z);
		split(y,pos-1,x,y);
		del_tree(y);
		root=merge(x,z);
	}
	void Make_same(int pos,int tot,int c){
		int x,y,z;
		split(root,pos+tot-1,y,z);
		split(y,pos-1,x,y);
		set_val(y,c);
		root=merge(merge(x,y),z);
	}
	void Reverse(int pos,int tot){
		int x,y,z;
		split(root,pos+tot-1,y,z);
		split(y,pos-1,x,y);
		reverse(y);
		root=merge(merge(x,y),z);
	}
	int Get_sum(int pos,int tot){
		int x,y,z;
		split(root,pos+tot-1,y,z);
		split(y,pos-1,x,y);
		int ans=tree[y].sum;
		root=merge(merge(x,y),z);
		return ans;
	}
	int Max_sum(){
		return tree[root].maxsum;
	}
#undef lson
#undef rson
}T;

int n,m;
int a[maxn+5];
int main(){
	char cmd[10];
	int pos,tot,c;
	pool.ini(maxn);
	qread(n);
	qread(m);
//	int sum=0;
	for(int i=1;i<=n;i++){
		qread(a[i]);
//		sum+=a[i];
	}
//	printf("%d\n",sum);
	T.Insert(0,n,a);
//	T.root=T.build_tree(1,n,a);
	for(int i=1;i<=m;i++){
		scanf("%s",cmd);
		if(cmd[0]=='I'){
			qread(pos);
			qread(tot);
			for(int j=1;j<=tot;j++) qread(a[j]);
			T.Insert(pos,tot,a); 
		}else if(cmd[0]=='D'){
			qread(pos);
			qread(tot);
			T.Delete(pos,tot);
		}else if(cmd[0]=='M'&&cmd[2]=='K'){
			qread(pos);
			qread(tot);
			qread(c);
			T.Make_same(pos,tot,c);
		}else if(cmd[0]=='R'){
			qread(pos);
			qread(tot);
			T.Reverse(pos,tot);
		}else if(cmd[0]=='G'){
			qread(pos);
			qread(tot);
			qprint(T.Get_sum(pos,tot));
			putchar('\n');
		}else if(cmd[0]=='M'&&cmd[2]=='X'){
			qprint(T.Max_sum());
			putchar('\n');
		}
	}
	
}

