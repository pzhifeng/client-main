#include "CommandFight.h"
#include "../views/SceneFight.h"

//======CommandFightPve======

int CommandFightPve::Head=20100;

LayerUI* CommandFightPve::success(VoObject* vo){
	LayerUI *layer = SceneFight::scene((VoFight*)vo);
	
    return layer;
}

void CommandFightPve::fail(int code,VoObject* vo){
	
}

VoObject* CommandFightPve::parse(const char *data){
    VoFight* vo=new VoFight();
    return vo;
}