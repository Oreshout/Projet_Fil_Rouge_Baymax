#include "settings_ChambouleTout.h"

int pi;

bool DetectionMarkerExist()
{
    struct marker *markers = get_markers(30); // Récupération des marqueurs de 51mm de côté (à modifier en fonction de vos marqueurs !)
    
    if (markers->id != -1) // Si un marqueur est détecté
    {
        printf("Marqueur trouvé: numéro %d à %dcm de distance. x=%d y=%d\n", markers->id, markers->z, markers->x, markers->y);
        return true;
    }
    
    return false;
}

int DetectionMarker()
{
    int distance = 0;
    struct marker *markers = get_markers(30); // Récupération des marqueurs de 51mm de côté (à modifier en fonction de vos marqueurs !)
    
    if (markers->id != -1) // Si un marqueur est détecté
    {
        distance = markers->z;
        printf("Marqué à %d cm\n", distance);
    }
    
    return distance;
}


void positionRobot(MotorController motorL, MotorController motorR)
{
    bool Touch = DetectionMarkerExist(); // Vérifie si un marqueur est détecté

    if(Touch == false) // Si un marqueur est détecté
    {
        gpio_write(pi, GPIO_BACKWARD_L, PI_HIGH);
        gpio_write(pi, GPIO_BACKWARD_R, PI_HIGH);
        usleep(500000); // Avance pendant 0.5 seconde
        turn(&motorL, &motorR, 90, 60.f); // Tourne à droite de 90 degrés  
        usleep(500000); // Attendre 0.5 seconde pour le mouvement
        drive(&motorL, &motorR,20.f, 60.f); // Avance à une vitesse de 60 cm/s sur 20cm
        usleep(500000); // Attendre 0.5 seconde pour le mouvement
        turn(&motorL, &motorR, -90, 60.f); // Tourne à droite de 90 degrés
        usleep(500000); // Attendre 0.5 seconde pour le mouvement
    }    
}

int main()
{
    pi = pigpio_start(NULL, NULL); // Démarre la bibliothèque pigpio pour le contrôle des GPIO

    MotorController motorL; // Création de l'objet contrôleur moteur
    MotorController_init(&motorL, pi, GPIO_FORWARD_L, GPIO_BACKWARD_L, GPIO_MOTOR_CONTROL_L); // Initialisation du contrôleur moteur

    MotorController motorR; // Création de l'objet contrôleur moteur
    MotorController_init(&motorR, pi, GPIO_FORWARD_R, GPIO_BACKWARD_R, GPIO_MOTOR_CONTROL_R); // Initialisation du contrôleur moteur

    positionRobot(motorL, motorR); // Positionne le robot

    pigpio_stop(pi); // Arrête la bibliothèque pigpio
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}
