#include "Common_Game.hpp"

player::player() {
	pos = Point(0, 0);
	direction = neutral;
	next_direction = neutral;
	score = 0;
	has_item = false;
	walking_timer = 0;
	invincible_timer = 0;
}
player::player(Point p) {
	pos = p;
	direction = neutral;
	next_direction = neutral;
	score = 0;
	has_item = false;
	walking_timer = 0;
	invincible_timer = 0;
}
void player::draw() const {
	//sinatori 上下左右静止
	//時間ごとに絵を変更
	if (invincible_timer > 60)return;
	if (invincible_timer > 0) {
		//ここ星が回転とかかっこいいエフェクトつけてみたい
		Circle(pos, invincible_timer + 20).draw(Color(col, 200));
	}

	if (direction == neutral) {
		player_picture[7].draw(Arg::center(pos));//ニュートラルの時の画像は一応下向きにしておく
	}
	else {
		player_picture[(direction - 1) * 2 + (walking_timer / 5) % 2].draw(Arg::center(pos));
	}
}
void player::draw_light() const {
	light().draw(6, Palette::Yellow);
}
void player::update() {
	if (!intersect_maze(Rect(Arg::center(pos), maze_brock_size).movedBy(delta_point[next_direction]))) {
		direction = next_direction;
	}
	if (!intersect_maze(Rect(Arg::center(pos), maze_brock_size).movedBy(delta_point[direction] * frame_per_move))) {
		pos.moveBy(delta_point[direction] * frame_per_move);
	}
	//sinatori 動いたら絵を一つ変える
	if (direction == neutral) {
		walking_timer = 0;
	}
	else {
		walking_timer++;
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
	return Line(p, pos);
}
bool player::intersects(item& it) {
	return Rect(Arg::center(pos), maze_brock_size).intersects(Circle(it.get_pos(), it.get_radius()));
}
void player::set_pos(Point p) {
	pos = p;
}
void player::set_pos(uint16 h, uint16 w) {
	pos = maze_brock_position(h, w);
}
void player::set_direction(e_direction e_dir) {
	//sinatori 向きを変えたら絵を最初からにしよう
	if (e_dir != direction) {
		walking_timer = 0;
	}
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
//sinatori
uint16 player::get_invincible_timer() {
	return invincible_timer;
}
void player::set_invincible_timer() {
	invincible_timer = default_invincible;
}
void player::count_invincible_timer() {
	invincible_timer--;
}
void player::set_texture(uint16 i, String file_name) {
	player_picture[i] = Texture(Resource(file_name));
}
void player::set_frame_per_move(uint16 fpm) {
	frame_per_move = fpm;
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

item_effect::item_effect(const Point& p) {
	pos = p;
}
bool item_effect::update(double t) {
	const double e = EaseOutExpo(t);
	Circle(pos, e * 60).drawFrame(12.0 * (1.0 - e), Palette::Lime);
	return t < 1.0;
}

tag_effect::tag_effect(const Point& p) {
	pos = p;
}

bool tag_effect::update(double t) {
	FontAsset(U"font40")(U"Tag!").drawAt(pos.movedBy(0, t * -80.0), Palette::Limegreen);
	return t < 1.0;
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
	return Scene::Center() + Point((-maze_width + 1) * maze_brock_size / 2, (-maze_height + 1) * maze_brock_size / 2) + Point(w * maze_brock_size, h * maze_brock_size);
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

Point random_player_respawn_position(player& player2, player& player3) {
	while (true) {
		Point p = random_maze_brock_position();
		if (player2.get_pos().distanceFrom(p) > maze_brock_size * 7 && player3.get_pos().distanceFrom(p) > maze_brock_size * 7)return p;//敵プレイヤーと7マス以上離して復活
	}
}



void draw_timer(uint16 t) {
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


bool tag(player ghost, player tagger) {
	auto p = tagger.get_pos();
	for (auto i : step(light_range)) {
		if (!intersect_maze(p + delta_point[tagger.get_direction()])) {
			p += delta_point[tagger.get_direction()];
		}
		if (Rect(Arg::center(ghost.get_pos()), maze_brock_size).intersects(p))return true;
	}
	return false;
}