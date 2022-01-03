#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

/**
 * @brief 
 * 
 */

#include "cocos2d.h"

class Level
{
    public:
        std::vector<char>   unidMap;
        cocos2d::Color3B    tileColor;
        cocos2d::Sprite*    ballSprite;
        cocos2d::Vec2       ballPosition;
        cocos2d::Vec2       mapDimention;

    public:
        Level(std::vector<std::vector<char>> levelMap, cocos2d::Color3B tileColor);
        ~Level();
        Level&  operator=(const Level &LevelInstance);
    public :
        Level(){};
        
};

#endif