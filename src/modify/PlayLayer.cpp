#include <Surge/modify/PlayLayer.hpp>

void MyPlayLayer::levelComplete() {
    auto levelID = m_level->m_levelID;

    if (levelID == 1001 && !m_isPracticeMode) {
        GameManager::sharedState()->reportAchievementWithID("geometry.ach.surge.vault03", 100, false);
    }

    PlayLayer::levelComplete();
}

// void MyPlayLayer::onQuit() {
//     FMODAudioEngine::sharedEngine()->stopAllMusic(true);
//     FMODAudioEngine::sharedEngine()->playMusic("menuLoop.mp3", true, 0.1f, 0);
//     CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
// }

void MyPlayLayer::showHint() {
    log::info("{} is bad at the game", GameManager::sharedState()->m_playerName);
}