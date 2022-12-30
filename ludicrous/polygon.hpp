#pragma once

#ifndef _polyg
#define _polyg

#include "pch.h"

struct polygon_t
{
public:
	polygon_t(std::vector<vf2d> verts);

	void RotateVerticies(const LineDirection direction);
	void DebugDraw();
	std::vector<vf2d> vertices;
	size_t vertCount = 0;
};

#endif