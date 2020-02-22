#include<iostream>
#include<cstring>
#define maxn 1000
using namespace std;
string a,b;
int f[maxn][maxn];
int main(){
	cin>>a>>b;
	memset(f,0,sizeof(f)); 
	int lena=a.length();
	int lenb=b.length();
	f[0][0]=0; 
    for(int i=1;i<=lena;i++){//小心越界！ 
    	for(int j=1;j<=lenb;j++){
    		if(a[i]==b[j]) f[i][j]=max(max(f[i-1][j-1]+1,f[i-1][j]),f[i][j-1]);
    		else f[i][j]=max(f[i-1][j],f[i][j-1]);
		}
	} 
	cout<<f[lena][lenb]<<endl;
} 
/*状态转移方程
f[i][j]:i为串a第i个位置，j为串b第j个位置,
表示串a前i个与串b前j个的公共子序列长度 

        {0   i=0,j=0
f[i][j]={f[i-1][j-1]+1  i>0,j>0,a[i]=b[i]
        {max(f[i-1][j],f[j][i-1]  i>0,j>0,a[i]!=b[i]
*/ 
