/* ########################################
   ### Rotary crane system 
   ### NC optimized by Cuckoo Search(CS) method.
   ### Evolution simulation in 1 trial.
   ### Compile: gcc -O2 -o crane-cs01 crane-cs01.c myfopen.c 
   crane_3dmodel.C neural_network.c cuckoo_search.c crane_control.c -lm
   ### programmed by nakazono. [2021/09/17]
   ######################################## */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "crane.h"
#include "nn.h"
#include "cuckoo.h"

//my file structure(myfopen.c)
extern FILE *myfopen(char *fname, char *mode);

//control simulation(crane_control.c)
extern float crane_control_simulation(NEURON_w NCw);
extern float crane_control_simulation_data(NEURON_w NCw);

//initial weights(cuckoo_search.c)
extern INDIVIDUAL rand_w(void);

// selection (ranking method)(cuckoo_search.c)
extern void sort(INDIVIDUAL kotai[]);

//levy flight(cuckoo_search.c)
extern INDIVIDUAL levy_flight(INDIVIDUAL CS_r1, float alpha, float beta);

// convert CS into NC weights(cuckoo_search.c)
extern NEURON_w convert_weight(INDIVIDUAL CS);

int main(void)
{
  FILE *fp1, *fpw;
  int seed, iteration, ind, i, j, k, r1, r2;
  float alpha=0.1, beta=1.5, weight;
  NEURON_w NCw;
  INDIVIDUAL CS, new_CS, tmp;

  fpw=myfopen("w-harmony.dat","r");

  // read connection weights
  for(j=0;j<J_MAX;j++)
            for(i=0;i<I_MAX;i++){
                fscanf(fpw, "%f¥n", &weight);
                HS.whid[i][j]=weight;
           }
  for(k=0;k<K_MAX;k++)
            for(j=0;j<J_MAX;j++){
                fscanf(fpw, "%f¥n", &weight);
                HS.whid[j][k]=weight;
           }
  // init weights
  NCw = convert_weight(HS);
  // Control start
  HS.E = crane_control_simulation_data(NCw);

  fclose(fpw);

  return 0;
} // end main