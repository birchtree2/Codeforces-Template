#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<cmath>
#include<vector>
#define maxn 100005
#define maxs 2005
#define INF 0x7fffffff 
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
inline void qread(long long &x) {
	x=0;
	long long sign=1;
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
		if(x/10>0) qprint(x/10);
		putchar('0'+x%10);
	}
}

int n,m,sz,bl;
int id[maxn];
int a[maxn];
int b[maxn];
inline int lb(int id) {
	return sz*(id-1)+1;
}
inline int rb(int id) {
	return sz*id>n?n:sz*id;
}

vector<int>pos[maxn];
int get_count(int val,int l,int r) {
	return upper_bound(pos[val].begin(),pos[val].end(),r)-lower_bound(pos[val].begin(),pos[val].end(),l);
}

int cnt[maxn];
int mode[maxs][maxs];
int maxt[maxs][maxs];
void ini() {
	for(int i=1; i<=n; i++) {
		pos[a[i]].push_back(i);
	}
//	for(int i=1; i<=m; i++) {
//		sort(pos[b[i]].begin(),pos[b[i]].end());
//	}
	for(int i=1; i<=bl; i++) {
		int ans=INF;
		int tim=0;
		for(int j=lb(i); j<=n; j++) {
			cnt[a[j]]++;
			if(cnt[a[j]]>tim||(cnt[a[j]]==tim&&a[j]<ans)) {
				ans=a[j];
				tim=cnt[a[j]];
			}
			if(j%sz==0) {
				mode[i][j/sz]=ans;
				maxt[i][j/sz]=tim;
			}else if(j==n){
				mode[i][bl]=ans;
				maxt[i][bl]=tim;
			}
		}
		for(int j=lb(i); j<=n; j++) cnt[a[j]]=0;
	}
}

int query(int l,int r) {
	int ans=INF;
	int tim=0;
	if(id[l]+1<=id[r]-1) {
		ans=mode[id[l]+1][id[r]-1];
		tim=maxt[id[l]+1][id[r]-1];
	}
	for(int i=l; i<=min(r,rb(id[l])); i++) {
		int tmp=get_count(a[i],l,r);
		if(tmp>tim||(tmp==tim&&a[i]<ans)) {
			ans=a[i];
			tim=tmp;
		}
	}
	if(id[l]!=id[r]) {
		for(int i=lb(id[r]); i<=r; i++) {
			int tmp=get_count(a[i],l,r);
			if(tmp>tim||(tmp==tim&&a[i]<ans)) {
				ans=a[i];
				tim=tmp;
			}
		}
	}
//	return ans;
	return b[ans];
}

int main() {
	int l,r;
	qread(n);
	for(int i=1; i<=n; i++) {
		qread(a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	m=unique(b+1,b+1+n)-b-1;
	for(int i=1; i<=n; i++) {
		a[i]=lower_bound(b+1,b+1+m,a[i])-b;
	}
	sz=sqrt(n/(log(n)/log(2)));
	bl=1;
	for(int i=1; i<=n; i++) {
		id[i]=bl;
		if(i%sz==0) bl++;
	}
	ini();
	for(int i=1; i<=n; i++) {
		qread(l);
		qread(r);
		qprint(query(l,r));
		putchar('\n');
	}
}
