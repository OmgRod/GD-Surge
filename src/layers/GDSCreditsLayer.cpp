#include "Geode/ui/General.hpp"
#include <Surge/layers/GDSCreditsLayer.hpp>

void GDSCreditsLayer::keyBackClicked() {
    GameManager::sharedState()->fadeInMenuMusic();
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
}

bool GDSCreditsLayer::init() {
    if (!CCLayer::init()) return false;

    setKeypadEnabled(true);

    FMODAudioEngine::sharedEngine()->playMusic("CreditsTheme.ogg"_spr, false, 0.1f, 0);

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto menu = CCMenu::create();
    menu->setPosition({ 0.f, 0.f });
    menu->setAnchorPoint({ 0.f, 0.f });
    addChild(menu);

    auto background = createLayerBG();
    background->setPosition({ -5.f, -5.f });
    addChild(background, -1);
    addSideArt(this, SideArt::Bottom, SideArtStyle::Layer, false);

    auto backButton = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(GDSCreditsLayer::backWrapper)
    );
    backButton->setPosition({ 25, winSize.height - 25 });
    menu->addChild(backButton);

    auto containerNode = CCNode::create();
    containerNode->setPosition({ 0.f, 0.f - winSize.height });
    addChild(containerNode);

    auto gdLogo = CCSprite::createWithSpriteFrameName("GJ_logo_001.png");
    gdLogo->setPosition({ winSize.width / 2, winSize.height * 0.8f });
    containerNode->addChild(gdLogo);

    auto surgeLogo = CCSprite::createWithSpriteFrameName("surgeLogo_001.png"_spr);
    CCRect logoBounds = gdLogo->boundingBox();
    surgeLogo->setAnchorPoint({ 1.0f, 1.0f });
    surgeLogo->setPosition(ccp(logoBounds.getMaxX() - 2.f, logoBounds.getMinY() - 1.5f));
    containerNode->addChild(surgeLogo);

    struct CreditEntry {
        std::string text;
        bool isTitle;
    };

    std::vector<CreditEntry> credits = {
        {"Programmers", true},
        {"Lead Developer - OmgRod", false},
        {"GD Lunar and Odyssey code - Capeling", false},
        {"Bindings - hiimjasmine00, OmgRod & TimeStepYT", false},
        {"Original GD World code - BitZ", false},
        {"Art Design", true},
        {"OmgRod", false},
        {"Alphalaneous", false},
        {"Icons", true},
        {"MobMasterMind", false},
        {"Levels - Classic", true},
        {"Badland by OmgRod", false},
        {"Unstable Geometry by OmgRod", false},
        {"Tomb by OmgRod", false},
        {"Detour by ____", false},
        {"Beginning of Time by flingus", false},
        {"Thermodynamix by OmgRod", false},
        {"Levels - Islands", true},
        {"The Factory by MobMasterMind", false},
        {"The Woods by MobMasterMind", false},
        {"The Complex by MobMasterMind", false},
        {"The Storage by MobMasterMind", false},
        {"The Ship by MobMasterMind", false},
        {"Dockline by MobMasterMind", false},
        {"Cargo Bay by MobMasterMind", false},
        {"Slipstream by MobMasterMind", false},
        {"Overpass by MobMasterMind", false},
        {"Terminal Drift by MobMasterMind", false},
        {"Songs", true},
        {"Badland by Boom Kitty", false},
        {"Unstable Geometry by Waterflame", false},
        {"Tomb by Boom Kitty", false},
        {"Detour by Boom Kitty", false},
        {"The Beginning of Time by dj-Nate", false},
        {"Thermodynamix by dj-Nate", false},
        {"Random Song 03 by RobTop", false},
        {"Action Theme 07 by Daniel Carl", false},
        {"Stay Inside Me by OcularNebula (credits song)", false},
        {"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false}, {"", false},
        {"Special thanks to RobTop", false},
        {"for creating Geometry Dash!", false}
    };

    float labelY = winSize.height * 0.5f;

    for (const auto& entry : credits) {
        if (entry.text.empty()) {
            labelY -= 40.f; // Spacer
            continue;
        }

        auto label = CCLabelBMFont::create(entry.text.c_str(), "bigFont.fnt");
        label->setAnchorPoint({ 0.5f, 1.f });
        label->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
        label->setPosition({ winSize.width / 2.f, labelY });

        float scale = entry.isTitle ? 1.f : 0.5f;
        label->setScale(scale);
        containerNode->addChild(label);

        float spacing = entry.isTitle
            ? (label->getContentSize().height + 16.0f)
            : (label->getContentSize().height * 0.5f + 4.0f);

        labelY -= spacing;
    }

    float totalHeight = 0.f;

    for (size_t i = 0; i < credits.size(); ++i) {
        const auto& entry = credits[i];
        if (entry.text.empty()) {
            totalHeight += 20.f;
            continue;
        }

        float scale = entry.isTitle ? 1.f : 0.5f;

        auto tempLabel = CCLabelBMFont::create(entry.text.c_str(), "bigFont.fnt");
        float labelHeight = tempLabel->getContentSize().height * scale;

        float spacing = 0.f;
        if (entry.isTitle) {
            spacing = labelHeight + 16.0f;
        } else {
            if (i + 1 < credits.size() && credits[i + 1].isTitle) {
                spacing = labelHeight + 32.0f;
            } else {
                spacing = labelHeight + 6.0f;
            }
        }

        totalHeight += spacing;
    }

    auto moveAction = CCMoveTo::create(100.f, { 0.f, winSize.height + totalHeight });
    auto callBack = CCCallFunc::create(this, callfunc_selector(GDSCreditsLayer::keyBackClicked));
    auto sequence = CCSequence::create(moveAction, callBack, NULL); // callback won't work - known issue
    containerNode->runAction(sequence);

    return true;
}

GDSCreditsLayer* GDSCreditsLayer::create() {
    auto layer = new GDSCreditsLayer();
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

CCScene* GDSCreditsLayer::scene() {
    auto scene = CCScene::create();
    auto layer = GDSCreditsLayer::create();
    scene->addChild(layer);
    return scene;
}

void GDSCreditsLayer::backWrapper(CCObject* sender) {
    keyBackClicked();
}

void GDSCreditsLayer::onExit() {
    CCLayer::onExit();
}