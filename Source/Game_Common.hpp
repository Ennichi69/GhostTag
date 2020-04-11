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

void Draw_Maze();
Point Maze_BrockPos(uint16 h, uint16 w);
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
constexpr Rect TimerBox = Rect(Arg::center(960, 1020), 300, 100);
constexpr Rect Player0_SpecialMeterBox = Rect(Arg::center(100, 700), 80, 700);
constexpr Rect Player1_SpecialMeterBox = Rect(Arg::center(1820, 700), 80, 700);
constexpr Rect Ghost_ScoreBox = Rect(Arg::center(250, 100), 400, 150);
constexpr Rect Tagger_ScoreBox = Rect(Arg::center(1670, 100), 400, 150);
constexpr Point Delta_Point[5] = { Point(0,0),Point(-1,0),Point(0,-1),Point(1,0),Point(0,1) };
constexpr uint16 Maze_Width = 21;
constexpr uint16 Maze_Height = 21;
constexpr uint16 Maze_BrockSize = 44;
constexpr uint16 Maze_CenterW = 10;
constexpr uint16 Maze_CenterH = 10;
constexpr uint16 Frame_Per_Move = 4;//���̒l��Map_BrockSize�̖񐔂���Ȃ��Ə�肭�����Ȃ��Ȃ�S�~�d�l ���̂�������
constexpr uint16 Init_Time = 7500;