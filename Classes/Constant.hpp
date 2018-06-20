//
//  Constant.hpp
//  GlowHockey
//
//  Created by Naushad on 05/03/18.
//
//

#ifndef Constant_h
#define Constant_h



#define winSize                   Director::getInstance()->getWinSize()
#define leftMargin                winSize.width * 0.08
#define rightMargin               winSize.width * 0.08
#define topMargin                 winSize.height * 0.02
#define downMargin                winSize.height * 0.02
#define gap_between_edge          20
#define edge_margin               20
#define edge_border               16

#define edgebox_material          PhysicsMaterial(1000000000, 1, 1)
#define edgebox_position          winSize.width * 0.5, winSize.height * 0.5
#define edgebox_tag               1000000
//--GameLayer SceneBoundry
#define top_edge_left_begin       Vec2(leftMargin, winSize.height - topMargin)
#define top_edge_left_end         Vec2(winSize.width * 0.30, winSize.height - topMargin)

#define top_edge_right_begin       Vec2(winSize.width * 0.70, winSize.height - topMargin)
#define top_edge_right_end         Vec2(winSize.width - rightMargin , winSize.height - topMargin)

#define left_lower_edge_begin     Vec2(edge_margin, downMargin + edge_margin)
#define left_lower_edge_end       Vec2(edge_margin, winSize.height * 0.5 - gap_between_edge)

#define left_upper_edge_begin     Vec2(edge_margin, winSize.height * 0.5  + gap_between_edge)
#define left_upper_edge_end       Vec2(edge_margin, winSize.height - (topMargin + edge_margin))

#define right_lower_edge_begin     Vec2(winSize.width - edge_margin, downMargin + edge_margin)
#define right_lower_edge_end       Vec2(winSize.width - edge_margin, winSize.height * 0.5 - gap_between_edge)

#define right_upper_edge_begin     Vec2(winSize.width - edge_margin, winSize.height * 0.5  + gap_between_edge)
#define right_upper_edge_end       Vec2(winSize.width - edge_margin, winSize.height - (topMargin + edge_margin))

#define bottom_edge_left_begin     Vec2(leftMargin, topMargin)
#define bottom_edge_left_end       Vec2(winSize.width * 0.30, topMargin)

#define bottom_edge_right_begin    Vec2(winSize.width * 0.70, topMargin)
#define bottom_edge_right_end      Vec2(winSize.width - rightMargin , topMargin)
#define edgeSegmentMaterial         1000000,1,1


#define edge_contactTestBitmask                               0xFFFFFFFF
#define edge_collisionBitmask                                 Striker_categoryBitmask
#define edge_categorybitMask                                  0x01

//addStriker
#define redStriker_name                          "redbutton.png"
#define redStriker_position                     Vec2(winSize.width * 0.5, winSize.height * 0.25)
#define Striker_material                              PhysicsMaterial(10, 1, 0)
#define redStrikerTag                                      1000
#define greenStriker_name                           "greenbutton.png"
#define greenStriker_position                        Vec2(winSize.width * 0.5, winSize.height * 0.75)
#define greenStrikerTag                               2000

#define Striker_contactTestBitmask                     0xFFFFFFFF
#define Striker_collisionBitmask                       ball_categoryBitmask
#define Striker_categoryBitmask                        ball_categoryBitmask

//addball
#define ball_name                                "ball.png"
#define ball_position                            Vec2(winSize.width * 0.5, winSize.height * 0.5)
#define ball_material                            PhysicsMaterial(3, 2, 0)
#define ball_tag                                  3000

#define ball_contactTestBitmask                  0xFFFFFFFF
#define ball_collisionBitmask                    Striker_categoryBitmask
#define ball_categoryBitmask                      0x04

//circle
#define largecircle                               "largecircle.png"
#define smallcircle                              "smallcircle.png"
#define circle_position                       Vec2(winSize/2)
#define lower_circle_position                  winSize.width * 0.5, 0
#define upper_circle_position                    winSize.width * 0.5, winSize.height

//middle
#define line_name                               "middleline.png"
#define middlelineposition                   winSize.width * 0.5, winSize.height * 0.5

//- score label
#define font_file                 "fonts/arial.ttf"
#define font_size                   80
#define player_1_score_position    Vec2(winSize.width * 0.9, winSize.height * 0.45)
#define player_2_score_position    Vec2(winSize.width * 0.9, winSize.height * 0.55)

#endif /* Constant_h */
