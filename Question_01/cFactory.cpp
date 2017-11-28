#include "cFactory.h"
#include "cFactory_Imp.h"

cFactory* cFactory::getInstance(void)
{
    if (cFactory::m_pTheFactoryInstance == NULL)
    {
        cFactory::m_pTheFactoryInstance = new cFactory();
    }
    // Return the pointer to the instance
    return cFactory::m_pTheFactoryInstance;
}

cFactory* cFactory::m_pTheFactoryInstance = NULL;

 
cFactory::cFactory()
{
    // Create the actual implementation
    this->pImp = new cFactory_Imp();
    return;
}


iGameObject* cFactory::CreateObject( std::string objType )
{
    return this->pImp->CreateObject(objType);
}

void cFactory::AssembleObject( iGameObject* pTheObject, std::string objType )
{
    this->pImp->AssembleObject(pTheObject, objType);
}

void cFactory::UpdateAllObjects( double timestep )
{
    this->pImp->UpdateAllObjects(timestep);
}

std::vector<std::string> cFactory::Mediate( std::string objType, std::string targetObj, std::vector<std::string> parameters )
{
    return this->pImp->Mediate( objType, targetObj, parameters );
}


iGameObject* cFactory::FindObjByID( unsigned int uniqueID )
{
    return this->FindObjByID(uniqueID);
}

iGameObject* cFactory::FindObjByName( std::string name )
{
    return this->pImp->FindObjByName(name);
}

iGameObject* cFactory::FindClosestObjByType( std::string objType, glm::vec3 fromPos )
{
    return this->FindClosestObjByType(objType, fromPos);
}