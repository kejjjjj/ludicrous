#pragma once

#ifndef _polyg
#define _polyg

#include "pch.h"

struct vertex_t
{
	float interiorAngles = 0;
	float exteriorAngles = 180;
	bool isConvex = false;
};

struct polygon_t
{
public:
	polygon_t(std::vector<vf2d> verts);

	polygon_t(){};

	void Initialize(std::vector<vf2d> verts);
	void RotateVerticies(const LineDirection direction);
	void DebugDraw();
	std::vector<vf2d> vertices;
	std::vector<vertex_t> vertex;
	size_t vertCount = 0;
};

std::vector<vf2d>ConvexHullAlgorithm(std::vector<vf2d> iPoints);
std::vector<vi2d>ConvexHullAlgorithm(std::vector<vi2d> iPoints);
std::vector<vf2d>::iterator BottomMostLeft(std::vector<vf2d>& points);

#endif