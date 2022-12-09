/*
######################################## 
### Cuckoo search method
### CS method  
### programmed by nakazono. [2021/09/17] 
######################################## */

#include<stdio.h> 
#include<stdlib.h> 
#include<math.h>

#include "crane.h" 
#include "nn.h" 
#include "bat.h"

//normal random number
float rand_n(void)
{
    return sqrt(-2.0*log(drand48()))*cos(2.0*PI*drand48());
}

float sigma(float beta)
{
    float nume,denom;
    nume = tgamma(1.0+beta)*sin(PI*beta/2.0);
    denom = tgamma((1.0+beta)/2.0)*beta*pow(2.0,
    (beta-1.0)/2);
             return pow(nume/denom,1.0/beta);
}

//initial weights　　型が構造体　　initがNC１コ　rand_wが全体
INDIVIDUAL rand_w(void)
{
    int i,j,k;
    INDIVIDUAL init;

    for(j=0;j<J_MAX;j++){
        for(i=0;i<I_MAX;i++){

    init.whid[i][j]=(float)(drand48()*(2.0*XMAX)-XMAX);
                          }
                }
                for(k=0;k<K_MAX;k++){
                         for(j=0;j<J_MAX;j++){
    init.whid[i][k]=(float)(drand48()*(2.0*XMAX)-XMAX);
                          }
                }

                return init;
}

//selection(ranking method) kakkoのアルゴリズム
void sort(INDIVIDUAL kotai[IND_SIZE])
{
          int i,j,k,o,m;
          INDIVIDUAL tmp;

          for(o=0;o<IND_SIZE-1;o++){
              for(m=IND_SIZE-1;m>0;m--){
                  if(kotai[m-1].E>kotai[m].E){
                      tmp=kotai[m-1];
                      kotai[m-1]=kotai[m];
                      kotai[m]=tmp;
                  }
              }
          }
}

//levy flight
INDIVIDUAL levy_flight(INDIVIDUAL CS_r1,float alpha,float beta)
{
    int i,j,k;
    float u,v,s;
    INDIVIDUAL new_CS;
    alpha=ALPHA2;

    for(j=0;j<J_MAX;j++){
        for(i=0;i<I_MAX;i++){
            u = rand_n()*sigma(beta);
            v = rand_n();
            s = u / pow(fabs(v),1/beta);

new_CS.whid[i][j]=CS_r1.whid[i][j]+alpha*s;
        }
    }
    for(k=0;k<K_MAX;k++){
        for(j=0;j<J_MAX;j++){
            u = rand_n()*sigma(beta);
            v = rand_n();
            s = u / pow(fabs(v),1/beta);

new_CS.wout[j][k]=CS_r1.wout[j][k]+alpha*s;
        }
    }
    return new_CS;
}
//convert CS into NC weights
NEURON_w convert_weight(INDIVIDUAL CS)
{
    int i,j,k;
    NEURON_w NCw;
    for(j=0;j<J_MAX;j++)
             for(i=0;i<I_MAX;i++)
                       NCw.n_ij[i][j]=CS.whid[i][j];
    for(j=0;j<J_MAX;j++){
             for(k=0;k<K_MAX;k++){
                       NCw.n_jk[j][k]=CS.wout[j][k];
             }
    }
    return NCw;
}

INDIVIDUAL bat_algorithm(BAT NC1, BAT NC2, BAT best_NC, int generation, double aveLoud,float Pulse_r1)
{
	int i, j, k;
	// BAT new_NC1, new_NC2, tmp_NC;
	INDIVIDUAL new_bat
	
    //最良のコウモリ
	//NC1.freq=(Freq_Max-Freq_Min);
	NC1.freq=(Freq_Max-Freq_Min)*rand()/RAND_MAX;
	for(j=0;j<J;j++) {
		for(i=0;i<I;i++) {
			NC1.vji[j][i]+=(best_NC.pji[j][i]-NC1.pji[j][i])*NC1.freq;
			NC1.pji[j][i]+=NC1.vji[j][i];
			//NC1.freq=*(best_NC.freq);
			
		}
	}
	for(k=0;k<K;k++) {
		for(j=0;j<J;j++) {
			NC1.vkj[k][j]+=(best_NC.pkj[k][j]-NC1.pkj[k][j])*NC1.freq;
			NC1.pkj[k][j]+=NC1.vkj[k][j];
			//NC1.freq=(best_NC.freq);
		}
	}
	NC1=control_simulation(NC1);
	if(isnan(NC1.E)) {
		NC1.E=DBL_MAX;
	}
	
    //良いコウモリ
	//if(0.01> NC1.pulse) {
	if(rand()/RAND_MAX > NC1.pulse) {		
		new_NC1=init_NC1();
		new_NC1.loudness=Loud_0*pow(Loud_r,0.1*(double)generation);	
		new_NC1.pulse=Pulse_0*(1.0-exp(-Pulse_r*(double)Pulse_r1*(double)generation));
		for(j=0;j<J;j++) {
			for(i=0;i<I;i++) {
				new_NC1.pji[j][i]=NC2.pji[j][i]+(rand()/(RAND_MAX/2.0)-1)*aveLoud;
				new_NC1.vji[j][i]=NC2.vji[j][i];
				//new_NC1.freq=NC2.freq;
				//new_NC1.pulse=NC2.pulse;
				//new_NC1.loudness=(NC2.loudness);
			}
		}
		for(k=0;k<K;k++) {
			for(j=0;j<J;j++) {
				new_NC1.pkj[k][j]=NC2.pkj[k][j]+(rand()/(RAND_MAX/2.0)-1)*aveLoud;
				new_NC1.vji[k][j]=NC2.vji[k][j];
				//new_NC1.freq=NC2.freq;
				//new_NC1.pulse=NC2.pulse;
				//new_NC1.loudness=(NC2.loudness);
			}
		}
		new_NC1=control_simulation(new_NC1);
		if(isnan(new_NC1.E)) {
			new_NC1.E=DBL_MAX;
		}
	} else {
		new_NC1.E=DBL_MAX;
		new_NC1.Ey=DBL_MAX;
		new_NC1.Et=DBL_MAX;
	}
	new_NC2=init_NC1();
	new_NC2.loudness=Loud_0*pow(Loud_r,0.1*(double)generation);	
	new_NC2.pulse=Pulse_0*(1.0-exp(-Pulse_r*Pulse_r1*(double)generation));
	new_NC2=control_simulation(new_NC2);
	if(isnan(new_NC2.E)) {
		new_NC2.E=DBL_MAX;
	}
	
    //パルス率を更新
	if(((new_NC1.E<NC1.E) || (new_NC2.E<NC1.E)) && ((rand()/RAND_MAX)<NC1.loudness)) {
			if(new_NC1.E<new_NC2.E) {
				tmp_NC=NC1;
			NC1=new_NC1;
			new_NC1=tmp_NC;
		} else {
			tmp_NC=NC1;
			NC1=new_NC2;
			new_NC2=tmp_NC;
		}
		//NC1.pulse=Pulse_0*(1.0-exp(-Pulse_r*(double)generation));
		//NC1.loudness*=Loud_r;
	}
	return NC1;
}
