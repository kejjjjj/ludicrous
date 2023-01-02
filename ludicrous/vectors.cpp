#include "pch.h"

float VAngleDifference(const vf2d& s, const vf2d& e)
{
	auto sub = s - e;
	return -atan2(-sub.y, -sub.x) * 180.f / PI;

}
float VNormalize(vf2d& out) {

	float length = out.mag(), ilength;

	if (length) {
		ilength = 1 / length;
		out /= ilength;
	}

	return length;
}
float VLineSlope(const vf2d& s, const vf2d& e)
{
	return (e.y - e.x) / (s.y - s.x);
}
vf2d VLinearCombination(const vf2d& a, const vf2d& b, const float scalarX, const float scalarY)
{
	return a * scalarX + b * scalarY;
}