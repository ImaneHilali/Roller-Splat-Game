
#include "cocos2d.h"
#include "Game.hpp"
#include "Level.hpp"

#define BLOCK_PATH "gameTextures/blockTextures/block.png"
#define BALL_PATH "gameTextures/ball.png"
#define EDGE_PATH "gameTextures/blockTextures/edge.png"
#define EMPTY_PATH "gameTextures/blockTextures/empty.png"


std::vector< std::vector<char> > level1{
    {'1','1','1','1','1','1'},
    {'1','0','0','0','0','1'},
    {'1','0','1','1','0','1'},
    {'1','0','1','1','0','1'},
    {'1','b','0','0','0','1'},
    {'1','1','1','1','1','1'},
} ;

std::vector< std::vector<char> > level2{
    {'1','1','1','1','1','1'},
    {'1','0','0','0','0','1'},
    {'1','0','1','1','1','1'},
    {'1','0','0','0','0','1'},
    {'1','1','1','1','0','1'},
    {'1','b','0','0','0','1'},
    {'1','1','1','1','1','1'},
} ;

std::vector< std::vector<char> > level3{
    {'1','1','1','1','1','1'},
    {'1','1','1','0','0','1'},
    {'1','1','1','0','0','1'},
    {'1','1','1','0','1','1'},
    {'1','0','0','0','0','1'},
    {'1','0','1','0','0','1'},
    {'1','0','1','0','1','1'},
    {'1','b','1','0','0','1'},
    {'1','1','1','1','1','1'},
} ;

Game* prepareGame()
{
    cocos2d::Sprite* blockTile = new cocos2d::Sprite();
    blockTile->initWithFile(BLOCK_PATH);
    
    cocos2d::Sprite* edgeTile = new cocos2d::Sprite();
    edgeTile->initWithFile(EDGE_PATH);
    
    cocos2d::Sprite* emptyTile = new cocos2d::Sprite();
    emptyTile->initWithFile(EMPTY_PATH);    

    cocos2d::Sprite* ball = new cocos2d::Sprite();
    ball->initWithFile(BALL_PATH);

    t_gameBlock gameBlock = {blockTile, emptyTile, edgeTile, ball, 50.0};

    Level *firstLevel = new Level(level1, cocos2d::Color3B(251, 0, 102));
    Level *secondLevel = new Level(level2, cocos2d::Color3B(36, 71, 244));
    Level *thirdLevel = new Level(level3, cocos2d::Color3B(246, 161, 29));
    // Level *firstLevel = new Level(level1, cocos2d::Color3B(255, 0, 255), cocos2d::Vec2(1,1), cocos2d::Vec2(6, 8));
    // Level *firstLevel = new Level(level1, cocos2d::Color3B(255, 0, 255), cocos2d::Vec2(1,1), cocos2d::Vec2(6, 8));
    
    Game *gameObject = new Game(firstLevel, gameBlock, cocos2d::Vec2(1024, 768), cocos2d::Vec2(800, 400));
    gameObject->addLevel(secondLevel);
    gameObject->addLevel(thirdLevel);

    return gameObject;
}