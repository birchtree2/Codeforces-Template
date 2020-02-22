#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define maxn 100005
using namespace std;
int vis[maxn];
int prime[maxn];
void sieve(int n){
	int m=(int)sqrt(n+0.5);
	vis[1]=1;
	for(int i=2;i<=m;i++){
		if(vis[i]==1) continue;
		for(int j=i*i;j<=n;j+=i){
			 vis[j]=1;
		}
	}
}
int c=0;
int get_prime(int n){
	memset(vis,0,sizeof(vis));
	sieve(n);
	for(int i=1;i<=n;i++) if(vis[i]==0) prime[++c]=i;
	return c;
}
int n;
int main(){
	cin>>n;
	int size=get_prime(n);
	for(int i=1;i<=size;i++) printf("%d ",prime[i]);
} 
