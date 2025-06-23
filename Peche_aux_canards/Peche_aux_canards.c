#include "settings_PecheAuxCanards.h"

/**
*
*
*    CODE : Pêche aux canards
*
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

void GestionServoMoteur()
{
    set_mode(pi, servo_pin, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pin, 500); // Position initiale
    sleep(1);
}

void GestionMoteur()
{

}

void GestionBouton()
{

}

int main()
{
    pi = pigpio_start(NULL, NULL);

}