#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>

mat T;
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