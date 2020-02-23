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
    const IPv4 ip = IPv4::Localhost();
    constexpr uint16 port = 50000;
    bool connected = false;
    TCPClient client;
    client.connect(ip, port);
    Window::Resize(800, 800);
    Window::SetTitle(U"TCPClient: Waiting for connection...");
    while (System::Update()) {
        for (Line L : Maze) {
            L.draw(2);
        }
        for (Circle C : Traps) {
            C.draw(Color(255, 0, 0, 100));
        }
        if (client.isConnected()) {
            if (!connected) {
                connected = true;
                Window::SetTitle(U"TCPClient: Connection established!");
                PB[0].R = Rect(100, 100, 40, 40);
                PB[1].R = Rect(660, 660, 40, 40);
                PB[2].R = Rect(100, 660, 40, 40);
                PB[3].R = Rect(660, 100, 40, 40);
                for (int i : step(4)) {
                    PB[i].B = Array<bool>(4, false);
                }
                caught[0] = caught[1] = false;
            }
            PB[2].B[0] = KeyUp.pressed();
            PB[2].B[1] = KeyLeft.pressed();
            PB[2].B[2] = KeyDown.pressed();
            PB[2].B[3] = KeyRight.pressed();
            PB[3].B[0] = KeyW.pressed();
            PB[3].B[1] = KeyA.pressed();
            PB[3].B[2] = KeyS.pressed();
            PB[3].B[3] = KeyD.pressed();
            for (int i : step(2)) {
                PB[i + 2].Move();
            }
            for (int i : step(12)) {
                if (((!caught[0]) && Traps[i].intersects(PB[0].R)) || (((!caught[1]) && Traps[i].intersects(PB[1].R)))) {
                    Traps[i].draw(Palette::Red);
                }
            }
            if (caught[0]) {
                PB[0].Draw(Color(50, 255, 255, 100));
            }
            if (caught[1]) {
                PB[1].Draw(Color(50, 100, 255, 100));
            }
            PB[2].Draw(Palette::Orangered);
            PB[3].Draw(Palette::Orange);
            long long t = ((((PB[2].R.x * 1000ll) + PB[2].R.y) * 1000ll) + PB[3].R.x) * 1000ll + PB[3].R.y;
            client.send(t);
            while (client.read(t)) {
                caught[1] = t % 2;
                t /= 2;
                caught[0] = t % 2;
                t /= 2;
                PB[1].R.y = t % 1000;
                t /= 1000;
                PB[1].R.x = t % 1000;
                t /= 1000;
                PB[0].R.y = t % 1000;
                t /= 1000;
                PB[0].R.x = t % 1000; 
            }
        }
        if (client.hasError()){
            client.disconnect();
            connected = false;
            Window::SetTitle(U"TCPClient: Waiting for connection...");
            client.connect(ip, port);
        }
    }
}