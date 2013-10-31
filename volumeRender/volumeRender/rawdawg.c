#include <stdio.h>
#include <math.h>

#define PI 3.141

#define SIZE 32
#define XDIM 32
#define YDIM 32
#define XMAX 31
#define YMAX 31
#define ZMAX 31
static float mat[ZMAX*XDIM*YDIM+YMAX*XDIM+XMAX];
static float step = SIZE;           //Increments 1/step


int main(void){
      FILE *f = fopen("dawg.raw","w");
      float v = 0.0;
      char c = 0;
      for(int i=0; i<SIZE; ++i){
	    for(int j=0; j<SIZE; ++j){
		  for(int k=0; k<SIZE; ++k, v+=1/8, c+=8){
			//v = sin (i*j*k*(PI/180));
			//mat[k*XDIM*YDIM+j*XDIM+i] = v;
			//v = 1;
			//v = ((j > (SIZE/2))&& (k > (SIZE / 2))) ? 1 : 0;
			char r = c-1;
			fwrite(&r, sizeof(char),1,f);
		  }
	    }
            v = 0.0;
      }
      /*
      for(int i=0;i<ZMAX*XDIM*YDIM+YMAX*XDIM+XMAX; ++i){
            fwrite(&mat[i], sizeof(float),1,f);
      }
      */
      fclose(f);
}

