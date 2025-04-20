#pragma once
#include <windows.h>
#include <stdio.h>

enum ingredients {
	TORTILLA,
	TORTILLAHARINA,
	CARNECERDO,
	CARNEASADA,
	PESCADO,
	CAMARON,
	BARBACOA,
	CEBOLLA,
	REPOLLO,
	CILANTRO,
	SALSAROJA,
	SALSAVERDE,
	HABANERO,
	LIMON,
	PINA,
	CREMA,
	QUESO
};

struct listActionPlayer {
	int id;
	listActionPlayer* next;
	listActionPlayer* last;
};

class WorldSystemLevels
{
private:
	listActionPlayer* headList;
	listActionPlayer* endList;

	bool renderNotification;
	int countOccurrences(int value) const;
public:
	WorldSystemLevels();
	~WorldSystemLevels();

	void sendRenderNotification();
	bool getRenderNotification();

	void pushActionsInHeap(int value);
	void pushActions(int value);
	void showActions();
	void showActionsInverse();
	void deleteActions();

	bool compareActionsWithCpu(WorldSystemLevels* listActionComputer) const;
};