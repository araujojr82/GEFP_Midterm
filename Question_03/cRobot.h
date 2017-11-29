#ifndef _cRobot_HG_
#define _cRobot_HG_

#include "iGameObject.h"

#include <vector>

class cGameObject;	// forward declare

class cRobot : public iGameObject
{
public:
	cRobot();
	virtual ~cRobot();		// Make this virtual, too

	virtual void Update( double currTime, double timestep );
	virtual void Destroy( void );
	virtual bool IsActive( void );

	virtual void SetPosition( glm::vec3 newPos );
	virtual void SetVelocity( glm::vec3 newVel );
	virtual void SetRotation( glm::vec3 newRot );
	virtual void SetName( std::string newName );
	virtual void SetRandomName( void );
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
	bool IsEmpty( void );
	bool Is50PercFull( void );
	void SeekMaterial();
	void CheckStorage();
	void StoreMaterial( std::string materialType, float amount );
	void ConsumeMaterials( double timestep );
	void ConsumeMaterial( std::string materialType, float amount );
	
	void SetCapacity( std::string materialType, float capacity );
	void SetConsumeRate( std::string materialType, float consRate );
	
	float GetCapacity( std::string materialType );
	float GetConsumeRate( std::string materialType );
	float GetStored( std::string materialType );

	cGameObject* pMesh;

	struct matPercAmount
	{
		float percAmount;
		std::string materialType;		

		matPercAmount( float k, const std::string& s ) : percAmount( k ), materialType( s ) {}

		bool operator < ( const matPercAmount& str ) const
		{
			return ( percAmount < str.percAmount );
		}
	};

private:
	std::string name, type, targetName;

	glm::vec3 targetPosition;
	
	bool isActive, isMoving;

	double firstEmpty;
	double lastPrint;

	int consumeRateMultiplier;

	std::string lowestMatStored;

	std::vector <matPercAmount> lowestMaterials;

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
