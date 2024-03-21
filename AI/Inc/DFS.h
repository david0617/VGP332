#pragma once

#include "GridBasedGragh.h"

namespace AI
{
    class DSF
    {
    public:
        bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY);

        const NodeList& GetClosedList() const { return mClosedList; }

    private:
        NodeList mOpenList;
        NodeList mClosedList;
    };
}