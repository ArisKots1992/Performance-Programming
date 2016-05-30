/* Exm No. B084151 */
/*
 *  Simple molecular dynamics code.
 *  $Id: MD-c.c,v 1.2 2002/01/31 16:43:14 spb Exp spb $
 *
 * This program implements:
 *     long range inverse square forces between particles. F = G * m1*m2 / r**2
 *     viscosity term     F = -u V
 * If 2 particles approach closer than Size we flip the direction of the
 * interaction force to approximate a collision.
 *
 * Coordinates are relative to a large central mass and the entire system is moving relative to the
 * viscous media.
 * If 2 particles approach closer than Size we flip the direction of the
 * interaction force to approximate a collision.
 *
 * This program was developed as part of a code optimisation course
 * and is therefore deliberately inefficient.
 *
 */
#include <stdio.h>
#include <math.h>
#include "coord.h"

/* optimized evolve for radiusOptimized=constant double */

void evolve(int count,double dt){
int  step;
int i,j,k,l,k1;
double Size;
double temp,temp1;
double G_M;
double f1,f2,f3,t;

/*
 * Loop over timesteps.
 */
    for(step = 1;step<=count;step++){
    //    printf("timestep %d\n",step);
    //    printf("collisions %d\n",collisions);

/* Final Optimization I combinatoon */
/* set the viscosity term in the force calculation */
/* add the wind term in the force calculation */
/* calculate distance from central mass */
/* calculate central force */
        for(i=0; i<Nbody; i++){
            temp = forcePartA(G_M_central*mass[i],sqrt( (pos[0][i] * pos[0][i])  +
                                                        (pos[1][i] * pos[1][i])  +
                                                        (pos[2][i] * pos[2][i]) ));
           /*  flip force if close in */
           f[0][i] = -visc[i] * vel[0][i] -visc[i] * wind[0] - forcePartB(temp,pos[0][i]);
           f[1][i] = -visc[i] * vel[1][i] -visc[i] * wind[1] - forcePartB(temp,pos[1][i]);
           f[2][i] = -visc[i] * vel[2][i] -visc[i] * wind[2] - forcePartB(temp,pos[2][i]);
        }

/* Final Optimization II combination */
/* calculate pairwise separation of particles */
/* calculate norm of seperation vector */
/* add pairwise forces. */

// some clever equations to retrieve i,j,k whenever we want from the triangular array
//i = n - 2 - floor(sqrt(-8*k + 4*n*(n-1)-7)/2.0 - 0.5)
//j = k + i + 1 - n*(n-1)/2 + (n-i)*((n-i)-1)/2
//k = (n*(n-1)/2) - (n-i)*((n-i)-1)/2 + j - i - 1;

        k = 0;
        f1=0; f2=0; f3=0;
        for(i=0;i<Nbody;i++){
            G_M = G*mass[i];
            Size = radius[i];
            for(j=i+1;j<Nbody;j++){
                t = sqrt( ((pos[0][i] - pos[0][j]) * (pos[0][i] - pos[0][j]))  + // <- delta_pos
                          ((pos[1][i] - pos[1][j]) * (pos[1][i] - pos[1][j]))  +
                          ((pos[2][i] - pos[2][j]) * (pos[2][i] - pos[2][j])) );
                k1=copysign(1,t -Size - radius[j]); // Instead of IF!

                temp1 = forcePartA(G_M*mass[j],t);

                temp = k1 * forcePartB(temp1,pos[0][i] - pos[0][j]);;
                f1-=temp;
                f[0][j] = f[0][j] + temp;

                temp = k1 * forcePartB(temp1,pos[1][i] - pos[1][j]);
                f2-=temp;
                f[1][j] = f[1][j] + temp;

                temp = k1 * forcePartB(temp1, pos[2][i] - pos[2][j]);
                f3-=temp;
                f[2][j] = f[2][j] + temp;

                k++;
            }
            f[0][i] = f[0][i] + f1;
            f[1][i] = f[1][i] + f2;
            f[2][i] = f[2][i] + f3;
            f1=0;f2=0;f3=0;
        }

        /* update positions */
        for(i=0;i<Nbody;i++){
          for(j=0;j<Ndim;j++){
            pos[j][i] += dt * vel[j][i];
            vel[j][i] += dt * (f[j][i]/mass[i]);
          }
        }
      }

}
