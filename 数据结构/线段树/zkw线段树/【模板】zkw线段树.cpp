#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 50005
using namespace std; 
inline int fread(){
	int x=0,sign=1;
	char c=getchar();
	while(c<'0'||c>'9'){
	    if(c=='-') sign=-1;
	    c=getchar();
    }
    while(c>='0'&&c<='9'){
    	x=x*10+c-'0';
    	c=getchar();
	}
	return x*sign;
} 
int t,n,m;
int tree[maxn<<2];
void build(){
	m=1;
	for(m=1;m<n;m<<=1);//寻找树中第一层足够容纳全部叶子节点 
	for(int i=m;i<n+m;i++) tree[i]=fread();
	for(int i=m-1;i!=0;i--) tree[i]=tree[i<<1]+tree[i<<1|1]; 
}
void update_point(int x,int v){
	x=m+x-1;
	tree[x]+=v;
	while(x!=0){
		x>>=1;
		tree[x]=tree[x<<1]+tree[x<<1|1];//向上递归 
	}
}
int query(int l,int r){
	l+=m-1;
	r+=m-1;//移动到叶子节点
	int ans=0;
	ans=ans+tree[l]+tree[r];
	if(l==r){
		return ans-tree[l];//特判 
	}
	for(;l^r^1;l>>=1,r>>=1){ //l^r^1==1表示l,r不是兄弟节点 
	    if(~l&1){//l%2==0 说明是左子节点，所以去右子节点 
	     	ans+=tree[l^1];//^1去兄弟节点 
		}
		if(r&1){//r%2==1，说明是右子节点，所以去左子节点 
			ans+=tree[r^1];
		}
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
		memset(tree,0,sizeof(tree));
		build();
		while(scanf("%s",cmd)!=EOF){
			if(cmd[0]=='E') break;
			else if(cmd[0]=='A'){
				scanf("%d %d",&i,&j);
				update_point(i,j);
			}
			else if(cmd[0]=='S'){
				scanf("%d %d",&i,&j);
				update_point(i,-j);
			}
			else if(cmd[0]=='Q'){
				scanf("%d %d",&i,&j);
			    printf("%d\n",query(i,j));
			}
		}
	}
}
