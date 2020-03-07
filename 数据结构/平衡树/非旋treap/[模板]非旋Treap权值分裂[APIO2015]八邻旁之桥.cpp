#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define maxn 200000
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
int k,n;
struct route {
	ll s;
	ll t;
	int type1;
	int type2;
	friend bool operator < (route p,route q){
		return p.s+p.t<q.s+q.t;
	}
} a[maxn+5];

namespace k_1 {
	ll tmp[maxn*2+5];
	ll calc(int mid) {
		ll ans=0;
		for(int i=1; i<=n; i++) {
			if(a[i].type1==a[i].type2) continue;
			ans+=abs(a[i].s-mid)+abs(a[i].t-mid);
		}
		return ans;
	}
	void solve() {
		int cnt=0,sz=0;
		ll ans=0,sum=0;
		for(int i=1; i<=n; i++) {
			if(a[i].type1==a[i].type2) {
				ans+=abs(a[i].s-a[i].t);
			} else {
				cnt++;
				tmp[++sz]=a[i].s;
				tmp[++sz]=a[i].t;
			}
		}
		sort(tmp+1,tmp+1+sz);
		if(sz%2==1) {
			sum=calc(tmp[sz/2+1]);
		} else {
			sum=min(calc(tmp[sz/2]),calc(tmp[sz/2+1]));
		}
		ans+=sum;
		ans+=cnt;
		printf("%lld\n",ans);
	}
}

namespace k_2 {
	struct fhq_treap {
#define lson(x) (tree[x].ls)
#define rson(x) (tree[x].rs)
		struct node {
			int ls;
			int rs;
			int sz;
			int dat;
			ll val;
			ll sum;
		} tree[maxn+5];
		int ptr;
		int root;
		int New(ll val) {
			ptr++;
			tree[ptr].ls=tree[ptr].rs=0;
			tree[ptr].sz=1;
			tree[ptr].val=tree[ptr].sum=val;
			tree[ptr].dat=rand();
			return ptr;
		}
		void push_up(int x) {
			tree[x].sz=tree[lson(x)].sz+tree[rson(x)].sz+1;
			tree[x].sum=tree[lson(x)].sum+tree[rson(x)].sum+tree[x].val;
		}
		int merge(int x,int y) {
			if(!x||!y) return x+y;
			if(tree[x].dat<tree[y].dat) {
				tree[x].rs=merge(tree[x].rs,y);
				push_up(x);
				return x;
			} else {
				tree[y].ls=merge(x,tree[y].ls);
				push_up(y);
				return y;
			}
		}
		void split(int now,ll k,int &x,int &y) { //按权值分裂
			if(now==0) {
				x=y=0;
				return;
			}
			if(k<tree[now].val) {
				y=now;
				split(lson(now),k,x,tree[y].ls);
			} else {
				x=now;
				split(rson(now),k,tree[x].rs,y);
			}
			push_up(now);
		}
		ll get_kth(int k) {
			int x=root;
			while(1) {
				if(k<=tree[lson(x)].sz) x=lson(x);
				else if(k==tree[lson(x)].sz+1) return tree[x].val;
				else {
					k-=tree[lson(x)].sz+1;
					x=rson(x);
				}
			}
			return -1;
		}
		void insert(ll val) {
			int x,y;
			split(root,val,x,y);
			root=merge(merge(x,New(val)),y);
		}
		void del(ll val) {
			int x,y,z;
			split(root,val,y,z);
			split(y,val-1,x,y);
			y=merge(lson(y),rson(y));//相同的值只删除一个 
			root=merge(merge(x,y),z);
		}
		ll get_mid() {
			return get_kth(tree[root].sz/2+1);
		}
		ll calc() {
			if(tree[root].sz==0) return 0;
			ll mid=get_mid();
			int x,y;
			ll ans=0;
			split(root,mid,x,y);
			ans+=mid*tree[x].sz-tree[x].sum;
			ans+=tree[y].sum-mid*tree[y].sz;
			root=merge(x,y);
			return ans;
		}
#undef lson
#undef rson
	} T1,T2;
	void solve() {
		sort(a+1,a+1+n); 
		ll ans=0,cnt=0;
		for(int i=1; i<=n; i++) {
			if(a[i].type1==a[i].type2) {
				ans+=abs(a[i].s-a[i].t);
			} else cnt++;
		}
		ll sum=INF;
		for(int i=1; i<=n; i++) {
			if(a[i].type1!=a[i].type2) {
				T1.insert(a[i].s);
				T1.insert(a[i].t);
			}
		}
//		printf("ok\n");
		sum=min(sum,T1.calc());
//		printf("ok\n");
		for(int i=1; i<=n; i++) {
			if(a[i].type1==a[i].type2) continue;
			else {
				T1.del(a[i].s);
				T1.del(a[i].t);
				T2.insert(a[i].s);
				T2.insert(a[i].t);
				sum=min(sum,T1.calc()+T2.calc());
			}
		}
		ans=ans+sum+cnt;
		printf("%lld\n",ans);
	}
}
int main() {
	char cmd1[2],cmd2[2];
	scanf("%d %d",&k,&n);
	for(int i=1; i<=n; i++) {
		scanf("%s %lld %s %lld",cmd1,&a[i].s,cmd2,&a[i].t);
		a[i].type1=cmd1[0]-'A'+1;
		a[i].type2=cmd2[0]-'A'+1;
	}
	if(k==1) {
		k_1::solve();
	} else {
		k_2::solve();
	}
}
