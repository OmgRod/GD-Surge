#include <Geode/Geode.hpp>
using namespace geode::prelude;

class GDSBasementLayer : public CCLayer {
protected:
	CCPoint m_obNext;
	CCMenu* m_pButtonMenu;
	bool m_bButtonsEntered;
    
    std::vector<std::pair<CCNode*, CCNode*>> m_vButtonLabelPairs;
    void runSequentialFadeIn();
    
	void onExit(CCObject*);
	void addButton(const char* node, const char* text, SEL_MenuHandler callback);
    
public:
    size_t m_dialogIndex = 0;

    bool init();
    static CCScene* scene();
    static GDSBasementLayer* create();
    void keyBackClicked();
    void backWrapper(CCObject* sender);

    void onSecretLevel(CCObject* sender);
    void onCredits(CCObject* sender);

    void onScratchDialog(CCObject* sender);
};