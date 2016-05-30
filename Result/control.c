/* Exm No. B084151 */
/*
 * $Id: control-c.c,v 1.2 2002/01/08 12:32:48 spb Exp spb $
 *
 * Control program for the MD update
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DECL
#include "coord.h"

double second(void);
int main(int argc, char *argv[]){

  int i,j;
  FILE *in, *out;
  double start,stop;
  char name[80];

  /*  timestep value */
  double dt=0.02;

  /*  number of timesteps to use. */
  int Nstep=100;
  int Nsave=5;

  if( argc > 1 ){
    Nstep=atoi(argv[1]);
  }
  wind[Xcoord] = 0.9;
  wind[Ycoord] = 0.4;
  wind[Zcoord] = 0.0;

  /* set up multi dimensional arrays */
  /* dynamic allocation (Malloc faster than Calloc)
//   mass = malloc(Nbody*sizeof(double));
//   radius = malloc(Nbody*sizeof(double));
//   visc = malloc(Nbody*sizeof(double));
//   for(i=0;i<Ndim;i++){
//     f[i] = malloc(Nbody*sizeof(double));
//     pos[i] = malloc(Nbody*sizeof(double));
//     vel[i] = malloc(Nbody*sizeof(double));
//   }

/* read the initial data from a file */

  collisions=0;
  in = fopen("input.dat","r");

  if( ! in ){
    perror("input.dat");
    exit(1);
  }
  int useOptimizedEvolve = 1;
  for(i=0;i<Nbody;i++){
    fscanf(in,"%16le%16le%16le%16le%16le%16le%16le%16le%16le\n",
                mass+i,radius+i,visc+i,
                &pos[Xcoord][i], &pos[Ycoord][i], &pos[Zcoord][i],
                &vel[Xcoord][i], &vel[Ycoord][i], &vel[Zcoord][i]);
//      if(radius[0] != radius[i])      // <-- input data optimization
//        useOptimizedEvolve = 0;
  }
  //radiusOptimized = 2*radius[0];
  fclose(in);

/* clever_k intitialization for faster tilling */
// for(i=0; i<Nbody; i++)
//     clever_k[i] =  Npair - (Nbody-i)*((Nbody-i)-1)/2 - i - 1;

 /*
  * Run Nstep timesteps and time how long it took
  */
  for(j=1;j<=Nsave;j++){
    start=second();
//      if(useOptimizedEvolve)      // <-- use the optimize evolve function ( if we create one)
//        evolveOp(Nstep,dt);
//      else
    evolve(Nstep,dt);
    stop=second();


    printf("%d timesteps took %f seconds\n",j*Nstep,stop-start);
    //  printf("collisions %d\n",collisions);       // no need for this information

/* write final result to a file */
    sprintf(name,"output.dat%03d",j*Nstep);
    out = fopen(name,"w");

    if( ! out ){
        perror(name);
	    exit(1);
    }

    for(i=0;i<Nbody;i++){
	  fprintf(out,"%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E\n",
		mass[i],radius[i],visc[i],
		pos[Xcoord][i], pos[Ycoord][i], pos[Zcoord][i],
		vel[Xcoord][i], vel[Ycoord][i], vel[Zcoord][i]);
    }
    fclose(out);
  }

}

double second()
{
/* struct timeval { long        tv_sec;
            long        tv_usec;        };

struct timezone { int   tz_minuteswest;
             int        tz_dsttime;      };     */

        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}
