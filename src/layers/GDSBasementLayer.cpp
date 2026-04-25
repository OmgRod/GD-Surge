#include <Surge/layers/GDSBasementLayer.hpp>
#include <Surge/layers/GDSCreditsLayer.hpp>
#include <DialogCallback.hpp>

void GDSBasementLayer::keyBackClicked() {
    GDSBasementLayer::onExit(nullptr);
}

bool GDSBasementLayer::init() {
    if (!CCLayer::init()) return false;

    auto director = CCDirector::sharedDirector();
	auto winSize = director->getWinSize();

    auto background = createLayerBG();
    background->setColor({ 60, 0, 60 });
    addChild(background, -1);

	auto misc = CCMenu::create();
	addChild(misc);

	m_pButtonMenu = CCMenu::create();
	addChild(m_pButtonMenu);

	m_obNext = ccp(0.0f, 75.0f);

	auto backBtn = CCMenuItemSpriteExtra::create(
		CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
		this,
		menu_selector(GDSBasementLayer::onExit)
	);
	backBtn->setPosition((-winSize.width / 2) + 25.0f, (winSize.height / 2) - 25.0f);
	misc->addChild(backBtn);

	auto title = CCLabelBMFont::create("The Basement", "goldFont.fnt");
	title->setPosition(winSize.width / 2, winSize.height / 2 + 130.0f);
	title->setScale(1.2f);
	addChild(title);

	addButton("GDS_playBtn_001.png"_spr, "Secret Level", menu_selector(GDSBasementLayer::onSecretLevel));
	addButton("GDS_homeBtn_001.png"_spr, "Home..?", menu_selector(GDSBasementLayer::onScratchDialog));
	addButton("GDS_questBtn_001.png"_spr, "Credits", menu_selector(GDSBasementLayer::onCredits));

	m_bButtonsEntered = false;

	setKeypadEnabled(true);

	runSequentialFadeIn();

    return true;
}

GDSBasementLayer* GDSBasementLayer::create() {
    auto layer = new GDSBasementLayer();
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

CCScene* GDSBasementLayer::scene() {
    auto scene = CCScene::create();
    auto layer = GDSBasementLayer::create();
    scene->addChild(layer);
    return scene;
}

void GDSBasementLayer::onExit(CCObject*) {
	GameManager::sharedState()->fadeInMusic("menuLoop.mp3");
	CCDirector::sharedDirector()->popSceneWithTransition(0.5f, kPopTransitionFade);
}

void GDSBasementLayer::addButton(const char* node, const char* text, SEL_MenuHandler callback) {
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    float padding = 1.25f;

    auto btn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName(node),
        this,
        callback
    );
    btn->setPosition(m_obNext.x - 150.0f, m_obNext.y);

    btn->setOpacity(0);

    m_pButtonMenu->addChild(btn);

    auto label = CCLabelBMFont::create(text, "bigFont.fnt");
    label->setAnchorPoint({ 0.f, 0.f });
    label->setPosition(m_obNext.x - 120.0f, m_obNext.y - 10.0f);
    label->setScale(0.7f);
    label->setOpacity(0);
    m_pButtonMenu->addChild(label);

    m_vButtonLabelPairs.push_back({ btn, label });
    m_obNext.y -= 45.0f * padding;
}

void GDSBasementLayer::runSequentialFadeIn() {
    float delay = 0.0f;

    for (auto& pair : m_vButtonLabelPairs) {
        auto btn = pair.first;
        auto label = pair.second;

        btn->runAction(CCSequence::create(
            CCDelayTime::create(delay),
            CCFadeTo::create(0.5f, 255),
            nullptr
        ));

        label->runAction(CCSequence::create(
            CCDelayTime::create(delay),
            CCFadeTo::create(0.5f, 255),
            nullptr
        ));

        delay += 0.5f;
    }
}

void GDSBasementLayer::onSecretLevel(CCObject*) {
    auto level = GJGameLevel::create();
    level->m_levelID = 1001;
    level->m_levelName = "The Gauntlet";
    level->m_audioTrack = 1000;
    level->m_levelString = LocalLevelManager::sharedState()->getMainLevelString(1001);
    level->m_stars = 8;
    level->m_difficulty = GJDifficulty::Insane;
    auto scene = PlayLayer::scene(level, false, false);
    auto transition = CCTransitionFade::create(0.5f, scene);
    CCDirector::sharedDirector()->pushScene(transition);
}

void GDSBasementLayer::onCredits(CCObject*) {
    auto scene = GDSCreditsLayer::scene();
    auto transition = CCTransitionFade::create(0.5f, scene);
    CCDirector::sharedDirector()->pushScene(transition);
}

void GDSBasementLayer::onScratchDialog(CCObject*) {
    static std::vector<std::pair<std::string, int>> dialogLines = {
        { "Uhh... hello?", 13 },
        { "What are you doing <cr>here</c>..?", 26 },
        { "Erm.. <s50> HELLO..?</s>", 11 },
        { "Are you even listening to me?", 14 },
        { "Seriously, stop clicking.", 14 },
        { "I'm warning you.", 11 },
        { "<cr>Stop it.</c>", 14 },
        { "<cr><s100>GET OUT OF HERE!</s></c>", 14 },
        { "This is my place, you know.", 12 },
        { "Why are you in my house?", 13 },
        { "Did you get lost or something?", 11 },
        { "You can't just walk in here!", 11 },
        { "Please, just leave my house.", 14 },
        { "I'm not kidding. Go away.", 14 },
        { "Fine, stay if you want... But it's still <cp>my</c> house.", 10 }
    };

    const auto& [line, frame] = dialogLines[m_dialogIndex];

    CCArray* objects = CCArray::create();
    objects->addObject(DialogObject::create("Scratch", line.c_str(), frame, 1.0f, false, ccWHITE));

    m_dialogIndex = (m_dialogIndex + 1) % dialogLines.size();

    auto dialog = DialogLayer::createWithObjects(objects, 2);
    dialog->addToMainScene();
    dialog->animateInRandomSide();

    auto* del = new DialogCallback();
    dialog->addChild(del);
    del->autorelease();
    del->m_callback = []() {};
    dialog->m_delegate = del;
}
