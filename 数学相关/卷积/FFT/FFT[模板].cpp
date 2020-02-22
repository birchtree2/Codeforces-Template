#include<iostream>
#include<cstdio>
#include<cstring>
#include<complex>
#include<cmath>
#define maxn 3000000
using namespace std;
const double pi=acos(-1.0);
typedef complex<double>com;
typedef long long ll;

inline void qread(int &x){
	x=0;
	int sign=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') sign=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	x=x*sign;
}

int rev[maxn+5];
void fft(com *x,int n,int type){
	for(int i=0;i<n;i++) if(i<rev[i]) swap(x[i],x[rev[i]]);
	for(int len=1;len<n;len*=2){
		int sz=len*2;
		com wn1=com(cos(2*pi/sz),type*sin(2*pi/sz));
		for(int l=0;l<n;l+=sz){
			int r=l+len-1;
			com wnk=com(1,0);
			for(int i=l;i<=r;i++){
				com tmp=x[i+len];
				x[i+len]=x[i]-wnk*tmp;
				x[i]=x[i]+wnk*tmp;
				wnk*=wn1; 
			} 
		}
	}
}

int n,m;
com a[maxn+5],b[maxn+5],c[maxn+5];
int main(){
	int x;
	qread(n);
	qread(m); 
	for(int i=0;i<=n;i++){
		qread(x);
		a[i]=x;
	}
	for(int i=0;i<=m;i++){
		qread(x);
		b[i]=x;
	}
	int k=0,sz=1;
	while(sz<=n+m){
		k++;
		sz*=2;
	}
	for(int i=0;i<sz;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	fft(a,sz,1);
	fft(b,sz,1);
	for(int i=0;i<sz;i++) c[i]=a[i]*b[i];
	fft(c,sz,-1);
	for(int i=0;i<=n+m;i++) printf("%lld ",(ll)(c[i].real()/sz+0.5)); 
}

