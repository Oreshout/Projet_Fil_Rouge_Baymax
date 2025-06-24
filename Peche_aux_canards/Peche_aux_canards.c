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
    int distance = 0;
    struct marker *DetectionMarker = getmarkers(30);
   
    distance = DetectionMarker->z;
    printf("Marqué à %d cm\n", distance);
    
    return distance;
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

int main()
{
    pi = pigpio_start(NULL, NULL);

}