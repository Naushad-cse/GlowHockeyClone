//
//  GameScene.hpp
//  GlowHockey
//
//  Created by Naushad on 05/03/18.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include <cocos2d.h>
using namespace cocos2d;
using namespace std;
class GameScene  : public Scene
{
public:
    static Scene* createScene();
    virtual bool init();
    void onEnter();
    void onExit();
    CREATE_FUNC(GameScene);
};


#endif /* GameScene_hpp */
