#include "CurrentApp.h"

CurrentApp::CurrentApp(PolycodeView *view) : EventHandler() {

	core = new SDLCore(view, 640,480,false,false,0,0,120);	  

	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", false);

	scene = new CollisionScene();
	level = new LevelManager(100, scene);

	// Creating the Player object
	ScenePrimitive * obj = new ScenePrimitive( ScenePrimitive::TYPE_SPHERE, 0.5, 10,10);
	obj->setPosition(Vector3(0.0, 0.0, 0.0));
	obj->setMaterialByName("CubeMaterial");
	scene->addCollisionChild(obj);

	Screen *hud = new Screen();
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
}

void CurrentApp::handleEvent(Event *e)
{

	if(e -> getDispatcher() == core->getInput())
	{
		InputEvent * inputEvent = (InputEvent*)e;
		switch(e->getEventCode())
		{
			case InputEvent::EVENT_KEYDOWN:
				switch(inputEvent->keyCode())
				{
					case KEY_UP:
						player.vel.y = 4;
						break;
					case KEY_DOWN:
						player.vel.y = -4;
						break;
					case KEY_LEFT:
						player.vel.x = -4;
						break;
					case KEY_RIGHT:
						player.vel.x = 4;
						break;
					default:
						break;
								
				}
				break;
			case InputEvent::EVENT_KEYUP:
				switch(inputEvent->keyCode())
				{
					case KEY_UP:
						player.accl.y = 0;
						break;
					case KEY_DOWN:
						player.accl.y = 0;
						break;
					case KEY_LEFT:
						player.accl.x = 0;
						break;
					case KEY_RIGHT:
						player.accl.x =0;
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
	
	timer.Update(elapsed);
	player.Update(elapsed);
	coins_hud->setText("Coins: "+ String::IntToString(player.coins));
	time_hud->setText("Time: " + timer.getTime());
	level->Update(elapsed, player);
	if(player.levelPos == level->getLevelSize() - 1) timer.stop();
    return core->updateAndRender();
}
