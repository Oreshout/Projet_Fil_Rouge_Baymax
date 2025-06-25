#include "settings_parade.h"

int pi;

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

void set_servo_to_custom(int angleL, int angleR)
{
    set_servo_pulsewidth(pi, servo_pinR, angleR); // Position finale
    set_servo_pulsewidth(pi, servo_pinL, angleL); // Position finale
}

void gauche_droite()
{
    set_servo_to_min();
    usleep(500000);
    set_servo_to_max();
}

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

void bras_gauche_movement(char *pos1, char *pos2, int time) // pos1 = depart
{                                                           // pos2 = fin
    int timePerStep = time / 40;
    int angle;
    if (pos1 == "bas" && pos2 == "milieu")
    {
        for (int i = 0; i < 40; i++)
        {
            angle = 2500 - 12.5 * i;
            set_servo_pulsewidth(pi, servo_pinL, angle);
            usleep(timePerStep);
        }
    }
    if (pos1 == "bas" && pos2 == "haut")
    {
        for (int i = 0; i < 40; i++)
        {
            angle = 2500 - 25 * i;
            set_servo_pulsewidth(pi, servo_pinL, angle);
            usleep(timePerStep);
        }
    }
    if (pos1 == "milieu" && pos2 == "bas")
    {
        for (int i = 0; i < 40; i++)
        {
            angle = 2000 + 12.5 * i;
            set_servo_pulsewidth(pi, servo_pinL, angle);
            usleep(timePerStep);
        }
    }
    if (pos1 == "milieu" && pos2 == "haut")
    {
        for (int i = 0; i < 40; i++)
        {
            angle = 2000 - 12.5 * i;
            set_servo_pulsewidth(pi, servo_pinL, angle);
            usleep(timePerStep);
        }
    }
    if (pos1 == "haut" && pos2 == "bas")
    {
        for (int i = 0; i < 40; i++)
        {
            angle = 1500 + 25 * i;
            set_servo_pulsewidth(pi, servo_pinL, angle);
            usleep(timePerStep);
        }
    }
    if (pos1 == "haut" && pos2 == "milieu")
    {
        for (int i = 0; i < 40; i++)
        {
            angle = 1500 + 12.5 * i;
            set_servo_pulsewidth(pi, servo_pinL, angle);
            usleep(timePerStep);
        }
    }
}

void bras_droit_movement(char *pos1, char *pos2, int time) // pos1 = depart
{                                                          // pos2 = fin
    int timePerStep = time / 40;
    int angle;
    if (pos1 == "bas" && pos2 == "milieu")
    {
        for (int i = 0; i < 40; i++)
        {
            angle = 500 + 12.5 * i;
            set_servo_pulsewidth(pi, servo_pinR, angle);
            usleep(timePerStep);
        }
    }
    if (pos1 == "bas" && pos2 == "haut")
    {
        for (int i = 0; i < 40; i++)
        {
            angle = 500 + 25 * i;
            set_servo_pulsewidth(pi, servo_pinR, angle);
            usleep(timePerStep);
        }
    }
    if (pos1 == "milieu" && pos2 == "bas")
    {
        for (int i = 0; i < 40; i++)
        {
            angle = 1000 - 12.5 * i;
            set_servo_pulsewidth(pi, servo_pinR, angle);
            usleep(timePerStep);
        }
    }
    if (pos1 == "milieu" && pos2 == "haut")
    {
        for (int i = 0; i < 40; i++)
        {
            angle = 1000 + 12.5 * i;
            set_servo_pulsewidth(pi, servo_pinR, angle);
            usleep(timePerStep);
        }
    }
    if (pos1 == "haut" && pos2 == "bas")
    {
        for (int i = 0; i < 40; i++)
        {
            angle = 1500 - 25 * i;
            set_servo_pulsewidth(pi, servo_pinR, angle);
            usleep(timePerStep);
        }
    }
    if (pos1 == "haut" && pos2 == "milieu")
    {
        for (int i = 0; i < 40; i++)
        {
            angle = 1500 - 12.5 * i;
            set_servo_pulsewidth(pi, servo_pinR, angle);
            usleep(timePerStep);
        }
    }
}

void bras_symmetriques_haut_bas()
{
    bras_gauche_bas();
    bras_droit_bas();
    usleep(800000);
    bras_gauche_milieu();
    bras_droit_milieu();
    usleep(800000);
    bras_gauche_haut();
    bras_droit_haut();
    usleep(800000);
}

void bras_ensemble_gauche_droite()
{
    bras_gauche_bas();
    bras_droit_haut();
    usleep(800000);
    bras_gauche_milieu();
    bras_droit_milieu();
    usleep(800000);
    bras_gauche_haut();
    bras_droit_bas();
    usleep(800000);
    bras_droit_milieu();
    bras_gauche_milieu();
    usleep(800000);
}

int main()
{
    pi = pigpio_start(NULL, NULL);

    int Right_Angle = 0;
    int Left_Angle = 0;

    /*printf("Input the angle for the crab's right arm : ");
    scanf("%d", &Right_Angle);
    printf("Input the angle for the crab's left arm : ");
    scanf("%d", &Left_Angle);*/

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

    sleep(1);
    printf("startig test\n");
    // set_servo_to_custom(Left_Angle, Right_Angle);

    /*bras_symmetriques_haut_bas();
    bras_symmetriques_haut_bas();
    bras_ensemble_gauche_droite();
    bras_symmetriques_haut_bas();
    bras_symmetriques_haut_bas();
    bras_ensemble_gauche_droite();
    bras_gauche_bas();
    bras_droit_bas();*/

    bras_gauche_bas();
    bras_droit_bas();
    sleep(1);
    bras_gauche_movement("bas", "milieu", 500000);
    bras_droit_movement("bas", "haut", 100000);

    return 0;
}