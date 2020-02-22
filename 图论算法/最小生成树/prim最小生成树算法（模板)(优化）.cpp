#include<iostream>
#include<cstring>
#include<queue>
#define maxn 5005
#define maxm 2*200000+5
using namespace std;
int n,m;
int head[maxn];
int key[maxn],used[maxn];
struct edge_table{
	int to;
	int next;
	int value;
}edge[maxm]; 
int edge_cnt=0;
struct heap_node{
	int id;
	int value;
	friend bool operator <(heap_node a,heap_node b){
		return a.value>b.value;
	}
};
void add_edge(int u,int v,int w){
	edge[++edge_cnt].to=v;
	edge[edge_cnt].value=w;
	edge[edge_cnt].next=head[u];
	head[u]=edge_cnt;
} 
int prim(){
	int ans=0,tot=0;
	memset(key,0x7f,sizeof(key));
	memset(used,0,sizeof(used));
	priority_queue<heap_node>heap;
	heap_node now,nex;
	now.id=1;
	now.value=key[1]=0;
	heap.push(now);
	while(!heap.empty()){
		now=heap.top();
		heap.pop();
		int u=now.id;
		if(now.value!=key[u]) continue;
		used[u]=1;
		ans+=key[u];
		tot++;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].to;
			if(used[v]==0&&key[v]>edge[i].value){
				key[v]=edge[i].value;
				nex.value=key[v];
				nex.id=v;
				heap.push(nex);
			} 
		}
	}
	if(tot<n) ans=-1;
	return ans;
}
int main(){
	cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        add_edge(a,b,c);
        add_edge(b,a,c);
    }
    int ans=prim();
    if(ans==-1) cout<<"orz"<<endl;
    else cout<<ans;
} 
