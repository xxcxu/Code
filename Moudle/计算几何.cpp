#include <bits/stdc++.h>
static const double eps = 1e-8; // zi ding yi
static const double pi = acos(-1);
bool equal(double a, double b) {return std::fabs(a - b) <= eps;}
struct Vector {
	double x, y;
	Vector(double a = 0.0, double b = 0.0): x(a), y(b) {}
	friend Vector operator + (const Vector &a, const Vector &b) {return Vector(a.x + b.x, a.y + b.y);}
	friend Vector operator - (const Vector &a, const Vector &b) {return Vector(a.x - b.x, a.y - b.y);}
	friend double operator ^ (const Vector &a, const Vector &b) {return a.x * b.x + a.y * b.y;} // 点积
	friend double operator * (const Vector &a, const Vector &b) {return a.x * b.y - a.y * b.x;} // 叉积
	friend Vector operator * (const Vector &a, const double &b) {return Vector(a.x * b, a.y * b);}
	friend bool   operator == (const Vector &a, const Vector &b) {return equal(a.x, b.x) && equal(a.y, b.y);}
	friend double len(const Vector &a) {return std::sqrt(a.x * a.x, a.y * a.y);}
	friend Vector rorate(const Vector &a, const double &b) {return Vector(a.x * cos(b) - a.y * sin(b), a.x * sin(b) + a.y * sin(b));}
	friend bool   operator < (const Vector &a, const Vector &b) {return (a.x < b.x) || (a.y < b.y);}
};
struct Line {
	Vector a, b;
    friend Line move(const Line &l, const double &k) {
        double d_v = len(l.b);
        Vector temp = Vector(-l.b.y, l.v.x) * (1.0 / k);
        return Line(l.a + temp * k, l.b);
    }
    friend Vector point(cosnt double &a, const double &k) {return a.a + a.b * t;}   
};
struct Circle {
    Vector c; double r;
    friend Vector point(const Circie &a, const double &k) {return c + Vector(r * cos(k), r * sin(k));}
};
double degree(Vector &a) {return atan2(a.y, a.x);}
double mod(double a, double b) {return a - b * floor(a / b);}
double change(double a) {return mod(a / 180 * pi, 2 * pi);}
bool   onSegment(Vector a, Vector p1, Vector p2) {}

In bool onSeg(Vec A, Vec p1, Vec p2)					      //A在线段p1p2上,dcmp小于等于/小于0表示含/不含端点 
{
	return dcmp((p1 - A) * (p2 - A)) == 0 && dcmp((p1 - A) ^ (p2 - A)) < 0;
}
In bool Cross(Vec A, Vec B, Vec C, Vec D)				      //判断两条线段是否相交 
{
	if(onSeg(A, C, D) || onSeg(B, C, D) || onSeg(C, A, B) || onSeg(D, A, B)) return 1;	//加上这一句表示算端点 
	return dcmp((B - A) * (C - A)) * dcmp((B - A) * (D - A)) < 0 && dcmp((D - C) * (A - C)) * dcmp((D - C) * (B - C)) < 0;
}
In Vec getCross(Vec A, Vec B, Vec C, Vec D)				      //计算两条直线的交点 
{
	Vec v = B - A, w = D - C, u = A - C;
	db tp = (w * u) / (v * w);
	return A + v * tp;
}
In db getDisPtL(Vec P, Vec A, Vec B)					      //计算点P到直线AB的距离 
{
	db S = (B - A) * (P - A);
	return fabs(S) / dis(B - A);
}
In db getLAD(Vec V)							      //计算直线的倾斜角（角度制） 
{
	db ang = atan(V.y / V.x) / PI * 180;
	while(ang < 0) ang += 360;
	while(dcmp(ang - 180) >= 0) ang -= 180;
	return ang; 
}

In bool disCC(Cir C1, Cir C2)						      //判断两圆是否相离（包含外切） 
{      
	return dcmp(dis(C1.C - C2.C) - (C1.r + C2.r)) >= 0;
}
In int getCrossCL(Lin l, Cir C, vector<Vec>& ans)		              //求直线和圆的交点，结果储存在ans中，返回交点个数 
{
	db a = l.v.x, b = l.A.x - C.C.x, c = l.v.y, d = l.A.y - C.C.y;
	db e = a * a + c * c, f = (a * b + c * d) * 2, g = b * b + d * d - C.r * C.r;
	db del = f * f - e * g * 4;
	if(dcmp(del) < 0) return 0;
	if(dcmp(del) == 0) {ans.push_back(l.Point(-f / (e * 2))); return 1;}
	ans.push_back(l.Point((-f - sqrt(del)) / (e * 2)));
	ans.push_back(l.Point((-f + sqrt(del)) / (e * 2)));
	return 2;
}
In int getCrossCC(Cir C1, Cir C2, vector<Vec>& ans)		              //计算两个圆的交点 
{      
	db d = dis(C1.C - C2.C);
	if(dcmp(d) == 0) return dcmp(C1.r - C2.r) ? 0 : -1;
	if(dcmp(d - C1.r - C2.r) > 0 || dcmp(fabs(C1.r - C2.r) - d) > 0) return 0;
	db a = Ang(C2.C - C1.C), d1 = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (C1.r * d * 2));//acos(d / 2 / C1.r);
	Vec p1 = C1.Point(a + d1), p2 = C1.Point(a - d1);
	ans.push_back(p1); if(p1 == p2) return 1;
	ans.push_back(p2); return 2;
}

In db calcS(Vec* p, int n)						     //计算一个多边形的面积 
{
	db ret = 0;
	for(int i = 2; i < n; ++i)
		ret += (p[i] - p[1]) * (p[i + 1] - p[1]);
	return fabs(ret / 2); 
}

In int PiP(Vec A, Vec* p, int n)					     //判定点是否在多边形内 
{
	int wn = 0;
	p[0] = p[n]; 
	for(int i = 1; i <= n; ++i)
	{
		Vec p1 = p[i - 1], p2 = p[i]; 
		if(onSeg(A, p1, p2)) return -1;
		int k = dcmp((p2 - p1) * (A - p1));
		int d1 = dcmp(p1.y - A.y), d2 = dcmp(p2.y - A.y);
		if(k > 0 && d1 <= 0 && d2 > 0) wn++;
		if(k < 0 && d2 <= 0 && d1 > 0) wn--;
	}
	p[0] = (Vec){0, 0};
	return wn != 0;
}

Vec S;									    //求凸包，返回凸包数组st和大小top. 
In bool cmpP(Vec A, Vec B)
{
	db s = (A - S) * (B - S);
	return dcmp(s) ? s > 0 : dis(A - S) < dis(B - S);
}
In db calcP(Vec A, Vec B, Vec C) {return (B - A) * (C - A);}
In void getPol(Vec* p, int n, Vec* st, int& top)
{
	int id = 1;
	for(int i = 2; i <= n; ++i)
		if(p[i].x < p[id].x || (!dcmp(p[i].x - p[id].x) && p[i].y < p[id].y)) id = i;
	if(id ^ 1) swap(p[1], p[id]);
	S = p[1];
	sort(p + 2, p + n + 1, cmpP);
	st[top = 1] = p[1];
	for(int i = 2; i <= n; ++i)
	{
		while(top > 1 && calcP(st[top - 1], st[top], p[i]) < 0) top--;
		st[++top] = p[i];
	}	
}