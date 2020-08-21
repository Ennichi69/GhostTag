#include "Common_Game.hpp"

player::player() {
	pos = Point(0, 0);
	direction = neutral;
	next_direction = neutral;
}
player::player(Point p) {
	pos = p;
	direction = neutral;
	next_direction = neutral;
}
void player::draw() const{
	Circle(pos, maze_brock_size / 2).draw(col);
}
void player::draw_light() const {
	light().draw(5, Palette::Yellow);
}
void player::update() {
	if (!intersect_maze(Rect(Arg::center(pos), maze_brock_size).movedBy(delta_point[next_direction]))) {
		direction = next_direction;
	}
	if (!intersect_maze(Rect(Arg::center(pos), maze_brock_size).movedBy(delta_point[direction]*frame_per_move))) {
		pos.moveBy(delta_point[direction] * frame_per_move);
	}
}
void player::update_direction(e_direction e_dir) {
	if (e_dir != neutral) {
		next_direction = e_dir;
	}
}
Line player::light()const {
	Point p = pos;
	for (auto i : step(light_range)) {
		if (!intersect_maze(p + delta_point[direction])) {
			p += delta_point[direction];
		}
	}
	return Line(pos, p);
}
void player::set_pos(Point p) {
	pos = p;
}
void player::set_pos(uint16 h, uint16 w) {
	pos = maze_brock_position(h, w);
}
void player::set_direction(e_direction e_dir) {
	direction = e_dir;
}
void player::set_next_direction(e_direction e_n_dir) {
	next_direction = e_n_dir;
}
Point player::get_pos() {
	return pos;
}
e_direction player::get_direction() {
	return direction;
}
e_direction player::get_next_direction() {
	return next_direction;
}
void player::set_color(Color c) {
	col = c;
}
item::item() {

}
item::item(Point p, uint16 t) {
	pos = p;
	type = t;
}
void item::draw() {
	Circle(pos, 10).draw(Palette::Yellow);
}
Point item::get_pos() {
	return pos;
}

void draw_maze() {
	for (auto i : step(maze_height)) {
		for (auto j : step(maze_width)) {
			if (maze_data[i][j]) {
				Rect(Arg::center(maze_brock_position(i, j)), maze_brock_size).draw(Palette::Orange);
			}
		}
	}
}

bool intersect_maze(Rect r) {
	bool f = false;
	for (auto i : step(maze_height)) {
		for (auto j : step(maze_width)) {
			if (maze_data[i][j]) {
				f |= Rect(Arg::center(maze_brock_position(i, j)), maze_brock_size).intersects(r);
			}
		}
	}
	return f;
}

bool intersect_maze(Point p) {
	bool f = false;
	for (auto i : step(maze_height)) {
		for (auto j : step(maze_width)) {
			if (maze_data[i][j]) {
				f |= Rect(Arg::center(maze_brock_position(i, j)), maze_brock_size).intersects(p);
			}
		}
	}
	return f;
}

Point maze_brock_position(uint16 h, uint16 w) {
	return Scene::Center()+Point((-maze_width + 1) * maze_brock_size / 2, (-maze_height + 1) * maze_brock_size / 2)+Point(w * maze_brock_size, h * maze_brock_size);
}