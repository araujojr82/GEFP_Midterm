#include "cRobot.h"
#include <iostream>

extern float generateRandomNumber( float min, float max );

cRobot::cRobot()
{
	//std::cout << "cRobot::cRobot() is called" << std::endl;
	isActive = true;
	isMoving = false;

	this->SetCapacity( "aluminum", generateRandomNumber( 0.5f, 2.0f ) );
	this->SetCapacity( "steel", generateRandomNumber( 0.5f, 4.5f ) );
	this->SetCapacity( "electronics", generateRandomNumber( 1.0f, 3.0f ) );
	this->SetCapacity( "plastic", generateRandomNumber( 2.0f, 15.0f ) );

	consumeRateMultiplier = 1;
	this->SetConsumeRate( "aluminum", generateRandomNumber( 0.01f, 0.03f ) );
	this->SetConsumeRate( "steel", generateRandomNumber( 0.01f, 0.05f ) );
	this->SetConsumeRate( "electronics", generateRandomNumber( 0.01f, 0.04f ) );
	this->SetConsumeRate( "plastic", generateRandomNumber( 0.05f, 0.12f ) );
	
	//Type			Capacity range	Consumption range
	//Aluminum Can	0.5 to 2.0 kg	0.01 to 0.03 kg / second
	//Steel Can 	0.5 to 4.5 kg	0.01 to 0.05 kg / second
	//Electronics	1.0 to 3.0 kg	0.01 to 0.04 kg / second
	//Plastics		2.0 to 15 kg	0.05 to 0.012 kg / second <-THIS MUST BE A TYPO, I'M CONSIDERING 0.12 as maximum

	storedAluminum = 0.0f;
	storedElectronics = 0.0f;
	storedPlastic = 0.0f;
	storedSteel = 0.0f;
	percAluminum = 0.0f;
	percElectronics = 0.0f;
	percPlastic = 0.0f;
	percSteel = 0.0f;
	lowestPerc = 0.0f;

	lowestMatStored = "aluminum";

	return;
}

cRobot::~cRobot()
{
	//std::cout << "cRobot::~cRobot() is called" << std::endl;
	return;
}

void cRobot::SetPosition( glm::vec3 newPos )
{
	this->pMesh->position = newPos;

	//TODO: Set GO
	return;
}

void cRobot::SetVelocity( glm::vec3 newVel )
{
	//TODO: Set GO
	this->pMesh->vel = newVel;
	return;
}

void cRobot::SetRotation( glm::vec3 newRot )
{
	this->pMesh->rotation = newRot;
	return;
}

glm::vec3 cRobot::GetPosition( void )
{
	return this->pMesh->position;
}

std::string cRobot::GetName( void )
{
	return this->name;
}

void cRobot::SetName( std::string newName )
{
	this->name = newName;
	return;
}

std::string cRobot::GetType( void )
{
	return this->type;
}

void cRobot::SetType( std::string newType )
{
	this->type = newType;
	return;
}

// NOTE: I'm passing iMediator NOT the full factory
void cRobot::SetMediator( iMediator* pMediator )
{
	this->m_pTheMediator = pMediator;
	return;
}

void cRobot::GatherObject( glm::vec3 newTargetPosition, std::string newTargetName )
{	
	float targetDistance = glm::distance( newTargetPosition, this->GetPosition() );

	if( targetDistance <= 5.0f )
	{	// Reach the target - Ask mediator for help to destroy it.
		isMoving = false;

		this->SetVelocity( glm::vec3( 0.0f ) );

		std::vector<std::string> vecParam;
		std::vector<std::string> vecResult;

		vecParam.push_back( "ConsumeMaterial" );
		vecParam.push_back( targetName );

		vecResult = this->m_pTheMediator->Mediate( ( iGameObject* )this, this->GetName(), vecParam );		
		
		targetName = "";
		targetPosition = ( glm::vec3( 0.0f ) );

	}
	else
	{
		isMoving = true;
		targetName = newTargetName;
		targetPosition = newTargetPosition;
		this->MoveTo( targetPosition );
	}

	return;
}

void cRobot::MoveTo( glm::vec3 targetPosition )
{
	float startX, startY, endX, endY;

	startX = this->GetPosition().x;
	startY = this->GetPosition().y;
	endX = targetPosition.x;
	endY = targetPosition.y;

	float distance = sqrt( pow( endX - startX, 2 ) + pow( endY - startY, 2 ) );
	float directionX = ( endX - startX ) / distance;
	float directionY = ( endY - startY ) / distance;

	directionX *= 50.0f;
	directionY *= 50.0f;

	this->SetVelocity( glm::vec3( directionX, directionY, 0.0f ) );

	return;
}

void cRobot::Destroy( void )
{
	isActive = false;
	this->pMesh->isActive = false;
	return;
}

bool cRobot::IsActive( void )
{
	return this->isActive;
}

void cRobot::Update( void )
{
	// Update storage levels information
	this->CheckStorage();

	if( this->IsFull() )
	{
		// TODO implement reproduction
		//this.reproduce();
	}
	else
	{
		// If any material is bellow 90%, try to find some
		if( lowestPerc <= 90.0f )
		{
			this->SeekMaterial();
		}
	}
	return;
}

bool cRobot::IsFull( void )
{
	bool materialFull = true;

	if( percAluminum < 95.0f ) materialFull = false;
	if( percElectronics < 95.0f ) materialFull = false;
	if( percPlastic < 95.0f ) materialFull = false;
	if( percSteel < 95.0f ) materialFull = false;
	
	return materialFull;
}

void cRobot::SeekMaterial()
{
	// I NEED MATERIAL - Mediator help me find some ? (lowestMatStored)
	glm::vec3 thePosition = this->GetPosition();

	std::vector<std::string> vecParam;
	std::vector<std::string> vecResult;

	vecParam.push_back( "FindClosestObjByType" );
	vecParam.push_back( lowestMatStored );

	vecParam.push_back( std::to_string( thePosition.x ) );
	vecParam.push_back( std::to_string( thePosition.y ) );
	vecParam.push_back( std::to_string( thePosition.z ) );

	vecResult = this->m_pTheMediator->Mediate( (iGameObject* )this, this->GetName(), vecParam );

	return;
}

void cRobot::CheckStorage()
{	
	lowestPerc = 100.0f;

	percAluminum = GetStored( "aluminum" ) / GetCapacity( "aluminum" );
	percElectronics = GetStored( "electronics" ) / GetCapacity( "electronics" );
	percPlastic = GetStored( "plastic" ) / GetCapacity( "plastic" );
	percSteel = GetStored( "steel" ) / GetCapacity( "steel" );

	//Start with the last material alphabetically, and backwards
	lowestPerc = percSteel;
	lowestMatStored = "steel";

	if( percPlastic <= lowestPerc )
	{	// If there's less Plastic than Steel...
		lowestPerc = percPlastic;
		lowestMatStored = "plastic";
	}
	if( percElectronics <= lowestPerc )
	{	// If there's less Electronics than whatever...
		lowestPerc = percElectronics;
		lowestMatStored = "electronics" ;
	}
	if( percAluminum <= lowestPerc )
	{	// If there's less Aluminum than whatever...
		lowestPerc = percAluminum;
		lowestMatStored = "aluminum";
	}

	consumeRateMultiplier = 1;

	if( storedAluminum == 0.0f )
		consumeRateMultiplier += 1;
	if( storedElectronics == 0.0f )
		consumeRateMultiplier += 1;
	if( storedPlastic == 0.0f )
		consumeRateMultiplier += 1;
	if( storedSteel == 0.0f )
		consumeRateMultiplier += 1;

	return;
}

void cRobot::StoreMaterial( std::string materialType, float amount )
{
	if( materialType == "aluminum" )
	{
		storedAluminum += amount;
		if( storedAluminum >= capacityOfAluminum ) storedAluminum = capacityOfAluminum;
	}	
	else if( materialType == "electronics" )
	{
		storedElectronics += amount;
		if( storedElectronics >= capacityOfElectronics ) storedAluminum = capacityOfElectronics;
	}
	else if( materialType == "plastic" )
	{
		storedPlastic += amount;
		if( storedPlastic >= capacityOfPlastic ) storedAluminum = capacityOfPlastic;
	}
	else if( materialType == "steel" )
	{
		storedSteel += amount;
		if( storedSteel >= capacityOfSteel ) storedAluminum = capacityOfSteel;
	}
	return;
}

void cRobot::ConsumeMaterial( std::string materialType, float amount )
{
	if( materialType == "aluminum" )
	{
		storedAluminum -= amount;
		if( storedAluminum <= 0.0f ) storedAluminum = 0.0f;
	}
	else if( materialType == "electronics" )
	{
		storedElectronics -= amount;
		if( storedElectronics <= 0.0f ) storedAluminum = 0.0f;
	}
	else if( materialType == "plastic" )
	{
		storedPlastic -= amount;
		if( storedPlastic <= 0.0f ) storedAluminum = 0.0f;
	}
	else if( materialType == "steel" )
	{
		storedSteel -= amount;
		if( storedSteel <= 0.0f ) storedAluminum = 0.0f;
	}
	return;
}

void cRobot::SetCapacity( std::string materialType, float capacity )
{
	if( materialType == "aluminum" )
		capacityOfAluminum = capacity;
	else if( materialType == "electronics" )
		capacityOfElectronics = capacity;
	else if( materialType == "plastic" )
		capacityOfPlastic = capacity;
	else if( materialType == "steel" )
		capacityOfSteel = capacity;
	return;
}

void cRobot::SetConsumeRate( std::string materialType, float consRate )
{
	if( materialType == "aluminum" )
		consumeRateAluminum = consRate;
	else if( materialType == "electronics" )
		consumeRateElectronics = consRate;
	else if( materialType == "plastic" )
		consumeRatePlastic = consRate;
	else if( materialType == "steel" )
		consumeRateSteel = consRate;

	return;
}


float cRobot::GetCapacity( std::string materialType )
{
	if( materialType == "aluminum" )
		return capacityOfAluminum;
	else if( materialType == "electronics" )
		return capacityOfElectronics;
	else if( materialType == "plastic" )
		return capacityOfPlastic;
	else if( materialType == "steel" )
		return capacityOfSteel;

	return NULL;
}

float cRobot::GetConsumeRate( std::string materialType )
{
	if( materialType == "aluminum" )
		return consumeRateAluminum;
	else if( materialType == "electronics" )
		return consumeRateElectronics;
	else if( materialType == "plastic" )
		return consumeRatePlastic;
	else if( materialType == "steel" )
		return consumeRateSteel;

	return NULL;
}

float cRobot::GetStored( std::string materialType )
{
	if( materialType == "aluminum" )
		return storedAluminum;
	else if( materialType == "electronics" )
		return storedElectronics;
	else if( materialType == "plastic" )
		return storedPlastic;
	else if( materialType == "steel" )
		return storedSteel;

	return NULL;
}
