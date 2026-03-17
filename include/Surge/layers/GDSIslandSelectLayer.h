#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

struct LevelPoints {
	CCSprite* level1PathPoint1;
	CCSprite* level1PathPoint2;
	CCSprite* level1PathPoint3;
	CCSprite* level1PathPoint4;
	CCSprite* level1PathPoint5;
	
	CCSprite* level2PathPoint1;
	CCSprite* level2PathPoint2;
	CCSprite* level2PathPoint3;
	CCSprite* level2PathPoint4;
	CCSprite* level2PathPoint5;
	
	CCSprite* level3PathPoint1;
	CCSprite* level3PathPoint2;
	CCSprite* level3PathPoint3;
	CCSprite* level3PathPoint4;
	CCSprite* level3PathPoint5;
	
	CCSprite* level4PathPoint1;
	CCSprite* level4PathPoint2;
	CCSprite* level4PathPoint3;
	CCSprite* level4PathPoint4;
	CCSprite* level4PathPoint5;
	
	CCSprite* level5PathPoint1;
	CCSprite* level5PathPoint2;
	CCSprite* level5PathPoint3;
	CCSprite* level5PathPoint4;
	CCSprite* level5PathPoint5;
	
	CCSprite* level6PathPoint1;
	CCSprite* level6PathPoint2;
	CCSprite* level6PathPoint3;
	CCSprite* level6PathPoint4;
	CCSprite* level6PathPoint5;
	
	CCSprite* level7PathPoint1;
	CCSprite* level7PathPoint2;
	CCSprite* level7PathPoint3;
	CCSprite* level7PathPoint4;
	CCSprite* level7PathPoint5;
	
	CCSprite* level8PathPoint1;
	CCSprite* level8PathPoint2;
	CCSprite* level8PathPoint3;
	CCSprite* level8PathPoint4;
	CCSprite* level8PathPoint5;
	CCSprite* level8PathPoint6;
	CCSprite* level8PathPoint7;
	CCSprite* level8PathPoint8;
	
	CCSprite* level9PathPoint1;
	CCSprite* level9PathPoint2;
	CCSprite* level9PathPoint3;
	CCSprite* level9PathPoint4;
	CCSprite* level9PathPoint5;
	
	CCSprite* level10PathPoint1;
	CCSprite* level10PathPoint2;
	CCSprite* level10PathPoint3;
	CCSprite* level10PathPoint4;
	CCSprite* level10PathPoint5;
};

struct GDSIslandLevel {
	GJGameLevel* iLevel1;
	GJGameLevel* iLevel2;
	GJGameLevel* iLevel3;
	GJGameLevel* iLevel4;
	GJGameLevel* iLevel5;
	GJGameLevel* iLevel6;
	GJGameLevel* iLevel7;
	GJGameLevel* iLevel8;
	GJGameLevel* iLevel9;
	GJGameLevel* iLevel10;

	CCMenuItemSpriteExtra* level1Btn;
	CCMenuItemSpriteExtra* level2Btn;
	CCMenuItemSpriteExtra* level3Btn;
	CCMenuItemSpriteExtra* level4Btn;
	CCMenuItemSpriteExtra* level5Btn;
	CCMenuItemSpriteExtra* level6Btn;
	CCMenuItemSpriteExtra* level7Btn;
	CCMenuItemSpriteExtra* level8Btn;
	CCMenuItemSpriteExtra* level9Btn;
	CCMenuItemSpriteExtra* level10Btn;

	int level1complete;
	int level2complete;
	int level3complete;
	int level4complete;
	int level5complete;
	int level6complete;
	int level7complete;
	int level8complete;
	int level9complete;
	int level10complete;
};

class GDSIslandSelectLayer : public CCLayer, public BoomScrollLayerDelegate, public DynamicScrollDelegate {
public:
    GJGroundLayer* m_ground;
    CCSprite* m_background;
    CCArray* m_mainLevels;
    CCArray* m_levelPages;
    BoomScrollLayer* m_scrollLayer;
	float m_fWindowWidth;
    int m_level;
	CCMenuItemSpriteExtra* m_nextPageBtn;
	CCMenuItemSpriteExtra* m_prevPageBtn;
	GJGameLevel* level;
	LevelPoints m_points;
	GDSIslandLevel m_iLevels;
	CCEaseBounceOut* m_scaleWithBounce = CCEaseBounceOut::create(CCScaleTo::create(0.5,1, 0.5));
	CCEaseBounceOut* m_scaleWithBounce2 = CCEaseBounceOut::create(CCScaleTo::create(0.5, 1));

	ccColor3B colorForPage(int);
	ccColor3B getColorValue(int, int, float);
	bool init(int page);
	void onClose(CCObject*);
	void onPrev(CCObject*);
	void onNext(CCObject*);
	void onBack(CCObject*);
	void keyBackClicked() override;
	void onIslandLevel(CCObject* sender);
	void runParticle();
	void scrollLayerMoved(CCPoint) override;
	void keyDown(int);
	void updateColors();
	static GDSIslandSelectLayer* create(int page);
	static CCScene* scene(int page);
	void updatePageWithObject(CCObject* page, CCObject* object) override;
	void onEnterTransitionDidFinish() override;
	void updatePageButtons();
	void updateProgressionStatus();
};