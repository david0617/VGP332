#include "TileMap.h"

using namespace AI;

namespace
{
	inline int ToIndex(int x, int y, int columns)
	{
		return x + (y * columns);
	}
}

void TileMap::LoadTiles(const char* fileName)
{
	if (!std::filesystem::exists(fileName))
	{
		return;
	}

	std::fstream file(fileName);

	int count = 0;
	int isWalkable = 0;
	std::string buffer;

	file >> buffer;
	file >> count;

	mTiles.clear();
	mTiles.reserve(count);
	for (int i = 0; i < count; ++i)
	{
		file >> buffer;
		file >> isWalkable;

		Tile& tile = mTiles.emplace_back();
		tile.textureId = X::LoadTexture(buffer.c_str());
		tile.isWalkable = isWalkable == 0;
	}
	file.close();

	mTileWidth = X::GetSpriteWidth(mTiles[0].textureId);
	mTileHeight = X::GetSpriteHeight(mTiles[0].textureId);
}

void TileMap::LoadMap(const char* fileName)
{
	if (!std::filesystem::exists(fileName))
	{
		return;
	}

	std::fstream file(fileName);
	int columns = 0;
	int rows = 0;
	std::string buffer;
	char tileType;

	file >> buffer;
	file >> columns;
	file >> buffer;
	file >> rows;

	mColumns = columns;
	mRows = rows;

	mMap.resize(columns * rows);
	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			file >> tileType;
			int mapIndex = ToIndex(x, y, columns);
			mMap[mapIndex] = tileType - '0';
		}
	}
	file.close();

	auto GetNeighbor = [&](int x, int y) -> AI::GridBasedGraph::Node*
	{
		if (IsBlocked(x, y))
		{
			return nullptr;
		}
		return mGraph.GetNode(x, y);
	};

	mGraph.Initialize(columns, rows);
	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			if (IsBlocked(x, y))
			{
				continue;
			}
			GridBasedGraph::Node* node = mGraph.GetNode(x, y);
			node->neighbors[GridBasedGraph::North] = GetNeighbor(x, y- 1);
			node->neighbors[GridBasedGraph::South] = GetNeighbor(x, y + 1);
			node->neighbors[GridBasedGraph::East] = GetNeighbor(x + 1, y);
			node->neighbors[GridBasedGraph::West] = GetNeighbor(x - 1, y);
			node->neighbors[GridBasedGraph::NorthEast] = GetNeighbor(x + 1, y - 1);
			node->neighbors[GridBasedGraph::NorthWest] = GetNeighbor(x - 1, y - 1);
			node->neighbors[GridBasedGraph::SouthEast] = GetNeighbor(x + 1, y + 1);
			node->neighbors[GridBasedGraph::SouthWest] = GetNeighbor(x - 1, y + 1);
		}
	}
}

void TileMap::Render() const
{
	// draw the tiles
	X::Math::Vector2 position;
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			int mapIndex = ToIndex(x, y, mColumns);
			int tileType = mMap[mapIndex];
			X::DrawSprite(mTiles[tileType].textureId, position, X::Pivot::TopLeft);
			position.x += mTileWidth;


		}
		position.x = 0.0f;
		position.y += mTileHeight;
	}
	// draw the graph node connections
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const GridBasedGraph::Node* node = mGraph.GetNode(x, y);
			for (const GridBasedGraph::Node* neighdor : node->neighbors)
			{
				if (neighdor != nullptr)
				{
					const X::Math::Vector2 a = GetPixelPosition(node->column, node->row);
					const X::Math::Vector2 b = GetPixelPosition(neighdor->column, neighdor->row);
					X::DrawScreenLine(a, b, X::Colors::Blue);
				}
			}
		}
	}
	// draw the search branches
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const GridBasedGraph::Node* node = mGraph.GetNode(x, y);
			if (node->parent != nullptr)
			{
				const X::Math::Vector2 a = GetPixelPosition(node->column, node->row);
				const X::Math::Vector2 b = GetPixelPosition(node->parent->column, node->parent->row);
				X::DrawScreenLine(a, b, X::Colors::White);
			}
		}
	}
}

bool TileMap::IsBlocked(int x, int y) const
{
	if (x >= 0 && x < mColumns &&
		y >= 0 && y < mRows)
	{
		const int index = ToIndex(x, y, mColumns);
		const int tileId = mMap[index];
		if (mTiles[tileId].isWalkable)
		{
			return false;
		}
	}
	return true;
}

X::Math::Vector2 TileMap::GetPixelPosition(int x, int y) const
{
	return {
		(x + 0.5f) * mTileWidth,
		(y + 0.5f) * mTileHeight
	};
}

Path TileMap::FindPathBFS(int startX, int startY, int endX, int endY)
{
	Path path;
	BSF bsf;
	if (bsf.Run(mGraph, startX, startY, endX, endY))
	{
		const NodeList& closrdList = bsf.GetClosedList();
		GridBasedGraph::Node* node = closrdList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}
	return path;
}
Path TileMap::FindPathDFS(int startX, int startY, int endX, int endY)
{
	Path path;
	DSF dsf;
	if (dsf.Run(mGraph, startX, startY, endX, endY))
	{
		const NodeList& closrdList = dsf.GetClosedList();
		GridBasedGraph::Node* node = closrdList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}
	return path;
}

Path TileMap::FindPathDijkstra(int startX, int startY, int endX, int endY)
{
	auto getCost = [](const GridBasedGraph::Node* node, const GridBasedGraph::Node* neighbor)->float
	{
		if (node->column != neighbor->column && node->row != neighbor->row)
		{
			return 10.0f;
		}
		return 1.0f;
	};
	Path path;
	Dijkstra dijkstra;
	if (dijkstra.Run(mGraph, startX, startY, endX, endY, getCost))
	{
		const NodeList& closrdList = dijkstra.GetClosedList();
		GridBasedGraph::Node* node = closrdList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}
	return path;
}

Path TileMap::FindPathAStar(int startX, int startY, int endX, int endY)
{
	auto getCost = [](const GridBasedGraph::Node* node, const GridBasedGraph::Node* neighbor)->float
	{
		if (node->column != neighbor->column && node->row != neighbor->row)
		{
			return 1.0f;
		}
		return 1.0f;
	};
	auto manhattanHeuristic = [](const GridBasedGraph::Node* neighbor, const GridBasedGraph::Node* endNode)->float
	{
		float D = 1.0f;
		float dx = abs(neighbor->column - endNode->column);
		float dy = abs(neighbor->row - endNode->row);
		return D * (dx + dy);
	};
	auto euclideanHeuristic = [](const GridBasedGraph::Node* neighbor, const GridBasedGraph::Node* endNode)->float
	{
		float D = 1.0f;
		float dx = abs(neighbor->column - endNode->column);
		float dy = abs(neighbor->row - endNode->row);
		return D * sqrt(dx * dx + dy * dy);
	};
	auto diagonalHeuristic = [](const GridBasedGraph::Node* neighbor, const GridBasedGraph::Node* endNode)->float
	{
		float D = 1.0f;
		float D2 = 1.0f;
		float dx = abs(neighbor->column - endNode->column);
		float dy = abs(neighbor->row - endNode->row);
		return D * (dx + dy) + (D2 - 2 * D) * std::min(dx, dy);
	};
	Path path;
	AStar aStar;
	if (aStar.Run(mGraph, startX, startY, endX, endY, getCost, manhattanHeuristic))
	{
		const NodeList& closrdList = aStar.GetClosedList();
		GridBasedGraph::Node* node = closrdList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}
	return path;
}
// 2D map - 5 columns x 4 rows
// [0][0][0][0][0]
// [0][0][0][0][0]
// [0][0][0][X][0]   X is at (3, 2)
// [0][0][0][0][0]

// Stored as 1D - 5x4 = 20 slots
// [0][0][0][0][0] [0][0][0][0][0] [0][0][0][X][0] [0][0][0][0][0]
//
// index = column + (row * columnCount)
//       = 3 + (2 * 5)
//       = 13