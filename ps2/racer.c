#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double prom_vrem(double newK, int *lenth, int *veloc, int parts_quanity) {
            double velocityK;
            double new_timeK = 0;
            int i = 0;
            while (i < parts_quanity) {
                velocityK = (double)veloc[i]+newK;
                new_timeK += (double)lenth[i]/velocityK;
                i++;
                }
                return new_timeK;
            }



    int main() {
        double minim_K, max_K, newK;
        int parts_quanity, commonTime, K_temp;
        scanf("%d %d", &parts_quanity, &commonTime);
        int *lenth = malloc(sizeof(int)*parts_quanity);
        int *veloc = malloc(sizeof(int)*parts_quanity);
        for (int i = 0; i < parts_quanity; i++) {
            scanf("%d %d", &lenth[i], &veloc[i]);
            if (i==0)
                K_temp = veloc[i];
            if (veloc[i] < K_temp)
                K_temp = veloc[i];
        }
        minim_K = 0.000000001 + K_temp*(-1);
        max_K = 1000;
        while (max_K-minim_K > 0.000000001) {
            newK = (minim_K+max_K)/2;
            if (prom_vrem(newK, lenth, veloc, parts_quanity) < commonTime )
                max_K = newK;
            else
                minim_K = newK;
        }
            free(lenth);
            free(veloc);
        printf("%.9f\n",(max_K+minim_K)/2);
    }
