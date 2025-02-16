#pragma once
#include "LineRenderer.h"
class MiddlePointLineRenderer :
    public LineRenderer
{
public:
    MiddlePointLineRenderer();
    virtual void draw(const DPoint& p1, const DPoint& p2);
    
};

