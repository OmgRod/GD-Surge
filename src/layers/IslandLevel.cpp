#include <Geode/Geode.hpp>
#include <Surge/layers/IslandLevel.hpp>
#include <Surge/layers/GDSIslandSelectLayer.h>

using namespace geode::prelude;

bool IslandLevel::init(GJGameLevel* level, CCMenuItemSpriteExtra* button) {
    if (!Popup::init(300.f, 260.f)) return false;

    if (!level) {
        log::error("Level is null in IslandLevel::init");
        return false;
    }
    m_level = level;

    if (!m_level->m_levelName.empty()) {
        setTitle(m_level->m_levelName);
    } else {
        setTitle("Unnamed Level");
    }

    setID("IslandLevel"_spr);

    auto GLM = GameLevelManager::sharedState();
    if (!m_mainLayer || m_mainLayer->getChildren()->count() == 0) {
        log::error("Main layer or its children are invalid in IslandLevel::init");
        return false;
    }

    auto BG = typeinfo_cast<CCScale9Sprite*>(m_mainLayer->getChildren()->objectAtIndex(0));
    if (!BG) {
        log::error("Failed to cast BG in IslandLevel::init");
        return false;
    }

    auto m_buttonMenu = CCMenu::create();
    auto corner1 = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();
    corner1->setPosition(BG->getPosition());
    corner1->setRotation(180);
    m_mainLayer->addChild(corner1);

    auto corner2 = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
    corner2->setPosition(BG->getPosition());
    corner2->setRotation(90);
    m_mainLayer->addChild(corner2);

    auto corner3 = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
    corner3->setPosition(BG->getPosition());
    corner3->setRotation(270);
    m_mainLayer->addChild(corner3);

    auto corner4 = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
    corner4->setPosition(BG->getPosition());
    
    corner1->setPositionX(corner1->getPositionX() + 125.45);
    corner1->setPositionY(corner1->getPositionY() + 105.1);
    
    corner2->setPositionX(corner2->getPositionX() - 125.45);
    corner2->setPositionY(corner2->getPositionY() + 105.1);
    
    corner3->setPositionX(corner3->getPositionX() + 125.45);
    corner3->setPositionY(corner3->getPositionY() - 105.1);
    
    corner4->setPositionX(corner4->getPositionX() - 125.45);
    corner4->setPositionY(corner4->getPositionY() - 105.1);

    CCMenu* infoMenu = CCMenu::create();
    CCSprite* info = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
    CCMenuItemSpriteExtra* infoBtn = CCMenuItemSpriteExtra::create(info, this, menu_selector(IslandLevel::onInfo));

    infoBtn->setTag(button->getTag());
    infoMenu->addChild(infoBtn);
    infoMenu->setPosition(BG->getPosition());
    infoMenu->setPositionX(infoMenu->getPositionX() + 146.5);
    infoMenu->setPositionY(infoMenu->getPositionY() + 126.1);
    info->setTag(button->getTag());
    infoMenu->setTag(button->getTag());
    m_mainLayer->addChild(infoMenu, 2);
    m_mainLayer->addChild(corner4);

    m_mainLayer->addChild(m_buttonMenu);

    int levelID = 2000 + button->getTag();
    m_level = GLM->getMainLevel(levelID, true);
    m_level->m_levelString = LocalLevelManager::sharedState()->getMainLevelString(levelID);

    auto songSprite = CCSprite::createWithSpriteFrameName("GJ_playMusicBtn_001.png");
    songSprite->setScale(0.75f);
    auto songBtn = CCMenuItemSpriteExtra::create(
        songSprite,
        button,
        menu_selector(IslandLevel::onSong)
    );
    songBtn->setPosition({ 300.f, 0.f });
    m_buttonMenu->addChild(songBtn);

    auto playBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png"), this, menu_selector(IslandLevel::onPlay));
    playBtn->setPosition({ BG->getPositionX(), BG->getPositionY() + 35.f });

    m_buttonMenu->addChild(playBtn);
    m_buttonMenu->setPositionX(0.f);
    m_buttonMenu->setPositionY(0.f);

    //Normal mode progress bar
    int per = 100;
    std::vector<int> normalPer(per, 0);

    std::vector<int> completePer(m_level->m_normalPercent, 100);

    auto levelVector = normalPer;
    auto completedVector = completePer;

    //progress bar
    auto bar = CCSprite::create("GJ_progressBar_001.png");
    bar->setScale(0.7f);
    bar->setPosition(BG->getPosition());
    bar->setPositionX(bar->getPositionX());
    bar->setPositionY(bar->getPositionY() - 153.5);
    bar->setColor({ 0, 0, 0 });
    bar->setOpacity(125);
    bar->setZOrder(1);
    bar->setID("progress-bar-normal"_spr);

    m_mainLayer->addChild(bar);

    float size = (float)completedVector.size() / (float)levelVector.size();

    auto status = CCLabelBMFont::create(fmt::format("{}%", completedVector.size(), levelVector.size()).c_str(), "bigFont.fnt");
    status->setPosition({ bar->getPosition() });
    status->limitLabelWidth(170, .7f, .3f);
    status->setScale(0.4f);
    status->setZOrder(2);
    status->setID("status"_spr);
    status->setPositionY(status->getPositionY() + 108);
    m_mainLayer->addChild(status);


    auto normal = CCLabelBMFont::create("Normal Mode", "bigFont.fnt");
    normal->setPosition(status->getPosition());
    normal->setID("normal"_spr);

    normal->setPositionY(normal->getPositionY() + 20);
    normal->setScale(0.4f);
    m_mainLayer->addChild(normal);

    auto progress = CCSprite::create("GJ_progressBar_001.png");
    progress->setColor({ 0,255,0 });
    progress->setScaleX(0.985f);
    progress->setScaleY(0.860f);
    progress->setOpacity(255);
    bar->addChild(progress);
    bar->setPositionY(bar->getPositionY() + 108);
    progress->setAnchorPoint({ 0.f,0.5f });
    progress->setPosition({ 2.5f, 10.f });
    progress->setID("progress-bar-internal"_spr);

    CCRect progressRect = progress->getTextureRect();
    progressRect.size.width *= size;
    progress->setTextureRect(progressRect);

    //practice progress bar

    int pper = 100;
    std::vector<int> pnormalPer(pper, 0);

    std::vector<int> pcompletePer(m_level->m_practicePercent, 100);

    auto plevelVector = pnormalPer;
    auto pcompletedVector = pcompletePer;

    //progress bar
    auto pbar = CCSprite::create("GJ_progressBar_001.png");
    pbar->setScale(0.7f);
    pbar->setPosition(BG->getPosition());

    pbar->setPositionX(pbar->getPositionX());
    pbar->setPositionY(pbar->getPositionY() - 150.5);
    pbar->setColor({ 0, 0, 0 });
    pbar->setOpacity(125);
    pbar->setZOrder(1);
    pbar->setID("progress-bar"_spr);

    m_mainLayer->addChild(pbar);

    float psize = (float)pcompletedVector.size() / (float)plevelVector.size();

    auto pstatus = CCLabelBMFont::create(fmt::format("{}%", pcompletedVector.size(), plevelVector.size()).c_str(), "bigFont.fnt");
    pstatus->setPosition({ pbar->getPosition() });
    pstatus->limitLabelWidth(170, .7f, .3f);
    pstatus->setScale(0.4f);
    pstatus->setZOrder(2);
    pstatus->setID("practice status"_spr);
    pstatus->setPositionY(pstatus->getPositionY() + 58);
    m_mainLayer->addChild(pstatus);


    auto practice = CCLabelBMFont::create("Practice Mode", "bigFont.fnt");
    practice->setPosition(pstatus->getPosition());
    practice->setID("practice"_spr);

    practice->setPositionY(practice->getPositionY() + 20);
    practice->setScale(0.4f);
    m_mainLayer->addChild(practice);

    auto pprogress = CCSprite::create("GJ_progressBar_001.png");
    pprogress->setColor({ 0,255,255 });
    pprogress->setScaleX(0.985f);
    pprogress->setScaleY(0.860f);
    pprogress->setOpacity(255);
    pbar->addChild(pprogress);
    pbar->setPositionY(pbar->getPositionY() + 58);
    pprogress->setAnchorPoint({ 0.f,0.5f });
    pprogress->setPosition({ 2.5f, 10.f });
    pprogress->setID("progress-bar-internal"_spr);

    CCRect pprogressRect = pprogress->getTextureRect();
    pprogressRect.size.width *= psize;
    pprogress->setTextureRect(pprogressRect);

    std::string starspr = "";

    if (m_level->isPlatformer()) {
        if (m_level->m_normalPercent == 100) {
            starspr = "GJ_starsIcon_001.png";
        } else {
            starspr = "GJ_starsIcon_gray_001.png";
        }
    } else {
        if (m_level->m_normalPercent == 100) {
            starspr = "GJ_moonsIcon_001.png";
        } else {
            starspr = "GJ_moonsIcon_gray_001.png"_spr;
        }
    }

    float starWidth = 0;
    float spaceBetweenStars = 35.0f;

    float totalWidth = m_level->m_stars * (starWidth * 0.65) + (m_level->m_stars - 1) * spaceBetweenStars;

    float startX = BG->getPositionX() - totalWidth / 2;

    float startY = (BG->getPositionY()) - 113;

    float currentX = startX;

    for (int i = 0; i < m_level->m_stars; ++i) {
        auto star = CCSprite::createWithSpriteFrameName(starspr.c_str());

        star->setPosition({ currentX, startY });
        star->setScale(0.65);

        m_mainLayer->addChild(star);

        currentX += (starWidth * 0.65) + spaceBetweenStars;
    }

    log::debug("Stars: {}", m_level->m_stars);

    return true;
}

IslandLevel* IslandLevel::create(GJGameLevel* level, CCMenuItemSpriteExtra* button) {
    auto ret = new IslandLevel();
    if (ret && ret->init(level, button)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

CCScene* IslandLevel::scene(GJGameLevel* level, CCMenuItemSpriteExtra* button) {
    auto scene = CCScene::create();
    auto popup = IslandLevel::create(level, button);
    if (popup)
        scene->addChild(popup);
    return scene;
}

void IslandLevel::onPlay(CCObject* sender) {
    if (!m_level) {
        log::debug("Error: m_level is null!");
        return;
    }

	auto currentScene = CCDirector::sharedDirector()->getRunningScene();

    CCMenuItemSpriteExtra* button = typeinfo_cast<CCMenuItemSpriteExtra*>(sender);
    auto GLM = GameLevelManager::sharedState();
    auto playLayer = PlayLayer::scene(m_level, false, false);
    FMODAudioEngine::sharedEngine()->playEffect("playSound_01.ogg"_spr /*std::filesystem::path(Mod::get()->getSaveDir() / "sfx" / "playSound_01.ogg").string()*/);

    CCDirector::get()->pushScene(CCTransitionFade::create(0.5f, playLayer));
}

void sLOLwshow2(GJGameLevel* level212) {
    if (level212 == nullptr) return;

    if (level212->m_levelID >= 0) {
        std::string name = level212->m_levelName;
        std::string contentStream = fmt::format(
            "<cy>{}</c>\n"
            "<cg>Total Attempts</c>: {}\n"
            "<cl>Total Jumps</c>: {}\n"
            "<cp>Normal</c>: {}%\n"
            "<co>Practice</c>: {}%",
            name,
            level212->m_attempts,
            level212->m_jumps,
            level212->m_normalPercent,
            level212->m_practicePercent
        );

        FLAlertLayer::create(nullptr, "Level Stats", contentStream, "OK", nullptr, 360)->show();
        return;
    } else {
        FLAlertLayer::create("hmm..", "something seems <cr>SUS</c> here...", "ikr")->show();
    }
}

void IslandLevel::onInfo(CCObject* sender) {
    auto GLM = GameLevelManager::sharedState();
    auto level = GLM->getMainLevel(m_level->m_levelID, true);
    sLOLwshow2(level);
}

void IslandLevel::onSong(CCObject* sender) {
    // if (!m_level) return;
    // SongInfoLayer::create(m_level->m_songID)->show();
    SongInfoLayer::create(1)->show();
}