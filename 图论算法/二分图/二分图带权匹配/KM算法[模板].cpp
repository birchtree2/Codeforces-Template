/*

            -. .
       _____   ',' ,
     ,'     ,'   ', ',
   ,'     ,'      |  |
  \       \       |  |
    \ /^\   \    ,' ,'
          \   \ ,' ,'      L'Internationale,
    / ~-.___\.-'  ,'            Sera le genre humain.
  /   .______.- ~ \
/   /'          \   \
\./               \/'

Problem:KM算法模板 
Source:
Algorithm:KM
Description:模板题 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 205
#define INF 0x3f3f3f3f
using namespace std;
int n,m;
int dist[maxn][maxn];
int la[maxn];
int lb[maxn];
int va[maxn];
int vb[maxn];
int match[maxn];
int delta;
int dfs(int x){
	va[x]=1;
	for(int y=1;y<=n;y++){
		if(!vb[y]&&dist[x][y]!=INF){
			if(la[x]+lb[y]==dist[x][y]){
				vb[y]=1;
				if(!match[y]||dfs(match[y])){
					match[y]=x;
					return 1;
				}
			}else{
				delta=min(delta,la[x]+lb[y]-dist[x][y]);
			}
		}
	}
	return 0;
}

int KM(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(dist[i][j]!=INF)la[i]=max(la[i],dist[i][j]);
		}
		lb[i]=0;
	}
	for(int i=1;i<=n;i++){
		while(1){
			memset(va,0,sizeof(va));
			memset(vb,0,sizeof(vb));
			delta=INF;
			if(dfs(i)) break;
			for(int j=1;j<=n;j++){
				if(!va[j]) continue;
				for(int k=1;k<=n;k++){
					if(!vb[k]&&dist[j][k]!=INF){
						delta=min(delta,la[j]+lb[k]-dist[j][k]);
					}
				}
			}
			if(delta==INF) return -1;
			for(int j=1;j<=n;j++){
				if(va[j]) la[j]-=delta;
				if(vb[j]) lb[j]+=delta;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=dist[match[i]][i];
	}
	return ans;
}


int main(){
	int u,v,w;
	scanf("%d %d",&n,&m);
	memset(dist,0x3f,sizeof(dist));
	for(int i=1;i<=m;i++){
		scanf("%d %d %d",&u,&v,&w);
		dist[u][v]=w;
	}
	printf("%d\n",KM());
}
/*
3 4
1 2 10
2 3 10
3 1 10
3 2 1
*/

