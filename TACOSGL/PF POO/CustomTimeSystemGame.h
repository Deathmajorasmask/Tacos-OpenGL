#pragma once

#include <iostream>
#include <chrono>

class CustomTimeSystemGame {
private:
    std::chrono::steady_clock::time_point startClock; // Marca inicial
    bool isEnd; // Estado de finalización
    bool stopClock; // Indica si se detuvo manualmente

public:
    // Constructor predeterminado
    CustomTimeSystemGame()
        : startClock(std::chrono::steady_clock::now()),
        isEnd(false),
        stopClock(false) {}

    // setRunForSeconds

    // Método que se ejecuta hasta que transcurra el tiempo o se detenga manualmente
    bool setRunUntilSeconds(int seconds) {
        if (stopClock) {
            return false; // Si está stopClock, indica que ya no debe ejecutarse
        }

        auto ahora = std::chrono::steady_clock::now();
        auto duracion = std::chrono::duration_cast<std::chrono::seconds>(ahora - startClock).count();

        if (duracion >= seconds) {
            // Reinicia automáticamente el tiempo inicial
            startClock = std::chrono::steady_clock::now();
            isEnd = true; // Marca que el tiempo ha terminado
            return false;   // Indica que ya se completaron los segundos
        }

        isEnd = false;  // Aún no ha terminado
        return true;    // Aún está dentro del tiempo permitido
    }

    // Método que consulta si el tiempo ya terminó
    bool isRunUntilSecondsFinish() const {
        return isEnd;
    }

    // Método para detener la ejecución manualmente
    void setStopUntilSeconds() {
        stopClock = true;
    }

    // Método para reiniciar el temporizador y habilitar la ejecución nuevamente
    void setReebotUntilSeconds() {
        startClock = std::chrono::steady_clock::now();
        isEnd = false;
        stopClock = false;
    }
};