#include <stdio.h>
#include <SDL/SDL.h>       // SDLを用いるために必要なヘッダファイルをインクルード
#include <SDL/SDL_image.h>       // SDL_imageを用いるために必要なヘッダファイルをインクルード
#include <SDL/SDL_gfxPrimitives.h>	// gfxによる図形処理をするために必要なヘッダファイルをインクルード
#include <SDL/SDL_ttf.h>	// TrueTypeフォントを表示するために必要なヘッダファイルをインクルード
#include <SDL/SDL_opengl.h> // SDLでOpenGLを扱うために必要なヘッダファイルをインクルード
#include "client_func.h"

void DisplayStatus(void);
void checkhit(void);
void SS(void);//Start Stetas 初期化
void title(void);
void EXIT(void);
void story(void);
void result(void);
void setstart(void);

void eventdisp(void);
void keycont(void);
void exepaste(void);
void EXITsetting(void);

/*サーバ移行予定の関数*/
void newpositionjadge(void);


//SDL_Surface *window; // ウィンドウ（画像）データへのポインタ（グローバル）

//変数などの宣言(main外)

int screensizex = 1520; // max1535 / 60*60 25マス / 80*80 19マス 
int screensizey = 800;  // max846  / 60*60 14マス / 80*80 10マス

int time = 0;	//時間
int LR = 0;		//左右入力
int UD = 0;		//上下入力
int jumpflag = 0;	//
int jump_a = 0;	//
int jump_LR = 0;//
int LR_sift = 0;//
int newposx = 0, newposy = 0;	//新規位置　まだ実装できてない

int fm = 0;		//
int titlep = 1, titlep2 = 0;//
int exit_p = 0;	//


SDL_Rect PA = { 0, 0, 80, 100 }; //プレイヤーキャラ座標読み取り　あとで構造体化
SDL_Rect P = { 200, 640 };
SDL_Rect PMR = { 0, 0, 80, 100 }; 
SDL_Rect PM = { 0, 0 };//Player_Message(_Read) 1Pとかの表示 あとで構造体化

SDL_Event event; // SDLによるイベントを検知するための構造体
SDL_Event quit_event = {SDL_QUIT};	// 特定のイベント名を格納

SDL_Surface *usa;  // 画像データへのポインタ

//SDL_TimerID timer_id;	//タイマ割り込みを行うためのタイマのID


/* フォント関連 */

#define MSG_NUM 6           /* メッセージの数 */

SDL_Color black = {0x00, 0x00, 0x00};
SDL_Color Yellow = {0xff, 0xff, 0x00};
TTF_Font* gTTF;	// TrueTypeフォントデータへのポインタ
extern TTF_Font* sTTF;	
static char gFontFile[] = "images/APJapanesefontT.ttf";

static char gMsgStrings[ 100 ][ 100 ] = { "はじめる", "あそびかた", "おわる", "つづける", "おわる", "1P"};
SDL_Surface *gMessages[ 100 ];




// メイン関数 /////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

/*初期設定*/
setstart();

title();

	// 無限ループ
	while(1){

	SDL_FillRect(window, NULL, 0xffffffff);	// ウィンドウ背景初期化
	SDL_Delay(20);
	time++;

	// イベントを取得したら
	if(SDL_PollEvent(&event))
		eventdisp();	// イベント処理

	keycont();	/*キーボード操作*/

	newpositionjadge(); /*当たり判定　後でサーバに移行*/

	exepaste(); /*貼り付け設定 & 実行*/

	SDL_Flip(window);// 画面に図形を表示（反映）
	DisplayStatus();

	if(exit_p == 1)//終了フラグが立てばwhilebreak
	break;

    } //whileループ

/*終了設定*/
EXITsetting();
return 0;
} //main

//ステータス初期化
void SS(void){
P.x = 200;
P.y = 400;
PA.y = 0;
time = 0;

exit_p = 0;

titlep = 1;
titlep2 = 0;

}




	/*貼り付け順*/
//	pasteorder();

/*貼り付け順決定（y軸上から）*/
/*
int paste0 = 0 paste1 = 1, paste2 = 2, paste3 = 3;
int pasten = 0;

if(P[0].y > P[1].y){
pasten = paste0;
paste0 = paste1;
paste1 = pasten;
}
if(P[0].y > P[2].y){
pasten = paste0;
paste0 = paste2;
paste2 = pasten;
}
if(P[0].y > P[3].y){
pasten = paste0;
paste0 = paste3;
paste3 = pasten;
}
if(P[1].y > P[2].y){
pasten = paste1;
paste1 = paste2;
paste2 = paste1;
}
if(P[1].y > P[3].y){
pasten = paste1;
paste1 = paste3;
paste3 = paste1;
}
if(P[2].y > P[3].y){
pasten = paste2;
paste2 = paste3;
paste3 = paste2;
}
*/






