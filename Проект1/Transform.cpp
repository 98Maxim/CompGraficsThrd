#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>

mat T;

void times(mat a, mat b, mat c) {
	for (int i = 0; i<M; i++) {
		for (int j = 0; j<M; j++) {
			float skalaar = 0;
			for (int k = 0; k<M; k++)
				skalaar += a[i][k] * b[k][j];
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat a, vec b, vec c) {
	for (int i = 0; i<M; i++) {
		float skalaar = 0;
		for (int j = 0; j<M; j++)
			skalaar += a[i][j] * b[j];
		c[i] = skalaar;
	}
}

void set(mat a, mat b) {
	for (int i = 0; i<M; i++)
		for (int j = 0; j<M; j++)
			b[i][j] = a[i][j];
}

void point2vec(point a, vec b) {
	b[0] = a.x; b[1] = a.y; b[2] = 1;
}

void vec2point(vec a, point &b) {
	b.x = ((float)a[0]) / a[2];
	b.y = ((float)a[1]) / a[2];
}

void makeHomogenVec(float x, float y, vec c) {
	c[0] = x; c[1] = y; c[2] = 1;
}

void unit(mat a) {
	for (int i = 0; i<M; i++) {
		for (int j = 0; j<M; j++) {
			if (i == j)a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, mat c) {
	unit(c);
	c[0][M - 1] = Tx;
	c[1][M - 1] = Ty;
}

void rotate(float phi, mat c) {
	unit(c);
	c[0][0] = cos(phi); c[0][1] = -sin(phi);
	c[1][0] = sin(phi); c[1][1] = cos(phi);
}

//void scale(float S, mat c) {
//	unit(c);
//	c[0][0] = S; c[1][1] = S;
//}
void scale(float Sx, float Sy, mat c) {
	unit(c);
	c[0][0] = Sx;
	c[1][1] = Sy;
}

void z_goriz(mat c) {
	unit(c);
	c[1][1] = -1;
}


void mirror(int mirror, float width, float height, mat c, mat t) {
	mat t1;
	unit(c);
	c[mirror][mirror] = -1;
	times(c, t, t1);
	set(t1, t);
	if (mirror == 0) {
		move(width / 2, 0, c);
	}
	else if (mirror == 1) {
		move(0, height / 2, c);
	}
	times(c, t, t1);
	set(t1, t);
}


void scale_x(float S, mat c) { 
	unit(c);
	c[0][0] = S; c[1][1] = 1;
}
void scale_y(float S, mat c) {
	unit(c);
	c[0][0] = 1; c[1][1] = S;
}
void frame (float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat c){
	
	//unit(c);
	//mat t, c1;

	//move(-Vcx, -Vcy, t);
	//times(t, c, c1);

	//scale(Wx / Vx, Wy / Vy, t);
	//times(t, c1, c);

	//z_goriz(t);
	//times(t, c, c1);

	//move(Wcx, Wcy, t);
	//times(t, c1, c);
	unit(c);
	mat m1, m2, m3, m4, m5, m6, m7, m8;

	move(-Vcx, -Vcy, m1);
	times(m1, c, m2);

	scale(Wx / Vx, Wy / Vy, m3);
	times(m3, m2, m4);

	unit(m5);
	m5[1][1] = -1;
	times(m5, m4, m6);

	move(Wcx, Wcy, m7);
	times(m7, m6, m8);

	set(m8, c);
}