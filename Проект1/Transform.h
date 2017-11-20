#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <array>
#include <vector>

value struct point {
	float x, y;
};
value struct line {
	point start, end;
	System::String^ name;
};
#define M 3
typedef std::tr1::array<float, M> vec;
typedef std::tr1::array<vec, M> mat;
extern mat T;
extern std::vector<mat> matrices;

typedef System::Collections::Generic::List<point> polygon;


void times(mat a, mat b, mat &c);
void timesMatVec(mat a, vec b, vec &c);
void set(mat a, mat &b);
void point2vec(point a, vec &b);
void vec2point(vec a, point &b);
void makeHomogenVec(float x, float y, vec &c);
void unit(mat &a);
void move(float Tx, float Ty, mat &c);
void rotate(float phi, mat &c);
void scale(float S, mat &c);
//void mirror(int mirror, float h, float w, mat &c, mat t);
void scaleX(float S, mat &c);
void scaleY(float S, mat &c);
void frame(float Vx, float Vy, float Vcx, float Vcy,
	float Wx, float Wy, float Wcx, float Wcy,
	mat &c);
void scale_x2(float S, float P, mat &c);
void psevdosk(point a, point b, float &c);
void rotate2(float phi, mat &c);

void reflectH(mat &c);
void reflectV(mat &c);
