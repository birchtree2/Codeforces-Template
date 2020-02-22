#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 1000005
using namespace std;
struct AC_automaton{
	int c[maxn][26];
	int val[maxn];
	int fail[maxn];
	int size=0;
	void insert(char *s){
		int n=strlen(s+1);
		int now=0;
		for(int i=1;i<=n;i++){
			int v=s[i]-'a';
			if(!c[now][v]) c[now][v]=++size;
			now=c[now][v];
		}
		val[now]++;
	}
	
	void build(){
		queue<int>q;
		for(int i=0;i<26;i++){
			if(c[0][i]){
				fail[c[0][i]]=0;
				q.push(c[0][i]);
			}
		}
		while(!q.empty()){
			int now=q.front();
			q.pop();
			for(int i=0;i<26;i++){
				if(c[now][i]){
					fail[c[now][i]]=c[fail[now]][i];
					q.push(c[now][i]);
				}else{
					c[now][i]=c[fail[now]][i];
				}
			}
		}
	}
	
	int query(char *s){
		int n=strlen(s+1);
		int now=0;
		int ans=0;
		for(int i=1;i<=n;i++){
			now=c[now][s[i]-'a'];
			for(int j=now;j!=0&&val[j]!=-1;j=fail[j]){
				ans+=val[j];
				val[j]=-1;
			}
		}
		return ans;
	}
}A; 
int n;
char a[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){ 
		scanf("%s",a+1);
		A.insert(a);
	} 
	A.build();
	scanf("%s",a+1);
	printf("%d\n",A.query(a)); 
}

