//https://www.luogu.com.cn/problem/P5410 
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100000
using namespace std;
int n,m;
char s[maxn+5],t[maxn+5];
void get_nex(char *t,int m,int *nex){
	nex[1]=m;
	nex[2]=0;
	while(t[2+nex[2]]==t[1+nex[2]]) nex[2]++;
	for(int i=3,p0=2,r=p0+nex[p0]-1;i<=m;i++){
		if(i+nex[i-p0+1]-1<r) nex[i]=nex[i-p0+1];
		else{
			nex[i]=max(r-i+1,0);
			while(t[i+nex[i]]==t[1+nex[i]]) nex[i]++;
			p0=i;
			r=i+nex[i]-1;
		}
	}
}
void get_extend(char *s,int n,char *t,int m,int *extend){
	static int nex[maxn+5];
	get_nex(t,m,nex);
	for(int i=1;i<=m;i++) printf("%d ",nex[i]);
	printf("\n");
	extend[1]=0;
	while(s[extend[1]+1]==t[extend[1]+1]) extend[1]++;
	for(int i=2,p0=1,r=p0+extend[p0]-1;i<=n;i++){
		if(i+nex[i-p0+1]-1<r) extend[i]=nex[i-p0+1];
		else{
			extend[i]=max(r-i+1,0);
			while(s[i+extend[i]]==t[1+extend[i]]) extend[i]++;
			p0=i;
			r=i+extend[i]-1;
		}
	}
}

int f[maxn+5];
int main(){
//	freopen("input.txt","r",stdin);
	scanf("%s",s+1);
	scanf("%s",t+1);
	n=strlen(s+1);
	m=strlen(t+1);
	get_extend(s,n,t,m,f);
	for(int i=1;i<=n;i++) printf("%d ",f[i]);
}

