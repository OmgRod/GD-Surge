#include <Geode/Geode.hpp>
#include "AchievementManager.hpp"
#include "Geode/modify/AchievementManager.hpp"

using namespace geode::prelude;

void MyAchievementManager::addManualAchievements() {
    AchievementManager::addAchievement("geometry.ach.level01a", "Not Bad", "Completed 'Badland' in Practice mode", "Complete 'Badland' in Practice mode", "icon_09", 1);
    AchievementManager::addAchievement("geometry.ach.level01b", "All Bad", "Completed 'Badland' in Normal mode", "Complete 'Badland' in Normal mode", "icon_05", 1);
    AchievementManager::addAchievement("geometry.ach.surge.levelcoin01", "Ultimate Badland", "Collected all 3 Secret Coins on \'Badland\'", "Collect all 3 Secret Coins on \'Badland\'", "icon_06", 0);

    AchievementManager::addAchievement("geometry.ach.surge.vault01", "Why??", "Entered code \'Badland\' in The Vault", "A secret is required", "icon_28", 0);
    AchievementManager::addAchievement("geometry.ach.surge.vault02", "I'm not RobTop", "Entered code \'I am RobTop\' in The Vault", "A secret is required", "icon_485", 0);
    AchievementManager::addAchievement("geometry.ach.surge.vault03", "The Gauntlet", "Complete The Guard's special quest", "A secret is required", "icon_30", 0);
    // AchievementManager::addAchievement("geometry.ach.surge.vault04", "Why??", "Of all codes, why \'Badland\'??", "A secret is required", "ship_02", 0);
    // AchievementManager::addAchievement("geometry.ach.surge.vault05", "Why??", "Of all codes, why \'Badland\'??", "A secret is required", "color_17", 0);

    AchievementManager::addAchievement("geometry.ach.demon01", "Reflex Champion", "Completed a Demon difficulty level in Normal mode", "Complete a Demon difficulty level in Normal mode", "icon_35", 1);

    AchievementManager::addAchievement("geometry.ach.coins01", "Coins?!", "Collected 5 Secret Coins", "Collect 5 Secret Coins", "icon_31", 1);
    AchievementManager::addAchievement("geometry.ach.coins02", "Maybe behind that block?", "Collected 10 Secret Coins", "Collect 10 Secret Coins", "ball_04", 1);
    AchievementManager::addAchievement("geometry.ach.coins03", "I.. Need... MORE!", "Collected 15 Secret Coins", "Collect 15 Secret Coins", "color2_16", 1);
    AchievementManager::addAchievement("geometry.ach.coins04", "We wants it!", "Collected 20 Secret Coins", "Collect 20 Secret Coins", "bird_03", 1);
    AchievementManager::addAchievement("geometry.ach.coins05", "We needs it!", "Collected 25 Secret Coins", "Collect 25 Secret Coins", "icon_32", 1);
    AchievementManager::addAchievement("geometry.ach.coins06", "Must have the precious", "Collected 30 Secret Coins", "Collect 30 Secret Coins", "color_15", 1);
    AchievementManager::addAchievement("geometry.ach.coins07", "They stole it from us!", "Collected 35 Secret Coins", "Collect 35 Secret Coins", "ball_03", 1);
    AchievementManager::addAchievement("geometry.ach.coins08", "Where is it?! Where is it?!", "Collected 40 Secret Coins", "Collect 40 Secret Coins", "icon_34", 1);

    AchievementManager::addAchievement("geometry.ach.jump01", "Bounce", "Jumped 1000 times", "Jump 1000 times", "color2_05", 0);
    AchievementManager::addAchievement("geometry.ach.jump02", "I like jumping", "Jumped 10000 times", "Jump 10000 times", "color2_11", 0);
    AchievementManager::addAchievement("geometry.ach.jump03", "You jump like a pro!", "Jumped 20000 times", "Jump 20000 times", "color2_12", 0);
    AchievementManager::addAchievement("geometry.ach.jump04", "Hop Hop Hop", "Jumped 50000 times", "Jump 50000 times", "bird_05", 0);
    AchievementManager::addAchievement("geometry.ach.jump05", "Can\'t stop jumping!!!", "Jumped 100000 times", "Jump 100000 times", "ball_13", 0);
    AchievementManager::addAchievement("geometry.ach.jump06", "Jumper", "Jumped 200000 times", "Jump 200000 times", "color_56", 0);
    AchievementManager::addAchievement("geometry.ach.jump07", "You need to rest...", "Jumped 300000 times", "Jump 300000 times", "icon_371", 0);
    AchievementManager::addAchievement("geometry.ach.jump08", "Jumpman", "Jumped 400000 times", "Jump 400000 times", "dart_93", 0);
    AchievementManager::addAchievement("geometry.ach.jump09", "One hop this time!", "Jumped 500000 times", "Jump 500000 times", "icon_365", 0);
    AchievementManager::addAchievement("geometry.ach.jump10", "Leaps and bounds!", "Jumped 750000 times", "Jump 750000 times", "dart_45", 0);
    AchievementManager::addAchievement("geometry.ach.jump11", "Jump King", "Jumped 1000000 times", "Jump 1000000 times", "swing_32", 0);

    AchievementManager::addAchievement("geometry.ach.attempt01", "Trial and error", "Did 100 attempts", "Do 100 attempts", "color2_06", 0);
    AchievementManager::addAchievement("geometry.ach.attempt02", "Crash Tester", "Did 500 attempts", "Do 500 attempts", "color2_07", 0);
    AchievementManager::addAchievement("geometry.ach.attempt03", "You Shall Not Pass!", "Did 2000 attempts", "Do 2000 attempts", "color2_14", 0);
    AchievementManager::addAchievement("geometry.ach.attempt04", "Ouch...", "Did 10000 attempts", "Do 10000 attempts", "color2_17", 0);
    AchievementManager::addAchievement("geometry.ach.attempt05", "That hurts!", "Did 20000 attempts", "Do 20000 attempts", "dart_03", 0);
    AchievementManager::addAchievement("geometry.ach.attempt06", "Never Give Up", "Did 30000 attempts", "Do 30000 attempts", "icon_341", 0);
    AchievementManager::addAchievement("geometry.ach.attempt07", "Never Surrender", "Did 40000 attempts", "Do 40000 attempts", "color_96", 0);
    AchievementManager::addAchievement("geometry.ach.attempt08", "Mom said it\'s my turn", "Did 60000 attempts", "Do 60000 attempts", "ship_161", 0);
    AchievementManager::addAchievement("geometry.ach.attempt09", "If at first you don\'t succeed", "Did 80000 attempts", "Do 80000 attempts", "icon_407", 0);
    AchievementManager::addAchievement("geometry.ach.attempt10", "Stop Trying", "Did 100000 attempts", "Do 100000 attempts", "swing_09", 0);
    AchievementManager::addAchievement("geometry.ach.attempt11", "This could become a meme", "Did 135000 attempts", "Do 135000 attempts", "ball_117", 0);
    AchievementManager::addAchievement("geometry.ach.attempt12", "Take a break!", "Did 185000 attempts", "Do 185000 attempts", "ball_46", 0);
    AchievementManager::addAchievement("geometry.ach.attempt13", "Made an attempt", "Did 250000 attempts", "Do 250000 attempts", "ship_65", 0);
    AchievementManager::addAchievement("geometry.ach.attempt14", "This is the one", "Did 300000 attempts", "Do 300000 attempts", "icon_368", 0);

    AchievementManager::addAchievement("geometry.ach.facebook", "Number one fan!", "Liked Geometry Dash on Facebook", "Like Geometry Dash on Facebook", "color2_13", 0);
    AchievementManager::addAchievement("geometry.ach.youtube", "GeometryTube", "Subscribed to RobTop Games on YouTube", "Subscribe to RobTop Games on YouTube", "color2_30", 0);
    AchievementManager::addAchievement("geometry.ach.twitter", "Geometry Bird!", "Followed RobTop Games on Twitter", "Follow RobTop Games on Twitter", "color2_31", 0);

    AchievementManager::addAchievement("geometry.ach.special01", "So close", "Crashed at over 95% on a main level in normal mode", "Crash at over 95% on a main level in normal mode", "color2_18", 0);

    AchievementManager::addAchievement("geometry.ach.secret01", "Rampage!", "Destroyed a player", "A secret is required", "color2_19", 0);
    AchievementManager::addAchievement("geometry.ach.secret02", "Dominating!", "Destroyed 50 players", "A secret is required", "icon_41", 0);
    AchievementManager::addAchievement("geometry.ach.secret02b", "Ultrakill!", "Destroyed 100 players", "A secret is required", "color2_27", 0);
    AchievementManager::addAchievement("geometry.ach.secret03", "Godlike!", "Destroyed 200 players", "A secret is required", "icon_39", 0);
    AchievementManager::addAchievement("geometry.ach.secret03b", "Wickedsick!", "Destroyed 500 players", "A secret is required", "ball_12", 0);
    AchievementManager::addAchievement("geometry.ach.secret04", "Master Detective", "Found the hidden coin", "A hidden treasure is required", "color2_21", 0);
}