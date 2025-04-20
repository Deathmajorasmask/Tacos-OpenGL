#include "PlayerSystemStadistics.h"

PlayerSystemStadistics::PlayerSystemStadistics() {
	currentLevel = 0;
	currentStage = 0;
	currentPlayerNumber = 0;
	errorPlayer = 0;
	correctPlayer = 0;
	resetLevel = false;
	resetStage = false;
	endLevelNotification = false;
	tutorialSkip = false;
	tutorialLoop = true;
	exitLevel = false;
};

PlayerSystemStadistics::~PlayerSystemStadistics() {

};

void PlayerSystemStadistics::sendEndLevelNotification() {
	endLevelNotification = true;
}


bool PlayerSystemStadistics::getEndLevelNotification() {
	if (endLevelNotification) {
		endLevelNotification = false;
		return true;
	}
	return false;
}

bool PlayerSystemStadistics::getStatusEndLevelNotificaction() {
	return endLevelNotification;
}

void PlayerSystemStadistics::sendExitLevelNotification() {
	exitLevel = true;
}

bool PlayerSystemStadistics::getExitLevelStatus() {
	return exitLevel;
}

void PlayerSystemStadistics::setDefaultConfigs() {
	currentLevel = 1;
	currentStage = 0;
	currentPlayerNumber = 1;
	errorPlayer = 0;
	correctPlayer = 0;
	resetLevel = false;
	resetStage = false;
	endLevelNotification = false;
	tutorialSkip = false;
	tutorialLoop = true;
	exitLevel = false;
}

void PlayerSystemStadistics::setResetLevel(bool reset) {
	resetLevel = reset;
}

bool PlayerSystemStadistics::getResetStatusLevel() {
	return resetLevel;
}

void PlayerSystemStadistics::setCurrentLevel(int value) {
	currentLevel = value;
}

int PlayerSystemStadistics::getCurrentLevel() {
	return currentLevel;
}

void PlayerSystemStadistics::pushNextLevel() {
	currentLevel++;
}

void PlayerSystemStadistics::setResetStage(bool reset) {
	resetStage = reset;
}

bool PlayerSystemStadistics::getResetStatusStage() {
	return resetStage;
}

void PlayerSystemStadistics::setCurrentStage(int value) {
	currentStage = value;
}

void PlayerSystemStadistics::pushNextStage() {
	currentStage++;
}

int PlayerSystemStadistics::getCurrentStage() {
	return currentStage;
}

void PlayerSystemStadistics::setCurrentPlayerNumber(int value) {
	currentPlayerNumber = value;
}

int PlayerSystemStadistics::getCurrentPlayerNumber() {
	return currentPlayerNumber;
}

void PlayerSystemStadistics::pushCorrectPlayer() {
	correctPlayer++;
}

int PlayerSystemStadistics::getCorrectPlayer() {
	return correctPlayer;
}

void PlayerSystemStadistics::pushErrorPlayer() {
	errorPlayer++;
}

int PlayerSystemStadistics::getErrorPlayer() {
	return errorPlayer;
}

void PlayerSystemStadistics::resetStadisticsPlayer() {
	errorPlayer = 0;
	correctPlayer = 0;
}

void PlayerSystemStadistics::sendSkipTutorialNotification() {
	tutorialSkip = true;
}

bool PlayerSystemStadistics::getSkipTutorialNotification() {
	if (tutorialSkip) {
		tutorialSkip = false;
		return true;
	}
	return false;
}

bool PlayerSystemStadistics::getSkipTutorialStatus() {
	return tutorialSkip;
}

void PlayerSystemStadistics::sendEndLoopTutorial() {
	tutorialLoop = false;
}

bool PlayerSystemStadistics::getEndLoopTutorial() {
	return tutorialLoop;
}

char* PlayerSystemStadistics::getScorePlayer() {
	static char buffer[50];
	sprintf(buffer, "Correctas: %d - Incorrectas: %d", correctPlayer,errorPlayer);
	return buffer;
}