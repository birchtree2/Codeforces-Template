#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib> 
#define maxn 200000
#define maxlogn 128
using namespace std;
int n;
struct node{
    int ls;
    int rs;
    long long val;
    long long sum;
    int dat;
    int sz;
    int mark;
}tree[maxn*maxlogn+5];
int ptr=0;
int root[maxn+5];
int New(long long val){
    ptr++;
    tree[ptr].val=tree[ptr].sum=val;
    tree[ptr].dat=rand();
    tree[ptr].sz=1;
    return ptr;
}
int copy(int last){
    int x=++ptr;
    tree[x]=tree[last];
    return x;	
}
void push_up(int x){
    tree[x].sz=tree[tree[x].ls].sz+tree[tree[x].rs].sz+1;
    tree[x].sum=tree[tree[x].ls].sum+tree[tree[x].rs].sum+tree[x].val;
}
void push_down(int x){
    if(tree[x].mark){
        if(tree[x].ls) tree[x].ls=copy(tree[x].ls);
        if(tree[x].rs) tree[x].rs=copy(tree[x].rs);
        swap(tree[x].ls,tree[x].rs);
        if(tree[x].ls) tree[tree[x].ls].mark^=1;
        if(tree[x].rs) tree[tree[x].rs].mark^=1;
        tree[x].mark=0;
    }
}
void split(int now,int k,int &x,int &y){
    if(now==0){
        x=0;
        y=0;
        return;
    }
    push_down(now);
    if(k<=tree[tree[now].ls].sz){
        y=copy(now);
        split(tree[y].ls,k,x,tree[y].ls);
        push_up(y);
    }else{
        x=copy(now);
        split(tree[x].rs,k-tree[tree[now].ls].sz-1,tree[x].rs,y);
        push_up(x);
    }
}
int merge(int x,int y){
    if(!x||!y) return x+y;
    push_down(x);
    push_down(y);
    if(tree[x].dat<tree[y].dat){
        tree[x].rs=merge(tree[x].rs,y);
        push_up(x);
        return x;
    }else{
        tree[y].ls=merge(x,tree[y].ls);
        push_up(y);
        return y;
    }
}

int cnt=0;
void insert(int ver,int p,int val){
    int x,y;
    split(root[ver],p,x,y);
    root[++cnt]=merge(merge(x,New(val)),y);
}
void del(int ver,int p){
    int x,y,z;
    split(root[ver],p,x,z);
    split(x,p-1,x,y);
    root[++cnt]=merge(x,z);
}
void reverse(int ver,int l,int r){
    int x,y,z;
    split(root[ver],r,x,z);
    split(x,l-1,x,y);
    tree[y].mark^=1;
    root[++cnt]=merge(merge(x,y),z);
}
long long query_sum(int ver,int l,int r){
    int x,y,z;
    split(root[ver],r,x,z);
    split(x,l-1,x,y);
    long long ans=tree[y].sum;
    root[++cnt]=merge(merge(x,y),z);
    return ans;
}

int main(){
    long long last=0;
    long long p,val,l,r;
    int ver,op;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d %d",&ver,&op);
        if(ver==6){
            ver=6;
        }
        if(op==1){
            scanf("%lld %lld",&p,&val);
            p^=last;
            val^=last;
            insert(ver,p,val);
        }else if(op==2){
            scanf("%lld",&p);
            p^=last;
            del(ver,p);
        }else if(op==3){
            scanf("%lld %lld",&l,&r);
            l^=last;
            r^=last;
            reverse(ver,l,r);
        }else{
            scanf("%lld %lld",&l,&r);
            l^=last;
            r^=last;
            last=query_sum(ver,l,r);
            printf("%lld\n",last);
        }
    }
}

