#include "Common_Game.hpp"

player::player() {
	pos = Point(0, 0);
	direction = neutral;
	next_direction = neutral;
	score = 0;
	invincible_timer = 0;
	special_item = nothing;
	special_item_thunder_timer = 0;
	special_item_wing_timer = 0;
}
player::player(Point p) {
	pos = p;
	direction = neutral;
	next_direction = neutral;
	score = 0;
	invincible_timer = 0;
	special_item = nothing;
	special_item_thunder_timer = 0;
	special_item_wing_timer = 0;
}
void player::draw(uint16 timer) const {
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
		player_picture[(direction - 1) * 2 + (timer / 5) % 2].draw(Arg::center(pos));
	}
}
void player::draw_range(Rect r, uint16 timer)const {
//	if (r.intersects(pos))draw();
	if (direction == neutral) {
		player_picture[7].drawAtClipped(pos, r);
	}
	else {
		player_picture[(direction - 1) * 2 + (timer / 5) % 2].drawAtClipped(pos, r);
	}
}
void player::draw_light() const {
	light_rect().draw(Color(255, 255, 0, 30));
	light_triangle().draw(Color(255, 255, 0, 30));
}
void player::update() {
	//6フレーム前まで見て、曲がれるか
	Point p = pos;
	for (auto i : step(frame_per_move * 6)) {
		if (!intersect_maze(Rect(Arg::center(p), maze_brock_size).movedBy(delta_point[next_direction]))) {
			direction = next_direction;
			p.moveBy(delta_point[direction] * i);
			pos = p;
			break;
		}
		else {
			p.moveBy(-delta_point[direction]);
		}
	}
	for (auto i : step(frame_per_move)) {
		if (!intersect_maze(Rect(Arg::center(pos), maze_brock_size).movedBy(delta_point[next_direction]))) {
			direction = next_direction;
		}
		if (!intersect_maze(Rect(Arg::center(pos), maze_brock_size).movedBy(delta_point[direction]))) {
			pos.moveBy(delta_point[direction]);
		}
	}
	//sinatori 動いたら絵を一つ変える
//	if (direction == neutral) {
//		walking_timer = 0;
//	}
//	else {
//		walking_timer++;
//	}
}
void player::update_direction(e_direction e_dir) {
	if (e_dir != neutral) {
		next_direction = e_dir;
	}
}
Rect player::light_rect()const {
	Point p, q;
	e_direction dir = direction;
	if (dir == e_direction::neutral) {
		dir = e_direction::down;
	}
	p = q = pos + delta_point[dir] * maze_brock_size / 2;
	for (auto i : step(180)) {
		if (!intersect_maze(p + delta_point[dir] * 10)) {
			p += delta_point[dir] * 10;
		}
		else {
			break;
		}
	}
	for (auto i : step(10)) {
		if (!intersect_maze(p + delta_point[dir])) {
			p += delta_point[dir];
		}
		else {
			break;
		}
	}
	p += delta_point[dir].yx() * maze_brock_size / 2;
	q -= delta_point[dir].yx() * maze_brock_size / 2;
	return Rect(p, q - p);
}
Triangle player::light_triangle()const {
	Point p, q;
	e_direction dir = direction;
	if (dir == e_direction::neutral) {
		dir = e_direction::down;
	}
	p = pos + (delta_point[dir] + delta_point[dir].yx()) * maze_brock_size / 2;
	q = pos + (delta_point[dir] - delta_point[dir].yx()) * maze_brock_size / 2;
	return Triangle(pos, p, q);
}
Rect player::rect_ghost_visible()const {
	Point p, q;
	e_direction dir = direction;
	if (dir == e_direction::neutral) {
		dir = e_direction::down;
	}
	p = q = pos - delta_point[dir] * maze_brock_size / 2;
	for (auto i : step(180)) {
		if (!intersect_maze(p + delta_point[dir] * 10)) {
			p += delta_point[dir] * 10;
		}
		else {
			break;
		}
	}
	for (auto i : step(10)) {
		if (!intersect_maze(p + delta_point[dir])) {
			p += delta_point[dir];
		}
		else {
			break;
		}
	}
	p += delta_point[dir].yx() * maze_brock_size / 2;
	q -= delta_point[dir].yx() * maze_brock_size / 2;
	//高さや幅が負になるとうまくいかなかったので
	Point a, b;
	a = Point(Min(p.x, q.x), Min(p.y, q.y));
	b = Point(Max(p.x, q.x), Max(p.y, q.y));
	return Rect(a, b - a);
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
//	if (e_dir != direction) {
//		walking_timer = 0;
//	}
	direction = e_dir;
}
void player::set_next_direction(e_direction e_n_dir) {
	next_direction = e_n_dir;
}
void player::set_score(uint16 t) {
	score = t;
}
void player::set_special_item(e_item_type t) {
	special_item = t;
}
void player::add_score(uint16 t) {
	score += t;
}
Point player::get_pos()const {
	return pos;
}
uint16 player::get_score()const {
	return score;
}
e_direction player::get_direction()const {
	return direction;
}
e_direction player::get_next_direction()const {
	return next_direction;
}
e_item_type player::get_special_item()const {
	return special_item;
}
uint16 player::get_special_item_thunder_timer()const {
	return special_item_thunder_timer;
}
uint16 player::get_special_item_wing_timer()const {
	return special_item_wing_timer;
}
void player::set_color(Color c) {
	col = c;
}
void player::set_special_item_thunder_timer(uint16 t) {
	special_item_thunder_timer = t;
}
void player::set_special_item_wing_timer(uint16 t) {
	special_item_wing_timer = t;
}
void player::count_special_item_thunder_timer() {
	if (special_item_thunder_timer != 0) {
		special_item_thunder_timer--;
	}
}
void player::count_special_item_wing_timer() {
	if (special_item_wing_timer != 0) {
		special_item_wing_timer--;
	}
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
uint16 player::get_frame_per_move() const {
	return frame_per_move;
}

item::item() {
	pos = Point(0, 0);
	type = point1;
	picture = NULL;
	radius = item_radius;
}
item::item(Point p, e_item_type t,Texture& te) {
	pos = p;
	type = t;
	picture = &te;
	radius = item_radius;
}
void item::draw() {
	picture->draw(Arg::center(pos));
}
void item::set_pos(Point p) {
	pos = p;
}
void item::set_type(e_item_type t, Texture* te) {
	type = t;
	picture = te + t;
}
void item::set_texture(Texture& te) {
	picture = &te;
}
Point item::get_pos() {
	return pos;
}
uint16 item::get_radius() {
	return radius;
}
e_item_type item::get_type() {
	return type;
}

item_effect::item_effect(const Point& p, const Color& c) {
	pos = p;
	col = c;
	AudioAsset(U"item_get").play();
}
bool item_effect::update(double t) {
	const double e = EaseOutExpo(t);
	Circle(pos, e * 60).drawFrame(12.0 * (1.0 - e), col);
	return t < 1.0;
}

tag_effect::tag_effect(const Point& p, Texture& t) {
	pos = p;
	texture = &t;
	AudioAsset(U"tag").play();
}

bool tag_effect::update(double t) {
	texture->drawAt(pos.movedBy(0, t * -80.0), ColorF(1, 1, 1, 1 - t));
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

item random_next_item(Array<item>& ai, Texture* tex, uint16& counter) {
	counter++;
	while (true) {
		bool f = true;
		Point p = random_maze_brock_position();
		for (auto it : ai) {
			if (it.get_pos().distanceFrom(p) < maze_brock_size * 4)f = false;//他のアイテムと4ブロック以内に湧かせない
		}
		if (f) {
			uint16 t;
			if (counter % 10 == 0) {
				if (counter % 20 == 0) {
					t = 3;
				}
				else {
					t = 4;
				}
			}
			else {
				t = Random(0, 2);
			}
			return item(p, (e_item_type)t, tex[t]);
		}
	}
}

Point random_player_respawn_position(player& player2, player& player3) {
	while (true) {
		Point p = random_maze_brock_position();
		if (player2.get_pos().distanceFrom(p) > maze_brock_size * 8 && player3.get_pos().distanceFrom(p) > maze_brock_size * 8)return p;//敵プレイヤーと8マス以上離して復活
	}
}

void draw_timer(uint16 t) {
	FontAsset(U"font40")(U"{:0>2}:{:0>2}"_fmt(t / 60 / 60, t / 60 % 60)).drawAt(timer_box.center(), Palette::White);
}

void draw_big_point_box(uint16 t) {
	FontAsset(U"font40")(U"{:0>4}"_fmt(t)).drawAt(big_point_box.center());
}

void draw_small_point_box(uint16 t) {
	FontAsset(U"font40")(U"{:0>4}"_fmt(t)).drawAt(small_point_box.center());
}


bool is_tagged(player ghost, player tagger) {
	//直接接触しているかの判定に変更
	return Rect(Arg::center(ghost.get_pos()), maze_brock_size).intersects(tagger.get_pos());
	/*
	auto p = tagger.get_pos();
	for (auto i : step(light_range)) {
		if (!intersect_maze(p + delta_point[tagger.get_direction()])) {
			p += delta_point[tagger.get_direction()];
		}
		if (Rect(Arg::center(ghost.get_pos()), maze_brock_size).intersects(p))return true;
	}
	return false;
	*/
}

void left_special_item_timer_draw(uint16 t, uint16 a, Color col) {
	for (uint16 i = 0;i < 6;i++) {
		Rect(263 - i * 7, 976 + i * 14, 350 * t / a, 14).draw(col);
	}
}
void right_special_item_timer_draw(uint16 t, uint16 a, Color col) {
	for (uint16 i = 0;i < 6;i++) {
		Rect(1663 + i * 7 - 350 * t / a, 975 + i * 14, 350 * t / a, 14).draw(col);
	}
}

void thunder_effect_draw() {
	Scene::Rect().draw(Color(255, 0, 0, 20));
}

void countdown_clock_draw(uint16 t) {
	if (t > 300) {
		Circle(Scene::Center(), 150).drawArc(0, 1_pi * ((t - 300) * 6) / 180, 0, 40, Palette::Blue);
		FontAsset(U"font200")(U"5").drawAt(Scene::Center());
	}
	else if (t > 240) {
		Circle(Scene::Center(), 150).drawArc(0, 1_pi * ((t - 240) * 6) / 180, 0, 40, Palette::Green);
		FontAsset(U"font200")(U"4").drawAt(Scene::Center());
	}
	else if (t > 180) {
		Circle(Scene::Center(), 150).drawArc(0, 1_pi * ((t - 180) * 6) / 180, 0, 40, Palette::Yellow);
		FontAsset(U"font200")(U"3").drawAt(Scene::Center());
	}
	else if (t > 120) {
		Circle(Scene::Center(), 150).drawArc(0, 1_pi * ((t - 120) * 6) / 180, 0, 40, Palette::Orange);
		FontAsset(U"font200")(U"2").drawAt(Scene::Center());
	}
	else if (t > 60) {
		Circle(Scene::Center(), 150).drawArc(0, 1_pi * ((t - 60) * 6) / 180, 0, 40, Palette::Red);
		FontAsset(U"font200")(U"1").drawAt(Scene::Center());
	}
	else {
		FontAsset(U"font200")(U"START!!").drawAt(Scene::Center(), Palette::Yellow);
	}
}