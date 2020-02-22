#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 1000000
#define maxs 128
using namespace std;
int n;
char str[maxn+5];
int sa[maxn+5];
int rk[maxn+5];
int tp[maxn+5];
int buck[maxn+5];
void sort(int m){
	for(int i=0;i<=m;i++) buck[i]=0;
	for(int i=1;i<=n;i++) buck[rk[i]]++;
	for(int i=0;i<=m;i++) buck[i]+=buck[i-1];
	for(int i=n;i>=1;i--) sa[buck[rk[tp[i]]]--]=tp[i];
} 
void suffix_sort(){
	for(int i=1;i<=n;i++){
		rk[i]=str[i];
		tp[i]=i;
	}
	sort(maxs);
	for(int k=1,m=maxs;k<=n;k*=2){
		int p=0;
		for(int i=n-k+1;i<=n;i++) tp[++p]=i;
		for(int i=1;i<=n;i++){
			if(sa[i]>k) tp[++p]=sa[i]-k;
		} 
		sort(m);
		swap(tp,rk);
		rk[sa[1]]=p=1;
		for(int i=2;i<=n;i++){
			if(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+k]==tp[sa[i]+k]) rk[sa[i]]=p;
			else rk[sa[i]]=++p;
		}
		if(p==n) break;
		m=p;
	}
}



int main(){
	scanf("%s",str+1);
	n=strlen(str+1);
	suffix_sort();
	for(int i=1;i<=n;i++) printf("%d ",sa[i]);
}

