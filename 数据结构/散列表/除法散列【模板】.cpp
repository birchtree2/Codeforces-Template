#include<iostream>
#define maxn 20005
using namespace std;
const int  c=13131;
struct myhash {
	struct node {
		long long v;
		long long cnt; 
		node* next;
	};
	node a[maxn];
	void set0(){
		for(int i=0;i<maxn;i++){
			a[i].v=0;
			a[i].next=NULL;
		}
	}
	void push(long long x) {
		long long t;
		if(x<0) t=-x;
		else t=x;
		node *tmp=a[t%c].next;
		if(tmp==NULL){
			tmp=new node();
			tmp->v=x;
			tmp->cnt=1;
			tmp->next=NULL; 
			a[t%c].next=tmp;
			return;
		}
		while(tmp!=NULL){
			if(tmp->v==x){
				tmp->cnt++;
				return;
			} 
		}
		if(tmp==NULL){ 
			node *tmp=new node();
			tmp->v=x;
			tmp->next=a[t%c].next;
			a[t%c].next=tmp;
		} 
	}
	int is_found(long long x) {
		long long t;
		if(x<0) t=-x;
		else t=x;
		if(a[t%c].next==NULL) return 0;
		else {
			node* tmp=a[t%c].next;
			while(tmp!=NULL) {
				if(tmp->v==x) return tmp->cnt;
				tmp=tmp->next;
			}
			return 0;
		}
	}
};
myhash H;
int main() {
	char c;
	long long x;
	//freopen("data.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	while(cin>>c>>x) {
		if(c=='A') H.push(x);
		else cout<<(H.is_found(x))<<endl;
	}
}
/*输入A X,表示插入x
  输入B X,表示查找x
*/
