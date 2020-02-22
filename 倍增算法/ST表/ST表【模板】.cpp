//luogu ST±í¡¾Ä£°å¡¿ 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define maxn 100005
using namespace std;
int a[maxn];
int st[maxn][35];
int n,m; 
void init(){
	for(int i=1;i<=n;i++) st[i][0]=a[i];
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
} 
int query(int l,int r){
	int k=log2(r-l+1);
	return max(st[l][k],st[r-(1<<k)+1][k]);
}
int main(){
	int l,r;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	init();
	while(m--){
		scanf("%d %d",&l,&r);
		printf("%d\n",query(l,r));
	}
}
