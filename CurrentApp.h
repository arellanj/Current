#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"
#include "player.h"
#include "LevelManager.h"
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
	LevelManager level;
	ScreenLabel *keys_pressed, *a_pressed, *d_pressed;
	void handleEvent(Event *e);
};
