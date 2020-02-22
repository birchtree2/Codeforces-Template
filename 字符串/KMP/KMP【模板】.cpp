#include<iostream>
#include<cstdio>
#include<cstring> 
#include<algorithm>
#define maxn 1000005
using namespace std;
int n,m;                                                                                                                                                                                                                                                                
char a[maxn],b[maxn];
int f[maxn];
int next[maxn];
int main(){
    scanf("%s",b+1);
    scanf("%s",a+1);
    n=strlen(a+1);
    m=strlen(b+1);
    next[1]=0;
    for(int i=2,j=0;i<=n;i++){
        while(j>0&&a[i]!=a[j+1]) j=next[j];
        if(a[i]==a[j+1]) j++;
        next[i]=j;
    }
    for(int i=1,j=0;i<=m;i++){
        while(j>0&&(j==n||b[i]!=a[j+1])) j=next[j];
        if(b[i]==a[j+1]) j++;
        f[i]=j;
    }
    for(int i=1;i<=m;i++){
        if(f[i]==n) printf("%d\n",i-n+1);
    }
    for(int i=1;i<=n;i++){
        printf("%d ",next[i]);
    }
    printf("\n");
}
