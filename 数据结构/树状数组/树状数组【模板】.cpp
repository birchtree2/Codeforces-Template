//hdu 1166 
#include<iostream>
#include<cstring>
#define maxn 50005
using namespace std;
int a[maxn],c[maxn];
int t,n;
inline int lowbit(int x){
	return x&(-x);
}
void update(int x,int value){
	while(x<=n){
		c[x]+=value;
		x+=lowbit(x);
	}
}
int sum(int x){
	int ans=0;
	while(x>0){
		ans+=c[x];
		x-=lowbit(x); 
	}
	return ans;
}
char cmd[20];
int main(){
	scanf("%d",&t);
	int i,j;
	for(int cas=1;cas<=t;cas++){
		printf("Case %d:\n",cas);
		scanf("%d",&n);
		memset(c,0,sizeof(c));
		for(int u=1;u<=n;u++){
			 scanf("%d",&a[u]);
			 for(int j=u-lowbit(u)+1;j<=u;j++) c[u]+=a[j];
		} 
		while(scanf("%s",cmd)!=EOF){
			if(cmd[0]=='E') break;
			else if(cmd[0]=='A'){
				scanf("%d %d",&i,&j);
				update(i,j);
			}
			else if(cmd[0]=='S'){
				scanf("%d %d",&i,&j);
				update(i,-j);
			}
			else if(cmd[0]=='Q'){
				scanf("%d %d",&i,&j);
			    printf("%d\n",sum(j)-sum(i-1));
			}
		}
	}
} 
