/* Exm No. B084151 */
/* $Id: coord.h,v 1.2 2002/01/08 12:32:48 spb Exp spb $
 * This file defines static arrays that contains the primary coordinates
 * of the particles,
 *
 *  Nbody	Number of particles
 *  Npair	Number of particle pairs
 *  pos		Position of the particles
 *  r           distance of partice from central mass
 * vel		velocity of the particles
 *  f		Forces acting on each particle
 *  visc		viscosity coefficient for each particle
 *  mass		mass of each particle
 *  delta_pos	seperation vector for each particle pair
 *  delta_r		seperation for each particle pair
 */

#ifdef DECL
#define DEF
#else
#define DEF extern
#endif
#define Ndim 3  // <-- optimization Constant folding
#define Nbody 4*1024
#define  Npair ((Nbody*(Nbody-1))/2)    // = 8386560
#define force(w,d,r) ((w)*(d))/((r)*(r)*(r))    // Inline optimization force
#define forcePartB(w,d) ((w)*(d))               // Inline force part B
#define forcePartA(w,r) ((w))/((r)*(r)*(r))     // Inline force part A
#define B 512       // block for tilling
enum{ Xcoord=0, Ycoord, Zcoord };   // <-- removed he Ndim

/* Array padding & the arrays are now allocated static (to the stack) */
DEF double pos[Ndim][Nbody+64], vel[Ndim][Nbody+64];
DEF double f[Ndim][Nbody+64], visc[Nbody], mass[Nbody], radius[Nbody];
//DEF double radiusOptimized;     // for input optimization
DEF double wind[Ndim];
DEF int collisions;
//DEF int clever_k[Nbody];        // for tilling optimization

#define G 2.0
#define M_central 1000.0
#define G_M_central G*M_central
void evolve(int Nstep, double dt);
