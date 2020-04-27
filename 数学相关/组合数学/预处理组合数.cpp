#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 998244353
#define maxn 5000
using namespace std;
typedef long long ll;
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
ll fact[maxn+5],invfact[maxn+5];
void ini(int n){
	fact[0]=1;
	for(int i=1;i<=n;i++) fact[i]=fact[i-1]*i%mod;
	invfact[n]=inv(fact[n]);
	for(int i=n-1;i>=0;i--) invfact[i]=invfact[i+1]*(i+1)%mod;
}
ll C(int n,int m){
	return fact[n]*invfact[n-m]%mod*invfact[m]%mod;
} 

int main(){
	
} 
