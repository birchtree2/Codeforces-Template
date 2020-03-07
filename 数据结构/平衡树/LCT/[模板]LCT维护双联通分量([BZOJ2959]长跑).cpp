#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 750000
using namespace std;
int n,m;
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


struct LCT{
#define fa(x) (tree[x].fa)
#define lson(x) (tree[x].ch[0])
#define rson(x) (tree[x].ch[1])
	struct node{
		int ch[2];
		int fa;
		int revm;
		int val;
		int sum;
	}tree[maxn+5];
	int bel[maxn+5];
	//并查集维护双连通分量关系,这里不能直接用Splay的fa(虽然也要存储);
	//选联通分量中的一个节点作为代表节点 
	//LCT模板里的fa(x)用find_bel(fa(x))代替,相当于每次跳到fa(x)所在e-DCC的代表节点 
	//如果两个点的fa不相等，则说明不在一个e-DCC中 
	int find_bel(int x){
		if(bel[x]==x) return x;
		else return bel[x]=find_bel(bel[x]);
	} 
	int con_id[maxn+5]; //并查集维护连通性
	int find_con(int x){
		if(con_id[x]==x) return x;
		else return con_id[x]=find_con(con_id[x]);
	}
	void merge_con(int x,int y){
		con_id[find_con(x)]=find_con(y);
	}
	
	void push_up(int x){
		tree[x].sum=tree[lson(x)].sum+tree[rson(x)].sum+tree[x].val;
	}
	inline bool is_root(int x){
		return !(lson(find_bel(fa(x)))==x||rson(find_bel(fa(x)))==x);
	}
	int check(int x){
		return rson(find_bel(fa(x)))==x;
	}
	void reverse(int x){
		swap(lson(x),rson(x));
		tree[x].revm^=1;
	}
	void push_down(int x){
		if(tree[x].revm){
			reverse(lson(x));
			reverse(rson(x));
			tree[x].revm=0;
		}
	}
	void push_down_all(int x){
		if(!is_root(x)) push_down_all(find_bel(fa(x)));
		push_down(x);
	}
	void rotate(int x){
		int y=find_bel(fa(x)),z=find_bel(fa(y)),k=check(x),w=tree[x].ch[k^1];
		tree[y].ch[k]=w;
		tree[w].fa=y;
		if(!is_root(y)) tree[z].ch[check(y)]=x;
		tree[x].fa=z;
		tree[x].ch[k^1]=y;
		tree[y].fa=x;
		push_up(y);
		push_up(x);
	}
	void splay(int x){
		push_down_all(x);
		while(!is_root(x)){
			int y=find_bel(fa(x));
			if(!is_root(y)){
				if(check(x)==check(y)) rotate(y);
				else rotate(x);
			}
			rotate(x);
		}
		push_up(x);
	}
	void access(int x){
		for(int y=0;x;y=x,x=find_bel(fa(x))){
			splay(x);
			rson(x)=y;
			push_up(x);
		}
	}
	void make_root(int x){
		access(x);
		splay(x);
		reverse(x);
	}
	void split(int x,int y){
		make_root(x);
		access(y);
		splay(y);
	}
	void link(int x,int y){
		make_root(x);
		fa(x)=y;
	}
	void cut(int x,int y){
		split(x,y);
		fa(x)=lson(y)=0;
		push_up(y);
	}

	void update_val(int x,int val){
		make_root(x);
		tree[x].val+=val;
		tree[x].sum+=val;
	}
	void dfs_tree(int x,int y){
		bel[x]=y;
		push_down(x);
		if(lson(x)) dfs_tree(lson(x),y);
		if(rson(x)) dfs_tree(rson(x),y);
	}
	void shrink(int x,int y){
		split(x,y);
		tree[y].val=tree[y].sum;//一个点y相当于整个联通块 
		dfs_tree(y,y);//把这棵树(整个联通块)里的节点全部指向y 
		lson(y)=0;
	}
	int query_sum(int x,int y){
		split(x,y);
		return tree[y].sum;
	}
}T;



//int bel[maxn+5];
int a[maxn+5];
int main(){
//#ifdef LOCAL
//	freopen("1.in","r",stdin);
//	freopen("1.ans","w",stdout);
//#endif
	int type,x,y;
	qread(n);
	qread(m);
	for(int i=1;i<=n;i++){
		qread(a[i]); 
		T.tree[i].val=a[i];
		T.bel[i]=T.con_id[i]=i;
	}
//	for(int i=1;i<=n;i++) bel[i]=i;

	for(int i=1;i<=m;i++){
		qread(type);
		qread(x);
		qread(y);
		if(type==1){
			int fx=T.find_bel(x);
			int fy=T.find_bel(y);
			if(fx!=fy){//不在一个e-DCC中 
				if(T.find_con(fx)!=T.find_con(fy)){//不连通,直接连边 
					T.link(fx,fy);
					T.merge_con(fx,fy); 
				}else{//缩点 
					T.shrink(fx,fy);
				}
			}

		}else if(type==2){
			int fx=T.find_bel(x);
			T.update_val(fx,y-a[x]);
			a[x]=y;
		}else{
			int fx=T.find_bel(x);
			int fy=T.find_bel(y);
			if(T.find_con(fx)==T.find_con(fy)) qprint(T.query_sum(fx,fy));
			else qprint(-1);
			putchar('\n');
		}
	}
}
