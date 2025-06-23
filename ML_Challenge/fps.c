#include "fps.h"

void FPS_init(FPS *self, int pi)
{
    assert(self);
    assert(pi >= 0);
    memset(self, 0, sizeof(*self));

    self->m_pi = pi;
    self->m_prevUpdateTick = get_current_tick(self->m_pi);
}
void FPS_quit(FPS *self)
{
    assert(self && self->m_pi >= 0 && "The FPS must be initialized");
    memset(self, 0, sizeof(*self));
    self->m_pi = -1;
}

void FPS_update(FPS *self)
{
    // Vérification des paramètres
    assert(self && self->m_pi >= 0 && "The FPS must be initialized");

    // TODO : mise à jour de l'accumulateur de temps 
    //                    du compteur de frames et
    //                    de prevUpdateTick (en fin de fonction)
    self->m_count+=1;
    self->m_accu += get_current_tick(self->m_pi) - self->m_prevUpdateTick;


    // TODO : si tps écoulé > 5s, afficher le FPS et modifier les variables
    if(self->m_accu >= 5000000) {
        printf("fps : %d\n", self->m_count/5);
        self->m_count = 0;
        self->m_accu %= 5000000;
    }
    
    self->m_prevUpdateTick = get_current_tick(self->m_pi);
}
