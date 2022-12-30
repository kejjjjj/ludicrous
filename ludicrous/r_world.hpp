#pragma once

#ifndef __rworld
#define __rworld

#include "pch.h"


class rWorld
{
	//rWorld(olc::PixelGameEngine* eng) : engine(eng) {}
public:
	bool OnRenderBrush(const brush_t* brush);
};

inline rWorld rworld;

#endif