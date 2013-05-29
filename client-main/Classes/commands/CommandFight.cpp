#include "CommandFight.h"
#include "../views/SceneFight.h"

USING_NS_CC;
USING_NS_CC_EXT;

//======CommandGate======
LayerUI* CommandGate::success(const char *data){
    return SceneFight::scene(NULL);
}


//======CommandPve======
LayerUI* CommandPve::success(const char *data){
    return SceneFight::scene(NULL);
}
