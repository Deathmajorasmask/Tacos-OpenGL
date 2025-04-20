#pragma once

#include <iostream>
#include <chrono>

class CustomTimeSystemGame {
private:
    std::chrono::steady_clock::time_point startClock; // Marca inicial
    bool isEnd; // Estado de finalizaci�n
    bool stopClock; // Indica si se detuvo manualmente

public:
    // Constructor predeterminado
    CustomTimeSystemGame()
        : startClock(std::chrono::steady_clock::now()),
        isEnd(false),
        stopClock(false) {}

    // setRunForSeconds

    // M�todo que se ejecuta hasta que transcurra el tiempo o se detenga manualmente
    bool setRunUntilSeconds(int seconds) {
        if (stopClock) {
            return false; // Si est� stopClock, indica que ya no debe ejecutarse
        }

        auto ahora = std::chrono::steady_clock::now();
        auto duracion = std::chrono::duration_cast<std::chrono::seconds>(ahora - startClock).count();

        if (duracion >= seconds) {
            // Reinicia autom�ticamente el tiempo inicial
            startClock = std::chrono::steady_clock::now();
            isEnd = true; // Marca que el tiempo ha terminado
            return false;   // Indica que ya se completaron los segundos
        }

        isEnd = false;  // A�n no ha terminado
        return true;    // A�n est� dentro del tiempo permitido
    }

    // M�todo que consulta si el tiempo ya termin�
    bool isRunUntilSecondsFinish() const {
        return isEnd;
    }

    // M�todo para detener la ejecuci�n manualmente
    void setStopUntilSeconds() {
        stopClock = true;
    }

    // M�todo para reiniciar el temporizador y habilitar la ejecuci�n nuevamente
    void setReebotUntilSeconds() {
        startClock = std::chrono::steady_clock::now();
        isEnd = false;
        stopClock = false;
    }
};