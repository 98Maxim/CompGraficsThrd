#pragma once
#include <vector>

polygon^ Pclip(polygon^ P, point Pmin, point Pmax);
void PFill(polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color Cgr, System::Drawing::Color Czal);