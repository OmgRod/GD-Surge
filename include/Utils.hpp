#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class GDSFollowLinks {
public:
    static void onTwitch() {
        CCApplication::sharedApplication()->openURL("https://www.twitch.tv/omgrod1000");
    }

    static void onTwitter() {
        CCApplication::sharedApplication()->openURL("https://x.com/0mgrod");
    }

    static void onDiscord() {
        CCApplication::sharedApplication()->openURL("https://discord.gg/vK3DuqJwyW");
    }

    static void onFacebook() {
        FLAlertLayer::create("nope", "i'm not a boomer", "OK")->show();
    }

    static void onYouTube() {
        CCApplication::sharedApplication()->openURL("https://www.youtube.com/@OmgRodYT");
    }

    static void onReddit() {
        CCApplication::sharedApplication()->openURL("https://www.reddit.com/r/omgrod/");
    }

    static void onRobTop() {
        CCApplication::sharedApplication()->openURL("https://omgrod.me/");
    }
};

// Orbs code by Prevter
// (currently useless tho)

namespace surge {
    inline int getTotalOrbsForLevel(GJGameLevel* level, int levelID) {
        return GameStatsManager::get()->getBaseCurrencyForLevel(level);
    }

    inline int getCurrentOrbsForLevel(GJGameLevel* level, int levelID) {
        auto gsm = GameStatsManager::get();
        auto totalOrbs = getTotalOrbsForLevel(level, levelID);
        auto dailyId = level->m_dailyID.value();

        cocos2d::CCDictionary* currencyScores;
        if (dailyId <= 0) {
            if (level->m_levelType == GJLevelType::Saved) {
                currencyScores = gsm->m_mainCurrencyScores;
            } else if (level->m_gauntletLevel) {
                currencyScores = gsm->m_gauntletCurrencyScores;
            } else {
                currencyScores = gsm->m_onlineCurrencyScores;
            }
            dailyId = levelID;
        } else {
            currencyScores = gsm->m_timelyCurrencyScores;
        }

        auto& str = currencyScores->valueForKey(fmt::to_string(dailyId))->m_sString;
        if (str.empty()) return 0;
        if (auto res = geode::utils::numFromString<int>(str)) {
            auto resValue = res.unwrap();
            if (resValue >= 100) return totalOrbs * 1.25;
            return std::floor(totalOrbs * (resValue / 100.f));
        }
        return 0;
    }
    inline bool isIconCustom(int id, IconType type) {
        if (id > 485 && type == IconType::Cube)
            return true;
        if (id > 169 && type == IconType::Ship)
            return true;
        if (id > 118 && type == IconType::Ball)
            return true;
        if (id > 149 && type == IconType::Ufo)
            return true;
        if (id > 96 && type == IconType::Wave)
            return true;
        if (id > 68 && type == IconType::Robot)
            return true;
        if (id > 69 && type == IconType::Spider)
            return true;
        if (id > 43 && type == IconType::Swing)
            return true;
        if (id > 8 && type == IconType::Jetpack)
            return true;
        if (id > 17 && type == IconType::Item)
            return true;
        return false;
    }

    inline std::vector<std::string> getPlayerFrames(int iconID, IconType type) {
        std::string iconName;
        switch (type)
        {
        case IconType::Ship:
            iconName = "ship";
            break;
        case IconType::Ball:
            iconName = "player_ball";
            break;
        case IconType::Ufo:
            iconName = "bird";
            break;
        case IconType::Wave:
            iconName = "dart";
            break;
        case IconType::Robot:
            iconName = "robot";
            break;
        case IconType::Spider:
            iconName = "spider";
            break;
        case IconType::Swing:
            iconName = "swing";
            break;
        case IconType::Jetpack:
            iconName = "jetpack";
            break;
        default:
            iconName = "player";
            break;
        }

        std::string frame1 = fmt::format("{}_{:02}_001.png"_spr, iconName, iconID);
        std::string frame2 = fmt::format("{}_{:02}_2_001.png"_spr, iconName, iconID);
        std::string frameExtra = fmt::format("{}_{:02}_extra_001.png"_spr, iconName, iconID);
        std::string frameGlow = fmt::format("{}_{:02}_glow_001.png"_spr, iconName, iconID);
        std::string frameDome = fmt::format("{}_{:02}_3_001.png"_spr, iconName, iconID);

        return {frame1, frame2, frameExtra, frameGlow, frameDome};
    }

    inline void updateIcon(CCNode *player, int iconID, IconType type, bool isPlayerObject) {
        if (!isIconCustom(iconID, type))
            return;

        if (type == IconType::Robot || type == IconType::Spider)
            return;

        auto frameCache = CCSpriteFrameCache::get();
        auto frameDict = frameCache->m_pSpriteFrames;

        auto frames = getPlayerFrames(iconID, type);
        auto frame1Texture = frames[0];
        auto frame2Texture = frames[1];
        auto extraTexture = frames[2];
        auto glowTexture = frames[3];
        gd::string domeTexture = frames[4];

        CCSprite *firstLayer;
        CCSprite *secondLayer;
        CCSprite *extraLayer;
        CCSprite *glowLayer;
        GJRobotSprite *robotSprite;
        CCSprite *ufoDome;

        if (isPlayerObject)
        {
            auto obj = static_cast<PlayerObject *>(player);

            firstLayer = obj->m_iconSprite;
            secondLayer = obj->m_iconSpriteSecondary;
            extraLayer = obj->m_iconSpriteWhitener;
            glowLayer = obj->m_iconGlow;
            robotSprite = obj->m_robotSprite;

            if (type == IconType::Ship || type == IconType::Jetpack || type == IconType::Ufo)
            {
                firstLayer = obj->m_vehicleSprite;
                secondLayer = obj->m_vehicleSpriteSecondary;
                extraLayer = obj->m_vehicleSpriteWhitener;
                glowLayer = obj->m_vehicleGlow;
            }

            if (type == IconType::Ufo)
                ufoDome = obj->m_birdVehicle;
        }
        else
        {
            auto obj = static_cast<SimplePlayer *>(player);

            firstLayer = obj->m_firstLayer;
            secondLayer = obj->m_secondLayer;
            extraLayer = obj->m_detailSprite;
            glowLayer = obj->m_outlineSprite;
            robotSprite = obj->m_robotSprite;

            if (type == IconType::Ufo)
                ufoDome = obj->m_birdDome;
        }

        if (frameDict->objectForKey(frame1Texture))
        {
            firstLayer->setDisplayFrame(frameCache->spriteFrameByName(frame1Texture.c_str()));
        }

        if (frameDict->objectForKey(frame2Texture))
        {
            secondLayer->setDisplayFrame(frameCache->spriteFrameByName(frame2Texture.c_str()));
            secondLayer->setPosition(firstLayer->getContentSize() / 2);
        }

        if (frameDict->objectForKey(extraTexture))
        {
            extraLayer->setVisible(true);
            extraLayer->setDisplayFrame(frameCache->spriteFrameByName(extraTexture.c_str()));
            extraLayer->setPosition(firstLayer->getContentSize() / 2);
        }
        else
            extraLayer->setVisible(false);

        if (frameDict->objectForKey(glowTexture))
        {
            glowLayer->setDisplayFrame(frameCache->spriteFrameByName(glowTexture.c_str()));
            if (!isPlayerObject)
                glowLayer->setPosition(firstLayer->getContentSize() / 2);
        }

        if (type == IconType::Ufo)
        {
            if (frameDict->objectForKey(domeTexture))
            {
                ufoDome->setDisplayFrame(frameCache->spriteFrameByName(domeTexture.c_str()));
                ufoDome->setPosition(firstLayer->getContentSize() / 2);
            }
        }
    }
}