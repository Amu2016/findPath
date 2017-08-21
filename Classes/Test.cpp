#include "Test.h"
#include "Lib_Navmesh\AStarSearch.h"
#include "Lib_Navmesh\GraphRender.h"

using namespace recast_navigation;

Scene * TestLayer::createScene()
{
	auto s = Scene::create();
	s->addChild(TestLayer::create(),1,"world");
	return s;
}

bool TestLayer::init()
{
	if (!Layer::init())
		return false;

	auto bg = LayerColor::create(Color4B::WHITE);
	this->addChild(bg, -10);

	//test navmesh graph
	NavmeshGraph nvmgh;

	nvmgh.loadFromFile("navmesh.json");

	// 画图
	GraphRender render(nvmgh);
	render.init();
	render.addToLayer(this, 1.0f);

	// 寻路
	AStarSearch pathFinder(nvmgh);

	Vec2 begin(200, 800);
	Vec2 end(600, 10);

	auto node1 = DrawNode::create();
	node1->drawCircle(begin, 2.0f, 360, 30, false, Color4F::MAGENTA);
	node1->drawCircle(end, 2.0f, 360, 30, false, Color4F::GREEN);
	this->addChild(node1, 10);

	auto nodes = pathFinder.result(begin, end);

	//画相交线
	for (int i = 1; i < nodes.size(); ++i)
	{
		auto poly1 = nvmgh.getNodeById(nodes[i - 1])->poly;
		auto poly2 = nvmgh.getNodeById(nodes[i])->poly;
		render.drawLine(poly1.findCommonEdge(poly2), Color4F::YELLOW);
	}


	//画路径网格
	CCLOG("%s", "route:");
	for (auto iter = nodes.cbegin(); iter != nodes.cend(); ++iter)
	{
		CCLOG("node is: %d", *iter);
		render.drawSolidPoly(*iter);
	}

	//画最终路径
	auto path = pathFinder.tp_path(begin, end);
	CCLOG("Way Point %d: %f, %f", 1, path[0].x, path[0].y);
	for (int i = 1; i < path.size(); ++i)
	{
		render.drawLine(Edge(path[i], path[i - 1]), Color4F::GREEN);
		CCLOG("Way Point %d: %f, %f", i + 1, path[i].x, path[i].y);
	}


	return true;
}
