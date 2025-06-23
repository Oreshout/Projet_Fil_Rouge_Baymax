/**         *****************************************************                                                                                           
 *          *                Projet du ML Challenge             *
 *          *****************************************************
*/

/**
 * @author : Cyprien Jallet
 * @author : Ombeline Porte
 * @author : Joachim Ludwiczak
 * @author : Lucas Doganis
 * @author : Mattéo Depestèle
 * @author : Eline Cezard-sibillot
 * 
 * @see GitHub : https://github.com/Polaerz/PermisEsieaBot.git (Permission requise)
 * @file : Basecode.zip 
*/

//------------------------------------------------------------------------------

/**
 * @defgroup : Libraires utilisées
 * 
 * @brief : Il faut télécharger Basecode.zip
 */
#include "settings.h"
#include "input.h"
#include "button.h"
#include "fps.h"
#include "led.h"
#include "motor_controller.h"
#include "ultrasonic_sensor.h"
#include "tools.h"

#define OUR_MAIN

#ifdef OUR_MAIN
//------------------------------------------------------------------------------
// Programme principal
/// @brief Programme principal.
int main(int argc, char *argv[])
{
    // Recherche un game controller
    g_joystick = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);
    if (g_joystick == -1)
    {
        printf("Could not open joystick\n");
        return EXIT_FAILURE;
    }

    // Initialise PiGPIO
    int pi = pigpio_start(NULL, NULL);
    if (pi < 0)
    {
        printf("Can't start gpio lib\n");
        assert(false);
        abort();
    }

    // Initialisation des composants de FPS
    FPS fps = { 0 };
    FPS_init(&fps, pi);

    // Initialisation des composants de Input et Button
    Input input = { 0 };
    Button button = { 0 };
    Button_init(&button, pi, GPIO_BUTTON);

    // Initialisation des composants de LED
    LED led = { 0 };
    LED_init(&led, pi, GPIO_LED);

//------------------------------------------------------------------------------

    /**
     * @defgroup : Init moteur
     * 
     * @param gear : Init de l'embrayage à 1
     * @param speed : Init vitesse initiale
     * @param kp : Init Constance de la proportionalité
     * @param ki : Init Constante de l'intégrale 
     */
    int gear = 1;
    bool printGear = false;
    bool urgenceled = false;
    float speed = 30.f;
    float kp = 4.0f;
    float ki = 2.0f;
    
    // Init du moteur
    MotorController motorL = { 0 };
    MotorController motorR = { 0 };
    MotorController_init(&motorL, pi, GPIO_FORWARD_L, GPIO_BACKWARD_L, GPIO_MOTOR_CONTROL_L);
    MotorController_init(&motorR, pi, GPIO_FORWARD_R, GPIO_BACKWARD_R, GPIO_MOTOR_CONTROL_R);
    MotorController_setStartPower(&motorL, 110);
    MotorController_setStartPower(&motorR, 110);
    MotorController_setController(&motorL, kp, ki);
    MotorController_setController(&motorR, kp, ki);

//------------------------------------------------------------------------------

    // Init du capteur Gauche
    UltrasonicSensor sensorL = { 0 };
    UltrasonicSensor_init(&sensorL, pi, GPIO_TRIG_L, GPIO_ECHO_L);

    // Init du capteur Droit 
    UltrasonicSensor sensorR = { 0 };
    UltrasonicSensor_init(&sensorR, pi, GPIO_TRIG_R, GPIO_ECHO_R);

//------------------------------------------------------------------------------

    /**
     * @defgroup : Init Epreuve
     * 
     * @param mode : Init le choix du mode à 0
     * @note 0 = Marche arrière -> 1 = Mode Slalom -> 2 = Mode Freinage d'urgence 
     *  -> 3 = Mode vitesse cible -> 4 = Mode Marche arrière
     */
    int mode = 0;
    printf("Mode marche arrière\n");

//------------------------------------------------------------------------------

    // Montrer que tout est bien init
    LED_blink(&led, 3, 0.2f);

//------------------------------------------------------------------------------

    // Boucle infini permettant que le code soit toujours actif
    while (true)
    {
        /**
         * @defgroup : Appel des fonctions Update 
         * 
         * @note : On remplace self part les composants init plus tôt
         */
        FPS_update(&fps);
        Input_update(&input);
        Button_update(&button);
        LED_update(&led);
        MotorController_update(&motorL);
        MotorController_update(&motorR);
        UltrasonicSensor_update(&sensorL);
        UltrasonicSensor_update(&sensorR);

//------------------------------------------------------------------------------

        // Arrêt Total du code en appuyant sur le bouton du Rasberry ou le bouton start de la manette
        if (Button_isPressed(&button) || input.startPressed){
            break;
        }

//------------------------------------------------------------------------------
        
        // Switch permettant de choisir les Epreuves en appuyant sur le bouton "MODE" de la manette
        if(input.modePressed){
            switch (mode){
            case 0:
                printf("Mode Slalom\n");
                mode++;
                break;     

            case 1:
                printf("Mode Freinage d'urgence\n");
                mode++;
                break;    

            case 2:
                printf("Mode vitesse cible\n");
                mode++;
                break;

            case 3:
                printf("Mode autonome\n");
                mode++;
                break;

            case 4:
                printf("Mode marche arrière\n");
                mode = 0;
                break;

            default:
                printf("error\n");
                break;
            }
        }

//------------------------------------------------------------------------------

        

        //Switch permettant de changer de vitesse après avoir changer gear, chaque gear correspond à une vitesse

        //Passer à la vitesse supérieur bouton "R1"
        if(input.speedLvlPlus){
        
            speed += 10.f;
            printf("SPEED : %f\n", speed);
        }

        //Passer à la vitesse inférieur bouton "L1"
        if(input.speedLvlMinus)
        {
            speed -= 10.f;
            printf("SPEED : %f\n", speed);
        }

//------------------------------------------------------------------------------

        //Switch permettant de choisir le mode adapté à l'épreuve
        switch(mode)
        {
        case 0:
            //modeMarcheArriere();
            if(input.superButtonPressed) // bouton Y
            {
                //prinf("launch c1");
                MotorController_setBackward(&motorL, false);
                MotorController_setBackward(&motorR, true);

                //speed = 40.f; //Ne pas prêter attention
                //float deltaV = input.leftAxisX * 15.f; //Ne pas prêter attention

                MotorController_setTargetSpeed(&motorL, speed);
                MotorController_setTargetSpeed(&motorR, speed);
            }else if(input.forwardDown)
            {
                MotorController_setBackward(&motorL, false);
                MotorController_setBackward(&motorR, false);

                //speed = 40.f;
                //float deltaV = input.leftAxisX * 15.f;

                MotorController_setTargetSpeed(&motorL, speed);
                MotorController_setTargetSpeed(&motorR, speed);
                
            }else if(input.backwardDown)
            {
                MotorController_setBackward(&motorL, true);
                MotorController_setBackward(&motorR, true);

                //speed = 40.f;
                //float deltaV = input.leftAxisX * 15.f;

                MotorController_setTargetSpeed(&motorL, speed);
                MotorController_setTargetSpeed(&motorR, speed);
            }
            else
            {
                MotorController_setTargetSpeed(&motorL, 0.f);
                MotorController_setTargetSpeed(&motorR, 0.f);
            }
            break;
            
        case 1:
            //modeSlalom();
            if(input.forwardDown)
            {
                MotorController_setBackward(&motorL, false);
                MotorController_setBackward(&motorR, false);

                //speed = 35.f;
                float deltaV = input.leftAxisX * 20.f;

                MotorController_setTargetSpeed(&motorL, speed + deltaV);
                MotorController_setTargetSpeed(&motorR, speed - deltaV);
            }
            else
            {
                MotorController_setTargetSpeed(&motorL, 0.f);
                MotorController_setTargetSpeed(&motorR, 0.f);
            }
            break;    
        case 2:
            //modeFreinageUrgence();
            if(urgenceled){
                LED_blink(&led, 5, 2.f/5.f);
            }

            if(input.superButtonPressed) // bouton Y
            {
                MotorController_setBackward(&motorL, false);
                MotorController_setBackward(&motorR, true);

                speed = 40.f; //Ne pas prêter attention
                //float deltaV = input.leftAxisX * 15.f; //Ne pas prêter attention

                MotorController_setTargetSpeed(&motorL, speed);
                MotorController_setTargetSpeed(&motorR, speed);
            }else if(input.backwardDown)
            {
                MotorController_setBackward(&motorL, true);
                MotorController_setBackward(&motorR, true);

                //speed = 50.f;
                float deltaV = input.leftAxisX * 15.f;

                MotorController_setTargetSpeed(&motorL, speed + deltaV);
                MotorController_setTargetSpeed(&motorR, speed - deltaV);
                
            }else if(input.forwardDown && UlrasonicSensor_getDistance(&sensorL) > 20.f)
            {
                MotorController_setBackward(&motorL, false);
                MotorController_setBackward(&motorR, false);

                //speed = 50.f;
                //float deltaV = input.leftAxisX * 15.f;

                MotorController_setTargetSpeed(&motorL, speed);
                MotorController_setTargetSpeed(&motorR, speed);
            }else if(input.forwardDown){
                urgenceled = true;

                MotorController_setTargetSpeed(&motorL, 0.f);
                MotorController_setTargetSpeed(&motorR, 0.f);
            }
            else
            {
                MotorController_setTargetSpeed(&motorL, 0.f);
                MotorController_setTargetSpeed(&motorR, 0.f);
                
                //urgenceled = true;
                //LED_blink(&led, 5, 2.f/5.f);
                
            }
                //DEMI-TOUR SUR PLACE
                //REPART EN MARCHE ARRIERE
            
            break;
            
        case 3:
            //modeVitesseCible();
            break;

        case 4:
            //modeCircuitAutonome();
            if(input.autoButtonToggle){
                MotorController_setBackward(&motorL, false);
                MotorController_setBackward(&motorR, false);

                //speed = 15.f;
                printf("%f\n", UlrasonicSensor_getDistance(&sensorR));
                
                if(UlrasonicSensor_getDistance(&sensorR) < 20.f){
                    MotorController_setTargetSpeed(&motorL, 50);
                    MotorController_setTargetSpeed(&motorR, 40);
                }else if(UlrasonicSensor_getDistance(&sensorR) > 25.f){
                    MotorController_setTargetSpeed(&motorL, 40);
                    MotorController_setTargetSpeed(&motorR, 50);
                }else{
                    MotorController_setTargetSpeed(&motorL, 50);
                    MotorController_setTargetSpeed(&motorR, 50);
                }
            }else{
                MotorController_setTargetSpeed(&motorL, 0.f);
                MotorController_setTargetSpeed(&motorR, 0.f);
            }
            break;
            
        default:
            printf("error\n");
            break;
        }
    }

    MotorController_quit(&motorL);
    MotorController_quit(&motorR);
    Button_quit(&button);
    LED_quit(&led);
    FPS_quit(&fps);
    UltrasonicSensor_quit(&sensorL);
    UltrasonicSensor_quit(&sensorR);
    pigpio_stop(pi);

    return EXIT_SUCCESS;
}
#endif
