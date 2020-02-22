#include<iostream>
#include<cstring>
#define maxn 151
using namespace std;
string a,b;
int f[maxn][maxn],d[maxn][maxn];
int lena,lenb;
void my_print(int x,int y) {
	if(!d[x][y])
		return;
	if(d[x][y]==1) my_print(x-1,y);	//×ó
	if(d[x][y]==2) my_print(x,y-1);	//ÉÏ
	if(d[x][y]==3) {
		my_print(x-1,y-1);	//×óÉÏ
		cout<<b[x-1];
	}
}
int main() {
	cin>>a>>b;
	lena=a.length();
	lenb=b.length();
	for(int i=1; i<=lenb; i++) {
		for(int j=1; j<=lena; j++) {
			if(a[j-1]==b[i-1]) {
				int temp=max(max(f[i-1][j-1]+1,f[i][j-1]),f[i-1][j]);
				f[i][j]=temp;
				if(f[i-1][j-1]+1==temp) {
					d[i][j]=3;
				} else if(f[i][j-1]==temp) {
					d[i][j]=2;
				} else {
					d[i][j]=1;
				}
			} else if(f[i][j-1]>f[i-1][j])	{
				f[i][j]=f[i][j-1];
				d[i][j]=2;
			} else {
				f[i][j]=f[i-1][j];
				d[i][j]=1;
			}
		}
	}
	cout<<f[lenb][lena]<<endl;
	my_print(lenb,lena);
	return 0;
}
