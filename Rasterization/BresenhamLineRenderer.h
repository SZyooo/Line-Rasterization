#pragma once
#include "LineRenderer.h"
class BresenhamLineRenderer :
    public LineRenderer
{
public:
    BresenhamLineRenderer();
    virtual void draw(const DPoint& p1, const DPoint& p2);
};

