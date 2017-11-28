#include "cGarbage.h"
#include <iostream>

cGarbage::cGarbage()
{
	this->size = 1;
	std::cout << "cGarbage::cGarbage() is called" << std::endl;
	return;
}

cGarbage::~cGarbage()
{
	std::cout << "cGarbage::~cGarbage() is called" << std::endl;
	return;
}

//void cGarbage::FlyAround( void )
//{
//	std::cout
//		<< "cGarbage::FlyAround() is called "
//		<< this->size
//		<< std::endl;
//	return;
//}

void cGarbage::ShootWeapons( void )
{
	std::cout << "cGarbage shoots:";
	//this->pMyLaser->Shoot();
	return;
}

void cGarbage::SetPosition( glm::vec3 newPos )
{
	this->pMesh->position = newPos;
	
	//TODO: Set GO
	return;
}

void cGarbage::SetVelocity( glm::vec3 newVel )
{
	//TODO: Set GO
	this->pMesh->vel = newVel;
	return;
}

void cGarbage::SetRotation( glm::vec3 newRot )
{
	this->pMesh->rotation = newRot;
	return;
}

glm::vec3 cGarbage::GetPosition( void )
{
	return this->pMesh->position;
}

std::string cGarbage::getName( void )
{
	return this->name;
}

void cGarbage::setName( std::string newName )
{
	this->name = newName;
	return;
}

// NOTE: I'm passing iMediator NOT the full factory
void cGarbage::SetMediator( iMediator* pMediator )
{
	this->m_pTheMediator = pMediator;
	return;
}

void cGarbage::moveTo( glm::vec3 targetPosition )
{
	return;
}

void cGarbage::update( void )
{
	return;
}