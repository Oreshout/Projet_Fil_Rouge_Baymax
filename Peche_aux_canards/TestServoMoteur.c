#include "settings_PecheAuxCanards.h"

int pi;

void test(int pi)
{
    int val = 1000;
    int val_miroir = 2000 - (val - 1000); 
    set_mode(pi, servo_pinR, PI_OUTPUT);
    set_mode(pi, servo_pinL, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pinR, 1000); // Position initiale // ! RIGHT
    set_servo_pulsewidth(pi, servo_pinL, val_miroir); // Position initiale // ! LEFT
    sleep(5);
    set_servo_pulsewidth(pi, servo_pinR, 500); // Position finale // ! RIGHT
    set_servo_pulsewidth(pi, servo_pinL, 500); // Position finale // ! LEFT

}

int main()
{
    pi = pigpio_start(NULL, NULL); // Démarre la bibliothèque pigpio pour le contrôle des GPIO
    test(pi); // Appelle la fonction de test Right
  
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}