//https://www.luogu.com.cn/blog/interestingLSY/cha-tou-dp-zong-jie
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 15
#define maxs 40000000
using namespace std;
typedef long long ll;
int n,m;
char tmp[maxn+5];
int a[maxn+5][maxn+5];

ll pw[maxn+5];
struct hash_table{//因为状态值太大,必须哈希完存储 
	static const int _base=131313;
	ll key[2][maxs+5];//[2]为滚动数组,存储状态 
	ll val[2][maxs+5];//存储DP值 
	int nex[maxs+5];
	int head[_base+5];
	int ptr[2];
	void insert(int now,ll k,ll v){
//		printf("insert: %lld %lld\n",k,v);
		int mo=k%_base+1;
		for(int i=head[mo];i;i=nex[i]){
			if(key[now][i]==k){//如果之前存在,直接累加 
				val[now][i]+=v;
				return;
			}
		}
		//链表插入 
		ptr[now]++;
		nex[ptr[now]]=head[mo];
		key[now][ptr[now]]=k;
		val[now][ptr[now]]=v;
		head[mo]=ptr[now]; 
	}
	inline int size(int now){
		return ptr[now];
	}
	void clear(int now){
		memset(head,0,sizeof(head));
		ptr[now]=0;
	}
}S;
int main(){
	scanf("%d %d",&n,&m);
	int tx,ty;
	for(int i=1;i<=n;i++){
		scanf("%s",tmp+1);
		for(int j=1;j<=m;j++){
			if(tmp[j]=='.'){
				a[i][j]=1;
				tx=i;
				ty=j;//记录最后一个空格的位置 
			}else a[i][j]=0; 
		}
	}
	pw[0]=1;
	for(int i=1;i<=15;i++) pw[i]=pw[i-1]<<2;
	
	int now=0,last;
	ll ans=0;
	S.insert(now,0,1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=S.size(now);j++) S.key[now][j]<<=2;////切换一行,后面整体右移一位 
		for(int j=1;j<=m;j++){
			now^=1;
			last=now^1;
			S.clear(now);
			for(int u=1;u<=S.size(last);u++){
				ll k=S.key[last][u],v=S.val[last][u];
				int p1=(k>>((j-1)*2))&3;
				int p2=(k>>(j*2))&3;//取出第j位和第j-1位 
				if(a[i][j]==0){//不通,直接继承上面的 
					if(p1==0&&p2==0) S.insert(now,k,v);
				}else if(p1==0&&p2==0){//Case 1,一个下插头和一个右插头,增加一对() 
					if(a[i+1][j]&&a[i][j+1]) S.insert(now,k+pw[j-1]*1+pw[j]*2,v);
				}else if(p1==0&&p2!=0){//Case 3.1,j-1处的竖线没被穿过,向上通过当前格,向下直走延续连通块
					if(a[i+1][j]) S.insert(now,k-pw[j]*p2+pw[j-1]*p2,v); //如果是下插头,j-1处会被穿过 
					if(a[i][j+1]) S.insert(now,k,v);  //如果是右插头,状态不变 
				}else if(p1!=0&&p2==0){//Case 3.2,j-1处的竖线被穿过向右通过当前格,向右直走延续连通块
					if(a[i+1][j]) S.insert(now,k,v);//同3.1
					if(a[i][j+1]) S.insert(now,k-pw[j-1]*p1+pw[j]*p1,v);
				}else if(p1==1&&p2==1){//Case2.1 (( ) -> ## (
					int bc=1;//记录括号匹配情况
					for(int l=j+1;l<=m;l++){
						if(((k>>(l*2))&3)==1) bc++;//左括号
						else if(((k>>(l*2))&3)==2) bc--;//右括号 
						if(bc==0){//找到匹配第j位的括号 
							S.insert(now,k-pw[j-1]*p1-pw[j]*p2-pw[l],v);
							//第l位从2变1,j-1和j变成0 
							break;
						}
					} 
				}else if(p1==1&&p2==2){//Case2.3,(),只会出现在转角 
					if(i==tx&&j==ty) ans+=v; 
				}else if(p1==2&&p2==1){//Case2.2,)(形成回路
					S.insert(now,k-pw[j-1]*p1-pw[j]*p2,v);//2,1全部变成0 
				}else if(p1==2&&p2==2){//Case2.4,)),同Case2.1反过来 
					int bc=1;//记录括号匹配情况
					for(int l=j-2;l>=0;l--){
						if(((k>>(l*2))&3)==1) bc--;//左括号
						else if(((k>>(l*2))&3)==2) bc++;//右括号 
						if(bc==0){//找到匹配第j-1位的括号 
							S.insert(now,k-pw[j-1]*p1-pw[j]*p2+pw[l],v);
							//第l位从1变2,j-1和j变成0 
							break;
						}
					} 
				}
			}
		}
	}
	printf("%lld\n",ans);
}

