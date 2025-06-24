#include "settings_PecheAuxCanards.h"

int pi;

int DetectionMarker()
{
    int distance = -1;
    struct marker *detection = get_markers(30);

    if (detection != NULL && detection->id != -1) 
    {
        distance = detection->z;
        printf("Detection : Marqué à %d cm\n", distance);
    } 
    else
    {
        printf("Detection : Aucun marqueur détecté\n");
    }

    return distance;
}

bool DetectionMarkerExist()
{
    struct marker *DetectionMarker = get_markers(30);
    
    if (DetectionMarker->id != -1) // Si un marqueur est détecté
    {
        printf("BOOL : Marqueur trouvé: numéro %d à %dcm de distance. x=%d y=%d\n", DetectionMarker->id, DetectionMarker->z, DetectionMarker->x, DetectionMarker->y);
        return true;
    }
    
    return false;
}


void* distance_update(void* arg)
{
    while (1) 
    {
        struct marker *markers = get_markers(30);
        if (markers == NULL) continue;

        struct marker *m;
        for (m = markers; m->id != -1; m++) 
        {
            printf("Marqueur trouvé: numéro %d à %dcm de distance. x=%d y=%d\n", m->id, m->z, m->x, m->y);
        }
        usleep(500000); // Petite pause pour éviter d'inonder le terminal
    }

    return NULL;
}

void GestionAttrape()
{
    // Implémentez ici la logique pour attraper le marqueur
    printf("Attrape du marqueur en cours...\n");
  
    set_mode(pi, servo_pin, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pin, 1750); // Position initiale 
    usleep(500000); // Pause de 0.5 seconde pour simuler l'attrape
}

void GestionLache()
{
    // Implémentez ici la logique pour attraper le marqueur
    printf("Attrape du marqueur en cours...\n");
  
    set_mode(pi, servo_pin, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pin, 1500); // Position initiale 
    usleep(500000); // Pause de 0.5 seconde pour simuler l'attrape
}




int main()
{
    pi = pigpio_start(NULL, NULL); // Démarre la bibliothèque pigpio pour le contrôle des GPIO

    float kp = 4.0f; // Valeurs conseillées pour le contrôleur PI
    float ki = 2.0f;

    MotorController motorL; // Création de lobjet contrôleur moteur
    MotorController_init(&motorL, pi, GPIO_FORWARD_L, GPIO_BACKWARD_L, GPIO_MOTOR_CONTROL_L); // Initialisation du contrôleur moteur

    MotorController motorR; // Création de lobjet contrôleur moteur
    MotorController_init(&motorR, pi, GPIO_FORWARD_R, GPIO_BACKWARD_R, GPIO_MOTOR_CONTROL_R); // Initialisation du contrôleur moteur

    MotorController_setStartPower(&motorL, 110);
    MotorController_setController(&motorL, kp, ki);

    MotorController_setStartPower(&motorR, 110);
    MotorController_setController(&motorR, kp, ki);

    MotorController_stop(&motorL);
    MotorController_stop(&motorR);


    printf("Démarrage du programme de détection de marqueurs...\n");

  //? Ajout Distanceupdate

    while(true)
    {
        if(DetectionMarkerExist()) // Si un marqueur est détecté
        {
            DetectionMarker(); // Vérifie si un marqueur est détecté
            printf("Un marqueur a été détecté à %dcm.\n", DetectionMarker()); // Affiche la distance du marqueur détecté
            gpio_write(pi, GPIO_FORWARD_L, PI_HIGH); // Avance les moteurs
            gpio_write(pi, GPIO_FORWARD_R, PI_HIGH);
            usleep(100000); // Avance pendant 0.1 seconde
            DetectionMarker(); // Vérifie si un marqueur est détecté
            printf("Un marqueur a été détecté à %dcm.\n", DetectionMarker());
            gpio_write(pi, GPIO_FORWARD_L, PI_LOW); // Arrêt des moteurs
            gpio_write(pi, GPIO_FORWARD_R, PI_LOW); 
            printf("Arrêt des moteurs après avoir détecté un marqueur.\n");
            if(DetectionMarker() < 10) // Si le marqueur est à moins de 5 cm
            {
                printf("Le marqueur est à moins de 5 cm, le robot va attraper le marqueur.\n");
                // Appel de la fonction pour attraper le marqueur
                GestionAttrape(); // Gestion de l'attrape du marqueur
                usleep(500000); // Pause de 0.5 seconde pour éviter une boucle trop rapide
                printf("Le marqueur a été attrapé.\n");
            }
            else
            {
                printf("Le marqueur est trop loin pour être attrapé.\n");
            }
        }
        else
        {
            printf("Aucun marqueur détecté, le robot va avancer.\n");
            gpio_write(pi, GPIO_FORWARD_L, PI_LOW); // Arrêt des moteurs
            gpio_write(pi, GPIO_FORWARD_R, PI_LOW);
            printf("Arrêt des moteurs après avoir avancé.\n");
            GestionLache(); // Gestion du lâcher du marqueur
            usleep(500000); // Pause de 0.5 seconde pour éviter une boucle
        }

    }

    pigpio_stop(pi); // Arrête la bibliothèque pigpio
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}