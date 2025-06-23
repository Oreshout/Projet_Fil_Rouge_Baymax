#include "settings.h"

/**
*
*
*      PREPARATION A FAIRE JOUR 1 
*
*       LED pin : 21
*       Bouton pin : 20
*
*/

void LED_update(LED_pin)
{
    int boucle = 0;
    set_mode(pi, LED_pin PI_OUTPUT); // Met le GPIO 21 en mode sortie pour la LED

    for(int i = 0; i < 5; i++)
    {
        gpio_write(pi, LED_pin, PI_HIGH); // Envoi un signal "HAUT" sur le GPIO 16 pour l'allumer
        sleep(1);
        gpio_write(pi, LED_pin, PI_LOW); // Envoi un signal "BAS" sur le GPIO16 pour l'éteindre
        sleep(1);
    }
}

void Bouton_update(Bouton_pin)
{
    set_mode(pi, Bouton_pin, PI_INPUT); // Met le GPIO 20 en mode entrée
    set_pull_up_down(pi, Bouton_pin, PI_PUD_DOWN); // Active la résistance de rappel sur le GPIO 20

    while (true) 
    {
        int state = gpio_read(pi, Bouton_pin); // Lecture de l'état du bouton poussoir
        
        if (state == PI_HIGH) 
        { // Si le GPIO a reçu un "HAUT"
            printf("Bouton apuyer\n");
            break;
        } 
        sleep(1);
    }
}

int main(){
    LED_update();
    Bouton_update();
    //servoMotor_update();
    //motor_update()
    //distance_update()
    return 0;
}