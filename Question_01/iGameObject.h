#ifndef _iGameObject_HG_
#define _iGameObject_HG_

// "interface" class:
// - ALL Pure virtual methods
// - no data
// - Make destructor virtual, too

#include <string>
#include <glm/glm.hpp>

#include "iMediator.h"
#include "cGameObject.h"
#include <vector>
#include <iomanip>
#include <sstream>

class iGameObject
{
public:
	//cGarbage();			// no need for c'tor because there's no data
	virtual ~iGameObject()  {};		// Make this virtual, too
								// NOTE: NO data, just function signatures

								// "pure virtual" method (because of the "= 0" at the end
	//virtual void FlyAround( void ) = 0;
	//virtual void ShootWeapons( void ) = 0;
	virtual void moveTo( glm::vec3 targetPosition ) = 0;
	virtual void update( void ) = 0;

	virtual void SetPosition( glm::vec3 newPos ) = 0;
	virtual void SetVelocity( glm::vec3 newVel ) = 0;
	virtual void SetRotation( glm::vec3 newRot ) = 0;
	virtual glm::vec3 GetPosition( void ) = 0;
	//virtual glm::vec3 GetVelocity(glm::vec3 newPos) = 0;
	virtual std::string getName( void ) = 0;
	virtual void setName( std::string newName ) = 0;

	// NOTE: I'm passing iMediator NOT the full factory
	virtual void SetMediator( iMediator* pMediator ) = 0;
};

#endif 
