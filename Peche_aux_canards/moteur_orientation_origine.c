#include "settings_PecheAuxCanards.h"

int pi;

void ServoMoteurOrientationOrigine()
{
    set_mode(pi, servo_pinR, PI_OUTPUT);
    set_mode(pi, servo_pinL, PI_OUTPUT);
    // Position finale
    set_servo_pulsewidth(pi, servo_pinR, 1500); // Position finale pour le servo droit
    set_servo_pulsewidth(pi, servo_pinL, 1500); // Position finale pour le servo gauche
}

int main()
{
    pi = pigpio_start(NULL, NULL); // Démarre la bibliothèque pigpio pour le contrôle des GPIO

      float kp = 4.0f; // Valeurs conseillées pour le contrôleur PI
    float ki = 2.0f;

    float speed = 50.f;

    MotorController motorL; // Création de l'objet contrôleur moteur
    MotorController_init(&motorL, pi, GPIO_FORWARD_L, GPIO_BACKWARD_L, GPIO_MOTOR_CONTROL_L); // Initialisation du contrôleur moteur

    MotorController motorR; // Création de l'objet contrôleur moteur
    MotorController_init(&motorR, pi, GPIO_FORWARD_R, GPIO_BACKWARD_R, GPIO_MOTOR_CONTROL_R); // Initialisation du contrôleur moteur

    MotorController_setStartPower(&motorL, 110);
    MotorController_setController(&motorL, kp, ki);

    MotorController_setStartPower(&motorR, 110);
    MotorController_setController(&motorR, kp, ki);

    MotorController_stop(&motorL);
    MotorController_stop(&motorR);

    ServoMoteurOrientationOrigine(); // Appelle la fonction pour positionner les servos à l'origine

    pigpio_stop(pi); // Arrête la bibliothèque pigpio
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}