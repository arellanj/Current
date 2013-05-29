#include "CurrentApp.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {

	core = new SDLCore(view, 640,480,false,false,0,0,120);	  

	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", false);


	CollisionScene *scene = new CollisionScene();
	ScenePrimitive * obj = new ScenePrimitive( ScenePrimitive::TYPE_SPHERE, 0.5, 10,10);
	obj->setPosition(Vector3(0.0, 0.0, 0.0));
	obj->setMaterialByName("CubeMaterial");
	scene->addCollisionChild(obj);

	ScenePrimitive * ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE,10,25);
	ground->setMaterialByName("GroundMaterial");
	ground->setPosition(0,-5,0);
	scene->addEntity(ground);
	
	ScenePrimitive * wall1 = new ScenePrimitive(ScenePrimitive::TYPE_PLANE,10,25);
	wall1->setMaterialByName("GroundMaterial");
	scene->addEntity(wall1);
	
	wall1->Roll(-90);
	wall1->setPosition(-5,0 ,0);


	SceneLight * light = new SceneLight ( SceneLight:: AREA_LIGHT, scene, 33 );
	light->setPosition(0,4,4);
	light->lookAt(Vector3(0,0,0));
	scene->addLight(light);

	scene->getDefaultCamera()->setPosition(0,1,7);
	scene->getDefaultCamera()->lookAt(Vector3(0,0,0));

	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
	
}

HelloPolycodeApp::~HelloPolycodeApp() {

}

void HelloPolycodeApp::HandleEvent(Event *e)
{
	if(e -> getDispatcher() == core->getInput());
	{
		InputEvent * inputEvent = (InputEvent*)e;
		switch(e-> getEventCode())
		{
		}
	}
}

bool HelloPolycodeApp::Update() {
    return core->updateAndRender();
}
