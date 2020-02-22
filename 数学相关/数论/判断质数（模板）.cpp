#include<iostream>
#include<cmath>
using namespace std;
bool is_prime(int x){
	if(x%2==0&&x!=2) return false;
	for(int i=3;i*i<=x;i++)
		if(x%i==0) return false;
	return true;
}
int main()
{
	long long int a;
    while(1){
	cout<<"请输入：";
	cin>>a;
	
	if(is_prime(a))
		cout<<a<<"是质数"<<'\n';
	else cout<<a<<"不是质数"<<'\n';
}
}
