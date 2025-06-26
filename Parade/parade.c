#include "settings_parade.h"

#define BAS "bas"
#define MID "milieu"
#define HAUT "haut"

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

void bras_gauche_et_droit_mouvement(char *posG1, char *posG2, char *posR1, char *posR2, int time)
{
    int timePerStep = time / 40;
    int i = 0;
    int angleG;
    int angleR;

    while (i < 41)
    {
        // Mouvement bras gauche
        if (posG1 == "bas" && posG2 == "milieu")
        {
            angleG = 2500 - 12.5 * i;
        }
        if (posG1 == "bas" && posG2 == "haut")
        {
            angleG = 2500 - 25 * i;
        }
        if (posG1 == "milieu" && posG2 == "bas")
        {
            angleG = 2000 + 12.5 * i;
        }
        if (posG1 == "milieu" && posG2 == "haut")
        {
            angleG = 2000 - 12.5 * i;
        }
        if (posG1 == "haut" && posG2 == "bas")
        {
            angleG = 1500 + 25 * i;
        }
        if (posG1 == "haut" && posG2 == "milieu")
        {
            angleG = 1500 + 12.5 * i;
        }

        // Mouvement bras droit
        if (posR1 == "bas" && posR2 == "milieu")
        {
            angleR = 500 + 12.5 * i;
        }
        if (posR1 == "bas" && posR2 == "haut")
        {
            angleR = 500 + 25 * i;
        }
        if (posR1 == "milieu" && posR2 == "bas")
        {
            angleR = 1000 - 12.5 * i;
        }
        if (posR1 == "milieu" && posR2 == "haut")
        {
            angleR = 1000 + 12.5 * i;
        }
        if (posR1 == "haut" && posR2 == "bas")
        {
            angleR = 1500 - 25 * i;
        }
        if (posR1 == "haut" && posR2 == "milieu")
        {
            angleR = 1500 - 12.5 * i;
        }

        set_servo_pulsewidth(pi, servo_pinR, angleR);
        set_servo_pulsewidth(pi, servo_pinL, angleG);
        usleep(timePerStep);

        i++;
    }
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

    usleep(1000000);

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
    
    //intro clap
    for (int i = 0; i < 3; i++)
    {
        MotorController_setBackward(&motorL, true);
        MotorController_setBackward(&motorR, true);
        drift_back();

        usleep(500000);
        bras_gauche_et_droit_mouvement(BAS, HAUT, BAS, HAUT, 100000);
        //bras_droit_haut();
        //bras_gauche_haut();
        usleep(750000);
        bras_gauche_et_droit_mouvement(HAUT, BAS, HAUT, BAS, 100000);
        //bras_droit_bas();
        //bras_gauche_bas();
        usleep(250000);

        G_all(200000);
        usleep(500000);
        G_all(200000);
        usleep(500000);
        G_all(200000);
        usleep(500000);
    }

    //Drop
    bras_droit_movement(BAS, MID, 100000);
    usleep(750000);
    bras_droit_movement(MID, HAUT, 100000);
    usleep(750000);
    bras_gauche_movement(BAS, MID, 100000);
    usleep(750000);
    bras_gauche_movement(MID, HAUT, 100000);
    usleep(500000);

    //smoth move
    bras_droit_movement(HAUT, BAS, 100000);
    for (int j = 0; j < 4; j++)
    {
        //bras_droit_haut();
        //bras_gauche_bas();
        bras_gauche_et_droit_mouvement(HAUT, BAS, BAS, HAUT, 100000);
        usleep(250000);
        drift_back();
        G_sequence(100000);
        usleep(750000);
        //bras_gauche_haut();
        //bras_droit_bas();
        bras_gauche_et_droit_mouvement(BAS, HAUT, HAUT, BAS, 100000);
        usleep(250000);
        drift_front();
        G_sequence(100000);
        usleep(750000);
    }

    //bras simple
    bras_droit_movement(BAS, HAUT, 200000);
    usleep(750000);

    bras_droit_movement(HAUT, MID, 100000);
    usleep(750000);
    G_Vers_int(100000);
    drift_back();
    usleep(750000);
    bras_gauche_movement(HAUT, MID, 100000);
    usleep(750000);
    G_Vers_int(100000);
    drift_front();
    usleep(750000);

    bras_droit_movement(MID, BAS, 100000);
    usleep(750000);
    G_Vers_int(100000);
    drift_back();
    usleep(750000);
    bras_gauche_movement(MID, BAS, 100000);
    usleep(750000);
    G_Vers_int(100000);
    drift_front();
    usleep(750000);


    //CLAP CLAP 
    for(int i =0; i<3; i++)
    {
        bras_droit_milieu();
        bras_gauche_milieu();
        usleep(100000);

        bras_droit_haut();
        bras_gauche_haut();
        usleep(200000);
    }

    //Bye bye

    bras_droit_movement(HAUT,MID,100000);
    bras_gauche_movement(HAUT,BAS,100000);

    for(int i=0; i<4; i++)
    {
        bras_droit_movement(MID,HAUT,100000);
        usleep(200000);
        bras_droit_movement(HAUT,MID,100000);
        usleep(200000);
    }

    rotate_right();
        
        


    return 0;
}