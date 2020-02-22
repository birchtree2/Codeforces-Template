//´ËÎªÄ£°å2 O(nlogn)
#include<iostream>
#define maxn 1000
using namespace std;
int num,n;
int a[maxn];
int search(int x,int l,int r) {
	int mid=(l+r)/2;
	if(a[mid]<x) return mid;
	else if(a[mid]>x) search(x,l,mid-1);
	else search(x,mid+1,r);
}
int main() {
	int i=1;
	while(1) {
		int pos=search(num,1,n);
		if(pos>i-1) a[i++]=pos;
		else a[pos]=num;
	}
    cout<<i;
    return 0;
}
