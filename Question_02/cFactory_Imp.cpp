#include "cFactory_Imp.h"
#include "cGarbage.h"
#include "cRobot.h"

#include "cGameObject.h"
#include <vector>
#include <glm/glm.hpp>

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
    // **************************************************
    // Ship behaviour update step
    for (int index = 0; index != this->vec_pObjects.size(); index++)
    {
        iGameObject* pCurObj = this->vec_pObjects[index];

		if( pCurObj->GetType() == "robot" )
		{
			pCurObj->Update();
		}

    }//for ( int index = 0;

    return;
}

std::vector<std::string> cFactory_Imp::Mediate( iGameObject* theActiveGO, std::string targetObj, std::vector<std::string> parameters)
{
	//iGameObject* pCurrentObj = this->FindObjByName( targetObj );
	std::vector<std::string> vecResult;

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

				theRobot->GatherObject( theGOPos, theGO->GetName() );

				vecResult.push_back( std::to_string( theGOPos.x ) );
				vecResult.push_back( std::to_string( theGOPos.y ) );
				vecResult.push_back( std::to_string( theGOPos.z ) );

				return vecResult;
			}
		}
		else if( parameters[0] == "ConsumeMaterial" )
		{
			cGarbage* theGarbage = ( cGarbage* )this->FindObjByName( parameters[1] );
			theRobot->StoreMaterial( theGarbage->GetType(), theGarbage->GetMass() );
			theGarbage->Destroy();

			return vecResult;
		}
	}

	return vecResult;
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
    float distance = 2100.0f;
	float tempDist = 0.0f;
	iGameObject* nearestObj = NULL;
	glm::vec3 targetPos;

	//Set first active object of that type to avoid null object
	for( int index = 0; index != this->vec_pObjects.size(); index++ )
	{
		nearestObj = this->vec_pObjects[index];
		if( nearestObj->GetType() == objType )
		{	
			if( nearestObj->IsActive() )
			break;
		}
	}

	//Find the actual nearest cell
	for( int index = 0; index != this->vec_pObjects.size(); index++ )
	{
		iGameObject* pCurrentObj = this->vec_pObjects[index];
		if( pCurrentObj->GetType() == objType )
		{	// Only compare distance to objects of target type

			if( pCurrentObj->IsActive() )
			{	// Only compare distance with active objects
				targetPos = pCurrentObj->GetPosition();
				tempDist = sqrt( pow( targetPos.x - fromPos.x, 2 ) + pow( targetPos.y - fromPos.y, 2 ) );
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