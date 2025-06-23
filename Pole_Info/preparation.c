/**
*
*
*      PREPARATION A FAIRE JOUR 1 
*
*
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

bool LED_isBlinking(LED *self)  // LED pin : 21
{
    assert(self && self->m_pi >= 0 && "The LED must be initialized");

    // TODO : vérifier si les cycles sont terminés
    if(self ->  m_cycleIndex < self ->  m_cycleCount)
    {
        return true;
    
    }
    return false;
}