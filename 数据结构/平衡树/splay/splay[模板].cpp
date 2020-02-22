#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100005 
#define INF 0x3f3f3f3f
using namespace std;
struct Splay {
#define lson(x) tree[x].ch[0]
#define rson(x) tree[x].ch[1]
	struct node {
		int fa;
		int ch[2];
		int val;
		int sz;
		int cnt;
	} tree[maxn];
	int ptr;
	int root;
	void push_up(int x) {
		tree[x].sz=tree[x].cnt+tree[lson(x)].sz+tree[rson(x)].sz;
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

	void find(int val) { //找到最大的<=val的数并把它转到根
		if(!root) return;
		int cur=root;
		while(tree[cur].ch[val>tree[cur].val]&&val!=tree[cur].val) {
			cur=tree[cur].ch[val>tree[cur].val];
		}
		splay(cur);
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

	int get_val(int k) {
		int x=root;
		while(1) {
			if(lson(x)&&k<=tree[lson(x)].sz) {
				x=lson(x);
			} else if(k<=tree[lson(x)].sz+tree[x].cnt) {
				return tree[x].val;
			} else {
				k-=tree[lson(x)].sz+tree[x].cnt;
				x=rson(x);
			}
		}
		return 0;
	}

	int get_rank(int val) {
		find(val);
		return tree[lson(root)].sz+1;
	}

	int _pre(int val) { //注意返回的是位置而不是值
		find(val);
		if(tree[root].val<val) return root;
		int cur=lson(root);
		while(rson(cur)) {
			cur=rson(cur);
		}
		return cur;
	}
	int pre(int val) {
		return tree[_pre(val)].val;
	}
	
	int _nex(int val) {
		find(val);
		if(tree[root].val>val) return root;
		int cur=rson(root);
		while(lson(cur)) {
			cur=lson(cur);
		}
		return cur;
	}
	int nex(int val){
		return tree[_nex(val)].val;
	}
//	前驱splay到根，后继splay到前驱的右儿子，那么后继的左儿子就是要删除的点。
	void del(int val) {
		int pre=_pre(val),nex=_nex(val); 
		splay(pre);
		splay(nex,pre);
		int del=lson(rson(pre));
		if(tree[del].cnt>1){
			tree[del].cnt--;
			splay(del);
		}else lson(nex)=0; 
	}

}T;

int n;
int main() {
#ifdef FILE_IO
	freopen("input2.in","r",stdin);
#endif
	int opt,x;
	scanf("%d",&n);
	T.insert(-INF);
	T.insert(INF);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&opt,&x); 
//		printf("ok %d %d\n",opt,x);
		if(opt==4&&x==3){
			opt=4;
		}
		switch(opt){
			case(1):{
				T.insert(x);
				break;
			} 
			case(2):{
				T.del(x);
				break;
			}
			case(3):{
				printf("%d\n",T.get_rank(x)-1);
				break;
			}
			case(4):{
				printf("%d\n",T.get_val(x+1));
				break;
			} 
			case(5):{
				printf("%d\n",T.pre(x));
				break;
			}
			case(6):{
				printf("%d\n",T.nex(x));
				break;
			}
			default:{
				
				break;
			} 
		}
	}
}

