#include "Game_Common.hpp"

Player::Player(Point pos, Color col) {
	Pos = pos;
	Col = col;
	Direction = 0;
	Next_Direction = 0;
}
void Player::Draw() const {
	Circle(Pos, Maze_BrockSize / 2).draw(Col);
}
void Player::Update() {
	if (!Intersect_Maze(Rect(Arg::center(Pos), Maze_BrockSize).movedBy(Delta_Point[Next_Direction]))) {
		Direction = Next_Direction;
	}
	if (!Intersect_Maze(Rect(Arg::center(Pos), Maze_BrockSize).movedBy(Delta_Point[Direction] * Frame_Per_Move))) {
		Pos.moveBy(Delta_Point[Direction] * Frame_Per_Move);
	}
}

void Player::Update_Direction(uint16 dir) {
	if (dir) {
		Next_Direction = dir;
	}
}

Item::Item() {
	Pos = Point();
	Type = 0;
}

Item::Item(Point pos, uint16 type) {
	Pos = pos;
	Type = type;
}

void Item::Draw() {
	Circle(Pos, 10).draw(Palette::Yellow);
}

void Draw_Maze() {
	for (auto h : step(Maze_Height)) {
		for (auto w : step(Maze_Width)) {
			if (MazeData[h][w]) {
				Rect(Arg::center(Maze_BrockPos(h, w)), Maze_BrockSize).draw(Palette::White).drawFrame(2, 0, Palette::Black);
			}
		}
	}
}
bool Intersect_Maze(Rect r) {
	for (uint16 h : step(Maze_Height)) {
		for (uint16 w : step(Maze_Width)) {
			if (MazeData[h][w]) {
				if (Rect(Arg::center(Maze_BrockPos(h, w)), Maze_BrockSize).intersects(r)) {
					return true;
				}
			}
		}
	}
	return false;
}
bool Intersect_Maze(Circle c) {
	for (uint16 h : step(Maze_Height)) {
		for (uint16 w : step(Maze_Width)) {
			if (MazeData[h][w]) {
				if (Rect(Arg::center(Maze_BrockPos(h, w)), Maze_BrockSize).intersects(c)) {
					return true;
				}
			}
		}
	}
	return false;
}
bool Intersect_Maze(Point p) {
	for (uint16 h : step(Maze_Height)) {
		for (uint16 w : step(Maze_Width)) {
			if (MazeData[h][w]) {
				if (Rect(Arg::center(Maze_BrockPos(h, w)), Maze_BrockSize).intersects(p)) {
					return true;
				}
			}
		}
	}
	return false;
}
Point Maze_BrockPos(uint16 h, uint16 w) {
	return Scene::Center().movedBy(0, -50).movedBy((h - Maze_CenterH) * Maze_BrockSize, (w - Maze_CenterW) * Maze_BrockSize);
}
Point Ghost0_InitPos() {
	return Maze_BrockPos(1, 1);
}
Point Ghost1_InitPos() {
	return Maze_BrockPos(19, 19);
}
Point Tagger0_InitPos() {
	return Maze_BrockPos(1, 19);
}
Point Tagger1_InitPos() {
	return Maze_BrockPos(19, 1);
}
