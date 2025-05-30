#pragma once
#include "Geode/modify/Modify.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LevelPage.hpp>

class $modify(MyLevelPage, LevelPage) {
public:
    $override
    void onInfo(CCObject* sender);
    void updateDynamicPage(GJGameLevel* level);

    void onIslands(CCObject* sender);
    void onPlay(CCObject* sender);
};