#include "cGarbage.h"
#include <iostream>

cGarbage::cGarbage()
{
	//std::cout << "cGarbage::cGarbage() is called" << std::endl;
	return;
}

cGarbage::~cGarbage()
{
	//std::cout << "cGarbage::~cGarbage() is called" << std::endl;
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

std::string cGarbage::GetName( void )
{
	return this->name;
}

void cGarbage::SetName( std::string newName )
{
	this->name = newName;
	return;
}

std::string cGarbage::GetType( void )
{
	return this->type;
}

void cGarbage::SetType( std::string newType )
{
	this->type = newType;

	if( newType == "aluminum" )
	{
		this->pMesh->meshName = "alum_can";
		this->pMesh->diffuseColour = glm::vec4( 0.8f, 0.8f, 0.8f, 1.0f );	// Light Grey
	}
	else if( newType == "electronics" )
	{
		this->pMesh->meshName = "elect_tv";
		this->pMesh->diffuseColour = glm::vec4( 0.5f, 0.5f, 0.5f, 1.0f );	// Grey
	}
	else if( newType == "plastic" )
	{
		this->pMesh->meshName = "plast_lego";
		this->pMesh->diffuseColour = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f );	// Green
	}
	else if( newType == "steel" )
	{
		this->pMesh->meshName = "steel_can";
		this->pMesh->diffuseColour = glm::vec4( 0.2f, 0.2f, 0.2f, 1.0f );	//Dark Grey
	}

	return;
}

// NOTE: I'm passing iMediator NOT the full factory
void cGarbage::SetMediator( iMediator* pMediator )
{
	this->m_pTheMediator = pMediator;
	return;
}

void cGarbage::Update( void )
{
	return;
}

void cGarbage::Destroy( void )
{
	isActive = false;
	return;
}

bool cGarbage::IsActive( void )
{
	return this->isActive;
}
