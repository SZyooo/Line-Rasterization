#include <graphics.h>

#include "MiddlePointLineRenderer.h"
#include "DPoint.h"
#include "utils.h"

MiddlePointLineRenderer::MiddlePointLineRenderer()
	:LineRenderer(TEXT("MiddlePoint"))
{}

void MiddlePointLineRenderer::draw(const DPoint& p1, const DPoint& p2)
{
	int x0 = (int)p1.x;
	int y0 = (int)p1.y;
	int x1 = (int)p2.x;
	int y1 = (int)p2.y;

	int dx = x1 - x0;
	int dy = y1 - y0;

	int sx = sign(dx);
	int sy = sign(dy);

	if (dx == 0)//处理斜率特殊情况
	{
		int y = y0;
		while (y != y0)
		{
			putpixel(x0, y, WHITE);
			y = y + sy;
		}
	}
	if (dy == 0)
	{
		int x = x0;
		while (x != x1)
		{
			putpixel(x, y0, WHITE);
			x = x + sx;
		}
	}
	int A = y1 - y0;
	int AA = A + A;
	int B = x0 - x1;
	int BB = B + B;

	int x = x0, y = y0;
	if (abs(dx) >= abs(dy))
	{
		int d = sx * AA + sy * B;//2 * A + B
		putpixel(x, y, WHITE);
		while (x != x1)
		{
			if (d * B * sy < 0)
			{
				putpixel(x + sx, y + sy, WHITE);
				y = y + sy;
				d = d + sx * AA + sy * BB; // d_1 = d_0 + 2 * (A + B)
			}
			else
			{
				putpixel(x + sx, y, WHITE);
				d = d + sx * AA;// d_1 = d_0 + 2 * A
			}
			x = x + sx;
		}
	}
	else
	{
		int d = sx * A + sy * BB;// A + 2 * B
		putpixel(x, y, WHITE);
		while (y != y1)
		{
			if (d * A * sx < 0)
			{
				putpixel(x + sx, y + sy, WHITE);
				x = x + sx;
				d = d + sx * AA + sy * BB;//d_1 = d_0 + 2 * B
			}
			else
			{
				putpixel(x, y + sy, WHITE);
				d = d + sy * BB;
			}
			y = y + sy;
		}
	}
}
