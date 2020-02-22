#include<iostream>
#include<cstdio>
#define mod 19260817
using namespace std;
typedef long long ll;
ll a,b;
inline void qread(ll &x){
	x=0;
	ll sign=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') sign=-1;
		c=getchar();
	} 
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		x%=mod;
		c=getchar();
	}
	x=x*sign;
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
ll inv(ll x){
	return fast_pow(x,mod-2);
}
int main(){
	qread(a);
	qread(b); 
	if(b==0){
		printf("Angry!\n");
		return 0;
	}
	printf("%lld\n",a*inv(b)%mod);
}

