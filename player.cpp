#include "player.h"

Player::Player( ScenePrimitive * obj, Camera * cam)
	:obj(obj), cam(cam)
{}

void Player::translate(const Number& x, const Number& y, const Number& z)
{
	dir = Vector3(0,0,0);
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
	Vector3 direction = dir;
	direction.Normalize();
	obj->Translate(direction*elapsed);
	cam->lookAt(obj->getPosition());
}

const Vector3& Player::getPosition()
{
	return obj->getPosition();
}
