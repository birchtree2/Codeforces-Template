//https://www.luogu.org/problem/P1903
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define maxn 100000
#define maxm 100000
#define maxv 1000000
using namespace std;
inline void qread(int &x) {
	x=0;
	int sign=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-') sign=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=x*10+c-'0';
		c=getchar();
	}
	x=x*sign;
}
inline void qprint(int x) {
	if(x<0) {
		putchar('-');
		qprint(-x);
	} else if(x==0) {
		putchar('0');
		return;
	} else {
		if(x>=10) qprint(x/10);
		putchar('0'+x%10);
	}
}

int n,m;
int a[maxn+5];

int bsz;
int belong[maxn+5];

int l,r,t;
int cntq;
struct que {
	int l;
	int r;
	int tim;
	int id;
	friend bool operator < (que p,que q){//排序函数要写对 
		if(belong[p.l]==belong[q.l]){
			if(belong[p.r]==belong[q.r]) return p.tim<q.tim;
			else return p.r<q.r;
		}else return belong[p.l]<belong[q.l];
	}

} q[maxm+5];
int cntu;
struct upd {
	int pos;
	int val;
} up[maxm+5];

int sum;
int cnt[maxv+5];
inline void add(int val) {
	cnt[val]++;
	if(cnt[val]==1) sum++;
}
inline void del(int val) {
	cnt[val]--;
	if(cnt[val]==0) sum--;
}
void update(upd &x) { //要用引用，因为会修改x.val
	if(l<=x.pos&&x.pos<=r) {
		del(a[x.pos]);
		add(x.val);
	}
	swap(x.val,a[x.pos]);//方便改回来
}

int ans[maxm+5];
int main() {
	freopen("4.in","r",stdin);
	freopen("4.out","w",stdout);
	char cmd[2];
	int x,y;
	qread(n);
	qread(m);
	for(int i=1; i<=n; i++) qread(a[i]);
	for(int i=1; i<=m; i++) {
		scanf("%s",cmd);
		qread(x);
		qread(y);
		if(cmd[0]=='Q') {
			cntq++;
			q[cntq].l=x;
			q[cntq].r=y;
			q[cntq].tim=cntu;
			q[cntq].id=cntq;
		} else {
			cntu++;
			up[cntu].pos=x;
			up[cntu].val=y;
		}
	}
//	cerr<<"ok"<<endl;
	bsz=pow(n,2.0/3.0);
	for(int i=1; i<=n; i++) belong[i]=i/bsz+1;
	sort(q+1,q+1+cntq);
	l=1,r=0,t=0;
//	cerr<<"ok"<<endl;
	for(int i=1; i<=cntq; i++) {
		while(l<q[i].l) del(a[l++]);
		while(l>q[i].l) add(a[--l]);
		while(r<q[i].r) add(a[++r]);
		while(r>q[i].r) del(a[r--]);
		while(t<q[i].tim) update(up[++t]);
		while(t>q[i].tim) update(up[t--]);
		ans[q[i].id]=sum;
	}
//	cerr<<"ok"<<endl;
	for(int i=1; i<=cntq; i++) {
		qprint(ans[i]);
		putchar('\n');
	}
}

