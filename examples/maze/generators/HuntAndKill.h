#ifndef HUNTANDKILL_H
#define HUNTANDKILL_H

#include "../MazeGeneratorBase.h"
#include "Point2D.h"
#include <map>
#include <vector>
#include <unordered_map>
#include <random>

class HuntAndKill : public MazeGeneratorBase {
private:
	std::mt19937 mt = std::mt19937(std::time(nullptr));
	std::unordered_map<int, std::unordered_map<int, bool>> visited;
	Point2D currentPlace;
	bool firstTurn = true;

	int Random(int upper, int lower = 0) { return mt() % upper + lower; };

	bool walk(World* world);
	Point2D hunt(World* world);

	void changeData(World* world, int direction, int newX, int newY);

	std::vector<Point2D> stack;
	//std::map<int, std::map<int, bool>> visited; // naive. not optimal
	Point2D randomStartPoint(World* world);
	std::vector<Point2D> getVisitables(World* w, const Point2D& p);
public:
	HuntAndKill() = default;
	std::string GetName() override { return "Hunt and Kill"; };
	bool Step(World* world) override;
	void Clear(World* world) override;
};

#endif  // HUNTANDKILL_H
