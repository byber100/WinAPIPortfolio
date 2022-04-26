#include "MapLevel.h"
#include "MainMap.h"


// Static Var

// Static Func

// constructor destructor
MapLevel::MapLevel()
{
}

MapLevel::~MapLevel()
{
}

//member Func
void MapLevel::Loading()
{
	CreateActor<MainMap>(0);
}

void MapLevel::Update()
{

}