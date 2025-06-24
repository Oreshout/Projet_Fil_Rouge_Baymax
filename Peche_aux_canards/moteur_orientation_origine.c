#include "settings_PecheAuxCanards.h"

int pi;

void ServoMoteurOrientationOrigine()
{
    set_mode(pi, servo_pin, PI_OUTPUT);
    // Position finale
    set_servo_pulsewidth(pi, servo_pin, 1500); // Position finale pour le servo droit
}

int main()
{
    pi = pigpio_start(NULL, NULL); // Démarre la bibliothèque pigpio pour le contrôle des GPIO

    ServoMoteurOrientationOrigine(); // Appelle la fonction pour positionner les servos à l'origine

    pigpio_stop(pi); // Arrête la bibliothèque pigpio
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}