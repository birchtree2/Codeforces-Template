#include<iostream>
#include<cstdio>
#include<cstring> 
#define maxn 100000
#define maxc 26
#define INF 0x3f3f3f3f
using namespace std;
struct SAM{
#define len(x) (t[x].len)
#define link(x) (t[x].link)
	struct node{
		 int ch[maxc];
		 int link;
		 int len;
		 int now;
		 int ans;
	}t[maxn*2+5];
	const int root=1;
	int ptr=1;
	int last=root;
	inline int size(){
		return ptr;
	}
	void extend(char ch){
		int c=ch-'a';
		int p=last,cur=++ptr;
		len(cur)=len(p)+1;
		while(p&&t[p].ch[c]==0){
			t[p].ch[c]=cur;
			p=link(p);
		}
		if(p==0) link(cur)=root;
		else{
			int q=t[p].ch[c];
			if(len(p)+1==len(q)) link(cur)=q;
			else{
				int clo=++ptr;
				t[clo]=t[q];
				len(clo)=len(p)+1;
				link(q)=link(cur)=clo;
				while(p&&t[p].ch[c]==q){
					t[p].ch[c]=clo;
					p=t[p].link;
				} 
			} 
		}
		last=cur;
	} 
	void build(char *s){
		int le=strlen(s+1);
		for(int i=1;i<=le;i++) extend(s[i]);
	}
	void calc(char *s){
		int le=strlen(s+1);
		int x=root;
		int tmp=0;
		for(int i=1;i<=le;i++){
			int c=s[i]-'a';
			if(t[x].ch[c]){
				tmp++;
				x=t[x].ch[c];
			}else{
				//跳parent树
				while(x&&t[x].ch[c]==0) x=link(x);
				if(x==0){
					tmp=0;
					x=root;
				}else{
					tmp=t[x].len+1;
					x=t[x].ch[c];
				} 
			}
			t[x].now=max(t[x].now,tmp);//一个字符串里可能匹配的所有子串(即自动机上的不同路径)取max 
		}
		for(int i=1;i<=size();i++){
			t[i].ans=min(t[i].ans,t[i].now);//不同字符串取min
			t[i].now=0;
		} 
	} 
}T;

int n;
char s[maxn+5];
int main(){
	scanf("%d",&n);
	scanf("%s",s+1);
	T.build(s);
	for(int i=1;i<=T.size();i++) T.t[i].ans=INF;
	for(int i=2;i<=n;i++){
		scanf("%s",s+1);
		T.calc(s);
	}
	int ans=0;
	for(int i=1;i<=T.size();i++) ans=max(ans,T.t[i].ans);
	printf("%d\n",ans);
}

