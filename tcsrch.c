#include <stdio.h>

/*
C言語学習用課題
コマンドラインを利用し、文字列oから指定文字列fを検索する
該当するものがあれば 検索文字列”xxx”が見つかりました
該当するものがなければ 検索文字列”xxx”が見つかりませんでした

想定コマンドライン : tcsrch -o "original" -f "matching chars"

エラーメッセージ
・引数が不正な場合
・その他

*/
int argerr(int cargc);				//エラーチェック
void errmsg(int p);					//エラーメッセージ表示
int srch(char* org, char* match);	//検索

int Strlength(const char* s);		//文字列の長さを調べる


int main(int argc, char *argv[]){
	int chk = argerr(argc);			//引数エラーの検出 errに結果を代入

	if (chk == 0) {
		chk = srch(argv[2], argv[4]);		//検索
	}
	errmsg(chk);
	return 0;
}


//検索
int srch(char* org, char* match){
	/*
	方針:1文字目を探す→全一致かどうか確認する
	*/
	int orglength = Strlength(org);
	int matchlength = Strlength(match);
	int scm = orglength - matchlength + 1; //サーチ回数
	int srchresult = 0;				//発見回数
	
//	printf("%s:%d\n", org, orglength);
//	printf("%s:%d\n", match, matchlength);
	
	if (scm <= 0) {
		return 2;					//検索文字列が対象文字列より長い
	}
	
	int i;	int j;
	for(i = 0; i < scm; i++){		
		if (org[i] == match[0]) {
			
			for(j = 0; j < matchlength; j++){	//1文字目の一致
				if (org[i+j] != match[j]) {
					break;			//ハズレ
				}
				if ((org[i+j] == match[j]) & (j == matchlength - 1)) {
					srchresult++;	//発見
					break;
				}
//				printf("m%d", j);
			}
		}
//		printf("s%d\n", i);
	}

	if (srchresult >= 1){
		printf("文字列\"%s\"が%d件見つかりました。\n", match, srchresult);
	}else{
		printf("文字列は見つかりませんでした。\n");
	}

	return 0;
}


//文字列の長さを調べる
int Strlength(const char* s){
	int n = 0;
	
	while (*s != '\0'){
		s++; n++;
	}
	return (n);
}


//エラー
int argerr(int cargc){
	if (cargc != 5) {
		return 1;					//引数の数が5でない場合エラーコード:1
	}
	return 0;
}


//エラーメッセージ
void errmsg(int chk){
	switch (chk){
	  case 0:
		break;
	  case 1:
		printf("引数が不正です。\n");
		break;
	  case 2:
		printf("検索文字列が探索文字列より長いです。\n");
		break;
	  default:
		printf("不正なエラーです。\n");
		break;
	}
}