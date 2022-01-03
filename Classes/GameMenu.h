
#include "cocos2d.h"
#include "Game.hpp"
using namespace cocos2d;
class GameMenu : public Layer
{
public:

    // we return the class instance pointer
    static Scene* createScene();
  
    // Method 'init' in cocos2d-x returns bool 
    virtual bool init();
    MenuItemImage* _button;
    // implement the "static create()" method manually
    CREATE_FUNC(GameMenu);

    Sprite* mySprite;

    void GameMenu::level2(Ref* pSender);

    void GameMenu::level3(Ref* pSender);

    void Play(Ref* pSender);

    void Levels(Ref* pSender); 

    void GameMenu::unlock(Ref* pSender);
  
    void Exit(Ref* pSender);

    bool ismute;
    void StopMusic(Ref* pSender);

    void Goback(Ref* pSender);
     
};
