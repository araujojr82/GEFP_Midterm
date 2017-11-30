#include "cFactory_Imp.h"
#include "cGarbage.h"
#include "cRobot.h"

#include "cGameObject.h"
#include <vector>
#include <glm/glm.hpp>

#include <iostream>

extern std::vector< cGameObject* >  g_vecGameObjects;

// A "factory" method
iGameObject* cFactory_Imp::CreateObject(std::string objType)
{
    iGameObject* pTheObject = NULL;	// or 0, or nullptr

	if( objType == "garbage" )
	{
		pTheObject = new cGarbage();
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 10.0f;
		//pTempGO->diffuseColour = glm::vec4( 0.5f, 0.5f, 0.5f, 1.0f );
		//pTempGO->meshName = "fighter";
		pTempGO->typeOfObject = eTypeOfObject::UNKNOWN;
		pTempGO->bIsUpdatedInPhysics = false;
		::g_vecGameObjects.push_back( pTempGO );
		cGarbage* pS = ( cGarbage* )pTheObject;
		pS->pMesh = pTempGO;
		this->AssembleObject( pTheObject, objType );
	}
    else if (objType == "robot")
    {
        pTheObject = new cRobot();
        cGameObject* pTempGO = new cGameObject();
        pTempGO->scale = 20.0f;
        pTempGO->diffuseColour = glm::vec4(0.6f, 0.6f, 1.0f, 1.0f);
        pTempGO->meshName = "robot";
        pTempGO->typeOfObject = eTypeOfObject::UNKNOWN;
        pTempGO->bIsUpdatedInPhysics = true;
        ::g_vecGameObjects.push_back(pTempGO);
		cRobot* pES = ( cRobot* )pTheObject;
        pES->pMesh = pTempGO;
        this->AssembleObject( pTheObject, objType );
    }

	// Save the ship if it's valid
	if( pTheObject != NULL )
	{	// Then it's a valid ship, so save it
		pTheObject->SetMediator( this );
		this->vec_pObjects.push_back( pTheObject );
	}

	return pTheObject;
}


// "builder" design pattern
void cFactory_Imp::AssembleObject(iGameObject* pTheObject, std::string objType)
{
	return;
}

// Mediator things
//// These are "Mediator" sort of methods
//iShip* FindShipByID( unsigned int uniqueID );
//iShip* FindShipByName( std::string name );

void cFactory_Imp::UpdateAllObjects(double currTime, double timestep)
{
	////Count the objects in the World
	//int numRobots = 0,
	//	numAlum = 0,
	//	numElec = 0,
	//	numPlas = 0,
	//	numStee = 0;

	//for( int index = 0; index != this->vec_pObjects.size(); index++ )
	//{
	//	iGameObject* pCurObj = this->vec_pObjects[index];
	//	if( pCurObj->IsActive() )
	//	{
	//		if( pCurObj->GetType() == "robot" ) numRobots += 1;
	//		if( pCurObj->GetType() == "aluminum" ) numAlum += 1;
	//		if( pCurObj->GetType() == "electronics" ) numElec += 1;
	//		if( pCurObj->GetType() == "plastic" ) numPlas += 1;
	//		if( pCurObj->GetType() == "steel" ) numStee += 1;
	//	}
	//}
	//std::cout << "Number of active objects in the world ( R:" << numRobots <<
	//											" A:" << numAlum <<
	//											" E:" << numElec <<
	//											" P:" << numPlas <<
	//											" S:" << numStee << std::endl;

    // **************************************************
    // Ship behaviour update step
    for (int index = 0; index != this->vec_pObjects.size(); index++)
    {
        iGameObject* pCurObj = this->vec_pObjects[index];

		if( pCurObj->GetType() == "robot" )
		{
			if( pCurObj->IsActive() )
				pCurObj->Update( currTime, timestep );
		}

    }//for ( int index = 0;

    return;
}

bool cFactory_Imp::Mediate( iGameObject* theActiveGO, std::string targetObj, std::vector<std::string> parameters)
{

	if( theActiveGO->GetType() == "robot" )
	{
		cRobot* theRobot = ( cRobot* )theActiveGO;

		if( parameters[0] == "FindClosestObjByType" )
		{
			iGameObject* theGO =
				this->FindClosestObjByType( parameters[1],
					glm::vec3( strtof( parameters[2].c_str(), 0 ),
						strtof( parameters[3].c_str(), 0 ),
						strtof( parameters[4].c_str(), 0 ) ) );
			
			if( !theGO == NULL )
			{
				glm::vec3 theGOPos = theGO->GetPosition();
				std::string theGOName = theGO->GetName();

				theRobot->GatherObject( theGOPos, theGOName );
				return true;
			}
			else
			{
				return false;
			}

		}
		else if( parameters[0] == "ConsumeMaterial" )
		{
			cGarbage* theGarbage = ( cGarbage* )this->FindObjByName( parameters[1] );
			if( !theGarbage == NULL )
			{
				theRobot->StoreMaterial( theGarbage->GetType(), theGarbage->GetMass() );
				theGarbage->Destroy();
				return true;
			}
			else return false;
		}
		else if( parameters[0] == "CreateRobot" )
		{
			float tenPercAl, tenPercEl, tenPercPl, tenPercSt;
			//iGameObject* cFactory_Imp::CreateObject( std::string objType )

			cRobot* theNewRobot = ( cRobot* )CreateObject( "robot" );
			if( !theNewRobot == NULL )
			{
				//Check for the container size of the newRobot (THE SON)
				tenPercAl = theNewRobot->GetCapacity( "aluminum" ) * 0.1;
				tenPercEl = theNewRobot->GetCapacity( "electronics" ) * 0.1;
				tenPercPl = theNewRobot->GetCapacity( "plastic" ) * 0.1;
				tenPercSt = theNewRobot->GetCapacity( "steel" ) * 0.1;

				if( ( theRobot->GetStored( "aluminum" ) >= tenPercAl ) &&
					( theRobot->GetStored( "electronics" ) >= tenPercEl ) &&
					( theRobot->GetStored( "plastic" ) >= tenPercPl ) &&
					( theRobot->GetStored( "steel" ) >= tenPercSt ) )
				{ // The Robot (Father) has enough material to create "life" 
					theRobot->ConsumeMaterial( "aluminum", tenPercAl );
					theRobot->ConsumeMaterial( "electronics", tenPercEl );
					theRobot->ConsumeMaterial( "plastic", tenPercPl );
					theRobot->ConsumeMaterial( "steel", tenPercSt );

					std::cout << std::fixed << std::setprecision( 2 ) << theRobot->GetName() <<
						": My storage is -> Al=" << theRobot->GetPercent("aluminum") <<
						" / El=" << theRobot->GetPercent( "electronics" ) <<
						" / Pl=" << theRobot->GetPercent( "plastic" ) <<
						" / St=" << theRobot->GetPercent( "steel" ) << std::endl;

					theNewRobot->StoreMaterial( "aluminum", tenPercAl );
					theNewRobot->StoreMaterial( "electronics", tenPercEl );
					theNewRobot->StoreMaterial( "plastic", tenPercPl );
					theNewRobot->StoreMaterial( "steel", tenPercSt );
					theNewRobot->SetRandomName();
					theNewRobot->SetType( "robot" );
					theNewRobot->SetPosition( theRobot->GetPosition() );
					theNewRobot->SetVelocity( glm::vec3( 0.0f, 0.0f, 0.0f ) );
					theNewRobot->SetRotation( glm::vec3( 0.0f, 0.0f, 0.0f ) );
					vec_pObjects.push_back( theNewRobot );

					std::cout << theRobot->GetName() << ": I have created life! My son will be called " << theNewRobot->GetName() << std::endl;

					return true;
				}
				else
				{ // Not enough material, destroy that empty shell
					theNewRobot->Destroy();
					return false;
				}

			}
			else return false;
		}
	}

	return false;
}


iGameObject* cFactory_Imp::FindObjByID(unsigned int uniqueID)
{
    // TODO: finish this
    return 0;
}

// Returns the ship or NULL(0) if didn't find it
iGameObject* cFactory_Imp::FindObjByName(std::string name)
{
    for (int index = 0; index != this->vec_pObjects.size(); index++)
    {
        iGameObject* pCurrentObj = this->vec_pObjects[index];
        if (pCurrentObj->GetName() == name)
        {
            return pCurrentObj;
        }
    }
    return NULL;
}

iGameObject* cFactory_Imp::FindClosestObjByType(std::string objType, glm::vec3 fromPos)
{
    float distance = 10000.0f;
	float tempDist = 0.0f;
	iGameObject* nearestObj = NULL;
	glm::vec3 targetPos;

	//Set first active object of that type to avoid null object
	for( int index = 0; index != this->vec_pObjects.size(); index++ )
	{
		//nearestObj = this->vec_pObjects[index];
		iGameObject* tempObj = this->vec_pObjects[index];
		if( tempObj->GetType() == objType )
		{	
			if( tempObj->IsActive() )
			{
				nearestObj = tempObj;
				break;
			}
		}
	}

	if( nearestObj != NULL ) //There's at least one object of that type
	{	//Find the actual nearest object
		for( int index = 0; index != this->vec_pObjects.size(); index++ )
		{
			iGameObject* pCurrentObj = this->vec_pObjects[index];
			if( pCurrentObj->GetType() == objType )
			{	// Only compare distance to objects of target type
				if( pCurrentObj->IsActive() )
				{	// Only compare distance with active objects
					targetPos = pCurrentObj->GetPosition();
					//tempDist = sqrt( pow( targetPos.x - fromPos.x, 2 ) + pow( targetPos.y - fromPos.y, 2 ) );
					tempDist = glm::distance( targetPos, fromPos );
					if( tempDist <= distance )
					{
						distance = tempDist;
						nearestObj = pCurrentObj;
					}
				}
			}
		}
		return nearestObj;
	}
	else return NULL;
}