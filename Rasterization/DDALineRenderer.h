#pragma once
#include "LineRenderer.h"
class DDALineRenderer :
    public LineRenderer
{
public:
    DDALineRenderer();
    virtual void draw(const DPoint& p1, const DPoint& p2) override;
};

