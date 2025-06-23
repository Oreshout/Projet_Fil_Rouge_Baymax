#include "motor_controller.h"
#include "tools.h"

static void _MotorController_cb(
    int pi, unsigned gpio, unsigned level, uint32_t tick, void *user);

void MotorController_init(MotorController *self, int pi, int gpioForward, int gpioBackward, int gpioControl)
{
    // Vérification des paramètres
    assert(self);
    assert(pi >= 0);
    assert(0 <= gpioForward && gpioForward < 32);
    assert(0 <= gpioBackward && gpioBackward < 32);
    assert(0 <= gpioControl && gpioControl < 32);
    memset(self, 0, sizeof(*self));

    uint32_t currTick = get_current_tick(self->m_pi);

    // Initialisation des champs de l'objet
    self->m_pi = pi;
    self->m_gpioForward = gpioForward;
    self->m_gpioBackward = gpioBackward;
    self->m_gpioControl = gpioControl;
    self->m_gpioMotor = gpioForward;
    self->m_callbackID = -1;

    // Constantes pour le PI à adapter en fonction du comportement du robot
    // Ne pas les modifier pour l'évaluation auto sur Moodle
    self->m_kp = 4.f;
    self->m_ki = 4.f;
    
    self->m_cbCount = 0;
    self->m_prevCbTick = currTick;
    self->m_prevUpdateTick = currTick;
    // On laisse passer 4 fentes avant de commencer la régulation
    self->m_controllerCbCount = self->m_cbCount + 4;

    // Initialisation des GPIO
    set_mode(self->m_pi, self->m_gpioForward, PI_OUTPUT);
    set_mode(self->m_pi, self->m_gpioBackward, PI_OUTPUT);
    set_mode(self->m_pi, self->m_gpioControl, PI_INPUT);
    set_pull_up_down(self->m_pi, self->m_gpioControl, PI_PUD_DOWN);

    // Branchement du callback
    self->m_callbackID = callback_ex(
        self->m_pi, self->m_gpioControl, RISING_EDGE,
        _MotorController_cb, self
    );
    assert(self->m_callbackID >= 0);
}

void MotorController_quit(MotorController *self)
{
    assert(self && self->m_pi >= 0 && "The MotorController must be initialized");
    gpio_write(self->m_pi, self->m_gpioForward, PI_LOW);
    gpio_write(self->m_pi, self->m_gpioBackward, PI_LOW);
    
    assert(self->m_callbackID >= 0);
    int exitStatus = callback_cancel(self->m_callbackID);
    assert(exitStatus == 0);

    memset(self, 0, sizeof(*self));
    self->m_pi = -1;
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

void MotorController_setController(MotorController *self, float kp, float ki)
{
    assert(self && self->m_pi >= 0 && "The MotorController must be initialized");
    self->m_kp = kp;
    self->m_ki = ki;
}

void MotorController_setStartPower(MotorController *self, int startPower)
{
    assert(self && self->m_pi >= 0 && "The MotorController must be initialized");
    self->m_startPower = startPower;
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

void MotorController_stop(MotorController *self)
{
    assert(self && self->m_pi >= 0 && "The MotorController must be initialized");
    gpio_write(self->m_pi, self->m_gpioForward, PI_LOW);
    gpio_write(self->m_pi, self->m_gpioBackward, PI_LOW);
    self->m_targetSpeed = 0.f;
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

float MotorController_getSpeed(MotorController *self)
{
    if (self->m_cbCount < self->m_controllerCbCount) return self->m_targetSpeed;
    return self->m_speed;
}

float MotorController_getDistance(MotorController *self)
{
    return (float)(self->m_cbCount) * 18.8495556f / 20.f;
}

static void _MotorController_cb(
    int pi, unsigned gpio, unsigned level, uint32_t tick, void *user)
{
    MotorController *self = (MotorController *)user;

    if (tick - self->m_prevCbTick < 10)
    {
        // Erreur de callback
        return;
    }

    float speed = 1000000.f / (float)(tick - self->m_prevCbTick);
    if (speed >= 120.f)
    {
        // Erreur de mesure
        self->m_errorCount++;
        return;
    }

    self->m_speed = speed;
    self->m_prevCbTick = tick;
    self->m_cbCount++;
}
