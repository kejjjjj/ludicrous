#pragma once

#ifndef PCH_H
#define PCH_H

#define NOMINMAX

#define PI 3.14159f
#define RADIAN 6.283185f

#define DEG2RAD(x) (x * PI / 180)
#define RAD2DEG(x) (x * 180 / PI)



#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

#include "olcPixelGameEngine.h"

using olc::vi2d;
using olc::vf2d;
using olc::Pixel;

#include "vectors.hpp"

#include "window.hpp"

#include "g_main.hpp"
#include "entry.hpp"

#include "polygon.hpp"
#include "col_brush.hpp"
#include "tris.hpp"

#include "g_world.hpp"
#include "r_world.hpp"




#endif