#pragma once
#include <vector>
#include "Object.h"
template<class T>
class GridList {
public:
	std::vector<T*> objects;

	void addObject(T * object)
	{
		object->textureScale = textureScale;
		objects.push_back(object);
	}

	void removeObject(T * object)
	{
		std::vector<T*> tobj = objects;
		objects.clear();
		for (int i = 0; i < tobj.size(); i++) {
			if (tobj[i] == object) {
				delete tobj[i];
			}
			else {
				objects.push_back(tobj[i]);
			}
		}
	}

	std::vector<T*> getObjects() {
		return objects;
	}

	float textureScale;
};