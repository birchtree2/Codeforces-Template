#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 10000005
#define maxm 100005
using namespace std;
typedef long long ll;
int vis[maxn];
int prime[maxn];
int cnt=0;
void sieve(int n){
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			prime[++cnt]=i;
		}
		for(ll j=1;j<=cnt&&(ll)i*prime[j]<=n;j++){
			vis[(ll)i*prime[j]]=1;
			if(!(i%prime[j])) break;
		}
	}
}
int n,m;
int main(){
	vis[1]=1; 
	scanf("%d %d",&n,&m);
	int x;
	sieve(n);
	for(int i=1;i<=m;i++){
		scanf("%d",&x);
		if(!vis[x]) printf("Yes\n");
		else printf("No\n");
	}	
} 
