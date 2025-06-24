#include "settings_PecheAuxCanards.h"

int pi;

int DetectionMarker()
{
    int distance = 0;
    struct marker *DetectionMarker = getmarkers(30);
   
    distance = DetectionMarker->z;
    printf("Marqué à %d cm\n", distance);
    
    return distance;
}

bool DetectionMarkerExist()
{
    struct marker *DetectionMarker = getmarkers(30);
    
    if (DetectionMarker->id != -1) // Si un marqueur est détecté
    {
        printf("Marqueur trouvé: numéro %d à %dcm de distance. x=%d y=%d\n", DetectionMarker->id, DetectionMarker->z, DetectionMarker->x, DetectionMarker->y);
        return true;
    }
    
    return false;
}

void GestionMoteurRoueAvant(MotorController motorL, MotorController motorR)
{
    gpio_write(pi, GPIO_FORWARD_L, PI_HIGH);
    gpio_write(pi, GPIO_FORWARD_R, PI_HIGH);
}

void GestionMoteurRoueArriere(MotorController motorL, MotorController motorR)
{
    gpio_write(pi, GPIO_BACKWARD_L, PI_HIGH);
    gpio_write(pi, GPIO_BACKWARD_R, PI_HIGH);
}

void GestionMoteurRoueArret(MotorController motorL, MotorController motorR)
{
    gpio_write(pi, GPIO_FORWARD_L, PI_LOW);
    gpio_write(pi, GPIO_FORWARD_R, PI_LOW);
    gpio_write(pi, GPIO_BACKWARD_L, PI_LOW);
    gpio_write(pi, GPIO_BACKWARD_R, PI_LOW);
}

void InitMoteur()
{
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
}


void GestionServoMoteurHaut() //! A travailler en fonction du schéma
{
    
    set_mode(pi, servo_pinR, PI_OUTPUT);
    set_mode(pi, servo_pinL, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pinR, 1000); // Position initiale // ! RIGHT
    set_servo_pulsewidth(pi, servo_pinL, val_miroir); // Position initiale // ! LEFT
}

int main()
{
    pi = pigpio_start(NULL, NULL); // Démarre la bibliothèque pigpio pour le contrôle des GPIO

    int distance = DetectionMarker(); // Appelle la fonction de détection de marqueur
    printf("Distance détectée: %d cm\n", distance);

    if (DetectionMarkerExist()) // Vérifie si un marqueur est détecté
    {
        printf("Un marqueur a été détecté.\n");
    }
    else
    {
        printf("Aucun marqueur n'a été détecté.\n");
    }

    InitMoteur(); // Initialise les moteurs

    while(distance > 5)
    {
        GestionMoteurRoueAvant(motorL, motorR); // Gère les roues du moteur
        sleep(1); // Attendre 1 seconde
    }

    GestionMoteurRoueArret(motorL, motorR); // Arrête les roues du moteur

    pigpio_stop(pi); // Arrête la bibliothèque pigpio
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}