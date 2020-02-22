#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int exgcd(int a,int b,int& x,int& y){
	if(!b){
		x=1;
		y=0;
		return a;
	}
	int g=exgcd(b,a%b,x,y);
	int x2=x;
	int y2=y;
	x=y2;
	y=x2-(a/b)*y2;
	return g;
}
int main(){
	int a,b,x,y;
	scanf("%d %d",&a,&b);
	int t=exgcd(a,b,x,y);
	printf("%d %d\n",x,y);
} 
