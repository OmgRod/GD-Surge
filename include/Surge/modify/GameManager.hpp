#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>

class $modify(MyGameManager, GameManager) {
    bool isIconUnlocked(int _id, IconType _type);
    bool isColorUnlocked(int _id, UnlockType _type);

    int countForType(IconType icon);

    void returnToLastScene(GJGameLevel* p0);
};