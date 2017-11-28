#ifndef _cGarbage_HG_
#define _cGarbage_HG_

#include "iGameObject.h"

class cGameObject;	// forward declare

class cGarbage : public iGameObject
{
public:
	cGarbage();
	virtual ~cGarbage();		// Make this virtual, too

	virtual void MoveTo( glm::vec3 targetPosition );
	virtual void Update( void );

	virtual void SetPosition( glm::vec3 newPos );
	virtual void SetVelocity( glm::vec3 newVel );
	virtual void SetRotation( glm::vec3 newRot );
	virtual void SetName( std::string newName );
	virtual void SetType( std::string newType );

	virtual glm::vec3 GetPosition( void );
	virtual std::string GetName( void );
	virtual std::string GetType( void );

	// NOTE: I'm passing iMediator NOT the full factory
	virtual void SetMediator( iMediator* pMediator );

	cGameObject* pMesh;

private:
	std::string name, type;

	iMediator* m_pTheMediator;
};

#endif 
