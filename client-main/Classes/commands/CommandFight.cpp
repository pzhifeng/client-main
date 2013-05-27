#include "CommandFight.h"
#include "../views/SceneFight.h"

USING_NS_CC;
USING_NS_CC_EXT;

//======CommandGate======

LayerUI* CommandGate::init(){
    return SceneFight::scene(NULL);
}


void CommandGate::parse(LayerUI* layer,const char *data){
    
}

void CommandGate::success(LayerUI* layer){
	
}

//======CommandPve======

LayerUI* CommandPve::init(){
    return SceneFight::scene(NULL);
}


void CommandPve::parse(LayerUI* layer,const char *data){
    
}

void CommandPve::success(LayerUI* layer){
	
}