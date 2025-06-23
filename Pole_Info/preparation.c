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
    int boucle = 0;
    set_mode(pi, LED_pin, PI_OUTPUT); // Met le GPIO 20 en mode sortie pour la LED

    for(int i = 0; i < 5; i++)
    {
        gpio_write(pi, LED_pin, PI_HIGH); // Envoi un signal "HAUT" sur le GPIO 16 pour l'allumer
        sleep(1);
        gpio_write(pi, LED_pin, PI_LOW); // Envoi un signal "BAS" sur le GPIO16 pour l'éteindre
        sleep(1);
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

int main(){
    int pi = pigpio_start(NULL, NULL);

    printf("starting led \n");
    LED_update(pi);
    printf("starting motor \n");
    Bouton_update(pi);
    servo_update(pi);
    //motor_update()
    //distance_update()
    return 0;
}