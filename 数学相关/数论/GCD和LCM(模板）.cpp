#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
int lcm(int a,int b){
	return a/gcd(a,b)*b;
}
int main(){
	
} 
