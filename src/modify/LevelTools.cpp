#include <Surge/modify/LevelTools.hpp>

using namespace geode::prelude;

bool MyLevelTools::verifyLevelIntegrity(gd::string verifyString, int levelID) {
    return true;
}

gd::string MyLevelTools::getAudioTitle(int audioID) {
    switch(audioID) {
        case -1: return "Stay Inside Me";
        case 0: return "Badland";
        case 1: return "Unstable Geometry";
        case 2: return "Tomb";
        case 3: return "Detour";
        case 4: return "The Beginning of Time";
        case 5: return "Thermodynamix";
        case 1000: return "Action Theme 07";
        default: return "";
    }
}

gd::string MyLevelTools::getAudioFileName(int audioID) {
    auto saveDir = Mod::get()->getSaveDir();
    switch(audioID) {
        case -1: return "StayInsideMe.mp3";
        case 0: return "Badland.mp3"_spr; /*(const char*)((saveDir / "songs" / "Badland.mp3").u8string().c_str());*/
        case 1: return "UnstableGeometry.mp3"_spr; /*(const char*)((saveDir / "songs" / "UnstableGeometry.mp3").u8string().c_str());*/
        case 2: return "Tomb.mp3"_spr; /*(const char*)((saveDir / "songs" / "Tomb.mp3").u8string().c_str());*/
        case 3: return "Detour.mp3"_spr; /*(const char*)((saveDir / "songs" / "Detour.mp3").u8string().c_str());*/
        case 4: return "TheBeginningOfTime.mp3"_spr; /*(const char*)((saveDir / "songs" / "TheBeginningOfTime.mp3").u8string().c_str());*/
        case 5: return "Thermodynamix.mp3"_spr; /*(const char*)((saveDir / "songs" / "Thermodynamix.mp3").u8string().c_str());*/
        case 1000: return "ActionTheme07.ogg"_spr; /*(const char*)((saveDir / "songs" / "ActionTheme07.ogg").u8string().c_str());*/
        default: return fmt::format("{}.ogg"_spr, audioID); /*(const char*)((saveDir / "songs" / fmt::format("{}.ogg", audioID)).u8string().c_str());*/
    }
}

gd::string MyLevelTools::nameForArtist(int artistID) {
    switch(artistID) {
        case 1: return "Boom Kitty";
        case 2: return "Waterflame";
        case 3: return "dj-Nate";
        case 4: return "OcularNebula";
        case 5: return "Daniel Carl";
        default: return "";
    }
}

gd::string MyLevelTools::urlForAudio(int audioID) {
    switch(audioID) {
        case -1: return "https://www.youtube.com/watch?v=5Epc1Beme90";
        case 0: return "https://www.youtube.com/watch?v=LfgzPpmjM0M";
        case 1: return "https://www.youtube.com/watch?v=8S9ZpjyrP0A";
        case 2: return "https://www.youtube.com/watch?v=k02da3gk0Yg";
        case 3: return "https://www.youtube.com/watch?v=9Q6XICGoEaM";
        case 4: return "https://www.youtube.com/watch?v=-66Vk9FqgMU";
        case 5: return "https://www.youtube.com/watch?v=QUFIGUBrN3M";
        case 1000: return "https://soundcloud.com/danny-colen/action-theme-07";
        default: return "";
    }
}

gd::string MyLevelTools::ngURLForArtist(int artistID) {
    switch(artistID) {
        case 1: return "https://boomkitty.newgrounds.com/";
        case 2: return "https://waterflame.newgrounds.com/";
        case 3: return "https://dj-nate.newgrounds.com/";
        case 4: return "https://ocularnebula.newgrounds.com/";
        default: return "";
    }
}

gd::string MyLevelTools::ytURLForArtist(int artistID) {
    switch(artistID) {
        case 1: return "https://www.youtube.com/@BoomKitty";
        case 2: return "https://www.youtube.com/@WaterflameMusic";
        case 3: return "https://www.youtube.com/@dj-Nate";
        case 4: return "https://www.youtube.com/@OcularNebula";
        default: return "";
    }
}

gd::string MyLevelTools::fbURLForArtist(int artistID) {
    switch(artistID) {
        case 2: return "https://www.facebook.com/Waterflameworkshop/";
        case 3: return "https://www.facebook.com/djnateofficial/";
        default: return "";
    }
}

int MyLevelTools::artistForAudio(int audioID) {
    switch(audioID) {
        case -1: return 4;
        case 0: return 1;
        case 1: return 2;
        case 2: return 1;
        case 3: return 1;
        case 4: return 3;
        case 5: return 3;
        case 1000: return 5;
        default: return 0;
    }
}

GJGameLevel* MyLevelTools::getLevel(int levelID, bool loaded) {
    GJGameLevel* level = GJGameLevel::create();

    switch(levelID) {
        case 1: 
            setLevelInfo(level, 4, GJDifficulty::Hard, 0);
            level->m_levelName = getAudioTitle(0);
            level->m_audioTrack = 0;
            level->m_coins = 3;
            break;
        case 2:
            setLevelInfo(level, 6, GJDifficulty::Harder, 0);
            level->m_levelName = getAudioTitle(1);
            level->m_audioTrack = 1;
            level->m_coins = 3;
            break;
        case 3:
            setLevelInfo(level, 7, GJDifficulty::Harder, 0);
            level->m_levelName = getAudioTitle(2);
            level->m_audioTrack = 2;
            level->m_coins = 3;
            break;
        case 4:
            setLevelInfo(level, 8, GJDifficulty::Insane, 0);
            level->m_levelName = getAudioTitle(3);
            level->m_audioTrack = 3;
            level->m_coins = 3;
            break;
        case 5:
            setLevelInfo(level, 5, GJDifficulty::Hard, 0);
            level->m_levelName = getAudioTitle(4);
            level->m_audioTrack = 4;
            level->m_coins = 3;
            break;
        case 6:
            setLevelInfo(level, 10, GJDifficulty::Demon, 15);
            level->m_levelName = getAudioTitle(5);
            level->m_audioTrack = 5;
            level->m_coins = 3;
            break;
        case 1001:
            setLevelInfo(level, 6, GJDifficulty::Harder, 0);
            level->m_levelName = getAudioTitle(1000);
            level->m_audioTrack = 1000;
            level->m_coins = 0;
            break;
        case 2001:
            setLevelInfo(level, 2, GJDifficulty::Normal, 0);
            level->m_levelName = "The Factory";
            level->m_audioTrack = -1;
            level->m_coins = 3;
            break;
        case 2002:
            setLevelInfo(level, 3, GJDifficulty::Normal, 0);
            level->m_levelName = "The Woods";
            level->m_audioTrack = -1;
            level->m_coins = 3;
            break;
        case 2003:
            setLevelInfo(level, 4, GJDifficulty::Normal, 0);
            level->m_levelName = "The Complex";
            level->m_audioTrack = -1;
            level->m_coins = 3;
            break;
        case 2004:
            setLevelInfo(level, 5, GJDifficulty::Normal, 0);
            level->m_levelName = "The Storage";
            level->m_audioTrack = -1;
            level->m_coins = 3;
            break;
        case 2005:
            setLevelInfo(level, 6, GJDifficulty::Normal, 0);
            level->m_levelName = "The Ship";
            level->m_audioTrack = -1;
            level->m_coins = 3;
            break;
        case 2006:
            setLevelInfo(level, 2, GJDifficulty::Normal, 0);
            level->m_levelName = "Dockline";
            level->m_audioTrack = -1;
            level->m_coins = 3;
            break;
        case 2007:
            setLevelInfo(level, 3, GJDifficulty::Normal, 0);
            level->m_levelName = "Cargo Bay";
            level->m_audioTrack = -1;
            level->m_coins = 3;
            break;
        case 2008:
            setLevelInfo(level, 4, GJDifficulty::Normal, 0);
            level->m_levelName = "Slipstream";
            level->m_audioTrack = -1;
            level->m_coins = 3;
            break;
        case 2009:
            setLevelInfo(level, 5, GJDifficulty::Normal, 0);
            level->m_levelName = "Overpass";
            level->m_audioTrack = -1;
            level->m_coins = 3;
            break;
        case 2010:
            setLevelInfo(level, 6, GJDifficulty::Normal, 0);
            level->m_levelName = "Terminal Drift";
            level->m_audioTrack = -1;
            level->m_coins = 3;
            break;
        case -1:
            setLevelInfo(level, 3, GJDifficulty::NA, 0);
            level->m_levelName = "THE END is NEaR";
            level->m_audioTrack = -1;

    }
    if (!loaded) {
        level->m_levelString = LocalLevelManager::sharedState()->getMainLevelString(levelID);
    }
    level->m_levelID = levelID;
    level->m_levelType = GJLevelType::Saved;
    return level;
}

void MyLevelTools::setLevelInfo(GJGameLevel* level, int stars, GJDifficulty difficulty, int coinsRequired) {
    level->m_stars = stars;
    level->m_difficulty = difficulty;
    level->m_requiredCoins = coinsRequired;
}