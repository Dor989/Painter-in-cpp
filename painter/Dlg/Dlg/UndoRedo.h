#pragma once

#include "UndoRedoPoly.h"
#include "Figure.h"
#include <vector>

using namespace std;

class UndoRedo : public UndoRedoPoly {
public:
	UndoRedo(vector<Figure*> &shapes, Figure *shape)
		: shapes(shapes), shape(shape) {}

	void perform() { shapes.push_back(shape); }

	void rollback() {
		vector<Figure*>::iterator it;
		for (it = shapes.begin(); it != shapes.end(); ++it)
			if (*it == shape)
				break;
		if (it != shapes.end())
			shapes.erase(it);
	}
private:
	vector<Figure*> &shapes;
	Figure *shape;
};