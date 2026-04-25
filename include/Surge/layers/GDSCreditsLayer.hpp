#include <Geode/Geode.hpp>
using namespace geode::prelude;

class GDSCreditsLayer : public CCLayer {
public:
    bool init();
    static CCScene* scene();
    static GDSCreditsLayer* create();
    void keyBackClicked();
    void backWrapper(CCObject* sender);
    void onExit();
};