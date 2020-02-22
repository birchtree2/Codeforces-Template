#include<iostream>
#include<cstdio>
using namespace std;
inline int qread_int(){
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
inline long long qread_ll(){
	long long x=0,sign=1;
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
struct node{
	int l;
	int r;
	long long v;
	node* lson;
	node* rson;
};
node* root=NULL;
long long m,d,last_q;
int n,cnt,l;
void ini(){
	root=new node();
	root->l=1;
	root->r=m;
	root->v=0;
	root->lson=NULL;
	root->rson=NULL;
}
void update(int pos,long long value,node* root){
	if(root->l==root->r){
		root->v=value;
		return;
	} 
	int mid=(root->l+root->r)/2;
	if(pos<=mid){
		if(root->lson==NULL){
			root->lson=new node();
			root->lson->l=root->l;
			root->lson->r=mid;
			root->lson->v=0;
			root->lson->lson=NULL;
			root->lson->rson=NULL;
			update(pos,value,root->lson);
		}else{
			update(pos,value,root->lson);
		}
	}else{
		if(root->rson==NULL){
			root->rson=new node();
			root->rson->l=mid+1;
			root->rson->r=root->r;
			root->rson->v=0;
			root->rson->lson=NULL;
			root->rson->rson=NULL;
			update(pos,value,root->rson);
		}else{
			update(pos,value,root->rson);
		}
	}
	if(root->lson!=NULL&&root->rson!=NULL) root->v=max(root->lson->v,root->rson->v);
	if(root->lson!=NULL&&root->rson==NULL) root->v=root->lson->v;
	if(root->lson==NULL&&root->rson!=NULL) root->v=root->rson->v;
}
long long query(int L,int R,node* root){
	if(root->l>=L&&root->r<=R){
		return root->v;
	}
	int mid=(root->l+root->r)/2;
	long long ans=0;
	if(L<=mid&&root->lson!=NULL) ans=max(ans,query(L,R,root->lson));
	if(R>mid&&root->rson!=NULL) ans=max(ans,query(L,R,root->rson));
	return ans;
}
int main(){
	//m=qread_int();
	//d=qread_ll();
	scanf("%d",&m);
	scanf("%lld",&d);
	char cmd;
	ini();
	while(m--){
		cin>>cmd;
		if(cmd=='Q'){
			//l=qread_int();
			cin>>l;
			last_q=query(cnt-l+1,cnt,root);
			printf("%lld\n",last_q);
		}else if(cmd=='A'){
			cnt++;
			cin>>n;
			long long tmp=(long long)(n+last_q)%d;
			update(cnt,tmp,root);
		}
	}
}
