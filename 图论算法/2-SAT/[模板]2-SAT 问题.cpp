#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector> 
#include<stack> 
#define maxn 1000000
using namespace std;
int n,m;
vector<int>E[maxn*2+5];
void add_edge(int u,int v){
	E[u].push_back(v);
}
inline int get_op(int x){
	if(x%2==1) return x+1;
	else return x-1; 
} 

int dfn[maxn*2+5];
int low[maxn*2+5];
stack<int>s;
int cnt=0,tim=0;
int bel[maxn*2+5];
bool ins[maxn*2+5];
void tarjan(int x){
	dfn[x]=low[x]=++tim;
	s.push(x);
	ins[x]=1;
	for(int y : E[x]){
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]); 
		}else if(ins[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		cnt++;
		int y;
		do{
			y=s.top();
			s.pop();
			ins[y]=0;
			bel[y]=cnt;
		}while(y!=x); 
	}
}

bool check(){
	for(int i=1;i<=n*2;i++){
		if(!dfn[i]) tarjan(i);
	}
	for(int i=1;i<=n;i++){
		if(bel[i]==bel[i+n]) return 0;
	}
	return 1;
}
int main(){
	int u,v,p,q;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d %d %d",&u,&p,&v,&q);
		add_edge(u+(1-p)*n,v+q*n);//如果u不为p，那么v一定为q,否则就不满足条件了 
		add_edge(v+(1-q)*n,u+p*n);
	}
	if(check()){
		puts("POSSIBLE");
		for(int i=1;i<=n;i++){
			if(bel[i]<bel[i+n]) printf("0 ");
			else printf("1 ");
		}
	}else puts("IMPOSSIBLE");
}

