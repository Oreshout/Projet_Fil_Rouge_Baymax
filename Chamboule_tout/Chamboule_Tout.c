#include "settings_ChambouleTout.h"

/**
*
*      CODE : Chamboule TOUT
*
*      ! Detecter les différents marqueurs et viser les goblets les plus bas pour en faire tomber le plus
*      ! possible 
*
*
*
*
*
*
*/

int pi;

bool DetectionMarkerExist()
{
    struct marker *markers = get_markers(30); // Récupération des marqueurs de 51mm de côté (à modifier en fonction de vos marqueurs !)
    
    if (markers->id != -1) // Si un marqueur est détecté
    {
        printf("Marqueur trouvé: numéro %d à %dcm de distance. x=%d y=%d\n", markers->id, markers->z, markers->x, markers->y);
        return true;
    }
    
    return false;
}

int DetectionMarker()
{
    int distance = 0;
    struct marker *markers = get_markers(30); // Récupération des marqueurs de 51mm de côté (à modifier en fonction de vos marqueurs !)
    
    if (markers->id != -1) // Si un marqueur est détecté
    {
        distance = markers->z;
        printf("Marqué à %d cm\n", distance);
    }
    
    return distance;
}

