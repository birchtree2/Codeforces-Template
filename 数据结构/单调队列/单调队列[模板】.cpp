//单调队列模板
//递减,数组模拟
//输入一串数，输出这个队列
#include<iostream>
#define ForMyLove return 0;
using namespace std;
int q[100];
int head=0,tail=0;
void push(int x){
	while(x>q[tail-1]&&head<tail) tail--;
	q[tail++]=x;
}
int pop(){
	if(head==tail) return -1;
	else{
		int t=q[head];
		head++;
		return t; 
	} 
}
int main() {
	string cmd;
	int n;
	while(cin>>cmd) {
		if(cmd=="PUSH") {
			cin>>n;
			push(n);
		}
		else if(cmd=="POP"){
			cout<<pop()<<endl;
		}
		//for(int i=head;i<tail;i++) cout<<q[i]<<' ';
		//cout<<endl;
	}
	ForMyLove
}
