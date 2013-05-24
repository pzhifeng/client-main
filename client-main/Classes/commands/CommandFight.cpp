#include "CommandFight.h"
#include "../views/SceneFight.h"

//======CommandPve======

LayerUI* CommandPve::init(){
    return SceneFight::scene(NULL);
}


void CommandPve::parse(LayerUI* layer,const char *data){
    
}

void CommandPve::success(LayerUI* layer){
	
}