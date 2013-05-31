#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"
#include "player.h"
#include "level.h"
#include <vector>
#include <iostream>
using namespace Polycode;

class CurrentApp : public EventHandler {
public:
    CurrentApp(PolycodeView *view);
    ~CurrentApp();
    bool Update();
    
private:
	Core *core;
	Player player;
	std::vector<Level*>path;
	ScreenLabel *keys_pressed, *a_pressed, *d_pressed;
	void handleEvent(Event *e);
};
