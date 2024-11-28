//GAME FLAPPY BIRD 
#include<iostream>
#include<conio.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 30
#define GAP_SIZE 7
#define PIPE_DIF 45
using namespace std;
      //cout<<"+";

HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition; 
int duongong[3];
int vt_khoangcach[3];
int pipeFlag[3];
char bird[2][6]={'/','-','-','o','\\',' ',
                 '|','_','_','_',' ','>' };
int birdPos=6;
int Score=0;

void Gotoxy(int x, int y){ //vi tri 
	CursorPosition.X=x;
	CursorPosition.Y=y;
	SetConsoleCursorPosition(Console,CursorPosition);
}

void Setcursor(bool visible,DWORD size){ //cung cap 
	if(size==0)
	   size = 20;
	   
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(Console,&lpCursor);
}

void veduongvien(){ 
	for(int i=0; i<SCREEN_WIDTH; i++){ //chieu rong cua man hinh
		Gotoxy(i,0); 
		cout<<"\e[107m   \e[0m";
		Gotoxy(i,SCREEN_HEIGHT); //chieu cao cua man hinh
		cout<<"\e[107m   \e[0m"; 
	}
	
	for(int i=0; i<SCREEN_HEIGHT; i++){
		Gotoxy(0,i); 
		cout<<"\e[107m  \e[0m";
		Gotoxy(SCREEN_WIDTH,i); 
		cout<<"\e[107m  \e[0m";
	}
	for(int i=0; i<SCREEN_HEIGHT; i++){
		Gotoxy(WIN_WIDTH,i); 
		cout<<"\e[107m   \e[0m";
	}
	cout<<endl; 
}

void genPipe(int ind){
	vt_khoangcach[ind] = 3 + rand()%14; 
}

void drawPipe(int ind){
	if( pipeFlag[ind] == true ){
		for(int i=0; i<vt_khoangcach[ind]; i++){ 
			Gotoxy(WIN_WIDTH-duongong[ind],i+1); 
			cout<<"\e[102m   \e[0m"; 
		}
		for(int i=vt_khoangcach[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
			Gotoxy(WIN_WIDTH-duongong[ind],i+1); 
			cout<<"\e[102m   \e[0m"; 
		}
	}
	cout<<endl; 
}


void erasePipe(int ind){
	if( pipeFlag[ind] == true ){
		for(int i=0; i<vt_khoangcach[ind]; i++){ 
			Gotoxy(WIN_WIDTH-duongong[ind],i+1); 
			cout<<"   "; 
		}
		for(int i=vt_khoangcach[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
			Gotoxy(WIN_WIDTH-duongong[ind],i+1); 
			cout<<"   "; 
		}
	}
	cout<<endl;
}

void vebird(){
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			Gotoxy(j+2,i+birdPos);
			cout<<"\e[93m"<<bird[i][j];
		}
	}
	cout<<endl;
}

void xoabird(){
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
		    Gotoxy(j+2,i+birdPos); 
			cout<<"      ";
		}
	}
	cout<<endl; 
}

int vacham(){
	if( duongong[0] >= 61  ){
		if( birdPos<vt_khoangcach[0] || birdPos >vt_khoangcach[0]+GAP_SIZE ){
//			cout<< " HIT ";
//			getch();
			return 1;
		}
	}
	return 0;
}

void goerror(){
	//Gotoxy(SCREEN_WIDTH + 3, 4); cout<<"diem: "<<score[0]<<endl;
}
void capnhapdiem(){
	Gotoxy(WIN_WIDTH + 8, 5);cout<<"\e[93mDiem:\e[0m"<<Score<<endl;
}


void gameover(){
	system("cls");
	cout<<endl;
	Gotoxy(40,5); cout<<"\e[41m                                        \e[0m"<<endl;
	Gotoxy(40,6); cout<<"\e[41m \e[0m                                      \e[41m \e[0m"<<endl;
	Gotoxy(40,7); cout<<"\e[41m \e[0m              \e[5m\e[96mGAME OVER\e[25m               \e[41m \e[0m"<<endl;
	Gotoxy(40,8); cout<<"\e[41m \e[0m                                      \e[41m \e[0m"<<endl;
	Gotoxy(40,9); cout<<"\e[41m                                        \e[0m"<<endl;
	Gotoxy(36,11); cout<<"  \e[33m* Nhan phim bat ki de quay lai MENU chinh! * "<<endl<<endl;
	getch();
}

void huongdan(){
	system("cls");
	Gotoxy(40,5);  cout<<" \033[91m*------------------------------------------------*\033[0m "<<endl;
	Gotoxy(40,6);  cout<<" \033[91m|\033[0m              \e[5m \e[95mHuong dan cach choi\e[25m              \033[91m|\033[0m "<<endl;
	Gotoxy(40,7);  cout<<" \033[91m*------------------------------------------------*\033[0m  "<<endl;
	Gotoxy(40,8);  cout<<" \033[91m|      \e[93mNhan phim Spacebar de cho bird bay!\e[0m       \033[91m|\033[0m  "<<endl;
	Gotoxy(40,9);  cout<<" \033[91m|    \e[93mNhan phim bat ki de quay lai MENU chinh!\e[0m    \033[91m|\033[0m  "<<endl;
	Gotoxy(40,10); cout<<" \033[91m*------------------------------------------------*\033[0m  "<<endl;
	Gotoxy(40,12); cout<<"              \e[5mCHUC BAN CHOI VUI VE! ^^\e[25m            "<<endl;
	getch();
}

void play(){
	birdPos=6;
	Score=0;
	pipeFlag[0]=1;
	pipeFlag[1]=0;
	duongong[0]=pipeFlag[1]=4;
	
	system("cls");
	veduongvien();
	genPipe(0);
	capnhapdiem();
	
	Gotoxy(WIN_WIDTH + 3, 2);  cout<<"   \e[5m\e[96mFLAPPY BIRD\e[25m   ";
	Gotoxy(WIN_WIDTH + 3, 4);  cout<<"    \e[96m---------";
	Gotoxy(WIN_WIDTH + 3, 6);  cout<<"    \e[96m---------";
	Gotoxy(WIN_WIDTH + 3, 12); cout<<"   \e[2m\e[91mDieu khien\e[22m    ";
	Gotoxy(WIN_WIDTH + 3, 13); cout<<"     \e[96m------";
	Gotoxy(WIN_WIDTH + 3, 14); cout<<" \e[39mSpacebar = jump";
	Gotoxy(10, 5); cout<<" \e[5m\e[93mNhan phim bat ki de bat dau tro choi!\e[25m";
	getch();
	Gotoxy(10, 5); cout<<"                                            ";
	while(1){	 
		if(kbhit()){
			char ch = getch();
			if(ch==32){
				if( birdPos > 3 )
					birdPos-=3;
			} 
			if(ch==27){
				break;
			}
		}
		
		vebird();
		drawPipe(0);
		drawPipe(1);
		goerror();
		if( vacham () == 1 ){
			gameover();
			return;
		}
		
		Sleep(100); //t?c d? c?a bird khi bay 
		xoabird();
		erasePipe(0);
		erasePipe(1);
		birdPos += 1;
		
		if( birdPos > SCREEN_HEIGHT - 2 ){
			gameover();
			return;
		}
		
		if( pipeFlag[0] == 1 )
			duongong[0] += 2;
		
		if( pipeFlag[1] == 1 )
			duongong[1] += 2;
		
		if( duongong[0] >= 40 && duongong[0] < 42 ){
			pipeFlag[1] = 1;
			duongong[1] = 4;
			genPipe(1);
		}
		if( duongong[0] > 68 ){
			Score++;
			capnhapdiem();
			pipeFlag[1] = 0;
			duongong[0] = duongong[1];
			vt_khoangcach[0] = vt_khoangcach[1];
		}
		
	}
	 
}



int main(){
	Setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
   // play();
	do{
		system("cls");
		Gotoxy(40,5);  cout<<" \e[91m*-------------------------*\e[0m "; 
		Gotoxy(40,6);  cout<<" \e[91m|\e[0m   \e[5m \e[40;38;5;82mF l a p p y \e[30;48;5;82mB i r d\e[0m\e[25m  \e[91m|\e[0m"; 
		Gotoxy(40,7);  cout<<" \e[91m*-------------------------*\e[0m ";
		Gotoxy(40,8);  cout<<" \e[91m|\e[0m     \e[93m1. Bat dau Game\e[0m     \e[91m|\e[0m";
		Gotoxy(40,9);  cout<<" \e[91m|\e[0m     \e[93m2. Huong dan        \e[91m|\e[0m";	 
		Gotoxy(40,10); cout<<" \e[91m|\e[0m     \e[93m3. Thoat\e[0m            \e[91m|\e[0m";
		Gotoxy(40,11); cout<<" \e[91m|\e[0m     \e[96mSelect option:\e[0m      \e[91m|\e[0m";
		Gotoxy(40,12); cout<<" \e[91m*-------------------------*\e[0m ";
		char op = getche();
		if( op=='1') play();
		else if( op=='2') huongdan();
		else if( op=='3') exit(0);
		
	}while(1);
	return 0;
}
