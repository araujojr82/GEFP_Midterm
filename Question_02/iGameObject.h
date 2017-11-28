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

	virtual void Update( void ) = 0;
	virtual void Destroy( void ) = 0;
	virtual bool IsActive( void ) = 0;

	virtual void SetPosition( glm::vec3 newPos ) = 0;
	virtual void SetVelocity( glm::vec3 newVel ) = 0;
	virtual void SetRotation( glm::vec3 newRot ) = 0;
	virtual void SetName( std::string newName ) = 0;
	virtual void SetType( std::string newType ) = 0;
	
	virtual glm::vec3 GetPosition( void ) = 0;
	virtual std::string GetName( void ) = 0;
	virtual std::string GetType( void ) = 0;

	// NOTE: I'm passing iMediator NOT the full factory
	virtual void SetMediator( iMediator* pMediator ) = 0;
};

#endif 
