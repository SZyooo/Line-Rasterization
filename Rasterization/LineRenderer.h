#pragma once
#include <string>
struct DPoint;

class LineRenderer
{
private:
	std::wstring m_name;
public:
	LineRenderer(const std::wstring& p_name);
	virtual void draw(const DPoint& p1, const DPoint& p2) = 0;
	const std::wstring& name() const;
};

