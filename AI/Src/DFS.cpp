#include "Precompiled.h"
#include "DFS.h""

bool AI::DSF::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY)
{
    bool found = false;
    graph.ResetSearchParams();
    mOpenList.clear();
    mClosedList.clear();

    //add the start node to the open list
    GridBasedGraph::Node* node = graph.GetNode(startX, startY);
    node->opened = true;
    mOpenList.push_back(node);

    // do the search
    while (!found && !mOpenList.empty())
    {
        // DFS LIFO
        node = mOpenList.back();
        mOpenList.pop_back();

        if (node->column == endX && node->row == endY)
        {
            found = true;
        }
        else
        {
            for (GridBasedGraph::Node* neighbor : node->neighbors)
            {
                if (neighbor == nullptr || neighbor->opened)
                {
                    continue;
                }
                mOpenList.push_back(neighbor);
                neighbor->opened = true;
                neighbor->parent = node;
            }
        }

        // add node to closed list
        mClosedList.push_back(node);
        node->closed = true;
    }

    return found;
}
