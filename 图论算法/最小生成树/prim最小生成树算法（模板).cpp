//洛谷 【模板】最小生成树
//无优化 O(n^2) 
#include<iostream>
#include<cstring> 
#define maxn 5005
#define INF  99999999
int n,m;
long long ans;
int g[maxn][maxn];
int key[maxn];
int used[maxn];
using namespace std;
long long prim(){
    memset(key,0x7f,sizeof(key));	
    key[1]=0;
    memset(used,0,sizeof(used));
    for(int i=1;i<=n;i++){
        int k=0;
        //int min=INF;
        for(int j=1;j<=n;j++){
            if(used[j]==0&&key[j]<key[k])
              k=j;
        } 
        used[k]=1;
        for(int j=1;j<=n;j++){
        	if(used[j]==0&&g[k][j]<key[j])
        	    key[j]=g[k][j];
        }
    }
    long long sum=0;
    for(int u=1;u<=n;u++) sum+=key[u];
    return sum;
}
int main(){
    int a,b,c;
    cin>>n>>m;
     for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){ 
            if(i==j)g[i][j]=0;
            else g[i][j]=INF;
        }
	} 
    for(int i=1;i<=m;i++){
   	     cin>>a>>b>>c;
   	    if(c<g[a][b])
   	     {
   	     	g[a][b]=g[b][a]=c;
        }
   	      
    }
    ans=prim();
    if(ans>=10000000)cout<<"orz"<<endl;
    else cout<<ans;
    return 0;
} 
