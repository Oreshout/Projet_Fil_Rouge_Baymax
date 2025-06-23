#include "settings.h"

/**
*
*
*      PREPARATION A FAIRE JOUR 1 
*
*       LED pin : 20
*       Bouton pin : 21
*
*/

void LED_update(int pi)
{
    set_mode(pi, LED_pin, PI_OUTPUT); // Met le GPIO 20 en mode sortie pour la LED

    for(int i = 0; i < 5; i++)
    {
        gpio_write(pi, LED_pin, PI_HIGH); // Envoi un signal "HAUT" sur le GPIO 16 pour l'allumer
        usleep(500000); // ?   Pause de 500ms
        gpio_write(pi, LED_pin, PI_LOW); // Envoi un signal "BAS" sur le GPIO16 pour l'éteindre
        usleep(500000); // ?   Pause de 500ms
    }
}

void Bouton_update(int pi)
{
    set_mode(pi, Bouton_pin, PI_INPUT); // Met le GPIO 21 en mode entrée
    set_pull_up_down(pi, Bouton_pin, PI_PUD_DOWN); // Active la résistance de rappel sur le GPIO 20

    while (true) 
    {
        int state = gpio_read(pi, Bouton_pin); // Lecture de l'état du bouton poussoir
        
        if (state == PI_HIGH) 
        { // Si le GPIO a reçu un "HAUT"
            printf("Bouton apuyé\n");
            break;
        } 
        sleep(1);
    }
}

void servo_update(int pi){

    set_mode(pi, servo_pin, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pin, 500);
    sleep(1);

    set_mode(pi, servo_pin, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pin, 2500);
    sleep(1);
}

void distance_update(int pi)
{
     while (true) 
     { // Boucle infinie du programme

        struct marker *markers = get_markers(51); // Récupération des marqueurs de 51mm de côté (à modifier en fonction de vos marqueurs !)
        struct marker *m;
        for (m = markers; m->id != -1; m++) 
        { // Pour tous les marqueurs trouvés...
            printf("Marqueur trouvé: numéro %d à %dcm de distance. x=%d y=%d\n", m->id, m->z, m->x, m->y);
        }
    }
}

int main(){
    int pi = pigpio_start(NULL, NULL);

    printf("starting led \n");
    LED_update(pi);
    printf("starting motor \n");
    Bouton_update(pi);
    servo_update(pi);
    //motor_update()
    printf("starting distance \n");
    distance_update(pi);
    printf("All updates done \n");
    return 0;
}