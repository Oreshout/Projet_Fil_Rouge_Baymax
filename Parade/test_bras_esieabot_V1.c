#include "settings_parade.h"

int pi;

void set_servo_to_min(){
    set_servo_pulsewidth(pi, servo_pinR, 500); // Position finale // ! RIGHT
    set_servo_pulsewidth(pi, servo_pinL, 500); // Position finale // ! LEFT
}

void set_servo_to_max(){
    set_servo_pulsewidth(pi, servo_pinR, 1500); // Position finale // ! RIGHT
    set_servo_pulsewidth(pi, servo_pinL, 1500); // Position finale // ! LEFT
}

void gauche_droite(){
    set_servo_to_min();
    usleep(500000);
    set_servo_to_max();
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
    set_servo_to_min();
    sleep(5);
    set_servo_to_max();

    

    return 0;
}