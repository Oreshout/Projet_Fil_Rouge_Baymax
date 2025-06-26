#include "settings_ChambouleTout.h"

int pi;

void initServoMoteur()
{
    set_mode(pi, servo_pin_Lancer, PI_OUTPUT); // Met le GPIO du servo en mode sortie
    set_servo_pulsewidth(pi, servo_pin_Lancer, 500); // Position initiale du servo
    usleep(500000); // Pause de 0.5 seconde pour laisser le temps au servo de se positionner
}

void ActivationServoMoteurLancer()
{
    set_mode(pi, servo_pin_Lancer, PI_OUTPUT); 
    set_servo_pulsewidth(pi, servo_pin_Lancer, 1500); // Position finale
    sleep(10); // Attendre que le servo se positionne
    set_servo_pulsewidth(pi, servo_pin_Lancer, 500); // Position finale

}


int main()
{
    pi = pigpio_start(NULL, NULL); // Démarre la bibliothèque pigpio pour le contrôle des GPIO

    initServoMoteur(); // Initialisation du servo moteur

    scanf("Démarrage du test de lancement et de recharge du servo moteur...\n");

    ActivationServoMoteurLancer(); // Active le servo moteur pour recharger
    // Attendre que le servo se positionne

    pigpio_stop(pi); // Arrête la bibliothèque pigpio
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}
