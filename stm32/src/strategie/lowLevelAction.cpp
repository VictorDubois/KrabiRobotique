#include "lowLevelAction.h"

LowLevelAction::LowLevelAction(int status) 
{
    this->status = status;
}
virtual LowLevelAction::~LowLevelAction()
{
}
bool LowLevelAction::update() {
	throw "Not yet implemented";
}
