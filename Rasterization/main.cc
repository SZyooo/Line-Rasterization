#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <array>


#include "LineRenderer.h"
#include "DDALineRenderer.h"
#include "MiddlePointLineRenderer.h"
#include "BresenhamLineRenderer.h"
#include "DPoint.h"


enum class DRAW_STATE
{
	NONE = 0,
	PUT_FIRST,
};

constexpr int window_width = 1000;
constexpr int window_height = 800;

int main()
{
	initgraph(window_width, window_height);	// 创建绘图窗口，大小为 640x480 像素
	//setorigin(window_width / 2, window_height / 2);
	//setaspectratio(1, -1);
	//circle(200, 200, 100);	// 画圆，圆心(200, 200)，半径 100
	
	setcolor(RED);
	setfillcolor(BLUE);

	DDALineRenderer dda;
	MiddlePointLineRenderer mp;
	BresenhamLineRenderer bresen;
	std::array<std::reference_wrapper<LineRenderer>, 3> renderers{ std::ref(dda), std::ref(mp),  std::ref(bresen) };

	int cur_renderer = 0;
	
	ExMessage m;

	DRAW_STATE state = DRAW_STATE::NONE;

	DPoint v1;
	DPoint v2;


	renderers[cur_renderer].get().draw({100, 100}, {10, 1});


	auto draw_title = [](const std::wstring& title) {
		static int w;
		static int h;
		int l = -window_width / 2;
		int t = window_height / 2;
		clearrectangle(l, t , l + w, t - h);
		w = textwidth(title.c_str());
		h = textheight(title.c_str());
		
		RECT r = { 0,0,w,h };
		drawtext(title.c_str(), &r, DT_BOTTOM | DT_SINGLELINE);
	};

	draw_title(renderers[cur_renderer].get().name());

	while (true)
	{
		m = getmessage(EX_MOUSE | EX_KEY |	EX_WINDOW);
		switch (m.message)
		{
			case WM_LBUTTONDOWN:
				{
					if (state == DRAW_STATE::NONE)
					{
						state = DRAW_STATE::PUT_FIRST;
						
						v1.x = (double)m.x;
						v1.y = (double)m.y;
						fillcircle((int)m.x, (int)m.y, 2);
					}
					else if (state == DRAW_STATE::PUT_FIRST)
					{
						renderers[cur_renderer].get().draw(v1, { (double)m.x, (double)m.y});
						state = DRAW_STATE::NONE;
					}
					break;
				}
			case WM_RBUTTONDOWN:
				{
					if (state == DRAW_STATE::PUT_FIRST)
					{
						state = DRAW_STATE::NONE;
					}
					break;
				}
				//case WM_LBUTTONUP:
				//	{
				//		state = DRAW_STATE::NONE;
				//		break;
				//	}
			case WM_MOUSEMOVE:
				{
					//if (state == DRAW_STATE::PUT_FIRST)
					//{
					//	renderer.draw(v1, { (double)m.x, (double)m.y });
					//}
					break;
				}
			case WM_KEYDOWN:
				{
					if (m.vkcode == VK_SPACE)
					{
						clearcliprgn();
						draw_title(renderers[cur_renderer].get().name());

					}
					if (m.vkcode == VK_TAB)
					{
						cur_renderer = (cur_renderer + 1) % renderers.size();
						draw_title(renderers[cur_renderer].get().name());
						state = DRAW_STATE::NONE;
					}
					break;
				}
			case WM_QUIT:
				{
					closegraph();
					return 0;
				}

		}
	}
	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
	return 0;
}
