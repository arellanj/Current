#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"
#include "player.h"
#include "LevelManager.h"
#include "keyboard.H"
#include <vector>
#include <iostream>

using namespace std;
using namespace Polycode;

class myTimer
{
	public:
		int minutes, seconds, milliseconds;
		bool isOn;	
		myTimer()
		:minutes(0), seconds(0), milliseconds(0), isOn(false)
		{}

		void Update(Number elapsed)
		{
			if( !isOn) return;
			milliseconds += elapsed * 1000;
			if( milliseconds >= 1000)
			{
				seconds++;
				milliseconds -=1000;
				if(seconds >= 60)
				{
					minutes++;
					seconds -= 60;
				}
			}	
		}

		void start()
		{
			isOn = true;
		}

		void stop()
		{
			isOn = false;
		}

		void reset()
		{
			minutes = 0;
			seconds = 0;
			milliseconds = 0;
		}

		String getTime()
		{
			return String::IntToString(minutes)+":"+
					String::IntToString(seconds)+":"+
					String::IntToString(milliseconds);
		}
};

class CurrentApp : public EventHandler {
public:
    CurrentApp(PolycodeView *view);
    ~CurrentApp();
    bool Update();
    
private:
	myTimer timer;
	Core *core;
	Player player;
	Keyboard keyboard;
	CollisionScene *scene;
	LevelManager *level;
	ScreenLabel *keys_pressed, *coins_hud, *time_hud;
	Screen *hud;
	void handleEvent(Event *e);
};
