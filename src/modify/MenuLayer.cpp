#include <Surge/modify/MenuLayer.hpp>
#include <Geode/utils/file.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/loader/Event.hpp>
#include <Surge/layers/GDSCreditsLayer.hpp>
#include <Utils.hpp>

float speed = 1.0f;
float delaySetting = 0.0f;
float addtlDuration = 0.0f;

bool stopLooping = false;
bool jumpedAlready = false;

bool downloadStarted = false;
bool startup = false;

static auto activeListeners = std::make_shared<std::vector<std::shared_ptr<async::TaskHolder<web::WebResponse>>>>();

bool MyMenuLayer::init() {
    if (!MenuLayer::init()) return false;

    auto socialMenu = getChildByID("social-media-menu");
    if (socialMenu) {
        auto button = socialMenu->getChildByID("robtop-logo-button");
        if (button) {
            auto sprite = button->getChildByType<CCSprite*>(0);
            if (sprite) {
                sprite->setDisplayFrame(CCSpriteFrameCache::get()->spriteFrameByName("omgrodLogo_01.png"_spr));
                sprite->setScale(0.55f);
            }
        }
    }

    auto logo = getChildByID("main-title");
    auto spriteLogo = typeinfo_cast<CCSprite*>(logo);
    if (spriteLogo && !(Loader::get()->getLoadedMod("ninxout.redash"))) {
        CCSprite* surgeLogo = CCSprite::createWithSpriteFrameName("surgeLogo_001.png"_spr);
        surgeLogo->setID("surge-logo");
        CCRect logoBounds = spriteLogo->boundingBox();
        surgeLogo->setAnchorPoint({1.0f, 1.0f});
        surgeLogo->setPosition(ccp(logoBounds.getMaxX() - 2.f, logoBounds.getMinY() - 1.5f));
        addChild(surgeLogo);

        std::string nodeChosenByYAMM = "this-mod-doesnt-assign-node-ids-to-anything-lmfao"_spr;

        auto fodsAnimMod = Loader::get()->getLoadedMod("raydeeux_hjfod.fodsmenuanimations");

        if (fodsAnimMod && fodsAnimMod->getSettingValue<bool>("enabled") &&
            (!(!surgeLogo->getID().empty() && surgeLogo->getID() == nodeChosenByYAMM))) {

            float animSpeed = std::clamp(speed, 0.01f, 16.0f);
            float animDelay = std::clamp(delaySetting, 0.0f, 10.0f);
            float animDuration = std::clamp(addtlDuration, 0.0f, 2.0f);

            CCDelayTime* delay = CCDelayTime::create((0.25f / animSpeed) + animDelay);
            CCEaseBackOut* eboScale = CCEaseBackOut::create(CCScaleTo::create((2.0f / animSpeed) + animDuration, 1.f));
            CCSequence* titleSequence = CCSequence::create(delay, eboScale, nullptr);

            surgeLogo->setScale(0.f);
            surgeLogo->runAction(titleSequence);
        }
    }

    if (!Mod::get()->getSettingValue<bool>("disable-warning-popup") && !startup) {
        scheduleOnce(SEL_SCHEDULE(&MyMenuLayer::onStartupPopup), 0.1f);
    }

    /*

    if (!downloadStarted) {
        downloadStarted = true;

        static EventListener<web::WebTask> s_listener;
        auto listURL = "https://raw.githubusercontent.com/OmgRod/GD-Surge/refs/heads/master/music/download.txt";

        log::debug("Starting fetch of music download list from {}", listURL);

        web::WebRequest request;
        auto listTask = request.get(listURL);

        s_listener.setFilter(listTask);
        s_listener.bind([=](web::WebTask::Event* e) {
            if (!e || e->isCancelled()) {
                log::warn("Music list download task was cancelled or null");
                geode::Notification::create("Download was cancelled", NotificationIcon::Error)->show();
                return;
            }

            if (web::WebResponse* res = e->getValue()) {
                log::debug("Received response for music list. Status code: {}", res->code());

                if (res->code() != 200) {
                    log::warn("Failed to fetch download list. Status: {}", res->code());
                    geode::Notification::create("Failed to fetch download list.", NotificationIcon::Error)->show();
                    return;
                }

                auto listContent = res->string();
                std::istringstream stream(listContent.unwrap());
                std::string line;

                auto mod = Mod::get();
                if (!mod) {
                    log::error("Mod instance is null");
                    return;
                }

                auto baseURL = "https://raw.githubusercontent.com/OmgRod/GD-Surge/refs/heads/master/music/";
                auto saveDir = mod->getSaveDir();

                log::debug("Parsed download list. Base URL: {}, Save Dir: {}", baseURL, saveDir.string());

                std::vector<std::string> filesToDownload;
                while (std::getline(stream, line)) {
                    if (!line.empty()) filesToDownload.push_back(line);
                }

                if (filesToDownload.empty()) {
                    geode::Notification::create("No files to download.", NotificationIcon::Info)->show();
                    return;
                }

                auto remaining = std::make_shared<std::atomic<int>>(filesToDownload.size());

                for (const auto& fileLine : filesToDownload) {
                    std::string fullURL = baseURL + fileLine;
                    auto savePath = saveDir / fileLine;

                    // Skip if file already exists
                    if (std::filesystem::exists(savePath)) {
                        log::info("File already exists, skipping: {}", fileLine);
                        if (--(*remaining) == 0) {
                            geode::Notification::create("All songs downloaded!", NotificationIcon::Success)->show();
                        }
                        continue;
                    }

                    std::error_code ec;
                    std::filesystem::create_directories(savePath.parent_path(), ec);
                    if (ec) {
                        log::warn("Failed to create directory for {}: {}", fileLine, ec.message());
                        if (--(*remaining) == 0) {
                            geode::Notification::create("All songs downloaded!", NotificationIcon::Success)->show();
                        }
                        continue;
                    }

                    web::WebRequest* fileRequest = new web::WebRequest();
                    auto fileTask = fileRequest->get(fullURL);

                    auto fileListener = std::make_shared<EventListener<web::WebTask>>();
                    fileListener->setFilter(fileTask);

                    fileListener->bind([fileListener, savePath, fileLine, remaining](web::WebTask::Event* fe) {
                        if (!fe || fe->isCancelled()) {
                            log::warn("Download cancelled: {}", fileLine);
                        } else if (web::WebResponse* fres = fe->getValue()) {
                            log::debug("Download completed for {}. Status: {}", fileLine, fres->code());

                            if (fres->code() != 200) {
                                log::warn("Failed to download {}: status code {}", fileLine, fres->code());
                            } else {
                                auto data = fres->data();
                                if (!geode::utils::file::writeBinary(savePath, data)) {
                                    log::warn("Failed to write file {}", savePath.string());
                                } else {
                                    log::info("Downloaded and saved: {}", fileLine);
                                }
                            }
                        }

                        if (--(*remaining) == 0) {
                            geode::Notification::create("All songs downloaded!", NotificationIcon::Success)->show();
                        }
                    });
                }

                geode::Notification::create("Music and SFX download started!", NotificationIcon::Success)->show();
                log::debug("All file download tasks scheduled.");
            } else {
                log::error("List response event had no response value");
            }
        });
    }


    */

    startup = true;

    std::string currentPath = FMODAudioEngine::sharedEngine()->m_fmodMusic[1].m_filePath;
    if (currentPath.find("menuLoop.mp3") == std::string::npos) {
        queueInMainThread([=]() {
            FMODAudioEngine::sharedEngine()->playMusic(
                "menuLoop.mp3",
                true,
                0.f,
                0
            );
        });
    }

    return true;
}

void MyMenuLayer::onCreator(CCObject* sender) {
#ifdef GITHUB_ACTIONS
    FLAlertLayer::create("Creator", "This feature is <cr>disabled</c>. To <cg>enable</c> it, please disable this mod. Sorry for the inconvenience.", "OK")->show();
#else
    MenuLayer::onCreator(sender);
#endif
}

void MyMenuLayer::onStartupPopup(float dt) {
    auto mod = Mod::get();
    auto tag = mod->getVersion().getTag();
    bool isAlpha = mod->getVersion().toVString(true).find("alpha") != std::string::npos;

    std::string message;
    if (isAlpha) {
        message =
            "1. This mod is currently in <co>alpha</c>. Bugs and instability are expected. "
            "Please report any issues on our <cy>[GitHub issue tracker](https://github.com/OmgRod/GD-Surge/issues)</c>.\n\n"
            "2. Surge uses a separate save file, so your original data is safe. "
            "However, we recommend backing up your original save just in case. "
            "To restore your original save, simply disable this mod.\n\n"
            "You may disable this popup in the mod settings.\n\n"
            "Thank you for trying Surge!";
    } else {
        message =
            "Surge uses a separate save file, so your original data is safe. "
            "However, we recommend backing up your original save just in case. "
            "To restore your original save, simply disable this mod.\n\n"
            "You may disable this popup in the mod settings.\n\n"
            "Thank you for trying Surge!";
    }

    MDPopup::create("Warning", message, "OK")->show();
}

void MyMenuLayer::onTwitch(CCObject* sender) {
    GDSFollowLinks::onTwitch();
}

void MyMenuLayer::onTwitter(CCObject* sender) {
    GDSFollowLinks::onTwitter();
}

void MyMenuLayer::onDiscord(CCObject* sender) {
    GDSFollowLinks::onDiscord();
}

void MyMenuLayer::onFacebook(CCObject* sender) {
    GDSFollowLinks::onFacebook();
}

void MyMenuLayer::onRobTop(CCObject* sender) {
    GDSFollowLinks::onRobTop();
}

void MyMenuLayer::onYouTube(CCObject* sender) {
    GDSFollowLinks::onYouTube();
}

// void MyMenuLayer::onMoreGames(CCObject* sender) {
//     auto scene = GDSCreditsLayer::scene();
//     auto transition = CCTransitionFade::create(0.5f, scene);
//     CCDirector::sharedDirector()->pushScene(transition);
// }
