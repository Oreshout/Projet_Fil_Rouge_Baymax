#include "settings_PecheAuxCanards.h"

int pi;

void testR(int pi)
{
    set_mode(pi, servo_pinR, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pinR, 1000); // Position initiale
    sleep(5);
    set_servo_pulsewidth(pi, servo_pinR, 500); // Position finale
}

void testL(int pi)
{
    set_mode(pi, servo_pinL, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pinL, 1000); // Position initiale
    sleep(5);
    set_servo_pulsewidth(pi, servo_pinL, 500); // Position finale
}

int main()
{
    pi = pigpio_start(NULL, NULL); // Démarre la bibliothèque pigpio pour le contrôle des GPIO
    testR(pi); // Appelle la fonction de test Right
    testL(pi); // Appelle la fonction de test Left
    
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}