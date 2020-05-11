#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath> 
#define maxn 100000
#define maxm 100000
using namespace std;
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
			if(bel[q.r]==bel[q.r]) return p.t<q.t;
			else return p.r<q.r;
		}else return bel[q.l]<bel[q.l];
	}
}q[maxm+5];
int cntu=0; 
struct utype{
	int x;
	int v;
}up[maxm+5];
int ans[maxm+5];

int cnt[maxn+maxm+5];
int sumc[maxn+maxm+5];
void add(int v){
	sumc[cnt[v]]--;
	cnt[v]++;
	sumc[cnt[v]]++;
}
void del(int v){
	sumc[cnt[v]]--;
	cnt[v]--;
	sumc[cnt[v]]++;
}
void update(int qid,int uid){
	if(up[uid].x>=q[qid].l&&up[uid].x<=q[qid].r){//被询问区间包含才真正修改cnt 
		del(a[up[uid].x]);
		add(up[uid].v);
	}else swap(a[up[uid].x],up[uid].v); //否则只需要修改a的值,为了在l,r移动时能删除,需要交换 
}
int calc(){
	int ans=0;
	while(sumc[ans]) ans++;
	return ans;
}


int main(){
	int op;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		tmp[++dn]=a[i];
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&op);
		if(op==1){
			cntq++;
			scanf("%d %d",q[cntq].l,q[cntq].r);
			q[cntq].id=cntq;
			q[cntq].t=cntu;
		}else{
			cntu++;
			scanf("%d %d",&up[cntu].x,up[cntu].v);
			tmp[++sz]=up[cntu].v;
		}
	}
	sort(tmp+1,tmp+1+dn);
	dn=unique(tmp+1,tmp+1+dn)-tmp-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(tmp+1,tmp+1+dn,a[i]);
	for(int i=1;i<=cntu;i++) up[i].v=lower_bound(tmp+1,tmp+1+dn,up[i].v);
	
	int bsz=pow(n,2.0/3.0);
	for(int i=1;i<=n;i++) bel[i]=i/bsz+1;
	int l=1,r=0,t=0;
	for(int i=1;i<=cntq;i++){
		while(l<q[i].l) del(a[l++]);
		while(r>q[i].r) del(a[r--]);
		while(l>q[i].l) add(a[--l]);
		while(r<q[i].r) add(a[++r]);
		while(t<q[i].t) 
	}
}

