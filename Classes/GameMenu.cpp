#pragma once
#include "GameMenu.h" 
#include "Game.hpp"
#include "SimpleAudioEngine.h"

Game* prepareGame();
 
using namespace cocos2d;

USING_NS_CC;
Scene* GameMenu::createScene()
{
    auto scene = Scene::create();

    Game* game = prepareGame();
    auto layer = GameMenu::create();
     
    scene->addChild(layer);
     
    return scene;
}
    bool GameMenu::init()
    { 
        if (!Layer::init())
        {
            return false;
        }

        bool ismute=false;

        Size visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();

        mySprite = Sprite::create("background.jpg");
        mySprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
        mySprite->setScale(2);

        this->addChild(mySprite);

        auto menu_item_1 = MenuItemImage::create("menu_Icon/start icon.png", " ", CC_CALLBACK_1(GameMenu::Play, this));
        menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 2.7));
        menu_item_1->setScale(Director::getInstance()->getWinSize().width * 0.2 / menu_item_1->getContentSize().width);

        auto menu_item_2 = MenuItemImage::create("menu_Icon/level icon.png", "  ", CC_CALLBACK_1(GameMenu::Levels, this));
        menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 1.8));
        menu_item_2->setScale(Director::getInstance()->getWinSize().width * 0.2 / menu_item_1->getContentSize().width);

        auto menu_item_3 = MenuItemImage::create("menu_Icon/exit icon.png", " ", CC_CALLBACK_1(GameMenu::Exit, this));
        menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 0.8));
        menu_item_3->setScale(Director::getInstance()->getWinSize().width * 0.2 / menu_item_1->getContentSize().width);

        auto menu_item_4 = MenuItemImage::create("menu_Icon/roller logo.png", " ", CC_CALLBACK_1(GameMenu::Goback, this));
        menu_item_4->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 4));
        menu_item_4->setScale(Director::getInstance()->getWinSize().width * 0.3 / menu_item_1->getContentSize().width);

        MenuItemImage* button = MenuItemImage::create("menu_Icon/music icon.png ", " " , CC_CALLBACK_1(GameMenu::StopMusic, this));
        this->_button = button;
        button->setScale(Director::getInstance()->getVisibleSize().width * 0.05 / button->getContentSize().width);
        GameMenu::_button->setPosition(Point(visibleSize.width / 1.3, (visibleSize.height / 14))); 
   
        auto* menu = Menu::create(menu_item_4, menu_item_1, menu_item_2, menu_item_3  ,button, NULL); 
        menu->setPosition(Point(0, 0));
        this->addChild(menu);

    
       //   CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music.mp3");

      //     CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music.mp3", true);
         
 
      //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound.mp3");
 
      // CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound.mp3");


         ParticleSystemQuad *particle = ParticleSystemQuad::create();
         particle->initWithFile("animation/particle_texture5.plist");
         particle->setSourcePosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2)));
         // particle->setSourcePosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2) ));
          
          this->addChild(particle);

          return true;
    }
   
    void GameMenu::Play(Ref * pSender)
    {
        Scene* scene = Game::createScene();
        
        Director::getInstance()->pushScene(scene);
    }

    void GameMenu::level2 (Ref* pSender)
    {
        Game::_gameSingleton->selectLevel(1);
        auto scene = Game::createScene();
        Director::getInstance()->pushScene(scene);
    }
    void GameMenu::level3(Ref* pSender) {
        Game::_gameSingleton->selectLevel(2);
        auto scene = Game::createScene();
        Director::getInstance()->pushScene(scene);
    }
    void GameMenu::Levels(Ref * pSender)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();

        mySprite = Sprite::create("level_Icon/empty level.png");
        mySprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
        mySprite->setScale(Director::getInstance()->getWinSize().width * 0.65 / mySprite->getContentSize().width);
        this->addChild(mySprite);
         
        auto menu_item_1 = MenuItemImage::create("level_Icon/level1 icon.png", " ", CC_CALLBACK_1(GameMenu::Play, this));
        menu_item_1->setPosition(Point(visibleSize.width / 2.9, (visibleSize.height / 1.5)));//1
        menu_item_1->setScale(Director::getInstance()->getWinSize().width * 0.1 / menu_item_1->getContentSize().width);

        auto menu_item_2 = MenuItemImage::create("level_Icon/level2 icon.png", " ", CC_CALLBACK_1(GameMenu::level2, this));
        menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.5)));//2
        menu_item_2->setScale(Director::getInstance()->getWinSize().width * 0.1 / menu_item_1->getContentSize().width);
         
        auto menu_item_3 = MenuItemImage::create("level_Icon/level3 icon.png", " ", CC_CALLBACK_1(GameMenu::level3, this));
        menu_item_3->setPosition(Point(visibleSize.width / 1.55, (visibleSize.height / 1.5)));//3
        menu_item_3->setScale(Director::getInstance()->getWinSize().width * 0.1 / menu_item_1->getContentSize().width);

        auto menu_item_4 = MenuItemImage::create("level_Icon/level4 icon.png", " ", CC_CALLBACK_1(GameMenu::unlock, this));
        menu_item_4->setPosition(Point(visibleSize.width / 2.9, (visibleSize.height / 2.3)));//4
        menu_item_4->setScale(Director::getInstance()->getWinSize().width * 0.1 / menu_item_1->getContentSize().width);
       
        auto menu_item_5 = MenuItemImage::create("level_Icon/level5 icon.png", " ", CC_CALLBACK_1(GameMenu::unlock, this));
        menu_item_5->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2.3)));//5
        menu_item_5->setScale(Director::getInstance()->getWinSize().width * 0.1 / menu_item_1->getContentSize().width);

        auto menu_item_6 = MenuItemImage::create("level_Icon/level6 icon.png", " ", CC_CALLBACK_1(GameMenu::unlock, this));
        menu_item_6->setPosition(Point(visibleSize.width / 1.55, (visibleSize.height / 2.3)));//6
        menu_item_6->setScale(Director::getInstance()->getWinSize().width * 0.1 / menu_item_1->getContentSize().width);

        auto menu_item_7 = MenuItemImage::create("level_Icon/level7 icon.png", " ", CC_CALLBACK_1(GameMenu::unlock, this));
        menu_item_7->setPosition(Point(visibleSize.width / 2.9, (visibleSize.height / 5.4)));//7
        menu_item_7->setScale(Director::getInstance()->getWinSize().width * 0.1 / menu_item_1->getContentSize().width);

        auto menu_item_8 = MenuItemImage::create("level_Icon/level8 icon.png", " ", CC_CALLBACK_1(GameMenu::unlock, this));
        menu_item_8->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5.4)));//8
        menu_item_8->setScale(Director::getInstance()->getWinSize().width * 0.1 / menu_item_1->getContentSize().width);

        auto menu_item_9 = MenuItemImage::create("level_Icon/level9 icon.png", " ", CC_CALLBACK_1(GameMenu::unlock, this));
        menu_item_9->setPosition(Point(visibleSize.width / 1.55, (visibleSize.height / 5.4)));//9
        menu_item_9->setScale(Director::getInstance()->getWinSize().width * 0.1 / menu_item_1->getContentSize().width);

        auto menu_item_10 = MenuItemImage::create("menu_Icon/home icon.png", " ", CC_CALLBACK_1(GameMenu::Goback, this));
        menu_item_10->setPosition(Point(visibleSize.width / 1.3, (visibleSize.height / 14)));//back
        menu_item_10->setScale(Director::getInstance()->getVisibleSize().width * 0.05 / menu_item_10->getContentSize().width);
         

        auto* menu = Menu::create( menu_item_1, menu_item_2, menu_item_3, menu_item_4, menu_item_5,menu_item_6, menu_item_7, menu_item_8, menu_item_9, menu_item_10, NULL);

        menu->setPosition(Point(0, 0));
      
        this->addChild(menu);
       
    }
 
    void GameMenu::Goback(Ref* pSender) {
          
        Director::getInstance()->replaceScene(TransitionSlideInL::create(0.01, GameMenu::createScene()));
        //pushScene(scene);
    }
 
    void GameMenu::StopMusic(Ref* pSender)
    { 
        if (ismute)
        {
            ismute = false;
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music.mp3");
            this->_button->setNormalImage(Sprite::create("music icon.png")); 
        }
        else
        { 
            ismute = true;
            CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
            GameMenu::_button->setNormalImage(Sprite::create("muted music icon.png"));
        }
    }
 
    void GameMenu::Exit(Ref * pSender)
    {
        Director::getInstance()->end();

    }

    void GameMenu::unlock(Ref* pSender)
    {


        Size visibleSize = Director::getInstance()->getVisibleSize();

        Point origin = Director::getInstance()->getVisibleOrigin();
       

        mySprite = Sprite::create("exit icon.png");
        mySprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
        mySprite->setScale(Director::getInstance()->getWinSize().width * 0.3 / mySprite->getContentSize().width);
        this->addChild(mySprite);
/*
        auto label = Label::createWithTTF("Unlock LEVEL!", "fonts/Marker Felt.ttf", 70);
         
        label->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2) ));
        // label->setColor(Color3B(100, 200, 100));
         label->enableGlow(Color4B(0, 0, 0, 255));
         label->enableOutline(Color4B(0, 255, 0, 255), 15);
          
         this->addChild(label, 1); 
*/
         MenuItemImage* button = MenuItemImage::create("music icon.png", " ", CC_CALLBACK_1(GameMenu::Levels, this));
         button->setPosition(Point(visibleSize.width / 1.6  , (visibleSize.height / 2.2)));

         auto* menu = Menu::create( button, NULL);

         menu->setPosition(Point(0, 0));

         this->addChild(menu);
        
    }
  