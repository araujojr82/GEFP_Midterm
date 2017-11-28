#ifndef _cFactory_HG_
#define _cFactory_HG_

// "Abstract Factory" design pattern
#include "iGameObject.h"
// Interface class for the "mediator"
#include "iMediator.h" 

#include <string>

// Forward declare to the actual implementation class
class cFactory_Imp;

class cFactory : public iMediator
{
public:

    // Singleton
    static cFactory* getInstance(void);

	// Note: the parameter is a GENERAL TYPE
	// Suggestion: DON'T use an enum
	// String, int, whatever, as long as it's general
	// Returns the interface class type (NOT specific types)
	// (Factory method)
	iGameObject* CreateObject( std::string objType );
	//	std::string GetLastError(void);

	// Builder pattern
	void AssembleObject( iGameObject* pTheObject, std::string objType );

	// These are "Mediator" sort of methods
	// Seen by the main, iShip, etc.
	virtual iGameObject* FindObjByID( unsigned int uniqueID );
	virtual iGameObject* FindObjByName( std::string name );
	virtual iGameObject* FindClosestObjByType( std::string objType, glm::vec3 fromPos );
	virtual std::vector<std::string> Mediate( std::string objType, std::string targetObj, std::vector<std::string> parameters );

	void UpdateAllObjects( double timestep );

private:
    
    // Singleton
    cFactory();    
    static cFactory* m_pTheFactoryInstance;
    
    // Pointer to the actual implementation class
    cFactory_Imp* pImp;

    

};

#endif