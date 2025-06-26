#include "settings_parade.h"

int pi;

void start_time()
{
    int startTime = get_current_tick(pi) % 1000000;
    int time;
    while (1)
    {
        time = get_current_tick(pi);
        if (time % 1000000 > startTime)
        {
            printf("%d\n", time);
            break;
        }
    }
}

void set_servo_to_min()
{
    set_servo_pulsewidth(pi, servo_pinR, 500); // Position finale // ! RIGHT
    set_servo_pulsewidth(pi, servo_pinL, 500); // Position finale // ! LEFT
}

void set_servo_to_max()
{
    set_servo_pulsewidth(pi, servo_pinR, 1500); // Position finale // ! RIGHT
    set_servo_pulsewidth(pi, servo_pinL, 1500); // Position finale // ! LEFT
}

void gauche_droite()
{
    set_servo_to_min();
    usleep(500000);
    set_servo_to_max();
}

/*void gauche_droite()
{
    set_servo_to_min();
    usleep(500000);
    set_servo_to_max();
}*/

void bras_gauche_bas()
{
    set_servo_pulsewidth(pi, servo_pinL, 2500);
}

void bras_gauche_milieu()
{
    set_servo_pulsewidth(pi, servo_pinL, 2000);
}

void bras_gauche_haut()
{
    set_servo_pulsewidth(pi, servo_pinL, 1500);
}

void bras_droit_bas()
{
    set_servo_pulsewidth(pi, servo_pinR, 500);
}

void bras_droit_milieu()
{
    set_servo_pulsewidth(pi, servo_pinR, 1000);
}

void bras_droit_haut()
{
    set_servo_pulsewidth(pi, servo_pinR, 1500);
}

void G_all(int t){ //ne marche pas
    gpio_write(pi, Girlande_1, PI_HIGH);
    gpio_write(pi, Girlande_2, PI_HIGH);
    gpio_write(pi, Girlande_3, PI_HIGH);
    gpio_write(pi, Girlande_4, PI_HIGH);
    usleep(t);
    gpio_write(pi, Girlande_1, PI_LOW);
    gpio_write(pi, Girlande_2, PI_LOW);
    gpio_write(pi, Girlande_3, PI_LOW);
    gpio_write(pi, Girlande_4, PI_LOW);
}

void G_sequence(int t){
    gpio_write(pi, Girlande_1, PI_HIGH);
    usleep(t);
    gpio_write(pi, Girlande_1, PI_LOW);
    gpio_write(pi, Girlande_2, PI_HIGH);
    usleep(t);
    gpio_write(pi, Girlande_2, PI_LOW);
    gpio_write(pi, Girlande_3, PI_HIGH);
    usleep(t);
    gpio_write(pi, Girlande_3, PI_LOW);
    gpio_write(pi, Girlande_4, PI_HIGH);
    usleep(t);
    gpio_write(pi, Girlande_4, PI_LOW);
}
void G_Vers_int(int t){
    gpio_write(pi, Girlande_1, PI_HIGH);
    gpio_write(pi, Girlande_4, PI_HIGH);
    usleep(t);
    gpio_write(pi, Girlande_1, PI_LOW);
    gpio_write(pi, Girlande_4, PI_LOW);
    gpio_write(pi, Girlande_2, PI_HIGH);
    gpio_write(pi, Girlande_3, PI_HIGH);
    usleep(t);
    gpio_write(pi, Girlande_2, PI_LOW);
    gpio_write(pi, Girlande_3, PI_LOW);
}


void drift_back()
{
    gpio_write(pi, GPIO_BACKWARD_L, PI_HIGH);
    gpio_write(pi, GPIO_BACKWARD_R, PI_HIGH);

    usleep(100000);

    gpio_write(pi, GPIO_BACKWARD_L, PI_LOW);
    gpio_write(pi, GPIO_BACKWARD_R, PI_LOW);
}

void drift_front()
{
    gpio_write(pi, GPIO_FORWARD_L, PI_HIGH);
    gpio_write(pi, GPIO_FORWARD_R, PI_HIGH);

    usleep(100000);

    gpio_write(pi, GPIO_FORWARD_L, PI_LOW);
    gpio_write(pi, GPIO_FORWARD_R, PI_LOW);
}

void long_drift_back()
{
    gpio_write(pi, GPIO_BACKWARD_L, PI_HIGH);
    gpio_write(pi, GPIO_BACKWARD_R, PI_HIGH);

    usleep(300000);

    gpio_write(pi, GPIO_BACKWARD_L, PI_LOW);
    gpio_write(pi, GPIO_BACKWARD_R, PI_LOW);
}

void long_drift_front()
{
    gpio_write(pi, GPIO_FORWARD_L, PI_HIGH);
    gpio_write(pi, GPIO_FORWARD_R, PI_HIGH);

    usleep(300000);

    gpio_write(pi, GPIO_FORWARD_L, PI_LOW);
    gpio_write(pi, GPIO_FORWARD_R, PI_LOW);
}

void rotate_right()
{
    //gpio_write(pi, GPIO_BACKWARD_L, PI_HIGH);
    gpio_write(pi, GPIO_FORWARD_R, PI_HIGH);

    usleep(150000);

    //gpio_write(pi, GPIO_BACKWARD_L, PI_LOW);
    gpio_write(pi, GPIO_FORWARD_R, PI_LOW);
}

int main()
{
    pi = pigpio_start(NULL, NULL);

    float kp = 4.0f; // Valeurs conseillées pour le contrôleur PI
    float ki = 2.0f;

    float speed = 50.f;

    MotorController motorL;                                                                   // Création de lobjet contrôleur moteur
    MotorController_init(&motorL, pi, GPIO_FORWARD_L, GPIO_BACKWARD_L, GPIO_MOTOR_CONTROL_L); // Initialisation du contrôleur moteur

    MotorController motorR;                                                                   // Création de lobjet contrôleur moteur
    MotorController_init(&motorR, pi, GPIO_FORWARD_R, GPIO_BACKWARD_R, GPIO_MOTOR_CONTROL_R); // Initialisation du contrôleur moteur

    MotorController_setStartPower(&motorL, 110);
    MotorController_setController(&motorL, kp, ki);

    MotorController_setStartPower(&motorR, 110);
    MotorController_setController(&motorR, kp, ki);

    MotorController_stop(&motorL);
    MotorController_stop(&motorR);

    //start_time();

    // programme principal
    printf("démarage\n");

    G_Vers_int(400000);

    usleep(500000);

    rotate_right();

    
    for (int i = 0; i < 3; i++)
    {
        MotorController_setBackward(&motorL, true);
        MotorController_setBackward(&motorR, true);
        drift_back();

        usleep(500000);
        bras_droit_haut();
        bras_gauche_haut();
        usleep(750000);
        bras_droit_bas();
        bras_gauche_bas();
        usleep(500000);

        G_all(200000);
        usleep(500000);
        G_all(200000);
        usleep(500000);
        G_all(200000);
        usleep(500000);
    }
    bras_droit_milieu();
    usleep(750000);
    bras_droit_haut();
    usleep(750000);
    bras_gauche_milieu();
    usleep(750000);
    bras_gauche_haut();
    usleep(500000);

    for (int j = 0; j < 4; j++)
    {
        bras_droit_haut();
        bras_gauche_bas();
        usleep(250000);
        drift_back();
        usleep(750000);
        bras_gauche_haut();
        bras_droit_bas();
        usleep(250000);
        drift_front();
        G_sequence(100000);
        usleep(750000);
    }
        
        


    return 0;
}