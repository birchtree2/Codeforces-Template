#include<iostream>
#include<cstdio>
using namespace std;
int gcd(int a,int b){
	if(b==0) return a;
	else return gcd(b,a%b);
} 
int a,b;
int main(){
	while(cin>>a>>b){
		cout<<gcd(a,b)<<endl;
	}
}
