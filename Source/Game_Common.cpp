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
				if (Rect(Arg::center(Scene::Center().movedBy(0, -100).movedBy((h - Maze_CenterH) * Maze_BrockSize, (w - Maze_CenterW) * Maze_BrockSize)), Maze_BrockSize).intersects(Rect(Arg::center(Pos.movedBy(Delta_Point[Next_Direction])), Maze_BrockSize))) {
					flag = false;
				}
			}
		}
	}
	if (flag) {
		Direction = Next_Direction;
	}
	//à⁄ìÆêÊÇ™ï«Ç»ÇÁreturn
	for (auto h : step(Maze_Height)) {
		for (auto w : step(Maze_Width)) {
			if (MazeData[h][w]) {
				if (Rect(Arg::center(Scene::Center().movedBy(0, -100).movedBy((h - Maze_CenterH) * Maze_BrockSize, (w - Maze_CenterW) * Maze_BrockSize)), Maze_BrockSize).intersects(Rect(Arg::center(Pos.movedBy(Delta_Point[Direction]*Frame_Per_Move)), Maze_BrockSize))) {
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

void DrawMaze() {
	for (auto h : step(Maze_Height)) {
		for (auto w : step(Maze_Width)) {
			if (MazeData[h][w]) {
				Rect(Arg::center(Scene::Center().movedBy(0,-100).movedBy((h - Maze_CenterH) * Maze_BrockSize, (w - Maze_CenterW) * Maze_BrockSize)), Maze_BrockSize).draw(Palette::White).drawFrame(2, 0, Palette::Black);
			}
		}
	}
}

Point Ghost0_InitPos() {
	return Scene::Center().movedBy(0, -100).movedBy((1 - Maze_CenterH) * Maze_BrockSize, (1 - Maze_CenterW) * Maze_BrockSize);
}
Point Ghost1_InitPos() {
	return Scene::Center().movedBy(0, -100).movedBy((19 - Maze_CenterH) * Maze_BrockSize, (19 - Maze_CenterW) * Maze_BrockSize);
}
Point Tagger0_InitPos() {
	return Scene::Center().movedBy(0, -100).movedBy((19 - Maze_CenterH) * Maze_BrockSize, (1 - Maze_CenterW) * Maze_BrockSize);
}
Point Tagger1_InitPos() {
	return Scene::Center().movedBy(0, -100).movedBy((1 - Maze_CenterH) * Maze_BrockSize, (19 - Maze_CenterW) * Maze_BrockSize);
}