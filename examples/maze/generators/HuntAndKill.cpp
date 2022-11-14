#include "HuntAndKill.h"
#include "../World.h"
#include "Random.h"
#include <climits>
bool HuntAndKill::Step(World* w) {
	//x right = world->GetSize() / 2, left = -world->GetSize() / 2
	//y bottom = world->GetSize() / 2, top = -world->GetSize() / 2 

	if (firstTurn)
	{
		currentPlace = Point2D(Random(w->GetSize(), -w->GetSize() / 2),
			Random(w->GetSize(), -w->GetSize() / 2));
		firstTurn = false;
		visited[currentPlace.x][currentPlace.y] = true;
	}

	if (!walk(w))
		currentPlace = hunt(w);

	return true;
}
void HuntAndKill::Clear(World* world) {
    visited.clear();
    stack.clear();
    auto sideOver2 = world->GetSize() / 2;

    for (int i = -sideOver2; i <= sideOver2; i++) {
        for (int j = -sideOver2; j <= sideOver2; j++) {
            visited[i][j] = false;
        }
    }
}

bool HuntAndKill::walk(World* world)
{
	//1 north, 2 east, 3 south, 4 west
	std::vector<int> directions{ 1,2,3,4 };
	std::shuffle(directions.begin(), directions.end(), mt);

	int newX = currentPlace.x, newY = currentPlace.y;
	for (int dir : directions)
	{
		newX = currentPlace.x, newY = currentPlace.y;
		switch (dir)
		{
		case 1:
			newY = currentPlace.y + 1;
			break;
		case 2:
			newX = currentPlace.x - 1;
			break;
		case 3:
			newY = currentPlace.y - 1;
			break;
		case 4:
			newX = currentPlace.x + 1;
			break;
		default:
			break;
		}

		if (newX < (world->GetSize() / 2) + 1 && newX >(-world->GetSize() / 2) - 1 &&
			newY < (world->GetSize() / 2) + 1 && newY >(-world->GetSize() / 2) - 1 &&
			visited[newX][newY] == false)
		{

			changeData(world, dir, newX, newY);
			currentPlace = Point2D(newX, newY);
			return true;
		}
	}
	return false;
}

Point2D HuntAndKill::hunt(World* world)
{
	std::vector<int> directions;
	for (int y = (-world->GetSize() / 2); y < (world->GetSize() / 2) + 1; y++)
	{
		for (int x = (-world->GetSize() / 2); x < (world->GetSize() / 2) + 1; x++)
		{
			if (visited[x][y])
				continue;

			//north
			if (y > (-world->GetSize() / 2) - 1 && visited[x][y - 1])
			{
				directions.push_back(1);
			}
			//west
			if (x > (-world->GetSize() / 2) - 1 && visited[x - 1][y])
			{
				directions.push_back(4);
			}
			//east
			if (x + 1 < (world->GetSize() / 2) + 1 && visited[x + 1][y])
			{
				directions.push_back(2);
			}
			//south
			if (y + 1 < (world->GetSize() / 2) + 1 && visited[x][y + 1])
			{
				directions.push_back(3);
			}

			std::shuffle(directions.begin(), directions.end(), mt);

			if (directions.empty())
				continue;

			changeData(world, directions[0], x, y);

			return Point2D(x, y);
		}
	}

	return Point2D(0, 0);
}

void HuntAndKill::changeData(World* world, int direction, int newX, int newY)
{
	world->SetNodeColor({ newX,newY }, Color::Black);
	visited[newX][newY] = true;
	if (direction == 1)
	{
		if (newY != -(world->GetSize() / 2))
			world->SetNorth(Point2D(newX, newY), false);
	}
	else if (direction == 2)
	{
		if (newX != world->GetSize() / 2)
			world->SetEast(Point2D(newX, newY), false);
	}
	else if (direction == 3)
	{
		if (newY != world->GetSize() / 2)
			world->SetSouth(Point2D(newX, newY), false);
	}
	else if (direction == 4)
	{
		if (newX != -(world->GetSize() / 2))
			world->SetWest(Point2D(newX, newY), false);
	}
}

Point2D HuntAndKill::randomStartPoint(World* world) {
    auto sideOver2 = world->GetSize() / 2;

    for (int y = -sideOver2; y <= sideOver2; y++)
        for (int x = -sideOver2; x <= sideOver2; x++)
            if (!visited[y][x])
                return { x,y };
    return { INT_MAX, INT_MAX };
}

std::vector<Point2D> HuntAndKill::getVisitables(World* w, const Point2D& p) {
    auto sideOver2 = w->GetSize() / 2;
    std::vector<Point2D> visitables;

    // todo: improve this
    // north
    if ((abs(p.x) <= sideOver2 && abs(p.y - 1) <= sideOver2) && // should be inside the board
        !visited[p.y - 1][p.x] && // not visited yet
        w->GetNorth({ p.x, p.y - 1 })) // has wall
        visitables.emplace_back(p.x, p.y - 1);
    // east
    if ((abs(p.x + 1) <= sideOver2 && abs(p.y) <= sideOver2) && // should be inside the board
        !visited[p.y][p.x + 1] && // not visited yet
        w->GetNorth({ p.x + 1, p.y })) // has wall
        visitables.emplace_back(p.x + 1, p.y);
    // south
    if ((abs(p.x) <= sideOver2 && abs(p.y + 1) <= sideOver2) && // should be inside the board
        !visited[p.y + 1][p.x] && // not visited yet
        w->GetNorth({ p.x, p.y + 1 })) // has wall
        visitables.emplace_back(p.x, p.y + 1);
    // west
    if ((abs(p.x - 1) <= sideOver2 && abs(p.y) <= sideOver2) && // should be inside the board
        !visited[p.y][p.x - 1] && // not visited yet
        w->GetNorth({ p.x - 1, p.y })) // has wall
        visitables.emplace_back(p.x - 1, p.y);

    return visitables;
}
