#include "settings_PecheAuxCanards.h"
#include <pthread.h>

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

    pthread_t distanceThread;
    pthread_create(&distanceThread, NULL, distance_update, NULL);

    int detection = DetectionMarker(); // Appel de la fonction pour détecter un marqueur
    printf("Distance détectée : %d cm\n", detection);
    if(detection < 10)
    {
        printf("Le robot est trop proche du marqueur, il doit reculer.\n");
        gpio_write(pi, GPIO_BACKWARD_L, PI_HIGH);
        gpio_write(pi, GPIO_BACKWARD_R, PI_HIGH);
        usleep(500000); // Recule pendant 0.5 seconde
        gpio_write(pi, GPIO_BACKWARD_L, PI_LOW);
        gpio_write(pi, GPIO_BACKWARD_R, PI_LOW); // Arrêt des moteurs
    }
    else
    {
        printf("Le robot est à une distance acceptable du marqueur.\n");
    }

    pthread_join(distanceThread, NULL);
    pigpio_stop(pi); // Arrête la bibliothèque pigpio
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}