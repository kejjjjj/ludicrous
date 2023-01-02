#pragma once

#ifndef _polyg
#define _polyg

#include "pch.h"

struct polygon_t
{
public:
	polygon_t(std::vector<vf2d> verts);

	polygon_t(){};

	void Initialize(std::vector<vf2d> verts);
	void RotateVerticies(const LineDirection direction);
	void DebugDraw();
	std::vector<vf2d> vertices;
	size_t vertCount = 0;
};

std::vector<vf2d>ConvexHullAlgorithm(std::vector<vf2d> iPoints);
std::vector<vi2d>ConvexHullAlgorithm(std::vector<vi2d> iPoints);

#endif