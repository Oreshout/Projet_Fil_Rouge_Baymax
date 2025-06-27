#include "settings_PecheAuxCanards.h"

int pi;

void initServoMoteur()
{
    set_mode(pi, servo_pin, PI_OUTPUT); // Met le GPIO du servo en mode sortie
    set_servo_pulsewidth(pi, servo_pin, 1675); // Position initiale du servo
    usleep(500000); // Pause de 0.5 seconde pour laisser le temps au servo de se positionner
}

int DetectionMarker()
{
    int distance = -1;
    struct marker *detection = get_markers(30);

    if (detection != NULL && detection->id != -1) 
    {
        distance = detection->z;
        printf("Detection : Marqué à %d cm\n", distance);
    } 
    else
    {
        printf("Detection : Aucun marqueur détecté\n");
    }

    return distance;
}

bool DetectionMarkerExist()
{
    struct marker *DetectionMarker = get_markers(30);
    
    if (DetectionMarker->id != -1) // Si un marqueur est détecté
    {
        printf("BOOL : Marqueur trouvé: numéro %d à %dcm de distance. x=%d y=%d\n", DetectionMarker->id, DetectionMarker->z, DetectionMarker->x, DetectionMarker->y);
        return true;
    }
    
    return false;
}


void* distance_update(void* arg)
{
    while (1) 
    {
        struct marker *markers = get_markers(30);
        if (markers == NULL) continue;

        struct marker *m;
        for (m = markers; m->id != -1; m++) 
        {
            printf("Marqueur trouvé: numéro %d à %dcm de distance. x=%d y=%d\n", m->id, m->z, m->x, m->y);
        }
        usleep(500000); // Petite pause pour éviter d'inonder le terminal
    }

    return NULL;
}

void GestionAttrape()
{
    // Implémentez ici la logique pour attraper le marqueur
    printf("Attrape du marqueur en cours...\n");
  
    set_mode(pi, servo_pin, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pin, 2000); // Position initiale 
    usleep(500000); // Pause de 0.5 seconde pour simuler l'attrape
}

void GestionLache()
{
    // Implémentez ici la logique pour attraper le marqueur
    printf("Attrape du marqueur en cours...\n");
  
    set_mode(pi, servo_pin, PI_OUTPUT);
    set_servo_pulsewidth(pi, servo_pin, 1750); // Position initiale 
    usleep(500000); // Pause de 0.5 seconde pour simuler l'attrape
}

void MotorController_setTargetSpeed(MotorController *self, float speed)
{
    assert(self && self->m_pi >= 0 && "The MotorController must be initialized");
    
    if (speed < MIN_SPEED)
    {
        MotorController_stop(self);
    }
    else
    {
        if (self->m_targetSpeed < MIN_SPEED)
        {
            // Le moteur est actuelement arrêté
            // Il faut le redémarrer
            self->m_controllerCbCount = self->m_cbCount + 4;
            self->m_integral = self->m_startPower;
            self->m_power = self->m_startPower;
        }
        self->m_targetSpeed = speed;
    }
}

void MotorController_setBackward(MotorController *self, bool goBackward)
{
    assert(self && self->m_pi >= 0 && "The MotorController must be initialized");
    
    // TODO : Attribution du bon gpio au gpiomotor en fonction de goBackward
    //        Arret du moteur en cas de changement de sens de rotation
    if (goBackward)
    {
        if(self->m_gpioMotor != self->m_gpioBackward){
           MotorController_stop(self);
            self->m_gpioMotor = self->m_gpioBackward; 
        }
        
    }else{
        if(self->m_gpioMotor != self->m_gpioForward){
            MotorController_stop(self);
            self->m_gpioMotor = self->m_gpioForward;
        }
        
    }
}


void MotorController_update(MotorController *self)
{
    assert(self && self->m_pi >= 0 && "The MotorController must be initialized");
    
    if(self->m_targetSpeed == 0){
       return; 
    }
    
    // TODO : calcul du PI si une nouvelle fente est détectée et vitesse cible suffisante
    if(self->m_controllerCbCount > self->m_cbCount){
        set_PWM_dutycycle(self->m_pi, self->m_gpioMotor, self->m_startPower);
    }else{
        float e = (self->m_targetSpeed - self->m_speed);
        // TODO : Calcule le dt
        float dt = (get_current_tick(self->m_pi)-self->m_prevUpdateTick)/1000000.f;
        self->m_prevUpdateTick = get_current_tick(self->m_pi);
        
        // TODO : Calcule l'intégrale
        self->m_integral += self->m_ki*(e * dt);

        // TODO : Calcule la puissance avec le PI
        self->m_power = self->m_kp*e + self->m_integral;

        // TODO : Si saturation, increment de saturationTime
        if (self->m_power >= 255)
        {
            self->m_saturationTime+=dt;
        }

        // TODO : commander le moteur avec la puissance calculée
        set_PWM_dutycycle(self->m_pi, self->m_gpioMotor, self->m_power);

    }
}

void PatternMouvementSiAucunMarqueur(MotorController *motorL, MotorController *motorR)
{
    int temp = 0;
    int tour = 0;
    struct marker* markerData = get_markers(30);

    temp = rand() % 2; // Génère un nombre aléatoire entre 0 et 1
    usleep(500000); // Pause de 1 seconde pour éviter une boucle trop rapide
    MotorController_setBackward(motorL, false); // ← AJOUTÉ
    MotorController_setBackward(motorR, false);
    MotorController_setTargetSpeed(motorL, 10.0f); // 10.0f = vitesse en rad/s ou unités utilisées dans ton contrôleur
    MotorController_setTargetSpeed(motorR, 10.0f);
    MotorController_update(motorL);
    MotorController_update(motorR);
    usleep(500000); // Avance pendant 0.5 seconde
    if(temp == 1)
    {
        MotorController_stop(motorL);
        MotorController_stop(motorR);
        MotorController_setBackward(motorL, true);
        MotorController_setBackward(motorR, false); // Avance
        MotorController_setTargetSpeed(motorL, 30.0f);
        MotorController_setTargetSpeed(motorR, 30.0f);
        MotorController_update(motorL);
        MotorController_update(motorR);
        usleep(100000); // 0.5s de rotation
        MotorController_stop(motorL);
        MotorController_stop(motorR);
        sleep(2); // Pause de 0.5 seconde pour éviter une boucle trop rapide
    }
    else if(temp == 0)
    {
        MotorController_stop(motorL);
        MotorController_stop(motorR);
        MotorController_setBackward(motorL, false);
        MotorController_setBackward(motorR, true); // Avance
        MotorController_setTargetSpeed(motorL, 30.0f);
        MotorController_setTargetSpeed(motorR, 30.0f);
        MotorController_update(motorL);
        MotorController_update(motorR);
        usleep(100000); // 0.5s de rotation
        MotorController_stop(motorL);
        MotorController_stop(motorR);
        usleep(500000); // Pause de 0.5 seconde pour éviter une boucle trop rapide
    }

    while(tour < 12)
    {
        if(markerData != NULL && markerData->id != -1 && markerData->y > -1 && markerData->y < 1) // Si un marqueur est détecté
        {
            printf("43534534523 ,Un marqueur a été détecté, le robot avance.Y = %d\n", markerData -> y);
            break; // Sort de la fonction si un marqueur est détecté
        }

        MotorController_stop(motorL);
        MotorController_stop(motorR);
        MotorController_setBackward(motorL, false);
        MotorController_setBackward(motorR, true); // Avance
        MotorController_setTargetSpeed(motorL, 30.0f);
        MotorController_setTargetSpeed(motorR, 30.0f);
        MotorController_update(motorL);
        MotorController_update(motorR);
        usleep(10000); // 0.5s de rotation
        MotorController_stop(motorL);
        MotorController_stop(motorR);
        sleep(1); // 0.5s de rotation
        tour++;
    }

    MotorController_setBackward(motorL, false); // ← AJOUTÉ
    MotorController_setBackward(motorR, false);

    printf("Aucun marqueur détecté, le robot avance.\n");
}


void MotorController_stop(MotorController *self)
{
    assert(self && self->m_pi >= 0 && "The MotorController must be initialized");
    gpio_write(self->m_pi, self->m_gpioForward, PI_LOW);
    gpio_write(self->m_pi, self->m_gpioBackward, PI_LOW);
    self->m_targetSpeed = 0.f;
}

int main()
{
    pi = pigpio_start(NULL, NULL); // Démarre la bibliothèque pigpio pour le contrôle des GPIO


    float kp = 4.0f; // Valeurs conseillées pour le contrôleur PI
    float ki = 2.0f;

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

    initServoMoteur(); // Initialisation du servo moteur

    printf("\033[1;31mDémarrage du programme de détection de marqueurs...\033[0m\n");

  //? Ajout Distanceupdate

    while(true)
    {

        struct marker* markerData = get_markers(30);

        if(markerData != NULL && markerData->id != -1)
        {
            int distance = markerData->z;
            printf("\033[1;34mUn marqueur a été détecté à %dcm.\033[0m\n", distance);

            if(DetectionMarkerExist()) // Si un marqueur est détecté
            {
                
                printf("\033[1;34mUn marqueur a été détecté à %dcm.\033[0m\n", distance);

                /*MotorController_setTargetSpeed(&motorL, 10.0f); // 10.0f = vitesse en rad/s ou unités utilisées dans ton contrôleur
                MotorController_setTargetSpeed(&motorR, 10.0f);
                MotorController_update(&motorL);
                MotorController_update(&motorR);
                usleep(1000); // Avance pendant 0.1 seconde
                DetectionMarker(); // Vérifie si un marqueur est détecté
                printf("\033[1;34mUn marqueur a été détecté à %dcm.\033[0m\n", DetectionMarker());
                MotorController_stop(&motorL); // Arrêt des moteurs    
                MotorController_stop(&motorR); // Arrêt des moteurs
                printf("\033[1;33mArrêt des moteurs après avoir détecté un marqueur.\033[0m\n");*/

                if(distance < 10) // Si le marqueur est à moins de 7 cm
                {
                    MotorController_setBackward(&motorL, false); 
                    MotorController_setBackward(&motorR, false);
                    GestionAttrape(); 

                    usleep(10000); // pause
                    /*markerData = get_markers(30); // 🔁 Rafraîchissement
                    
                    if(markerData != NULL && markerData->id != -1)
                        distance = markerData->z;

                    usleep(100000); // pause
                    markerData = get_markers(30); // 🔁 Encore un rafraîchissement
                    if(markerData != NULL && markerData->id != -1)
                        distance = markerData->z;
                    */
                    // Avance un peu
                    MotorController_setTargetSpeed(&motorL, 10.0f);
                    MotorController_setTargetSpeed(&motorR, 10.0f);
                    MotorController_update(&motorL);
                    MotorController_update(&motorR);

                    usleep(250000); // moitié de la phase d’avance
                    /*
                    markerData = get_markers(30); // 🔁 Surveillance en cours de route
                    if(markerData != NULL && markerData->id != -1)
                        distance = markerData->z;
                    */
                    usleep(250000); // fin de l’avance
                    MotorController_stop(&motorL);    
                    MotorController_stop(&motorR);

                    usleep(100000);
                    /*
                    markerData = get_markers(30); // Encore une vérif avant de lâcher
                    if(markerData != NULL && markerData->id != -1)
                        distance = markerData->z;
                    */


                    // Lâche
                    GestionLache();

                    // Recule
                    MotorController_setBackward(&motorL, true); 
                    MotorController_setBackward(&motorR, true); 
                    MotorController_setTargetSpeed(&motorL, 10.0f);
                    MotorController_setTargetSpeed(&motorR, 10.0f);
                    MotorController_update(&motorL);
                    MotorController_update(&motorR);

                    printf("Le robot va reculer après avoir attrapé le marqueur.\n");

                    usleep(250000);
                    /*
                    markerData = get_markers(30); // 🔁 Pendant le recul
                    if(markerData != NULL && markerData->id != -1)
                        distance = markerData->z;
                    */
                    usleep(250000);
                    MotorController_stop(&motorL);    
                    MotorController_stop(&motorR);
                }
                else if(DetectionMarker() >= 10) // Si le marqueur est à plus de 15 cm
                {
                    printf("Le marqueur est trop loin pour être attrapé.\n");
                    MotorController_setTargetSpeed(&motorL, 10.0f); // 10.0f = vitesse en rad/s ou unités utilisées dans ton contrôleur
                    MotorController_setTargetSpeed(&motorR, 10.0f);
                    MotorController_update(&motorL);
                    MotorController_update(&motorR);
                    usleep(100000); // Avance pendant 0.5 seconde
                    MotorController_stop(&motorL); // Arrêt des moteurs    
                    MotorController_stop(&motorR); // Arrêt des moteurs
                }
                else
                {
                    printf("Le marqueur est trop loin pour être attrapé.\n");
                }
            }
        }
        else
        {
            if(DetectionMarkerExist() == false)
            {
                printf("\033[1;31mAucun marqueur détecté, le robot va avancer.\033[0m\n");
                printf("Arrêt des moteurs après avoir avancé.\n");
                PatternMouvementSiAucunMarqueur(&motorL, &motorR); // Avance si aucun marqueur n'est détecté
                printf("Je viens de faire le pattern de mouvement car aucun marqueur n'est détecté.\n");
                printf("Le robot avance car aucun marqueur n'est détecté.\n");
                initServoMoteur(); // Initialisation du servo moteur
                usleep(500000); // Pause de 0.5 seconde pour éviter une boucle
            }
        }
    }

    pigpio_stop(pi); // Arrête la bibliothèque pigpio
    return 0; // Retourne 0 pour indiquer que le programme s'est terminé avec succès
}