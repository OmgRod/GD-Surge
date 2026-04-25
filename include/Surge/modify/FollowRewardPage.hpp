#include <Geode/Geode.hpp>
#include <Geode/modify/FollowRewardPage.hpp>

using namespace geode::prelude;

class $modify(MyFollowRewardPage, FollowRewardPage) {
public:
    bool init();
    void onSpecialItem(CCObject* sender);
    void onSpecialItemConfirm();
    struct Fields {
        int m_specialID;
        RewardsPage* m_rewardsPage;
    };
};