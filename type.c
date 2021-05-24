#include "type.h"

void triInventaire (item inv[])
{
    int signal;
    item temp;
    do {
        signal = 0;
        for(int i = 1; i < 4 ; i++) {
            if (inv[i].pris == VRAI && inv[i-1].pris == FAUX) {
                temp = inv[i];
                inv[i] = inv[i-1];
                inv[i-1]=temp;
                signal++;
            }
        }
    } while(signal != 0);
}
