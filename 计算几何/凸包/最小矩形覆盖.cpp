#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100000
#define eps 1e-10
#define INF 1e20
using namespace std;
int n;
struct Vector{
    double x;
    double y;
    Vector(){

    }
    Vector(double _x,double _y){
        x=_x;
        y=_y;
    }
    friend Vector operator + (Vector p,Vector q){
        return Vector(p.x+q.x,p.y+q.y);
    }
    friend Vector operator - (Vector p,Vector q){
        return Vector(p.x-q.x,p.y-q.y);
    }
    friend Vector operator * (Vector a,double d){
    	return Vector(a.x*d,a.y*d);
	}
	friend Vector operator / (Vector a,double d){
		return Vector(a.x/d,a.y/d);
	}
};
typedef Vector point;
inline double dot(Vector p,Vector q){
    return p.x*q.x+p.y*q.y;
}
inline double dist(point p,point q){
    return sqrt(dot(p-q,p-q));
}
inline double cross(Vector p,Vector q){
    return p.x*q.y-p.y*q.x;
}
inline double length(Vector x){
	return sqrt(dot(x,x));
} 
point a[maxn+5];

point O;
int cmp(point P,point Q){
	double ang=cross(P-O,Q-O);
	if(fabs(ang)<eps) return dist(O,P)<dist(O,Q);
	else return ang>eps; 
} 

int top=0;
point s[maxn+5];
void Graham(){
    for(int i=1;i<=n;i++){
        if(a[i].x<a[1].x||(a[i].x==a[1].x&&a[i].y<=a[1].y)) swap(a[i],a[1]);
    }
    O=a[1];
    sort(a+2,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        while(top>1&&cross(s[top]-s[top-1],a[i]-s[top-1])<=eps) top--;//在逆时针方向，叉积<0 
        s[++top]=a[i];
    }
}


inline int nex(int x){
	return x%top+1;//不要写成成%n 
}
inline Vector rotate90(Vector p){//把向量逆时针旋转90度 
	//(xcos(a)-ysin(a),xsin(a)+ycos(a))  a=pi/2
	return Vector(-p.y,p.x);
}

point res[10];
double ans=INF;
void Spin(){
	s[top+1]=s[1];
	int l,r,p;
	l=r=p=2;
	for(int i=1;i<=top;i++){
		double D=length(s[i+1]-s[i]);
		while(cross(s[i+1]-s[i],s[p+1]-s[i])-cross(s[i+1]-s[i],s[p]-s[i])>-eps) p=nex(p);
		while(dot(s[r+1]-s[i],s[i+1]-s[i])-dot(s[r]-s[i],s[i+1]-s[i])>-eps) r=nex(r);
		if(i==1) l=r;
		while(dot(s[l+1]-s[i],s[i+1]-s[i])-dot(s[l]-s[i],s[i+1]-s[i])<eps) l=nex(l);
		 //在左侧的时候点积为负数，最小 
		double lenl=dot(s[l]-s[i],s[i+1]-s[i])/D;
		double lenr=dot(s[r]-s[i],s[i+1]-s[i])/D;
		double height=cross(s[i+1]-s[i],s[p]-s[i])/D;
		double area=(fabs(lenr)+fabs(lenl))*fabs(height);//lenl,lenr是有方向的
		if(area<ans){
			ans=area;
			res[1]=s[i]+(s[i+1]-s[i])/D*lenl;
			res[2]=s[i]+(s[i+1]-s[i])/D*lenr;
			res[3]=res[1]+rotate90((s[i+1]-s[i])/D)*height;
			res[4]=res[2]+rotate90((s[i+1]-s[i])/D)*height;
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf %lf",&a[i].x,&a[i].y);
	}
	Graham();
	Spin();
	for(int i=1;i<=4;i++){
		if(res[i].y<res[1].y||(res[i].y==res[1].y&&res[i].x<res[1].x)) swap(res[1],res[i]);
	} 
	O=res[1];
	sort(res+2,res+1+4,cmp);
	for(int i=1;i<=4;i++){
		if(fabs(res[i].x)<eps) res[i].x=0;
		if(fabs(res[i].y)<eps) res[i].y=0;
	}
	printf("%.5f\n",ans);
	for(int i=1;i<=4;i++){
		printf("%.5f %.5f\n",res[i].x,res[i].y);
	}
}
/*
6 
1.0 3.00000
1 4.00000
2.0000 1
3 0.0000
3.00000 6
6.0 3.0
*/ 
