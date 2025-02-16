#include <graphics.h>

#include "BresenhamLineRenderer.h"
#include "DPoint.h"
#include "utils.h"

#include <iostream>

BresenhamLineRenderer::BresenhamLineRenderer()
	:LineRenderer(TEXT("Bresenham"))
{}

void BresenhamLineRenderer::draw(const DPoint& p1, const DPoint& p2)
{

	int x0{ 0 }, y0{ 0 }, x1{ 0 }, y1{ 0 };
	//保证(x0,y0)在左边，可以极大简化条件
	if (p1.x <= p2.x)
	{
		x0 = (int)p1.x;
		y0 = (int)p1.y;
		x1 = (int)p2.x;
		y1 = (int)p2.y;
	}
	else
	{
		x0 = (int)p2.x;
		y0 = (int)p2.y;
		x1 = (int)p1.x;
		y1 = (int)p1.y;
	}



	int dx = x1 - x0;
	int dy = y1 - y0;

	int sx = sign(dx);
	int sy = sign(dy);


	//处理斜率特殊情况

	if (!sx)
	{
		int y = y0;
		while (y != (y1 + sy))
		{
			putpixel(x0, y, WHITE);
			y = y + sy;
		}
		return;
	}

	if (!sy)
	{
		int x = x0;
		while (x != (x1 + sx))
		{
			putpixel(x, y0, WHITE);
			x = x + sx;
		}
		return;
	}

	int _x0, _y0, _x1, _y1;

	//增长-x主轴，增长-y主轴，降低-x主轴，降低-y主轴
	enum LINE_CASE { INC_X = 0, INC_Y, DEC_X, DEC_Y } line_case;

	//我们将线的起初坐标、终点坐标对称到斜率小于1的标准情形下
	if (dy > 0)
	{
		if (dx > dy)
		{
			_x0 = x0; _y0 = y0;
			_x1 = x1; _y1 = y1;
			line_case = INC_X;
		}
		else
		{
			_x0 = y0; _y0 = x0;
			_x1 = y1; _y1 = x1;
			line_case = INC_Y;
		}
	}
	else
	{
		if (dx > -dy)
		{
			_x0 = x0; _y0 = -y0;
			_x1 = x1; _y1 = -y1;
			line_case = DEC_X;
		}
		else
		{
			_x0 = -y0; _y0 = x0;
			_x1 = -y1; _y1 = x1;
			line_case = DEC_Y;
		}
	}

	int x = _x0;
	int y = _y0;
	int _dx = _x1 - _x0;
	int _dy = _y1 - _y0;
	int a = -_dx;

	putpixel(x0, y0, WHITE);
	while (x < (_x1 + sx)) //我们上面保证了sx = 1
	{
		int draw_x = x + 1, draw_y = y;

		a = a + _dy + _dy;


		if (a <= 0)
		{}
		else
		{
			draw_y = y + 1;
		}


		if (a >= _dx)
		{
			a = a - _dx - _dx;
			y = y + 1;
		}


		switch (line_case)
		{
			case INC_X:
				putpixel(draw_x, draw_y, WHITE);
				break;
			case INC_Y:
				std::cout << "[" << draw_y << "," << draw_x << "]\n";
				putpixel(draw_y, draw_x, WHITE);
				break;
			case DEC_X:
				putpixel(draw_x, -draw_y, WHITE);
				break;
			case DEC_Y:
				putpixel(draw_y, -draw_x, WHITE);
				break;
			default: break;
		}
		x = x + 1;
	}

	auto outline_c = getcolor(); 
	auto fill_c = getfillcolor();
	setcolor(RED);
	setfillcolor(RED);
	fillcircle(x0, y0, 3);
	fillcircle(x1, y1, 3);
	setcolor(outline_c);
	setfillcolor(fill_c);

}
