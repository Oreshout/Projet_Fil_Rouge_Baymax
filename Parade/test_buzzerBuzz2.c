#include "settings_parade.h"


#define NOTE_C4  262
#define NOTE_D4  294
#define REST     0

#define NOTE_A3  220  // La3
#define NOTE_B3  247  // Si3

int melody5[] = {
    NOTE_A3, REST, NOTE_A3, REST, NOTE_B3, REST, 
    NOTE_B3, REST, NOTE_B3, REST, NOTE_A3, REST, 
    NOTE_B3, REST, NOTE_B3, REST, NOTE_A3, REST, 
    NOTE_A3, REST, NOTE_A3, REST
};

int durations[] = {
    25, 75, 25, 50, 25, 25, //noire - croche_pointé - croche
    25, 50, 25, 75, 25, 75, //croche_pointé - noire - noire
    25, 50, 25, 50, 25, 25, //croche_pointé - croche_pointé - croche
    25, 25, 25, 25 //croche - croche
};

int pi;

void playNote(int freq, int duration_ms) {
    if (freq == REST) {
        gpio_write(pi, Buzz_2, PI_LOW);
        usleep(duration_ms * 1000);
    } else {
        for (int i = 0; i < freq * duration_ms / 1000; i++) {
            gpio_write(pi, Buzz_2, PI_HIGH);
            usleep(500000 / freq);
            gpio_write(pi, Buzz_2, PI_LOW);
            usleep(500000 / freq);
        }
    }
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

    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 22; i++)
        {
            playNote(melody5[i]/2, durations[i]*4.8);
        }
    }

    return 0;
}