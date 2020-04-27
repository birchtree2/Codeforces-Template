//朴素TSP
/*问题：假设有一个旅行商人要拜访N个城市，他必须选择所要走的路径，
路径的限制是每个城市只能拜访一次，而且最后要回到原来出发的城市（哈密顿环路），
要求路径的总和最小 
*/ 
/*分析：状态压缩 点集s
	   把集合s中第i个点删除： s&=~(1<<i)
	   判断第i个点是否属于集合s： if(s&(1<<i)==0) return false; else return true;
	   
	   状态dp[s][i]：以s为点集，当前在第i个节点的最小总和 
	   状态转移方程：dp[i][j]=min(dp[s&~(1<<i)][j]+dis[j][i],dp[i][j])
	   j为点集s中不等于i的一个点 
*/
#include<iostream>
#include<cstring>
#include<cmath> 
#define maxn 17
using namespace std;
int n;
struct node{
	double x;
	double y;
}dot[maxn];
double dis[maxn][maxn];
double dp[1<<maxn][maxn];
double cal_dist(double x1,double y1,double x2,double y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
void ini(){
	for(int i=0;i<(1<<n);i++){
		for(int j=0;j<n;j++){
			dp[i][j]=0x7fffffff;
		}
	}
	
	dp[1][0]=0;//若需回到起点，只要把起点1设为0 
	//若不需回到起点for(int i=0;i<n;i++) dp[(1<<i)][i]=0;//把1,10等每一个可能起始点设成0        
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			dis[i][j]=dis[j][i]=cal_dist(dot[i].x,dot[i].y,dot[j].x,dot[j].y);
		}
	}
}
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>dot[i].x>>dot[i].y;
	}
	ini();
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<n;i++){
			if(s&(1<<i)==0) continue;
			for(int j=0;j<n;j++){
				if(i!=j&&(s&(1<<j))>0){
					dp[s][i]=min(dp[s&(~(1<<i))][j]+dis[j][i],dp[s][i]);
					//debug();
				}
			}
		}
	}
	double ans=0x7fffffff;
	for(int i=0;i<n;i++){
		ans=min(ans,dp[(1<<n)-1][i]+dis[i][0]);
	}
	cout<<ans<<endl; 
	//debug();
}
/*
3
2.5 4.0
1.2 -2.4
8.7 1.2
*/
