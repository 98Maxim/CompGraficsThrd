#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <array>
#include <vector>

value struct point {
	float x, y;
};

value struct point3D
{
	double x, y, z;
};

value struct line {
	point start, end;
	System::String^ name;
};
#define M 3
typedef std::tr1::array<float, M> vec;
typedef std::tr1::array<vec, M> mat;

#define K 4 
typedef std::tr1::array<float, K> vec3D;
typedef std::tr1::array<vec3D, K> mat3D;

//extern mat T; old version '7'
extern mat3D T;
extern std::vector<mat> matrices;

typedef System::Collections::Generic::List<point> polygon;
typedef System::Collections::Generic::List<point3D> polygon3D;


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

// Все, что потребуется для 3D
void set(point3D a, point &b);
void point2vec(point3D a, vec3D &b);
void vec2point(vec3D a, point3D &b);
void vec2skewSymmetricMat(vec3D a, mat3D &b);
void normalize(vec3D &a);
void vecSubtr(vec3D a, vec3D b, vec3D &c);
void crossProduct(vec3D a, vec3D b, vec3D &c);

// Матрица 3D
void unit(mat3D &a);
void set(mat3D a, mat3D &b);
void times(mat3D a, mat3D b, mat3D &c);
void timesMatVec(mat3D a, vec3D b, vec3D &c);
void timesMatFloat(mat3D a, float b, mat3D &c);
void move(float Tx, float Ty, float Tz, mat3D &c);
void rotate(point3D n, float phi, mat3D &c);
void add(mat3D a, mat3D b, mat3D &c);
void LookAt(point3D eye, point3D center, point3D up, mat3D &c);
void Perspective(float fovy, float aspect, float near, float far, mat3D &c);
void Ortho(float Vx, float Vy, float near, float far, mat3D &c);
