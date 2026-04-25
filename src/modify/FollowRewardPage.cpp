#include "Geode/ui/Popup.hpp"
#include <Surge/modify/FollowRewardPage.hpp>
#include <Utils.hpp>

using namespace geode::prelude;

bool MyFollowRewardPage::init() {
    if (!FollowRewardPage::init())
        return false;

    if (auto layer = getChildByType<CCLayer*>(0)) {
        if (auto title = layer->getChildByType<CCLabelBMFont*>(0)) {
            title->setString("Follow OmgRod!");
        }
    }

    m_fields->m_rewardsPage = typeinfo_cast<RewardsPage*>(getParent());

    return true;
}

void MyFollowRewardPage::onSpecialItem(CCObject* sender) {
    auto item = typeinfo_cast<CCMenuItemSpriteExtra*>(sender);
    if (!item) {
        log::debug("onSpecialItem: Invalid item cast.");
        return;
    }

    auto gm = GameManager::sharedState();
    auto gsm = GameStatsManager::sharedState();

    m_fields->m_specialID = sender->getTag();
    log::debug("onSpecialItem: Clicked special ID {}", m_fields->m_specialID);

    std::string chestTypeStr;
    std::string unlockMessage;
    std::string actionButtonText;
    bool isUnlocked = false;

    switch (m_fields->m_specialID) {
        case 1:
            chestTypeStr = "YouTube";
            unlockMessage = "Subscribe to OmgRod on <cr>YouTube</c> to unlock this chest!";
            actionButtonText = "Sub!";
            isUnlocked = gm->getUGV("22");
            break;
        case 2:
            chestTypeStr = "Twitter";
            unlockMessage = "Follow OmgRod on <cj>Twitter</c> to unlock this chest!";
            actionButtonText = "Follow!";
            isUnlocked = gm->getUGV("24");
            break;
        case 3:
            chestTypeStr = "Facebook";
            unlockMessage = "Like OmgRod on <cb>Facebook</c> to unlock this chest!";
            actionButtonText = "Like!";
            isUnlocked = gm->getUGV("23");
            break;
        case 4:
            chestTypeStr = "Twitch";
            unlockMessage = "Follow OmgRod on <ca>Twitch</c> to unlock this chest!";
            actionButtonText = "Follow!";
            isUnlocked = gm->getUGV("26");
            break;
        case 5:
            chestTypeStr = "Discord";
            unlockMessage = "Join OmgRod on <ca>Discord</c> to unlock this chest!";
            actionButtonText = "Join!";
            isUnlocked = gm->getUGV("27");
            break;
        case 6:
            chestTypeStr = "Reddit";
            unlockMessage = "Join OmgRod on <cr>Reddit</c> to unlock this chest!";
            actionButtonText = "Join!";
            isUnlocked = gm->getUGV("32");
            break;
        default:
            log::debug("onSpecialItem: Invalid special ID {}", m_fields->m_specialID);
            return;
    }

    log::debug("onSpecialItem: ChestType = {}, isUnlocked = {}", chestTypeStr, isUnlocked);

    if (!isUnlocked) {
        log::debug("onSpecialItem: Chest not unlocked yet. Showing unlock prompt.");
        createQuickPopup(
            chestTypeStr.c_str(),
            unlockMessage,
            "Cancel",
            actionButtonText.c_str(),
            360.f,
            [&](auto layer, bool btn2) {
                if (btn2) {
                    onSpecialItemConfirm();
                }
            }
        );
    }
}

void MyFollowRewardPage::onSpecialItemConfirm() {
    auto gm = GameManager::sharedState();
    auto gsm = GameStatsManager::sharedState();

    switch (m_fields->m_specialID) {
        case 1:
            GDSFollowLinks::onYouTube();
            gm->reportAchievementWithID("geometry.ach.youtube", 100, false);
            gsm->unlockSpecialChest("22");
            gm->setUGV("22", true);
            break;
        case 2:
            GDSFollowLinks::onTwitter();
            gm->reportAchievementWithID("geometry.ach.twitter", 100, false);
            gsm->unlockSpecialChest("24");
            gm->setUGV("24", true);
            break;
        case 3:
            GDSFollowLinks::onFacebook();
            gm->reportAchievementWithID("geometry.ach.facebook", 100, false);
            gsm->unlockSpecialChest("23");
            gm->setUGV("23", true);
            break;
        case 4:
            GDSFollowLinks::onTwitch();
            gm->reportAchievementWithID("geometry.ach.twitch", 100, false);
            gsm->unlockSpecialChest("26");
            gm->setUGV("26", true);
            break;
        case 5:
            GDSFollowLinks::onDiscord();
            gm->reportAchievementWithID("geometry.ach.discord", 100, false);
            gsm->unlockSpecialChest("27");
            gm->setUGV("27", true);
            break;
        case 6:
            GDSFollowLinks::onReddit();
            gm->reportAchievementWithID("geometry.ach.reddit", 100, false);
            gsm->unlockSpecialChest("32");
            gm->setUGV("32", true);
            break;
    }
}