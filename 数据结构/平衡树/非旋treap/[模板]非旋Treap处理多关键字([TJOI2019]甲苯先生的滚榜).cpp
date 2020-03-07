#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 1000000
using namespace std;
typedef unsigned int ui ;
inline void qread(ui &x){
	x=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
}
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
		putchar('0'+x%10);
	}
}

int cas;
int n,m;
ui seed;
ui randNum( ui& seed , ui last , const ui m){ 
    seed = seed * 17 + last ; return seed % m + 1; 
}

struct mem_pool{
	int stk[maxn+5];
	int top;
	int New(){
		return stk[top--];
	} 
	void Del(int x){
		stk[++top]=x;
	}
	void ini(int sz){
		for(int i=sz;i>=1;i--) Del(i); 
	} 
}pool; 

struct val_type{
	int tim;
	int cnt;
	int id;
	val_type(){
		
	}
	val_type(int _cnt,int _tim,int _id){
		cnt=_cnt;
		tim=_tim;
		id=_id;
	}
	friend bool operator < (val_type p,val_type q){
		if(p.cnt==q.cnt){
			if(p.tim==q.tim) return p.id<q.id;
			else return p.tim<q.tim;
		}else return p.cnt>q.cnt;
	}
	friend bool operator == (val_type p,val_type q){
		return p.cnt==q.cnt&&p.tim==q.tim&&p.id==q.id;
	} 
};
struct fhq_treap{
#define lson(x) (tree[x].ls)
#define rson(x) (tree[x].rs)
	struct node{
		int ls;
		int rs;
		int sz;
		int dat;
		val_type val;
	}tree[maxn+5];
	int ptr;
	int root;
	void push_up(int x){
		tree[x].sz=tree[lson(x)].sz+tree[rson(x)].sz+1;	
	}
	int New(val_type val){
		int x=pool.New();
		tree[x].ls=tree[x].rs=0;
		tree[x].sz=1;
		tree[x].dat=rand();
		tree[x].val=val;
		return x;
	} 
	int merge(int x,int y){
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
	void split(int now,val_type val,int &x,int &y){
		if(now==0){
			x=y=0;
			return;
		}
		if(val<tree[now].val||val==tree[now].val){
			y=now;
			split(lson(now),val,x,tree[y].ls);
		}else{
			x=now;
			split(rson(now),val,tree[x].rs,y);
		}
		push_up(now);
	}
	void insert(val_type val){
		int x,y;
		split(root,val,x,y);
		root=merge(merge(x,New(val)),y);
	}
	void del(val_type val){
		int x,y,z;
		split(root,val,x,y);
		split(y,val_type(val.cnt,val.tim,val.id+1),y,z);
		root=merge(x,z);
		pool.Del(y);
	} 
	int query(val_type val){
		int x,y;
		split(root,val_type(val.cnt,val.tim,0),x,y);
		int ans=tree[x].sz;
		root=merge(x,y);
		return ans;
	}
	void del_tree(int x){
		if(x==0) return;
		del_tree(lson(x));
		del_tree(rson(x));
		pool.Del(x);
	}
	void clear(){
		del_tree(root);
		root=0;
	}
}T; 

int last=7;
val_type a[maxn+5];
int main(){
	qread(cas);
	pool.ini(maxn); 
	while(cas--){
		T.clear(); 
		qread(n);
		qread(m);
		qread(seed);
		for(int i=1;i<=n;i++){
			a[i]=val_type(0,0,i);
			T.insert(a[i]); 
		} 
		for(int i=1;i<=m;i++){
			int Ria=randNum(seed,last,n);
			int Rib=randNum(seed,last,n);
//			printf("db:%d %d\n",Ria,Rib);
			T.del(a[Ria]);
			a[Ria].cnt++;
			a[Ria].tim+=Rib;
			T.insert(a[Ria]);
			last=T.query(a[Ria]);
			qprint(last);
			putchar('\n');
		}
	}
}
