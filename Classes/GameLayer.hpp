//
//  GameLayer.hpp
//  GlowHockey
//
//  Created by Naushad on 05/03/18.
//
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include <stdio.h>
#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <Box2D/Box2D.h>
using namespace cocos2d;
using namespace std;
using namespace ui;
class GameLayer : public Layer {
public:
    static Layer* createLayer();
    virtual bool init();
    void onEnter();
    void onExit();
    void createUI();
    void createScreenBorder();
    void createScreenBoundry();
    void setPhysicsWorld(PhysicsWorld* world);
    void createEdge(Vec2 begining_position, Vec2 ending_position);
    Sprite* createSprite(string Strikername, Vec2 position );
    void addStrikerSprite();
    void middleCircle();
    void middleLine();
    void lowerCircle();
    void upperCircle();
    void scoreLabel();
     void addBall();
    void physicsContactListener();
    bool onContactBeginCallback(PhysicsContact& contact);
    bool onContactPreSolveback(PhysicsContact& contact);
    bool onContactPostSolveCallback(PhysicsContact& contact);
    bool onContactSeprateCallback(PhysicsContact& contact);
    Label* createLabel(string label, Vec2 position);
    void  simulationSpeedUpdate();
    void updateTimer(float delta);
    void updateScore();
    void redmouseJoint();
    void greenmouseJoint();
    
    CREATE_FUNC(GameLayer);
    
private:
    PhysicsWorld* physics_world;
    int upper_player_score = 0;
    int lower_player_score = 0;
    Touch* userTouch;
    Sprite* touched_Striker;
    b2MouseJointDef* redmousejpointdef;
    b2MouseJointDef* greenmouseJointdef;
    
};
#endif /* GameLayer_hpp */
