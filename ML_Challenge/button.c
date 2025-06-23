#include "button.h"

static void _Button_cb(
    int pi, unsigned gpio, unsigned level, uint32_t tick, void *user);

void Button_init(Button *self, int pi, int gpio)
{
    // Vérification des arguments
    assert(self);
    assert(pi >= 0);
    assert(0 <= gpio && gpio < 32);

    // Initialisation des champs de la structure self
    memset(self, 0, sizeof(*self));
    self->m_pi = pi;
    self->m_gpio = gpio;

    // Connexion aux GPIO
    set_mode(self->m_pi, self->m_gpio, PI_INPUT);
    set_pull_up_down(self->m_pi, self->m_gpio, PI_PUD_DOWN);

    // Branchement du callback
    self->m_callbackID = callback_ex(
        self->m_pi, self->m_gpio, RISING_EDGE,
        _Button_cb, self);
    assert(self->m_callbackID >= 0 && "The callback ID must be >= 0");
    //
}

void Button_quit(Button *self)
{
    // Vérification des paramètres de la fonction
    assert(self && self->m_pi >= 0 && "The MotorController must be initialized");    
    assert(self->m_callbackID >= 0);

    // Annulation du callback
    int exitStatus = callback_cancel(self->m_callbackID);
    assert(exitStatus == 0);

    // Réinitialisation des champs de l'objet
    memset(self, 0, sizeof(*self));
    self->m_pi = -1;
    //
}

void Button_update(Button *self)
{
    // Vérification des paramètres de la fonction
    assert(self && self->m_pi >= 0 && "The Button must be initialized");

    
    // TODO : comparer les compteurs prev et curr
    //        et modifier la valeur de isPressed en fonction
    //        Si besoin, mise à jour de prev
    if(self->m_prevCbCount < self->m_currCbCount){
        self->m_prevCbCount = self->m_currCbCount;
        self->m_isPressed = true;
    }else{
        self->m_isPressed = false;
    }
}

bool Button_isPressed(Button *self)
{
    // Vérification des paramètres de la fonction
    assert(self && self->m_pi >= 0 && "The Button must be initialized");

    // TODO retourner la valeur de la variable m_isPressed
    return self -> m_isPressed;
}

static void _Button_cb(
    int pi, unsigned gpio, unsigned level, uint32_t tick, void *user)
{
    // Cast du pointeur user pour accéder aux champs de la structure
    Button *self = (Button *)user;

    // TODO : incrémenter le compteur curr
    printf("I am pressed");
    self->m_currCbCount+=1;
}
