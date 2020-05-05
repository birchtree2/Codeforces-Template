#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100
using namespace std;
double mat[maxn+5][maxn+5];
bool gauss(int n,int m){
	for(int i=1;i<=n;i++){
		int id=i;
		for(int j=i+1;j<=n;j++){
			if(mat[j][i]>mat[id][i]) id=j;
		}
		for(int k=1;k<=m;k++) swap(mat[i][k],mat[id][k]);
		if(mat[i][i]==0) return 0;
		for(int j=1;j<=n;j++){
			if(j==i) continue;
			double r=mat[j][i]/mat[i][i];
			for(int k=1;k<=m;k++) mat[j][k]-=mat[i][k]*r;
		}
	}
	for(int i=1;i<=n;i++){
		mat[i][m]/=mat[i][i];
	}
	return 1;
} 

int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n+1;j++){
			scanf("%lf",&mat[i][j]);
		}
	}
	if(gauss(n,n+1)){
		for(int i=1;i<=n;i++) printf("%.2f\n",mat[i][n+1]);
	}else printf("No Solution"); 
}
