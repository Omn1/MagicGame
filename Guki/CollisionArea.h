#pragma once
#include "Misc.h"
#include <iostream>
class CollisionArea
{
public:
	CollisionArea() {}
	CollisionArea(sf::FloatRect rect, sf::Vector2f direction) {
		isRectangle = 1;
		x = rect.left;
		y = rect.top;
		width = rect.width;
		height = rect.height;
		isCircle = 0;
		radius = 0;
		dx = direction.x;
		dy = direction.y;
	}
	bool intersects(CollisionArea &r) {
		normalize(dx, dy);
		normalize(r.dx, r.dy);
		if (isRectangle && r.isRectangle) {
			float x2 = x + width*dx;
			float y2 = y + width*dy;
			float x3 = x2 - height*dy;
			float y3 = y2 + height*dx;
			float x4 = x - height*dy;
			float y4 = y + height*dx;
			//std::cout << "// " << dx << " " << dy << " " << height << " " << width << std::endl;
			//std::cout << x << " " << y << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " " << x4 << " " << y4 << std::endl;
			sf::Vector2f p1(x, y), p2(x2, y2), p3(x3, y3), p4(x4, y4);
			sf::RectangleShape shape(sf::Vector2f(20, 20));
			shape.setPosition(p1);
			shape.setFillColor(sf::Color::Red);
			mainWindow.draw(shape);
			float rx2 = r.x + r.width*r.dx;
			float ry2 = r.y + r.width*r.dy;
			float rx3 = rx2 - r.height*r.dy;
			float ry3 = ry2 + r.height*r.dx;
			float rx4 = r.x - r.height*r.dy;
			float ry4 = r.y + r.height*r.dx;
			sf::Vector2f rp1(r.x, r.y), rp2(rx2, ry2), rp3(rx3, ry3), rp4(rx4, ry4);
			return
				segIntersect(p1, p2, rp1, rp2) ||
				segIntersect(p1, p2, rp2, rp3) ||
				segIntersect(p1, p2, rp3, rp4) ||
				segIntersect(p1, p2, rp4, rp1) ||
				segIntersect(p2, p3, rp1, rp2) ||
				segIntersect(p2, p3, rp2, rp3) ||
				segIntersect(p2, p3, rp3, rp4) ||
				segIntersect(p2, p3, rp4, rp1) ||
				segIntersect(p3, p4, rp1, rp2) ||
				segIntersect(p3, p4, rp2, rp3) ||
				segIntersect(p3, p4, rp3, rp4) ||
				segIntersect(p3, p4, rp4, rp1) ||
				segIntersect(p4, p1, rp1, rp2) ||
				segIntersect(p4, p1, rp2, rp3) ||
				segIntersect(p4, p1, rp3, rp4) ||
				segIntersect(p4, p1, rp4, rp1);

		}
	}
	bool isRectangle;
	bool isCircle;
	float x, y;
	float dx, dy;
	float width, height, radius;
};

