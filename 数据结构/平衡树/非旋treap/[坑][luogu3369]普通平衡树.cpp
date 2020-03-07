//https://www.cnblogs.com/elpsycongroo/p/10371406.html
#include<iostream>
#include<cstdio>
#includ<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
struct fhq_treap {
	struct node {
		int ls;
		int rs;
		int val;
		int sz;
		int dat;
	};
	int merge(int x,int y) {
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
		if(k<=tree[now].val){
			y=now;
			split(lson(now),k,x,tree[y].ls);
		}else{
			x=now;
			split(rson(now),k,tree[x].rs,y);
		}
		push_up(now);
	}
	void split_2(int now,int k,int &x,int &y){
		if(now==0){
			x=y=0;
			return;
		}
		if(k<=tree[lson(now)].sz){
			y=now;
			split(lson(now),k,x,tree[y].ls); 
		}else{
			x=now;
			split(rson(now),k-tree[lson(now)].sz-1,tree[x].rs,y); 
		} 
		push_up(now);
	}
};

int main() {

}

