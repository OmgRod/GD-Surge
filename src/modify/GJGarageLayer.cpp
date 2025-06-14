#include <Surge/modify/GJGarageLayer.hpp>

using namespace geode::prelude;

bool MyGJGarageLayer::init() {
    if (!GJGarageLayer::init())
        return false;
    
    auto menu = getChildByID("top-left-menu");
    menu->getChildByID("shop-button")->getChildByType<CCSprite*>(0)->setDisplayFrame(CCSpriteFrameCache::get()->spriteFrameByName("GDS_shopRope.png"_spr));

    if (auto shardsMenu = getChildByID("shards-menu")) {
        if (auto shardsButton = shardsMenu->getChildByID("shards-button")) {
            shardsButton->setVisible(false);
        }
        shardsMenu->updateLayout();
    }

    return true;
}

void MyGJGarageLayer::showUnlockPopup(int p0, UnlockType p1) {
    ItemInfoPopup::create(p0, p1)->show();
}

void MyGJGarageLayer::onShop(CCObject* sender) {
    auto shop = GJShopLayer::scene(ShopType{5});
    auto transition = CCTransitionMoveInT::create(0.5f, shop);
    CCDirector::sharedDirector()->replaceScene(transition);
}