#include "WorldSystemLevels.h"

WorldSystemLevels::WorldSystemLevels() {
    headList = nullptr;
    endList = nullptr;
};

WorldSystemLevels::~WorldSystemLevels() {
    listActionPlayer* currentActionPlayer = headList;
    while (currentActionPlayer != nullptr) {
        listActionPlayer* temp = currentActionPlayer;
        currentActionPlayer = currentActionPlayer->next;
        delete temp;
    }
};

void WorldSystemLevels::sendRenderNotification() {
    renderNotification = true;
}


bool WorldSystemLevels::getRenderNotification() {
    if (renderNotification) {
        renderNotification = false;
        return true;
    }
    return false;
}

void WorldSystemLevels::pushActionsInHeap(int value) {
    listActionPlayer* actionPlayer = new listActionPlayer();
    actionPlayer->id = value;
    actionPlayer->next = headList;
    actionPlayer->last = nullptr;

    if (headList != nullptr) {
        headList->last = actionPlayer;
    }
    else {
        endList = actionPlayer;
    }

    headList = actionPlayer;
}

void WorldSystemLevels::pushActions(int value) {
    listActionPlayer* actionPlayer = new listActionPlayer();
    actionPlayer->id = value;
    actionPlayer->next = nullptr;
    actionPlayer->last = endList;

    if (endList != nullptr) {
        endList->next = actionPlayer;
    }
    else {
        headList = actionPlayer;
    }

    endList = actionPlayer;
}

// Debug Config function - Show list actions player
void WorldSystemLevels::showActions() {
    char buffer[50];
    listActionPlayer* currentActionPlayer = headList;
    while (currentActionPlayer != nullptr) {
        sprintf(buffer, "Object: %d \n", currentActionPlayer->id);
        OutputDebugString(buffer);
        currentActionPlayer = currentActionPlayer->next;
    }
}

// Debug Config function - Show list actions player inverse
void WorldSystemLevels::showActionsInverse() {
    char buffer[50];
    listActionPlayer* currentActionPlayer = headList;
    while (currentActionPlayer != nullptr) {
        sprintf(buffer, "Object: %d \n", currentActionPlayer->id);
        OutputDebugString(buffer);
        currentActionPlayer = currentActionPlayer->last;
    }
    deleteActions();
}

void WorldSystemLevels::deleteActions() {
    listActionPlayer* currentActionPlayer = headList;
    while (currentActionPlayer != nullptr) {
        listActionPlayer* temp = currentActionPlayer;
        currentActionPlayer = currentActionPlayer->next;
        delete temp;
    }
    headList = nullptr;
    endList = nullptr;
}
int WorldSystemLevels::countOccurrences(int value) const
{
    int count = 0;
    listActionPlayer* currentAction = headList;
    while (currentAction != nullptr) {
        if (currentAction->id == value) {
            count++;
        }
        currentAction = currentAction->next;
    }
    return count;
}

bool WorldSystemLevels::compareActionsWithCpu(WorldSystemLevels* listActionComputer) const {
    if (headList == nullptr || endList == nullptr) {
        return false;
    }

    listActionPlayer* currentActionPlayer = headList;

    // We use a set of unique values to avoid counting the same value multiple times.
    while (currentActionPlayer != nullptr) {
        int value = currentActionPlayer->id;

        // Count occurrences of value in both lists
        int occurrencesInList1 = countOccurrences(value);
        int occurrencesInList2 = listActionComputer->countOccurrences(value);

        // Count occurrences in both lists
        if (occurrencesInList1 != occurrencesInList2) {
            return false;  // If occurrences do not match, return false
        }

        // Advance to the next non-repeated value
        currentActionPlayer = currentActionPlayer->next;
        while (currentActionPlayer != nullptr && currentActionPlayer->id == value) {
            currentActionPlayer = currentActionPlayer->next;  // Skip nodes with the same data
        }
    }
    // Verify that each element in the second list has the same occurrences in the first list
    listActionPlayer* currentActionCpu = listActionComputer->headList;
    while (currentActionCpu != nullptr) {
        int value = currentActionCpu->id;

        int ocurrenciasEnLista1 = countOccurrences(value);
        int ocurrenciasEnLista2 = listActionComputer->countOccurrences(value);

        if (ocurrenciasEnLista1 != ocurrenciasEnLista2) {
            return false;
        }

        currentActionCpu = currentActionCpu->next;
        while (currentActionCpu != nullptr && currentActionCpu->id == value) {
            currentActionCpu = currentActionCpu->next;
        }
    }

    return true;  // If all the elements and their occurrences match
}