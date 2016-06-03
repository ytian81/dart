#ifndef worldsetup_h
#define worldsetup_h


#include "dart/dart.h"

//#define mSTAT  // prompt of the statistics of mCartPole

using namespace dart::dynamics;
using namespace dart::simulation;
using namespace dart::utils;
using namespace dart::common;
using namespace dart::math;
using namespace dart::gui;

SkeletonPtr addCartPole();
void WorldSetup(WorldPtr mWorld);
#endif
