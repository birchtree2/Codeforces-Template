#include<iostream>
#include<cstdio>
#include<cstring>
#define m1 998244353ll
#define m2 1004535809ll
#define m3 469762049ll
#define G 3
#define maxn 1048576
using namespace std; 
typedef long long ll;
const ll mm=m1*m2;
ll C;
ll fast_pow(ll x,ll k,ll m){
	ll ans=1;
	while(k){
		if(k&1) ans=ans*x%m;
		x=x*x%m;
		k>>=1; 
	}
	return ans;
}
inline ll inv(ll a,ll m){
	return fast_pow(a%m,m-2,m); //一定要取模m 
} 

ll mul(ll a,ll b,ll m){
	ll ans=0;
	while(b){
		if(b&1) ans=(ans+a)%m;
		a=(a+a)%m;
		b>>=1;
	}
	return ans;
}
ll CRT(ll a1,ll a2,ll a3){
	//[Warning]You are not expected to understand this.
    ll r=(mul(a1*m2%mm,inv(m2,m1),mm)+mul(a2*m1%mm,inv(m1,m2),mm))%mm;
    ll e=((a3-r)%m3+m3)%m3*inv(mm,m3)%m3;
    return ((e%C)*(mm%C)%C+r%C)%C;
}

int n,m,N,L;
int rev[maxn+5];
void NTT(ll *x,int n,int type,ll mod){
	ll invG=inv(G,mod); 
	for(int i=0;i<n;i++) if(i<rev[i]) swap(x[i],x[rev[i]]); 
	for(int len=1;len<n;len*=2){
		int sz=len*2;
		ll gn1=fast_pow((type==1?G:invG),(mod-1)/sz,mod);
		for(int l=0;l<n;l+=sz){
			int r=l+len-1;
			ll gnk=1;
			for(int i=l;i<=r;i++){
				ll tmp=x[i+len];
				x[i+len]=(x[i]-gnk*tmp%mod+mod)%mod;
				x[i]=(x[i]+gnk*tmp%mod)%mod;
				gnk=gnk*gn1%mod; 
			}
		}
	} 
	if(type==-1){
		ll invn=inv(n,mod);
		for(int i=0;i<n;i++) x[i]=x[i]*invn%mod; 
	}
} 
void fmul(ll *a,ll *b,ll *ans,int n,ll mod){
	static ll ta[maxn+5],tb[maxn+5];
	for(int i=0;i<n;i++) ta[i]=a[i];
	for(int i=0;i<n;i++) tb[i]=b[i];
	NTT(ta,n,1,mod);
	if(a!=b) NTT(tb,n,1,mod);
	for(int i=0;i<n;i++) ans[i]=ta[i]*tb[i]%mod;
	NTT(ans,n,-1,mod);
}

ll a[maxn+5],b[maxn+5],c[3][maxn+5];
int main(){
	scanf("%d %d %lld",&n,&m,&C);
	for(int i=0;i<=n;i++){
		scanf("%lld",&a[i]);
		a[i]%=C;
	}
	for(int i=0;i<=m;i++){
		scanf("%lld",&b[i]);
		b[i]%=C;
	}
	N=1,L=0;
	while(N<n+m+1){
		N*=2;
		L++;
	}
	for(int i=0;i<N;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
	fmul(a,b,c[0],N,m1);
	fmul(a,b,c[1],N,m2);
	fmul(a,b,c[2],N,m3);
	for(int i=0;i<n+m+1;i++){
//		printf("[%lld,%lld,%lld]",c[0][i],c[1][i],c[2][i]);
		printf("%lld ",CRT(c[0][i],c[1][i],c[2][i]));
	}
}
