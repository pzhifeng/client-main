#include "CommandSkill.h"
#include "../views/SceneSkill.h"

USING_NS_CC;
USING_NS_CC_EXT;

//======CommandSkill======

LayerUI* CommandSkill::init(){
    return LayerUI::scene("SceneSkill", SceneSkillLoader::loader());
}


void CommandSkill::parse(LayerUI* layer,const char *data){
    SceneSkill *scene=(SceneSkill*)layer;
    scene->title->setString("SceneSkill OK!");
}

void CommandSkill::success(LayerUI* layer){
	
}