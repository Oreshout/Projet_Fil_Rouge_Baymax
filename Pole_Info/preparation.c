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