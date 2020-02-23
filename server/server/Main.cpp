#include <Siv3D.hpp> // OpenSiv3D v0.4.2

const Array<Line>Maze = {
	Line(80,80,720,80),Line(320,160,400,160),Line(560,160,640,160),Line(240,240,320,240),Line(640,240,720,240),Line(400,320,640,320),Line(160,400,320,400),Line(480,400,640,400),Line(160,480,240,480),Line(320,480,400,480),Line(560,480,640,480),Line(80,560,160,560),Line(240,560,320,560),Line(400,560,480,560),Line(640,560,720,560),Line(160,640,320,640),Line(560,640,640,640),Line(80,720,720,720),Line(80,80,80,720),Line(160,160,160,320),Line(240,80,240,320),Line(240,480,240,560),Line(320,320,320,400),Line(400,160,400,320),Line(400,480,400,640),Line(480,80,480,240),Line(480,400,480,480),Line(480,640,480,720),Line(560,160,560,240),Line(560,480,560,640),Line(720,80,720,720)
};

const Array<Circle>Traps = { 
	Circle(360,120,30),Circle(440,120,30),Circle(120,360,30),Circle(360,360,30),Circle(440,360,30),Circle(680,360,30),Circle(120,440,30),Circle(360,440,30),Circle(440,440,30),Circle(680,440,30),Circle(360,680,30),Circle(440,680,30)
};

const int d = 5;

struct PlayerBalls {
	Rect R;
	Array<bool>B;
	void Move() {
		if (B[0]) {
			R.y -= d;
			for (Line L : Maze) {
				if (R.intersects(L))R.y += d;
			}
		}
		if (B[1]) {
			R.x -= d;
			for (Line L : Maze) {
				if (R.intersects(L))R.x += d;
			}
		}
		if (B[2]) {
			R.y += d;
			for (Line L : Maze) {
				if (R.intersects(L))R.y -= d;
			}
		}
		if (B[3]) {
			R.x += d;
			for (Line L : Maze) {
				if (R.intersects(L))R.x -= d;
			}
		}
		
	}
	void Draw(Color Col) {
		R.draw(Col);
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
				PB[0].R = Rect(100, 100, 40, 40);
				PB[1].R = Rect(660, 660, 40, 40);
				PB[2].R = Rect(100, 660, 40, 40);
				PB[3].R = Rect(660, 100, 40, 40);	
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
					caught[i] |= PB[i].R.intersects(PB[j + 2].R);
				}
			}
			for (int i : step(2)) {
				PB[i].Move();
			}
			for (int i : step(12)) {
				if (((!caught[0])&&Traps[i].intersects(PB[0].R)) || (((!caught[1])&&Traps[i].intersects(PB[1].R)))) {
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
			PB[2].Draw(Palette::Orangered);
			PB[3].Draw(Palette::Orange);
			long long t = ((((((PB[0].R.x * 1000ll) + PB[0].R.y) * 1000ll) + PB[1].R.x) * 1000ll + PB[1].R.y) * 2 + caught[0]) * 2 + caught[1];
			server.send(t);
			while (server.read(t)) {
				PB[3].R.y = t % 1000;
				t /= 1000;
				PB[3].R.x = t % 1000;
				t /= 1000;
				PB[2].R.y = t % 1000;
				t /= 1000;
				PB[2].R.x = t % 1000;
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