#pragma once
#include "stdafx.h"

#include <math.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <stack>
#include "Transform.h"
#include "PClip.h"
#include "MyForm.h"

using namespace System::Drawing;

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
void PFill(polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color Cgr, System::Drawing::Color Czal) {
	polygon^ S = gcnew polygon(0);

	point ip;

	float ymin = P[0].y;
	int yminin = 0;

	for (int i = 1; i < P->Count; i++) {
		if (P[i].y < ymin) {
			ymin = P[i].y;
			yminin = i;
		}
	}

	point n = P[yminin];
	point n1 = P[(yminin + 1) % P->Count];
	point n2 = P[(yminin + 2) % P->Count];

	point s1;
	s1.x = (int)(n.x + n1.x) / 2;
	s1.y = (int)(n.y + n1.y) / 2;
	point s2;
	s2.x = (int)(n1.x + n2.x) / 2;
	s2.y = (int)(n1.y + n2.y) / 2;

	ip.x = (int)(s1.x + s2.x) / 2;
	ip.y = (int)(s1.y + s2.y) / 2;

	S->Add(ip); //точка вн

	while (S->Count > 0) {
		point j = S[S->Count - 1];
		S->RemoveAt(S->Count - 1);

		System::Drawing::Color Cxy = image->GetPixel(j.x, j.y);

		if (Cxy.ToArgb() != Czal.ToArgb()) {
			float xmin = j.x;
			float xmax = j.x;

			System::Drawing::Color Cmin = image->GetPixel(xmin - 1, j.y);
			while (Cmin.ToArgb() != Cgr.ToArgb()) {
				xmin--;
				Cmin = image->GetPixel(xmin, j.y); //падает?
			}

			System::Drawing::Color Cmax = image->GetPixel(xmax + 1, j.y);
			while (Cmax.ToArgb() != Cgr.ToArgb()) {
				xmax++;
				Cmax = image->GetPixel(xmax, j.y);
			}

			for (float x = xmin + 1; x < xmax + 1; x++) {
				image->SetPixel(x, j.y, Czal);

				System::Drawing::Color Cup = image->GetPixel(x, j.y + 1);
				if (Cup.ToArgb() != Cgr.ToArgb() && Cup.ToArgb() != Czal.ToArgb()) {
					point pup;
					pup.x = x;
					pup.y = j.y + 1;

					S->Add(pup);
				}

				System::Drawing::Color Cdn = image->GetPixel(x, j.y - 1);
				if (Cdn.ToArgb() != Cgr.ToArgb() && Cdn.ToArgb() != Czal.ToArgb()) {
					point pdn;
					pdn.x = x;
					pdn.y = j.y - 1;

					S->Add(pdn);
				}
			}
		}
	}
}