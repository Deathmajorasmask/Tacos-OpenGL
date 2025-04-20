#pragma once

#include <stdio.h>

class PlayerSystemStadistics
{
private:
	int currentLevel;
	int currentStage;
	int currentPlayerNumber;
	int errorPlayer;
	int correctPlayer;
	bool resetStage;
	bool resetLevel;
	bool endLevelNotification;
	bool tutorialSkip;
	bool tutorialLoop;
	bool exitLevel;
public:
	PlayerSystemStadistics();
	~PlayerSystemStadistics();

	void setDefaultConfigs();

	void sendEndLevelNotification();
	bool getEndLevelNotification();
	bool getStatusEndLevelNotificaction();

	void sendExitLevelNotification();
	bool getExitLevelStatus();

	void setResetLevel(bool reset = true);
	bool getResetStatusLevel();
	void setCurrentLevel(int value = 1);
	int getCurrentLevel();
	void pushNextLevel();

	void setResetStage(bool reset = true);
	bool getResetStatusStage();
	void setCurrentStage(int value = 1);
	int getCurrentStage();
	void pushNextStage();

	void setCurrentPlayerNumber(int value = 1);
	int getCurrentPlayerNumber();

	void pushCorrectPlayer();
	int getCorrectPlayer();

	void pushErrorPlayer();
	int getErrorPlayer();

	void resetStadisticsPlayer();

	void sendSkipTutorialNotification();
	bool getSkipTutorialNotification();
	bool getSkipTutorialStatus();
	void sendEndLoopTutorial();
	bool getEndLoopTutorial();

	char* getScorePlayer();

};