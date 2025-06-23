#include "settings.h"

int pi = pigpio_start(NULL, NULL); // Démarre la bibliothèque pigpio

void test(pi)
{
    set_mode(pi, servo_pin, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pin, 500); // Position initiale
    sleep(5);
}

int main(pi)
{
    test(); // Appelle la fonction de test
    
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}