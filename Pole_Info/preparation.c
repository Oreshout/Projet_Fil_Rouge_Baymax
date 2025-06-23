/**
*
*
*      PREPARATION A FAIRE JOUR 1 
*
*       LED pin : 21
*       Bouton pin : 20
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void LED_update()
{
    int boucle = 0;
    set_mode(pi, 21, PI_OUTPUT); // Met le GPIO 21 en mode sortie pour la LED

    while (boucle < 5)
    {
        gpio_write(pi, 21, PI_HIGH); // Envoi un signal "HAUT" sur le GPIO 16 pour l'allumer
        sleep(1);
        gpio_write(pi, 21, PI_LOW); // Envoi un signal "BAS" sur le GPIO16 pour l'éteindre
        sleep(1);
        boucle++;
    }
}

void Bouton_update()
{
    set_mode(pi, 20, PI_INPUT); // Met le GPIO 20 en mode entrée
    set_pull_up_down(pi, 20, PI_PUD_DOWN); // Active la résistance de rappel sur le GPIO 20

    while (1) 
    {
        int state = gpio_read(pi, 20); // Lecture de l'état du bouton poussoir
        if (state == PI_HIGH) { // Si le GPIO a reçu un "HAUT"
            printf("Le bouton poussoir sur le GPIO 20 est enclenché\n");
        } else if (state == PI_LOW) { // Si le GPIO a reçu un "BAS"
            printf("Le bouton poussoir sur le GPIO 20 est relaché\n");
        } else { // Ne devrait pas exister
            printf("Le GPIO 16 est dans un état inconnu\n");
        }
        sleep(1);
    }
}

