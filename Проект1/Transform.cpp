#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>

//mat T;
mat3D T;
std::vector<mat> matrices(0);

void times(mat a, mat b, mat &c) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			float skalaar = 0;
			for (int k = 0; k < M; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat a, vec b, vec &c) {
	for (int i = 0; i < M; i++) {
		float skalaar = 0;
		for (int j = 0; j < M; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}


void set(mat a, mat &b) {
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			b[i][j] = a[i][j];
}

void point2vec(point a, vec &b) {
	b[0] = a.x; b[1] = a.y; b[2] = 1;
}

void vec2point(vec a, point &b) {
	b.x = ((float)a[0]) / a[2];
	b.y = ((float)a[1]) / a[2];
}

void makeHomogenVec(float x, float y, vec &c) {
	c[0] = x;
	c[1] = y;
	c[2] = 1;
}

void unit(mat &a) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i == j) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, mat &c) {
	unit(c);
	c[0][M - 1] = Tx;
	c[1][M - 1] = Ty;
}

void rotate(float phi, mat &c) {
	unit(c);
	c[0][0] = cos(phi); c[0][1] = -sin(phi);
	c[1][0] = sin(phi); c[1][1] = cos(phi);
}

void scale(float S, mat &c) {
	unit(c);
	c[0][0] = S;
	c[1][1] = S;
}

void mirror(int mirror, float w, float h, mat &c, mat t) {
	mat t1;
	unit(c);
	c[mirror][mirror] = -1;
	times(c, t, t1);
	set(t1, t);
	if (mirror == 0) {
		move(w / 2, 0, c);
	}
	else if (mirror == 1) {
		move(0, h / 2, c);
	}
	times(c, t, t1);
	set(t1, t);
}


void scaleX(float S, mat &c) {
	unit(c);
	c[0][0] = S; c[1][1] = 1;
}

void scaleY(float S, mat &c) {
	unit(c);
	c[0][0] = 1; c[1][1] = S;
}
void frame(float Vx, float Vy, float Vcx, float Vcy,
	float Wx, float Wy, float Wcx, float Wcy,
	mat &c)
{
	mat t1, R;
	unit(c);
	unit(R);
	move(-Vcx, -Vcy, c);
	scale_x2(Wx / Vx, Wy / Vy, R);
	times(R, c, t1);
	set(t1, c);
	unit(R);
	R[1][1] = -1;
	times(R, c, t1);
	set(t1, c);
	move(Wcx, Wcy, R);
	times(R, c, t1);
	set(t1, c);
}
void scale_x2(float S, float P, mat &c)
{
	unit(c);
	c[0][0] = S; c[1][1] = P;
}
void psevdosk(point a, point b, float &c)
{
	c = a.x*b.y - a.y*b.x;
}

void rotate2(float phi, mat &c) {
	unit(c);
	c[0][0] = cos(phi); c[0][1] = -sin(phi);
	c[1][0] = sin(phi); c[1][1] = cos(phi);
}

void reflectH(mat &c) {
	unit(c);
	c[1][1] = -1;
}

void reflectV(mat &c) {
	unit(c);
	c[0][0] = -1;
}

// Все, что потребуется для 3D

void set(point3D a, point &b)
{
	b.x = a.x;
	b.y = a.y;
}

void point2vec(point3D a, vec3D &b)
{
	b[0] = a.x;
	b[1] = a.y;
	b[2] = a.z;
	b[3] = 1;
}

void vec2point(vec3D a, point3D &b)
{
	b.x = ((float)a[0]) / a[3];
	b.y = ((float)a[1]) / a[3];
	b.z = ((float)a[2]) / a[3];
}

void vec2skewSymmetricMat(vec3D a, mat3D &b)
{
	unit(b);
	b[2][1] = a[0]; b[1][2] = -a[0];
	b[0][2] = a[1]; b[2][0] = -a[1];
	b[1][0] = a[2]; b[0][1] = -a[2];
	b[0][0] = 0; b[1][1] = 0; b[2][2] = 0;
}

void normalize(vec3D &a)
{
	float len = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	if (len) {
		a[0] /= len;
		a[1] /= len;
		a[2] /= len;
	}
}

void vecSubtr(vec3D a, vec3D b, vec3D &c)
{
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];
	c[3] = 1;
}

void crossProduct(vec3D a, vec3D b, vec3D &c)
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
	c[3] = 1;
}

// Матрица 3D

void unit(mat3D &a)
{
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < K; j++)
		{
			if (i == j) a[i][j] = 1;
			else       a[i][j] = 0;
		}
	}
}

void set(mat3D a, mat3D &b)
{
	for (int i = 0; i < K; i++)
		for (int j = 0; j < K; j++)
			b[i][j] = a[i][j];
}

void times(mat3D a, mat3D b, mat3D &c)
{
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < K; j++)
		{
			float scalar = 0;
			for (int k = 0; k < K; k++)
				scalar += a[i][k] * b[k][j];
			c[i][j] = scalar;
		}
	}
}

void timesMatVec(mat3D a, vec3D b, vec3D &c)
{
	for (int i = 0; i < K; i++)
	{
		float scalar = 0;
		for (int j = 0; j < K; j++)
			scalar += a[i][j] * b[j];
		c[i] = scalar;
	}
}

void timesMatFloat(mat3D a, float b, mat3D &c)
{
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < K; j++)
		{
			c[i][j] = a[i][j] * b;
		}
	}
}

void move(float Tx, float Ty, float Tz, mat3D &c)
{
	unit(c);
	c[0][K - 1] = Tx;
	c[1][K - 1] = Ty;
	c[2][K - 1] = Tz;
}

void add(mat3D a, mat3D b, mat3D &c)
{
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < K; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

void rotate(point3D n, float phi, mat3D &c)
{
	unit(c);
	vec3D u;
	point2vec(n, u);
	normalize(u);

	mat3D c1, c2;
	vec2skewSymmetricMat(u, c1);
	times(c1, c1, c2);

	timesMatFloat(c1, sin(phi), c1);
	timesMatFloat(c2, 1.0 - cos(phi), c2);
	c1[K - 1][K - 1] = 1; c2[K - 1][K - 1] = 1;

	add(c, c1, c);
	add(c, c2, c);
	c[K - 1][K - 1] = 1;
}

void LookAt(point3D eye, point3D center, point3D up, mat3D &c)
{
	mat3D R1;
	move(-eye.x, -eye.y, -eye.z, R1);

	vec3D s, p, u;
	point2vec(eye, s);
	point2vec(center, p);
	point2vec(up, u);

	vec3D e1, e2, e3;
	vecSubtr(s, p, e3);
	normalize(e3);

	crossProduct(u, e3, e1);
	normalize(e1);

	crossProduct(e3, e1, e2);

	mat3D R2;
	unit(R2);
	R2[0][0] = e1[0]; R2[0][1] = e1[1]; R2[0][2] = e1[2];
	R2[1][0] = e2[0]; R2[1][1] = e2[1]; R2[1][2] = e2[2];
	R2[2][0] = e3[0]; R2[2][1] = e3[1]; R2[2][2] = e3[2];

	times(R2, R1, c);
}

void Perspective(float fovy, float aspect, float near, float far, mat3D &c)
{
	unit(c);
	c[0][0] = 1.0 / (aspect * tan(fovy / 2));
	c[1][1] = 1.0 / tan(fovy / 2);
	c[2][2] = (far + near) / (far - near);
	c[2][3] = 2 * far * near / (far - near);
	c[3][2] = -1;
	c[3][3] = 0;
}

void Ortho(float Vx, float Vy, float near, float far, mat3D &c)
{
	unit(c);

	c[0][0] = 2.0 / Vx;
	c[1][1] = 2.0 / Vy;
	c[2][2] = 2.0 / (far - near);
	c[2][3] = (far + near) / (far - near);
}