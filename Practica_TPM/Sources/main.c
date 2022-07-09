#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#define MODULO 0xFFFF
#define BCLK 4000000
#define T_OV MODULO*PRESCALER * (1/BCLK)

void init_outputcompare(void);
void output_compare(unsigned int tiempo);
unsigned int captura(void);
void nota(int nota, int duracion);
void tone(int nota, int duracion);
void delay(int duracion);
void noTone(void);
 
unsigned int arreglo[20];

unsigned int Do = 261;
unsigned int Re = 293;
unsigned int Mi = 329;
unsigned int Fa = 349;
unsigned int Sol = 392;
unsigned int La = 440;
unsigned int Si = 493;
 
unsigned int negra = 250;
unsigned int blanca = 500;
unsigned int retardo = 3000;

void main(void) {
	SOPT1_COPE = 0;
	PTBDD_PTBDD7 = 1;	// LED de la tarjeta
	PTADD_PTADD0 = 1;	// Definir usar CH0 como TPM Output Compare
	PTAD_PTAD0 = 0;
	init_outputcompare();
	
	for(;;) {
		 PTBD_PTBD7 = ~PTBD_PTBD7;
		
		 nota(Do, negra);
		 nota(Do, negra);
		 nota(Sol, negra);
		 nota(Sol, negra);
		 nota(La, negra);
		 nota(La, negra);
		 nota(Sol, blanca);
		 
		 nota(Fa, negra);
		 nota(Fa, negra);
		 nota(Mi, negra);
		 nota(Mi, negra);
		 nota(Re, negra);
		 nota(Re, negra);
		 nota(Do, blanca);
		 
		 nota(Sol, negra);
		 nota(Sol, negra);
		 nota(Fa, negra);
		 nota(Fa, negra);
		 nota(Mi, negra);
		 nota(Mi, negra);
		 nota(Re, blanca);
		 
		 nota(Sol, negra);
		 nota(Sol, negra);
		 nota(Fa, negra);
		 nota(Fa, negra);
		 nota(Mi, negra);
		 nota(Mi, negra);
		 nota(Re, blanca);
		 
		 nota(Do, negra);
		 nota(Do, negra);
		 nota(Sol, negra);
		 nota(Sol, negra);
		 nota(La, negra);
		 nota(La, negra);
		 nota(Sol, blanca);
		 
		 nota(Fa, negra);
		 nota(Fa, negra);
		 nota(Mi, negra);
		 nota(Mi, negra);
		 nota(Re, negra);
		 nota(Re, negra);
		 nota(Do, blanca);
		 delay(retardo);
	}
}

void init_outputcompare(void) {
	TPMMOD = MODULO;
	TPMC0V = 0x0000;
	TPMC0SC = 0x14;
	TPMSC = 0x0D;
}

void output_compare(unsigned int tiempo) {
	while(!TPMC0SC_CH0F);
	TPMC0SC;
	TPMC0SC_CH0F = 0;
	TPMC0V = TPMC0V + tiempo;
}
 
void nota(int nota, int duracion) {
  tone(nota, duracion);
  delay(duracion);
  noTone();
  delay(duracion);
}

void tone(int nota, int duracion) {
	unsigned int i;
	
	PTAD_PTAD0 = ~PTAD_PTAD0;
	
	for(i = 0; i < duracion; i++) {
		output_compare(nota);
	}
}

void delay(int duracion) {
	output_compare(duracion);
}

void noTone(void) {
	PTAD_PTAD0 = ~PTAD_PTAD0;
}
