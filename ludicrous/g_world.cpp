#include "pch.h"

vi2d Grid2Screen(const vf2d& p)
{
	return p * gGlobals.gridSize;
}
vf2d Screen2Grid(const vi2d& p)
{
	return vf2d{ (float)p.x, (float)p.y } / gGlobals.gridSize;
}