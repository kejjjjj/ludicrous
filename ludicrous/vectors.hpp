#pragma once

#ifndef _vectrs
#define _vectrs

#include "pch.h"

enum LineDirection
{
	COLINEAR,
	ANTI_CLOCKWISE,
	CLOCKWISE
};

float VAngleDifference(const vf2d& s, const vf2d& e);
float VNormalize(vf2d& out);
#endif