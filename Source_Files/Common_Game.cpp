#include "Common_Game.hpp"

player::player() {
	pos = Point(0, 0);
	direction = neutral;
	next_direction = neutral;
	score = 0;
	has_item = false;
}
player::player(Point p) {
	pos = p;
	direction = neutral;
	next_direction = neutral;
	score = 0;
	has_item = false;
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
bool player::intersects(Line l) {
	return Rect(Arg::center(pos), maze_brock_size).intersects(l);
}
bool player::intersects(item it) {
	return Rect(Arg::center(pos), maze_brock_size).intersects(Circle(it.get_pos(), it.get_radius()));
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
void player::set_score(uint16 t) {
	score = t;
}
void player::add_score(uint16 t) {
	score += t;
}
void player::set_has_item(bool b) {
	has_item = b;
}
Point player::get_pos() {
	return pos;
}
uint16 player::get_score()const {
	return score;
}
e_direction player::get_direction() {
	return direction;
}
e_direction player::get_next_direction() {
	return next_direction;
}
bool player::get_has_item() {
	return has_item;
}
void player::set_color(Color c) {
	col = c;
}


item::item() {
	pos = Point(0, 0);
	type = point;
	radius = item_radius;
}
item::item(Point p, e_item_type t) {
	pos = p;
	type = t;
	radius = item_radius;
}
void item::draw() {
	Circle(pos, radius).draw(Palette::Yellow);
}
void item::set_pos(Point p) {
	pos = p;
}
Point item::get_pos() {
	return pos;
}
uint16 item::get_radius() {
	return radius;
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

Point random_maze_brock_position() {
	while (true) {
		int h = Random(0, maze_height - 1);
		int w = Random(0, maze_width - 1);
		Point p = maze_brock_position(h, w);
		if (!intersect_maze(p))return p;
	}
}

Point random_point_item_position(Array<item>& ai) {
	while (true) {
		bool f = true;
		Point p = random_maze_brock_position();
		for (auto it : ai) {
			if (it.get_pos().distanceFrom(p) < maze_brock_size * 4)f = false;//他のアイテムと4ブロック以内に湧かせない
		}
		if (f)return p;
	}
}

void draw_timer(uint16 t){
	timer_box.drawFrame();
	FontAsset(U"font40")(U"{:0>2}:{:0>2}"_fmt(t / 60 / 60, t / 60 % 60)).drawAt(timer_box.center(), Palette::White);
}

void draw_big_point_box(uint16 t) {
	big_point_box.drawFrame();
	FontAsset(U"font40")(U"{:0>4}pt"_fmt(t)).drawAt(big_point_box.center());
}

void draw_small_point_box(uint16 t) {
	small_point_box.drawFrame();
	FontAsset(U"font40")(U"{:0>4}pt"_fmt(t)).drawAt(small_point_box.center());
}
