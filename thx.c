#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sndfile.h"

#define LERP(t, a, b)	((1-(t))*(a)+(t)*(b))
#define N_OSCILLATORS	(150)
#define SWING		(9.)

#define SAMPLERATE	(44100)
#define DURATION	(10*SAMPLERATE)
#define HOLDDURATION	(2.5*SAMPLERATE)

typedef struct t_oscillators {
	double f0, f1 ;
	double omega ;
} Oscillator ;

Oscillator osc[N_OSCILLATORS] ;

#if 0
double freqs[]  = { 65.406, 32.703, 
		    41.204, 82.407,
		    48.999, 97.999,
	 	 130.813, 261.626, 523.251, 1046.602,
       		 164.814, 329.628, 659.255, 1318.510,
		 195.998, 391.995, 783.991, 1567.982 } ;
#endif

double freqs[] = {
	20.625,
	41.25,
	82.5,
	165.0,
	330.0,
	660,
	1320,
	2640,
	5280,
	10560,
} ;



double
pickfreq(double f)
{
	return freqs[lrand48() % 10] ;
}

main()
{
    int i ;
    SNDFILE *sf ;
    SF_INFO sfinfo ;
    int s ;
    double f, t, sum ;

    srand48(314) ;

    for (i=0; i<N_OSCILLATORS; i++) {
	/* random phase */
   	osc[i].omega = drand48() * 2.0 * M_PI ;
	t = drand48() ;
	t = t * t ;
	osc[i].f0 = LERP(t, 32.f, 1760.0) ;
	osc[i].f1 = pickfreq(osc[i].f0) + (drand48() - 0.5) * SWING ;
    }

    sfinfo.channels = 1 ;
    sfinfo.samplerate = SAMPLERATE ;
    sfinfo.format = SF_FORMAT_WAV|SF_FORMAT_PCM_16 ;

    sf = sf_open("thx.wav", SFM_WRITE, &sfinfo) ;

    for (s=0; s < DURATION; s++) {
	t = pow((s + 0.5) / (DURATION), .15) ;
	sum = 0. ;
	for (i=0; i<N_OSCILLATORS; i++) {
	    f = LERP(t, osc[i].f0, osc[i].f1) ;
	    osc[i].omega += f * 2.0 * M_PI / SAMPLERATE ;
	    osc[i].omega = fmod(osc[i].omega, 2.0 * M_PI) ;
	    sum += cos(osc[i].omega) ;
	}
	sum /= N_OSCILLATORS ;
	sf_write_double(sf, &sum, 1) ;
    }
    for (s=0; s < HOLDDURATION; s++) {
	sum = 0. ;
	for (i=0; i<N_OSCILLATORS; i++) {
	    osc[i].omega += osc[i].f1 * 2.0 * M_PI / SAMPLERATE ;
	    osc[i].omega = fmod(osc[i].omega, 2.0 * M_PI) ;
	    sum += cos(osc[i].omega) ;
	}
	sum /= N_OSCILLATORS ;
	sf_write_double(sf, &sum, 1) ;
    }

    sf_close(sf) ;
    
}
