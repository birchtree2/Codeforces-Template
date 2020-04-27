#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath> 
#define maxn 50000
#define maxm 50000
using namespace std;
inline void qread(int &x) {
	x=0;
	int sign=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-') sign=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=x*10+c-'0';
		c=getchar();
	}
	x=x*sign;
}
inline void qprint(int x) {
	if(x<0) {
		putchar('-');
		qprint(-x);
	} else if(x==0) {
		putchar('0');
		return;
	} else {
		if(x>=10) qprint(x/10);
		putchar('0'+x%10);
	}
}
int n,m;
int a[maxn+5];
int bsz;
int belong[maxn+5];
struct query{
	int l;
	int bel;//减少数组寻址次数 
	int r;
	int id;
	friend bool operator < (query p,query q){
		return p.bel<q.bel||(p.bel==q.bel&&p.r<q.r);
	}
}q[maxm+5]; 


int ans[maxn+5];
int rb[maxn+5],lb[maxn+5];
//记录第i向左和向右的连续段长度 

//用于撤销修改操作的栈
struct node{
	int type;//记录是哪个数组修改，1则是lb,2则是rb 
	int pos;
	int val;
	node(){
		
	}
	node(int _type,int _pos,int _val){
		type=_type;
		pos=_pos;
		val=_val;
	}
}st[maxn+5];
int main(){
	qread(n);
	qread(m);
	for(int i=1;i<=n;i++) qread(a[i]);
	bsz=n/sqrt(m);
	for(int i=1;i<=n;i++) belong[i]=i/bsz+1;
	for(int i=1;i<=m;i++){
		qread(q[i].l);
		qread(q[i].r);
		q[i].id=i;
		q[i].bel=belong[q[i].l];
	}
	sort(q+1,q+1+m);
	int r=0;
	int sum=0;
	for(int i=1;i<=m;i++){
		if(q[i].bel!=q[i-1].bel){//新的块 
			sum=0;
			for(int i=1;i<=n;i++) lb[i]=rb[i]=0;
			r=q[i].bel*bsz;
		}
		while(r<q[i].r){//如果l,r不在同一个块，把r在块外部分加入,r单调递增，可不用撤销修改 
			r++;
			lb[a[r]]=lb[a[r]-1]+1;
			rb[a[r]]=rb[a[r]+1]+1;
			int tmp=lb[a[r]]+rb[a[r]]-1; 
			sum=max(sum,tmp);
			//对于a[r]两端的连续段来说，我们不需要修改每一个值的lb,rb，只需要修改段边界的就可以了
			//因为下一次插入a[r]，若a[r]已经存在，则答案不变，
			//若a[r]落在某个连续段的边界上，我们才要更新答案，而更新的答案只与段边界的lb,rb有关 
			lb[a[r]+rb[a[r]]-1]=tmp;
			rb[a[r]-lb[a[r]]+1]=tmp;
		}
		int res=sum;//由于撤销对sum的修改比较麻烦，移动左端点的时候不更新sum,而更新答案res 
		int top=0;
		//min(q[i].r,q[i].bel*bsz)表示把询问在当前块内部分加入 
		for(int l=q[i].l;l<=min(q[i].r,q[i].bel*bsz);l++){//移动左端点，要回滚 
			lb[a[l]]=lb[a[l]-1]+1;
			rb[a[l]]=rb[a[l]+1]+1;
			int tmp=lb[a[l]]+rb[a[l]]-1;
			st[++top]=node(1,a[l]+rb[a[l]]-1,lb[a[l]+rb[a[l]]-1]);//修改前把原来的值记下来 
			st[++top]=node(2,a[l]-lb[a[l]]+1,rb[a[l]-lb[a[l]]+1]);
			lb[a[l]+rb[a[l]]-1]=tmp;
			rb[a[l]-lb[a[l]]+1]=tmp;
			res=max(res,tmp);
		}
		for(int j=top;j>=1;j--){//撤销对连续段端点的修改 
			if(st[j].type==1) lb[st[j].pos]=st[j].val;
			else rb[st[j].pos]=st[j].val; 
		}
		for(int j=q[i].l;j<=min(q[i].r,q[i].bel*bsz);j++){//撤销新加入的点对lb,rb的修改 
			lb[a[j]]=rb[a[j]]=0;
		} 
		ans[q[i].id]=res; 
	}
	for(int i=1;i<=m;i++){
		qprint(ans[i]);
		putchar('\n');
	}
}

