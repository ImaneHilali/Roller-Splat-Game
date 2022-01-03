#include "Level.hpp"


Level::Level(std::vector<std::vector<char>> levelMap, cocos2d::Color3B tileColor) : tileColor(tileColor)
{
    int mapWidth = levelMap[0].size();
    int mapHeight = levelMap.size();
    this->mapDimention = cocos2d::Vec2(levelMap[0].size(), levelMap.size());

    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            if (levelMap[i][j] == 'b')
                this->ballPosition = cocos2d::Vec2(j, i);
            if (levelMap[i][j] != '0' && levelMap[i][j] != '1')
                levelMap[i][j] = '0';
            this->unidMap.push_back(levelMap[i][j]);
        }
    }
}


Level& Level::operator=(const Level &LevelInstance)
{
    if(this == &LevelInstance)
        return *this;
    this->unidMap = LevelInstance.unidMap;
    this->tileColor = LevelInstance.tileColor;
    this->ballPosition = LevelInstance.ballPosition;
    this->mapDimention = LevelInstance.mapDimention;
    return *this;
}

Level::~Level()
{
}
