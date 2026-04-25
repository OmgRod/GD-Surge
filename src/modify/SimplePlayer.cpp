#include <Geode/Geode.hpp>
#include <Geode/modify/SimplePlayer.hpp>
#include <Utils.hpp>

using namespace geode::prelude;
using namespace surge;

class $modify(CustomSimplePlayer, SimplePlayer)
{
    void updatePlayerFrame(int iconID, IconType type)
    {
        SimplePlayer::updatePlayerFrame(iconID, type);

        surge::updateIcon(this, iconID, type, false);
    }
};
