// 计算几何.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<string>
#include<cmath>
#include<cstring>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<deque>
#include<iomanip>
#include<sstream>
#include<stack>
#include<iostream>
#include<limits>
#include<bitset>
#include<list>
#include<queue>
#include<memory>
#include<functional>
using namespace std;
typedef long long LL;
namespace Computational_geometry
{
	const double PI = acos(-1.0);//pi=3.1415926535897932
	const double EPS = 1e-8;
	int dcmp(double x) //比较用，减小精度误差
	{
		if (fabs(x) < EPS)
			return 0;
		else
			return x < 0 ? -1 : 1;
	}
	struct Point_2D
	{
		double x, y;
		Point_2D(double a = 0, double b = 0) :x(a), y(b) {}//二维点
		double distance(Point_2D &b)
		{
			return sqrt(pow(b.x - x, 2) + pow(b.y - y, 2));
		}
		bool operator==(Point_2D &b)
		{
			if (dcmp(x - b.x) == 0 && dcmp(y - b.y) == 0)
				return true;
			return false;
		}
		friend bool operator<(Point_2D a, Point_2D b)//水平序排序
		{
			if (dcmp(a.x-b.x) == 0)
				return a.y < b.y;
			else
			{
				return a.x < b.x;
			}
		}
	};
	struct Point_3D
	{
		double x, y, z;
		Point_3D(double a = 0, double b = 0, double c = 0) :x(a), y(b), z(c) {};
	};
	double distance_3D(Point_3D a,Point_3D b)
	{
		double ans = 0;
		return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
	}
	struct Vector_3D
	{
		Point_3D point1, point2;
		Vector_3D(Point_3D &a, Point_3D &b) :point1(a), point2(b) {};
	};
	struct Vector_2D
	{
		double x;
		double y;
		Vector_2D(Point_2D Begin, Point_2D End)
		{
			x = End.x - Begin.x;
			y = End.y - Begin.y;
		}
		double dot_product(Vector_2D part)
		{
			return x * part.x + y * part.y;
		}
		double CrossProduct(Vector_2D part)
		{
			return x * part.y - y * part.x;
		}
		double length()
		{
			return sqrt(x*x + y * y);
		}
		double angle()
		{
			return atan2(y, x);
		}
		Vector_2D() = default;
		Vector_2D operator -(Vector_2D b)
		{
			Vector_2D part;
			part.x = x - b.x;
			part.y = y - b.y;
			return part;
		}
	};
	struct Line_2D
	{
		Point_2D vertex;
		Vector_2D vec;
		double ang;   //极角
		Line_2D(Point_2D a, Vector_2D b) :vertex(a), vec(b)
		{
			ang = atan2(vec.y, vec.x);
		}
		Line_2D(Point_2D a, Point_2D b)
		{
			vertex = a;
			vec = Vector_2D(b, a);
			ang = atan2(vec.y, vec.x);
		}
		Line_2D() {};
		friend bool operator <(Line_2D a, Line_2D L)
		{
			return a.ang < L.ang;
		}
		bool on_Left(Point_2D &a)//不统计线上的点 具体看题目需求
		{
			return vec.CrossProduct(Vector_2D(vertex, a)) >= 0;
		}
	};
	struct segment
	{
		Point_2D Begin;
		Point_2D End;
		segment() = default;
		segment(Point_2D &a, Point_2D &b) :Begin(a), End(b) {}
		double Point_2D_distance(Point_2D &a)
		{
			Vector_2D part1(Begin, End), part2(Begin, a);
			return fabs(part1.CrossProduct(part2)) / part1.length();
		}
		bool Point_2D_in(Point_2D a)
		{
			if (a.x <= End.x + EPS && a.y <= End.y + EPS && a.x + EPS >= Begin.x && a.y + EPS >= Begin.y && Point_2D_distance(a) < EPS)
				return true;
			return false;
		}
	};
	struct circle
	{
		Point_2D vertex;
		double r;
		circle(double a = 0, double b = 0, double c = 0) :vertex(a, b), r(c) {}
		bool in(Point_2D a)
		{
			if (vertex.distance(a) <= r + EPS)
				return true;
			return false;
		}
		Point_2D point(double a) //a为圆心角
		{
			return Point_2D(vertex.x + cos(a)*r, vertex.y + sin(a)*r);
		}
		bool operator ==(circle &a)
		{
			if (vertex == a.vertex && dcmp(r - a.r) == 0)
				return true;
			return false;
		}
		double area()
		{
			return acos(-1.0) * r*r;
		}
	};
	struct rectangle
	{
		Point_2D vertex1, vertex2;
		rectangle(double x1, double y1, double x2, double y2) :vertex1(x1, y1), vertex2(x2, y2) {}
		bool in(Point_2D a)
		{
			if (dcmp(vertex1.x - a.x) <= 0 && dcmp(vertex1.y - a.y) >= 0 && dcmp(vertex2.x - a.x) >= 0 && dcmp(vertex2.y - a.y) <= 0)
				return true;
			return false;
		}

	};
	struct triangle
	{
		Point_2D vertex1, vertex2, vertex3;
		triangle(double x1, double y1, double x2, double y2, double x3, double y3) :vertex1(x1, y1), vertex2(x2, y2), vertex3(x3, y3) {}
		bool in(Point_2D p)
		{
			segment part4(vertex1, vertex2), part5(vertex2, vertex3), part6(vertex3, vertex1);
			if (part4.Point_2D_in(p) || part5.Point_2D_in(p) || part6.Point_2D_in(p))
				return true;
			Vector_2D p_vertex1(p, vertex1), p_vertex2(p, vertex2), p_vertex3(p, vertex3);
			double part1 = p_vertex1.CrossProduct(p_vertex2);
			double part2 = p_vertex2.CrossProduct(p_vertex3);
			double part3 = p_vertex3.CrossProduct(p_vertex1);
			if ((part1 > 0 && part2 > 0 && part3 > 0) || (part1 < 0 && part2 < 0 && part3 < 0))
				return true;
			return false;
		}
		double area()
		{
			Vector_2D vec1(vertex1, vertex2), vec2(vertex1, vertex3);
			return vec1.CrossProduct(vec2) / 2;
		}
	};
	struct polygon
	{
		vector<Point_2D> vertex_collection;
		polygon(long x = 0) :vertex_collection(x) {};
		polygon(vector<Point_2D> &a):vertex_collection(a){}
		bool Point_2D_in(Point_2D &a)
		{
			int sum = 0;
			int n = vertex_collection.size();
			for (int i = 0; i < n; ++i)
			{
				segment part5(vertex_collection[i], vertex_collection[(i + 1) % n]);
				if (part5.Point_2D_in(a) == true)
					return true;
				Vector_2D part1(vertex_collection[i], vertex_collection[(i + 1) % n]), part2(vertex_collection[i], a);
				double k = part1.CrossProduct(part2);
				double part3 = vertex_collection[i].y - a.y;
				double part4 = vertex_collection[(i + 1) % n].y - a.y;
				if (k > 0 && part3 <= 0 && part4 > 0)
					sum++;
				if (k < 0 && part4 <= 0 && part3>0)
					sum--;
			}
			if (sum == 0)
				return false;
			else
				return true;
		}
		void insert(Point_2D &a)
		{
			vertex_collection.push_back(a);
		}
	};
	double triangle_area(Point_2D vertex1,Point_2D vertex2,Point_2D vertex3) //计算三角形的有向面积
	{
		Vector_2D vec1(vertex1, vertex2), vec2(vertex1, vertex3);
		return vec1.CrossProduct(vec2) / 2;
	}
	vector<Point_2D> andrew(vector<Point_2D> &Point_2D_collection)//andrew水平序凸包，求出来的凸包点数为n+1，原点两次；
	{
		vector<Point_2D> storage(Point_2D_collection.size() + 1);
		long total = 0;
		sort(Point_2D_collection.begin(), Point_2D_collection.end());
		for (int i = 0; i < Point_2D_collection.size(); ++i)
		{
			while (total > 1 && Vector_2D(storage[total - 2], storage[total - 1]).CrossProduct(Vector_2D(storage[total - 2], Point_2D_collection[i])) <= 0) total--;
			storage[total] = Point_2D_collection[i];
			total++;
		}
		int k = total;
		for (int i = Point_2D_collection.size() - 2; i >= 0; --i)
		{
			while (total > k && Vector_2D(storage[total - 2], storage[total - 1]).CrossProduct(Vector_2D(storage[total - 2], Point_2D_collection[i])) <= 0) total--;
			storage[total] = Point_2D_collection[i];
			total++;
		}
		vector<Point_2D> Hull(storage.begin(), storage.begin() + total - 1);
		return Hull;
	}
	double distance(Point_2D &a, Point_2D &b)
	{
		return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
	}
	double distance(Point_3D &a, Point_3D &b)
	{
		return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
	}
	int ccw(Point_2D p0, Point_2D p1, Point_2D p2)//逆时针方向 counter_clockwise 判断三点方位
	{
		Vector_2D a(p0, p1), b(p0, p2);
		if (dcmp(a.CrossProduct(b)) > 0)
			return 1;
		if (dcmp(a.CrossProduct(b)) < 0)
			return -1;
		if (dcmp(a.dot_product(b)) < 0)
			return 2;
		if (dcmp(a.length()-b.length())<0)
			return -2;
		return 0;

	}
	double polygon_cir(polygon &Polygon)//多边形周长
	{
		Polygon.vertex_collection.push_back(Polygon.vertex_collection[0]);
		double cir = 0;
		for (long i = 1; i < Polygon.vertex_collection.size(); ++i)
			cir += distance(Polygon.vertex_collection[i], Polygon.vertex_collection[i - 1]);
		Polygon.vertex_collection.pop_back();
		return cir;
	}
	double polygon_area(polygon &Polygon)//多边形有向面积
	{
		vector<Point_2D> P=Polygon.vertex_collection;
		if (P.size() < 3)
			return 0.0;
		double area = P[0].y*(P.back().x - P[1].x);
		P.push_back(P[0]);
		for (int i = 1; i < P.size() - 1; ++i)
			area += P[i].y*(P[i - 1].x - P[i + 1].x);
		return fabs(area*0.5);
	}
	double polygon_area(vector<Point_2D> &P)//多边形有向面积
	{
		if (P.size() < 3)
			return 0.0;
		double area = P[0].y*(P.back().x - P[1].x);
		P.push_back(P[0]);
		for (int i = 1; i < P.size()-1; ++i)
			area += P[i].y*(P[i - 1].x - P[i + 1].x);
		return fabs(area*0.5);
	}
	vector<Point_2D> get_line_circle_intersection(circle c1,Line_2D L) //给定直线与圆交点
	{
		vector<Point_2D> sol;
		double a = L.vec.x, b = L.vertex.x - c1.vertex.x, c = L.vec.y, d = L.vertex.y - c1.vertex.y,t1,t2;
		double e = a * a + c * c, f = 2 * (a*b + c * d), g = b * b + d * d - c1.r*c1.r;
		double delta = f * f - 4 * e*g;
		if (dcmp(delta) < 0)
			return sol;
		if (dcmp(delta) == 0)
		{
			t1 = -f / (2 * e);
			sol.push_back(c1.point(t1));
			return sol;
		}
		t1 = (-f - sqrt(delta)) / (2 * e);
		t2 = (-f + sqrt(delta)) / (2 * e);
		sol.push_back(c1.point(t1));
		sol.push_back(c1.point(t2));
		return sol;
	}
	vector<Point_2D> circle_circle_intersection(circle c1, circle c2)//计算两圆交点
	{
		vector<Point_2D> intersection;
		double d = distance(c1.vertex, c2.vertex);
		if (dcmp(d) == 0 || dcmp(c1.r + c2.r - d) < 0 || dcmp(fabs(c1.r - c2.r) - d) > 0)//判断特殊情况
		{
			return intersection;
		}
		double ang = Vector_2D(c1.vertex, c2.vertex).angle();//向量c1,c2的极角
		double d_ang = acos((c1.r*c1.r + d * d - c2.r*c2.r) / (2 * c1.r*d));//c1，c2到c1，p1的角；
		Point_2D p1 = c1.point(ang + d_ang), p2 = c1.point(ang - d_ang);
		intersection.push_back(p1);
		if (p1 == p2)
			return intersection;
		intersection.push_back(p2);
		return intersection;
	}
	double circle_common_area(circle c1, circle c2)
	{
		double area1 = 0, area3 = 0;
		double d = distance(c1.vertex, c2.vertex);
		if (dcmp(c1.r + c2.r - d) <= 0)//判断相离
			return 0.000;
		if (dcmp(fabs(c1.r - c2.r) - d) >= 0)//判断内含
			if (c1.r > c2.r)
				return c2.area();
			else
				return c1.area();
		double  p = (c1.r + c2.r + d) / 2;
		area1 = 2 * sqrt(p*(p - c1.r)*(p - c2.r)*(p - d));//海伦公式求三角形面积
		double c1_ang = acos((c1.r*c1.r + d * d - c2.r*c2.r) / (2 * c1.r*d));
		double c2_ang = acos((c2.r*c2.r + d * d - c1.r*c1.r) / (2 * c2.r*d));
		area3 = c1.r*c1.r*c1_ang + c2.r*c2.r*c2_ang - area1;
		return area3;
	}
	Point_2D line_intersection(Line_2D a, Line_2D b)//判断两直线交点
	{
		Vector_2D part(b.vertex, a.vertex);
		double t = b.vec.CrossProduct(part) / a.vec.CrossProduct(b.vec);
		Point_2D part2;
		part2.x = a.vertex.x + a.vec.x*t;
		part2.y = a.vertex.y + a.vec.y*t;
		return part2;
	}
	bool segment_intersection(segment ab, segment cd)
	{
		Point_2D p1, p2, p3, p4;
		p1 = ab.Begin,p2=ab.End,p3=cd.Begin,p4=cd.End;
		if (ccw(p1, p2, p3)*ccw(p1, p2, p4) <= 0 && ccw(p3, p4, p1)*ccw(p3, p4, p2) <= 0)
			return true;
		return false;
	}
	vector<Point_2D> half_plane_intersection(vector<Line_2D> line_collection)//半平面主过程
	{
		sort(line_collection.begin(), line_collection.end());
		int first = 0, last = 0;
		vector<Point_2D> point1(line_collection.size());
		vector<Line_2D> line(line_collection.size());
		line[0] = line_collection[0];
		for (int i = 1; i < line_collection.size(); ++i)
		{
			while (first < last && !line_collection[i].on_Left(point1[last - 1]))
				last--;
			while (first < last && !line_collection[i].on_Left(point1[first]))
				first++;
			line[++last] = line_collection[i];
			if (fabs(line[last].vec.CrossProduct(line[last - 1].vec)) < EPS)
			{
				last--;
				if (line[last].on_Left(line_collection[i].vertex))
					line[last] = line_collection[i];
			}
			if (first < last)
			{
				point1[last - 1] = line_intersection(line[last - 1], line[last]);
			}
		}
		while (first < last && !line[first].on_Left(point1[last - 1]))
			last--;
		vector<Point_2D> result;
		if (last - first <= 1)
			return result;
		point1[last] = line_intersection(line[last], line[first]);
		int m = 0;
		for (int i = first; i <= last; ++i)
			result.push_back(point1[i]);
		return result;
	}
	vector<Line_2D> polygon_to_line(polygon &pol)
	{
		vector<Line_2D> part1(pol.vertex_collection.size());
		part1[0] = Line_2D(pol.vertex_collection[pol.vertex_collection.size() - 1], pol.vertex_collection[0]);//头尾连线；
		for (int i = 1; i < pol.vertex_collection.size(); ++i)
			part1[i] = Line_2D(pol.vertex_collection[i - 1], pol.vertex_collection[i]);
		return part1;
	}
	Point_2D intersection(Point_2D a, Point_2D b, Point_2D c, Point_2D d)//确定有交点后线段求交
	{
		Point_2D p = a;
		double t = ((a.x - c.x)*(c.y - d.y) - (a.y - c.y)*(c.x - d.x)) / ((a.x - b.x)*(c.y - d.y) - (a.y - b.y)*(c.x - d.x));
		p.x += (b.x - a.x)*t;
		p.y += (b.y - a.y)*t;
		return p;
	}
	double CPIA(vector<Point_2D> a,vector<Point_2D> b)//凸多边形面积交
	{
		a.push_back(a[0]),b.push_back(b[0]);
		vector<Point_2D> p, tmp;
		int tn = 0,sflag, eflag=0;
		p = b;
		int nb = p.size() - 1;
		for (int i = 0; i < a.size()-1 && nb>2; ++i)
		{
			sflag = dcmp(Vector_2D(a[i],a[i+1]).CrossProduct(Vector_2D (a[i],p[0])));
			for (int j = 0; j < nb; ++j, sflag = eflag)
			{
				if (sflag >= 0)
					tmp.push_back(p[j]);
				eflag = dcmp(Vector_2D(a[i], a[i + 1]).CrossProduct(Vector_2D(a[i], p[j+1])));
				if ((sflag^eflag) == -2)
					tmp.push_back(intersection(a[i], a[i + 1], p[j], p[j + 1]));
			}
			p = tmp;
			nb = p.size();
			tmp.clear();
			p.push_back(p[0]);
		}
		a.pop_back(), b.pop_back();
		if (nb < 3)
			return 0.0;
		return polygon_area(p);
	}
	double SPIA(polygon &A,polygon &B)//凹，凸多边形的求面积并  显然的需要进行三角剖分
	{
		vector<Point_2D> t1(3), t2(3);
		vector<Point_2D> a = A.vertex_collection, b = B.vertex_collection;
		int na = a.size(), nb = b.size();
		double res = 0, num1, num2;
		a.push_back(a.front());
		b.push_back(b.front());
		t1[0] = a[0];
		t2[0] = b[0];
		for (int i = 2; i < na; ++i)
		{
			t1[1] = a[i - 1], t1[2] = a[i];
			num1 = dcmp(Vector_2D(t1[0], t1[1]).CrossProduct(Vector_2D(t1[0], t1[2])));
			if (num1 < 0)
				swap(t1[1], t1[2]);
			for (int j = 2; j < nb; ++j)
			{
				t2[1] = b[j - 1], t2[2] = b[j];
				num2 = dcmp(Vector_2D(t2[0], t2[1]).CrossProduct(Vector_2D(t2[0],t2[2])));
				if (num2 < 0)
					swap(t2[1], t2[2]);
				res += CPIA(t1, t2)*num1*num2;
			}
		}
		return polygon_area(a) + polygon_area(b) -res;
	}
	double circle_triangle_area(circle cir,Point_2D p1,Point_2D p2)//以圆心为原点的三角形与圆面积交
	{
		int sign = 1;
		if (dcmp(cir.r - cir.vertex.distance(p1)) >= 0 && dcmp(cir.r - cir.vertex.distance(p2)) >= 0)
		{
			return triangle_area(cir.vertex, p1, p2);
		}
		else if (dcmp(cir.r - cir.vertex.distance(p1)) < 0 && dcmp(cir.r - cir.vertex.distance(p2)) < 0)
		{
			if (dcmp(segment(p1, p2).Point_2D_distance(cir.vertex) - cir.r) >= 0)
			{
				return (Line_2D(cir.vertex, p1).ang - Line_2D(cir.vertex, p2).ang)*cir.r*cir.r;
			}
			else
			{

			}
		}
		else if (dcmp(cir.r - cir.vertex.distance(p1)) >= 0 && dcmp(cir.r - cir.vertex.distance(p2)) < 0)
		{
			if (dcmp(triangle_area(cir.vertex, p1, p2)) < 0)
				sign = -1;
		}
		else if (dcmp(cir.r - cir.vertex.distance(p1)) < 0 && dcmp(cir.r - cir.vertex.distance(p2)) >= 0)
		{

		}
		else
		{

		}
	} 
	double circle_polygon_area(circle cir,polygon pol) //求简单多边形与圆面积交,三角剖分，支持凹多边形
	{
		vector<Point_2D> part = pol.vertex_collection;
		double area=0;
		part.push_back(part[0]);
		for (int i = 0; i < part.size() - 1; ++i)
			area+=circle_triangle_area(cir, part[i], part[i + 1]);
		return area;
	}
	double minimal_circle_2D(vector<Point_3D> &A)//最小球覆盖
	{
		Point_3D center; int lm = 0;
		center.x = center.y = center.z = 0;
		double dmax = 100050, ans = 100000000000;
		while (dmax > 1e-7) {
			for (int i = 0; i < A.size(); ++i) {
				if (distance_3D(A[i],center) > distance_3D(center, A[lm]))lm = i;
			}
			double d = distance_3D(center, A[lm]);
			ans = min(ans, d);
			center.x += (A[lm].x - center.x) / d * dmax;//逐步向最远点移动 
			center.y += (A[lm].y - center.y) / d * dmax;
			center.z += (A[lm].z - center.z) / d * dmax;
			dmax *= 0.99;//0.97都不行至少0.98 
		}
		return ans;
	}
	double minmal_circle_2D()//最小圆覆盖
	{

	}
}

using namespace Computational_geometry;


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	return 0;
}

