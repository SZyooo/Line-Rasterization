#include "DDALineRenderer.h"
#include "DPoint.h"
#include <graphics.h>

DDALineRenderer::DDALineRenderer()
	:LineRenderer(TEXT("DDA"))
{}

void DDALineRenderer::draw(const DPoint& p1, const DPoint& p2)
{
	int x1 = (int)p1.x;
	int y1 = (int)p1.y;
	int x2 = (int)p2.x;
	int y2 = (int)p2.y;
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (dx == 0)
	{
		int sign = (y2 - y1) > 0 ? 1 : -1;
		for (int y = y1; y != y2; y += sign)
		{
			putpixel(x1, y, WHITE);
		}
	}
	else if (dy == 0)
	{
		int sign = (x2 - x1) > 0 ? 1 : -1;
		for (int x = x1; x != x2; x += sign)
		{
			putpixel(x, y1, WHITE);
		}
	}
	else
	{
		
		if (abs(dx) > abs(dy))
		{
			double k = 1.0 * dy / dx;
			int sign = (x2 - x1 > 0) ? 1 : -1;
			double y = y1;
			for (int x = x1; x != (x2+sign); x += sign)
			{
				putpixel(x, (int)y, WHITE);
				if (sign > 0)
				{
					y += k;
				}
				else y -= k;
			}
		}
		else
		{
			double k = 1.0 * dx / dy;
			int sign = (y2 - y1 > 0) ? 1 : -1;
			double x = x1;
			for (int y = y1; y != (y2+sign); y += sign)
			{
				putpixel((int)x, y, WHITE);
				if (sign > 0)
				{
					x += k;
				}
				else x -= k;
			}
		}
	}
}
