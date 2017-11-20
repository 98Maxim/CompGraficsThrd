#pragma once
#include "Transform.h"
#include "PClip.h"
#include <limits> 

polygon^ PClip(polygon^ P, point Pmin, point Pmax) {
	int n = P->Count;
	float x1 = P[n - 1].x;
	float y1 = P[n - 1].y;
	float xMax = Pmax.x;
	float yMax = Pmax.y;
	float xMin = Pmin.x;
	float yMin = Pmin.y;
	int n1 = 0;
	polygon^ P1 = gcnew polygon(0);
	for (int k = 0; k <= n - 1; k++)
	{
		float o8o = std::numeric_limits<float>::max();   //бесконечность
		float x2 = P[k].x; //3
		float y2 = P[k].y; //3
		float dx = x2 - x1; //4
		float dy = y2 - y1; //4
		float xIn, xOut, yIn, yOut, txOut, tyOut, t1Out, t2Out, txIn, tyIn, t1In, t2In;
		if (dx > 0 || (abs(dx) < 0.0000001 && x1 > xMax)) { xIn = xMin; xOut = xMax; } //5
		else { xIn = xMax; xOut = xMin; }  //5
		if (dy > 0 || (abs(dy) < 0.0000001 && y1 > yMax)) { yIn = yMin; yOut = yMax; } //6
		else { yIn = yMax; yOut = yMin; }  //6
		if (abs(dx) > 0) txOut = (xOut - x1) / dx; //7
		else if (xMin <= x1 && x1 <= xMax) txOut = o8o; //7
		else txOut = -o8o;  //7
		if (abs(dy) > 0) tyOut = (yOut - y1) / dy; //8
		else if (yMin <= y1 && y1 <= yMax) tyOut = o8o;  //8
		else tyOut = -o8o;  //8
		if (txOut < tyOut) { t1Out = txOut; t2Out = tyOut; } //9
		else { t1Out = tyOut; t2Out = txOut; } //9
		if (t2Out > 0) //10
		{
			if (abs(dx) > 0) txIn = (xIn - x1) / dx; //10a
			else txIn = -o8o; //10a
			if (abs(dy) > 0) tyIn = (yIn - y1) / dy; //10b
			else tyIn = -o8o; //10b
			if (txIn < tyIn) t2In = tyIn; //10c
			else t2In = txIn; //10c
			if (t1Out < t2In) //10d
				if (0 < t1Out && t1Out <= 1) //10d i
				{
					n1 = n1 + 1; //10d i A
					if (txIn < tyIn) { point tmp; tmp.x = xOut; tmp.y = yIn; P1->Add(tmp); } //10d i B
					else { point tmp; tmp.x = xIn; tmp.y = yOut; P1->Add(tmp); } //10d i B
				}
				else;
			else if (t1Out > 0 && t2In <= 1) //10d
			{
				if (t2In >= 0) //10d i
				{
					n1 = n1 + 1; //10d i A
					if (txIn > tyIn) { point tmp; tmp.x = xIn; tmp.y = y1 + txIn * dy; P1->Add(tmp); } //10d i B
					else { point tmp; tmp.x = x1 + tyIn * dx; tmp.y = yIn; P1->Add(tmp); } //10d i B
				}
				if (t1Out <= 1) //10d ii
				{
					n1 = n1 + 1; //10d ii A
					if (txOut < tyOut) { point tmp; tmp.x = xOut; tmp.y = y1 + txOut * dy; P1->Add(tmp); } //10d ii B
					else { point tmp; tmp.x = x1 + tyOut * dx; tmp.y = yOut; P1->Add(tmp); } //10d ii B
				}

				else {
					n1 = n1 + 1; //10d A
					point tmp; tmp.x = x2; tmp.y = y2; P1->Add(tmp); //10d B
				}
			}
			if (0 < t2Out && t2Out <= 1) //10e
			{
				n1 = n1 + 1; //10e A
				point tmp; tmp.x = xOut; tmp.y = yOut; P1->Add(tmp); //10e B
			}
		}
		x1 = x2; //11
		y1 = y2; //11
	}
	return P1;
}