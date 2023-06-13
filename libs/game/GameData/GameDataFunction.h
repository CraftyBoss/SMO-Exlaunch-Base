/**
 * @file GameDataFunction.h
 * @brief Holds static functions for getting / storage save data.
 */

#pragma once

#include "GameDataHolderAccessor.h"
#include "GameDataHolderWriter.h"
#include "game/GameData/GameDataFile.h"
#include "game/MapObj/ChangeStageInfo.h"

#include <al/Library/Camera/CameraTicket.h>
#include <al/Library/LiveActor/LiveActor.h>
#include <al/Library/Layout/LayoutActor.h>
#include <al/Library/Scene/Scene.h>

class GameDataFunction {
public:

    // sets the current worn costume
    static void wearCostume(GameDataHolderWriter, char const *);

    // sets the current worn cap
    static void wearCap(GameDataHolderWriter, char const *);

    // remove cappy
    static void disableCapByPlacement(al::LiveActor const *);

    // restarts current stage
    static void restartStage(GameDataHolderWriter);

    // restarts current stage
    static void missAndRestartStage(GameDataHolderWriter);

    // attempts to change the current stage the player is in
    static bool tryChangeNextStage(GameDataHolderWriter, ChangeStageInfo const *);

    // gets prev save file's current world id
    static s32 getPrevWorldId(GameDataHolderAccessor);

    // gets current save file's current world id
    static s32 getCurrentWorldId(GameDataHolderAccessor);

    // gets next save file's current world id
    static s32 getNextWorldId(GameDataHolderAccessor);

    // gets current save file's current stage scenario no
    static u8 getScenarioNo(al::LiveActor const *);

    static s32 calcNextScenarioNo(GameDataHolderAccessor);

    // gets the current scenario No of the specified kingdom
    static s32 getWorldScenarioNo(GameDataHolderAccessor, int);

    static char *getCurrentStageName(GameDataHolderAccessor);

    static char *getMainStageName(GameDataHolderAccessor, int);

    static char *getNextStageName(GameDataHolderAccessor);

    // gets the currently stored ChangeStageId from the save file
    static const char *tryGetPlayerStartId(GameDataHolderAccessor);

    static s32 getCurrentShineNum(GameDataHolderAccessor);

    // gets total moons collected on a specified save file (-1 for current save)
    static s32 getTotalShineNum(GameDataHolderAccessor, int);

    // gets the total amount of moons available in a kingdom
    static s32 getWorldTotalShineNum(GameDataHolderAccessor, int);

    // checks save file if shine is collected in kingdom index
    static bool isGotShine(GameDataHolderAccessor, int, int);

    // checks save file if shine is collected by shine index only (0 through 725)
    static bool isGotShine(GameDataHolderAccessor, int);

    // Gets Index for X Kingdom
    static s32 getWorldIndexWaterfall(void);

    static s32 getWorldIndexMoon(void);

    // gets the current level of the Odyssey
    static int getHomeLevel(GameDataHolderAccessor);

    // checks if cappy is enabled
    static bool isEnableCap(GameDataHolderAccessor);

    // enables cappy if not enabled already
    static void enableCap(GameDataHolderWriter);

    // kills the player
    static void killPlayer(GameDataHolderWriter);

    // damages the player
    static void damagePlayer(GameDataHolderWriter);

    // upgrades the odyssey
    static void upHomeLevel(GameDataHolderWriter);

    // Saves shine if obtained
    static void setGotShine(GameDataHolderWriter, ShineInfo const *);

    //unlocks a kingdom based off index
    static void unlockWorld(GameDataHolderWriter, int);

    //sets the scenario of the specified kingdom
    static void setMainScenarioNo(GameDataHolderWriter, int scenarioNo);

    // checks if the opening cutscene needs to play
    static bool isPlayDemoOpening(GameDataHolderAccessor);

    // checks if odyssey is/needs a repair
    static bool isRepairHome(GameDataHolderAccessor);

    static void repairHome(GameDataHolderWriter);

    // checks if odyssey is crashed
    static bool isCrashHome(GameDataHolderAccessor);

    static void crashHome(GameDataHolderWriter);

    // checks if odyssey is activated
    static bool isActivateHome(GameDataHolderAccessor);

    static void activateHome(GameDataHolderWriter);

    // checks if the odyssey has launched for the first time.
    static bool isLaunchHome(GameDataHolderAccessor);

    static void launchHome(GameDataHolderWriter);

    static bool isHomeShipStage(GameDataHolder const *);

    // used during the event that enables the odyssey to be used (enables the globe for the odyssey)
    static void talkCapNearHomeInWaterfall(al::LiveActor const *);

    // gives the player a life up heart
    static void getLifeMaxUpItem(al::LiveActor const *);

    // gets current coin count
    static s32 getCoinNum(GameDataHolderAccessor);

    // gets current purple coin count
    static s32 getCoinCollectNum(GameDataHolderAccessor);

    // saves an objects Stage Name, Object ID, and custom value to the save file
    static void saveObjS32(GameDataHolderWriter, al::PlacementId const *, int);

    // gets the value stored in the unique obj info that matches placement id and curstage
    static bool tryFindSaveObjS32Value(int *value, GameDataHolderAccessor accessor, al::PlacementId const *objId);

    // subtracts the supplied int value from the current coin count
    static void subCoin(GameDataHolderWriter, int value);

    static const char *getCurrentStageName(GameDataHolderAccessor, int);

    static const char *getNextStageName(GameDataHolderAccessor, int);

    static const char *tryGetCurrentMainStageName(GameDataHolderAccessor);

    static const char *findMainStageNameByDevelopName(GameDataHolderAccessor, char const *);

    static int tryFindWorldIdByMainStageName(al::Scene const *, char const *);

    static int tryFindWorldIdByMainStageName(al::IUseSceneObjHolder const *, char const *);

    static const char *getHomeShipStageName(void);

    static bool isUnlockedWorld(GameDataHolderAccessor, int);

    static bool isUnlockedNextWorld(GameDataHolderAccessor);

    static bool isUnlockedAllWorld(GameDataHolderAccessor);

    static bool isUnlockedCurrentWorld(GameDataHolderAccessor);

    static bool isUnlockWorld(int);

    static bool isUnlockFirstForest(void);

    static bool isUnlockFirstSea(void);

    // the rest of these funcs are mostly undocumented as i grabbed their symbols and plopped em here

    static bool isGameClear(GameDataHolderAccessor);

    static bool isTimeBalloonSequence(GameDataHolderAccessor);

    static bool isSeaOfTreeStage(GameDataHolderAccessor);

    static bool isMissEndPrevStageForInit(GameDataHolderAccessor);

    static bool isMissEndPrevStageForSceneDead(GameDataHolderAccessor);

    static bool isAlreadyGoWorld(GameDataHolderAccessor, int);

    static bool isForwardWorldWarpDemo(GameDataHolderAccessor);

    static bool isFirstTimeNextWorld(GameDataHolderAccessor);

    static bool isEqualScenario(class RiseMapPartsHolder const *, int);

    static bool isPlayerStartObj(al::LiveActor const *, al::ActorInitInfo const &);

    static bool isPlayerStartObj(al::LiveActor const *, al::PlacementInfo const &);

    static bool isPlayerStartObj(al::LiveActor const *, char const *);

    static bool isPlayerStartLinkedObj(al::LiveActor const *, al::ActorInitInfo const &, char const *);

    static bool isAlreadyShowExplainCheckpointFlag(GameDataHolderAccessor);

    static bool isEnableShowExplainCheckpointFlag(GameDataHolderAccessor);

    static bool isPlayerHitPointMax(GameDataHolderAccessor);

    static bool isPlayerHitPointMaxWithItem(GameDataHolderAccessor);

    static bool isPlayerLifeZero(GameDataHolderAccessor);

    static bool isGotShine(GameDataHolderAccessor, ShineInfo const *);

    static bool isGotShine(GameDataHolderAccessor, al::PlacementId const *);

    static bool isGotShine(GameDataHolderAccessor, char const *, char const *);

    static bool isGotShine(class Shine const *);

    static bool isPlayScenarioCamera(GameDataHolderAccessor, QuestInfo const *);

    static bool isPlayAlreadyScenarioStartCamera(GameDataHolderAccessor, int);

    static bool isEnterStageFirst(GameDataHolderAccessor);

    static bool isNextMainShine(GameDataHolderAccessor, int);

    static bool isMainShine(GameDataHolderAccessor, int);

    static bool isLatestGetMainShine(GameDataHolderAccessor, ShineInfo const *);

    static bool isGotLinkedShineBeforeInitActor(al::ActorInitInfo const &, char const *);

    static bool isExistInHackDictionary(GameDataHolderAccessor, char const *, int);

    static bool isEnableOpenMoonRock(al::LiveActor const *);

    static bool isOpenMoonRock(GameDataHolderAccessor);

    static bool isEnableShowDemoOpenMoonRockFirst(GameDataHolderAccessor);

    static bool isEnableShowDemoOpenMoonRockWorld(GameDataHolderAccessor);

    static bool isAppearedMoonRockTalkMessage(GameDataHolderAccessor);

    static bool isPayShineAllInAllWorld(GameDataHolderAccessor);

    static bool isOpenDoorLock(GameDataHolderAccessor, al::PlacementId const *);

    static bool isObjStarted(GameDataHolder const *, al::PlacementId const *);

    static bool isObjStarted(GameDataHolderAccessor, char const *, char const *);

    static bool isOnObjNoWriteSaveData(GameDataHolderAccessor, al::PlacementId const *);

    static bool isOnObjNoWriteSaveDataResetMiniGame(GameDataHolderAccessor, al::PlacementId const *);

    static bool isOnObjNoWriteSaveDataInSameScenario(GameDataHolder const *, al::PlacementId const *);

    static bool isPayCoinToSphinx(al::LiveActor const *);

    static bool isRemovedCapByJango(al::LiveActor const *);

    static bool isMainStage(GameDataHolderAccessor);

    static bool isGetCapFromJango(al::LiveActor const *);

    static bool isFirstWorldTravelingStatus(class WorldTravelingNpc const *);

    static bool isRaceStart(GameDataHolderAccessor);

    static bool isRaceStartFlag(GameDataHolderAccessor);

    static bool isRaceStartYukimaru(GameDataHolderAccessor);

    static bool isRaceStartYukimaruTutorial(GameDataHolderAccessor);

    static bool isRaceWin(GameDataHolderAccessor);

    static bool isRaceWin(GameDataHolderAccessor, int);

    static bool isRaceResultSecond(GameDataHolderAccessor);

    static bool isRaceResultThird(GameDataHolderAccessor);

    static bool isRaceLose(GameDataHolderAccessor);

    static bool isRaceCancel(GameDataHolderAccessor);

    static bool isGotCoinCollect(GameDataHolderAccessor, al::ActorInitInfo const &);

    static bool isAppearCourseName(GameDataHolderAccessor);

    static bool isEnableCheckpointWarp(GameDataHolderAccessor);

    static bool isGotCheckpointInWorld(GameDataHolderAccessor, int);

    static bool isGotCheckpoint(GameDataHolderAccessor, al::PlacementId *);

    static bool isWarpCheckpoint(GameDataHolderAccessor);

    static bool isEnableUnlockHint(GameDataHolderAccessor);

    static bool isCollectShineForNextWorldAndNotUnlockNextWorld(al::LiveActor const *);

    static bool isNewSaveDataByFileId(al::LayoutActor const *, int);

    static bool isCityWorldCeremonyAll(int, int);

    static bool isClearSandWorldScenario1(al::Scene const *);

    static bool isClearCityWorldScenario1(al::Scene const *);

    static bool isClearSkyWorldScenario1(al::Scene const *);

    static bool isCityWorldScenario2(al::IUseSceneObjHolder const *);

    static bool isWorldCity(GameDataHolderAccessor);

    static bool isPlayDemoWorldWarp(GameDataHolderAccessor);

    static bool isPlayDemoWorldWarpHole(GameDataHolderAccessor);

    static bool isPlayDemoReturnToHome(GameDataHolderAccessor);

    static bool isPlayDemoAwardSpecial(GameDataHolderAccessor);

    static bool isPlayDemoLavaErupt(GameDataHolderAccessor);

    static bool isPlayDemoPlayerDownForBattleKoopaAfter(GameDataHolderAccessor);

    static bool isCostumeRandomMode(al::IUseSceneObjHolder *);

    static bool isCapRandomMode(al::IUseSceneObjHolder *);

    static bool isExistHackObjInfo(GameDataHolderAccessor, char const *);

    static bool isExistInHackDictionary(GameDataHolderAccessor, char const *);

    static bool isShowHackTutorial(GameDataHolderAccessor, char const *, char const *);

    static bool isShowBindTutorial(GameDataHolderAccessor, class BindInfo const &);

    static bool isOpenShineName(al::LayoutActor const *, int, int);

    static bool isExistHome(GameDataHolderAccessor);

    static bool isShopSellout(GameDataHolderAccessor, int);

    static bool isExistRaceStartNpc(GameDataHolderAccessor);

    static bool isExistHintNpc(GameDataHolderAccessor);

    static bool isExistJango(GameDataHolderAccessor);

    static bool isExistAmiiboNpc(GameDataHolderAccessor);

    static bool isInInvalidOpenMapStage(GameDataHolderAccessor);

    static bool isExistTimeBalloonNpc(GameDataHolderAccessor);

    static bool isExistPoetter(GameDataHolderAccessor);

    static bool isBossAttackedHome(GameDataHolderAccessor);

    static bool isRepairHomeByCrashedBoss(GameDataHolderAccessor);

    static bool isFindKoopaNext(GameDataHolderAccessor, int);

    static bool isBossAttackedHomeNext(GameDataHolderAccessor, int);

    static bool isFindKoopa(GameDataHolderAccessor);

    static bool isMeetCap(GameDataHolderAccessor);

    static bool isTalkedCapNearHomeInWaterfall(al::LiveActor const *);

    static bool isFlagOnTalkMessageInfo(al::IUseSceneObjHolder const *, int);

    static bool isWorldCap(GameDataHolderAccessor);

    static bool isWorldWaterfall(GameDataHolderAccessor);

    static bool isWorldSand(GameDataHolderAccessor);

    static bool isWorldForest(GameDataHolderAccessor);

    static bool isWorldLake(GameDataHolderAccessor);

    static bool isWorldCloud(GameDataHolderAccessor);

    static bool isWorldClash(GameDataHolderAccessor);

    static bool isWorldSnow(GameDataHolderAccessor);

    static bool isWorldSea(GameDataHolderAccessor);

    static bool isWorldBoss(GameDataHolderAccessor);

    static bool isWorldSky(GameDataHolderAccessor);

    static bool isWorldMoon(GameDataHolderAccessor);

    static bool isWorldPeach(GameDataHolderAccessor);

    static bool isWorldSpecial1(GameDataHolderAccessor);

    static bool isWorldSpecial2(GameDataHolderAccessor);

    static bool isWorldTypeMoon(GameDataHolderAccessor, int);

    static bool isSnowMainScenario1(al::IUseSceneObjHolder const *);

    static bool isSnowMainScenario2(al::IUseSceneObjHolder const *);

    static bool isCityWorldCeremonyAgain(int, int);

    static bool isGoToCeremonyFromInsideHomeShip(GameDataHolderAccessor);

    static bool isEnableExplainAmiibo(GameDataHolderAccessor);

    static bool isCollectedBgm(GameDataHolderAccessor, char const *, char const *);

    static bool isKoopaLv3(GameDataHolderAccessor);

    // getters

    static GameDataHolder *getGameDataHolder(al::IUseSceneObjHolder const *);

    static GameDataHolder *getGameDataHolder(al::SceneObjHolder const *);

    static GameDataHolder *getGameDataHolder(al::GameDataHolderBase *);

    static void *getGameDataFile(GameDataHolderWriter);

    static void *getPlayTimeTotal(GameDataHolderAccessor);

    static void *getPlayTimeAcrossFile(GameDataHolderAccessor);

    static void *getSaveDataIdForPrepo(GameDataHolderAccessor);

    static s32 getWorldNumForNewReleaseShop(GameDataHolderAccessor);

    static void *getWorldDevelopName(GameDataHolderAccessor, int);

    static void *getWorldIdForNewReleaseShop(GameDataHolderAccessor, int);

    static s32 getWorldNum(GameDataHolderAccessor);

    static void *getCurrentWorldIdNoDevelop(GameDataHolderAccessor);

    static void *getScenarioNo(al::LayoutActor const *);

    static void *getScenarioNoPlacement(GameDataHolderAccessor);

    static void *getMainQuestMin(al::LiveActor const *);

    static void *getStartShineNextIndex(GameDataHolderAccessor);

    static void *getPlayerHitPoint(GameDataHolderAccessor);

    static void *getPlayerHitPointMaxCurrent(GameDataHolderAccessor);

    static void *getPlayerHitPointMaxNormal(GameDataHolderAccessor);

    static s32 getGotShineNum(GameDataHolderAccessor, int);

    static void *getLatestGetShineInfo(GameDataHolderAccessor);

    static s32 getTotalShopShineNum(GameDataHolderAccessor, int);

    static s32 getMainScenarioNumMax(GameDataHolderAccessor);

    static s32 getCollectedBgmNum(GameDataHolderAccessor, int);

    static s32 getCollectedBgmMaxNum(GameDataHolderWriter);

    static s32 getPayShineNum(GameDataHolderAccessor);

    static s32 getPayShineNum(GameDataHolderAccessor, int);

    static s32 getTotalPayShineNum(GameDataHolderAccessor);

    static s32 getTotalPayShineNumClamp(GameDataHolderAccessor);

    static s32 getKeyNum(GameDataHolderAccessor);

    static s32 getCurrentKeyNum(GameDataHolderAccessor);

    static s32 getOpenDoorLockNum(GameDataHolderAccessor);

    static void *getSessionEventProgress(GameDataHolderAccessor);

    static void *getCapFromJango(al::LiveActor const *);

    static void *getJangoCount(al::LiveActor const *);

    static void *getWorldTravelingStatus(WorldTravelingNpc const *);

    static void *getRaceRivalLevel(al::LiveActor const *);

    static void *getRaceRivalLevel(al::Scene const *);

    static void *getLastRaceRanking(GameDataHolderWriter);

    static void *getRaceLoseCount(al::LiveActor const *, int);

    static s32 getCoinCollectGotNum(GameDataHolderAccessor);

    static s32 getCoinCollectGotNum(GameDataHolderAccessor, int);

    static s32 getCoinCollectNumMax(GameDataHolderAccessor);

    static s32 getCoinCollectNumMax(GameDataHolderAccessor, int);

    static s32 getTotalCoinNum(GameDataHolderAccessor);

    static s32 getCheckpointNumMaxInWorld(GameDataHolderAccessor);

    static sead::Vector3f &getCheckpointTransInWorld(GameDataHolderAccessor, int);

    static void *getCheckpointObjIdInWorld(GameDataHolderAccessor, int);

    static sead::Vector3f &getCheckpointTransInWorld(GameDataHolderAccessor, char const *);

    static void *getCheckpointWarpObjId(GameDataHolderAccessor);

    static s32 getHintNumMax(GameDataHolderAccessor);

    static sead::Vector3f &getLatestHintTrans(GameDataHolderAccessor);

    static s32 getHintMoonRockNumMax(GameDataHolderAccessor);

    static void *getWorldIndexSpecial2(void);

    static void *getWorldDevelopNameCurrent(GameDataHolderAccessor);

    static s32 getWorldScenarioNum(GameDataHolderAccessor, int);

    static void *getWorldIndexSpecial1(void);

    static void *getLastUpdateFileTime(al::LayoutActor const *, int);

    static s32 getWorldIndexPeach(void);

    static s32 getWorldIndexCity(void);

    static s32 getWorldIndexSea(void);

    static void *getUnlockWorldIdForWorldMap(al::LayoutActor const *, int);

    static void *getUnlockWorldIdForWorldMap(al::LiveActor const *, int);

    static void *getUnlockWorldIdForWorldMap(al::Scene const *, int);

    static void *getUnlockWorldIdForWorldMap(GameDataHolder const *, int);

    static s32 getUnlockWorldNumForWorldMap(al::Scene const *);

    static s32 getUnlockWorldNumForWorldMap(al::LiveActor const *);

    static s32 getUnlockWorldNumForWorldMap(al::LayoutActor const *);

    static void *getWorldIdForShineList(al::LayoutActor const *, int);

    static void *getLatestUnlockWorldIdForShineTowerMeter(al::LiveActor const *);

    static void *getCurrentCostumeTypeName(GameDataHolderAccessor);

    static void *getCurrentCapTypeName(GameDataHolderAccessor);

    static void *getShopItemInfoList(GameDataHolderAccessor);

    static void *getHackObjInfo(GameDataHolderAccessor, char const *);

    static s32 getWorldTotalShineNumMax(GameDataHolderAccessor, int);

    static sead::Vector3f &getHomeTrans(GameDataHolderAccessor);

    static s32 getMiniGameNum(GameDataHolderAccessor);

    static s32 getMiniGameNumMax(GameDataHolderAccessor);

    static sead::Vector3f &getMiniGameTrans(GameDataHolderAccessor, int);

    static void *getMiniGameName(GameDataHolderAccessor, int);

    static sead::Vector3f &getRaceStartTrans(GameDataHolderAccessor);

    static sead::Vector3f &getRaceGoalTrans(GameDataHolderAccessor);

    static sead::Vector3f &getHintNpcTrans(GameDataHolderAccessor);

    static sead::Vector3f &getShopNpcTrans(GameDataHolderAccessor, int);

    static s32 getShopNpcIconNumMax(GameDataHolderAccessor);

    static void *getCurrentMapView(GameDataHolderAccessor);

    static sead::Vector3f &getJangoTrans(GameDataHolderAccessor);

    static sead::Vector3f &getAmiiboNpcTrans(GameDataHolderAccessor);

    static sead::Vector3f &getStageMapPlayerPos(GameDataHolderAccessor);

    static sead::Vector3f &getTimeBalloonNpcTrans(GameDataHolderAccessor);

    static sead::Vector3f &getPoetterTrans(GameDataHolderAccessor);

    static sead::Vector3f &getMoonRockTrans(GameDataHolderAccessor);

    static s32 getWorldIndexHat(void); // Cap Kingdom
    static s32 getWorldIndexSand(void); // Sand Kingdom
    static s32 getWorldIndexForest(void); // Wooded Kingdom
    static s32 getWorldIndexLake(void); // Lake Kingdom
    static s32 getWorldIndexCloud(void); // Cloud Kingdom
    static s32 getWorldIndexClash(void); // Ruined Kingdom
    static s32 getWorldIndexSnow(void); // Snow Kingdom
    static s32 getWorldIndexLava(void); // Luncheon Kingdom
    static s32 getWorldIndexBoss(void); // Lost Kingdom
    static s32 getWorldIndexSky(void); // Bowser's Kingdom
    static void *getCollectBgmByIndex(GameDataHolderAccessor, int);

    static s32 getCollectedBgmNum(GameDataHolderWriter);

    // setters

    static void setCheckpointId(GameDataHolderWriter, al::PlacementId const *);

    static void setPlayingFileId(GameDataHolderWriter, int);

    static void setRestartPointId(GameDataHolderWriter, al::PlacementId const *);

    static void setRequireSaveFrame(GameDataHolderWriter);

    static void setStartShine(al::LiveActor const *, ShineInfo const *);

    static void setObjStarted(GameDataHolder *, al::PlacementId const *);

    static void setRequireSave(GameDataHolderWriter);

    static void setStageHakoniwa(GameDataHolderWriter);

    static void setSessionEventProgress(GameDataHolderWriter, class SessionEventProgress const &);

    static void setLastRaceRanking(GameDataHolderAccessor, int);

    static void setCostumeRandomMode(al::IUseSceneObjHolder *);

    static void setRaceRivalLevel(al::LiveActor const *, int);

    static void setHomeTrans(al::LiveActor const *, sead::Vector3f const &);

    static void setShowHackTutorial(GameDataHolderWriter, char const *, char const *);

    static void setCapRandomMode(al::IUseSceneObjHolder *);

    static void setRaceStartTrans(al::LiveActor const *);

    static void setRaceGoalTrans(al::LiveActor const *);

    static void setShowBindTutorial(GameDataHolderWriter, BindInfo const &);

    static void setShopNpcTrans(al::LiveActor const *, char const *, int);

    static void setRaceStartNpcTrans(al::LiveActor const *);

    static void setHintNpcTrans(al::LiveActor const *);

    static void setAmiiboNpcTrans(al::LiveActor const *);

    static void setShopNpcTrans(GameDataHolderAccessor, al::PlacementInfo const &);

    static void setJangoTrans(al::LiveActor const *);

    static void setStageMapPlayerPos(GameDataHolderWriter, sead::Vector3f const &);

    static void setTimeBalloonTrans(GameDataHolderAccessor, sead::Vector3f const &);

    static void setMiniGameInfo(GameDataHolderAccessor, al::PlacementInfo const &);

    static void setKidsModeOn(al::Scene const *);

    static void setKidsModeOff(al::Scene const *);

    static void setMoonRockTrans(GameDataHolderWriter, sead::Vector3f const &);

    static void setHintTrans(GameDataHolderAccessor, int, sead::Vector3f const &);

    static void setPoetterTrans(GameDataHolderAccessor, sead::Vector3f const &);

    // misc

    static void initializeData(GameDataHolderWriter, int);

    static void startDemoStage(GameDataHolderWriter, char const *);

    static void tryChangeNextStageWithStartRaceFlag(GameDataHolderWriter, ChangeStageInfo const *);

    static void tryChangeNextStageWithStartRaceYukimaru(GameDataHolderWriter, ChangeStageInfo const *);

    static void tryChangeNextStageWithDemoWorldWarp(GameDataHolderWriter, char const *);

    static void tryChangeNextStageWithWorldWarpHole(GameDataHolderWriter, char const *);

    static void changeNextStageWithStartTimeBalloon(GameDataHolderWriter, int);

    static void changeNextStageWithEndTimeBalloon(GameDataHolderWriter);

    static void changeNextStageWithCloset(GameDataHolderWriter);

    static void findAreaAndChangeNextStage(GameDataHolderWriter, al::LiveActor const *, sead::Vector3<float> const *);

    static void returnPrevStage(GameDataHolderWriter);

    static void reenterStage(GameDataHolderWriter);

    static void checkIsNewWorldInAlreadyGoWorld(GameDataHolderAccessor);

    static void clearStartId(GameDataHolderWriter);

    static void tryGetRestartPointIdString(GameDataHolderAccessor);

    static void showExplainCheckpointFlag(GameDataHolderAccessor);

    static void recoveryPlayer(al::LiveActor const *);

    static void recoveryPlayerForDebug(al::LiveActor const *);

    static void recoveryPlayerMax(al::LiveActor const *);

    static void recoveryPlayerForSystem(GameDataHolder const *);

    static void recoveryPlayerMaxForSystem(GameDataHolder const *);

    static void initPlayerHitPointForSystem(GameDataHolder const *);

    static void tryGetNextMainScenarioLabel(sead::BufferedSafeStringBase<char> *, sead::BufferedSafeStringBase<char> *,
                                            al::IUseSceneObjHolder const *);

    static void tryGetNextMainScenarioPos(sead::Vector3<float> *, GameDataHolderAccessor);

    static void tryFindLinkedShineIndex(al::LiveActor const *, al::ActorInitInfo const &);

    static void tryFindLinkedShineIndex(al::LiveActor const *, al::ActorInitInfo const &, int);

    static void tryFindLinkedShineIndexByLinkName(al::LiveActor const *, al::ActorInitInfo const &, char const *);

    static void calcLinkedShineNum(al::LiveActor const *, al::ActorInitInfo const &);

    static void tryFindShineIndex(al::LiveActor const *, al::ActorInitInfo const &);

    static void tryFindShineIndex(al::LiveActor const *, char const *, char const *);

    static void tryFindShineUniqueId(al::Scene const *, ShineInfo const *);

    static void disableHintByShineIndex(al::LiveActor const *, int);

    static void enableHintByShineIndex(al::LiveActor const *, int);

    static void calcIsGetMainShineAll(al::IUseSceneObjHolder const *);

    static void calcIsGetShineAllInWorld(GameDataHolderAccessor, int);

    static void calcIsGetShineAllInAllWorld(GameDataHolderAccessor);

    static void tryFindAndInitShineInfoByOptionalId(ShineInfo *, GameDataHolderAccessor, char const *);

    static void checkIsComplete(al::IUseSceneObjHolder const *, int);

    static void openMoonRock(al::LiveActor const *, al::PlacementId const *);

    static void showDemoOpenMoonRockFirst(GameDataHolderAccessor);

    static void showDemoOpenMoonRockWorld(GameDataHolderAccessor);

    static void calcMoonRockTalkMessageIndex(GameDataHolderAccessor);

    static void addMoonRockTalkMessageIndex(GameDataHolderWriter);

    static void addPayShine(GameDataHolderWriter, int);

    static void addPayShineCurrentAll(GameDataHolderWriter);

    static void addKey(GameDataHolderWriter, int);

    static void openDoorLock(GameDataHolderWriter, al::PlacementId const *);

    static void onObjNoWriteSaveData(GameDataHolderWriter, al::PlacementId const *);

    static void offObjNoWriteSaveData(GameDataHolderWriter, al::PlacementId const *);

    static void onObjNoWriteSaveDataResetMiniGame(GameDataHolderWriter, al::PlacementId const *);

    static void offObjNoWriteSaveDataResetMiniGame(GameDataHolderWriter, al::PlacementId const *);

    static void onObjNoWriteSaveDataInSameScenario(GameDataHolder *, al::PlacementId const *);

    static void payCoinToSphinx(al::LiveActor const *);

    static void removeCapByJango(al::LiveActor const *);

    static void addJangoCount(al::LiveActor const *);

    static void saveWorldTravelingStatus(WorldTravelingNpc const *, char const *);

    static void winRace(GameDataHolderWriter);

    static void endRaceResultSecond(GameDataHolderWriter);

    static void endRaceResultThird(GameDataHolderWriter);

    static void loseRace(GameDataHolderWriter);

    static void incrementRaceLoseCount(al::Scene const *, int);

    static void addCoinCollect(GameDataHolderWriter, al::PlacementId const *);

    static void useCoinCollect(GameDataHolderWriter, int);

    static void tryFindExistCoinCollectStagePosExcludeHomeStageInCurrentWorld(sead::Vector3<float> *, char const **,
                                                                              GameDataHolderAccessor);

    static void addCoin(GameDataHolderWriter, int);

    static void validateCheckpointWarp(GameDataHolderWriter);

    static void invalidateCheckpointWarp(GameDataHolderWriter);

    static void calcGotCheckpointNumInWorld(GameDataHolderAccessor);

    static void changeNextSceneByGotCheckpoint(GameDataHolderWriter, int);

    static void changeNextSceneByHome(GameDataHolderWriter);

    static void registerCheckpointTrans(GameDataHolderWriter, al::PlacementId const *, sead::Vector3<float> const &);

    static void unlockHint(GameDataHolderWriter);

    static void unlockHintAmiibo(GameDataHolderWriter);

    static void calcHintNum(GameDataHolderAccessor);

    static void calcRestHintNum(GameDataHolderAccessor);

    static void checkExistHint(GameDataHolderAccessor);

    static void calcHintTrans(GameDataHolderAccessor, int);

    static void checkLatestHintSeaOfTree(GameDataHolderAccessor);

    static void calcHintMoonRockNum(GameDataHolderAccessor);

    static void calcHintMoonRockTrans(GameDataHolderAccessor, int);

    static void initializeHintList(GameDataHolderWriter);

    static void calcHintTransMostEasy(GameDataHolderAccessor);

    static void calcHintTransMostNear(sead::Vector3<float> *, GameDataHolderAccessor, sead::Vector3<float> const &);

    static void checkHintSeaOfTree(GameDataHolderAccessor, int);

    static void checkHintSeaOfTreeMoonRock(GameDataHolderAccessor, int);

    static void findUnlockShineNum(bool *, GameDataHolderAccessor);

    static void findUnlockShineNumByWorldId(bool *, GameDataHolderAccessor, int);

    static void tryGetWorldName(al::LayoutActor const *, int);

    static void tryGetWorldNameCurrent(al::LayoutActor const *);

    static void tryGetRegionNameCurrent(al::LayoutActor const *);

    static void findWorldIdByDevelopName(GameDataHolderAccessor, char const *);

    static void checkEnableUnlockWorldSpecial1(al::LiveActor const *);

    static void checkEnableUnlockWorldSpecial2(al::LiveActor const *);

    static void tryGetWorldNameByFileId(al::LayoutActor const *, int);

    static void
    makeTextureSaveDataFileName(sead::BufferedSafeStringBase<char> *, nn::g3d::ResFile const *, GameDataHolder const *,
                                int);

    static void calcNextLockedWorldIdForWorldMap(al::LayoutActor const *, int);

    static void calcNextLockedWorldIdForWorldMap(al::Scene const *, int);

    static void calcNextLockedWorldNumForWorldMap(al::Scene const *);

    static void calcNextLockedWorldNumForWorldMap(al::LayoutActor const *);

    static void calcWorldNumForShineList(al::LayoutActor const *);

    static void calcNextWorldId(GameDataHolderAccessor);

    static void noPlayDemoWorldWarp(GameDataHolderWriter);

    static void requestPlayDemoReturnToHome(GameDataHolderWriter);

    static void requestPlayDemoAwardSpecial(GameDataHolderWriter);

    static void disablePlayDemoPlayerDownForBattleKoopaAfter(GameDataHolderWriter);

    static void enteredStage(GameDataHolderWriter);

    static void wearCostumeRandom(al::IUseSceneObjHolder *);

    static void wearCapRandom(al::IUseSceneObjHolder *);

    static void tryWearCostumeRandomIfEnable(al::IUseSceneObjHolder *);

    static void tryWearCapRandomIfEnable(al::IUseSceneObjHolder *);

    static void resetCostumeRandomMode(al::IUseSceneObjHolder *);

    static void resetCapRandomMode(al::IUseSceneObjHolder *);

    static void addHackDictionary(GameDataHolderWriter, char const *);

    static void checkAchievementShine(al::LayoutActor const *, int, int);

    static void calcShineNumInOneShine(al::LayoutActor const *, int, int);

    static void tryFindShineMessage(al::LayoutActor const *, int, int);

    static void tryFindShineMessage(al::LiveActor const *, al::IUseMessageSystem const *, int, int);

    static void findShineGetTime(al::LayoutActor const *, int, int);

    static void checkMoonRockShineForShineList(al::LayoutActor const *, int, int);

    static void checkUnlockHintByHintNpcForShineList(al::LayoutActor const *, int, int);

    static void checkUnlockHintByAmiiboForShineList(al::LayoutActor const *, int, int);

    static void checkShineSeaOfTreeForShineList(al::LayoutActor const *, int, int);

    static void findShineTrans(sead::Vector3<float> *, GameDataHolderAccessor, int, int);

    static void calcShopNum(GameDataHolderAccessor);

    static void disableJangoTrans(al::LiveActor const *);

    static void bossAttackHome(GameDataHolderWriter);

    static void repairHomeByCrashedBoss(GameDataHolderWriter);

    static void findKoopa(GameDataHolderWriter);

    static void onFlagTalkMessageInfo(al::IUseSceneObjHolder const *, int);

    static void registerScenarioStartCameraInfo(class ScenarioStartCamera const *, int, al::CameraTicket *);

    static void endExplainAmiibo(GameDataHolderWriter);

    static void startSearchHintByAmiibo(GameDataHolderWriter);

    static void endSearchHintByAmiibo(GameDataHolderWriter);

    static void trySetCollectedBgm(GameDataHolderWriter, char const *, char const *);

    static void registerShineInfo(GameDataHolderAccessor, ShineInfo const *, sead::Vector3<float> const &);

    static void resetHintTrans(GameDataHolderAccessor, int);

};