#include "cFactory.h"

#include <iostream>

int numberOfDumpedItens = 0;

extern float generateRandomNumber( float min, float max );

float distanceSqEucl( float x1, float y1, float x2, float y2 ) {

	int diffX = x1 - x2;
	int diffY = y1 - y2;
	return ( diffX * diffX + diffY * diffY );
}

float direction( float x1, float y1, float x2, float y2, float x3, float y3 ) {

	int d = ( ( x2 - x1 )*( y3 - y1 ) ) - ( ( y2 - y1 )*( x3 - x1 ) );

	return d;
}

bool CheckDistance( glm::vec3 position, glm::vec3 fromPoint, float maxDistance )
{
	float thisDistance = 0.0f;
	thisDistance = glm::distance( position, fromPoint );

	if( thisDistance <= maxDistance ) return true;

	return false;
}

glm::vec3 GetRandomPosition( glm::vec3 fromPoint, float maxDistance )
{	
	glm::vec3 center = glm::vec3( 0.0f );
	glm::vec3 newPosition = glm::vec3( 0.0f );
	bool validPosition = false;

	while( !validPosition )
	{
		newPosition = glm::vec3( generateRandomNumber( -maxDistance, maxDistance ),
								generateRandomNumber( -maxDistance, maxDistance ),
								0.0f );
		validPosition = CheckDistance( newPosition, center, 2000.0f );
	}
	
	return newPosition;
}

void DumpGarbage( cFactory* pFactory, std::vector< iGameObject* > vecObjects )
{	
	std::cout << "Dumping materials..." << std::endl;
	glm::vec3 center = glm::vec3( 0.0f );

	int numberOfalumiObjs = 0;
	int numberOfelectObjs = 0;
	int numberOfplastObjs = 0;
	int numberOfsteelObjs = 0;

	numberOfalumiObjs = generateRandomNumber( 0, 50 );
	numberOfsteelObjs = generateRandomNumber( 0, 25 );
	numberOfelectObjs = generateRandomNumber( 0, 10 );
	numberOfplastObjs = generateRandomNumber( 0, 100 );

	for( int index = 0; index != numberOfalumiObjs; index++ )
	{	// Create aluminum garbage objects
		numberOfDumpedItens += 1;
		iGameObject* pGarbage = pFactory->CreateObject( "garbage" );
		pGarbage->SetName( "garbage" + std::to_string( numberOfDumpedItens ) );
		pGarbage->SetType( "aluminum" );
		pGarbage->SetPosition( GetRandomPosition( center, 2000.0f ) );

		pGarbage->SetRotation( glm::vec3( 0.0f ) );
		vecObjects.push_back( pGarbage );
	}

	for( int index = 0; index != numberOfsteelObjs; index++ )
	{	// Create steel garbage objects
		numberOfDumpedItens += 1;
		iGameObject* pGarbage = pFactory->CreateObject( "garbage" );
		pGarbage->SetName( "garbage" + std::to_string( numberOfDumpedItens ) );
		pGarbage->SetType( "steel" );
		pGarbage->SetPosition( GetRandomPosition( center, 2000.0f ) );

		pGarbage->SetRotation( glm::vec3( 0.0f ) );
		vecObjects.push_back( pGarbage );
	}

	for( int index = 0; index != numberOfelectObjs; index++ )
	{	// Create electronics garbage objects
		numberOfDumpedItens += 1;
		iGameObject* pGarbage = pFactory->CreateObject( "garbage" );
		pGarbage->SetName( "garbage" + std::to_string( numberOfDumpedItens ) );
		pGarbage->SetType( "electronics" );
		pGarbage->SetPosition( GetRandomPosition( center, 2000.0f ) );

		pGarbage->SetRotation( glm::vec3( 0.0f ) );
		vecObjects.push_back( pGarbage );
	}

	for( int index = 0; index != numberOfplastObjs; index++ )
	{	// Create aluminum garbage objects
		numberOfDumpedItens += 1;
		iGameObject* pGarbage = pFactory->CreateObject( "garbage" );
		pGarbage->SetName( "garbage" + std::to_string( numberOfDumpedItens ) );
		pGarbage->SetType( "plastic" );
		pGarbage->SetPosition( GetRandomPosition( center, 2000.0f ) );

		pGarbage->SetRotation( glm::vec3( 0.0f ) );
		vecObjects.push_back( pGarbage );
	}

}

void loadObjectsUsingFactory( cFactory* pFactory, std::vector< iGameObject* > vecObjects )
{
    iGameObject* pRobot = pFactory->CreateObject("robot");    
	pRobot->SetName("R2D2");
	pRobot->SetType( "robot" );
	pRobot->SetPosition( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	pRobot->SetVelocity( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	pRobot->SetRotation( glm::vec3( 0.0f, 0.0f, 0.0f ) );
    vecObjects.push_back( pRobot );
    
 //   // These lines create a new object just by recompiling this object. Uncoment to test!
 //   iGameObject* pSpaceShip2 = pFactory->CreateObject("fighter2");
	//pSpaceShip2->setName( "Player2Ship" );
	//pSpaceShip2->SetPosition( glm::vec3( 4.0f, -4.5f, 0.0f ) );
	//pSpaceShip2->SetVelocity( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	//pSpaceShip2->SetRotation( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	//vecObjects.push_back( pSpaceShip2 );

	//for( int index = 0; index != 5; index++ )
	//{
	//	iGameObject* pVirus = pFactory->CreateObject( "virus" );
	//	pVirus->setName( "virus" + std::to_string( index ) );
	//	pVirus->SetPosition( glm::vec3( generateRandomNumber( -11.0f, 11.0f ), //x
	//									generateRandomNumber( -6.0f, 6.0f ), //y
	//									0.0f ) );				             //z
	//	
	//	pVirus->SetRotation( glm::vec3( generateRandomNumber( -0.02f, 0.02f ),
	//		generateRandomNumber( -0.02f, 0.02f ),
	//		generateRandomNumber( -0.02f, 0.02f ) ) );
	//	vecObjects.push_back( pVirus );
	//}

	//for( int index = 0; index != 2; index++ )
	//{
	//	iGameObject* pBacteria = pFactory->CreateObject( "bacteria" );
	//	pBacteria->setName( "bacteria" + std::to_string( index ) );
	//	pBacteria->SetPosition( glm::vec3( generateRandomNumber( -11.0f, 11.0f ), //x
	//		generateRandomNumber( -6.0f, 6.0f ), //y
	//		0.0f ) );				             //z
	//
	//	pBacteria->SetRotation( glm::vec3( generateRandomNumber( -0.02f, 0.02f ),
	//		generateRandomNumber( -0.02f, 0.02f ),
	//		generateRandomNumber( -0.02f, 0.02f ) ) );
	//	vecObjects.push_back( pBacteria );
	//}

}