#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100000
using namespace std;
typedef long long ll;
int n,m;
int cnt;
bool vis[maxn+5];
int prime[maxn+5];
int phi[maxn+5];
ll sum_phi[maxn+5];
//(mu*id)=phi
void sieve(int n){
	phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}else{
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
			} 
		}
	}
	for(int i=1;i<=n;i++) sum_phi[i]=sum_phi[i-1]+phi[i];
}
int main(){
	sieve(maxn);
	scanf("%d %d",&n,&m);
	if(n>m) swap(n,m);
	ll sum=0;
	for(int l=1,r;l<=n;l=r+1){
		r=min(n/(n/l),m/(m/l));
		sum+=(sum_phi[r]-sum_phi[l-1])*(n/l)*(m/l);
	}
	printf("%lld\n",2*sum-(ll)n*m);
}

