#include "settings_parade.h"


#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define REST     0

#define NOTE_A3  220  // La3
#define NOTE_AS3 233  // La#3 / Sib3
#define NOTE_B3  247  // Si3

int melody[] = {
    NOTE_C4, REST, NOTE_C4, REST, NOTE_D4, REST, 
    NOTE_D4, REST, NOTE_D4, REST, NOTE_C4, REST, 
    NOTE_D4, REST, NOTE_D4, REST, NOTE_D4, REST, 
    NOTE_D4, REST, NOTE_D4, REST
};

int durations[] = {
    2, 6, 2, 4, 2, 2,
    2, 4, 2, 6, 2, 6,
    2, 6, 2, 4, 2, 4,
    2, 2, 2, 6
};

int pi;

void playNote(int freq, int duration_ms) {
    if (freq == REST) {
        gpio_write(pi, Buzz_1, PI_LOW);
        usleep(duration_ms * 1000);
    } else {
        for (int i = 0; i < freq * duration_ms / 1000; i++) {
            gpio_write(pi, Buzz_1, PI_HIGH);
            usleep(500000 / freq);
            gpio_write(pi, Buzz_1, PI_LOW);
            usleep(500000 / freq);
        }
    }
}

/*void play2NotesBIS(int freq1, int freq2) {
    gpioHardwarePWM(Buzz_1, freq1, 500000);  // 50% duty
    gpioHardwarePWM(Buzz_3, freq2, 500000);  // 50% duty
}*/

void play2Notes(int freq1, int freq2, int duration_ms) {
    int t_us = duration_ms * 1000;
    int time_step = 50;  // résolution = 50 µs
    int steps = t_us / time_step;

    int toggle1 = 0, toggle2 = 0;
    int acc1 = 0, acc2 = 0;
    int period1 = (freq1 == REST) ? 0 : 1000000 / freq1 / 2;
    int period2 = (freq2 == REST) ? 0 : 1000000 / freq2 / 2;

    for (int i = 0; i < steps; i++) {
        acc1 += time_step;
        acc2 += time_step;

        if (freq1 != REST && acc1 >= period1) {
            toggle1 = !toggle1;
            gpio_write(pi, Buzz_1, toggle1);
            acc1 = 0;
        }

        if (freq2 != REST && acc2 >= period2) {
            toggle2 = !toggle2;
            gpio_write(pi, Buzz_3, toggle2);
            acc2 = 0;
        }

        usleep(time_step);
    }

    gpio_write(pi, Buzz_1, PI_LOW);
    gpio_write(pi, Buzz_3, PI_LOW);
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
            playNote(melody[i], durations[i]*50);
        }
    }

    return 0;
}