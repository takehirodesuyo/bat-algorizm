#define ITERATION 10
#define ABA_RATE 0.1      
#define IND_SIZE 100    
#define ALPHA2 0.1        
#define BETA2 1.5         
#define XMAX 1.0
#define J 8
#define I 3
#define K 1
#define mM 1300
#define IM 1600
#define l_f 1.05
#define l_r 1.48
#define K_f 35000.0
#define K_r 40000.0
#define V0 (36/3.6)
#define h 0.01
#define P 100
// #define Tm 12
#define G 3000
#define RATE 20
#define Math_PI 3.14/180
// #define R 5.0
// //*円軌道の半径*//

#define Freq_Min 0.0
#define Freq_Max 1.0
#define Loud_0 1.0
#define Loud_01 1,0
#define Loud_r 0.9
#define Pulse_0 0.5
#define Pulse_r 1.0
#define Best_rate 0.1
// #define aveLoud 0.0
// #define Pulse_r1 0.9

// individual of cuckoo(NC)　INDIVIDUALという名前の構造体ここに必要な値変数を描く
// 入力層中間層出力層があって　入力層に重みをかけて中間層に行く　中間層に出力層に重みをかけて処理をする
// 一連の流れがクレーンの制御となる　重みの評価を考える
// ニューラルネットワークの重みの組み合わせ
typedef struct{ 
	double pji[J][I],pkj[K][J];		// 評価重み　入力-中間 中間-出力
	double vji[J][I],vkj[K][J];		// 速度　入力-中間 中間-出力
	double freq;				// 周波数
	double pulse;				// パルス率
	double loudness;			// 音量
    // float whid[I_MAX][J_MAX]; //中間層重み
    // float wout[J_MAX][K_MAX]; //出力層重み
    // double E, Ey, Et;			// 評価値
    float E; //最終の評価値
}INDIVIDUAL;
