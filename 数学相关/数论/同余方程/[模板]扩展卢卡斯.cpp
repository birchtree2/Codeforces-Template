#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 30
using namespace std;
typedef long long ll;
ll gcd(ll a,ll b){
	return b==0?a:gcd(b,a%b); 
}
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1;
		y=0;
		return a;		
	}
	ll x2,y2;
	ll g=exgcd(b,a%b,x2,y2);
	x=y2;
	y=x2-a/b*y2;
	return g;
}
inline ll inv(ll a,ll mod){
	ll x,y;
	exgcd(a,mod,x,y);
	return (x+mod)%mod;
}
inline ll fast_pow(ll x,ll k){
	ll ans=1;
	while(k){
		if(k&1) ans=ans*x;
		x=x*x;
		k>>=1;
	}
	return ans;
}
inline ll fast_pow(ll x,ll k,ll mod){
	ll ans=1;
	while(k){
		if(k&1) ans=ans*x%mod;
		x=x*x%mod;
		k>>=1;
	}
	return ans;
}

ll f(ll n,ll p,ll pk){//n!/p^x 
	if(n==0) return 1;
	ll sum1=1,sum2=1;
	for(ll i=1;i<=pk;i++){
		if(i%p!=0) sum1=sum1*i%pk;
	}
	sum1=fast_pow(sum1,n/pk,pk);
	for(ll i=pk*(n/pk);i<=n;i++){
		if(i%p!=0) sum2=sum2*(i%pk)%pk;
	}
	return sum1*sum2%pk*f(n/p,p,pk)%pk;
}
ll g(ll n,ll p){//1~n里面有多少个p的质因子 
	if(n<p) return 0;
	else return n/p+g(n/p,p); 
}
inline ll C_pk(ll n,ll m,ll p,ll pk){//C(n,m)%(p^k)
	return f(n,p,pk)*inv(f(m,p,pk),pk)%pk*inv(f(n-m,p,pk),pk)%pk*fast_pow(p,g(n,p)-g(m,p)-g(n-m,p),pk)%pk;
}
int divide(ll x,ll *p,ll *k){
	int tot=0;
	for(ll i=2;i*i<=x;i++){
		if(x%i==0){
			tot++;
			p[tot]=i;
			while(x%i==0){
				x/=i;
				k[tot]++;
			}
		}
	}
	if(x!=1){
		tot++;
		p[tot]=x;
		k[tot]=1;
	}
	return tot;
}
ll exlucas(ll n,ll m,ll mod){
	static ll p[maxn+5],k[maxn+5];
	int tot=divide(mod,p,k);
	ll ans=0;
	for(int i=1;i<=tot;i++){
		ll pk=fast_pow(p[i],k[i]);
		ll cpk=C_pk(n,m,p[i],pk);
		//因为p^k之间互质，直接用CRT，不用EXCRT 
		ll mi=mod/pk,ti=inv(mi,pk);//ti*mi=1(mod p^k);
		ans=(ans+cpk*mi%mod*ti%mod)%mod;
	}
	return ans;
}

int main(){
	ll n,m,p;
	scanf("%lld %lld %lld",&n,&m,&p);
	printf("%lld\n",exlucas(n,m,p));
}

