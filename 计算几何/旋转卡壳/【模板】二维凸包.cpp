//https://www.luogu.org/problem/P2742
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<algorithm>
#define maxn 50000
#define eps 1e-6
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
    friend bool operator < (Vector p,Vector q){
        if(p.x==q.x) return p.y<q.y;
        else return p.x<q.x;
    }
};
typedef Vector point;
inline double dot(Vector p,Vector q){
    return p.x*q.x+p.y*q.y;
}
inline double dist(point p,point q){
    return sqrt(dot(p-q,p-q));
}
inline double dist2(point p,point q){
    return dot(p-q,p-q);
}
inline double cross(Vector p,Vector q){
    return p.x*q.y-p.y*q.x;
}


point a[maxn+5];
int cmp(point x,point y){
    double ang=cross(x-a[1],y-a[1]);
    if(fabs(ang)<eps) return dist(a[1],x)<dist(a[1],y);
    else return ang>eps; 
} 

int top;
point s[maxn+5];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lf %lf",&a[i].x,&a[i].y);
    }
    for(int i=1;i<=n;i++){
        if(a[i]<a[1]) swap(a[i],a[1]);
    }
    sort(a+2,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        while(top>1&&cross(s[top]-s[top-1],a[i]-s[top-1])<=eps) top--;//Ò»¶¨Òª>=0 
        s[++top]=a[i];
    }
    double ans=0; 
    s[top+1]=s[1];
    for(int i=1;i<=top;i++) ans+=dist(s[i],s[i+1]);
    printf("%.2f",ans);
}
