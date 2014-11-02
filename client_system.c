#include "client_func.h"









void eventdisp(){
	// イベントの種類ごとに処理
	switch (event.type) {
		case SDL_QUIT:
			exit_p = 1; //終了フラグが立ったぞー
			break;

		if (event.type == SDL_KEYDOWN ){ 
			case SDL_KEYDOWN:// キーボードのキーが押された時
			switch(event.key.keysym.sym){

			case SDLK_RIGHT:
			LR = 1;
			break;
			case SDLK_LEFT:
			LR = -1;
			break;

			case SDLK_UP:
			UD = 1;
			break;
			case SDLK_DOWN:  
			UD = -1;
			break;

			case SDLK_SPACE: //スペースキーを押した時
			if(jumpflag == 0){
			jumpflag = 1;}
			jump_a = 14; //初速んんんんんんんんん
				
			break;

			case SDLK_ESCAPE:	// エスケープキー
				EXIT();
			break;
	
			default:
			break;        //それ以外のイベントは無視する
			}
		}

		else if (event.type == SDL_KEYUP){
		case SDL_KEYUP:// キーボードのキーが離された時
			switch(event.key.keysym.sym){
			case SDLK_RIGHT:
			case SDLK_LEFT:  //左右キーどちらかで
			LR = 0;
			case SDLK_UP:
			case SDLK_DOWN:  //上下キーどちらかで
			UD = 0;
			break;
			}
		}
	}
}


void keycont(void){

	Uint8 *key = SDL_GetKeyState(NULL);
	if(key[SDLK_RIGHT] == SDL_PRESSED){	//右移動
		P.x += 4; 
		if(jumpflag == 1)
			jump_LR = 1;
	}
	if(key[SDLK_LEFT] == SDL_PRESSED){	//左移動
		P.x -= 4; 
		if(jumpflag == 1)
			jump_LR = -1;
	}
	if(key[SDLK_UP] == SDL_PRESSED){	//上移動
		P.y -= 2;
		UD = 1; //←あとで消す
		jumpflag = 0; //←あとで消す
	}
	if(key[SDLK_DOWN] == SDL_PRESSED){	//下移動
		P.y += 4;
	}


/*その他詳細設定*/

	if(key[SDLK_RIGHT] != SDL_PRESSED && key[SDLK_LEFT] != SDL_PRESSED && jump_LR != 0)
		P.x += 4 * jump_LR; //空中なら静止しない

	if(jumpflag == 1 && jump_a > -8)	
		jump_a -= 1; //重力加速　

	if(jumpflag == 0){		
		jump_a = 0;	//ジャンプフラグないとき重力ない
		jump_LR = 0;//LR判定もない
	}

	if(jumpflag == 1)
	P.y -= jump_a;//加速度で移動(y軸なのでマイナス)

}





void EXIT(void){
int a = P.x;
int b = P.y;
P.x = 100;
P.y = 350;
PA.x = 0;
PA.y = 0;

titlep2 = 1;//ループ条件
	// 無限ループ
	while(titlep2){
		SDL_FillRect(window, NULL, 0x00808080);	// ウィンドウ背景初期化
		// イベントを取得したなら
		if(SDL_PollEvent(&event)){
			// イベントの種類ごとに処理
			switch (event.type) {
			case SDL_QUIT:
				exit_p = 1;
				titlep = 0;
				titlep2 = 0;
				break;
            case SDL_KEYDOWN:// キーボードのキーが押された時
                switch(event.key.keysym.sym){
				case SDLK_RIGHT:
					P.x += 300;
					if(P.x >= 700)
					P.x = 100;
					break;	
				case SDLK_LEFT:
					P.x -= 300;
					if(P.x <= 0)
					P.x = 400;
					break;

				case SDLK_RETURN: //エンターを押した時
					if(P.x == 400){
					exit_p = 1;
					titlep = 0;
					}
					titlep2 = 0;
					break;

				case SDLK_ESCAPE:	// エスケープキー
					exit_p = 1;
					titlep = 0;
					titlep2 = 0;
					break;
				}	
		}
	}

    /* メッセージ表示 */
    SDL_Rect srcRect = {0,0,0,0};
    SDL_Rect dstRect = {220,370};

for(fm=3; fm <= 4; fm++){
        srcRect.x = srcRect.y = 0;
        srcRect.w = gMessages[fm]->w;
        srcRect.h = gMessages[fm]->h;
 
        SDL_BlitSurface(gMessages[fm], &srcRect, SDL_GetVideoSurface(), &dstRect);
	dstRect.x += 300;
}

SDL_BlitSurface(usa, &PA, SDL_GetVideoSurface(), &P);
SDL_Flip(window);// 画面に図形を表示（反映）
	}

P.x = a;
P.y = b;

}


/*終了設定*/
void EXITsetting(){
    // フォントを閉じる 
	TTF_CloseFont(gTTF);  gTTF=NULL;
	TTF_CloseFont(sTTF);  gTTF=NULL;

	SDL_FillRect(window, NULL, 0xffffffff);	// ウィンドウ背景初期化
	SDL_Flip(window);// 画面に図形を表示（反映）
	SS();
}


/*サーバ移行予定地*/

void newpositionjadge(){

	if(P.x >= screensizex-100)
		P.x = screensizex-100;
	if(P.x <= 0)
		P.x = 0;//画面外に出ない

	if(P.y - jump_a > 640){
		jumpflag = 0;
		P.y = 640;//画面外に出ない あとで消す
	}
}

