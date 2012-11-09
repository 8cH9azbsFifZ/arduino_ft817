/* 
  CTCSS Dekoder
;  es werden die CTCSS frequenzen mit Hilfe des Goertzel Algorhytmuses detektiert
;  und zwar wird mit hilfe der Formel:
;    V = ADC + a*V1 - V2
;    V2 = V1
;    V1 = V
;  uber N_VAL = 435 Abtastungen werden die werte fuer V1 + V2 bestimmt.
;  Dabei ergibt sich eine Rechnerische Bandbreite von FS(1Khz) / N_VAL(435) = 2,3 Hz
;  was fuer die Detektion der CTCSS frequenzen ausreichend ist
;  Nach den N_VAL = 435 abtastungen des Signals wird werden die Y-Werte der
;  einzelenen Frequenzen ausgerechnet mit Hilfe der Folgenden Formel
;    Y = V1*V1 + V2*V2 - V1*V2*a
; der höchste Y Wert ist die gesuchte Frequenz (bzw. deren Index zur Minimalfrequenz)
;
;  Berechnung der Faktoren N,a,k
;  Den Faktor N der die Bandbreite des Goertzel Filter bestimmt wird folgendermassen
;  berechnet
;    N = FS/B
;    FS = Abtastfrequenz
;    B  = Bandbreite
;    N = 1000 / 2.3Hz = 435
;
;  Der Faktor k berechnet sich folgender massen
;    k = (Fk * N) / FS
;    Fk = die zu detektierende Frequenz
;    N = siehe oben
;    FS = siehe oben
;    k = 67 * 435 / 1000 = 29.145
;
;  Der Faktor a berechnet   sich folgender massen
;    a = 2 * cos ((k*2*Pi)/N)
;    a = 1.8253
*/

#include <stdio.h>
#include <math.h>

#define ABTASTRATE	1000	// Abtastungen pro Sekunde
#define BANDBREITE	3
#define MAXFREQ    	28    	// Anzahl der Frequenzen
#define N_VAL   	(ABTASTRATE/BANDBREITE)
#define MINFREQ		67		// unterste zu erkennende Frequenz

int data[N_VAL];	// ADC data, 1 Sekunde Abtastung mit 1kHz Abtastrate
int a[MAXFREQ];
int V1[MAXFREQ];
int V2[MAXFREQ];
int Y[MAXFREQ];

void init()
{
int i;
double k,af;

	for(i=0; i<MAXFREQ; i++)
	{
		k = ((MINFREQ+i*BANDBREITE)*(ABTASTRATE/BANDBREITE))/ABTASTRATE;
		af = 2*cos((k*2*3.14159)/N_VAL);
		af *= 128;	// normieren auf Werte unter 256
		a[i] = (unsigned char)af;

		V1[i]=V2[i]=0;
	}
}

#define TESTFREQ	111
void takesamples()
{
int i;

	// z.B. 100 Hz Ton, hat 100 Perioden in 1 Sekunde
	for(i=0; i<N_VAL; i++)
	{
		/*if((i%10)>5) data[i]=0;
		else data[i]=1023;*/

		data[i] = 100*cos(TESTFREQ*i*2*3.14159/ABTASTRATE);
	}
}

int calcgoerzel()
{
int step,frqcnt;
int maxf,maxy;
int V;

	for(step=0; step<N_VAL; step++)
	{
		for(frqcnt=0; frqcnt<MAXFREQ; frqcnt++)
		{
    		V = data[step] + ((a[frqcnt]*V1[frqcnt])>>7) - V2[frqcnt];
    		V2[frqcnt] = V1[frqcnt];
    		V1[frqcnt] = V;
		}	
	}

	for(frqcnt=0; frqcnt<MAXFREQ; frqcnt++)
	{
		V1[frqcnt] >>=8;
		V2[frqcnt] >>=8;
    	Y[frqcnt] = V1[frqcnt]*V1[frqcnt] + V2[frqcnt]*V2[frqcnt] - V1[frqcnt]*V2[frqcnt]*a[frqcnt];
		Y[frqcnt] = abs(Y[frqcnt]);
	}

	// seek maximum value
	maxy=0;
	for(frqcnt=0; frqcnt<MAXFREQ; frqcnt++)
	{
		if(Y[frqcnt]>maxy) {
			maxy=Y[frqcnt];
			maxf=frqcnt;
		}
	}
	maxf = (int)(MINFREQ+(double)maxf*BANDBREITE);

	return maxf;
}

int main()
{
	takesamples();
	init();

	printf("\nMAX at: %d Hz\n\n",calcgoerzel());

	return 0;
}

