
#include<iostream>
#include<cstdio>
#include<cstring> 
#include<queue> 
#define maxn 500000 
#define maxlogn 25
using namespace std;
typedef long long ll;
int n,k,L,R;
struct sparse_table{
	int log2[maxn+5];
	int st[maxn+5][maxlogn+5];
	void ini(ll *a,int n){
		log2[0]=-1;
		for(int i=1;i<=n;i++) log2[i]=log2[i>>1]+1;
		for(int i=1;i<=n;i++) st[i][0]=i;
		for(int j=1;j<=log2[n]+1;j++){
			for(int i=1;i+(1<<(j-1))<=n;i++){
				if(a[st[i][j-1]]>a[st[i+(1<<(j-1))][j-1]]) st[i][j]=st[i][j-1];
				else st[i][j]=st[i+(1<<(j-1))][j-1];
			} 
		}
	}
	int query(ll *a,int l,int r){
		int k=log2[r-l+1];
		if(a[st[l][k]]>a[st[r-(1<<k)+1][k]]) return st[l][k];
		else return st[r-(1<<k)+1][k];
	}
}T;

int a[maxn+5];
ll sum[maxn+5];
struct node{
	int l;
	int r;
	int i;
	inline ll val(){
		return sum[T.query(sum,l,r)]-sum[i-1];
	}
	node(){
		
	} 
	node(int _i,int _l,int _r){
		i=_i;
		l=_l;
		r=_r;
	} 
	friend bool operator < (node p,node q){
		return p.val()<q.val();
	} 
};
priority_queue<node>q; 
int main(){
	scanf("%d %d %d %d",&n,&k,&L,&R);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	T.ini(sum,n);
	for(int i=1;i+L-1<=n;i++){
		q.push(node(i,i+L-1,min(i+R-1,n)));
	}
	ll ans=0;
	for(int i=1;i<=k;i++){
		node now=q.top();
		q.pop(); 
		ans+=now.val();
		int p=T.query(sum,now.l,now.r);
		if(p>now.l) q.push(node(now.i,now.l,p-1));
		if(p<now.r) q.push(node(now.i,p+1,now.r)); 
	}
	printf("%lld\n",ans); 
}

