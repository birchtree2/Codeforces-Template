#include<iostream>
#include<cstdio>
#include<cstring> 
#include<cmath>
#include<algorithm> 
#define INF 0x3f3f3f3f
#define maxn 2000000
#define maxlogn 25
using namespace std;
int n,len;
struct seg{
	int l;
	int r;
	seg(){
		
	}
	seg(int _l,int _r){
		l=_l;
		r=_r;
	}
	friend bool operator  < (seg p,seg q){
		if(p.l==q.l) return p.r<q.r;
		else return p.l<q.l;
	}
}a[maxn+5],stk[maxn+5];
int sz,log2n;

int anc[maxn+5][maxlogn+5];
int query(int x){
	int ans=1;
	int r=a[x].l+len-1; 
	for(int i=log2n;i>=0;i--){
		if(anc[x][i]!=0&&a[anc[x][i]].r<=r){
			ans+=(1<<i); 
			x=anc[x][i];
		}
	}
	if(anc[x][0]&&a[x].r<r){
		ans++;
		x=anc[x][0];
	}
	if(a[x].r>=r) return ans;
	else return INF;
}
int main(){
	int l,r;
	scanf("%d %d",&len,&n);
	log2n=log2(n*2);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&l,&r);
		if(l<=r){
			a[++sz]=seg(l,r);
			a[++sz]=seg(l+len,r+len);
		}else{
			a[++sz]=seg(l,r+len);
			a[++sz]=seg(l+len,r+len+len);
		}
	}
	sort(a+1,a+1+sz);
	int top=0;
	for(int i=1;i<=sz;i++){
		if(a[i].r>stk[top].r) stk[++top]=a[i];
	}
	sz=top;
	for(int i=1;i<=top;i++) a[i]=stk[i];
	
	int ptr=1;
	for(int i=1;i<=sz;i++){
		while(ptr<sz&&a[ptr+1].l<=a[i].r+1) ptr++;
		if(ptr!=i) anc[i][0]=ptr;
	}
	for(int j=1;j<=log2n;j++){
		for(int i=1;i<=sz;i++){
			anc[i][j]=anc[anc[i][j-1]][j-1];
		}
	}
	
	int ans=INF;
	for(int i=1;i<=sz;i++){
		ans=min(ans,query(i));
	}
	if(ans==INF) printf("impossible\n");
	else printf("%d\n",ans);
}

