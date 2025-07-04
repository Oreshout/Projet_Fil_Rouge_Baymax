#include "settings_PecheAuxCanards.h"

/**
*
*
*    CODE : Pêche aux canards
*   * Attention : Revoir droite Gauche pour les servos
*/

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

int GestionMarker()
{
    struct marker *markers = get_markers(30); // Récupération des marqueurs de 51mm de côté (à modifier en fonction de vos marqueurs !)
    
    if (markers->id != -1) // Si un marqueur est détecté
    {
        printf("ID : Marqueur trouvé: numéro %d\n", markers->id);
    }

    return markers->id; // Retourne l'id du marqueur détecté
}

void GestionBras()
{

}

void GestionServoMoteurHaut()
{
    int val = 1000;
    int val_miroir = 2000 - (val - 1000); 
    set_mode(pi, servo_pinR, PI_OUTPUT);
    set_mode(pi, servo_pinL, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pinR, 1000); // Position initiale // ! RIGHT
    set_servo_pulsewidth(pi, servo_pinL, val_miroir); // Position initiale // ! LEFT
}

void GestionServoMoteurBas()
{
    set_mode(pi, servo_pinR, PI_OUTPUT);
    set_mode(pi, servo_pinL, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pinR, 500); // Position finale // ! RIGHT
    set_servo_pulsewidth(pi, servo_pinL, 500); // Position finale // ! LEFT
}

void GestionMoteur()
{

}

void GestionBouton()
{
    set_mode(pi, Bouton_pin, PI_INPUT); // Met le GPIO 21 en mode entrée
    set_pull_up_down(pi, Bouton_pin, PI_PUD_DOWN); // Active la résistance de rappel sur le GPIO 20

    while (true) 
    {
        int state = gpio_read(pi, Bouton_pin); // Lecture de l'état du bouton poussoir
        
        if (state == PI_HIGH) 
        { // Sitf("Bouton appuyé\n");
          GestionServoMoteurHaut();
        } 
        else 
        {
            GestionServoMoteurBas();
        }

        sleep(1);
    }
}

void GestionAttrape()
{
    int distance = DetectionMarker();
    
    if (distance < 5) // Si le marqueur est à moins de 5 cm
    {
        GestionBras();
        GestionServoMoteurHaut();
        sleep(1); // Attendre que le bras se positionne
    }
}

void GestionLache()
{
    int distance = DetectionMarker();
    
    if (distance < 5) // Si le marqueur est à moins de 5 cm
    {
        GestionBras();
        GestionServoMoteurBas();
        sleep(1); // Attendre que le bras se positionne
    }
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

void GestionMouvementRobot(MotorController motorL, MotorController motorR)
{
    turn(&motorL, &motorR, 360, 60.f);
    usleep(200000); 
    drive(&motorL, &motorR,20, 60.f); // Avance à une vitesse de 60 cm/s
    usleep(200000); 
    turn(&motorL, &motorR, 90, 60.f); // Tourne à droite de 90 degrés
    usleep(200000);
    drive(&motorL, &motorR,20, 60.f); // Avance à une vitesse de 60 cm/s
    usleep(200000);
    turn(&motorL, &motorR, -90, 60.f); // Tourne à gauche de 90 degrés
    usleep(200000);
    drive(&motorL, &motorR,20,  60.f); // Avance à une vitesse de 60 cm/s
}

void AvancerUnPetitPeu(MotorController motorL, MotorController motorR)
{
    gpio_write(pi, GPIO_FORWARD_L, PI_HIGH);
    gpio_write(pi, GPIO_FORWARD_R, PI_HIGH);
    usleep(200000); // Avance pendant 0.2 seconde
    gpio_write(pi, GPIO_FORWARD_L, PI_LOW);
    gpio_write(pi, GPIO_FORWARD_R, PI_LOW); // Arrêt des moteurs
}

bool parcourirLeTab(int TAB[30])
{
    int temp = GestionMarker(); // Récupération de l'ID du marqueur

    for(int i = 0; i < 30; i++)
    {
        if(TAB[i] == temp) // Si l'ID est déjà présent
        {
            return false; // Il est déjà dans le tableau
        }
    }
    return true; // Il n'est pas encore dans le tableau
}

int main()
{
    pi = pigpio_start(NULL, NULL);
    int TabRecupMerker[30];
    int MarkerIDTrouve = 0; // Initialisation de l'ID du marqueur
    int distance = 0; // Initialisation de la distance

    MotorController motorL; // Création de l'objet contrôleur moteur
    MotorController motorR; // Création de l'objet contrôleur moteur

    for(int i = 0; i < 30; i++)
    {
        TabRecupMerker[i] = 0; // Initialisation du tableau de marqueurs
    }

    InitMoteur(); // Initialisation des moteurs

    while(true)
    {
        printf("je suis dans le while true");

        //if(parcourirLeTab(TabRecupMerker) == true)
        //{
            printf("Le Marker n'est pas dans le tableau, le robot va avancer.\n");

            if(DetectionMarkerExist() == true) // Si un marqueur est détecté
            {
                printf("Un marqueur a été détecté, le robot va avancer.\n");

                distance = DetectionMarker(); // Récupération de la distance du marqueur
                printf("Distance du marqueur : %d cm\n", distance);

                gpio_write(pi, GPIO_FORWARD_L, PI_HIGH);
                gpio_write(pi, GPIO_FORWARD_R, PI_HIGH);

                while(distance > 10)
                {
                    printf("Je suis rentré dans le While\n");
                    distance = DetectionMarker(); // Récupération de la distance du marqueur
                }
                
                usleep(500000); // Pause de 0.5 seconde pour éviter une boucle trop rapide
                printf("Je suis sorti du While\n");
                gpio_write(pi, GPIO_FORWARD_L, PI_LOW);
                gpio_write(pi, GPIO_FORWARD_R, PI_LOW);  
                
                printf("Je suis juste devant le Goblet\n");
                AvancerUnPetitPeu(motorL, motorR); // Avance un petit peu pour se rapprocher du marqueur
                printf("Je vais attraper le marqueur\n");
                GestionAttrape(); // Gestion de l'attrape du marqueur

                gpio_write(pi, GPIO_FORWARD_L, PI_HIGH);
                gpio_write(pi, GPIO_FORWARD_R, PI_HIGH);
                usleep(500000); // Avance pendant 0.5 seconde
                gpio_write(pi, GPIO_FORWARD_L, PI_LOW);
                gpio_write(pi, GPIO_FORWARD_R, PI_LOW); // Arrêt des moteurs
                printf("Je vais lâcher le marqueur\n");
                GestionLache(); // Gestion du lâcher du marqueur

                gpio_write(pi, GPIO_BACKWARD_L, PI_HIGH);
                gpio_write(pi, GPIO_BACKWARD_R, PI_HIGH);
                usleep(500000); // Recule pendant 0.5 seconde
                gpio_write(pi, GPIO_BACKWARD_L, PI_LOW);
                gpio_write(pi, GPIO_BACKWARD_R, PI_LOW); // Arrêt des moteurs

                if (MarkerIDTrouve < 30) {
                    TabRecupMerker[MarkerIDTrouve] = GestionMarker(); // Stockage de l'ID
                    MarkerIDTrouve++;
                }
                else 
                {
                    printf(" Tableau plein ! Impossible d'ajouter plus de marqueurs.\n");
                }            
            }
        //}
        else
        {
            printf("JE suis dans le else\n");
            while(DetectionMarkerExist() == false) // Tant qu'un marqueur est détecté
            {
               GestionMouvementRobot(motorL, motorR); // Gestion du mouvement du robot
               usleep(500000); // Pause de 0.5 seconde pour éviter une boucle trop rapide 
            }
        }
    }
}