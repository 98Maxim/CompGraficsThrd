#pragma once
#include "stdafx.h"
#include "Transform.h"
#include "PClip.h"
#include <math.h>
#include <algorithm>

polygon^ Pclip(polygon^ P, point Pmin, point Pmax)
{
	int i = 1;
	int n1 = P->Count;
	polygon^ P1 = P;
	std::vector< std::pair<float, float> > N(5);
	N[1].first = 1;	N[1].second = 0;
	N[2].first = 0; N[2].second = -1;
	N[3].first = -1; N[3].second = 0;
	N[4].first = 0;	N[4].second = 1;

	std::vector< std::pair<float, float> > F(5);
	F[1].first = Pmin.x; F[1].second = Pmin.y;
	F[2].first = Pmin.x; F[2].second = Pmax.y;
	F[3].first = Pmax.x; F[3].second = Pmax.y;
	F[4].first = Pmax.x; F[4].second = Pmin.y;

	std::vector< float > Q(2);

	while (i <= 4)
	{
		int k = 1;
		Q[0] = (P1[n1 - 1].x - F[i].first) * N[i].first + (P1[n1 - 1].y - F[i].second) * N[i].second;
		point p0;
		p0.x = P1[n1 - 1].x;
		p0.y = P1[n1 - 1].y;
		int n2 = 0;
		polygon^ P2 = gcnew polygon(0);
		while (k <= n1)
		{
			Q[1] = (P1[k - 1].x - F[i].first) * N[i].first + (P1[k - 1].y - F[i].second) * N[i].second;
			if (Q[0] * Q[1] < 0)
			{
				float t;
				t = Q[0] / (Q[0] - Q[1]);
				n2++;
				point buf;
				buf.x = p0.x - (p0.x - P1[k - 1].x) * t;
				buf.y = p0.y - (p0.y - P1[k - 1].y) * t;
				P2->Add(buf);
			}
			if (Q[1] >= 0)
			{
				n2++;
				point buf;
				buf.x = P1[k - 1].x;
				buf.y = P1[k - 1].y;
				P2->Add(buf);
			}
			Q[0] = Q[1];
			p0.x = P1[k - 1].x;
			p0.y = P1[k - 1].y;
			k++;
		}
		P1 = P2;
		n1 = n2;
		if (n1 == 0)
			return P1;
		else
			i++;
	}

	return P1;
}