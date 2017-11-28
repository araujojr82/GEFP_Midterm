#include "cFactory.h"

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

void loadObjectsUsingFactory(cFactory* pFactory, std::vector< iGameObject* > vecObjects)
{
 //   iGameObject* pSpaceShip = pFactory->CreateObject("fighter");    
 //   pSpaceShip->setName("Player1Ship");
	//pSpaceShip->SetPosition( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	//pSpaceShip->SetVelocity( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	//pSpaceShip->SetRotation( glm::vec3( 0.0f, 0.0f, 0.0f ) );
 //   vecObjects.push_back(pSpaceShip);
 //   
 //   // These lines create a new object just by recompiling this object. Uncoment to test!
 //   iGameObject* pSpaceShip2 = pFactory->CreateObject("fighter2");
	//pSpaceShip2->setName( "Player2Ship" );
	//pSpaceShip2->SetPosition( glm::vec3( 4.0f, -4.5f, 0.0f ) );
	//pSpaceShip2->SetVelocity( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	//pSpaceShip2->SetRotation( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	//vecObjects.push_back( pSpaceShip2 );

	for( int index = 0; index != 100; index++ )
	{
        iGameObject* pGarbage = pFactory->CreateObject("garbage");
		pGarbage->SetName("garbage" + std::to_string(index));
		pGarbage->SetType( "plastic" );
		pGarbage->SetPosition( glm::vec3( generateRandomNumber( -200.0f, 200.0f ),
										  generateRandomNumber( -200.0f, 200.0f ),
										  0.0f ) );								  

		pGarbage->SetRotation( glm::vec3( 0.0f ) );
        vecObjects.push_back( pGarbage );
    }

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