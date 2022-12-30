#pragma once

#ifndef __gworld
#define __gworld

#include "pch.h"

//everything gameplay related
//rWorld has everything rendering related

inline struct g_world_globals
{
	int32_t gridSize = 10;

}gGlobals;

vi2d Grid2Screen(const vf2d& p);
vf2d Screen2Grid(const vi2d& p);

class gWorld
{
public:
	
	gWorld(int32_t p2gScale = 10) : gridSize(p2gScale) { gGlobals.gridSize = p2gScale; };
	gWorld() = default;
	~gWorld() = default;

	//std::list<brush_t> brushes;
protected:


private:

	int32_t gridSize = 10; //how many screen pixels is one block

};

inline gWorld gworld(20);

#endif