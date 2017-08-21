#ifndef _GRAPH_RENDER_H_
#define _GRAPH_RENDER_H_
#include "Lib_Navmesh\NavmeshGraph.h"

using namespace recast_navigation;

class GraphRender
{
public:
	GraphRender(NavmeshGraph& root);
	~GraphRender();

	void init();

	void drawLine(const Edge& e, Color4F color = Color4F(0.76f, 0.45f, 0.0f, 1));

	void drawPoly(const ConvexPolygon& poly);

	void drawSolidPoly(int idx, Color4F color = Color4F(0.13f, 0.1f, 0.6f, 0.4f));

	void drawIndex(const Vec2& centroid, int idx);

	void addToLayer(Layer* container,float scale);
private:
	NavmeshGraph& _root;
	Node* _canvas;
};


#endif
