//
//  GameScene.cpp
//  GlowHockey
//
//  Created by Naushad on 05/03/18.
//
//

#include "GameScene.hpp"
#include "GameLayer.hpp"

#pragma mark - create scene
Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
   scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    auto layer = GameLayer::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

#pragma mark - init method
bool GameScene::init(){
    if(!Scene::init()){
        return false;
    }
    return true;
}

#pragma merk - onEnter method

void GameScene::onEnter()
{
    Scene::onEnter();
    
}


#pragma mark -  onExit method
void GameScene::onExit()
{
    Scene::onExit();
}
