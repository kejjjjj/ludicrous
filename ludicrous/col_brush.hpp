#pragma once

#ifndef col_brush
#define col_brush

#include "pch.h"

inline int offset = 0;

struct plane_t
{
	vf2d s;
	vf2d e;
	float normal = 0;

	void SetNormal() {
		vf2d sub = s - e;
		normal = atan2(sub.y, sub.x) * 180.f / PI;
		//normal /= 180;
		
	};

};
class brush_t
{
public:
	brush_t(const std::list<vf2d> points);

	~brush_t(){
		delete[] polygon;
	};
	bool Triangulate();
	void DebugDraw();
	plane_t* polygon;
	uint8_t faces = 0;

};


#endif