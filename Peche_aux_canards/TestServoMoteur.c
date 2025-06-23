#include "settings.h"

int pi;

void test(int pi)
{
    set_mode(pi, servo_pin, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pin, 1000); // Position initiale
    sleep(5);
    set_servo_pulsewidth(pi, servo_pin, 500); // Position finale
}

int main()
{
    pi = pigpio_start(NULL, NULL); // Démarre la bibliothèque pigpio pour le contrôle des GPIO
    test(pi); // Appelle la fonction de test
    
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}