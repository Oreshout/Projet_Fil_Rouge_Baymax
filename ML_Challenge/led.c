#include "led.h"

void LED_init(LED *self, int pi, int gpio)
{
    assert(self);
    assert(pi >= 0);
    assert(0 <= gpio && gpio < 32);
    memset(self, 0, sizeof(*self));

    self->m_pi = pi;
    self->m_gpio = gpio;
    self->m_cycleTime = 1000000;
    self->m_prevUpdateTick = get_current_tick(self->m_pi);
    
    set_mode(self->m_pi, self->m_gpio, PI_OUTPUT);
}

void LED_quit(LED *self)
{
    assert(self && self->m_pi >= 0 && "The LED must be initialized");

    // TODO : envoyer un signal bas
    gpio_write(self -> m_pi, self ->  m_gpio, PI_LOW);
    
    // TODO : Ré-initialiser la structure
    memset(self, 0, sizeof(*self));
    self->m_pi = -1;
}

void LED_update(LED *self)
{
    assert(self && self->m_pi >= 0 && "The LED must be initialized");

    // TODO : si nécessaire, gérer le clignotement
    
    if(LED_isBlinking(self))
    {
        self->m_accu += get_current_tick(self->m_pi) - (self->m_prevUpdateTick);

        if(self->m_accu >= self->m_cycleTime)
        {
            if(self-> m_cycleIndex % 2 == 0)
            {
                 gpio_write(self -> m_pi, self -> m_gpio, PI_LOW);
            }
            else
            {
                 gpio_write(self -> m_pi, self -> m_gpio, PI_HIGH);
            }
            self->m_cycleIndex++;
            if(self-> m_cycleIndex == self ->  m_cycleCount){
                gpio_write(self -> m_pi, self -> m_gpio, PI_LOW);   
            }
        }
        self->m_accu=self->m_accu%self->m_cycleTime;
        self->m_prevUpdateTick = get_current_tick(self->m_pi);    
    }
}


void LED_blink(LED *self, int count, float cycleTime)
{
    assert(self && self->m_pi >= 0 && "The LED must be initialized");

    // TODO : initialiser correctement les champs de la structure pour lancer un clignotement
    self->m_accu = 0;
    self->m_cycleCount = count*2;
    self->m_cycleTime = (cycleTime*1000000)/2;
    self->m_cycleIndex = 0;
    // TODO : allumer la led (mode PI_HIGH)
    
    gpio_write(self -> m_pi, self -> m_gpio, PI_HIGH);
    self->m_prevUpdateTick = get_current_tick(self->m_pi); 
}

bool LED_isBlinking(LED *self)
{
    assert(self && self->m_pi >= 0 && "The LED must be initialized");

    // TODO : vérifier si les cycles sont terminés
    if(self ->  m_cycleIndex < self ->  m_cycleCount)
    {
        return true;
    
    }
    return false;
}

