//https://www.cnblogs.com/cjyyb/p/8253033.html
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 10000000
#define mod 20101009//不是1e9+7!!! 
using namespace std;
typedef long long ll;
int cnt;
bool vis[maxn+5];
int prime[maxn+5];
int mu[maxn+5];
ll sumg[maxn+5];//g(n)=n*n*mu(n)
void sieve(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				break;
			}else mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<=n;i++) sumg[i]=(sumg[i-1]+(ll)i*i%mod*mu[i]%mod)%mod;
}
 
inline ll fast_pow(ll x,ll k){
	ll ans=1;
	while(k){
		if(k&1) ans=ans*x%mod;
		x=x*x%mod;
		k>>=1;
	}
	return ans;
}
inline ll inv(ll x){
	return fast_pow(x,mod-2);
}

ll n,m;
ll inv2;
inline ll S(ll n){
	return n*(n+1)%mod*inv2%mod;
}
ll calc(int n,int m){
	ll ans=0;
	for(int l=1,r;l<=n;l=r+1){
		r=min(n/(n/l),m/(m/l));
		ans+=(sumg[r]-sumg[l-1])*S(n/l)%mod*S(m/l)%mod;
		ans=(ans+mod)%mod;//注意mu可能为负数 
	}
	return ans;
}

int main(){
	sieve(maxn);
	inv2=inv(2);
	scanf("%lld %lld",&n,&m);
	if(n>m) swap(n,m);
	ll ans=0;
	for(int l=1,r;l<=n;l=r+1){
		r=min(n/(n/l),m/(m/l));
		ans+=(ll)(l+r)*(r-l+1)%mod*inv2%mod*calc(n/l,m/l)%mod;
		ans=(ans+mod)%mod;
	} 
	printf("%lld\n",ans);
}
