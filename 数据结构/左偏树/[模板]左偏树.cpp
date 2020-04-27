#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100000
using namespace std;
struct leftist_tree{
#define lson(x) (tree[x].ls)
#define rson(x) (tree[x].rs)
	struct node{
		int ls;
		int rs;
		int val;
		int dis;
	}tree[maxn+5];
	int rt[maxn+5];
	bool del[maxn+5];
	int find(int x){
		if(rt[x]==x) return x;
		else return rt[x]=find(rt[x]);
	}
	int merge(int x,int y){
		if(!x||!y) return x+y;
		if(tree[x].val>tree[y].val) swap(x,y);
		rson(x)=merge(rson(x),y);
		if(tree[lson(x)].dis<tree[rson(x)].dis) swap(lson(x),rson(x));
		tree[x].dis=tree[rson(x)].dis+1;
		return x;
	}
	void link(int x,int y){
		if(del[x]||del[y]) return;
		x=find(x);
		y=find(y);
		if(x!=y) rt[x]=rt[y]=merge(rt[x],rt[y]);
	}
	int erase(int x){
		if(del[x]) return -1;
		x=find(x);
		int ans=tree[x].val;
		del[x]=1;
		rt[lson(x)]=rt[rson(x)]=rt[x]=merge(lson(x),rson(x));
		//注意更新rt[x],这样查询和x在同一个堆里的节点的rt才不会错,rt[x]在这里起到了跳板作用 
		lson(x)=rson(x)=0;
		return ans; 
	}
	void ini(int *a,int n){
		for(int i=1;i<=n;i++){
			tree[i].val=a[i];
			rt[i]=i;
		}
	}
}T;
int n,m;
int a[maxn+5];
int main(){
	int x,y,cmd;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	T.ini(a,n);
	for(int i=1;i<=m;i++){
		scanf("%d",&cmd);
		if(cmd==1){
			scanf("%d %d",&x,&y);
			T.link(x,y);
		}else{
			scanf("%d",&x);
			printf("%d\n",T.erase(x));
		}
	}
}

