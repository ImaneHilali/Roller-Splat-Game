#include "Game.hpp"

void Game::addLevel(Level *levelMap)
{
    Game::_gameSingleton->_maxLevelIndex++;
    Game::_gameSingleton->_levelMapList.insert(std::map<int, Level *>::value_type(Game::_gameSingleton->_maxLevelIndex, levelMap));
}

Game::Game(Level *levelMap,t_gameBlock gameSprite,
                                    cocos2d::Vec2 windowBoundaries, cocos2d::Vec2 gameBoundaries)
{
    Game::_gameSingleton->_maxLevelIndex = -1;
    addLevel(levelMap);
    Game::_gameSingleton->_windowBoundaries = windowBoundaries;
    Game::_gameSingleton->_gameBoundaries = gameBoundaries;
    Game::_gameSingleton->_tileSprite = gameSprite;
    Game::_gameSingleton->_currentLevelIndex = 0;
    Game::_gameSingleton->_ballIsMoving = false;
    Game::_gameSingleton->_currentLevel = Game::_gameSingleton->_levelMapList.at(Game::_gameSingleton->_currentLevelIndex);
    Game::_gameSingleton->_drawingIndex = calculateDrawingIndex();
    Game::_gameSingleton->_dispatcher= new cocos2d::EventDispatcher();
}

void Game::selectLevel(unsigned int levelIndex)
{
    Game::_gameSingleton->_currentLevelIndex = levelIndex;
    Game::_gameSingleton->_currentLevel = Game::_gameSingleton->_levelMapList.at(Game::_gameSingleton->_currentLevelIndex);
}

cocos2d::Sprite* Game::chooseSprite(char icon, cocos2d::Vec2 unidMapPosition, cocos2d::Vec2 screenPosition)
{
    cocos2d::Sprite* blockSprite;
    cocos2d::Sprite* shadowSprite;
    unsigned int    unidIndex;
    double scale;
    blockSprite = cocos2d::Sprite::create();
    if (icon == '1')
        blockSprite = cocos2d::Sprite::createWithTexture(Game::_gameSingleton->_tileSprite.blockTile->getTexture());
    if (icon == '0')
        blockSprite = cocos2d::Sprite::createWithTexture(Game::_gameSingleton->_tileSprite.emptyTile->getTexture());
    scale = Game::_gameSingleton->_scaledTile / Game::_gameSingleton->_tileSprite.sizeTile;
    blockSprite->setPosition(screenPosition);
    blockSprite->setScale(scale);
    unidIndex = ((unidMapPosition.y - 1) * Game::_gameSingleton->_currentLevel->mapDimention.x) + unidMapPosition.x;
    Game::addChild(blockSprite);

    if(unidMapPosition.y && icon == '0' && Game::_gameSingleton->_currentLevel->unidMap[unidIndex] == '1')
    {
        shadowSprite = cocos2d::Sprite::createWithTexture(Game::_gameSingleton->_tileSprite.shadowTile->getTexture());
        shadowSprite->setPosition(screenPosition);
        shadowSprite->setScale(scale);
        shadowSprite->setLocalZOrder(3);
        Game::addChild(shadowSprite);
    }
    return blockSprite; 
}
cocos2d::Vec2  Game::calculateDrawingIndex()
{
    cocos2d::Vec2                   startIndex;

    Game::_gameSingleton->selectLevel(Game::_gameSingleton->_currentLevelIndex);
    Game::_gameSingleton->_scaledTile = floor(Game::_gameSingleton->_gameBoundaries.x / Game::_gameSingleton->_currentLevel->mapDimention.x);
    if (Game::_gameSingleton->_scaledTile > floor(Game::_gameSingleton->_gameBoundaries.y / Game::_gameSingleton->_currentLevel->mapDimention.y))
        Game::_gameSingleton->_scaledTile =  floor(Game::_gameSingleton->_gameBoundaries.y / Game::_gameSingleton->_currentLevel->mapDimention.y);
    startIndex.x = (Game::_gameSingleton->_windowBoundaries.x / 2.0)
        - ((Game::_gameSingleton->_currentLevel->mapDimention.x * Game::_gameSingleton->_scaledTile)  / 2.0);
    startIndex.y = (Game::_gameSingleton->_windowBoundaries.y / 2.0)
        + ((Game::_gameSingleton->_currentLevel->mapDimention.y * Game::_gameSingleton->_scaledTile)  / 2.0);
    startIndex.x += Game::_gameSingleton->_scaledTile / 2.0;
    startIndex.y -= Game::_gameSingleton->_scaledTile / 2.0;
    startIndex.x = floor(startIndex.x);
    startIndex.y = floor(startIndex.y);

    return startIndex;
}



void Game::drawMap()
{
    std::vector<char>::iterator     mapIterator;
    
    cocos2d::Vec2                   drawIndex;
    cocos2d::Vec2                   mapPosition;
    cocos2d::Sprite                 *blockSprite;
     cocos2d::Vec2                   startIndex;

    startIndex = Game::_gameSingleton->_drawingIndex;
    for (std::vector<char>::iterator mapIterator = Game::_gameSingleton->_currentLevel->unidMap.begin();
                mapIterator != Game::_gameSingleton->_currentLevel->unidMap.end(); ++mapIterator)
    {

        mapPosition.x = std::distance(Game::_gameSingleton->_currentLevel->unidMap.begin(), mapIterator)
            % static_cast<int>(Game::_gameSingleton->_currentLevel->mapDimention.x);
        mapPosition.y = floor(std::distance(Game::_gameSingleton->_currentLevel->unidMap.begin(), mapIterator)
            / Game::_gameSingleton->_currentLevel->mapDimention.x);
        
        drawIndex.x = mapPosition.x * Game::_gameSingleton->_scaledTile;
        drawIndex.y = mapPosition.y * Game::_gameSingleton->_scaledTile;
        drawIndex.x = drawIndex.x + startIndex.x;
        drawIndex.y = startIndex.y - drawIndex.y;

        blockSprite = chooseSprite(*mapIterator,mapPosition, drawIndex);
    }
}

Game * Game::_gameSingleton = new Game();


cocos2d::Scene* Game::createScene(){
    cocos2d::Scene* scene = cocos2d::Scene::create();
    Game* layer = Game::create();
    scene->addChild(layer);
    return scene;
}

void Game::verticalCheck(double offset)
{
    int ballPosition;
    int mapWidth;
    int index;

    mapWidth = Game::_gameSingleton->_currentLevel->mapDimention.x;
    ballPosition = Game::_gameSingleton->_currentLevel->ballPosition.x + (Game::_gameSingleton->_currentLevel->ballPosition.y * mapWidth);
    Game::_gameSingleton->_ballIsMoving = true;
    index = 0;
    while(1){
        index += offset;
        if(!((ballPosition + (index * mapWidth)) > 0 && ballPosition + (index * mapWidth) < Game::_gameSingleton->_currentLevel->unidMap.size()))
            break;
        if(!(Game::_gameSingleton->_currentLevel->unidMap[ballPosition + (index * mapWidth)] != '1'))
            break;
    }
    index -= offset;
    cocos2d::MoveBy *nodeAction = cocos2d::MoveBy::create(0.1 * abs(index), cocos2d::Vec2(0, -index * Game::_gameSingleton->_scaledTile));
    cocos2d::EaseBounceOut *easeAction = cocos2d::EaseBounceOut::create(nodeAction);
    auto callback = cocos2d::CallFunc::create([](){
        Game::_gameSingleton->_ballIsMoving = false;;
    });
    auto seq = cocos2d::Sequence::create(easeAction, callback, NULL);
    Game::_gameSingleton->_currentLevel->ballSprite->runAction(seq);
    Game::_gameSingleton->_currentLevel->ballPosition.y += index;   
}



void Game::horizontalCheck(double offset)
{
    int             ballPosition;
    int mapWidth;
    int index;

    mapWidth = Game::_gameSingleton->_currentLevel->mapDimention.x;
    ballPosition = Game::_gameSingleton->_currentLevel->ballPosition.x + (Game::_gameSingleton->_currentLevel->ballPosition.y * mapWidth);
    Game::_gameSingleton->_ballIsMoving = true;
    index = 0;
    while(1){
        index += offset;
        if(!((ballPosition + index) > 0 && ballPosition + index < Game::_gameSingleton->_currentLevel->unidMap.size()))
            break;
        if(Game::_gameSingleton->_currentLevel->unidMap[ballPosition + index] == '1')
            break;
    }
    index -= offset;
    cocos2d::MoveBy *nodeAction = cocos2d::MoveBy::create(0.1 * abs(index), cocos2d::Vec2(index * Game::_gameSingleton->_scaledTile, 0));
    cocos2d::EaseBounceOut *easeAction = cocos2d::EaseBounceOut::create(nodeAction);
    auto callback = cocos2d::CallFunc::create([](){
        Game::_gameSingleton->_ballIsMoving = false;;
    });
    auto seq = cocos2d::Sequence::create(easeAction, callback, NULL);
    Game::_gameSingleton->_currentLevel->ballSprite->runAction(seq);
    Game::_gameSingleton->_currentLevel->ballPosition.x += index;
}


void Game::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if(!Game::_gameSingleton->_ballIsMoving &&(
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW
        || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A))
        horizontalCheck(-1);
    else if(!Game::_gameSingleton->_ballIsMoving &&(
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW
        || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D))
        horizontalCheck(1);
    else if(!Game::_gameSingleton->_ballIsMoving &&(
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW
        || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W))
        verticalCheck(-1);
    else if(!Game::_gameSingleton->_ballIsMoving &&(
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW
        || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S))
        verticalCheck(1);
    else
        return;
}

cocos2d::EventListenerKeyboard* Game::onKeyBoardEvent()
{
    auto listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Game::onKeyPressed, this);
	return listener;
}


void Game::drawBall()
{
    cocos2d::Sprite *ballSprite;
    cocos2d::Vec2   ballPosition;


    Game::_gameSingleton->_currentLevel->ballSprite = new cocos2d::Sprite();
    ballPosition.x = Game::_gameSingleton->_currentLevel->ballPosition.x * Game::_gameSingleton->_scaledTile;
    ballPosition.y = Game::_gameSingleton->_currentLevel->ballPosition.y * Game::_gameSingleton->_scaledTile;
    
    ballPosition.x = ballPosition.x + Game::_gameSingleton->_drawingIndex.x;
    ballPosition.y = Game::_gameSingleton->_drawingIndex.y - ballPosition.y;

    Game::_gameSingleton->_currentLevel->ballSprite = cocos2d::Sprite::createWithTexture(Game::_gameSingleton->_tileSprite.ballSprite->getTexture());

    Game::_gameSingleton->_currentLevel->ballSprite->setPosition(ballPosition);
    Game::_gameSingleton->_currentLevel->ballSprite->setScale(Game::_gameSingleton->_scaledTile / Game::_gameSingleton->_tileSprite.sizeTile);
    Game::_gameSingleton->_currentLevel->ballSprite->setColor(cocos2d::Color3B(Game::_gameSingleton->_currentLevel->tileColor));

    Game::_gameSingleton->_currentLevel->ballSprite->setLocalZOrder(2);
    Game::addChild(Game::_gameSingleton->_currentLevel->ballSprite);
}

cocos2d::Vec2   Game::wordPosToMap(cocos2d::Vec2 wordPos)
{
    cocos2d::Vec2 ballPosition;

    ballPosition = Game::_gameSingleton->_currentLevel->ballSprite->getPosition();
    cocos2d::Vec2 wordBallPosition = ballPosition;
    ballPosition.x -= Game::_gameSingleton->_drawingIndex.x;
    ballPosition.y -= Game::_gameSingleton->_drawingIndex.y;
    ballPosition.y  = abs(ballPosition.y);
    ballPosition.x /= Game::_gameSingleton->_scaledTile;
    ballPosition.y /= Game::_gameSingleton->_scaledTile;
    ballPosition.x = round(ballPosition.x);
    ballPosition.y = round(ballPosition.y);

    return ballPosition;
}

void Game::update(float dt)
{
    if(Game::_gameSingleton->_ballIsMoving)
    {
        int unidMapIndex;
        cocos2d::Vec2 gridBallPosition;
        cocos2d::Vec2 wordBallPosition;

        gridBallPosition = wordPosToMap(Game::_gameSingleton->_currentLevel->ballSprite->getPosition());
        unidMapIndex = gridBallPosition.x + (gridBallPosition.y * Game::_gameSingleton->_currentLevel->mapDimention.x);
        if (Game::_gameSingleton->_currentLevel->unidMap[unidMapIndex] == '0')
        {
            Game::_gameSingleton->_currentLevel->unidMap[unidMapIndex] = 'c';
            auto blockSprite = cocos2d::Sprite::createWithTexture(Game::_gameSingleton->_tileSprite.blockTile->getTexture());
            blockSprite->setColor(cocos2d::Color3B(Game::_gameSingleton->_currentLevel->tileColor));
            wordBallPosition = gridBallPosition * Game::_gameSingleton->_scaledTile;
            wordBallPosition.x = wordBallPosition.x + Game::_gameSingleton->_drawingIndex.x;
            wordBallPosition.y = Game::_gameSingleton->_drawingIndex.y - wordBallPosition.y;

            blockSprite->setPosition(wordBallPosition);
            blockSprite->setScale(Game::_gameSingleton->_scaledTile / Game::_gameSingleton->_tileSprite.sizeTile);
            Game::addChild(blockSprite);
        }
    }
    else
    {
        if(std::find(Game::_gameSingleton->_currentLevel->unidMap.begin(), Game::_gameSingleton->_currentLevel->unidMap.end(), '0') == Game::_gameSingleton->_currentLevel->unidMap.end())
        {
            if(Game::_gameSingleton->_currentLevelIndex + 1 < Game::_gameSingleton->_levelMapList.size())
            {
                Game::selectLevel(Game::_gameSingleton->_currentLevelIndex + 1);
                Game::removeAllChildren();
                Game::_gameSingleton->_drawingIndex = calculateDrawingIndex();
                Game::drawMap();
                Game::drawBall();
            }
        }
    }
}


bool Game::init()
{
    if (!cocos2d::Layer::init())
        return false;
    Game::drawMap();
    Game::drawBall();
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Game::onKeyBoardEvent(), this);
    scheduleUpdate();
     
     cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
     cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

     auto menu_item_1 = cocos2d::MenuItemImage::create("menu_Icon/home icon.png", " ", CC_CALLBACK_1(Game::Goback, this));
     menu_item_1->setPosition(cocos2d::Point(visibleSize.width / 2, (visibleSize.height / 6)));
     menu_item_1->setScale(cocos2d::Director::getInstance()->getVisibleSize().width * 0.05 / menu_item_1->getContentSize().width);

     auto* menu = cocos2d::Menu::create(menu_item_1, NULL);
     menu->setPosition(cocos2d::Point(0, 0));
     this->addChild(menu);

    return true;
}

Game::~Game()
{
}
void Game::Goback(Ref* pSender) {

  cocos2d::Director::getInstance()->popScene();
}