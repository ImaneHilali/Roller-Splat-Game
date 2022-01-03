#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "cocos2d.h"
#include "Level.hpp"

    
typedef struct              s_gameBlock
{
    cocos2d::Sprite         *blockTile;
    cocos2d::Sprite         *emptyTile;
    cocos2d::Sprite         *shadowTile;
    cocos2d::Sprite         *ballSprite;
    double                  sizeTile;
}                           t_gameBlock;

class Game: public cocos2d::Layer
{
    public:
        static Game*                    _gameSingleton;
        
    private:
        cocos2d::Vec2                   _windowBoundaries;
        cocos2d::Vec2                   _gameBoundaries;
        cocos2d::Vec2                   _drawingIndex;
        std::map<int, Level*>           _levelMapList;
        Level*                          _currentLevel;
        t_gameBlock                     _tileSprite;
        double                          _scaledTile;
        int                             _maxLevelIndex;
        int                             _currentLevelIndex;
        bool                            _ballIsMoving;
        cocos2d::EventDispatcher*       _dispatcher;
    public:
                                        Game(){};
        void                            verticalCheck(double offset);
        void                            horizontalCheck(double offset);
        void                            drawMap();
        void                            drawBall();
        cocos2d::EventListenerKeyboard* onKeyBoardEvent() ;
        void                            onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode,
                                            cocos2d::Event* event);
        cocos2d::Sprite*                chooseSprite(char icon, cocos2d::Vec2 unidMapPosition,
                                            cocos2d::Vec2 screenPosition);
        cocos2d::Vec2                   calculateDrawingIndex();
        cocos2d::Vec2                   wordPosToMap(cocos2d::Vec2 wordPos);
    public:
        virtual bool                    init();
        static cocos2d::Scene           *createScene();
                                        CREATE_FUNC(Game);
                                        Game(Level *levelMap,t_gameBlock gameSprite,
                                            cocos2d::Vec2 windowBoundaries, cocos2d::Vec2 gameBoundaries);
        virtual void                    update(float dt);
        void                            selectLevel(unsigned int index);
        void                            addLevel(Level *levelMap);
                                        ~Game();
        void                            Goback(Ref* pSender);
};

#endif