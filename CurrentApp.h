#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"
#include "player.h"
#include "EnemyManager.cpp"
#include "level.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace Polycode;

class CurrentApp : public EventHandler {
public:
    CurrentApp(PolycodeView *view);
    ~CurrentApp();
    bool Update();
    
private:
	Core *core;
	Player player;
	CollisionScene *scene;
	EnemyManager enemies;
	std::vector<Level*>path;
	ScreenLabel *keys_pressed, *a_pressed, *d_pressed;
	void handleEvent(Event *e);
};
