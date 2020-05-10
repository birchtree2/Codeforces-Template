#include<iostream>
#include<cstdio>
#include<cstring> 
#include<cmath>
#define maxn 1000000
using namespace std;
typedef long double db;
typedef long long ll;
const db pi=acos(-1.0);
struct com{
	db x;
	db y;
	com(){}
	com(db _x,db _y){
		x=_x;
		y=_y;
	}
	inline db real(){return x;}
	inline db imag(){return y;}
	friend com operator + (com p,com q){
		return com(p.x+q.x,p.y+q.y);
	} 
	friend com operator - (com p,com q){
		return com(p.x-q.x,p.y-q.y);
	}
	friend com operator * (com p,com q){
		return com(p.x*q.x-p.y*q.y,p.x*q.y+p.y*q.x);
	}
	friend com operator / (com p,db k){
		return com(p.x/k,p.y/k);
	} 
	inline com conj(){
		return com(x,-y);
	}
};
int rev[maxn+5];
void fft(com *x,int n,int type){
	for(int i=0;i<n;i++) if(i<rev[i]) swap(x[i],x[rev[i]]);
	for(int len=1;len<n;len*=2){
		int sz=len*2;
		com wn1=com(cos(2*pi/sz),sin(2*pi/sz)*type);
		for(int l=0;l<n;l+=sz){
			int r=l+len-1;
			com wnk=com(1,0);
			for(int i=l;i<=r;i++){
				com tmp=x[i+len];
				x[i+len]=x[i]-wnk*tmp;
				x[i]=x[i]+wnk*tmp;
				wnk=wnk*wn1;
			}
		}
	}
	if(type==-1) for(int i=0;i<n;i++) x[i]=x[i]/n;
}

void mul(ll *ina,ll *inb,ll *outc,int n,ll mod){
	static com p[maxn+5],q[maxn+5],r[maxn+5],s[maxn+5];
	for(int i=0;i<n;i++){
		ina[i]%=mod;inb[i]%=mod; 
		p[i]=com(ina[i]>>15,ina[i]&((1<<15)-1));
		q[i]=com(inb[i]>>15,inb[i]&((1<<15)-1));
	}
	fft(p,n,1);
	fft(q,n,1);
	for(int i=0;i<n;i++){
		int j=(i==0?0:n-i);
		com aa=(p[i]+p[j].conj())*com(0.5,0);
		com bb=(p[i]-p[j].conj())*com(0,-0.5);
		com cc=(q[i]+q[j].conj())*com(0.5,0);
		com dd=(q[i]-q[j].conj())*com(0,-0.5);
		r[i]=aa*cc+aa*dd*com(0,1);
		s[i]=bb*cc+bb*dd*com(0,1);
	}
	fft(r,n,-1);
	fft(s,n,-1);
	for(int i=0;i<n;i++){
		ll ac=(ll)(r[i].real()+0.5)%mod;
		ll ad=(ll)(r[i].imag()+0.5)%mod;
		ll bc=(ll)(s[i].real()+0.5)%mod;
		ll bd=(ll)(s[i].imag()+0.5)%mod;
		outc[i]=((ac<<30)+((ad+bc)<<15)+bd)%mod;
	}
}

int n,m;
ll mod; 
ll a[maxn+5],b[maxn+5],c[maxn+5];
int main(){
    scanf("%d %d %lld",&n,&m,&mod);
    for(int i=0;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=0;i<=m;i++) scanf("%lld",&b[i]);
	int N=1,L=0;
	while(N<=n+m+1){
		N*=2;
		L++;
	}
	for(int i=0;i<N;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
	mul(a,b,c,N,mod);
    for(int i=0;i<n+m+1;i++) printf("%lld ",c[i]);
}

