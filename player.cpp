#include "player.h"

Player::Player( ScenePrimitive * obj)
	:obj(obj), cam(NULL), spotlight(NULL), coins(0)
{
	vel = Vector3(0,0,0);
	accl = Vector3(0,0,-1);
	levelPos = -1;
	maxSpeed = 40;
}

void Player::Load(Scene* scene)
{
	cam = scene->getDefaultCamera();
	cam -> setPosition(Vector3(1,2,17));
	//cam -> setPosition(Vector3(15,15,15));
	//cam -> setPosition(Vector3(-70,0,0));
	cam -> lookAt(obj->getPosition());
	spotlight = new SceneLight(SceneLight::SPOT_LIGHT, scene, 33, .2, .5, .05);
	spotlight->setSpotlightProperties(20,6);
	scene->addLight(spotlight);

}

void Player::translate(const Number& x, const Number& y, const Number& z)
{
	obj->Translate(x,y,z);
}

void Player::rotate(const Quaternion& q)
{
	Quaternion rotated =q+ obj->getRotationQuat() ; 
	rotated.Normalize();
	obj->setRotationQuat(rotated.w, rotated.x, rotated.y, rotated.z);
}

void Player::Update(Number elapsed)
{

	vel += accl*elapsed;

	accl.z = (vel.z-maxSpeed);
	if(vel.length() > maxSpeed)
	{
	  vel.Normalize();
		vel = vel * maxSpeed;
	}
	//std::cout<<"speed: "<<vel.z<<std::endl;
	obj->Translate(vel*elapsed);
	obj->setYaw(obj->getYaw()+100*elapsed);
	
	//cam-> Translate(0,0, vel.z*elapsed);
	//cam->lookAt(obj->getPosition());
	cam->setPositionZ(obj->getPosition().z + 15);
	spotlight->setPosition( cam -> getPosition() );
	spotlight->lookAt( obj->getPosition() );
}

const Vector3& Player::getPosition()
{
	return obj->getPosition();
}

void Player::setMaxSpeed(double speed)
{
	maxSpeed = speed;
}

void Player::incrCoins()
{
	coins++;
}

