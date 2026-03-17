#include <Geode/Geode.hpp>
#include <Surge/layers/GDSIslandSelectLayer.h>
#include <Surge/layers/IslandNode.h>
#include <Surge/layers/IslandLevel.hpp>

using namespace geode::prelude;

ccColor3B colors2s[] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255}
};
int numColors2s = sizeof(colors2s) / sizeof(colors2s[0]);
int currentColorIndex2s = 0;

GDSIslandSelectLayer* GDSIslandSelectLayer::create(int page) {
    auto ret = new GDSIslandSelectLayer();
    if (ret && ret->init(page)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
};

CCScene* GDSIslandSelectLayer::scene(int page) {
    auto layer = GDSIslandSelectLayer::create(page);
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
}

bool GDSIslandSelectLayer::init(int page) {
    if (!CCLayer::init()) return false;

    setKeypadEnabled(true);
    setTouchEnabled(true);
    setKeyboardEnabled(true);

    auto node = IslandNode::create(1,this);
    auto node2 = IslandNode::create(1, this);
    auto node3 = IslandNode::create(1, this);

    auto GM = GameManager::sharedState();
    auto GLM = GameLevelManager::sharedState();
   
    CCString* path = CCString::createWithFormat("island_%02d.png"_spr, 1);
    CCSprite* sprite = CCSprite::createWithSpriteFrameName(path->getCString());

    CCString* path2 = CCString::createWithFormat("island_%02d.png"_spr, 2);
    CCSprite* sprite2 = CCSprite::createWithSpriteFrameName(path2->getCString());

    CCString* path3 = CCString::createWithFormat("island_%02d.png"_spr, 3);
    CCSprite* sprite3 = CCSprite::createWithSpriteFrameName(path->getCString());

    CCSprite* backSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(backSpr, this, menu_selector(GDSIslandSelectLayer::onClose));

    CCMenu* backMenu = CCMenu::create();
    backMenu->addChild(backBtn);
    addChild(backMenu, 1);

    backMenu->setPosition(ccp(CCDirector::sharedDirector()->getScreenLeft() + 25.f, CCDirector::sharedDirector()->getScreenTop() - 22.f));

    CCSprite* TheAssembly = CCSprite::createWithSpriteFrameName("islandLabel_01_001.png"_spr);

    CCSprite* TheInterface = CCSprite::createWithSpriteFrameName("islandLabel_02_001.png"_spr);

    auto ComingSoon = CCLabelBMFont::create("Coming Soon","bigFont.fnt");

    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();

    m_fWindowWidth = winSize.width;

    CCMenu* dashlandsmenu = CCMenu::create();

    //locked sprites
    CCSprite* level2 = CCSprite::createWithSpriteFrameName("islandLevelBtn_locked_001.png"_spr);
    CCSprite* level3 = CCSprite::createWithSpriteFrameName("islandLevelBtn_locked_001.png"_spr);
    CCSprite* level4 = CCSprite::createWithSpriteFrameName("islandLevelBtn_locked_001.png"_spr);
    CCSprite* level5 = CCSprite::createWithSpriteFrameName("islandLevelBtn_locked_001.png"_spr);
    CCSprite* level6 = CCSprite::createWithSpriteFrameName("islandLevelBtn_locked_001.png"_spr);
    CCSprite* level7 = CCSprite::createWithSpriteFrameName("islandLevelBtn_locked_001.png"_spr);
    CCSprite* level8 = CCSprite::createWithSpriteFrameName("islandLevelBtn_locked_001.png"_spr);
    CCSprite* level9 = CCSprite::createWithSpriteFrameName("islandLevelBtn_locked_001.png"_spr);
    CCSprite* level10 = CCSprite::createWithSpriteFrameName("islandLevelBtn_locked_001.png"_spr);

    //pointers animation 1 (-)
    m_points.level1PathPoint1 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level1PathPoint2 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level1PathPoint3 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level1PathPoint4 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level1PathPoint5 = CCSprite::createWithSpriteFrameName("uiDot_001.png");

    //pointers animation 2 (B)
    m_points.level2PathPoint1 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level2PathPoint2 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level2PathPoint3 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level2PathPoint4 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level2PathPoint5 = CCSprite::createWithSpriteFrameName("uiDot_001.png");

    //pointers animation 3 (M)
    m_points.level3PathPoint1 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level3PathPoint2 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level3PathPoint3 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level3PathPoint4 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level3PathPoint5 = CCSprite::createWithSpriteFrameName("uiDot_001.png");

    //pointers animation 4 (Y)
    m_points.level4PathPoint1 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level4PathPoint2 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level4PathPoint3 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level4PathPoint4 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level4PathPoint5 = CCSprite::createWithSpriteFrameName("uiDot_001.png");

    //pointers animation 5 (F)
    m_points.level5PathPoint1 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level5PathPoint2 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level5PathPoint3 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level5PathPoint4 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level5PathPoint5 = CCSprite::createWithSpriteFrameName("uiDot_001.png");

    //pointers animation 6 (SP)
    m_points.level6PathPoint1 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level6PathPoint2 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level6PathPoint3 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level6PathPoint4 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level6PathPoint5 = CCSprite::createWithSpriteFrameName("uiDot_001.png");

    //pointers animation 7 (S)
    m_points.level7PathPoint1 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level7PathPoint2 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level7PathPoint3 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level7PathPoint4 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level7PathPoint5 = CCSprite::createWithSpriteFrameName("uiDot_001.png");

    //pointers animation 8 (E)
    m_points.level8PathPoint1 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level8PathPoint2 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level8PathPoint3 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level8PathPoint4 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level8PathPoint5 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level8PathPoint6 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level8PathPoint7 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level8PathPoint8 = CCSprite::createWithSpriteFrameName("uiDot_001.png");

    //pointers animation 9 (R)
    m_points.level9PathPoint1 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level9PathPoint2 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level9PathPoint3 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level9PathPoint4 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level9PathPoint5 = CCSprite::createWithSpriteFrameName("uiDot_001.png");

    //pointers animation 10 (MDO)
    m_points.level10PathPoint1 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level10PathPoint2 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level10PathPoint3 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level10PathPoint4 = CCSprite::createWithSpriteFrameName("uiDot_001.png");
    m_points.level10PathPoint5 = CCSprite::createWithSpriteFrameName("uiDot_001.png");

    dashlandsmenu->addChild(m_points.level1PathPoint1);
    dashlandsmenu->addChild(m_points.level1PathPoint2);
    dashlandsmenu->addChild(m_points.level1PathPoint3);
    dashlandsmenu->addChild(m_points.level1PathPoint4);
    dashlandsmenu->addChild(m_points.level1PathPoint5);

    dashlandsmenu->addChild(m_points.level2PathPoint1);
    dashlandsmenu->addChild(m_points.level2PathPoint2);
    dashlandsmenu->addChild(m_points.level2PathPoint3);
    dashlandsmenu->addChild(m_points.level2PathPoint4);
    dashlandsmenu->addChild(m_points.level2PathPoint5);

    dashlandsmenu->addChild(m_points.level3PathPoint1);
    dashlandsmenu->addChild(m_points.level3PathPoint2);
    dashlandsmenu->addChild(m_points.level3PathPoint3);
    dashlandsmenu->addChild(m_points.level3PathPoint4);
    dashlandsmenu->addChild(m_points.level3PathPoint5);

    dashlandsmenu->addChild(m_points.level4PathPoint1);
    dashlandsmenu->addChild(m_points.level4PathPoint2);
    dashlandsmenu->addChild(m_points.level4PathPoint3);
    dashlandsmenu->addChild(m_points.level4PathPoint4);
    dashlandsmenu->addChild(m_points.level4PathPoint5);

    m_iLevels.level1Btn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("islandLevelBtn_001.png"_spr), this, menu_selector(GDSIslandSelectLayer::onIslandLevel));

    m_iLevels.level1Btn->setTag(1);
    m_iLevels.level1Btn->setPosition(-189, -15);

    //LEVEL 1 POINTS
    //point 1
    m_points.level1PathPoint1->setPosition(m_iLevels.level1Btn->getPosition());
    m_points.level1PathPoint1->setPositionX(m_points.level1PathPoint1->getPositionX()+20);
    m_points.level1PathPoint1->setPositionY(-20);
    m_points.level1PathPoint1->setScale(0.5);
    m_points.level1PathPoint1->setScaleX(1);
    //point 2
    m_points.level1PathPoint2->setPosition(m_iLevels.level1Btn->getPosition());
    m_points.level1PathPoint2->setPositionX(m_points.level1PathPoint2->getPositionX()+32);
    m_points.level1PathPoint2->setPositionY(-25);
    m_points.level1PathPoint2->setScale(0.5);
    m_points.level1PathPoint2->setScaleX(1);
    //point 3
    m_points.level1PathPoint3->setPosition(m_iLevels.level1Btn->getPosition());
    m_points.level1PathPoint3->setPositionX(m_points.level1PathPoint3->getPositionX()+50);
    m_points.level1PathPoint3->setPositionY(-22);
    m_points.level1PathPoint3->setScale(0.5);
    m_points.level1PathPoint3->setScaleX(1);
    //point 4
    m_points.level1PathPoint4->setPosition(m_iLevels.level1Btn->getPosition());
    m_points.level1PathPoint4->setPositionX(m_points.level1PathPoint4->getPositionX()+77);
    m_points.level1PathPoint4->setPositionY(-22.5);
    m_points.level1PathPoint4->setScale(0.5);
    m_points.level1PathPoint4->setScaleX(1);
    //point 5
    m_points.level1PathPoint5->setPosition(m_iLevels.level1Btn->getPosition());
    m_points.level1PathPoint5->setPositionX(m_points.level1PathPoint5->getPositionX()+89.7);
    m_points.level1PathPoint5->setPositionY(-26);
    m_points.level1PathPoint5->setScale(0.5);
    m_points.level1PathPoint5->setScaleX(1);
    m_iLevels.level2Btn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("islandLevelBtn_001.png"_spr), this, menu_selector(GDSIslandSelectLayer::onIslandLevel));

    m_iLevels.level2Btn->setTag(2);
    m_iLevels.level2Btn->setPosition(-83, -25);
    m_iLevels.level2Btn->setVisible(false);
    level2->setPosition({ -80, -30 });

    //LEVEL 2 POINTS
    //point 1
    m_points.level2PathPoint1->setPosition(m_iLevels.level2Btn->getPosition());
    m_points.level2PathPoint1->setPositionX(m_points.level2PathPoint1->getPositionX() + 7);
    m_points.level2PathPoint1->setPositionY(-22);
    m_points.level2PathPoint1->setScale(0.5);
    m_points.level2PathPoint1->setScaleX(1);
    //point 2
    m_points.level2PathPoint2->setPosition(m_iLevels.level2Btn->getPosition());
    m_points.level2PathPoint2->setPositionX(m_points.level2PathPoint2->getPositionX() + 13);
    m_points.level2PathPoint2->setPositionY(-15);
    m_points.level2PathPoint2->setScale(0.5);
    m_points.level2PathPoint2->setScaleX(1);
    //point 3
    m_points.level2PathPoint3->setPosition(m_iLevels.level2Btn->getPosition());
    m_points.level2PathPoint3->setPositionX(m_points.level2PathPoint3->getPositionX() + 23);
    m_points.level2PathPoint3->setPositionY(-7);
    m_points.level2PathPoint3->setScale(0.5);
    m_points.level2PathPoint3->setScaleX(1);
    //point 4
    m_points.level2PathPoint4->setPosition(m_iLevels.level2Btn->getPosition());
    m_points.level2PathPoint4->setPositionX(m_points.level2PathPoint4->getPositionX() + 40);
    m_points.level2PathPoint4->setPositionY(2.5);
    m_points.level2PathPoint4->setScale(0.5);
    m_points.level2PathPoint4->setScaleX(1);
    //point 5
    m_points.level2PathPoint5->setPosition(m_iLevels.level2Btn->getPosition());
    m_points.level2PathPoint5->setPositionX(m_points.level2PathPoint5->getPositionX() + 52);
    m_points.level2PathPoint5->setPositionY(5);
    m_points.level2PathPoint5->setScale(0.5);
    m_points.level2PathPoint5->setScaleX(1);

    m_iLevels.level3Btn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("islandLevelBtn_001.png"_spr), this, menu_selector(GDSIslandSelectLayer::onIslandLevel));

    m_iLevels.level3Btn->setTag(3);
    m_iLevels.level3Btn->setPosition(-12, 15);
    m_iLevels.level3Btn->setVisible(false);
    level3->setPosition({ -10, 10 });

    //LEVEL 3 POINTS
    //point 1
    m_points.level3PathPoint1->setPosition(m_iLevels.level3Btn->getPosition());
    m_points.level3PathPoint1->setPositionX(m_points.level3PathPoint1->getPositionX() + 13);
    m_points.level3PathPoint1->setPositionY(2);
    m_points.level3PathPoint1->setScale(0.5);
    m_points.level3PathPoint1->setScaleX(1);
    //point 2
    m_points.level3PathPoint2->setPosition(m_iLevels.level3Btn->getPosition());
    m_points.level3PathPoint2->setPositionX(m_points.level3PathPoint2->getPositionX() + 17);
    m_points.level3PathPoint2->setPositionY(-11);
    m_points.level3PathPoint2->setScale(0.5);
    m_points.level3PathPoint2->setScaleX(1);
    //point 3
    m_points.level3PathPoint3->setPosition(m_iLevels.level3Btn->getPosition());
    m_points.level3PathPoint3->setPositionX(m_points.level3PathPoint3->getPositionX() + 19);
    m_points.level3PathPoint3->setPositionY(-20);
    m_points.level3PathPoint3->setScale(0.5);
    m_points.level3PathPoint3->setScaleX(1);
    //point 4
    m_points.level3PathPoint4->setPosition(m_iLevels.level3Btn->getPosition());
    m_points.level3PathPoint4->setPositionX(m_points.level3PathPoint4->getPositionX() + 25);
    m_points.level3PathPoint4->setPositionY(-26);
    m_points.level3PathPoint4->setScale(0.5);
    m_points.level3PathPoint4->setScaleX(1);
    //point 5
    m_points.level3PathPoint5->setPosition(m_iLevels.level3Btn->getPosition());
    m_points.level3PathPoint5->setPositionX(m_points.level3PathPoint5->getPositionX() + 42);
    m_points.level3PathPoint5->setPositionY(-28);
    m_points.level3PathPoint5->setScale(0.5);
    m_points.level3PathPoint5->setScaleX(1);

    m_iLevels.iLevel1 = GLM->getMainLevel(2001, false);
    m_iLevels.iLevel2 = GLM->getMainLevel(2002, false);
    m_iLevels.iLevel3 = GLM->getMainLevel(2003, false);
    m_iLevels.iLevel4 = GLM->getMainLevel(2004, false);
    m_iLevels.iLevel5 = GLM->getMainLevel(2005, false);
    m_iLevels.iLevel6 = GLM->getMainLevel(2006, false);
    m_iLevels.iLevel7 = GLM->getMainLevel(2007, false);
    m_iLevels.iLevel8 = GLM->getMainLevel(2008, false);
    m_iLevels.iLevel9 = GLM->getMainLevel(2009, false);
    m_iLevels.iLevel10 = GLM->getMainLevel(2010, false);

    m_iLevels.level1complete = Mod::get()->getSavedValue<int>("islandlevel1complete");
    m_iLevels.level2complete = Mod::get()->getSavedValue<int>("islandlevel2complete");
    m_iLevels.level3complete = Mod::get()->getSavedValue<int>("islandlevel3complete");
    m_iLevels.level4complete = Mod::get()->getSavedValue<int>("islandlevel4complete");
    m_iLevels.level5complete = Mod::get()->getSavedValue<int>("islandlevel5complete");
    m_iLevels.level6complete = Mod::get()->getSavedValue<int>("islandlevel6complete");
    m_iLevels.level7complete = Mod::get()->getSavedValue<int>("islandlevel7complete");
    m_iLevels.level8complete = Mod::get()->getSavedValue<int>("islandlevel8complete");
    m_iLevels.level9complete = Mod::get()->getSavedValue<int>("islandlevel9complete");
    m_iLevels.level10complete = Mod::get()->getSavedValue<int>("islandlevel10complete");

    //level 1 to level 2 animation
    if (m_iLevels.iLevel1->m_normalPercent != 100) {
        Mod::get()->setSavedValue("islandlevel1complete", 0);
    }
    
    if (m_iLevels.iLevel1->m_normalPercent == 100) {
        m_iLevels.level2Btn->setVisible(true);
    } else {
        m_points.level1PathPoint1->setOpacity(0);
        m_points.level1PathPoint2->setOpacity(0);
        m_points.level1PathPoint3->setOpacity(0);
        m_points.level1PathPoint4->setOpacity(0);
        m_points.level1PathPoint5->setOpacity(0);
    }

    if (m_iLevels.iLevel2->m_normalPercent != 100) {
        Mod::get()->setSavedValue("islandlevel2complete", 0);
    }
    if (m_iLevels.iLevel2->m_normalPercent == 100) {
        m_iLevels.level3Btn->setVisible(true);
    } else {
        m_points.level2PathPoint1->setOpacity(0);
        m_points.level2PathPoint2->setOpacity(0);
        m_points.level2PathPoint3->setOpacity(0);
        m_points.level2PathPoint4->setOpacity(0);
        m_points.level2PathPoint5->setOpacity(0);
    }
    /*dashlandsmenu->addChild(particles, 2);*/
    // Establecer la escala inicial como 0 para que est�n invisibles
    
    m_iLevels.level4Btn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("islandLevelBtn_001.png"_spr), this, menu_selector(GDSIslandSelectLayer::onIslandLevel));

    m_iLevels.level4Btn->setTag(4);
    m_iLevels.level4Btn->setPosition(47, -20);
    m_iLevels.level4Btn->setVisible(false);
    level4->setPosition({ 50, -25 });

    //LEVEL 4 POINTS
    //point 1
    m_points.level4PathPoint1->setPosition(m_iLevels.level4Btn->getPosition());
    m_points.level4PathPoint1->setPositionX(m_points.level4PathPoint1->getPositionX() + 20);
    m_points.level4PathPoint1->setPositionY(-24);
    m_points.level4PathPoint1->setScale(0.5);
    m_points.level4PathPoint1->setScaleX(1);
    //point 2
    m_points.level4PathPoint2->setPosition(m_iLevels.level4Btn->getPosition());
    m_points.level4PathPoint2->setPositionX(m_points.level4PathPoint2->getPositionX() + 36);
    m_points.level4PathPoint2->setScale(0.5);
    m_points.level4PathPoint2->setScaleX(1);
    //point 3
    m_points.level4PathPoint3->setPosition(m_iLevels.level4Btn->getPosition());
    m_points.level4PathPoint3->setPositionX(m_points.level4PathPoint3->getPositionX() + 51);
    m_points.level4PathPoint3->setPositionY(-22.5);
    m_points.level4PathPoint3->setScale(0.5);
    m_points.level4PathPoint3->setScaleX(1);
    //point 4
    m_points.level4PathPoint4->setPosition(m_iLevels.level4Btn->getPosition());
    m_points.level4PathPoint4->setPositionX(m_points.level4PathPoint4->getPositionX() + 72);
    m_points.level4PathPoint4->setPositionY(-25.5);
    m_points.level4PathPoint4->setScale(0.5);
    m_points.level4PathPoint4->setScaleX(1);
    //point 5
    m_points.level4PathPoint5->setPosition(m_iLevels.level4Btn->getPosition());
    m_points.level4PathPoint5->setPositionX(m_points.level4PathPoint5->getPositionX() + 88);
    m_points.level4PathPoint5->setPositionY(-20.5);
    m_points.level4PathPoint5->setScale(0.5);
    m_points.level4PathPoint5->setScaleX(1);

    if (m_iLevels.iLevel3->m_normalPercent != 100) {
        Mod::get()->setSavedValue("islandlevel3complete", 0);
    }
    //level 3 to level 4 animation
    if (m_iLevels.iLevel3->m_normalPercent == 100) {
        m_iLevels.level4Btn->setVisible(true);
    } else {
        m_points.level3PathPoint1->setOpacity(0);
        m_points.level3PathPoint2->setOpacity(0);
        m_points.level3PathPoint3->setOpacity(0);
        m_points.level3PathPoint4->setOpacity(0);
        m_points.level3PathPoint5->setOpacity(0);
    }
    
    m_iLevels.level5Btn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("islandLevelBtn_001.png"_spr), this, menu_selector(GDSIslandSelectLayer::onIslandLevel));

    m_iLevels.level5Btn->setTag(5);
    m_iLevels.level5Btn->setPosition(152, -5);
    m_iLevels.level5Btn->setVisible(false);
    level5->setPosition({ 155, -10 });


    if (m_iLevels.iLevel4->m_normalPercent != 100) {
        Mod::get()->setSavedValue("islandlevel4complete", 0);
    }
    //level 4 to level 5 animation
    if (m_iLevels.iLevel4->m_normalPercent == 100) {
        m_iLevels.level5Btn->setVisible(true);
    } else {
        m_points.level4PathPoint1->setOpacity(0);
        m_points.level4PathPoint2->setOpacity(0);
        m_points.level4PathPoint3->setOpacity(0);
        m_points.level4PathPoint4->setOpacity(0);
        m_points.level4PathPoint5->setOpacity(0);
    }

    auto TheInterfaceMenu = CCMenu::create();
    m_iLevels.level6Btn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("islandLevelBtn_001.png"_spr), this, menu_selector(GDSIslandSelectLayer::onIslandLevel));

    m_iLevels.level6Btn->setTag(6);
    m_iLevels.level6Btn->setPosition(-175, -12);
    m_iLevels.level6Btn->setVisible(false);
    level6->setPosition(m_iLevels.level6Btn->getPosition());

    //LEVEL 6 POINTS
    // point 1
    m_points.level6PathPoint1->setPosition(m_iLevels.level6Btn->getPosition());
    m_points.level6PathPoint1->setPositionX(m_points.level6PathPoint1->getPositionX() + 20);
    m_points.level6PathPoint1->setPositionY(-16);
    m_points.level6PathPoint1->setScale(0.5);
    m_points.level6PathPoint1->setScaleX(1);
    //point 2
    m_points.level6PathPoint2->setPosition(m_iLevels.level6Btn->getPosition());
    m_points.level6PathPoint2->setPositionX(m_points.level6PathPoint2->getPositionX() + 38);
    m_points.level6PathPoint2->setPositionY(-16.5);
    m_points.level6PathPoint2->setScale(0.5);
    m_points.level6PathPoint2->setScaleX(1);
    //point 3
    m_points.level6PathPoint3->setPosition(m_iLevels.level6Btn->getPosition());
    m_points.level6PathPoint3->setPositionX(m_points.level6PathPoint3->getPositionX() + 55);
    m_points.level6PathPoint3->setPositionY(-11);
    m_points.level6PathPoint3->setScale(0.5);
    m_points.level6PathPoint3->setScaleX(1);
    //point 4
    m_points.level6PathPoint4->setPosition(m_iLevels.level6Btn->getPosition());
    m_points.level6PathPoint4->setPositionX(m_points.level6PathPoint4->getPositionX() + 72);
    m_points.level6PathPoint4->setPositionY(-12);
    m_points.level6PathPoint4->setScale(0.5);
    m_points.level6PathPoint4->setScaleX(1);
    //point 5
    m_points.level6PathPoint5->setPosition(m_iLevels.level6Btn->getPosition());
    m_points.level6PathPoint5->setPositionX(m_points.level6PathPoint5->getPositionX() + 85);
    m_points.level6PathPoint5->setPositionY(-19.5);
    m_points.level6PathPoint5->setScale(0.5);
    m_points.level6PathPoint5->setScaleX(1);

    TheInterfaceMenu->addChild(m_points.level6PathPoint1,2);
    TheInterfaceMenu->addChild(m_points.level6PathPoint2, 2);
    TheInterfaceMenu->addChild(m_points.level6PathPoint3, 2);
    TheInterfaceMenu->addChild(m_points.level6PathPoint4, 2);
    TheInterfaceMenu->addChild(m_points.level6PathPoint5, 2);

    m_iLevels.level7Btn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("islandLevelBtn_001.png"_spr), this, menu_selector(GDSIslandSelectLayer::onIslandLevel));

    m_iLevels.level7Btn->setTag(7);
    m_iLevels.level7Btn->setPosition(-73, -28);
    m_iLevels.level7Btn->setVisible(false);
    level7->setPosition(m_iLevels.level7Btn->getPosition());

    //LEVEL 7 POINTS
    // point 1
    m_points.level7PathPoint1->setPosition(m_iLevels.level7Btn->getPosition());
    m_points.level7PathPoint1->setPositionX(m_points.level7PathPoint1->getPositionX() + 10);
    m_points.level7PathPoint1->setPositionY(-8);
    m_points.level7PathPoint1->setScale(0.5);
    m_points.level7PathPoint1->setScaleX(1);
    //point 2
    m_points.level7PathPoint2->setPosition(m_iLevels.level7Btn->getPosition());
    m_points.level7PathPoint2->setPositionX(m_points.level7PathPoint2->getPositionX() + 15);
    m_points.level7PathPoint2->setPositionY(0);
    m_points.level7PathPoint2->setScale(0.5);
    m_points.level7PathPoint2->setScaleX(1);
    //point 3
    m_points.level7PathPoint3->setPosition(m_iLevels.level7Btn->getPosition());
    m_points.level7PathPoint3->setPositionX(m_points.level7PathPoint3->getPositionX() + 30);
    m_points.level7PathPoint3->setPositionY(7);
    m_points.level7PathPoint3->setScale(0.5);
    m_points.level7PathPoint3->setScaleX(1);
    //point 4
    m_points.level7PathPoint4->setPosition(m_iLevels.level7Btn->getPosition());
    m_points.level7PathPoint4->setPositionX(m_points.level7PathPoint4->getPositionX() + 44);
    m_points.level7PathPoint4->setPositionY(9.5);
    m_points.level7PathPoint4->setScale(0.5);
    m_points.level7PathPoint4->setScaleX(1);

    TheInterfaceMenu->addChild(m_points.level7PathPoint1, 2);
    TheInterfaceMenu->addChild(m_points.level7PathPoint2, 2);
    TheInterfaceMenu->addChild(m_points.level7PathPoint3, 2);
    TheInterfaceMenu->addChild(m_points.level7PathPoint4, 2);

    if (m_iLevels.iLevel6->m_normalPercent != 100) {
        Mod::get()->setSavedValue("islandlevel6complete", 0);
    }
    if (m_iLevels.iLevel6->m_normalPercent == 100) {
        m_iLevels.level7Btn->setVisible(true);
    } else {
        m_points.level6PathPoint1->setOpacity(0);
        m_points.level6PathPoint2->setOpacity(0);
        m_points.level6PathPoint3->setOpacity(0);
        m_points.level6PathPoint4->setOpacity(0);
        m_points.level6PathPoint5->setOpacity(0);
    }

    m_iLevels.level8Btn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("islandLevelBtn_001.png"_spr), this, menu_selector(GDSIslandSelectLayer::onIslandLevel));

    m_iLevels.level8Btn->setTag(8);
    m_iLevels.level8Btn->setPosition(-10, 15);
    m_iLevels.level8Btn->setVisible(false);
    level8->setPosition(m_iLevels.level8Btn->getPosition());

    //LEVEL 8 POINTS
    //point 1
    m_points.level8PathPoint1->setPosition(m_iLevels.level8Btn->getPosition());
    m_points.level8PathPoint1->setPositionX(m_points.level8PathPoint1->getPositionX() + 10);
    m_points.level8PathPoint1->setPositionY(3);
    m_points.level8PathPoint1->setScale(0.5);
    m_points.level8PathPoint1->setScaleX(1);
    //point 2
    m_points.level8PathPoint2->setPosition(m_iLevels.level8Btn->getPosition());
    m_points.level8PathPoint2->setPositionX(m_points.level8PathPoint2->getPositionX());
    m_points.level8PathPoint2->setPositionY(-7);
    m_points.level8PathPoint2->setScale(0.5);
    m_points.level8PathPoint2->setScaleX(1);
    //point 3
    m_points.level8PathPoint3->setPosition(m_iLevels.level8Btn->getPosition());
    m_points.level8PathPoint3->setPositionX(m_points.level8PathPoint3->getPositionX() - 10);
    m_points.level8PathPoint3->setPositionY(-11);
    m_points.level8PathPoint3->setScale(0.5);
    m_points.level8PathPoint3->setScaleX(1);
    //point 4
    m_points.level8PathPoint4->setPosition(m_iLevels.level8Btn->getPosition());
    m_points.level8PathPoint4->setPositionX(m_points.level8PathPoint4->getPositionX() - 15 );
    m_points.level8PathPoint4->setPositionY(-20);
    m_points.level8PathPoint4->setScale(0.5);
    m_points.level8PathPoint4->setScaleX(1);
    //point 5
    m_points.level8PathPoint5->setPosition(m_iLevels.level8Btn->getPosition());
    m_points.level8PathPoint5->setPositionX(m_points.level8PathPoint5->getPositionX() - 5);
    m_points.level8PathPoint5->setPositionY(-32);
    m_points.level8PathPoint5->setScale(0.5);
    m_points.level8PathPoint5->setScaleX(1);
    //point 6
    m_points.level8PathPoint6->setPosition(m_iLevels.level8Btn->getPosition());
    m_points.level8PathPoint6->setPositionX(m_points.level8PathPoint6->getPositionX() + 17);
    m_points.level8PathPoint6->setPositionY(-36.5);
    m_points.level8PathPoint6->setScale(0.5);
    m_points.level8PathPoint6->setScaleX(1);
    //point 7
    m_points.level8PathPoint7->setPosition(m_iLevels.level8Btn->getPosition());
    m_points.level8PathPoint7->setPositionX(m_points.level8PathPoint7->getPositionX() + 41);
    m_points.level8PathPoint7->setPositionY(-40);
    m_points.level8PathPoint7->setScale(0.5);
    m_points.level8PathPoint7->setScaleX(1);
    //point 8
    m_points.level8PathPoint8->setPosition(m_iLevels.level8Btn->getPosition());
    m_points.level8PathPoint8->setPositionX(m_points.level8PathPoint8->getPositionX() + 63);
    m_points.level8PathPoint8->setPositionY(-40.5);
    m_points.level8PathPoint8->setScale(0.5);
    m_points.level8PathPoint8->setScaleX(1);

    TheInterfaceMenu->addChild(m_points.level8PathPoint1, 2);
    TheInterfaceMenu->addChild(m_points.level8PathPoint2, 2);
    TheInterfaceMenu->addChild(m_points.level8PathPoint3, 2);
    TheInterfaceMenu->addChild(m_points.level8PathPoint4, 2);
    TheInterfaceMenu->addChild(m_points.level8PathPoint5, 2);
    TheInterfaceMenu->addChild(m_points.level8PathPoint6, 2);
    TheInterfaceMenu->addChild(m_points.level8PathPoint7, 2);
    TheInterfaceMenu->addChild(m_points.level8PathPoint8, 2);

    if (m_iLevels.iLevel7->m_normalPercent != 100) {
        Mod::get()->setSavedValue("islandlevel7complete", 0);
    }
    ////level 7 to level 8 animation
    if (m_iLevels.iLevel7->m_normalPercent == 100) {
        m_iLevels.level8Btn->setVisible(true);
    } else {
        m_points.level7PathPoint1->setOpacity(0);
        m_points.level7PathPoint2->setOpacity(0);
        m_points.level7PathPoint3->setOpacity(0);
        m_points.level7PathPoint4->setOpacity(0);
        m_points.level7PathPoint5->setOpacity(0);
    }

    m_iLevels.level9Btn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("islandLevelBtn_001.png"_spr), this, menu_selector(GDSIslandSelectLayer::onIslandLevel));

    m_iLevels.level9Btn->setTag(9);
    m_iLevels.level9Btn->setPosition(80, -38);
    m_iLevels.level9Btn->setVisible(false);
    level9->setPosition(m_iLevels.level9Btn->getPosition());

    //LEVEL 9 POINTS
    //point 1
    m_points.level9PathPoint1->setPosition(m_iLevels.level9Btn->getPosition());
    m_points.level9PathPoint1->setPositionX(m_points.level9PathPoint1->getPositionX() + 16);
    m_points.level9PathPoint1->setPositionY(-34);
    m_points.level9PathPoint1->setScale(0.5);
    m_points.level9PathPoint1->setScaleX(1);
    //point 2
    m_points.level9PathPoint2->setPosition(m_iLevels.level9Btn->getPosition());
    m_points.level9PathPoint2->setPositionX(m_points.level9PathPoint2->getPositionX() + 25);
    m_points.level9PathPoint2->setPositionY(-27);
    m_points.level9PathPoint2->setScale(0.5);
    m_points.level9PathPoint2->setScaleX(1);
    //point 3
    m_points.level9PathPoint3->setPosition(m_iLevels.level9Btn->getPosition());
    m_points.level9PathPoint3->setPositionX(m_points.level9PathPoint3->getPositionX() + 34);
    m_points.level9PathPoint3->setPositionY(-20.5);
    m_points.level9PathPoint3->setScale(0.5);
    m_points.level9PathPoint3->setScaleX(1);
    //point 4
    m_points.level9PathPoint4->setPosition(m_iLevels.level9Btn->getPosition());
    m_points.level9PathPoint4->setPositionX(m_points.level9PathPoint4->getPositionX() + 45);
    m_points.level9PathPoint4->setPositionY(-16);
    m_points.level9PathPoint4->setScale(0.5);
    m_points.level9PathPoint4->setScaleX(1);
    //point 5
    m_points.level9PathPoint5->setPosition(m_iLevels.level9Btn->getPosition());
    m_points.level9PathPoint5->setPositionX(m_points.level9PathPoint5->getPositionX() + 67);
    m_points.level9PathPoint5->setPositionY(-12);
    m_points.level9PathPoint5->setScale(0.5);
    m_points.level9PathPoint5->setScaleX(1);

    TheInterfaceMenu->addChild(m_points.level9PathPoint1, 2);
    TheInterfaceMenu->addChild(m_points.level9PathPoint2, 2);
    TheInterfaceMenu->addChild(m_points.level9PathPoint3, 2);
    TheInterfaceMenu->addChild(m_points.level9PathPoint4, 2);
    TheInterfaceMenu->addChild(m_points.level9PathPoint5, 2);

    if (m_iLevels.iLevel8->m_normalPercent != 100) {
        Mod::get()->setSavedValue("islandlevel8complete", 0);
    }
    //level 8 to level 9 animation
    if (m_iLevels.iLevel8->m_normalPercent == 100) {
        m_iLevels.level9Btn->setVisible(true);
    } else {
        m_points.level8PathPoint1->setOpacity(0);
        m_points.level8PathPoint2->setOpacity(0);
        m_points.level8PathPoint3->setOpacity(0);
        m_points.level8PathPoint4->setOpacity(0);
        m_points.level8PathPoint5->setOpacity(0);
        m_points.level8PathPoint6->setOpacity(0);
        m_points.level8PathPoint7->setOpacity(0);
        m_points.level8PathPoint8->setOpacity(0);
    }

    m_iLevels.level10Btn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("islandLevelBtn_001.png"_spr), this, menu_selector(GDSIslandSelectLayer::onIslandLevel));

    m_iLevels.level10Btn->setTag(10);
    m_iLevels.level10Btn->setPosition(170, -10);

    m_iLevels.level10Btn->setVisible(false);
    level10->setPosition(m_iLevels.level10Btn->getPosition());

    if (m_iLevels.iLevel9->m_normalPercent != 100) {
        Mod::get()->setSavedValue("islandlevel9complete", 0);
    }
    // level 9 to level 10 animation
    if (m_iLevels.iLevel9->m_normalPercent == 100) {
        m_iLevels.level10Btn->setVisible(true);
    } else {
        m_points.level9PathPoint1->setOpacity(0);
        m_points.level9PathPoint2->setOpacity(0);
        m_points.level9PathPoint3->setOpacity(0);
        m_points.level9PathPoint4->setOpacity(0);
        m_points.level9PathPoint5->setOpacity(0);
    }

    if (m_iLevels.iLevel10->m_normalPercent != 100) {
        Mod::get()->setSavedValue("islandlevel10complete", 0);
    }
    if (m_iLevels.iLevel10->m_normalPercent == 100) {
        m_iLevels.level10Btn->setVisible(true);
    }

    TheInterfaceMenu->addChild(m_iLevels.level6Btn,2);
    TheInterfaceMenu->addChild(m_iLevels.level7Btn, 2);
    TheInterfaceMenu->addChild(m_iLevels.level8Btn,2);
    TheInterfaceMenu->addChild(m_iLevels.level9Btn, 2);
    TheInterfaceMenu->addChild(m_iLevels.level10Btn,2);

    TheInterfaceMenu->addChild(level6);
    TheInterfaceMenu->addChild(level7);
    TheInterfaceMenu->addChild(level8);
    TheInterfaceMenu->addChild(level9);
    TheInterfaceMenu->addChild(level10);
    
    //LEVEL 5 POINTS
    //point 1
    m_points.level10PathPoint1->setPosition(m_iLevels.level5Btn->getPosition());
    m_points.level10PathPoint1->setPositionX(m_points.level10PathPoint1->getPositionX() + 20);
    m_points.level10PathPoint1->setPositionY(-20);
    m_points.level10PathPoint1->setScale(0.5);
    m_points.level10PathPoint1->setScaleX(1);
    //point 2
    m_points.level10PathPoint2->setPosition(m_iLevels.level5Btn->getPosition());
    m_points.level10PathPoint2->setPositionX(m_points.level10PathPoint2->getPositionX() + 32);
    m_points.level10PathPoint2->setPositionY(-25);
    m_points.level10PathPoint2->setScale(0.5);
    m_points.level10PathPoint2->setScaleX(1);
    //point 3
    m_points.level10PathPoint3->setPosition(m_iLevels.level5Btn->getPosition());
    m_points.level10PathPoint3->setPositionX(m_points.level10PathPoint3->getPositionX() + 50);
    m_points.level10PathPoint3->setPositionY(-22);
    m_points.level10PathPoint3->setScale(0.5);
    m_points.level10PathPoint3->setScaleX(1);
    //point 4
    m_points.level10PathPoint4->setPosition(m_iLevels.level5Btn->getPosition());
    m_points.level10PathPoint4->setPositionX(m_points.level10PathPoint4->getPositionX() + 77);
    m_points.level10PathPoint4->setPositionY(-22.5);
    m_points.level10PathPoint4->setScale(0.5);
    m_points.level10PathPoint4->setScaleX(1);
    //point 5
    m_points.level10PathPoint5->setPosition(m_iLevels.level5Btn->getPosition());
    m_points.level10PathPoint5->setPositionX(m_points.level10PathPoint5->getPositionX() + 89.7);
    m_points.level10PathPoint5->setPositionY(-26);
    m_points.level10PathPoint5->setScale(0.5);
    m_points.level10PathPoint5->setScaleX(1);

    dashlandsmenu->setPosition(winSize / 2);
    dashlandsmenu->setPositionY(dashlandsmenu->getPositionY());
    //button levels
    dashlandsmenu->addChild(m_iLevels.level1Btn);
    dashlandsmenu->addChild(m_iLevels.level2Btn,1);
    dashlandsmenu->addChild(m_iLevels.level3Btn,1);
    dashlandsmenu->addChild(m_iLevels.level4Btn,1);
    dashlandsmenu->addChild(m_iLevels.level5Btn,1);

    //skull - locked levels
    dashlandsmenu->addChild(level2);
    dashlandsmenu->addChild(level3);
    dashlandsmenu->addChild(level4);
    dashlandsmenu->addChild(level5);
    dashlandsmenu->setZOrder(1);
    
    node->addChild(sprite);
    node->addChild(dashlandsmenu);
    node->addChild(TheAssembly);
    node->setTag(20);

    node2->addChild(sprite2);
    node2->addChild(TheInterface);
    node2->addChild(TheInterfaceMenu);
    node2->setTag(22);

    TheInterfaceMenu->setPosition(winSize / 2);
    TheInterfaceMenu->setPositionY(TheInterfaceMenu->getPositionY());

    node3->addChild(sprite3);
    node3->addChild(ComingSoon);
    node3->setTag(23);

    m_mainLevels = CCArray::create();
    m_levelPages = CCArray::create();

    m_level = 0;

    m_levelPages->addObject(node);
    m_levelPages->addObject(node2);
    m_levelPages->addObject(node3);

    m_scrollLayer = BoomScrollLayer::create(m_levelPages, 0, false, nullptr, static_cast<DynamicScrollDelegate*>(this));
    m_scrollLayer->m_extendedLayer->m_delegate = static_cast<BoomScrollLayerDelegate*>(this);

    if (page) {
        if (page == 21) m_scrollLayer->instantMoveToPage(20);
        m_scrollLayer->instantMoveToPage(page);
    } else {
        scrollLayerMoved(m_scrollLayer->m_extendedLayer->getPosition());
    }

    auto pointer = (CCSpriteBatchNode*)m_scrollLayer->getChildren()->objectAtIndex(1);
    pointer->setPositionY(director->getScreenBottom() - 45);
    addChild(m_scrollLayer);

    //level 5 to level 6 animation
    if (m_iLevels.iLevel5->m_normalPercent != 100) {
        Mod::get()->setSavedValue("islandlevel5complete", 0);
    }
    if (m_iLevels.iLevel5->m_normalPercent == 100) {
        m_iLevels.level6Btn->setVisible(true);
    }
    else {
        m_points.level5PathPoint1->setOpacity(0);
        m_points.level5PathPoint2->setOpacity(0);
        m_points.level5PathPoint3->setOpacity(0);
        m_points.level5PathPoint4->setOpacity(0);
        m_points.level5PathPoint5->setOpacity(0);
    }

    sprite->setPosition(winSize / 2);
    sprite->setPositionY(sprite->getPositionY() - 30);

    TheAssembly->setPositionX(sprite->getPositionX());
    TheAssembly->setPositionY(sprite->getPositionY() + 150);
    TheAssembly->setScale(0.8);

    sprite2->setPosition(winSize / 2);
    sprite2->setPositionY(sprite2->getPositionY() - 30);

    sprite3->setPosition(winSize / 2);
    sprite3->setPositionY(sprite3->getPositionY() - 30);

    TheInterface->setPositionX(sprite2->getPositionX());
    TheInterface->setPositionY(sprite2->getPositionY() + 150);
    TheInterface->setScale(0.8);

    ComingSoon->setPositionX(sprite3->getPositionX());
    ComingSoon->setPositionY(sprite3->getPositionY() + 150);
    ComingSoon->setScale(0.8);
    
    //start arrow animation
    auto moveUp = CCMoveBy::create(0.5f, ccp(0, 5)); 
    auto moveDown = CCMoveBy::create(0.5f, ccp(0, -5));

    auto easeOutUp = CCEaseInOut::create(moveUp,1.5f);   
    auto easeInDown = CCEaseInOut::create(moveDown, 1.5f);

    auto moveSequence = CCSequence::create(easeOutUp, easeInDown, nullptr);

    auto repeatAction = CCRepeatForever::create(moveSequence);

    // Loops
    
    auto moveUp21 = CCMoveBy::create(1.0f, ccp(0, 1));
    auto moveDown21 = moveUp21->reverse();

    auto moveUp121 = CCMoveBy::create(1.0f, ccp(0, 1));
    auto moveDown121 = moveUp121->reverse();

    auto easeOutUp21 = CCEaseOut::create(moveUp21, 1.5f);
    auto easeInDown21 = CCEaseIn::create(moveDown21, 1.5f);

    auto easeOutDown21 = CCEaseOut::create(moveDown121, 1.5f);
    auto easeInUp21 = CCEaseIn::create(moveUp121, 1.5f);
    auto moveSequence21 = CCSequence::create(easeOutUp21, easeInDown21, easeOutDown21, easeInUp21, nullptr);

    auto repeatAction21 = CCRepeatForever::create(moveSequence21);

    auto moveUp2 = CCMoveBy::create(1.0f, ccp(0, 1)); 
    auto moveDown2 = moveUp2->reverse(); 

    auto moveUp12 = CCMoveBy::create(1.0f, ccp(0, 1)); 
    auto moveDown12 = moveUp2->reverse();

    auto easeOutUp2 = CCEaseOut::create(moveUp2, 1.5f); 
    auto easeInDown2 = CCEaseIn::create(moveDown2, 1.5f); 

    auto easeOutDown2 = CCEaseOut::create(moveDown12, 1.5f); 
    auto easeInUp2 = CCEaseIn::create(moveUp12, 1.5f); 
    auto moveSequence2 = CCSequence::create(easeOutUp2, easeInDown2, easeOutDown2, easeInUp2, nullptr);

    auto repeatAction2 = CCRepeatForever::create(moveSequence2);

    node->runAction(repeatAction21);
    node2->runAction(repeatAction2);

    if (m_iLevels.iLevel1->m_normalPercent != 100) {
        auto level1arrow = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");

        level1arrow->setPosition(m_iLevels.level1Btn->getPosition());

        level1arrow->setPositionY(level1arrow->getPositionY() + 40);
        level1arrow->setRotation(-90);
        level1arrow->setScale(0.6);
        dashlandsmenu->addChild(level1arrow);
        level1arrow->runAction(repeatAction);
    }

    m_background = createLayerBG();
    m_background->setZOrder(-4);
    addChild(m_background);

    sprite3->setColor(ccBLACK);
    sprite3->setOpacity(40);
    
    m_background->setColor({ 0, 125, 255 });
    addSideArt(this, SideArt::Bottom, false);
    
    auto pageBtnsMenu = CCMenu::create();
    pageBtnsMenu->setPosition({ 0, 0 });
    pageBtnsMenu->setZOrder(2);
    
    auto nextPageIcon = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    nextPageIcon->setFlipX(false);
    
    m_nextPageBtn = CCMenuItemSpriteExtra::create(
        nextPageIcon,
        this,
        menu_selector(GDSIslandSelectLayer::onNext)
    );
    m_nextPageBtn->setPosition({ winSize.width * 0.95f, winSize.height * 0.5f });

    auto prevPageIcon = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    prevPageIcon->setFlipX(true);
    
    m_prevPageBtn = CCMenuItemSpriteExtra::create(
        prevPageIcon,
        this,
        menu_selector(GDSIslandSelectLayer::onPrev)
    );
    m_prevPageBtn->setPosition({ winSize.width * 0.05f, winSize.height * 0.5f });
    m_prevPageBtn->setVisible(false);

    pageBtnsMenu->addChild(m_nextPageBtn);
    pageBtnsMenu->addChild(m_prevPageBtn);

    addChild(pageBtnsMenu);

    if (m_iLevels.level2complete == 1) {
        level2->setVisible(false);
    }
    if (m_iLevels.level3complete == 1) {
        level3->setVisible(false);
    }
    if (m_iLevels.level4complete == 1) {
        level4->setVisible(false);
    }
    if (m_iLevels.level5complete == 1) {
        level5->setVisible(false);
    }
    if (m_iLevels.level6complete == 1) {
        level6->setVisible(false);
    }
    if (m_iLevels.level7complete == 1) {
        level7->setVisible(false);
    }
    if (m_iLevels.level8complete == 1) {
        level8->setVisible(false);
    }
    if (m_iLevels.level9complete == 1) {
        level9->setVisible(false);
    }
    if (m_iLevels.level10complete == 1) {
        level10->setVisible(false);
    }

    if (m_iLevels.iLevel1->m_normalPercent == 100 && m_iLevels.iLevel2->m_normalPercent == 0 && m_iLevels.level1complete == 0) {
        m_points.level1PathPoint1->setScaleY(1.2);
        m_points.level1PathPoint2->setScaleY(1.2);
        m_points.level1PathPoint3->setScaleY(1.2);
        m_points.level1PathPoint4->setScaleY(1.2);
        m_points.level1PathPoint5->setScaleY(1.2);

        m_points.level1PathPoint1->setScaleX(2);
        m_points.level1PathPoint2->setScaleX(2);
        m_points.level1PathPoint3->setScaleX(2);
        m_points.level1PathPoint4->setScaleX(2);
        m_points.level1PathPoint5->setScaleX(2);
        //opacty
        m_points.level1PathPoint1->setOpacity(0);
        m_points.level1PathPoint2->setOpacity(0);
        m_points.level1PathPoint3->setOpacity(0);
        m_points.level1PathPoint4->setOpacity(0);
        m_points.level1PathPoint5->setOpacity(0);
        m_iLevels.level2Btn->setOpacity(0);
    
        m_points.level1PathPoint1->runAction(CCSequence::create(CCDelayTime::create(0.3), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level1PathPoint2->runAction(CCSequence::create(CCDelayTime::create(0.6), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level1PathPoint3->runAction(CCSequence::create(CCDelayTime::create(0.9), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level1PathPoint4->runAction(CCSequence::create(CCDelayTime::create(1.2), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level1PathPoint5->runAction(CCSequence::create(CCDelayTime::create(1.5), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        
        m_iLevels.level2Btn->setScale(1.5);
        m_iLevels.level2Btn->setVisible(true);

        Mod::get()->setSavedValue("iLevelUnlocked", 1);
        m_iLevels.level2Btn->runAction(CCSequence::create(
            CCDelayTime::create(1.8),
            CCCallFunc::create(this, callfunc_selector(GDSIslandSelectLayer::runParticle)),
            CCFadeIn::create(0.1),
            CCEaseBounceOut::create(m_scaleWithBounce2),
            nullptr
        ));

        Mod::get()->setSavedValue("islandlevel1complete", 1);
    }
    if (m_iLevels.iLevel2->m_normalPercent == 100 && m_iLevels.iLevel3->m_normalPercent == 0 && m_iLevels.level2complete == 0) {
        //level 2 to level 3 animation
        m_points.level2PathPoint1->setScaleY(1.2);
        m_points.level2PathPoint2->setScaleY(1.2);
        m_points.level2PathPoint3->setScaleY(1.2);
        m_points.level2PathPoint4->setScaleY(1.2);
        m_points.level2PathPoint5->setScaleY(1.2);

        m_points.level2PathPoint1->setScaleX(2);
        m_points.level2PathPoint2->setScaleX(2);
        m_points.level2PathPoint3->setScaleX(2);
        m_points.level2PathPoint4->setScaleX(2);
        m_points.level2PathPoint5->setScaleX(2);
        //opacty
        m_points.level2PathPoint1->setOpacity(0);
        m_points.level2PathPoint2->setOpacity(0);
        m_points.level2PathPoint3->setOpacity(0);
        m_points.level2PathPoint4->setOpacity(0);
        m_points.level2PathPoint5->setOpacity(0);
        m_iLevels.level3Btn->setOpacity(0);

        m_points.level2PathPoint1->runAction(CCSequence::create(CCDelayTime::create(0.3), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level2PathPoint2->runAction(CCSequence::create(CCDelayTime::create(0.6), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level2PathPoint3->runAction(CCSequence::create(CCDelayTime::create(0.9), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level2PathPoint4->runAction(CCSequence::create(CCDelayTime::create(1.2), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level2PathPoint5->runAction(CCSequence::create(CCDelayTime::create(1.5), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));

        m_iLevels.level3Btn->setScale(1.5);
        m_iLevels.level3Btn->setVisible(true);

        Mod::get()->setSavedValue("iLevelUnlocked", 2);
        m_iLevels.level3Btn->runAction(CCSequence::create(
            CCDelayTime::create(1.8),
            CCCallFunc::create(this, callfunc_selector(GDSIslandSelectLayer::runParticle)),
            CCFadeIn::create(0.1),
            CCEaseBounceOut::create(m_scaleWithBounce2),
            nullptr
        ));
        Mod::get()->setSavedValue("islandlevel2complete", 1);
    }
    if (m_iLevels.iLevel3->m_normalPercent == 100 && m_iLevels.iLevel4->m_normalPercent == 0 && m_iLevels.level3complete == 0) {
        m_points.level3PathPoint1->setScaleY(1.2);
        m_points.level3PathPoint2->setScaleY(1.2);
        m_points.level3PathPoint3->setScaleY(1.2);
        m_points.level3PathPoint4->setScaleY(1.2);
        m_points.level3PathPoint5->setScaleY(1.2);

        m_points.level3PathPoint1->setScaleX(2);
        m_points.level3PathPoint2->setScaleX(2);
        m_points.level3PathPoint3->setScaleX(2);
        m_points.level3PathPoint4->setScaleX(2);
        m_points.level3PathPoint5->setScaleX(2);
        //opacty
        m_points.level3PathPoint1->setOpacity(0);
        m_points.level3PathPoint2->setOpacity(0);
        m_points.level3PathPoint3->setOpacity(0);
        m_points.level3PathPoint4->setOpacity(0);
        m_points.level3PathPoint5->setOpacity(0);
        m_iLevels.level4Btn->setOpacity(0);

        m_points.level3PathPoint1->runAction(CCSequence::create(CCDelayTime::create(0.3), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level3PathPoint2->runAction(CCSequence::create(CCDelayTime::create(0.6), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level3PathPoint3->runAction(CCSequence::create(CCDelayTime::create(0.9), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level3PathPoint4->runAction(CCSequence::create(CCDelayTime::create(1.2), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level3PathPoint5->runAction(CCSequence::create(CCDelayTime::create(1.5), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));

        m_iLevels.level4Btn->setScale(1.5);
        m_iLevels.level4Btn->setVisible(true);

        Mod::get()->setSavedValue("iLevelUnlocked", 3);
        m_iLevels.level4Btn->runAction(CCSequence::create(
            CCDelayTime::create(1.8),
            CCCallFunc::create(this, callfunc_selector(GDSIslandSelectLayer::runParticle)),
            CCFadeIn::create(0.1),
            CCEaseBounceOut::create(m_scaleWithBounce2),
            nullptr
        ));
        Mod::get()->setSavedValue("islandlevel3complete", 1);
    }
    if (m_iLevels.iLevel4->m_normalPercent == 100 && m_iLevels.iLevel5->m_normalPercent == 0 && m_iLevels.level4complete == 0) {
        m_points.level4PathPoint1->setScaleY(1.2);
        m_points.level4PathPoint2->setScaleY(1.2);
        m_points.level4PathPoint3->setScaleY(1.2);
        m_points.level4PathPoint4->setScaleY(1.2);
        m_points.level4PathPoint5->setScaleY(1.2);

        m_points.level4PathPoint1->setScaleX(2);
        m_points.level4PathPoint2->setScaleX(2);
        m_points.level4PathPoint3->setScaleX(2);
        m_points.level4PathPoint4->setScaleX(2);
        m_points.level4PathPoint5->setScaleX(2);
        //opacty
        m_points.level4PathPoint1->setOpacity(0);
        m_points.level4PathPoint2->setOpacity(0);
        m_points.level4PathPoint3->setOpacity(0);
        m_points.level4PathPoint4->setOpacity(0);
        m_points.level4PathPoint5->setOpacity(0);
        m_iLevels.level5Btn->setOpacity(0);

        m_points.level4PathPoint1->runAction(CCSequence::create(CCDelayTime::create(0.3), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level4PathPoint2->runAction(CCSequence::create(CCDelayTime::create(0.6), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level4PathPoint3->runAction(CCSequence::create(CCDelayTime::create(0.9), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level4PathPoint4->runAction(CCSequence::create(CCDelayTime::create(1.2), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level4PathPoint5->runAction(CCSequence::create(CCDelayTime::create(1.5), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));

        m_iLevels.level5Btn->setScale(1.5);
        m_iLevels.level5Btn->setVisible(true);

        Mod::get()->setSavedValue("iLevelUnlocked", 4);
        m_iLevels.level5Btn->runAction(CCSequence::create(
            CCDelayTime::create(1.8),
            CCCallFunc::create(this, callfunc_selector(GDSIslandSelectLayer::runParticle)),
            CCFadeIn::create(0.1),
            CCEaseBounceOut::create(m_scaleWithBounce2),
            nullptr
        ));
        Mod::get()->setSavedValue("islandlevel4complete", 1);
    }
    if (m_iLevels.iLevel5->m_normalPercent == 100 && m_iLevels.iLevel6->m_normalPercent == 0 && m_iLevels.level5complete == 0) {
        m_iLevels.level6Btn->setOpacity(0);

        m_iLevels.level6Btn->setScale(1.5);
        m_iLevels.level6Btn->setVisible(true);

        Mod::get()->setSavedValue("iLevelUnlocked", 5);

        m_scrollLayer->moveToPage(1);
        m_iLevels.level6Btn->runAction(CCSequence::create(
            CCDelayTime::create(1.2),
            CCCallFunc::create(this, callfunc_selector(GDSIslandSelectLayer::runParticle)),
            CCFadeIn::create(0.1),
            CCEaseBounceOut::create(m_scaleWithBounce2),
            nullptr
        ));

        Mod::get()->setSavedValue("islandlevel5complete", 1);
    }
    if (m_iLevels.iLevel6->m_normalPercent == 100 && m_iLevels.iLevel7->m_normalPercent == 0 && m_iLevels.level6complete == 0) {
        m_points.level6PathPoint1->setScaleY(1.2);
        m_points.level6PathPoint2->setScaleY(1.2);
        m_points.level6PathPoint3->setScaleY(1.2);
        m_points.level6PathPoint4->setScaleY(1.2);
        m_points.level6PathPoint5->setScaleY(1.2);

        m_points.level6PathPoint1->setScaleX(2);
        m_points.level6PathPoint2->setScaleX(2);
        m_points.level6PathPoint3->setScaleX(2);
        m_points.level6PathPoint4->setScaleX(2);
        m_points.level6PathPoint5->setScaleX(2);
        //opacty
        m_points.level6PathPoint1->setOpacity(0);
        m_points.level6PathPoint2->setOpacity(0);
        m_points.level6PathPoint3->setOpacity(0);
        m_points.level6PathPoint4->setOpacity(0);
        m_points.level6PathPoint5->setOpacity(0);
        m_iLevels.level7Btn->setOpacity(0);

        m_points.level6PathPoint1->runAction(CCSequence::create(CCDelayTime::create(0.3), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level6PathPoint2->runAction(CCSequence::create(CCDelayTime::create(0.6), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level6PathPoint3->runAction(CCSequence::create(CCDelayTime::create(0.9), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level6PathPoint4->runAction(CCSequence::create(CCDelayTime::create(1.2), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level6PathPoint5->runAction(CCSequence::create(CCDelayTime::create(1.5), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));

        m_iLevels.level7Btn->setScale(1.5);
        m_iLevels.level7Btn->setVisible(true);

        Mod::get()->setSavedValue("iLevelUnlocked", 6);
        m_iLevels.level7Btn->runAction(CCSequence::create(
            CCDelayTime::create(1.8),
            CCCallFunc::create(this, callfunc_selector(GDSIslandSelectLayer::runParticle)),
            CCFadeIn::create(0.1),
            CCEaseBounceOut::create(m_scaleWithBounce2),
            nullptr
        ));
        Mod::get()->setSavedValue("islandlevel6complete", 1);
    }
    if (m_iLevels.iLevel7->m_normalPercent == 100 && m_iLevels.iLevel8->m_normalPercent == 0 && m_iLevels.level7complete == 0) {
        m_points.level7PathPoint1->setScaleY(1.2);
        m_points.level7PathPoint2->setScaleY(1.2);
        m_points.level7PathPoint3->setScaleY(1.2);
        m_points.level7PathPoint4->setScaleY(1.2);
    
        m_points.level7PathPoint1->setScaleX(2);
        m_points.level7PathPoint2->setScaleX(2);
        m_points.level7PathPoint3->setScaleX(2);
        m_points.level7PathPoint4->setScaleX(2);

        //opacty
        m_points.level7PathPoint1->setOpacity(0);
        m_points.level7PathPoint2->setOpacity(0);
        m_points.level7PathPoint3->setOpacity(0);
        m_points.level7PathPoint4->setOpacity(0);

        m_iLevels.level8Btn->setOpacity(0);

        m_points.level7PathPoint1->runAction(CCSequence::create(CCDelayTime::create(0.3), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level7PathPoint2->runAction(CCSequence::create(CCDelayTime::create(0.6), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level7PathPoint3->runAction(CCSequence::create(CCDelayTime::create(0.9), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level7PathPoint4->runAction(CCSequence::create(CCDelayTime::create(1.2), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));

        m_iLevels.level8Btn->setScale(1.5);
        m_iLevels.level8Btn->setVisible(true);

        Mod::get()->setSavedValue("iLevelUnlocked", 7);
        m_iLevels.level8Btn->runAction(CCSequence::create(
            CCDelayTime::create(1.5),
            CCCallFunc::create(this, callfunc_selector(GDSIslandSelectLayer::runParticle)),
            CCFadeIn::create(0.1),
            CCEaseBounceOut::create(m_scaleWithBounce2),
            nullptr
        ));
        Mod::get()->setSavedValue("islandlevel7complete", 1);
    }
    if (m_iLevels.iLevel8->m_normalPercent == 100 && m_iLevels.iLevel9->m_normalPercent == 0 && m_iLevels.level8complete == 0) {
        m_points.level8PathPoint1->setScaleY(1.2);
        m_points.level8PathPoint2->setScaleY(1.2);
        m_points.level8PathPoint3->setScaleY(1.2);
        m_points.level8PathPoint4->setScaleY(1.2);
        m_points.level8PathPoint5->setScaleY(1.2);
        m_points.level8PathPoint6->setScaleY(1.2);
        m_points.level8PathPoint7->setScaleY(1.2);
        m_points.level8PathPoint8->setScaleY(1.2);

        m_points.level8PathPoint1->setScaleX(2);
        m_points.level8PathPoint2->setScaleX(2);
        m_points.level8PathPoint3->setScaleX(2);
        m_points.level8PathPoint4->setScaleX(2);
        m_points.level8PathPoint5->setScaleX(2);
        m_points.level8PathPoint6->setScaleX(2);
        m_points.level8PathPoint7->setScaleX(2);
        m_points.level8PathPoint8->setScaleX(2);
        //opacty
        m_points.level8PathPoint1->setOpacity(0);
        m_points.level8PathPoint2->setOpacity(0);
        m_points.level8PathPoint3->setOpacity(0);
        m_points.level8PathPoint4->setOpacity(0);
        m_points.level8PathPoint5->setOpacity(0);
        m_points.level8PathPoint6->setOpacity(0);
        m_points.level8PathPoint7->setOpacity(0);
        m_points.level8PathPoint8->setOpacity(0);
      

        m_iLevels.level9Btn->setOpacity(0);

        m_points.level8PathPoint1->runAction(CCSequence::create(CCDelayTime::create(0.3), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level8PathPoint2->runAction(CCSequence::create(CCDelayTime::create(0.6), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level8PathPoint3->runAction(CCSequence::create(CCDelayTime::create(0.9), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level8PathPoint4->runAction(CCSequence::create(CCDelayTime::create(1.2), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level8PathPoint5->runAction(CCSequence::create(CCDelayTime::create(1.5), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level8PathPoint6->runAction(CCSequence::create(CCDelayTime::create(1.8), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level8PathPoint7->runAction(CCSequence::create(CCDelayTime::create(2.1), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level8PathPoint8->runAction(CCSequence::create(CCDelayTime::create(2.4), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));

        m_iLevels.level9Btn->setScale(1.5);
        m_iLevels.level9Btn->setVisible(true);

        Mod::get()->setSavedValue("iLevelUnlocked", 8);
        m_iLevels.level9Btn->runAction(CCSequence::create(
            CCDelayTime::create(2.7),
            CCCallFunc::create(this, callfunc_selector(GDSIslandSelectLayer::runParticle)),
            CCFadeIn::create(0.1),
            CCEaseBounceOut::create(m_scaleWithBounce2),
            nullptr
        ));
        Mod::get()->setSavedValue("islandlevel8complete", 1);
    }
    if (m_iLevels.iLevel9->m_normalPercent == 100 && m_iLevels.iLevel10->m_normalPercent == 0 && m_iLevels.level9complete == 0) {
        m_points.level9PathPoint1->setScaleY(1.2);
        m_points.level9PathPoint2->setScaleY(1.2);
        m_points.level9PathPoint3->setScaleY(1.2);
        m_points.level9PathPoint4->setScaleY(1.2);
        m_points.level9PathPoint5->setScaleY(1.2);

        m_points.level9PathPoint1->setScaleX(2);
        m_points.level9PathPoint2->setScaleX(2);
        m_points.level9PathPoint3->setScaleX(2);
        m_points.level9PathPoint4->setScaleX(2);
        m_points.level9PathPoint5->setScaleX(2);

        //opacty
        m_points.level9PathPoint1->setOpacity(0);
        m_points.level9PathPoint2->setOpacity(0);
        m_points.level9PathPoint3->setOpacity(0);
        m_points.level9PathPoint4->setOpacity(0);
        m_points.level9PathPoint5->setOpacity(0);

        m_iLevels.level10Btn->setOpacity(0);

        m_points.level9PathPoint1->runAction(CCSequence::create(CCDelayTime::create(0.3), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level9PathPoint2->runAction(CCSequence::create(CCDelayTime::create(0.6), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level9PathPoint3->runAction(CCSequence::create(CCDelayTime::create(0.9), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level9PathPoint4->runAction(CCSequence::create(CCDelayTime::create(1.2), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));
        m_points.level9PathPoint5->runAction(CCSequence::create(CCDelayTime::create(1.5), CCFadeIn::create(0.1), CCEaseBounceOut::create(m_scaleWithBounce), nullptr));

        m_iLevels.level10Btn->setScale(1.5);
        m_iLevels.level10Btn->setVisible(true);

        Mod::get()->setSavedValue("iLevelUnlocked", 9);
        m_iLevels.level10Btn->runAction(CCSequence::create(
            CCDelayTime::create(1.8),
            CCCallFunc::create(this, callfunc_selector(GDSIslandSelectLayer::runParticle)),
            CCFadeIn::create(0.1),
            CCEaseBounceOut::create(m_scaleWithBounce2),
            nullptr
        ));
        Mod::get()->setSavedValue("islandlevel9complete", 1);
    }
    if (m_iLevels.iLevel10->m_normalPercent == 100 && m_iLevels.level10complete == 0) {
        CCArray* arr = CCArray::create();
        int colour = 2;

        auto dialog1 = DialogObject::create("The Keymaster", "Well, well, well...<d020> I see you have <cg>completed</c> the <cl>first two</c> islands.", 2, 1, false, { 255,255,255 });

        auto dialog2 = DialogObject::create("The Keymaster", "Not bad,<d030> not bad at all.\n<d030>I have <co>unlocked</c> <cg>online levels</c> for you.", 2, 1, false, { 255,255,255 });

        auto dialog3 = DialogObject::create("The Keymaster", "Or maybe, if you were in <cy>Geometry Dash Island game</c>, LOL.", 2, 1, false, { 255,255,255 });

        auto dialog4 = DialogObject::create("The Keymaster", "<cl>Let's see what more you can do<d010>.<d010>.<d010>.</c>", 2, 1, false, { 255,255,255 });

        arr->addObject(dialog1);
        arr->addObject(dialog2);
        arr->addObject(dialog3);
        arr->addObject(dialog4);

        auto dl = DialogLayer::createDialogLayer(nullptr, arr, colour);
        dl->animateInRandomSide();
        dl->setZOrder(2);

        addChild(dl, 3);
        Mod::get()->setSavedValue("islandlevel10complete", 1);
    }

    return true;
}

void GDSIslandSelectLayer::runParticle() {
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto particles = CCParticleSystemQuad::create("coinPickupEffect.plist", 1);

    auto levelunlocked = Mod::get()->getSavedValue<int>("iLevelUnlocked");

    auto extendedLayer = (ExtendedLayer*)m_scrollLayer->getChildren()->objectAtIndex(0);

    auto levelsnode1 = (IslandNode*)extendedLayer->getChildren()->objectAtIndex(0);
    auto levelsmenu1 = (CCMenu*)levelsnode1->getChildren()->objectAtIndex(2);

    auto levelsnode2 = (IslandNode*)extendedLayer->getChildren()->objectAtIndex(1);
    auto levelsmenu2 = (CCMenu*)levelsnode2->getChildren()->objectAtIndex(2);

    particles->setAnchorPoint({ 0.5f, 0.5f });
    particles->setScale(0.5f);
    particles->setZOrder(3);
  
    auto circlewave = CCCircleWave::create(16.0, 30, 0.3, 0,1);
    circlewave->setAnchorPoint({ 0.5f, 0.5f });
    circlewave->setScale(0.5f);
    circlewave->setZOrder(3);

    auto circlewave2 = CCCircleWave::create(16, 80, 0.3, 1, 1);
    circlewave2->setAnchorPoint({ 0.5f, 0.5f });
    circlewave2->setScale(0.5f);
    circlewave->setZOrder(3);

    if (levelunlocked == 1) {
        particles->setPosition({ -80, -30 });
    }
    if (levelunlocked == 2) {
        particles->setPosition({ -10, 10 });
    }
    if (levelunlocked == 3) {
        particles->setPosition({ 50, -25 });
    }
    if (levelunlocked == 4) {
        particles->setPosition({ 155, -10 });
    }
    if (levelunlocked == 5) {
        particles->setPosition({ -175, -12 });
    }
    if (levelunlocked == 6) {
        particles->setPosition({ -73, -28 });
    }
    if (levelunlocked == 7) {
        particles->setPosition({ -10, 15 });
    }
    if (levelunlocked == 8) {
        particles->setPosition({ 80, -38 });
    }
    if (levelunlocked == 9) {
        particles->setPosition({ 170, -10 });
    }

    particles->init();

    if (levelunlocked >= 1 && levelunlocked <= 4) {
        levelsmenu1->addChild(particles, 2);
   
    }
    else if (levelunlocked >= 5 && levelunlocked <= 9) {
        levelsmenu2->addChild(particles, 2);
    }
    particles->addChild(circlewave, 2);
    particles->addChild(circlewave2, 2);
}

void GDSIslandSelectLayer::keyBackClicked() {
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
}

void GDSIslandSelectLayer::onIslandLevel(CCObject* sender) {
    CCMenuItemSpriteExtra* button = typeinfo_cast<CCMenuItemSpriteExtra*>(sender);
    auto GLM = GameLevelManager::sharedState();
    IslandLevel::create(level, button)->show();
}

cocos2d::ccColor3B GDSIslandSelectLayer::colorForPage(int page) {
    auto GM = GameManager::sharedState();
    int colIDs[9] = { 6, 17, 4, 9, 3, 11, 1, 3, 4 };

    return GM->colorForIdx(colIDs[page % 5]);
}

ccColor3B GDSIslandSelectLayer::getColorValue(int level, int level2, float a3) {
    float mod = (a3 * (2 / 3)) - 0.2f; // do NOT touch this line
    if (mod < 1.0f) {
        if (mod <= 0.0f)
            mod = 0.0f;
    } else mod = 1.0f;

    ccColor3B col1 = colorForPage(level);
    ccColor3B col2 = colorForPage(level2);

    ccColor3B col3 = {
    static_cast<GLubyte>((col2.r * mod) + col1.r * (1.0f - mod)),
    static_cast<GLubyte>((col2.g * mod) + col1.g * (1.0f - mod)),
    static_cast<GLubyte>((col2.b * mod) + col1.b * (1.0f - mod))
    };
    return col3;
}

void GDSIslandSelectLayer::scrollLayerMoved(CCPoint point) {
    const int pageCount = 3; 
    const float threshold = 0.7f; 

    float x = -point.x / m_fWindowWidth;
    while (x < 0.0f) {
        x += pageCount;
    }

    int ix = std::floor(x);

    float offset = x - ix;

    int firstPage = ix % pageCount;

    int lmao = firstPage + 1;
    int secondPage = lmao % pageCount;

    m_level = firstPage;

    if (std::abs(offset) > threshold) {
        ccColor3B color = getColorValue(firstPage, secondPage - 1, 12);
        m_background->setColor(color);

        ccColor3B Color1 = color;
        Color1.r = color.r * 0.8;
        Color1.g = color.g * 0.8;
        Color1.b = color.b * 0.8;

        ccColor3B Color2 = color;
        Color2.r = color.r * 0.9;
        Color2.g = color.g * 0.9;
        Color2.b = color.b * 0.9;
    }

    updatePageButtons();
}

void GDSIslandSelectLayer::onClose(CCObject*) {
    keyBackClicked();
}

void GDSIslandSelectLayer::updatePageWithObject(CCObject* page, CCObject* object) {
    if (!page || !object) {
        return;
    }

    GJGameLevel* level = static_cast<GJGameLevel*>(object);
  
    LevelPage* levelPage = typeinfo_cast<LevelPage*>(page);

    if (!levelPage) {
        return;
    }

    levelPage->updateDynamicPage(level);

}

void GDSIslandSelectLayer::onNext(CCObject*) {
    m_scrollLayer->quickUpdate();
    m_scrollLayer->moveToPage(m_level + 1);

    updatePageButtons();
}

void GDSIslandSelectLayer::onPrev(CCObject*) {
    m_scrollLayer->quickUpdate();
    m_scrollLayer->moveToPage(m_level - 1);

    updatePageButtons();
}

void GDSIslandSelectLayer::onEnterTransitionDidFinish() {
    CCLayer::onEnterTransitionDidFinish();

    if (!m_scaleWithBounce) {
        m_scaleWithBounce = CCEaseBounceOut::create(CCScaleTo::create(0.5,1, 0.5));
    }
    if (!m_scaleWithBounce2) {
        m_scaleWithBounce2 = CCEaseBounceOut::create(CCScaleTo::create(0.5,1));
    }

    // Update progression status when layer becomes active again
    updateProgressionStatus();
}

void GDSIslandSelectLayer::updatePageButtons() {
    if (m_nextPageBtn) {
        if (m_scrollLayer->m_page >= m_scrollLayer->m_pages->count() - 1) {
            m_nextPageBtn->setVisible(false);
        } else {
            m_nextPageBtn->setVisible(true);
        }
    }

    if (m_prevPageBtn) {
        if (m_scrollLayer->m_page <= 0) {
            m_prevPageBtn->setVisible(false);
        } else {
            m_prevPageBtn->setVisible(true);
        }
    }
}

void GDSIslandSelectLayer::updateProgressionStatus() {
    auto GLM = GameLevelManager::sharedState();
    
    // Reload level data to ensure we have the latest completion percentages
    m_iLevels.iLevel1 = GLM->getMainLevel(2001, false);
    m_iLevels.iLevel2 = GLM->getMainLevel(2002, false);
    m_iLevels.iLevel3 = GLM->getMainLevel(2003, false);
    m_iLevels.iLevel4 = GLM->getMainLevel(2004, false);
    m_iLevels.iLevel5 = GLM->getMainLevel(2005, false);
    m_iLevels.iLevel6 = GLM->getMainLevel(2006, false);
    m_iLevels.iLevel7 = GLM->getMainLevel(2007, false);
    m_iLevels.iLevel8 = GLM->getMainLevel(2008, false);
    m_iLevels.iLevel9 = GLM->getMainLevel(2009, false);
    m_iLevels.iLevel10 = GLM->getMainLevel(2010, false);

    // Reload completion status from saved values
    m_iLevels.level1complete = Mod::get()->getSavedValue<int>("islandlevel1complete");
    m_iLevels.level2complete = Mod::get()->getSavedValue<int>("islandlevel2complete");
    m_iLevels.level3complete = Mod::get()->getSavedValue<int>("islandlevel3complete");
    m_iLevels.level4complete = Mod::get()->getSavedValue<int>("islandlevel4complete");
    m_iLevels.level5complete = Mod::get()->getSavedValue<int>("islandlevel5complete");
    m_iLevels.level6complete = Mod::get()->getSavedValue<int>("islandlevel6complete");
    m_iLevels.level7complete = Mod::get()->getSavedValue<int>("islandlevel7complete");
    m_iLevels.level8complete = Mod::get()->getSavedValue<int>("islandlevel8complete");
    m_iLevels.level9complete = Mod::get()->getSavedValue<int>("islandlevel9complete");
    m_iLevels.level10complete = Mod::get()->getSavedValue<int>("islandlevel10complete");

    // Simple progression check - make levels visible if they should be unlocked
    if (m_iLevels.iLevel1->m_normalPercent == 100) {
        m_iLevels.level2Btn->setVisible(true);
    }
    if (m_iLevels.iLevel2->m_normalPercent == 100) {
        m_iLevels.level3Btn->setVisible(true);
    }
    if (m_iLevels.iLevel3->m_normalPercent == 100) {
        m_iLevels.level4Btn->setVisible(true);
    }
    if (m_iLevels.iLevel4->m_normalPercent == 100) {
        m_iLevels.level5Btn->setVisible(true);
    }
    if (m_iLevels.iLevel5->m_normalPercent == 100) {
        m_iLevels.level6Btn->setVisible(true);
    }
    if (m_iLevels.iLevel6->m_normalPercent == 100) {
        m_iLevels.level7Btn->setVisible(true);
    }
    if (m_iLevels.iLevel7->m_normalPercent == 100) {
        m_iLevels.level8Btn->setVisible(true);
    }
    if (m_iLevels.iLevel8->m_normalPercent == 100) {
        m_iLevels.level9Btn->setVisible(true);
    }
    if (m_iLevels.iLevel9->m_normalPercent == 100) {
        m_iLevels.level10Btn->setVisible(true);
    }
}