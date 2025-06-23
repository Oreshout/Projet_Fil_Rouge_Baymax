#include "settings.h"

/**
*
*
*    CODE : Pêche aux canards
*
*/


int DetectionMarker()
{
    int distance = 0;
    struct marker *DetectionMarker = getmarkers(30);
   
    distance = DetectionMarker->z;
    printf("Marqué à %d cm\n", distance);
    
    return distance;
}

void GestionBras()
{

}

void GestionServoMoteur()
{

}

void GestionMoteur()
{

}

void GestionBouton()
{

}

int main()
{
    
}