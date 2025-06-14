#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class IslandLevel : public geode::Popup<GJGameLevel*, CCMenuItemSpriteExtra*> {

protected:
    bool init(GJGameLevel* level, CCMenuItemSpriteExtra* button);

public:
    static IslandLevel* create(GJGameLevel* level, CCMenuItemSpriteExtra* button);
    static CCScene* scene(GJGameLevel* level, CCMenuItemSpriteExtra* button);
    bool setup(GJGameLevel* level, CCMenuItemSpriteExtra* button);
    void onPlay(CCObject* sender);
    void onInfo(CCObject*);
    void onSong(CCObject*);

    GJGameLevel* m_level;
};

