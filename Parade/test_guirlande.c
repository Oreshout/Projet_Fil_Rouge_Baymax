#include "settings_parade.h"

int pi;

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

    sleep(1);
    printf("startig test\n");
    G_all(1000000);
    sleep(1);
    G_sequence(200000);
    sleep(1);
    G_Vers_int(400000);
    
    

    return 0;
}