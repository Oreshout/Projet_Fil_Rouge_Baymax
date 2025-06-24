#include "settings_ChambouleTout.h"

/**
*
*      CODE : Chamboule TOUT
*
*      ! Detecter les différents marqueurs et viser les goblets les plus bas pour en faire tomber le plus
*      ! possible 
*
*
*
*
*
*
*/

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

void ActivationServoMoteur()
{
    set_mode(pi, servo_pin, PI_OUTPUT); 
    set_servo_pulsewidth(pi, servo_pin, 1000); // Position initiale
    sleep(5); // Attendre que le servo se positionne
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

bool DistanceoOptimal()
{
    if(distance == DISTANCE_TIR_OPTIMAL) // Si le marqueur est à la distance optimale
    {
        printf("Marqueur à la distance optimale pour un tir.\n");
        return true;
    }
    else
    {
        printf("Marqueur hors de portée pour un tir optimal.\n");
        return false;
    }
}

void Tir()
{
    int distance = DetectionMarker();

    if(DistanceOptimal == true) // Si le marqueur est à la distance optimale
    {
       
    }
    else
    {
        printf("Marqueur hors de portée pour un tir optimal.\n");
    }
}


int main()
{
    pi = pigpio_start(NULL, NULL); // Démarre la bibliothèque pigpio pour le contrôle des GPIO

    bool Touch = false;
}