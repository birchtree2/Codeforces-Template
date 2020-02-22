#include<iostream>
#inclue<cstdio>
using namespace std; 
int fast_pow(int x,int k,int mod){
	int ans=x;
	k-=1;
	while(k>0){
		if(k%2==1){
			ans=(ans*x)%mod;
		}
		x=(x*x)%mod;
		k/=2;
	}
	return ans%mod;
}
int inv(int x,int mod){
	return fast_pow(x,mod-2,mod);
}
int main(){
	
}
