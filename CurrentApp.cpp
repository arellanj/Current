#include "CurrentApp.h"
#include <time.h>
	
CurrentApp::CurrentApp(PolycodeView *view) : EventHandler() {

	core = new SDLCore(view, 640,480,false,false,0,0,120);	  

	srand(time(NULL));
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", false);

	scene = new CollisionScene();
	level = new LevelManager(30, scene);

	// Creating the Player object
	ScenePrimitive * obj = new ScenePrimitive( ScenePrimitive::TYPE_SPHERE, 0.5, 10,10);
	obj->setPosition(Vector3(0.0, 0.0, 0.0));
	obj->setMaterialByName("CubeMaterial");
	scene->addCollisionChild(obj);

	hud = new Screen();
	keys_pressed = new ScreenLabel("Stats: ",16);
	hud->addChild(keys_pressed);
	coins_hud = new ScreenLabel("Coins: 0", 16);
	coins_hud->setPosition(0,20);
	time_hud = new ScreenLabel("Time: 00:00:00", 16);
	time_hud->setPosition(0,40);
	hud->addChild(coins_hud);
	hud->addChild(time_hud);
	

	player = Player(obj);

	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
	
	//player.Load(scene, hud);
	//physScene->addPhysicsChild(obj, PhysicsSceneEntity::SHAPE_SPHERE, 1.0);
	player.Load(scene);
	
	timer.start();
}

CurrentApp::~CurrentApp() {
	delete level;
	delete scene;
	delete core;
	delete coins_hud;
	delete time_hud;
	delete keys_pressed;
	delete hud;
}

void CurrentApp::handleEvent(Event *e)
{
 	static int camnum = 1;
	if(e -> getDispatcher() == core->getInput())
	{
		InputEvent * inputEvent = (InputEvent*)e;
		switch(e->getEventCode())
		{
			case InputEvent::EVENT_KEYDOWN:
				switch(inputEvent->keyCode())
				{
					case 27: // ESCAPE
						exit(0);
						break;
					case KEY_UP:
						keyboard.setKey(KEY_UP, true);
						break;
					case KEY_DOWN:
						keyboard.setKey(KEY_DOWN, true);
						break;
					case KEY_LEFT:
						keyboard.setKey(KEY_LEFT, true);
						break;
					case KEY_RIGHT:
						keyboard.setKey(KEY_RIGHT, true);
						break;
					case 306: // Left Control 
						keyboard.setKey(306, true);
						break;
					case 304: // Left Shift
						keyboard.setKey(304, true);
						break;
					case 49: // 1 
						if (camnum == 1 ) break;
						camnum = 1;
						scene->getDefaultCamera()->setPosition(Vector3(1,2,17));
						player.dirtyCam = true;
						break;
					case 50: // 2 
						if (camnum == 2 ) break;
						camnum = 2;
						scene->getDefaultCamera()->setPosition(Vector3(15,15,17));
						player.dirtyCam = true;
						break;
					default:
						//std::cout<<"KEY "<<inputEvent->keyCode()<<std::endl;
						break;
								
				}
				break;
			case InputEvent::EVENT_KEYUP:
				switch(inputEvent->keyCode())
				{
					case KEY_UP:
						keyboard.setKey(KEY_UP, false);
						break;
					case KEY_DOWN:
						keyboard.setKey(KEY_DOWN, false);
						break;
					case KEY_LEFT:
						keyboard.setKey(KEY_LEFT, false);
						break;
					case KEY_RIGHT:
						keyboard.setKey(KEY_RIGHT, false);
						break;
					case 306: // Left Control 
						keyboard.setKey(306, false);
						break;
					case 304: // Left Shift
						keyboard.setKey(304, false);
						break;
					default:
						break;
				}
				break;
				default:
				break;
					
		}
		
	}
}

bool CurrentApp::Update() {
	double elapsed = core->getElapsed();

	if(player.levelPos == level->getLevelSize() - 1)
	{
		timer.stop();
		
		int timeBonusPoints = 0;
		if(timer.getTimeInSeconds() <= 107.0) timeBonusPoints += 1000;
		else if(timer.getTimeInSeconds() <= 111.0) timeBonusPoints += 500;
		else if(timer.getTimeInSeconds() <= 116.0) timeBonusPoints += 250;
		
		//winner label
		ScreenLabel * winner = new ScreenLabel("Congratulations!", 50);
		winner->setPosition(120,140);
		hud->addChild(winner);
		//time bonus
		ScreenLabel * timebonus = new ScreenLabel("Time Bonus: ", 16);
		timebonus->setPosition(220,200);
		hud->addChild(timebonus);
		ScreenLabel * timebonusDisp = new ScreenLabel(String::IntToString(timeBonusPoints), 16);
		timebonusDisp->setPosition(330,200);
		hud->addChild(timebonusDisp);		
		//coin bonus
		ScreenLabel * coinbonus = new ScreenLabel("Coin Bonus: ", 16);
		coinbonus->setPosition(220,220);
		hud->addChild(coinbonus);
		ScreenLabel * coinbonusDisp = new ScreenLabel(String::IntToString(player.coins * 100), 16);
		coinbonusDisp->setPosition(330,220);
		hud->addChild(coinbonusDisp);		
		//total score
		ScreenLabel * score = new ScreenLabel("Total Score: ", 16);
		score->setPosition(220,240);
		hud->addChild(score);
		ScreenLabel * scoreDisp = new ScreenLabel(String::IntToString(player.coins*100 + timeBonusPoints), 16);
		scoreDisp->setPosition(330,240);
		hud->addChild(scoreDisp);
				
		Vector3 winPos = level->getLevel(level->getLevelSize() - 1)->light->getPosition();
		Vector3 winDir = winPos - player.getPosition();
		winDir.Normalize();
		player.obj->Translate(winDir);
	}
	else
	{
		level->Update(elapsed, player);
		timer.Update(elapsed);
		player.Update(elapsed, keyboard);
		coins_hud->setText("Coins: "+ String::IntToString(player.coins));
		time_hud->setText("Time: " + timer.getTime());
	}
    return core->updateAndRender();
}
