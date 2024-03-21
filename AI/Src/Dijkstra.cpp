#include "Precompiled.h"
#include "Dijkstra.h"

using namespace AI;

bool Dijkstra::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost)
{
    graph.ResetSearchParams();
    mOpenList.clear();
    mClosedList.clear();

    GridBasedGraph::Node* endNode = nullptr;
    //add the start node to the open list
    GridBasedGraph::Node* node = graph.GetNode(startX, startY);
    node->opened = true;
    mOpenList.push_back(node);

    auto sortCost = [](const GridBasedGraph::Node* a, const GridBasedGraph::Node* b)
    {
        return a->cost < b->cost;
    };

    // do the search
    while (!mOpenList.empty())
    {
        // Dijkstra
        node = mOpenList.front();
        mOpenList.pop_front();

        if (node->column == endX && node->row == endY)
        {
            endNode = node;
        }
        else
        {
            for (GridBasedGraph::Node* neighbor : node->neighbors)
            {
                if (neighbor == nullptr || neighbor->closed)
                {
                    continue;
                }
                float cost = node->cost + getCost(node, neighbor);
                if (!neighbor->opened)
                {
                    mOpenList.push_back(neighbor);
                    neighbor->opened = true;
                    neighbor->parent = node;
                    neighbor->cost = cost;
                }
                else if (cost < neighbor->cost)
                {
                    neighbor->parent = node;
                    neighbor->cost = cost;
                }
            }
        }

        mOpenList.sort(sortCost);

        // add node to closed list
        mClosedList.push_back(node);
        node->closed = true;
    }
    mClosedList.push_back(endNode);

    return endNode != nullptr;
}
