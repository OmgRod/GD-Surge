#include <DialogCallback.hpp>
#include <Surge/modify/SecretLayer.hpp>
#include <Surge/layers/GDSBasementLayer.hpp>

using namespace geode::prelude;

// Static member definitions
int MySecretLayer::lastIndex = -1;

std::vector<std::string> MySecretLayer::messages = {
    "What are you poking around for?",
    "Don't you have better things to do?",
    "There is no spoo",
    "I should have hid this room better...",
    "You're not supposed to be in here...",
    "RubRub won't like this...",
    "Don't touch that",
    "Why U touch my stuff?",
    "RubRub better not find you in here...",
    "Can't you just leave?",
    "This is not the room you are looking for...",
    "Sneaky sneaky...",
    "It's my precious...",
    "You shall not pass!",
    "Don't push the button!",
    "You're gonna get me in trouble...",
    "This is getting ridiculus...",
    "Go collect some stars",
    "Maybe there are new levels?",
    "Just, stop bothering me",
    "I'm gonna stop talking",
    "You're hopeless...",
    "Really, still here?",
    "Fine, press the button",
    "How did you get in here?!",
    "I'm gonna sleep now... ZzZzZzzZzZzZzZzZzZzZz",
    "You're STILL here?!",
    "Why not just leave??",
    "Why not start counting levels?",
    "Fine, you win. You may press the button.",
    "Did RubRub send you? No? Even worse.",
    "This place is off-limits, capisce?",
    "You again? What now?",
    "Great, another button masher.",
    "Touch anything and I scream.",
    "What do you even want from me?",
    "You can't keep doing this forever.",
    "Snooping detected.",
    "This is classified nonsense, go away.",
    "RubRub secured this room for a reason!",
    "You're like a bad penny...",
    "Still haven't found the exit, huh?",
    "You must be bored out of your mind.",
    "At this point I admire your persistence.",
    "No secrets here. Go bother someone else.",
    "You want answers? Wrong vault.",
    "You're gonna trigger something bad!",
    "I'm not responsible for what happens next.",
    "Hey! My stuff!",
    "This is my space, not a public park.",
    "Maybe a spider will scare you away...",
    "I'm running out of ways to say 'go away'.",
    "This isn't a therapy session.",
    "Do I LOOK like I know anything?",
    "You're making me nervous...",
    "You're going to mess everything up!",
    "Maybe RubRub wants me to suffer...",
    "If I say the code, will you leave?",
    "I'm about to lose it, seriously.",
    "Touch that again and I'll bite.",
    "You're poking the wrong corner, buddy.",
    "No Easter Eggs here. Only regret.",
    "I've seen things... like YOU coming back again.",
    "Wanna hear a secret? Too bad.",
    "I told you to stop, didn't I?",
    "Why must you poke the void?",
    "You're opening things you shouldn't be touching.",
    "RubRub warned me about people like you.",
    "Back! Back, foul intruder!",
    "This vault is cursed. Just sayin'.",
    "You think this is a game? …oh wait.",
    "You're giving me actual anxiety.",
    "Stop it. Just stop it.",
    "The walls aren't listening, but I am.",
    "Even the icons are judging you.",
    "You're about to unlock... disappointment.",
    "If this is about the stars, I don't have them.",
    "This is why we can't have nice secret rooms.",
    "I knew hiding it behind a fake wall wasn't enough.",
    "Do you even know what you're looking for?",
    "Knock knock. Who's there? NOT YOU.",
    "404: Entry denied.",
    "This isn't what RubRub meant by 'exploration'.",
    "Do you feel accomplished yet?",
    "I had dreams once… then you showed up.",
    "There's no treasure. Just me. And you. Unfortunately.",
    "Hey look, it's you again… joy.",
    "This isn't a chatroom.",
    "Your curiosity is... irritating.",
    "Keep pressing and see what happens. I dare you.",
    "One more press and I walk out.",
    "I should charge rent for how often you visit.",
    "You won't find anything. Except my resentment.",
    "What if I told you this room was a fake?",
    "You're wasting your time here.",
    "Guess who doesn't want you here? Me.",
    "The password is... haha no.",
    "RubRub's gonna hear about this!",
    "This is a certified no-touch zone.",
    "Why do you hurt me this way?",
    "Back so soon? I was almost happy.",
    "If I rolled my eyes harder, I'd see my brain.",
    "I miss when this place was quiet.",
    "Your presence here is... statistically unfortunate.",
    "You just HAD to touch the weird-looking wall.",
    "Oh sure, come in, press things, ignore warnings.",
    "Do you even know how many rules you're breaking?",
    "You press things like you're trying to get a prize.",
    "Go away or I'll start rhyming.",
    "If you're trying to unlock something, try not being annoying.",
    "I swear, I had sanity before you arrived.",
    "Stop. Think. Then leave.",
    "This is the definition of trespassing.",
    "You've already found all the secrets. Probably.",
    "What are you expecting, applause?",
    "No codes, no cookies, no hope.",
    "My patience level is lower than your star count.",
    "I bet you're proud of yourself, huh?",
    "Maybe if I ignore you, you'll vanish.",
    "Still pushing buttons like it's gonna change things.",
    "Ever heard of boundaries?",
    "I've been here since 2.0 and you're still annoying.",
    "I could be napping right now.",
    "There's nothing here but disappointment.",
    "Careful, you're gonna cause problems.",
    "If I had emotions, they'd be tired.",
    "Oh cool, you again. Yay.",
    "This vault is empty. Like your inbox.",
    "The more you poke, the more I question everything.",
    "Congratulations. You've unlocked... absolutely nothing."
};

std::vector<MySecretLayer::VaultCode> MySecretLayer::vaultCodes = {
    VaultCode{
        "badland",
        []() {
            auto array = CCArray::create();
            array->addObject(CCString::create("Where the journey starts anew"));
            array->addObject(CCString::create("You think you're him? That's kinda cute."));
            array->addObject(CCString::create("Darkness stirs, but you're no ghost"));
            array->addObject(CCString::create("The first path, not the final boast"));
            return array;
        },
        []() -> bool { return !(AchievementManager::sharedState()->isAchievementEarned("geometry.ach.surge.vault01")); },
        []() -> const char* {
            return "Do I look like the Wraith?";
        },
        [](MySecretLayer* self) {
            GameManager::sharedState()->reportAchievementWithID("geometry.ach.surge.vault01", 100, false);
        }
    },    
    VaultCode{
        "i am robtop",
        []() {
            auto array = CCArray::create();
            array->addObject(CCString::create("Still poking? Have some popcorn."));
            array->addObject(CCString::create("I'm the dev, and I'm watching."));
            array->addObject(CCString::create("Throwing popcorn, entertained."));
            array->addObject(CCString::create("Here's the code - don't mess up."));
            array->addObject(CCString::create("It's clear. Just think a bit."));
            array->addObject(CCString::create("Say my name. Escape awaits."));
            return array;
        },
        []() -> bool { return !(AchievementManager::sharedState()->isAchievementEarned("geometry.ach.surge.vault02")); },
        []() -> const char* {
            return "no you're not...";
        },
        [](MySecretLayer* self) {
            GameManager::sharedState()->reportAchievementWithID("geometry.ach.surge.vault02", 100, false);
        }
    },
    VaultCode{
        "the basement",
        []() {
            auto array = CCArray::create();
            array->addObject(CCString::create("Beneath the floor, secrets reside."));
            array->addObject(CCString::create("Locked away, out of sight, out of mind."));
            array->addObject(CCString::create("A room below, where whispers dwell."));
            array->addObject(CCString::create("Find the hidden path, descend the stair."));
            array->addObject(CCString::create("Name the place where shadows meet."));
            array->addObject(CCString::create("Say its name, and the door will greet."));
            return array;
        },
        []() -> bool {
            return !(AchievementManager::sharedState()->isAchievementEarned("geometry.ach.surge.vault03"))
                && !(Mod::get()->getSavedValue<bool>("basement-unlocked"));
        },
        []() -> const char* {
            return "Come in...";
        },
        [](MySecretLayer* self) {
            GameManager::sharedState()->reportAchievementWithID("geometry.ach.surge.vault03", 50, false);
            Mod::get()->setSavedValue("basement-unlocked", true);
            auto menu = self->getChildByID("basement-menu");
            if (menu) {
                auto btn = menu->getChildByID("basement-button");
                CCEaseIn* ease = CCEaseIn::create(CCScaleTo::create(0.2f, 1.f), 0.5f);
                btn->setScale(0.f);
                btn->setVisible(true);
                btn->runAction(ease);
                menu->updateLayout();
            }
        }
    },
    VaultCode{
        "shattered",
        []() {
            auto array = CCArray::create();
            array->addObject(CCString::create("Once a page stood, a future untold"));
            array->addObject(CCString::create("But cracks began, the story unfolds"));
            array->addObject(CCString::create("Beneath the surface, secrets break free"));
            array->addObject(CCString::create("What remains is a vision lost, shattered to be"));
            return array;
        },
        []() -> bool { return !(AchievementManager::sharedState()->isAchievementEarned("geometry.ach.surge.vault04")); },
        []() -> const char* {
            auto formatted = fmt::format("The final truth, only for you to see, {}", GameManager::sharedState()->m_playerName).c_str();
            return formatted;
        },
        [](MySecretLayer* self) {
            GameManager::sharedState()->reportAchievementWithID("geometry.ach.surge.vault04", 100, false);
        }
    }    
};

std::unordered_map<std::string, int> MySecretLayer::riddleProgress;

bool MySecretLayer::init() {
    if (!SecretLayer::init()) return false;

    FMODAudioEngine::sharedEngine()->playMusic("secretLoop.mp3", true, 0.1f, 0);

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto menu = CCMenu::create();
    menu->setPosition({ winSize.width * 0.95f, winSize.height * 0.5f });
    menu->setContentSize({ winSize.width * 0.1f, winSize.height * 0.95f });
    menu->setID("basement-menu");

    auto layout = SimpleAxisLayout::create(Axis::Column);
    layout->setMainAxisAlignment(MainAxisAlignment::End);
    layout->setMainAxisScaling(AxisScaling::None);
    // layout->setAutoScale(false);
    // layout->setAxisAlignment(AxisAlignment::Center);
    menu->setLayout(layout);

    addChild(menu);

    auto basementIcon = CCSprite::createWithSpriteFrameName("secretDoorBtn2_open_001.png");
    basementIcon->setScale(0.5f);
    auto basementBtn = CCMenuItemSpriteExtra::create(
        basementIcon,
        menu,
        menu_selector(MySecretLayer::onBasement)
    );
    basementBtn->setVisible(false);
    basementBtn->setID("basement-button");
    menu->addChild(basementBtn);

    if (Mod::get()->getSavedValue<bool>("basement-unlocked")) {
        basementBtn->setVisible(true);
    }

    menu->updateLayout();

    if (!Mod::get()->getSavedValue<bool>("vault-open-message")) {
        m_searchInput->setTouchEnabled(false);
        m_submitButton->setEnabled(false);
        runAction(
            CCSequence::create(
                CCDelayTime::create(1.5f),
                CCCallFunc::create(this, callfunc_selector(MySecretLayer::showEntryDialog)),
                nullptr
            )
        );               
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int index;
    do {
        index = std::rand() % messages.size();
    } while (index == lastIndex && messages.size() > 1);

    lastIndex = index;

    m_messageLabel->setString(messages[index].c_str());
    m_messageLabel->setColor({ 255, 255, 255 });

    m_searchInput->setAllowedChars(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");

    return true;
}

void MySecretLayer::onSubmit(CCObject* sender) {
    std::string input = m_searchInput->getString();
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (const VaultCode& vaultCode : vaultCodes) {
        if (input == vaultCode.code && vaultCode.condition()) {
            m_messageLabel->setString(vaultCode.successText());
            m_messageLabel->setColor({ 0, 255, 0 });

            vaultCode.onSuccess(this);

            m_fields->isRiddle = false;
            m_fields->selectedRiddleIndex = -1;
            m_fields->currentRiddleIndex = 0;
            m_fields->normalMessages = 0;

            return;
        }
    }

    bool showedMessage = false;

    if (m_fields->normalMessages > 10)
        m_fields->isRiddle = true;

    if (m_fields->isRiddle) {
        if (m_fields->selectedRiddleIndex == -1) {
            std::vector<int> validIndices;
            for (int i = 0; i < vaultCodes.size(); ++i) {
                if (vaultCodes[i].condition()) {
                    validIndices.push_back(i);
                }
            }

            if (!validIndices.empty()) {
                int randomPick = std::rand() % validIndices.size();
                m_fields->selectedRiddleIndex = randomPick;
                m_fields->currentRiddleIndex = 0;
            } else {
                m_fields->isRiddle = false;
                m_fields->selectedRiddleIndex = -1;
                m_fields->currentRiddleIndex = 0;
            }
        }

        if (m_fields->isRiddle && m_fields->selectedRiddleIndex != -1) {
            VaultCode& selectedVaultCode = vaultCodes[m_fields->selectedRiddleIndex];
            CCArray* riddles = selectedVaultCode.riddle();

            if (riddles && riddles->count() > 0) {
                CCString* riddleString = (CCString*)riddles->objectAtIndex(m_fields->currentRiddleIndex);
                m_messageLabel->setString(riddleString->getCString());
                m_messageLabel->setColor({ 0, 255, 255 });

                m_fields->currentRiddleIndex++;

                if (m_fields->currentRiddleIndex >= riddles->count()) {
                    m_fields->isRiddle = false;
                    m_fields->normalMessages = 1;
                    m_fields->selectedRiddleIndex = -1;
                    m_fields->currentRiddleIndex = 0;
                }

                showedMessage = true;
            }
        }
    }

    if (!showedMessage) {
        m_fields->normalMessages++;
        int index;
        do {
            index = std::rand() % messages.size();
        } while (index == lastIndex && messages.size() > 1);

        lastIndex = index;

        m_messageLabel->setString(messages[index].c_str());
        m_messageLabel->setColor({ 255, 255, 255 });
    }
}

void MySecretLayer::showEntryDialog() {
    CCArray* objects = CCArray::create();
    objects->addObject(DialogObject::create("The Guard", "Wait a minute<d020>.<d020>.<d100> When did <cr>I</c> allow visitors?", 1, 1.0f, false, ccWHITE));
    objects->addObject(DialogObject::create("The Guard", "This <cg>hidden vault</c> is not for the curious...", 1, 1.0f, false, ccWHITE));
    objects->addObject(DialogObject::create("The Guard", "You've <co>ignored</c> the warnings<d050>...<d050> I should <cy>throw</c> you out.", 1, 1.0f, false, ccWHITE));
    objects->addObject(DialogObject::create("The Guard", "<cl>Rules</c> exist for a reason...", 1, 1.0f, false, ccWHITE));
    objects->addObject(DialogObject::create("The Guard", "But perhaps<d050>...<d050> you have earned a glimpse.", 1, 1.0f, false, ccWHITE));
    objects->addObject(DialogObject::create("The Guard", "Tread carefully<d030>.<d030>.<d030> I will be watching.", 1, 1.0f, true, ccWHITE));

    auto dialog = DialogLayer::createWithObjects(objects, 1);
    dialog->addToMainScene();
    dialog->animateInRandomSide();

    std::function<void()> secretCallback = [&]() {
        Mod::get()->setSavedValue<bool>("vault-open-message", true);
        m_searchInput->setTouchEnabled(true);
        m_submitButton->setEnabled(true);
    };

    auto* del = new DialogCallback();
    dialog->addChild(del);
    del->autorelease();
    del->m_callback = secretCallback;
    dialog->m_delegate = del;
}

void MySecretLayer::onBasement(CCObject* sender) {
    // auto level = GJGameLevel::create();
    // level->m_levelID = 1001;
    // level->m_levelName = "The basement";
    // level->m_audioTrack = 1000;
    // level->m_levelString = LocalLevelManager::sharedState()->getMainLevelString(1001);
    // level->m_stars = 8;
    // level->m_difficulty = GJDifficulty::Insane;
    // auto scene = PlayLayer::scene(level, false, false);
    // auto transition = CCTransitionFade::create(0.5f, scene);
    // CCDirector::sharedDirector()->pushScene(transition);

    auto scene = GDSBasementLayer::scene();
    auto transition = CCTransitionFade::create(0.5f, scene);
    CCDirector::sharedDirector()->pushScene(transition);
}