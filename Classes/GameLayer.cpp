//
//  GameLayer.cpp
//  GlowHockey
//
//  Created by Naushad on 05/03/18.
//
//

#include "GameLayer.hpp"
#include "Constant.hpp"
#include <ui/CocosGUI.h>
#include <Box2D/Box2D.h>


using namespace ui;
using namespace std;

#pragma mark - CraeteLayer
Layer* GameLayer::createLayer()
{
    return GameLayer::create();
}

#pragma mark - init
 bool GameLayer::init()
{
    if(!Layer::init()){
        return false;
    }
    return true;
}

#pragma mark - onEnter
void GameLayer::onEnter(){
    Layer::onEnter();
    createUI();
    simulationSpeedUpdate();
    physicsContactListener();
}

#pragma mark - onExit
void GameLayer::onExit(){
    Layer::onExit();
}

#pragma mark- create UI
void GameLayer::createUI()
{
    createScreenBorder();
    createScreenBoundry();
    middleCircle();
    lowerCircle();
    upperCircle();
    middleLine();
    addStrikerSprite();
    addBall();
    scoreLabel();
//    redmouseJoint();
//    greenmouseJoint();
    
}

void GameLayer::createScreenBorder(){
    auto edgebox = PhysicsBody::createEdgeBox(winSize, edgebox_material);
    edgebox->setContactTestBitmask(ball_categoryBitmask);
    edgebox->setCollisionBitmask(Striker_categoryBitmask);
    edgebox->setCategoryBitmask(edge_categorybitMask);
    auto edgenode = Node::create();
    edgenode->setPosition(edgebox_position);
    edgenode->setTag(edgebox_tag);
    edgenode->setPhysicsBody(edgebox);
    this->addChild(edgenode);
    
}
#pragma mark - create_Screen_Boundry
void GameLayer::createScreenBoundry()
{
    Vec2 edgeposition[] = {top_edge_left_begin, top_edge_left_end, top_edge_right_begin, top_edge_right_end, left_lower_edge_begin, left_lower_edge_end, left_upper_edge_begin, left_upper_edge_end, bottom_edge_left_begin, bottom_edge_left_end, bottom_edge_right_begin, bottom_edge_right_end, right_lower_edge_begin, right_lower_edge_end, right_upper_edge_begin, right_upper_edge_end };
    
    for(int index  = 0 ; index < 16 ; index = index + 2)
    {
        createEdge(edgeposition[index], edgeposition[index  + 1 ]);
    }
}



#pragma mark - create_Striker_method

Sprite* GameLayer::createSprite(string spritename, Vec2 position )
{
    auto sprite  = Sprite::create(spritename);
    sprite->setPosition(position);
    auto spritebody = PhysicsBody::createCircle(sprite->getContentSize().height * 0.6, Striker_material, Vec2::ANCHOR_MIDDLE );
    spritebody->setCategoryBitmask(Striker_categoryBitmask);
    spritebody->setCollisionBitmask(ball_categoryBitmask);
    sprite->setPhysicsBody(spritebody);
    return sprite;
    
}

#pragma mark - addStriker
void GameLayer::addStrikerSprite(){
    auto redStriker = createSprite(redStriker_name, redStriker_position);
    redStriker->setTag(redStrikerTag);
    this->addChild(redStriker);
    
    
    auto greenStriker = createSprite(greenStriker_name, greenStriker_position);
    greenStriker->setTag(greenStrikerTag);
    this->addChild(greenStriker);
    
    auto touchlistener  = EventListenerTouchOneByOne::create();
   
    
    //-onTouchBegan touchListener
    touchlistener->onTouchBegan = ([&](Touch* touch, Event* event){
        auto redsprite = (Sprite*)this->getChildByTag(redStrikerTag);
        auto greensprite = (Sprite*)this->getChildByTag(greenStrikerTag);
        auto moveTo = MoveTo::create(0.1, touch->getLocation());
        if((touch->getLocation().x > leftMargin + edge_margin) && (touch->getLocation().x < winSize.width - rightMargin + edge_margin ) &&
           (touch->getLocation().y > downMargin + edge_margin ) && (touch->getLocation().y < winSize.height - topMargin + edge_margin ))
        {
            if((touch->getLocation().y < winSize.height * 0.5))
            {
                redsprite->setPosition(touch->getLocation());
            }
            else
            {
                if(greensprite->getNumberOfRunningActions()==0){
                    greensprite->runAction(moveTo);
                }
                
            }
        }
        
        
        return true;
    });
    
    //--onTouchMoved
    touchlistener->onTouchMoved  = ([&](Touch* touch, Event* event){
        auto redsprite = (Sprite*)this->getChildByTag(redStrikerTag);
        auto greensprite = (Sprite*)this->getChildByTag(greenStrikerTag);
        auto moveTo = MoveTo::create(0.1, touch->getLocation());
        if((touch->getLocation().x > leftMargin + edge_margin ) && (touch->getLocation().x < winSize.width - rightMargin + edge_margin ) &&
           (touch->getLocation().y > downMargin + edge_margin ) && (touch->getLocation().y < winSize.height - topMargin + edge_margin ))
        
        {
            if((touch->getLocation().y < winSize.height * 0.5) && (touch->getStartLocation().y < winSize.height * 0.5))
            {
                redsprite->setPosition(touch->getLocation());
            }
            
            }
            else
            {
                if((touch->getLocation().y < winSize.height  && touch->getLocation().y > winSize.height * 0.5 ) && (touch->getStartLocation().y > winSize.height * 0.5))
        
                    greensprite->setPosition(touch->getLocation());
                
            
            }
        return true;
    });
        //--onTouchEnded
    touchlistener->onTouchEnded  =  ([&](Touch* touch, Event* event){
        return true;
    });
        
        
      //--onTouchCancelled
    touchlistener->onTouchCancelled =  ([&](Touch* touch, Event* event){

        return true;
});
    
    
   this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchlistener, this);
}

#pragma mark - Add Ball
void GameLayer::addBall(){
    auto ball = Sprite::create(ball_name);
    ball->setPosition(ball_position);
    auto ballbody = PhysicsBody::createCircle(ball->getContentSize().height/2, ball_material, Vec2::ANCHOR_MIDDLE);
    ballbody->setVelocity(Vec2(0,0));
    ballbody->setVelocityLimit(400);
    ballbody->setCategoryBitmask(ball_categoryBitmask);
    ballbody->setCollisionBitmask(Striker_categoryBitmask);
    ballbody->setContactTestBitmask(edge_categorybitMask);
     ball->setPhysicsBody(ballbody);
    ball->setTag(ball_tag);
    this->addChild(ball);
    
}
#pragma mark - Physics_world_setting
void GameLayer::setPhysicsWorld( PhysicsWorld* world){
    physics_world = world;
}

#pragma mark - creadeEdge
  void GameLayer::createEdge(Vec2 begining_position, Vec2 Ending_position){
    auto screenBoundry = PhysicsBody::createEdgeSegment(begining_position, Ending_position,  PhysicsMaterial(edgeSegmentMaterial), edge_border);
    auto boundryNode = Node::create();
    boundryNode->setAnchorPoint(Vec2::ZERO);
    boundryNode->setPhysicsBody(screenBoundry);
    this->addChild(boundryNode);
}

#pragma mark - Middle_line_and_circle
void GameLayer::middleCircle()
{
    
    auto largeCircle = Sprite::create(largecircle);
    largeCircle->setPosition(circle_position);
    this->addChild(largeCircle);
    
    auto smallCircle = Sprite::create(smallcircle);
    smallCircle->setPosition(circle_position);
    this->addChild(smallCircle);

    
}
#pragma mark - lower circle
void GameLayer::lowerCircle(){
    auto largeCircle = Sprite::create(largecircle);
    largeCircle->setPosition(lower_circle_position);
    this->addChild(largeCircle);
    
    auto smallCircle = Sprite::create(smallcircle);
    smallCircle->setPosition(lower_circle_position);
    this->addChild(smallCircle);

}

#pragma mark - UpperCircle
void GameLayer::upperCircle(){
    auto largeCircle = Sprite::create(largecircle);
    largeCircle->setPosition(upper_circle_position);
    this->addChild(largeCircle);
    
    auto smallCircle = Sprite::create(smallcircle);
    smallCircle->setPosition(upper_circle_position);
    this->addChild(smallCircle);
    
}

#pragma mark  - middleLine
void GameLayer::middleLine(){
    auto upperline  = Sprite::create(line_name);
    upperline->setPosition(middlelineposition);
    this->addChild(upperline);

}

#pragma mark  - scoreLabel
void GameLayer::scoreLabel(){
    auto lower_player = createLabel("lower_player", player_1_score_position);
    lower_player->setString(std::to_string(lower_player_score));
    this->addChild(lower_player);
    auto upper_player = createLabel("upper_player", player_2_score_position);
    upper_player->setString(std::to_string(upper_player_score));
    this->addChild(upper_player);
    
}
#pragma mark - PhysicsContactListener

void GameLayer::physicsContactListener()
{
    
     auto contactListener = EventListenerPhysicsContact::create();
     contactListener->onContactBegin   = CC_CALLBACK_1(GameLayer::onContactBeginCallback, this);
     contactListener->onContactPreSolve  = CC_CALLBACK_1(GameLayer::onContactPreSolveback, this);
     contactListener->onContactPostSolve  = CC_CALLBACK_1(GameLayer::onContactPostSolveCallback, this);
     contactListener->onContactSeparate  = CC_CALLBACK_1(GameLayer::onContactSeprateCallback, this);
     this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
 }

#pragma mark - Callback functions
bool GameLayer::onContactBeginCallback(PhysicsContact& contact)
{
 
    auto shapeA = contact.getShapeA()->getBody();
    auto shapeB = contact.getShapeB()->getBody();
    if(((shapeA->getCategoryBitmask() & shapeB->getContactTestBitmask()) != 0)  || ((shapeB->getCategoryBitmask() & shapeA->getContactTestBitmask()) != 0) ){
        CCLOG("insertion called");
           updateScore();
    }
    if(((shapeA->getCategoryBitmask() & shapeB->getCollisionBitmask()) == 0)  || ((shapeB->getCategoryBitmask() & shapeA->getCollisionBitmask()) == 0) ){
        
    }
    else{
        CCLOG("collision called");
        if(shapeA->getTag()==ball_tag)
        {
            shapeA->applyImpulse(Vec2(50,50));
        }
        if(shapeB->getTag()==ball_tag){
            shapeB->applyImpulse(Vec2(50,50));
           
        }
    }
    return true;
}


bool GameLayer::onContactPreSolveback(PhysicsContact& contact)
{
    //CCLOG("onContactPreSolveback called");
    return true;
}

bool GameLayer::onContactPostSolveCallback(PhysicsContact& contact)
{
    //CCLOG("onContactPostSolveCallback called");
    return true;
}

bool GameLayer::onContactSeprateCallback(PhysicsContact& contact)
{
    //
    //CCLOG("onContactSeprateCallback called");
    return true;
}
#pragma mark - Create Layer
Label* GameLayer::createLabel(string label, Vec2 position){
    auto scorelabel = Label::createWithTTF(label, font_file, font_size);
    scorelabel->setPosition(position);
    scorelabel->setName(label);
    return scorelabel;
}

#pragma mark - UpdateScore
void GameLayer::updateScore(){
auto ball = getChildByTag(ball_tag);
    
    auto lowerPlayerScore = (Label*)getChildByName("lower_player");
    auto upperPlayerScore = (Label*)getChildByName("upper_player");

   if(ball->getPosition().y > winSize.height)
   {
       CCLOG("  ball->getPosition() %f", ball->getPosition().y);
   lowerPlayerScore->setString(std::to_string(++lower_player_score));
   }
   else
   {
    upperPlayerScore->setString(std::to_string(++upper_player_score));
   }

}


void  GameLayer::simulationSpeedUpdate(){
    physics_world->setSpeed(1);
    //physics_world->setFixedUpdateRate(50);
    
}


void GameLayer::updateTimer(float delta)
{
    
    if(touched_Striker->getPosition() == userTouch->getLocation()){
        touched_Striker->getPhysicsBody()->setVelocity(Vec2::ZERO);
        touched_Striker->getPhysicsBody()->resetForces();
    }
    
}


#pragma mark- joint definition
void GameLayer::redmouseJoint(){
//    
//    redmousejpointdef =  new b2MouseJointDef();
//    redmousejpointdef->bodyA = (b2Body*)((Node*)getChildByTag(edgebox_tag))->getPhysicsBody();
//    redmousejpointdef->bodyB = (b2Body*)((Sprite*)getChildByTag(redStrikerTag))->getPhysicsBody();
//    redmousejpointdef->target.Set(0,0);
//    redmousejpointdef->maxForce  = getChildByTag(redStrikerTag)->getPhysicsBody()->getMass() * 100;
//    redmousejpointdef->frequencyHz = 100;
//     auto jointworld = (b2World*)physics_world;
//    physics_world->addJoint((PhysicsJoint*)jointworld->CreateJoint(redmousejpointdef));
    
}

void GameLayer::greenmouseJoint(){
    
    greenmouseJointdef =  new b2MouseJointDef();
    
    greenmouseJointdef->bodyA = (b2Body*)((Node*)getChildByTag(edgebox_tag)->getPhysicsBody());
    greenmouseJointdef->bodyB = (b2Body*)((Sprite*)getChildByTag(greenStrikerTag));
    greenmouseJointdef->target.Set(0,0);
    greenmouseJointdef->maxForce  = getChildByTag(greenStrikerTag)->getPhysicsBody()->getMass() * 100;
    greenmouseJointdef->frequencyHz = 100;
    auto jointworld = (b2World*)physics_world;
    physics_world->addJoint((PhysicsJoint*)jointworld->CreateJoint(greenmouseJointdef));
}

