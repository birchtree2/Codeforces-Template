#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define maxn 2000000
using namespace std;
typedef long long ll;
int cnt;
bool vis[maxn+5];
int prime[maxn+5];
int phi[maxn+5];
int mu[maxn+5];
ll sum_phi[maxn+5]; 
ll sum_mu[maxn+5];
void sieve(int n){
	phi[1]=mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			mu[i]=-1;
			phi[i]=i-1;
			prime[++cnt]=i; 
		}
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}else{
				mu[i*prime[j]]=-mu[i];
				phi[i*prime[j]]=phi[i]*phi[prime[j]]; 
			}
		}
	}
	for(int i=1;i<=n;i++) sum_mu[i]=sum_mu[i-1]+mu[i];
	for(int i=1;i<=n;i++) sum_phi[i]=sum_phi[i-1]+phi[i]; 
}

int t;
ll n; 
map<ll,ll>ans_mu;
map<ll,ll>ans_phi;
//ll sieve_mu(ll n){//orz dujiao
//	if(n<=maxn) return sum_mu[n];
//	if(ans_mu.find(n)!=ans_mu.end()) return ans_mu[n];
//	ll ans=1;
//	for(ll l=2,r;l<=n;l=r+1){
//		r=n/(n/l);
//		ans-=(r-l+1)*sieve_mu(n/l);
//	}
//	ans_mu[n]=ans;
//	return ans;
//}
//ll sieve_phi(ll n){
//	if(n<=maxn) return sum_phi[n];
//	if(ans_phi.find(n)!=ans_phi.end()) return ans_phi[n];
//	ll ans=n*(n+1)/2;
//	for(ll l=2,r;l<=n;l=r+1){
//		r=n/(n/l);
//		ans-=(r-l+1)*sieve_phi(n/l); 
//	}
//	ans_phi[n]=ans;
//	return ans;
//} 
struct node{
	ll phi;
	ll mu;
	node(){
		
	}
	node(ll _phi,ll _mu){
		phi=_phi;
		mu=_mu;
	}
};
node dujiao_sieve(ll n){
	if(n<=maxn) return node(sum_phi[n],sum_mu[n]);
	if(ans_phi.count(n)) return node(ans_phi[n],ans_mu[n]);
	ll ans1=n*(n+1)/2,ans2=1;
	node tmp;
	for(ll l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		tmp=dujiao_sieve(n/l);
		ans1-=(r-l+1)*tmp.phi;
		ans2-=(r-l+1)*tmp.mu; 
	} 
	ans_phi[n]=ans1;
	ans_mu[n]=ans2;
	return node(ans1,ans2);
}
int main(){
	sieve(maxn+5);
	scanf("%d",&t);
	while(t--){
		scanf("%lld",&n);
		node ans=dujiao_sieve(n);
		printf("%lld %lld\n",ans.phi,ans.mu);
	}
}

