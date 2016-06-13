#include "DCPagent.h"

namespace GPS_NSpace
{

extern hyperparameters mHyperparameters;

DCPagent::DCPagent():agent(true)
{
	rendering = true;
	mHyperparameters.tupleBool.insert(pair<string,bool>("rendering",rendering));

	// setup_conditions, augment some variable to conditions, this method is not necessary since we can setup it in hyperparamters
	// ('x0', 'x0var', 'pos_body_idx', 'pos_body_offset', 'noisy_body_idx', 'noisy_body_var') populate to vector as vector
}

void DCPagent::sample()
{
	cout<<"DCP_agent sample"<<endl;
}

void DCPagent::get_samples()
{
	cout<<"DCP_agent get samples"<<endl;
}

void _setup_world()
{
	WorldPtr mWorld = std::make_shared<World>();
	WorldSetup(mWorld);

	MyWindow window(mWorld);

	mWorld->getSkeleton("mDoubleCartPole")->getDof("Joint_hold_cart")->setPosition((window.mController->x0)(0));
	mWorld->getSkeleton("mDoubleCartPole")->getDof("Joint_cart_pole")->setPosition((window.mController->x0)(1));
	mWorld->getSkeleton("mDoubleCartPole")->getDof("Joint_pole_pole2")->setPosition((window.mController->x0)(2));
	mWorld->getSkeleton("mDoubleCartPole")->getDof("Joint_hold_cart")->setVelocity((window.mController->x0)(3));
	mWorld->getSkeleton("mDoubleCartPole")->getDof("Joint_cart_pole")->setVelocity((window.mController->x0)(4));
	mWorld->getSkeleton("mDoubleCartPole")->getDof("Joint_pole_pole2")->setVelocity((window.mController->x0)(5));
#ifdef mSTAT
	std::cout<<"-----------------------------------------------------------------------------------"<<std::endl;
	std::cout<<"Gravity is "<<mWorld->getGravity().transpose()<<std::endl;
	std::cout<<"-----------------------------------------------------------------------------------"<<std::endl;
#endif

	glutInit(&argc, argv);
	window.initWindow(1024, 768, "Vehicle");
	glutMainLoop();



}


}
