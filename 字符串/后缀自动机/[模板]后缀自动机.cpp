#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
#define maxn 1000000
#define maxc 26
using namespace std;
struct SAM {
//#define len(x) (t[x].len)
//#define link(x) (t[x].link)
	struct node {
		int len;
		int link;
		int ch[maxc+1];
	} t[maxn*2+5];
	int mark[maxn*2+5];
	int sz=1;
	int last=1;
	void insert(int c) {
		int p=last,cur=last=++sz;
		mark[cur]=1;
		t[cur].len=t[p].len+1;
		while(p>0&&t[p].ch[c]==0){
			t[p].ch[c]=cur;
			p=t[p].link;
		}
		if(p==0) t[cur].link=1;
		else{
			int q=t[p].ch[c];
			if(t[p].len+1==t[q].len) t[cur].link=q;
			else{
				int clo=++sz;
				t[clo]=t[q];
				t[clo].len=t[p].len+1;
				t[q].link=t[cur].link=clo;
				while(p>0&&t[p].ch[c]==q){
					t[p].ch[c]=clo;
					p=t[p].link;
				}

			}
		}
	}
//#undef len
//#undef link
} S;

long long ans=0;
vector<int>E[maxn*2+5];
int sz[maxn*2+5];
inline void add_edge(int u,int v) {
//	printf("%d->%d\n",u,v);
	E[u].push_back(v);
}
void dfs(int x) {
	sz[x]=S.mark[x];
	for(int i=0; i<(int)E[x].size(); i++) {
		int y=E[x][i];
		dfs(y);
		sz[x]+=sz[y];
	}
	if(sz[x]!=1) ans=max(ans,1ll*sz[x]*S.t[x].len);
}

int n;
char in[maxn+5];
int main() {
	scanf("%s",in+1);
	n=strlen(in+1);
//	S.ini();
	for(int i=1; i<=n; i++) {
		S.insert(in[i]-'a');
//		printf("ok %d\n",i);
	}
	for(int i=2;i<=S.sz;i++) add_edge(S.t[i].link,i);
	dfs(1);
	printf("%lld\n",ans);
}

