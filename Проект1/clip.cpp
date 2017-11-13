#pragma once
#include <algorithm>
#include "Transform.h"
#include <cmath>
#include "Clip.h"
#include <math.h> 

using namespace std;


bool Clip(float &x1, float &x2, float &y1, float &y2, float xm, float ym, float xmax, float ymax)
{
	float tmin = 0, tmax = 1, i = 1;
	float x11 = 566, x21, y11, y21;
stap2:
	if (i > 4)
	{
		x11 = x1 + tmin*(x2 - x1);
		x21 = x1 + (x2 - x1)*tmax;
		y11 = y1 + (y2 - y1)*tmin;
		y21 = y1 + (y2 - y1)*tmax;
		x1 = x11; y1 = y11; x2 = x21; y2 = y21; return true;
	}
	else
	{
		float Qx, Qy, f, Fi, pp, Nix, Niy, Fix, Fiy, Qi, Qix, Qiy, Pi, px, py, ppx, ppy;
		if (i == 1) { Nix = 1; Niy = 0; Fix = xm; Fiy = ym; }
		if (i == 2) { Nix = 0; Niy = -1; Fix = xm; Fiy = ymax; }
		if (i == 3) { Nix = -1; Niy = 0; Fix = xmax; Fiy = ymax; }
		if (i == 4) { Nix = 0; Niy = 1; Fix = xmax; Fiy = ym; }
		px = x2 - x1; py = y2 - y1;
		ppx = x1; ppy = y1;
		Qx = ppx - Fix;
		Qy = ppy - Fiy;
		f = (Qx*Nix + Qy*Niy) / (sqrt(Qx*Qx + Qy*Qy) * sqrt(Nix*Nix + Niy * Niy));
		Qi = f*sqrt(Qx*Qx + Qy*Qy)*sqrt(Nix*Nix + Niy*Niy);
		f = (px*Nix + py*Niy) / (sqrt(px*px + py*py) * sqrt(Nix*Nix + Niy * Niy));
		Pi = f*sqrt(px*px + py*py)*sqrt(Nix*Nix + Niy * Niy);
		if (Pi == 0)
			if (Qi < 0) return false;
			else
			{
				++i; goto stap2;
			}
		if (Pi > 0)
		{
			if (tmin < (-Qi / Pi)) tmin = -Qi / Pi;
		}
		else
		{
			if (tmax >(-Qi / Pi)) tmax = -Qi / Pi;
		}
		if (tmin > tmax)
			return false;
		else
		{
			++i;  goto stap2;
		}
	}
}