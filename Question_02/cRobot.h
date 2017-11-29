#ifndef _cRobot_HG_
#define _cRobot_HG_

#include "iGameObject.h"

class cGameObject;	// forward declare

class cRobot : public iGameObject
{
public:
	cRobot();
	virtual ~cRobot();		// Make this virtual, too

	virtual void Update( void );
	virtual void Destroy( void );
	virtual bool IsActive( void );

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

	//Robot exclusive methods
	void GatherObject( glm::vec3 targetPosition, std::string targetName );
	void MoveTo( glm::vec3 targetPosition );
	bool IsFull( void );
	void SeekMaterial();
	void CheckStorage();
	void StoreMaterial( std::string materialType, float amount );
	void ConsumeMaterial( std::string materialType, float amount );
	
	void SetCapacity( std::string materialType, float capacity );
	void SetConsumeRate( std::string materialType, float consRate );
	
	float GetCapacity( std::string materialType );
	float GetConsumeRate( std::string materialType );
	float GetStored( std::string materialType );

	cGameObject* pMesh;

private:
	std::string name, type, targetName;

	glm::vec3 targetPosition;
	
	bool isActive, isMoving;

	int consumeRateMultiplier;

	std::string lowestMatStored;
	float lowestPerc;

	float consumeRateAluminum;
	float consumeRateElectronics;
	float consumeRatePlastic;
	float consumeRateSteel;
	float capacityOfAluminum;
	float capacityOfElectronics;
	float capacityOfPlastic;
	float capacityOfSteel;
	float storedAluminum;
	float storedElectronics;
	float storedPlastic;
	float storedSteel;
	float percAluminum;
	float percElectronics;
	float percPlastic;
	float percSteel;

	iMediator* m_pTheMediator;
};

#endif 
