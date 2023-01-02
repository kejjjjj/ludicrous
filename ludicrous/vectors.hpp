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
float VLineSlope(const vf2d& s, const vf2d& e);
vf2d VLinearCombination(const vf2d& s, const vf2d& e, const float scalarX = .5f, const float scalarY = .5f);
#endif