#include "settings_ChambouleTout.h"

int pi;

void ActivationServoMoteurLancer()
{
    set_mode(pi, servo_pin_Lancer, PI_OUTPUT); 
    set_servo_pulsewidth(pi, servo_pin_Recharge, 1000); // Position initiale
    sleep(5); // Attendre que le servo se positionne
    set_mode(pi, servo_pin_Recharge, PI_OUTPUT); 
    set_servo_pulsewidth(pi, servo_pin_Lancer, 1000); // Position finale
    sleep(10); // Attendre que le servo se positionne
    set_servo_pulsewidth(pi, servo_pin_Lancer, 500); // Position finale
    set_servo_pulsewidth(pi, servo_pin_Recharge, 500);
}


int main()
{
    pi = pigpio_start(NULL, NULL); // Démarre la bibliothèque pigpio pour le contrôle des GPIO

    scanf("Démarrage du test de lancement et de recharge du servo moteur...\n");

    ActivationServoMoteurLancer(); // Active le servo moteur pour recharger
    // Attendre que le servo se positionne

    pigpio_stop(pi); // Arrête la bibliothèque pigpio
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}
