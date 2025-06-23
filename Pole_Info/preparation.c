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

int pi;

void led_update()
{
    set_mode(pi, LED_pin, PI_OUTPUT); // Met le GPIO 20 en mode sortie pour la LED

    for(int i = 0; i < 5; i++)
    {
        gpio_write(pi, LED_pin, PI_HIGH); // Envoi un signal "HAUT" sur le GPIO 16 pour l'allumer
        usleep(500000); // ?   Pause de 500ms
        gpio_write(pi, LED_pin, PI_LOW); // Envoi un signal "BAS" sur le GPIO16 pour l'éteindre
        usleep(500000); // ? Pause de 500ms
    }
}

void Bouton_update()
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

void servo_update(){

    set_mode(pi, servo_pin, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pin, 500);
    sleep(1);

    set_mode(pi, servo_pin, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pin, 2500);
    sleep(1);
}

void distance_update()
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

void motor_update(MotorController motorL, MotorController motorR)
{

    gpio_write(pi, GPIO_FORWARD_L, PI_HIGH);
    gpio_write(pi, GPIO_FORWARD_R, PI_HIGH);

    sleep(1);
    printf("je sors du drive\n");

    gpio_write(pi, GPIO_FORWARD_L, PI_LOW);
    gpio_write(pi, GPIO_FORWARD_R, PI_LOW);

    gpio_write(pi, GPIO_BACKWARD_L, PI_HIGH);
    gpio_write(pi, GPIO_BACKWARD_R, PI_HIGH);

    sleep(1);

    gpio_write(pi, GPIO_BACKWARD_L, PI_LOW);
    gpio_write(pi, GPIO_BACKWARD_R, PI_LOW);
}

int main(){
    pi = pigpio_start(NULL, NULL);

    float kp = 4.0f; // Valeurs conseillées pour le contrôleur PI
    float ki = 2.0f;

    float speed = 50.f;

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

    printf("starting led \n");
    led_update();
    printf("starting button \n");
    Bouton_update();
    printf("starting servo \n");
    servo_update();
    printf("starting motor \n");
    motor_update(motorL, motorR);
    printf("starting distance \n");
    distance_update();
    printf("all tests completed \n");
    return 0;
}