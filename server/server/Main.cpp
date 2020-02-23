#include <Siv3D.hpp> // OpenSiv3D v0.4.2

const Array<Line>Maze = {
	Line(80,80,720,80),Line(160,160,400,160),Line(560,160,640,160),Line(240,240,320,240),Line(640,240,720,240),Line(400,320,640,320),Line(160,400,320,400),Line(480,400,640,400),Line(160,480,240,480),Line(320,480,400,480),Line(560,480,640,480),Line(80,560,160,560),Line(240,560,320,560),Line(400,560,480,560),Line(640,560,720,560),Line(160,640,320,640),Line(560,640,640,640),Line(80,720,720,720),Line(80,80,80,720),Line(160,160,160,320),Line(240,240,240,320),Line(240,480,240,560),Line(320,320,320,400),Line(400,160,400,320),Line(400,480,400,640),Line(480,80,480,240),Line(480,400,480,480),Line(480,640,480,720),Line(560,160,560,240),Line(560,480,560,640),Line(720,80,720,720)
};

const Array<Circle>Traps = {
	Circle(360,120,35),Circle(440,120,35),Circle(120,360,35),Circle(360,360,35),Circle(440,360,35),Circle(680,360,35),Circle(120,440,35),Circle(360,440,35),Circle(440,440,35),Circle(680,440,35),Circle(360,680,35),Circle(440,680,35)
};

const int d = 5;

struct PlayerBalls {
	Circle C;
	Array<bool>B;
	void Move() {
		if (B[0]) {
			C.y -= d;
			for (Line L : Maze) {
				if (C.intersects(L))C.y += d;
			}
		}
		if (B[1]) {
			C.x -= d;
			for (Line L : Maze) {
				if (C.intersects(L))C.x += d;
			}
		}
		if (B[2]) {
			C.y += d;
			for (Line L : Maze) {
				if (C.intersects(L))C.y -= d;
			}
		}
		if (B[3]) {
			C.x += d;
			for (Line L : Maze) {
				if (C.intersects(L))C.x -= d;
			}
		}
		
	}
	void Draw(Color Col) {
		C.draw(Col);
	}
};

PlayerBalls PB[4];
bool caught[2];

void Main() {
	constexpr uint16 port = 50000;
	bool connected = false;

	TCPServer server;
	server.startAccept(port);
	Window::SetTitle(U"TCPServer: Waiting for connection...");
	Window::Resize(800, 800);
	while (System::Update()) {
		for (Line L : Maze) {
			L.draw(2);
		}
		for (Circle C : Traps) {
			C.draw(Color(255, 0, 0, 100));
		}
		if (server.hasSession()) {
			if (!connected) {
				connected = true;
				Window::SetTitle(U"TCPServer: Connection established!");
				PB[0].C = Circle(120, 120, 30);
				PB[1].C = Circle(680, 680, 30);
				PB[2].C = Circle(120, 680, 30);
				PB[3].C = Circle(680, 120, 30);	
				for (int i : step(4)) {
					PB[i].B = Array<bool>(4, false);
				}
				caught[0] = caught[1] = false;
			}
			PB[0].B[0] = KeyUp.pressed();
			PB[0].B[1] = KeyLeft.pressed();
			PB[0].B[2] = KeyDown.pressed();
			PB[0].B[3] = KeyRight.pressed();
			PB[1].B[0] = KeyW.pressed();
			PB[1].B[1] = KeyA.pressed();
			PB[1].B[2] = KeyS.pressed();
			PB[1].B[3] = KeyD.pressed();
			for (int i : step(2)) {
				for (int j : step(2)) {
					caught[i] |= PB[i].C.intersects(PB[j + 2].C);
				}
			}
			for (int i : step(2)) {
				PB[i].Move();
			}
			for (int i : step(12)) {
				if (((!caught[0])&&Traps[i].intersects(PB[0].C)) || (((!caught[1])&&Traps[i].intersects(PB[1].C)))) {
					Traps[i].draw(Palette::Red);
				}
			}
			if (caught[0]) {
				PB[0].Draw(Color(50, 255, 255, 100));
			}
			else {
				PB[0].Draw(Color(50, 255, 255));
			}
			if (caught[1]) {
				PB[1].Draw(Color(50, 100, 255, 100));
			}
			else {
				PB[1].Draw(Color(50, 100, 255));
			}
			PB[2].Draw(Palette::Pink);
			PB[3].Draw(Palette::Orange);
			long long t = ((((PB[0].C.x * 1000ll) + PB[0].C.y) * 1000ll) + PB[1].C.x) * 1000ll + PB[1].C.y;
			server.send(t);
			while (server.read(t)) {
				PB[3].C.y = t % 1000;
				t /= 1000;
				PB[3].C.x = t % 1000;
				t /= 1000;
				PB[2].C.y = t % 1000;
				t /= 1000;
				PB[2].C.x = t % 1000;
			}
		}
		if (connected && !server.hasSession()) {
			server.disconnect();
			connected = false;
			Window::SetTitle(U"TCPServer: Waiting for connection...");
			server.startAccept(port);
		}
	}
}