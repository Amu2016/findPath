#include "NavmeshGraph.h"
#include <map>
#include <queue>
#include "FileNavmeshParser.h"

recast_navigation::NavmeshGraph::NavmeshGraph() :
	_size(0)
{
}

recast_navigation::NavmeshGraph::~NavmeshGraph()
{
	traversal([](GraphNode* node) {
		delete node;
		node = nullptr;
	});
}

bool recast_navigation::NavmeshGraph::loadFromFile(const string & filename, float scale_factor)
{
	FileNavmeshParser parser(*this);

	parser.parse(filename, scale_factor);

	initQuerySet();

	return true;
}

void recast_navigation::NavmeshGraph::saveTofile(const string & filename)
{
	FileNavmeshParser saver(*this);
	saver.saveToFile(filename);
}

vector<Vec2> recast_navigation::NavmeshGraph::AStarSearch(Vec2 start, Vec2 end)
{
	return vector<Vec2>();
}

int recast_navigation::NavmeshGraph::pointInWhichPoly(const Vec2 & point)
{
	//// 直接查询
	//int ret = 0;
	//traversal([&ret,point](GraphNode* node) {
	//	if (node->poly.containsPoint(point))
	//	{
	//		ret = node->idx;
	//		return;
	//	}
	//});

	//if (ret != 0)
	//{
	//	return ret;
	//}
	//else
	//{
	//	CCLOG("cannot find this point in map, it's likely that inside the obstacle set, point： %f, %f", point.x, point.y);
	//	return 0;
	//}

	// 利用曼哈顿表来查询
	float Manhattan_dist = point.x + point.y;
	int centre = 0;
	int length = _ref4Query.size();
	for (; centre < length; ++centre)
	{
		if (_ref4Query.at(centre).centroid < Manhattan_dist)
			break;
	}

	centre = centre < length ? centre : (length - 1);

	if (_nodeMap[_ref4Query.at(centre).idx]->poly.containsPoint(point))
	{
		return _ref4Query.at(centre).idx;
	}

	int ret = 0;

	int left = centre;
	int right = centre;

	bool leftEnd = false;
	bool rightEnd = false;

	while (!(leftEnd && rightEnd))
	{
		if (left < length && left >= 0)
		{
			if (_nodeMap.at(_ref4Query.at(left).idx)->poly.containsPoint(point))
			{
				ret = _ref4Query.at(left).idx;
			}
			left--;
		}
		else
		{
			leftEnd = true;
		}

		if (right < length && right >= 0)
		{
			if (_nodeMap.at(_ref4Query.at(right).idx)->poly.containsPoint(point))
			{
				ret = _ref4Query.at(right).idx;
			}

			right++;
		}
		else
		{
			rightEnd = true;
		}
	}

	if (ret != 0)
	{
		return ret;
	}
	else
	{
		//CCLOG("cannot find this point in map, it's likely that inside the obstacle set, point： %f, %f", point.x, point.y);
		return 0;
	}
}

bool recast_navigation::NavmeshGraph::LOS_test(const Vec2 heading, Edge e)
{
	Vec3 h3d = Vec3(heading.x, heading.y, 0);
	Vec3 f3d = Vec3(e.from.x, e.from.y, 0);
	Vec3 t3d = Vec3(e.to.x, e.to.y, 0);

	Vec3 test_a = Vec3::ZERO;
	Vec3 test_b = Vec3::ZERO;
	
	Vec3::cross(f3d, h3d, &test_a);
	Vec3::cross(t3d, h3d, &test_b);

	bool tag_a = test_a.z > 0;
	bool tag_b = test_b.z > 0;

	return tag_a == tag_b;
}

void recast_navigation::NavmeshGraph::traversal(function<void(GraphNode*)> func) const
{
	for (auto iter = _nodeMap.cbegin(); iter != _nodeMap.cend(); ++iter)
	{
		func(iter->second);
	}
}

void recast_navigation::NavmeshGraph::initQuerySet()
{
	for (auto iter = _nodeMap.begin(); iter != _nodeMap.end(); ++iter)
	{
		Index_Centroid idx_cen;
		idx_cen.idx = iter->second->idx;
		auto cen = iter->second->poly.centroid;

		// 此处采用曼哈顿街道函数来表示位置信息
		idx_cen.centroid = cen.x + cen.y;
		_ref4Query.push_back(idx_cen);
	}

	std::sort(_ref4Query.begin(), _ref4Query.end());
}

void recast_navigation::NavmeshGraph::addPoly(GraphNode* node)
{
	_nodeMap.insert(make_pair(node->idx,node));
	_size++;
}

void recast_navigation::NavmeshGraph::sliceEdge(Vec2 from, Vec2 to)
{
}

void recast_navigation::NavmeshGraph::combineEdge(Vec2 from, Vec2 to)
{
}
