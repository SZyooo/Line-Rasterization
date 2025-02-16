#include "LineRenderer.h"

LineRenderer::LineRenderer(const std::wstring& p_name)
	:m_name(p_name){}

const std::wstring& LineRenderer::name() const
{
	return m_name;
}
