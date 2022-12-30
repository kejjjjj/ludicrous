#include "pch.h"


bool rWorld::OnRenderBrush(const brush_t* brush)
{
	if (brush->polygon) {
		for (int i = 0; i < brush->faces; i++) {
			engine->DrawLine(Grid2Screen(brush->polygon[i].s), Grid2Screen(brush->polygon[i].e), olc::RED);
		}
	}
	else return 0;

	return 1;
}