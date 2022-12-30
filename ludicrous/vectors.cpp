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