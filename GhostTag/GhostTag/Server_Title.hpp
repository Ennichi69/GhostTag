#pragma once
#include "Common.hpp"

class Server_Title : public App::Scene {
public:
	Server_Title(const InitData& init);
	void update() override;
	void draw() const override;
private:
	bool IsReady = false;
};