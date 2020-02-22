/*
M个旅行商从同一个(或不同的城市,以题目为准)出发，分别走一条路线，使每一个城市有且仅有一个旅行商经过（出发城市除外）
求最短的总路程
best[i]=min(best[i],best[i&~j]+best[j])
*/ 
#include<iostream>
using namespace std;
int n;
int dp[][],best[];
void tsp(){
	memset(dp,0x3f,sizeof(dp));
	for(int i=0;i<n;i++){
		dp[1<<i][i]=0;
	}
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<n;i++){
			if(s&(1<<i)==0) continue;
			for(int j=0;j<n;j++){
				if(i==j||s&(1<<j)==0) continue;
				dp[s][i]=min(dp[s][i],dp[s&~(1<<i)][j]+dis[j][i])
			}
			best[s]=min(best[s],dp[s][i]);
		}
	}
}
int mtsp(){
	tsp();
	for(int i=0;i<(1<<n);i++){
		//for(int j=i-1;j>0;j--){
		//为了保证i包含j,用i&j
		//如：i=1100,j=1010,i&j=1000
		for(int j=i&(i-1);j>0;j=i&(j-1))
			best[i]=min(best[i],best[i-j]+best[j]);//如果是规定1开始，则best[(i-j)|1],保证状态合法 
		}
	}
	return best[(1<<n)-1];
}
int main(){
	input();
	cout<<mtsp();
}
