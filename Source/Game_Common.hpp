#pragma once
#include "Common.hpp"

class Player {
public:
	Player(Point pos, Color col);
	void Draw() const;
	void Update();
	void Update_Direction(uint16 dir);
	Point Pos;
	uint16 Type;
	uint16 Direction;
	uint16 Next_Direction;
private:
	Color Col;
};

void DrawMaze();

Point Ghost0_InitPos();
Point Ghost1_InitPos();
Point Tagger0_InitPos();
Point Tagger1_InitPos();

const Grid<bool>MazeData =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1},
	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
	{1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1},
	{1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1},
	{1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1},
	{1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1},
	{1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1},
	{1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1},
	{1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1},
	{1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1},
	{1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1},
	{1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1},
	{1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1},
	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
	{1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

constexpr Point Delta_Point[5] = { Point(0,0),Point(-1,0),Point(0,-1),Point(1,0),Point(0,1) };
constexpr uint16 Maze_Width = 21;
constexpr uint16 Maze_Height = 21;
constexpr uint16 Maze_BrockSize = 40;
constexpr uint16 Maze_CenterW = 10;
constexpr uint16 Maze_CenterH = 10;
constexpr uint16 Frame_Per_Move = 4;//Map_BrockSizeの約数じゃないと上手くいかなくなるゴミ仕様 そのうち直す
constexpr uint16 Init_Time = 7500;