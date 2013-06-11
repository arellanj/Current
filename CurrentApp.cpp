#include "CurrentApp.h"

CurrentApp::CurrentApp(PolycodeView *view) : EventHandler() {

	core = new SDLCore(view, 640,480,false,false,0,0,120);	  

	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", false);

	scene = new CollisionScene();
	level = LevelManager(50, scene);

	// Creating the Player object
	ScenePrimitive * obj = new ScenePrimitive( ScenePrimitive::TYPE_SPHERE, 0.5, 10,10);
	obj->setPosition(Vector3(0.0, 0.0, 0.0));
	obj->setMaterialByName("CubeMaterial");
	scene->addCollisionChild(obj);

	Screen *hud = new Screen();
	keys_pressed = new ScreenLabel("Coins: ",16);
	hud->addChild(keys_pressed);
	a_pressed = new ScreenLabel("a:no", 16);
	a_pressed->setPosition(0,20);
	d_pressed = new ScreenLabel("d:no", 16);
	d_pressed->setPosition(0,40);
	hud->addChild(a_pressed);
	hud->addChild(d_pressed);

	player = Player(obj);

	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
	


	//player.Load(scene, hud);
	//physScene->addPhysicsChild(obj, PhysicsSceneEntity::SHAPE_SPHERE, 1.0);
	player.Load(scene, hud);
	
}

CurrentApp::~CurrentApp() {

}

void CurrentApp::handleEvent(Event *e)
{

	if(e -> getDispatcher() == core->getInput())
	{
		InputEvent * inputEvent = (InputEvent*)e;
		switch(e-> getEventCode())
		{
			case InputEvent::EVENT_KEYDOWN:
				switch(inputEvent->keyCode())
				{
					case KEY_UP:
						player.accl.y = 4;
						break;
					case KEY_DOWN:
						player.accl.y = -4;
						break;
					case KEY_LEFT:
						player.accl.x = -4;
						a_pressed->setText("a:yes");
						break;
					case KEY_RIGHT:
						player.accl.x = 4;
						d_pressed->setText("d:yes");
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
						a_pressed->setText("a:no");
						break;
					case KEY_RIGHT:
						player.accl.x =0;
						d_pressed->setText("d:no");
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
	
	player.Update(elapsed);
	level.Update(elapsed, player);
    return core->updateAndRender();
}
