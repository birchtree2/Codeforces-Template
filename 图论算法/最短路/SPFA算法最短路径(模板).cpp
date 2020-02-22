//洛谷 【模板】单源最短路径 
#include<iostream>
#include<cstring>
#include<cstdio>
#define maxn 500005
using namespace std;
int n,m,s;
struct node{
	int to;
	int next;
	int value;
}edge[maxn]; //邻接表 
int cnt=0;
int head[maxn],used[maxn],d[maxn],queue[maxn];
inline int fastread(){
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
void addedge(int x,int y,int z){
	cnt++;
	edge[cnt].to=y;
	edge[cnt].next=head[x];
	edge[cnt].value=z;
	head[x]=cnt;
} 
void spfa(){
	int tmp;
	int qhead=0,qtail=1;
	queue[1]=s;
	used[s]=1;
	d[s]=0;
	while(qhead<qtail){
		tmp=queue[++qhead];
		used[tmp]=0;
		for(int i=head[tmp];i!=-1;i=edge[i].next){
			if(d[tmp]+edge[i].value<d[edge[i].to]){
				d[edge[i].to]=d[tmp]+edge[i].value;
				if(used[edge[i].to]==0){
					used[edge[i].to]==1;
					queue[++qtail]=edge[i].to;
				}
			}
		}
	}
}
int main(){
	int x,y,z;
	cin>>n>>m>>s;
	memset(head,-1,sizeof(head));
	memset(d,127,sizeof(d));
	for(int i=1;i<=m;i++){
		//cin>>x>>y>>z;
		x=fastread();y=fastread();z=fastread();    //此为有向图 
		addedge(x,y,z);
	}
	spfa();
	for(int i=1;i<=n;i++)
    {
        if(i==s) cout<<"0 ";
        else if(d[i]>=0x3f3f3f3f) cout<<"2147483647 ";//如果没有被连，那就输出2147483647 
        else cout<<d[i]<<' '; 
    }
    return 0;
}
