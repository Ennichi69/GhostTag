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
	bool flag = true;//true:ï˚å¸ÇïœÇ¶ÇÈ
	for (auto h : step(Maze_Height)) {
		for (auto w : step(Maze_Width)) {
			if (MazeData[h][w]) {
				if (Rect(Arg::center(Maze_BrockPos(h,w)), Maze_BrockSize).intersects(Rect(Arg::center(Pos.movedBy(Delta_Point[Next_Direction])), Maze_BrockSize))) {
					//ï˚å¸ÇïœÇ¶ÇΩêÊÇ™ï«Ç»ÇÁfalse
					flag = false;
				}
			}
		}
	}
	if (flag) {
		Direction = Next_Direction;
	}
	for (auto h : step(Maze_Height)) {
		for (auto w : step(Maze_Width)) {
			if (MazeData[h][w]) {
				if (Rect(Arg::center(Maze_BrockPos(h, w)), Maze_BrockSize).intersects(Rect(Arg::center(Pos.movedBy(Delta_Point[Direction] * Frame_Per_Move)), Maze_BrockSize))) {
					//à⁄ìÆêÊÇ™ï«Ç»ÇÁreturn
					return;
				}
			}
		}
	}
	
	Pos.moveBy(Delta_Point[Direction] * Frame_Per_Move);
}

void Player::Update_Direction(uint16 dir) {
	if (dir) {
		Next_Direction = dir;
	}
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
