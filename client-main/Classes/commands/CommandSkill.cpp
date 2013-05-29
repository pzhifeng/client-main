#include "CommandSkill.h"
#include "../views/SceneSkill.h"

USING_NS_CC;
USING_NS_CC_EXT;

//=========================
LayerUI* CommandSkill::success(const char *data){
    SceneSkill *scene=(SceneSkill*)LayerUI::scene("SceneSkill", SceneSkillLoader::loader());
    
    scene->title->setString("SceneSkill OK!");
    
    return (LayerUI*)scene;
}
