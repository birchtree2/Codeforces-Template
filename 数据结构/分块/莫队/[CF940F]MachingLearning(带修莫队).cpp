#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath> 
#include<algorithm>
#define maxn 500000
#define maxm 500000
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
int dn=0;
int tmp[maxn+maxm+5];
 
int bel[maxn+5];
int cntq=0;
struct qtype{
	int l;
	int r;
	int id;
	int t;
	friend bool operator < (qtype p,qtype q){
		if(bel[p.l]==bel[q.l]){
			if(bel[p.r]==bel[q.r]) return p.t<q.t;
			else return p.r<q.r;
		}else return bel[p.l]<bel[q.l];
	}
}q[maxm+5];
int cntu=0; 
struct utype{
	int x;
	int v;
}up[maxm+5];
int ans[maxm+5];
 
//int cnt[maxn+maxm+5];
//int sumc[maxn+maxm+5];
//void add(int v){
//	sumc[cnt[v]]--;
//	cnt[v]++;
//	sumc[cnt[v]]++;
//}
//void del(int v){
//	sumc[cnt[v]]--;
//	cnt[v]--;
//	sumc[cnt[v]]++;
//}
//void update(int l,int r,int uid){
//	if(up[uid].x>=l&&up[uid].x<=r){//被询问区间包含才真正修改cnt 
//		del(a[up[uid].x]);
//		add(up[uid].v);
//	}
//	 swap(a[up[uid].x],up[uid].v); //修改a的值,为了能撤回修改操作,需要交换 
//}
int cnt[maxn+maxm+5];//离散化之后值域为n+m 
int sumcnt[maxn+maxm+5];//统计cnt出现的次数，用于求cnt的mex
void add(int val){
	sumcnt[cnt[val]]--;
	cnt[val]++;
	sumcnt[cnt[val]]++;
}
void del(int val){
	sumcnt[cnt[val]]--;
	cnt[val]--;
	sumcnt[cnt[val]]++;
}
void update(int l,int r,utype &p){
	if(l<=p.x&&p.x<=r){
		del(a[p.x]);
		add(p.v);
	}
	swap(p.v,a[p.x]);
}
int calc(){
	int ans=1;
	while(sumcnt[ans]) ans++;
	return ans;
}
 
 
int main(){
	int cmd;
	qread(n);
	qread(m);
	for(int i=1;i<=n;i++){
		qread(a[i]);
		tmp[++dn]=a[i];
	}
	for(int i=1;i<=m;i++){
		qread(cmd);
		if(cmd==1){
			cntq++;
			qread(q[cntq].l);
			qread(q[cntq].r);
			q[cntq].id=cntq;
			q[cntq].t=cntu;
		}else{
			cntu++;
			qread(up[cntu].x);
			qread(up[cntu].v);
			tmp[++dn]=up[cntu].v;
		}
	}
	sort(tmp+1,tmp+1+dn);
	dn=unique(tmp+1,tmp+1+dn)-tmp-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(tmp+1,tmp+1+dn,a[i])-tmp;
	for(int i=1;i<=cntu;i++) up[i].v=lower_bound(tmp+1,tmp+1+dn,up[i].v)-tmp;
	
	int bsz=pow(n,2.0/3.0);
	for(int i=1;i<=n;i++) bel[i]=i/bsz+1;
	sort(q+1,q+1+cntq);
	int l=1,r=0,t=0;
	for(int i=1;i<=cntq;i++){
		while(l<q[i].l) del(a[l++]);
		while(r>q[i].r) del(a[r--]);
		while(l>q[i].l) add(a[--l]);
		while(r<q[i].r) add(a[++r]);
		while(t>q[i].t) update(l,r,up[t--]);
		while(t<q[i].t) update(l,r,up[++t]);
		ans[q[i].id]=calc();
	}
	for(int i=1;i<=cntq;i++){
		qprint(ans[i]);
		putchar('\n');		
	}
}
