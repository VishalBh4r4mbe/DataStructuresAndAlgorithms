#include <bits/stdc++.h>
using namespace std;
template <typename T> struct Point2D{
    T x, y;
    Point2D(){};
    Point2D(T _x,T _y){
        x=_x;y=_y;
    }
    Point2D& operator+=(const Point2D& other){
        x+=other.x;y+=other.y;
        return *this;
    }
    Point2D& operator-=(const Point2D& other){
        x-=other.x;y-=other.y;
        return *this;
    }
    Point2D& operator*=(T other){
        x*=other;y*=other;
        return *this;
    }
    Point2D& operator/=(T other){
        x/=other;y/=other;
        return *this;
    }
    Point2D operator+(const Point2D& other){
        return Point2D(x+other.x,y+other.y);
    }
    Point2D operator-(const Point2D& other){
        return {x-other.x,y-other.y};
    }
    Point2D operator*(T other){
        return {x*=other,y*=other};
    }
    Point2D operator/(T other){
        return {x/=other,y/=other};
    }
    inline bool operator==(const Point2D& other){
        if(other.x==x&&other.y==y)return true;
        return false;
    }
};

template <typename T> std::ostream& operator<<(std::ostream& out,const Point2D<T>& p){
    out<<p.x<<" "<<p.y;
    return out;
}
template <typename T> struct Point3D{
    T x, y,z;
    Point3D(){};
    Point3D(T _x,T _y,T _z){
        x=_x;y=_y,z=_z;
    }
    Point3D& operator+=(const Point3D& other){
        x+=other.x;y+=other.y;z+=other.z;
        return *this;
    }
    Point3D& operator-=(const Point3D& other){
        x-=other.x;y-=other.y;z-=other.z;
        return *this;
    }
    Point3D& operator*=(T other){
        x*=other;y*=other;z*=other;
        return *this;
    }
    Point3D& operator/=(T other){
        x/=other;y/=other;z/=other;
        return *this;
    }
    Point3D operator+(const Point3D& other){
        return Point3D(x+other.x,y+other.y,z+other.z);
    }
    Point3D operator-(const Point3D& other){
        return {x-other.x,y-other.y,z-other.z};
    }
    Point3D operator*(T other){
        return {x*=other,y*=other,z*=other};
    }
    Point3D operator/(T other){
        return {x/=other,y/=other,z/=other};
    }
    inline bool operator==(const Point3D& other){
        if(other.x==x&&other.y==y&&z==other.z)return true;
        return false;
    }
};

template <typename T> std::ostream& operator<<(std::ostream& out,const Point3D<T>& p){
    out<<p.x<<" "<<p.y<<" "<<p.z;
    return out;
}


int main(){
    Point2D<double> first(1,2),Second(1,2);
    first = first*3;
    //cout<<std::fixed<<std::setprecision(10);

    cout<<first;
}