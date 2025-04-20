#ifndef __Level_01
#define __Level_01

#include <gl\GLU.h>
#include <gl\GL.h>
#include "SkyDome.h"
#include "Terrain.h"
#include "TerrainEx.h"
#include "Model.h"
#include "Camera.h"
#include <stdlib.h>
#include "OpenMove.h"
#include "nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg_gl.h"

#include "WorldSystemLevels.h"
#include "PlayerSystemStadistics.h"
#include "SoundSystemLevels.h"
#include "AnimationsSystemLevels.h"
#include "CustomTimeSystemGame.h"

class Level_01
{
private:
	bool isEnableOrderKeyboard = false;
	bool isCuteTacoShow = false;
	bool isSadTacoShow = false;
	CustomTimeSystemGame* timeSystem;
	SoundSystemLevels* SSLKeyOrderSound;
	SoundSystemLevels* SSLOrderClientSound;
	SoundSystemLevels* SSLSystemVGSound;
	SoundSystemLevels* SSLTutorialLoopSound;
	SoundSystemLevels* SSLBackgroundSoundtrack;
	std::string pathSoundtrackLvl1 = "sounds/Level_01_Trail_Dance.wav";
	std::string pathOrderStage0 = "sounds/ordersLevel1/orderStage0.wav";
	std::string pathOrderStage1 = "sounds/ordersLevel1/orderStage1.wav";
	std::string pathOrderStage2 = "sounds/ordersLevel1/orderStage2.wav";
	std::string pathOrderStage3 = "sounds/ordersLevel1/orderStage3.wav";
	std::string pathOrderStage4 = "sounds/ordersLevel1/orderStage4.wav";
	std::string pathOrderStage5 = "sounds/ordersLevel1/orderStage5.wav";
	std::string pathOrderStage6 = "sounds/ordersLevel1/orderStage6.wav";
	std::string pathOrderStage7 = "sounds/ordersLevel1/orderStage7.wav";
	std::string pathOrderStage8 = "sounds/ordersLevel1/orderStage8.wav";
	std::string pathOrderStage9 = "sounds/ordersLevel1/orderStage9.wav";
	std::string pathOrderStage10 = "sounds/ordersLevel1/orderStage10.wav";
	std::string pathSysEndLevel = "sounds/Sys_EndLevel.wav";
	std::string pathSysCorrectOrder = "sounds/Sys_CorrectOrder_treasure_2066.wav";
	std::string pathSysErrorOrder = "sounds/Sys_ErrorOrder_beep_fail_2964.wav";
	std::string pathSysAceptOption = "sounds/Sys_AceptOption.wav";
	std::string pathKeyPressAlertSweep = "sounds/KeyPress_alert_sweep_236.wav";
	std::string pathKeyPressRetroClick = "sounds/KeyPress_retro_click_237.wav";
	std::string pathKeyPressTap = "sounds/KeyPress_tap_2073.wav";
	std::string pathKeyPressMartialPunch = "sounds/KeyPress_martial_arts_punch_2047.wav";
	std::string pathKeyPressSmoothBeep = "sounds/KeyPress_point_smooth_beep_230573.wav";
	std::string pathKeyPressWhooshPro = "sounds/KeyPress_whoosh_pro_sfx_223360.wav";
	std::string pathKeyPressWoosh = "sounds/KeyPress_woosh_230554.wav";
	std::string pathKeyPressExplosion = "sounds/KeyPress_explosion_43814.wav";
	std::string pathKeyPressFillerSfx = "sounds/KeyPress_filler_sfx_246910.wav";
	std::string pathKeyPressGameUi = "sounds/KeyPress_game_ui685099.wav";

	NVGcontext* vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
	int font = nvgCreateFont(vg, "default", "fonts/Roboto-Bold.ttf");
	RECT rect;
	int heightRender = 720;
	int widthRender = 1080;

	EDXFramework::Model* cuteTaco, * sadTaco, * lowTaco, * particleTacoM, * particleTacoS;

	AnimationsSystemLevels* animLowTaco;

	WorldSystemLevels *_actionsPlayerList, *_actionsComputerList;
	PlayerSystemStadistics* _playerSystemStadistics;

public:
	Level_01(HWND hWnd) {

		if (font == -1) {
			nvgDeleteGL3(vg);
			MessageBox(hWnd, "nvgCreateFont", "Error", MB_OK);
		}

		GLfloat AmbMat[] = { 1, 1, 1, 1 };
		GLfloat AmbPos[] = { 0, 1, 50, 1 };

		GLfloat diffuse[] = { 1.0f, 0.5f, 0.0f, 0.5f };
		GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, AmbPos);
		// Enable to reflect light
		glEnable(GL_COLOR_MATERIAL);

		cuteTaco = new EDXFramework::Model("models//CuteTaco//CuteTaco.obj", "models//CuteTaco//Taco_Base_Color.bmp", 1);
		sadTaco = new EDXFramework::Model("models//CuteTaco//SadTaco.obj", "models//CuteTaco//Taco_Base_Color.bmp", 1);
		lowTaco = new EDXFramework::Model("models//Taco//LowTaco.obj", "models//Taco//Materil.166_baseColor.bmp", 1);
		particleTacoM = new EDXFramework::Model("models//CuteTaco//ParticleTacoM//ParticleTacoM.obj", "models//CuteTaco//Taco_Base_Color.bmp", 1);
		particleTacoS = new EDXFramework::Model("models//CuteTaco//ParticleTacoS//ParticleTaco.obj", "models//CuteTaco//Taco_Base_Color.bmp", 1);

		timeSystem = new CustomTimeSystemGame();

		animLowTaco = new AnimationsSystemLevels();
		animLowTaco->setAnimation(-0.0f, -5.0f);

		SSLKeyOrderSound = new SoundSystemLevels();
		SSLOrderClientSound = new SoundSystemLevels();
		SSLSystemVGSound = new SoundSystemLevels();
		SSLTutorialLoopSound = new SoundSystemLevels();
		SSLBackgroundSoundtrack = new SoundSystemLevels();
		SSLBackgroundSoundtrack->SoundSystemLevelsStereo(pathSoundtrackLvl1, 0.05f, true);

		_actionsPlayerList = new WorldSystemLevels();
		_actionsComputerList = new WorldSystemLevels();

		_playerSystemStadistics = new PlayerSystemStadistics();
		_playerSystemStadistics->setDefaultConfigs();
		ordersClientsData(_playerSystemStadistics->getCurrentStage());
	}

	~Level_01() {

	}

	void actionsKeys(int keyPress) {
		if (isEnableOrderKeyboard){
			switch (keyPress)
			{
			case VK_ESCAPE:

				break;
			case VK_RETURN:

				break;
			case VK_UP:
			
				break;
			case VK_DOWN:

				break;
			case VK_LEFT:

				break;
			case VK_RIGHT:

				break;
			case 0x46: // F
				SSLKeyOrderSound->SoundSystemLevelsMono(pathKeyPressAlertSweep);
				_actionsPlayerList->pushActions(TORTILLA);
				break;
			case 0x44: // D
				SSLKeyOrderSound->SoundSystemLevelsMono(pathKeyPressRetroClick);
				_actionsPlayerList->pushActions(SALSAROJA);
				break;
			case 0x53: // S
				SSLKeyOrderSound->SoundSystemLevelsMono(pathKeyPressTap);
				_actionsPlayerList->pushActions(CILANTRO);
				break;
			case 0x41: // A
				SSLKeyOrderSound->SoundSystemLevelsMono(pathKeyPressMartialPunch);
				_actionsPlayerList->pushActions(CEBOLLA);
				break;
			case 0x4A: // J
				SSLKeyOrderSound->SoundSystemLevelsMono(pathKeyPressSmoothBeep);
				_actionsPlayerList->pushActions(CARNEASADA);
				break;
			case VK_SPACE: // SPACE
				_actionsPlayerList->sendRenderNotification();
				break;
			}
		}
		else {
			switch (keyPress)
			{
			case VK_ESCAPE:
				// Exit
				if (_playerSystemStadistics->getStatusEndLevelNotificaction()) {
					PostQuitMessage(0);
				}
				else {

				}
				break;
			case VK_RETURN:
				// Reebot
				if (_playerSystemStadistics->getStatusEndLevelNotificaction()) {
					_playerSystemStadistics->setDefaultConfigs();
					ordersClientsData(_playerSystemStadistics->getCurrentStage());
				}
				else {
				
				}
				break;
			case VK_UP:

				break;
			case VK_DOWN:

				break;
			case VK_LEFT:

				break;
			case VK_RIGHT:

				break;
			case 0x46: // F

				break;
			case 0x44: // D

				break;
			case 0x53: // S

				break;
			case 0x41: // A

				break;
			case 0x4A: // J

				break;
			case VK_SPACE: // SPACE
				if (_playerSystemStadistics->getStatusEndLevelNotificaction()) {
					_playerSystemStadistics->sendExitLevelNotification();
				}
				else {
					_playerSystemStadistics->sendSkipTutorialNotification();
					_actionsPlayerList->sendRenderNotification();
					isEnableOrderKeyboard = true;
				}
				// Next Level
				break;
			}
		}
	}

	void ordersClientsData(int orderStage) {
		switch (orderStage)
		{
		case 0:
			// level instructions
			SSLOrderClientSound->SoundSystemLevelsMono(pathOrderStage0);
			break;
		case 1:
			SSLOrderClientSound->SoundSystemLevelsMono(pathOrderStage1);
			_actionsComputerList->pushActions(TORTILLA);
			_actionsComputerList->pushActions(CARNEASADA);
			break;
		case 2:
			SSLOrderClientSound->SoundSystemLevelsMono(pathOrderStage2);
			_actionsComputerList->pushActions(TORTILLA);
			_actionsComputerList->pushActions(CARNEASADA);
			_actionsComputerList->pushActions(SALSAROJA);
			break;
		case 3:
			SSLOrderClientSound->SoundSystemLevelsMono(pathOrderStage3);
			_actionsComputerList->pushActions(TORTILLA);
			_actionsComputerList->pushActions(CARNEASADA);
			_actionsComputerList->pushActions(CILANTRO);
			_actionsComputerList->pushActions(CEBOLLA);
			_actionsComputerList->pushActions(SALSAROJA);
			break;
		case 4:
			SSLOrderClientSound->SoundSystemLevelsMono(pathOrderStage4);
			_actionsComputerList->pushActions(TORTILLA);
			_actionsComputerList->pushActions(CARNEASADA);
			_actionsComputerList->pushActions(CILANTRO);
			_actionsComputerList->pushActions(CEBOLLA);
			break;
		case 5:
			SSLOrderClientSound->SoundSystemLevelsMono(pathOrderStage5);
			_actionsComputerList->pushActions(TORTILLA);
			_actionsComputerList->pushActions(CARNEASADA);
			_actionsComputerList->pushActions(CILANTRO);
			_actionsComputerList->pushActions(SALSAROJA);
			break;
		case 6:
			SSLOrderClientSound->SoundSystemLevelsMono(pathOrderStage6);
			_actionsComputerList->pushActions(TORTILLA);
			_actionsComputerList->pushActions(CARNEASADA);
			_actionsComputerList->pushActions(SALSAROJA);
			break;
		case 7:
			SSLOrderClientSound->SoundSystemLevelsMono(pathOrderStage7);
			_actionsComputerList->pushActions(TORTILLA);
			_actionsComputerList->pushActions(CARNEASADA);
			_actionsComputerList->pushActions(CEBOLLA);
			break;
		case 8:
			SSLOrderClientSound->SoundSystemLevelsMono(pathOrderStage8);
			_actionsComputerList->pushActions(TORTILLA);
			_actionsComputerList->pushActions(CARNEASADA);
			_actionsComputerList->pushActions(CILANTRO);
			_actionsComputerList->pushActions(CEBOLLA);
			_actionsComputerList->pushActions(SALSAROJA);
			break;
		case 9:
			SSLOrderClientSound->SoundSystemLevelsMono(pathOrderStage9);
			_actionsComputerList->pushActions(TORTILLA);
			_actionsComputerList->pushActions(CARNEASADA);
			_actionsComputerList->pushActions(CARNEASADA);
			_actionsComputerList->pushActions(SALSAROJA);
			break;
		case 10:
			SSLOrderClientSound->SoundSystemLevelsMono(pathOrderStage10);
			_actionsComputerList->pushActions(TORTILLA);
			_actionsComputerList->pushActions(TORTILLA);
			_actionsComputerList->pushActions(CARNEASADA);
			_actionsComputerList->pushActions(CILANTRO);
			_actionsComputerList->pushActions(CEBOLLA);
			_actionsComputerList->pushActions(SALSAROJA);
			break;
		case 11:
			SSLOrderClientSound->SoundSystemLevelsMono(pathSysEndLevel);
			_playerSystemStadistics->sendEndLevelNotification();
			break;
		default:
			break;
		}
	}

	void render(HDC hDC, HWND hWnd) {

		// read windows dimentions
		if (GetWindowRect(hWnd, &rect)) {
			widthRender = rect.right - rect.left;
			heightRender = rect.bottom - rect.top;
		}
		// Canvas Text in Screen Scene
		nvgBeginFrame(vg, widthRender, heightRender, 1.0f);

		// SystemSound Notification
		if(SSLOrderClientSound->SoundSystemLevelsMonoBucle() == 0) {
			// End Order CPU
			if (!_playerSystemStadistics->getSkipTutorialStatus() && _playerSystemStadistics->getEndLoopTutorial()) {
				// Skip tutorial & End Sound
				ordersClientsData(_playerSystemStadistics->getCurrentStage());
			}
			if (SSLOrderClientSound->getSoundNotification() ) {
				ordersClientsData(_playerSystemStadistics->getCurrentStage());
			}
		}

		if (_playerSystemStadistics->getStatusEndLevelNotificaction()) {
			isEnableOrderKeyboard = false; // Change keyboard to Menu

			glPushMatrix();
			nvgFontSize(vg, 100.0f);
			nvgFontFaceId(vg, font);
			nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
			nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
			nvgText(vg, widthRender * 0.5f, heightRender * 0.5f, "Fin del juego", nullptr);
			glPopMatrix();

			glPushMatrix();
			nvgFontSize(vg, 40.0f);
			nvgFontFaceId(vg, font);
			nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
			nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
			nvgText(vg, (widthRender * 0.5f), (heightRender * 0.5f) + 100.0f, _playerSystemStadistics->getScorePlayer(), nullptr);
			glPopMatrix();
		}
		
		// render Notification for player send task
		if (_actionsPlayerList->getRenderNotification()) {
			SSLOrderClientSound->SoundSystemLevelsMonoStop();
			if(_playerSystemStadistics->getSkipTutorialNotification()) {
				SSLSystemVGSound->SoundSystemLevelsMono(pathSysAceptOption);
				_actionsComputerList->deleteActions();
				_playerSystemStadistics->pushNextStage();
				_playerSystemStadistics->sendEndLoopTutorial();
				SSLOrderClientSound->sendSoundNotification();
				_actionsPlayerList->deleteActions();
			}
			else {
				if (_actionsPlayerList->compareActionsWithCpu(_actionsComputerList) && &_actionsPlayerList != nullptr) {
					SSLSystemVGSound->SoundSystemLevelsMono(pathSysCorrectOrder);
					_actionsComputerList->deleteActions();
					_playerSystemStadistics->pushCorrectPlayer();
					_playerSystemStadistics->pushNextStage();
					SSLOrderClientSound->sendSoundNotification();
					timeSystem->setReebotUntilSeconds();  // Reebot timer
					isCuteTacoShow = true;
				}
				else {
					SSLSystemVGSound->SoundSystemLevelsMono(pathSysErrorOrder);
					_actionsComputerList->deleteActions();
					_playerSystemStadistics->pushErrorPlayer();
					SSLOrderClientSound->sendSoundNotification();
					timeSystem->setReebotUntilSeconds();  // Reebot timer
					isSadTacoShow = true;
				}
				_actionsPlayerList->deleteActions();
			}
		}

		if(isCuteTacoShow) {
			if (timeSystem->setRunUntilSeconds(1)) {
				// Cute Taco Render
				glPushMatrix();
				OpenMove::traslate(0.0, 1.0, -5.0);
				OpenMove::scale(0.5, 0.5, 0.5);
				cuteTaco->Draw();
				glPopMatrix();

				// Particle Left Render
				glPushMatrix();
				OpenMove::traslate(-2.0, 3.0, -5.0);
				OpenMove::scale(1.5, 1.5, 1.5);
				particleTacoS->Draw();
				glPopMatrix();

				// Particle Left Render
				glPushMatrix();
				OpenMove::traslate(-2.3, 2.3, -5.0);
				OpenMove::scale(0.6, 0.6, 0.6);
				particleTacoS->Draw();
				glPopMatrix();

				// Particle Left Render
				glPushMatrix();
				OpenMove::traslate(-1.9, 2.1, -5.0);
				OpenMove::scale(0.4, 0.4, 0.4);
				particleTacoS->Draw();
				glPopMatrix();

				// Particle Right Render
				glPushMatrix();
				OpenMove::traslate(2.0, 2.3, -5.0);
				particleTacoS->Draw();
				glPopMatrix();

				// Particle Right Render
				glPushMatrix();
				OpenMove::traslate(2.3, 1.6, -5.0);
				OpenMove::scale(0.5, 0.5, 0.5);
				particleTacoS->Draw();
				glPopMatrix();

				// Particle Right Render
				glPushMatrix();
				OpenMove::traslate(1.5, 2.8, -5.0);
				OpenMove::scale(0.3, 0.3, 0.3);
				particleTacoS->Draw();
				glPopMatrix();
			}
			else {
				isCuteTacoShow = false;
			}
		}

		if (isSadTacoShow) {
			if (timeSystem->setRunUntilSeconds(1)) {
				// Sad Taco Render
				glPushMatrix();
				OpenMove::traslate(0.0, 1.0, -5.0);
				OpenMove::scale(0.5, 0.5, 0.5);
				sadTaco->Draw();
				glPopMatrix();

				// Particle Left Render
				glPushMatrix();
				OpenMove::traslate(-1.7, 1.5, -3.0);
				OpenMove::scale(1.5, 1.5, 1.5);
				particleTacoS->Draw();
				glPopMatrix();

				// Particle Left Render
				glPushMatrix();
				OpenMove::traslate(-2.3, 2.2, -5.0);
				OpenMove::scale(0.6, 0.6, 0.6);
				particleTacoS->Draw();
				glPopMatrix();

				// Particle Left Render
				glPushMatrix();
				OpenMove::traslate(-1.9, 3.4, -5.0);
				OpenMove::scale(0.4, 0.4, 0.4);
				particleTacoS->Draw();
				glPopMatrix();

				// Particle Right Render
				glPushMatrix();
				OpenMove::traslate(2.0, 1.5, -5.0);
				particleTacoS->Draw();
				glPopMatrix();

				// Particle Right Render
				glPushMatrix();
				OpenMove::traslate(2.3, 1.0, -5.0);
				OpenMove::scale(0.5, 0.5, 0.5);
				particleTacoS->Draw();
				glPopMatrix();

				// Particle Right Render
				glPushMatrix();
				OpenMove::traslate(1.0, 1.8, -3.0);
				OpenMove::scale(0.3, 0.3, 0.3);
				particleTacoS->Draw();
				glPopMatrix();
			}
			else {
				isSadTacoShow = false;
			}
		}
		
		// Active Animations Objects
		animLowTaco->setAnimationBucle(UPANDDOWN);
		animLowTaco->setAnimationBucle(ROTATE360);

		for (int j = 1; j <= 6; j++)
		{
			for (int i = 1; i <= 3; i++)
			{
				glPushMatrix();
				OpenMove::traslate(6.0f * i - (3.0f * j), (animLowTaco->getPosition() + (3.0f * j)) - 5.0f, -10.0f);
				OpenMove::rotate(animLowTaco->getRotation() + 10.0f, 0, 1, 0);
				OpenMove::rotate(45.0f, 1, 0, 0);
				lowTaco->Draw();
				glPopMatrix();

				glPushMatrix();
				OpenMove::traslate(-6.0f * i + (3.0f * j), (animLowTaco->getPosition() + (3.0f * j)) - 5.0f, -10.0f);
				OpenMove::rotate(animLowTaco->getRotation() + 10.0f, 0, 1, 0);
				OpenMove::rotate(45.0f, 1, 0, 0);
				lowTaco->Draw();
				glPopMatrix();

			}
		}

		// render Text
		glPushMatrix();
		nvgFontSize(vg, 35.0f);
		nvgFontFaceId(vg, font);
		nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
		nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
		nvgText(vg, 10, 10, "Beta", nullptr);
		glPopMatrix();

		// End canvas Text in Screen Scene
		nvgBeginFrame(vg, widthRender, heightRender, 1.0f);
		nvgEndFrame(vg);
	}

	bool exitLevelSuccessfully() {
		return _playerSystemStadistics->getExitLevelStatus();
	}
};
#endif
