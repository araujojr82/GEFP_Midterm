#include "cFactory_Imp.h"
#include "cGarbage.h"

#include "cGameObject.h"
#include <vector>
#include <glm/glm.hpp>

extern std::vector< cGameObject* >  g_vecGameObjects;

// A "factory" method
iGameObject* cFactory_Imp::CreateObject(std::string objType)
{
    iGameObject* pTheObject = NULL;	// or 0, or nullptr

	//if( objType == "basic" )
	//{
	//	pTheObject = new cGarbage();		// Abstract Factory
	//	this->AssembleObject( pTheObject, objType );
	//}
	if( objType == "fighter" )
	{
		pTheObject = new cGarbage();
		cGameObject* pTempGO = new cGameObject();
		pTempGO->scale = 2.0f;
		pTempGO->diffuseColour = glm::vec4( 0.5f, 0.5f, 0.5f, 1.0f );
		pTempGO->meshName = "fighter";
		pTempGO->typeOfObject = eTypeOfObject::UNKNOWN;
		pTempGO->bIsUpdatedInPhysics = true;
		//pTempGO->bIsWireFrame = true;
		::g_vecGameObjects.push_back( pTempGO );
		cGarbage* pS = ( cGarbage* )pTheObject;
		pS->pMesh = pTempGO;
		this->AssembleObject( pTheObject, objType );
	}
 //   else if (objType == "fighter2")
 //   {
 //       pTheObject = new cEvilShip();
 //       cGameObject* pTempGO = new cGameObject();
 //       pTempGO->scale = 2.0f;
 //       pTempGO->diffuseColour = glm::vec4(0.3f, 0.3f, 0.4f, 1.0f);
 //       pTempGO->meshName = "fighter";
 //       pTempGO->typeOfObject = eTypeOfObject::UNKNOWN;
 //       pTempGO->bIsUpdatedInPhysics = true;
 //       //pTempGO->bIsWireFrame = true;
 //       ::g_vecGameObjects.push_back(pTempGO);
 //       cEvilShip* pES = ( cEvilShip*)pTheObject;
 //       pES->pMesh = pTempGO;
 //       this->AssembleObject(pTheObject, objType);
 //   }
	//else if( objType == "cell" )
	//{
	//	pTheObject = new cCell();
	//	cGameObject* pTempGO = new cGameObject();
	//	pTempGO->scale = 1.0f;
	//	pTempGO->diffuseColour = glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f );
	//	pTempGO->meshName = "bloodcell";
	//	pTempGO->typeOfObject = eTypeOfObject::UNKNOWN;
	//	pTempGO->bIsUpdatedInPhysics = true;
	//	//pTempGO->bIsWireFrame = true;

	//	::g_vecGameObjects.push_back( pTempGO );
	//	cCell* pS = ( cCell* )pTheObject;
	//	pS->pMesh = pTempGO;
	//	this->AssembleObject( pTheObject, objType );
	//}
	//else if( objType == "virus" )
	//{
	//	pTheObject = new cVirus();
	//	cGameObject* pTempGO = new cGameObject();
	//	pTempGO->scale = 1.0f;
	//	pTempGO->diffuseColour = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f );
	//	pTempGO->meshName = "virus";
	//	pTempGO->typeOfObject = eTypeOfObject::UNKNOWN;
	//	pTempGO->bIsUpdatedInPhysics = true;
	//	//pTempGO->bIsWireFrame = true;

	//	::g_vecGameObjects.push_back( pTempGO );
	//	cVirus* pS = ( cVirus* )pTheObject;
	//	pS->pMesh = pTempGO;
	//	this->AssembleObject( pTheObject, objType );
	//}
	//else if( objType == "bacteria" )
	//{
	//	pTheObject = new cBacteria();
	//	cGameObject* pTempGO = new cGameObject();
	//	pTempGO->scale = 1.0f;
	//	pTempGO->diffuseColour = glm::vec4( 0.0f, 1.0f, 1.0f, 1.0f );
	//	pTempGO->meshName = "bacteria1";
	//	pTempGO->typeOfObject = eTypeOfObject::UNKNOWN;
	//	pTempGO->bIsUpdatedInPhysics = true;
	//	//pTempGO->bIsWireFrame = true;

	//	::g_vecGameObjects.push_back( pTempGO );
	//	cBacteria* pS = ( cBacteria* )pTheObject;
	//	pS->pMesh = pTempGO;
	//	this->AssembleObject( pTheObject, objType );
	//}

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
 //   if( objType == "fighter" )
	//{	// Assemble or build the specifics of that object
	//	// It's got one Laser Gun

	//	cGarbage* pShip = ( cGarbage* )pTheObject;	// not iShip
	//	pShip->pMyLaser = new cLaserGun();
	//}
	//else if( objType == "fighter2" )
	//{	// Assemble or build the specifics of that object
	//	// It's got one Thruster

	//	cEvilShip* pEvilShip = ( cEvilShip* )pTheObject;	// not iShip
	//	pEvilShip->pMyThruster = new cThruster();
	//}
	return;
}


// Mediator things
//// These are "Mediator" sort of methods
//iShip* FindShipByID( unsigned int uniqueID );
//iShip* FindShipByName( std::string name );

void cFactory_Imp::UpdateAllObjects(double timestep)
{
    // **************************************************
    // Ship behaviour update step
    for (int index = 0; index != this->vec_pObjects.size(); index++)
    {
        iGameObject* pCurObj = this->vec_pObjects[index];

        //if( strncmp( pCurObj->getName().c_str(), "virus", 5 ) == 0 )
        //{ // It's a virus!
        //pCurObj->moveTo( FindClosestObjByType( "cell", pCurObj->GetPosition() )->GetPosition() );
        //}
        pCurObj->update();


        // For "fly around" (or anything tied with the physics),
        //	you might want to use the physics updater
        //pCurObj->FlyAround();
        // TODO: Any other behaviour we want 

    }//for ( int index = 0;

    return;
}

std::vector<std::string> cFactory_Imp::Mediate( std::string objType, std::string targetObj, std::vector<std::string> parameters)
{
	iGameObject* pCurrentObj = this->FindObjByName( targetObj );
	std::vector<std::string> vecResult;

	if( parameters[0] == "FindClosestObjByType" )
	{
		iGameObject* theGO =
			this->FindClosestObjByType( parameters[1],
				glm::vec3( strtof( parameters[2].c_str(), 0 ),
					strtof( parameters[3].c_str(), 0 ),
					strtof( parameters[4].c_str(), 0 ) ) );

		glm::vec3 theGOPos = theGO->GetPosition();

		vecResult.push_back( std::to_string( theGOPos.x ) );
		vecResult.push_back( std::to_string( theGOPos.y ) );
		vecResult.push_back( std::to_string( theGOPos.z ) );
		
		//if( objType == "virus" )
		//{
		//	cVirus* theVirus = ( cVirus* )pCurrentObj;
		//	theVirus->attackCell( theGO->getName(), theGOPos );
		//}

		//if( objType == "bacteria" )
		//{
		//	cBacteria* theBacteria = ( cBacteria* )pCurrentObj;
		//	theBacteria->attackShip( theGO->getName(), theGOPos );
		//}

		return vecResult;
	}

	return parameters;
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
        if (pCurrentObj->getName() == name)
        {
            return pCurrentObj;
        }
    }
    return NULL;
}

iGameObject* cFactory_Imp::FindClosestObjByType(std::string objType, glm::vec3 fromPos)
{
    float distance = 1000.0f;
	float tempDist = 0.0f;
	iGameObject* nearestObj;
	glm::vec3 targetPos;

	//Set first object to avoid null object
	for( int index = 0; index != this->vec_pObjects.size(); index++ )
	{
		nearestObj = this->vec_pObjects[index];
		if( strncmp( nearestObj->getName().c_str(), objType.c_str(), 4 ) == 0 )
		{
			exit;
		}
	}

	//Find the actual nearest cell
	for( int index = 0; index != this->vec_pObjects.size(); index++ )
	{
		iGameObject* pCurrentObj = this->vec_pObjects[index];
		if( strncmp( pCurrentObj->getName().c_str(), objType.c_str(), 4 ) == 0 )
		{	// Only compare distance to objects of target type

			targetPos = pCurrentObj->GetPosition();
			tempDist = sqrt( pow( targetPos.x - fromPos.x, 2 ) + pow( targetPos.y - fromPos.y, 2 ) );
			if( tempDist <= distance )
			{
				distance = tempDist;
				nearestObj = pCurrentObj;
			}
		}
	}
	return nearestObj;
}