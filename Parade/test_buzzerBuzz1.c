#include "settings_parade.h"


#define NOTE_C4  262
#define NOTE_D4  294
#define REST     0

#define NOTE_A3  220  // La3
#define NOTE_B3  247  // Si3

#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_AS4 466  // Bb4
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659

#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_AS5 932  // Bb5
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_D6  1175
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_G6  1568
#define NOTE_A6  1760
#define NOTE_B6  1976

#define TAP_DROIT 1
#define TAP_GAUCHE 2
#define RELEVE_DROIT 3
#define RELEVE_GAUCHE 4

#define RIEN_FAIRE 5

int melody[] = {
    NOTE_C4, REST, NOTE_C4, REST, NOTE_D4, REST, 
    NOTE_D4, REST, NOTE_D4, REST, NOTE_C4, REST, 
    NOTE_D4, REST, NOTE_D4, REST, NOTE_D4, REST, 
    NOTE_D4, REST, NOTE_D4, REST
};
int durations[] = {
    25, 75, 25, 50, 25, 25, //noire - croche_pointé - croche
    25, 50, 25, 75, 25, 75, //croche_pointé - noire - noire
    25, 50, 25, 50, 25, 25, //croche_pointé - croche_pointé - croche
    25, 25, 25, 25          //croche - croche
};

int durationsP2[] = {
    25, 25, 25, 25, 25, 25, //croche - croche - croche
    15, 10, 25, 25, 15, 10,   //double_croche - croche - double_croche
    25, 25, 25, 25, 25, 25, //croche - croche - croche
    25, 25, 15, 10, 25, 25,  //croche - double_croche - croche
    25, 25, 15, 10, 25, 25,  //croche - double_croche - croche
    25, 25, 25, 25, 15, 10,  //croche - croche - double_croche
    15, 10                   //double_croche
};
int melodyP2[] = {
    NOTE_D6, REST, NOTE_B6, REST, NOTE_G5, REST, 
    NOTE_G5, REST, NOTE_D6, REST, NOTE_D6, REST, 
    NOTE_A6, REST, NOTE_F5, REST, NOTE_F5, REST, 
    NOTE_D6, REST, NOTE_D6, REST, NOTE_A6, REST, 
    NOTE_F5, REST, NOTE_F5, REST, NOTE_C5, REST, 
    NOTE_C5, REST, NOTE_E5, REST, NOTE_E5, REST, 
    NOTE_F5, REST
};
int melodyP2Bis[] = {
    NOTE_D5, REST, NOTE_B5, REST, NOTE_G4, REST, 
    NOTE_G4, REST, NOTE_D5, REST, NOTE_D5, REST, 
    NOTE_A5, REST, NOTE_F4, REST, NOTE_F4, REST, 
    NOTE_D5, REST, NOTE_D5, REST, NOTE_A5, REST, 
    NOTE_F4, REST, NOTE_F4, REST, NOTE_C4, REST, 
    NOTE_C4, REST, NOTE_E4, REST, NOTE_E4, REST, 
    NOTE_F4, REST
};

int melodytrans[] = {
    NOTE_D4, REST, NOTE_D4, REST, NOTE_D4, REST, 
    NOTE_D4, REST, NOTE_F4, REST, NOTE_F4, REST, 
    NOTE_F4, REST, NOTE_F4
};

int durationsTrans[] = {
    25, 75, 25, 75, 25, 75, //noire - noire - noire
    25, 75, 25, 75, 25, 75, //noire - noire - noire
    25, 75, 25, 75  //noire - noire
};

//tape

int melodyDROIT[] = {
    TAP_DROIT, RIEN_FAIRE, RELEVE_DROIT, RIEN_FAIRE, TAP_DROIT, RIEN_FAIRE, 
    RELEVE_DROIT, RIEN_FAIRE, TAP_DROIT, RIEN_FAIRE, RELEVE_DROIT, RIEN_FAIRE, 
    TAP_DROIT, RIEN_FAIRE, RELEVE_DROIT, RIEN_FAIRE, TAP_DROIT, RIEN_FAIRE, 
    RELEVE_DROIT, RIEN_FAIRE, TAP_DROIT, RIEN_FAIRE
}; //fini par taper a droite.
int melodyGAUCHE[] = {
    RIEN_FAIRE, RIEN_FAIRE, TAP_GAUCHE, RIEN_FAIRE, RELEVE_GAUCHE, RIEN_FAIRE, 
    TAP_GAUCHE, RIEN_FAIRE, RELEVE_GAUCHE, RIEN_FAIRE, TAP_GAUCHE, RIEN_FAIRE, 
    RELEVE_GAUCHE, RIEN_FAIRE, TAP_GAUCHE, RIEN_FAIRE, RELEVE_GAUCHE, RIEN_FAIRE, 
    TAP_GAUCHE, RIEN_FAIRE, RELEVE_GAUCHE, RIEN_FAIRE
};

int melodyP2DROIT[] = {
    TAP_DROIT, RIEN_FAIRE, RIEN_FAIRE, RELEVE_DROIT, RIEN_FAIRE, RIEN_FAIRE, 
    TAP_DROIT, RIEN_FAIRE, RIEN_FAIRE, RELEVE_DROIT, RIEN_FAIRE, RIEN_FAIRE, 
    TAP_DROIT, RIEN_FAIRE, RIEN_FAIRE, RELEVE_DROIT, RIEN_FAIRE, RIEN_FAIRE, 
    TAP_DROIT, RIEN_FAIRE, RIEN_FAIRE, RELEVE_DROIT, RIEN_FAIRE, RIEN_FAIRE, 
    TAP_DROIT, RIEN_FAIRE, RIEN_FAIRE, RELEVE_DROIT, RIEN_FAIRE, RIEN_FAIRE, 
    TAP_DROIT, RIEN_FAIRE, RIEN_FAIRE, RELEVE_DROIT, RIEN_FAIRE, RIEN_FAIRE, 
    RIEN_FAIRE, RIEN_FAIRE
}; 
int melodyP2GAUCHE[] = {
    TAP_GAUCHE, RIEN_FAIRE, RIEN_FAIRE, RELEVE_GAUCHE, RIEN_FAIRE, RIEN_FAIRE, 
    TAP_GAUCHE, RIEN_FAIRE, RIEN_FAIRE, RELEVE_GAUCHE, RIEN_FAIRE, RIEN_FAIRE, 
    TAP_GAUCHE, RIEN_FAIRE, RIEN_FAIRE, RELEVE_GAUCHE, RIEN_FAIRE, RIEN_FAIRE, 
    TAP_GAUCHE, RIEN_FAIRE, RIEN_FAIRE, RELEVE_GAUCHE, RIEN_FAIRE, RIEN_FAIRE, 
    TAP_GAUCHE, RIEN_FAIRE, RIEN_FAIRE, RELEVE_GAUCHE, RIEN_FAIRE, RIEN_FAIRE, 
    TAP_GAUCHE, RIEN_FAIRE, RIEN_FAIRE, RELEVE_GAUCHE, RIEN_FAIRE, RIEN_FAIRE, 
    RIEN_FAIRE, RIEN_FAIRE
}; //fini par en haut les deux

int melodytransDROIT[] = {
    TAP_DROIT, RIEN_FAIRE, RELEVE_DROIT, RIEN_FAIRE, TAP_DROIT, RIEN_FAIRE, 
    RELEVE_DROIT, RIEN_FAIRE, RELEVE_DROIT, RIEN_FAIRE, RELEVE_DROIT, RIEN_FAIRE, 
    TAP_DROIT, RIEN_FAIRE, RELEVE_DROIT
};//fini tap droit

int melodytransGAUCHE[] = {
    TAP_GAUCHE, RIEN_FAIRE, RELEVE_GAUCHE, RIEN_FAIRE, TAP_GAUCHE, RIEN_FAIRE, 
    RELEVE_GAUCHE, RIEN_FAIRE, RELEVE_GAUCHE, RIEN_FAIRE, RELEVE_GAUCHE, RIEN_FAIRE, 
    TAP_DROIT, RIEN_FAIRE, RELEVE_GAUCHE
};

int pi;

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

void play_drum_L(int DrumPos){
    switch (DrumPos)
    {
    case TAP_GAUCHE:
        bras_gauche_bas();
        break;

    case RELEVE_GAUCHE:
        bras_gauche_haut();
        break;

    case RIEN_FAIRE:
        return;
        break;
    
    default:
    printf("grosse ereur drum L\n");
        break;
    }
}

void play_drum_R(int DrumPos){
    switch (DrumPos)
    {
    case TAP_DROIT:
        bras_droit_bas();
        break;

    case RELEVE_DROIT:
        bras_droit_haut();
        break;

    case RIEN_FAIRE:
        return;
        break;
    
    default:
    printf("grosse ereur drum R\n");
        break;
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

    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 22; i++)
        {
            playNote(melody[i]/2, durations[i]*4.8);
            play_drum_L(melodyGAUCHE[i]);
            play_drum_R(melodyDROIT[i]);
        }
    }

    for (int i = 0; i < 16; i++)
    {
        playNote(melodytrans[i]/2, durationsTrans[i]*4.8);
        play_drum_L(melodytransGAUCHE[i]);
        play_drum_R(melodytransDROIT[i]);
    }
    

    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 37; i++)
        {
            playNote(melodyP2[i]/2, durationsP2[i]*4.8);
            play_drum_L(melodyP2GAUCHE[i]);
            play_drum_R(melodyP2DROIT[i]);
        }
    }
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 37; i++)
        {
            playNote(melodyP2Bis[i]/2, durationsP2[i]*4.8);
            play_drum_L(melodyP2GAUCHE[i]);
            play_drum_R(melodyP2DROIT[i]);
        }
    }

    return 0;
}