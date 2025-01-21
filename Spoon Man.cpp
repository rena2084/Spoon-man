//Score = (10000/(Bomb*5+NumberOfMoves)+DestroyedWalls*500+EnemiesKilled*1000)
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include "colors.h"
#include "parameters.h"

using namespace std;

struct Player{
    string Name;
    string Difficulty;
    int Score = 0;
}PlayerData,Temp;

int X_P;
int Y_P;
int X_TNT;
int Y_TNT;
int NumberOfMoves = 0;
int Bomb = 0;
int DestroyedWalls = 0;
int EnemiesKilled = 0;
int MoveAfterPlacementTNT = 0;
char DiagonalLine = 92;
bool Health = true;
bool TNTPlacement = false;


vector<int> InDWallsX;
vector<int> InDWallsY;
vector<int> DWallsX;
vector<int> DWallsY;
vector<int> EnemysX;
vector<int> EnemysY;
vector<Player> Players;
vector<Player> Players_Easy;
vector<Player> Players_Normal;
vector<Player> Players_Hard;


//------- BasicFunctions -------
int MainFunction();
void gotoxy(int x, int y);
void HideCursor();
void ClearTheProgramMemory();
void MoveUpPlayer();
void MoveDownPlayer();
void LeftMovePlayer();
void RightMovePlayer();
bool ReadObjectUp();
bool ReadObjectDown();
bool ReadObjectLeft();
bool ReadObjectRight();
//----------- Design -----------
void TextColor(int x);
void Border();
void TitleMenu();
void BoxMenu(int x, int y);
void MainMenu();
char DifficultyMenu();
void BorderGetName();
void BorderGameOver();
void TitleGameOver();
void GameOverMenu();
void BorderWinner();
void TitleWinner();
void WinnerMenu();
void BorderRecords();
void TextRecords();
void BorderHowToPlay();
void TextHowToPlay();
void Explosion();
void IntroAnimation();
void SplashScreen();
//----------- Object -----------
void Player();
void Enemy(int x, int y);
void DeadEnemy(int x, int y);
void DWall(int x, int y);
void DestroyedWall(int x, int y);
void InDWall(int x, int y);
void TNT(int x, int y);
void EndGame();
void Clear(int x, int y);
//------------ Easy ------------
void GameScreen_Easy();
void ColumnEasy();
void RowEasy();
void RandDWallEasy();
void StartGameEasy();
void RunningGameEasy();
void RandEnemyEasy();
//----------- Normal -----------
void GameScreen_Normal();
void ColumnNormal();
void RowNormal();
void RandDWallNormal();
void StartGameNormal();
void RunningGameNormal();
void RandEnemyNormal();
//------------ Hard ------------
void GameScreen_Hard();
void ColumnHard();
void RowHard();
void RandDWallHard();
void StartGameHard();
void RunningGameHard();
void RandEnemyHard();


int main(){
    HideCursor();
    IntroAnimation();
    while(true){
        int Ans = MainFunction();
        if(Ans==1){
            int MainFunction();
        }else{
            TextColor(Default_Color);
            gotoxy(0,27);
            exit(0);
        }
    }

    return 0;
}
int MainFunction(){
    char UserResponse;
    srand(time(0));
    ClearTheProgramMemory();
    system("cls");
    Border();
    TitleMenu();
    MainMenu();

    char a;
    char b;
    while(true){
        a = _getch();
        if(a>'0' && a<'5'){
            break;
        }
    }

    if(a=='1'){
        system("cls");
        Border();
        TitleMenu();
        b = DifficultyMenu();
        //------------ Easy ------------
        if(b=='1'){
            NumberOfMoves = 0;
            Bomb = false;
            system("cls");
            PlayerData.Difficulty = "Easy";
            BorderGetName();
            cin>> PlayerData.Name;


            //------ Start Game ------
            StartGameEasy();
            gotoxy(Xe,Ye);
            Player();
            RandDWallEasy();
            RandEnemyEasy();
            RunningGameEasy();



        //----------- Normal -----------
        }else if(b=='2'){
            NumberOfMoves = 0;
            system("cls");
            PlayerData.Difficulty = "Normal";
            BorderGetName();
            cin>> PlayerData.Name;


            //------ Start Game ------
            StartGameNormal();
            gotoxy(Xsm,Ysm);
            Player();
            RandDWallNormal();
            RandEnemyNormal();
            RunningGameNormal();



        //------------ Hard ------------
        }else if(b=='3'){
            NumberOfMoves = 0;
            system("cls");
            PlayerData.Difficulty = "Hard";
            BorderGetName();
            cin>> PlayerData.Name;


            //------ Start Game ------
            StartGameHard();
            gotoxy(Xsh,Ysh);
            Player();
            RandDWallHard();
            RandEnemyHard();
            RunningGameHard();



        }else{
            return 1;
        }
    }else if(a=='2'){
        char Answer;
        system("cls");
        BorderRecords();
        TextRecords();
        while(true){
            Answer = _getch();
            if(Answer=='B' || Answer=='b'){
                break;
            }
        }
        return 1;
    }else if(a=='3'){
        char Answer;
        system("cls");
        BorderHowToPlay();
        TextHowToPlay();
        while(true){
            Answer = _getch();
            if(Answer=='B' || Answer=='b'){
                break;
            }
        }
        return 1;
    }else{
        gotoxy(0,27);
        return 0;
    }
    while(true){
        UserResponse = _getch();
        if(UserResponse=='M' || UserResponse=='m' || UserResponse=='E' || UserResponse=='e'){
            break;
        }
    }
    if(UserResponse=='M' || UserResponse=='m'){
        return 1;
    }else{
        return 0;
    }

}


//-------------------------- Gotoxy --------------------------

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//------------------------ TextColor -------------------------

void TextColor(int x){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

//------------------------ Hidecursor ------------------------

void HideCursor(){
    HANDLE hStdOut = NULL;
    CONSOLE_CURSOR_INFO curInfo;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &curInfo);
}


//------------------ ClearTheProgramMemory -------------------

void ClearTheProgramMemory(){
    X_TNT = 0;
    Y_TNT = 0;
    NumberOfMoves = 0;
    Bomb = 0;
    DestroyedWalls = 0;
    EnemiesKilled = 0;
    MoveAfterPlacementTNT = 0;
    Health = true;
    TNTPlacement = false;
    DWallsX.clear();
    DWallsY.clear();
    InDWallsX.clear();
    InDWallsY.clear();
    EnemysX.clear();
    EnemysY.clear();
    Players.clear();
    Players_Easy.clear();
    Players_Normal.clear();
    Players_Hard.clear();
}

//------------------------ ColumnEasy ------------------------

void ColumnEasy(){
    cout<<"|     ||     ||     ||     ||     ||     ||     |";
}

//------------------------- RowEasy --------------------------

void RowEasy(){
    cout<<" -----  -----  -----  -----  -----  -----  ----- ";
}

//----------------------- ColumnNormal -----------------------

void ColumnNormal(){
    cout<<"|     ||     ||     ||     ||     ||     ||     ||     ||     |";
}

//------------------------ RowNormal -------------------------

void RowNormal(){
    cout<<" -----  -----  -----  -----  -----  -----  -----  -----  ----- ";
}

//------------------------ ColumnHard ------------------------

void ColumnHard(){
    cout<<"|     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     |";
}

//------------------------- RowHard --------------------------

void RowHard(){
    cout<<" -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  ----- ";
}


//-------------------------- Border --------------------------

void Border(){
    TextColor(Border_Color);
    for(int i=0; i<27; i++){
        gotoxy(3*i,0);
        cout<<"=#=";
    }
    for(int i=0; i<27; i++){
        gotoxy(3*i,26);
        cout<<"=#=";
    }

    for(int i=0; i<27; i++){
        gotoxy(0,i);
        cout<<'*';
    }
    for(int i=0; i<27; i++){
        gotoxy(80,i);
        cout<<'*';
    }
}

//------------------------ TitleMenu ------------------------

void TitleMenu(){
    TextColor(TitleMenu_Color);
    Sleep(150);
    gotoxy(8,1);
    cout<<" _______";
    Sleep(150);
    gotoxy(8,2);
    cout<<"|     __|.-----..-----..-----..-----.    .--------..---.-..-----.";
    Sleep(150);
    gotoxy(8,3);
    cout<<"|__     ||  _  ||  _  ||  _  ||     |    |        ||  _  ||     |";
    Sleep(150);
    gotoxy(8,4);
    cout<<"|_______||   __||_____||_____||__|__|    |__|__|__||___._||__|__|";
    Sleep(150);
    gotoxy(8,5);
    cout<<"         |__|";
    Sleep(150);
}

//------------------------- BoxMenu --------------------------

void BoxMenu(int x, int y){
    TextColor(BoxMenu_Color);
    gotoxy(x,y);
    for(int i=0; i<21; i++){
        gotoxy(x+i,y);
        cout<<'_';
    }
    for(int i=0; i<3; i++){
        gotoxy(x-1,y+1+i);
        cout<<'|';
        gotoxy(x+1+20,y+1+i);
        cout<<'|';
    }
    for(int i=0; i<21; i++){
        gotoxy(x+i,y+3);
        cout<<'_';
    }
}

//------------------------ MainMenu ------------------------

void MainMenu(){
    TextColor(MainMenu_Color);
    gotoxy(40,7);
    for(int i=0; i<13; i++){
        gotoxy(40+i,7);
        cout<<'_';
        gotoxy(40-i,7);
        cout<<'_';
        Sleep(10);
    }
    Sleep(50);
    for(int i=0; i<17; i++){
        gotoxy(27,8+i);
        cout<<'|';
        gotoxy(53,8+i);
        cout<<'|';
        Sleep(10);
    }
    Sleep(50);
    for(int i=0; i<13; i++){
        gotoxy(28+i,24);
        cout<<'_';
        gotoxy(52-i,24);
        cout<<'_';
        Sleep(10);
    }

    BoxMenu(30,8);
    gotoxy(35,10);
    TextColor(7);
    cout<<"1-Start Game";
    Sleep(200);

    BoxMenu(30,12);
    gotoxy(36,14);
    TextColor(7);
    cout<<"2-Records";
    Sleep(200);

    BoxMenu(30,16);
    gotoxy(34,18);
    TextColor(7);
    cout<<"3-How to play";
    Sleep(200);

    BoxMenu(30,20);
    gotoxy(37,22);
    TextColor(7);
    cout<<"4-Exit";
    Sleep(200);
}

//---------------------- DifficultyMenu ----------------------

char DifficultyMenu(){
    gotoxy(30,8);
    cout<<"Game Difficulty Level";

    for(int i=0; i<13; i++){
        gotoxy(40+i,9);
        cout<<'_';
        gotoxy(40-i,9);
        cout<<'_';
        Sleep(10);
    }
    Sleep(50);
    for(int i=0; i<13; i++){
        gotoxy(27,10+i);
        cout<<'|';
        gotoxy(53,10+i);
        cout<<'|';
        Sleep(10);
    }
    Sleep(50);
    for(int i=0; i<13; i++){
        gotoxy(28+i,22);
        cout<<'_';
        gotoxy(52-i,22);
        cout<<'_';
        Sleep(10);
    }

    BoxMenu(30,10);
    gotoxy(37,12);
    TextColor(7);
    cout<<"1-Easy";
    Sleep(200);

    BoxMenu(30,14);
    gotoxy(36,16);
    TextColor(7);
    cout<<"2-Normal";
    Sleep(200);

    BoxMenu(30,18);
    gotoxy(37,20);
    TextColor(7);
    cout<<"3-Hard";
    Sleep(200);

    gotoxy(6,23);
    TextColor(TextBack_Color);
    cout<<"Back(B)";

    char a;
    while(true){
        a = _getch();
        if(a>'0' && a<'4' || a=='B' || a=='b'){
            return a;
        }
    }
}

//---------------------- BorderGameOver ----------------------

void BorderGameOver(){
    TextColor(BorderGameOver_Color);
    for(int i=0; i<23; i++){
        gotoxy(40+i,7);
        cout<<'_';
        gotoxy(40-i,7);
        cout<<'_';
    }
    for(int i=0; i<17; i++){
        gotoxy(17,8+i);
        cout<<'|';
        gotoxy(63,8+i);
        cout<<'|';
    }
    for(int i=0; i<23; i++){
        gotoxy(18+i,24);
        cout<<'_';
        gotoxy(62-i,24);
        cout<<'_';
    }
}

//---------------------- TitleGameOver -----------------------

void TitleGameOver(){
    TextColor(TitleGameOver_Color);
    Sleep(500);
    gotoxy(24,8);
    cout<<" _______";
    gotoxy(24,9);
    cout<<"|     __|.---.-..--------..-----.";
    gotoxy(24,10);
    cout<<"|    |  ||  _  ||        ||  -__|";
    gotoxy(24,11);
    cout<<"|_______||___._||__|__|__||_____|";
    gotoxy(24,12);
    cout<< endl;
    Sleep(500);
    gotoxy(24,13);
    cout<<"   _______";
    gotoxy(24,14);
    cout<<"  |       |.--.--..-----..----.";
    gotoxy(24,15);
    cout<<"  |   -   ||  |  ||  -__||   _|";
    gotoxy(24,16);
    cout<<"  |_______| "<<DiagonalLine<<"___/ |_____||__|  ";
    Sleep(500);

}

//----------------------- GameOverMenu -----------------------

void GameOverMenu(){
    ofstream pout("Players_Data.txt", ios::app);
    PlayerData.Score = (10000/(Bomb*5+NumberOfMoves)+DestroyedWalls*500+EnemiesKilled*1000);
    pout<< PlayerData.Name <<" "<< PlayerData.Difficulty <<" "<< PlayerData.Score << endl;
    pout.close();
    system("cls");
    Border();
    TitleMenu();
    BorderGameOver();
    TitleGameOver();
    gotoxy(20,18);
    cout<<"Player Name: "<<PlayerData.Name;
    gotoxy(20,19);
    cout<<"Difficulty: "<<PlayerData.Difficulty;
    gotoxy(20,20);
    cout<<"Score: "<<PlayerData.Score;
    gotoxy(20,22);
    cout<<"Press the 'M' key to go to the main menu...";
    gotoxy(20,23);
    cout<<"Press the 'E' key to Exit this game...";
}

//----------------------- BorderWinner -----------------------

void BorderWinner(){
    TextColor(BorderWinner_Color);
    for(int i=0; i<23; i++){
        gotoxy(40+i,7);
        cout<<'_';
        gotoxy(40-i,7);
        cout<<'_';
    }
    for(int i=0; i<17; i++){
        gotoxy(17,8+i);
        cout<<'|';
        gotoxy(63,8+i);
        cout<<'|';
    }
    for(int i=0; i<23; i++){
        gotoxy(18+i,24);
        cout<<'_';
        gotoxy(62-i,24);
        cout<<'_';
    }
}

//----------------------- TitleWinner ------------------------

void TitleWinner(){
    TextColor(TitleWinner_Color);
    Sleep(500);
    gotoxy(20,9);
    cout<<" ________  __";
    gotoxy(20,10);
    cout<<"|  |  |  ||__|.-----..-----..-----..----.";
    gotoxy(20,11);
    cout<<"|  |  |  ||  ||     ||     ||  -__||   _|";
    gotoxy(20,12);
    cout<<"|________||__||__|__||__|__||_____||__|  ";
    Sleep(500);
}

//------------------------ WinnerMenu ------------------------

void WinnerMenu(){
    ofstream pout("Players_Data.txt", ios::app);
    PlayerData.Score = 10000/(Bomb*5+NumberOfMoves)+DestroyedWalls*500+EnemiesKilled*1000+10000;
    pout<< PlayerData.Name <<" "<< PlayerData.Difficulty <<" "<< PlayerData.Score << endl;
    pout.close();
    system("cls");
    Border();
    TitleMenu();
    BorderWinner();
    TitleWinner();
    gotoxy(20,15);
    cout<<"Player Name: "<<PlayerData.Name;
    gotoxy(20,16);
    cout<<"Difficulty: "<<PlayerData.Difficulty;
    gotoxy(20,17);
    cout<<"Score: "<<PlayerData.Score;
    gotoxy(20,22);
    cout<<"Press the 'M' key to go to the main menu...";
    gotoxy(20,23);
    cout<<"Press the 'E' key to Exit this game...";
}

//---------------------- BorderGetName -----------------------

void BorderGetName(){
    Border();
    TitleMenu();
    gotoxy(35,8);
    cout<<"Player Name";

    for(int i=0; i<33; i++){
        gotoxy(24+i,10);
        cout<<'_';
        gotoxy(24+i,13);
        cout<<'_';

    }
    for(int i=0; i<3; i++){
        gotoxy(23,11+i);
        cout<<'|';
        gotoxy(57,11+i);
        cout<<'|';

    }
    Sleep(200);
    string GetName = "Enter your name: ";
    for(int i=0; i<GetName.size(); i++){
        gotoxy(25+i,12);
        cout<< GetName[i];
        Sleep(10);
    }
}

//--------------------- BorderHowToPlay ----------------------

void BorderHowToPlay(){
    TextColor(BorderHowToPlay_Color);
    Border();
    TitleMenu();
    for(int i=0; i<37; i++){
        gotoxy(40+i,6);
        cout<<'_';
        gotoxy(40-i,6);
        cout<<'_';
        Sleep(10);
    }
    Sleep(50);
    for(int i=0; i<18; i++){
        gotoxy(3,7+i);
        cout<<'|';
        gotoxy(77,7+i);
        cout<<'|';
        Sleep(10);
    }
    Sleep(50);
    for(int i=0; i<37; i++){
        gotoxy(4+i,24);
        cout<<'_';
        gotoxy(76-i,24);
        cout<<'_';
        Sleep(10);
    }
}

//------------------------ HowToPlay -------------------------

void TextHowToPlay(){
    TextColor(TextHowToPlay_Color);
    gotoxy(6,8);
    Player();
    TextColor(TextHowToPlay_Color);
    cout<<" : Player(You)";
    Enemy(6,9);
    TextColor(TextHowToPlay_Color);
    cout<<" : Enemy => If you crash into an enemy, you will be game over!";
    InDWall(6,10);
    TextColor(TextHowToPlay_Color);
    cout<<" : Indestructable wall => These walls are impossible to destroy,";
    TextColor(TextHowToPlay_Color);
    gotoxy(6,11);
    cout<<"        not even with TNT!";
    DWall(6,12);
    TextColor(TextHowToPlay_Color);
    cout<<" : Box => These boxes can be destroyed with TNT.";
    TNT(6,13);
    TextColor(TextHowToPlay_Color);
    cout<<" : TNT => TNT can be used to destroy boxes and kill enemies.";
    gotoxy(6,14);
    TextColor(White_Color);
    cout<<" Tip1";
    TextColor(TextHowToPlay_Color);
    cout<<" : TNT will explode after two moves!";
    gotoxy(6,15);
    TextColor(White_Color);
    cout<<" Tip2";
    TextColor(TextHowToPlay_Color);
    cout<<" : Be very careful when working with TNT! Beecause if you are";
    gotoxy(6,16);
    cout<<"        one block away from TNT, you will be gam over.";
    gotoxy(6,17);
    EndGame();
    TextColor(TextHowToPlay_Color);
    cout<<" : Destination => This is the block you need to reach.";

    gotoxy(6,19);
    TextColor(White_Color);
    cout<<"How to play:";
    TextColor(TextHowToPlay_Color);
    gotoxy(6,20);
    cout<<"1. Move whith the 'W','S','A','D' keys.";
    gotoxy(6,21);
    cout<<"2. Place TNT eith the 'Space' key.";


    TextColor(White_Color);
    gotoxy(6,22);
    cout<<"tip";
    TextColor(TextHowToPlay_Color);
    cout<<" : You should try to reach the end block with the  minimum";
    gotoxy(6,23);
    cout<<"number of moves and minimum use of TNT to get a higher score.";
    gotoxy(69,23);
    TextColor(TextBack_Color);
    cout<<"Back(B)";
}

//---------------------- BorderRecords -----------------------

void BorderRecords(){
    TextColor(BorderRecords_Color);
    Border();
    TitleMenu();
    for(int i=0; i<37; i++){
        gotoxy(40+i,6);
        cout<<'_';
        gotoxy(40-i,6);
        cout<<'_';
        Sleep(10);
    }
    Sleep(50);
    for(int i=0; i<18; i++){
        gotoxy(3,7+i);
        cout<<'|';
        gotoxy(77,7+i);
        cout<<'|';
        Sleep(10);
    }
    Sleep(50);
    for(int i=0; i<37; i++){
        gotoxy(4+i,24);
        cout<<'_';
        gotoxy(76-i,24);
        cout<<'_';
        Sleep(10);
    }
     Sleep(50);
    for(int i=0; i<18; i++){
        gotoxy(28,7+i);
        cout<<'*';
        gotoxy(52,7+i);
        cout<<'*';
        Sleep(10);
    }
}

//----------------------- TextRecords ------------------------

void TextRecords(){
    int score;
    string name;
    string difficulty;
    ifstream pin("Players_Data.txt", ios::in);

    while(!pin.eof()){
        pin>>name;
        pin>>difficulty;
        pin>>score;
        Players.push_back({name, difficulty, score});
    }

    for(int j=0; j<Players.size()-1; j++){
        if(Players[j].Difficulty=="Easy"){
            name = Players[j].Name;
            difficulty = Players[j].Difficulty;
            score = Players[j].Score;
            Players_Easy.push_back({name, difficulty, score});
        }else if(Players[j].Difficulty=="Normal"){
            name = Players[j].Name;
            difficulty = Players[j].Difficulty;
            score = Players[j].Score;
            Players_Normal.push_back({name, difficulty, score});
        }else if(Players[j].Difficulty=="Hard"){
            name = Players[j].Name;
            difficulty = Players[j].Difficulty;
            score = Players[j].Score;
            Players_Hard.push_back({name, difficulty, score});
        }
    }
    for(int j=0; j<Players_Easy.size(); j++){
        for(int k=j+1; k<Players_Easy.size(); k++){
            if(Players_Easy[j].Score<Players_Easy[k].Score){
                Temp.Name = Players_Easy[j].Name;
                Temp.Difficulty = Players_Easy[j].Difficulty;
                Temp.Score = Players_Easy[j].Score;

                Players_Easy[j].Name = Players_Easy[k].Name;
                Players_Easy[j].Difficulty = Players_Easy[k].Difficulty;
                Players_Easy[j].Score = Players_Easy[k].Score;

                Players_Easy[k].Name = Temp.Name;
                Players_Easy[k].Difficulty = Temp.Difficulty;
                Players_Easy[k].Score = Temp.Score;
            }
        }
    }


    for(int j=0; j<Players_Normal.size(); j++){
        for(int k=j+1; k<Players_Normal.size(); k++){
            if(Players_Normal[j].Score<Players_Normal[k].Score){
                Temp.Name = Players_Normal[j].Name;
                Temp.Difficulty = Players_Normal[j].Difficulty;
                Temp.Score = Players_Normal[j].Score;

                Players_Normal[j].Name = Players_Normal[k].Name;
                Players_Normal[j].Difficulty = Players_Normal[k].Difficulty;
                Players_Normal[j].Score = Players_Normal[k].Score;

                Players_Normal[k].Name = Temp.Name;
                Players_Normal[k].Difficulty = Temp.Difficulty;
                Players_Normal[k].Score = Temp.Score;
            }
        }
    }


    for(int j=0; j<Players_Hard.size(); j++){
        for(int k=j+1; k<Players_Hard.size(); k++){
            if(Players_Hard[j].Score<Players_Hard[k].Score){
                Temp.Name = Players_Hard[j].Name;
                Temp.Difficulty = Players_Hard[j].Difficulty;
                Temp.Score = Players_Hard[j].Score;

                Players_Hard[j].Name = Players_Hard[k].Name;
                Players_Hard[j].Difficulty = Players_Hard[k].Difficulty;
                Players_Hard[j].Score = Players_Hard[k].Score;

                Players_Hard[k].Name = Temp.Name;
                Players_Hard[k].Difficulty = Temp.Difficulty;
                Players_Hard[k].Score = Temp.Score;
            }
        }
    }

    Sleep(200);
    gotoxy(13,8);
    TextColor(Easy_Color);
    cout<<"Easy";
    gotoxy(37,8);
    TextColor(Normal_Color);
    cout<<"Normal";
    gotoxy(62,8);
    TextColor(Hard_Color);
    cout<<"Hard";
    Sleep(200);
    gotoxy(5,9);
    TextColor(White_Color);
    cout<<"Name";
    gotoxy(22,9);
    cout<<"Score";
    gotoxy(30,9);
    cout<<"Name";
    gotoxy(46,9);
    cout<<"Score";
    gotoxy(54,9);
    cout<<"Name";
    gotoxy(71,9);
    cout<<"Score";
    Sleep(200);


    TextColor(TextRecords_Color);
    for(int j=0; j<10; j++){
        gotoxy(5,11+j);
        if(j<Players_Easy.size()){
            cout<<Players_Easy[j].Name;
        }
        gotoxy(22,11+j);
        if(j<Players_Easy.size()){
            cout<<Players_Easy[j].Score;
        }
        gotoxy(30,11+j);
        if(j<Players_Normal.size()){
            cout<<Players_Normal[j].Name;
        }
        gotoxy(46,11+j);
        if(j<Players_Normal.size()){
            cout<<Players_Normal[j].Score;
        }
        gotoxy(54,11+j);
        if(j<Players_Hard.size()){
            cout<<Players_Hard[j].Name;
        }
        gotoxy(71,11+j);
        if(j<Players_Hard.size()){
            cout<<Players_Hard[j].Score;
        }
    }
    TextColor(TextRecords_Color);
    gotoxy(12,21);
    cout<<"Highest";
    gotoxy(12,22);
    cout<<"scores";
    gotoxy(37,21);
    cout<<"Highest";
    gotoxy(37,22);
    cout<<"scores";
    gotoxy(61,21);
    cout<<"Highest";
    gotoxy(61,22);
    cout<<"scores";
    TextColor(TextBack_Color);
    gotoxy(6,23);
    cout<<"Back(B)";

    pin.close();
}

//------------------------ MovePlayer ------------------------

void MoveUpPlayer(){
    gotoxy(X_P,Y_P);
    cout<<"     ";
    if(TNTPlacement == true && MoveAfterPlacementTNT==1){
        TNT(X_P,Y_P);
        Bomb++;
    }
    Y_P -= 2;
    gotoxy(X_P,Y_P);
    Player();
}
void MoveDownPlayer(){
    gotoxy(X_P,Y_P);
    cout<<"     ";
    if(TNTPlacement == true && MoveAfterPlacementTNT==1){
        TNT(X_P,Y_P);
        Bomb++;
    }
    Y_P += 2;
    gotoxy(X_P,Y_P);
    Player();
}
void RightMovePlayer(){
    gotoxy(X_P,Y_P);
    cout<<"     ";
    if(TNTPlacement == true && MoveAfterPlacementTNT==1){
        TNT(X_P,Y_P);
        Bomb++;
    }
    X_P += 7;
    gotoxy(X_P,Y_P);
    Player();
}
void LeftMovePlayer(){
    gotoxy(X_P,Y_P);
    cout<<"     ";
    if(TNTPlacement == true && MoveAfterPlacementTNT==1){
        TNT(X_P,Y_P);
        Bomb++;
    }
    X_P -= 7;
    gotoxy(X_P,Y_P);
    Player();
}

//------------------------- ObjectUp -------------------------

bool ReadObjectUp(){
    int j=0;
    for(int i=0; i<InDWallsY.size(); i++){
        if(InDWallsX[i]==X_P && InDWallsY[i]==Y_P-2){
            j++;
        }
    }
    for(int i=0; i<DWallsY.size(); i++){
        if(DWallsX[i]==X_P && DWallsY[i]==Y_P-2){
            j++;
        }
    }
    if(j==0){
        return true;
    }
    return false;
}

//------------------------ ObjectDown ------------------------

bool ReadObjectDown(){
    int j=0;
    for(int i=0; i<InDWallsY.size(); i++){
        if(InDWallsX[i]==X_P && InDWallsY[i]==Y_P+2){
            j++;
        }
    }
    for(int i=0; i<DWallsY.size(); i++){
        if(DWallsX[i]==X_P && DWallsY[i]==Y_P+2){
            j++;
        }
    }
    if(j==0){
        return true;
    }
    return false;
}

//------------------------ ObjectLeft ------------------------

bool ReadObjectLeft(){
    int j=0;
    for(int i=0; i<InDWallsX.size(); i++){
        if(InDWallsX[i]==X_P-7 && InDWallsY[i]==Y_P ){
            j++;
        }
    }
    for(int i=0; i<DWallsX.size(); i++){
        if(DWallsX[i]==X_P-7 && DWallsY[i]==Y_P ){
            j++;
        }
    }
    if(j==0){
        return true;
    }
    return false;
}


//----------------------- ReadObjectRight ------------------------

bool ReadObjectRight(){
    int j=0;
    for(int i=0; i<InDWallsX.size(); i++){
        if(InDWallsX[i]==X_P+7 && InDWallsY[i]==Y_P ){
            j++;
        }
    }
    for(int i=0; i<DWallsX.size(); i++){
        if(DWallsX[i]==X_P+7 && DWallsY[i]==Y_P ){
            j++;
        }
    }
    if(j==0){
        return true;
    }
    return false;
}

//------------------------ Explosion -------------------------

void Explosion(){
    Clear(X_TNT, Y_TNT);
    for(int i=0; i<DWallsX.size(); i++){
        if(X_TNT==DWallsX[i] && Y_TNT-2==DWallsY[i] ||
           X_TNT==DWallsX[i] && Y_TNT+2==DWallsY[i] ||
           X_TNT-7==DWallsX[i] && Y_TNT==DWallsY[i] ||
           X_TNT+7==DWallsX[i] && Y_TNT==DWallsY[i])
        {
            DestroyedWall(DWallsX[i], DWallsY[i]);
            Sleep(200);
            Clear(DWallsX[i], DWallsY[i]);
            DWallsX.erase(DWallsX.begin() + i);
            DWallsY.erase(DWallsY.begin() + i);
            DestroyedWalls++;
        }
    }
    for(int i=0; i<EnemysX.size(); i++){
        if(X_TNT==EnemysX[i] && Y_TNT-2==EnemysY[i] ||
           X_TNT==EnemysX[i] && Y_TNT+2==EnemysY[i] ||
           X_TNT-7==EnemysX[i] && Y_TNT==EnemysY[i] ||
           X_TNT+7==EnemysX[i] && Y_TNT==EnemysY[i])
        {
            DeadEnemy(EnemysX[i], EnemysY[i]);
            Sleep(200);
            Clear(EnemysX[i], EnemysY[i]);
            EnemysX.erase(EnemysX.begin() + i);
            EnemysY.erase(EnemysY.begin() + i);
            EnemiesKilled++;
        }
    }
    if(X_TNT==X_P && Y_TNT==Y_P ||
           X_TNT==X_P && Y_TNT-2==Y_P ||
           X_TNT==X_P && Y_TNT+2==Y_P ||
           X_TNT-7==X_P && Y_TNT==Y_P ||
           X_TNT+7==X_P && Y_TNT==Y_P)
    {
       Health = false;
    }
}

//---------------------- IntroAnimation ----------------------

void IntroAnimation(){
    Border();
    for(int i=1; i<26; i++){
        gotoxy(36,i);
        cout<<"|";
        TextColor(196);
        cout<<"       ";
        TextColor(8);
        cout<<"|";
        if(i>1){
            gotoxy(36,i-1);
            cout<<"|";
            TextColor(252);
            cout<<"  TNT  ";
            TextColor(8);
            cout<<"|";
        }
        if(i>2){
            gotoxy(36,i-2);
            cout<<"|";
            TextColor(196);
            cout<<"       ";
            TextColor(8);
            cout<<"|";
        }
        if(i>3){
            gotoxy(36,i-3);
            cout<<" _______ ";
            gotoxy(40,i-3);
            TextColor(7);
            cout<<"|";
        }
        if(i>4){
            gotoxy(36,i-4);
            TextColor(7);
            cout<<"    |    ";
        }
        if(i>5){
            gotoxy(36,i-5);
            cout<<"         ";
        }
        Sleep(50);
    }
    gotoxy(40,21);
    TextColor(14);
    cout<<"*";
    Sleep(200);
    gotoxy(40,21);
    TextColor(12);
    cout<<"#";
    Sleep(200);
    gotoxy(40,21);
    TextColor(14);
    cout<<"*";
    Sleep(200);
    gotoxy(40,21);
    TextColor(12);
    cout<<"#";
    Sleep(200);
    gotoxy(40,21);
    TextColor(8);
    cout<<"|";
    gotoxy(40,22);
    TextColor(14);
    cout<<"*";
    Sleep(200);
    gotoxy(40,22);
    TextColor(12);
    cout<<"#";
    Sleep(200);
    gotoxy(40,22);
    TextColor(14);
    cout<<"*";
    Sleep(200);
    gotoxy(40,22);
    TextColor(12);
    cout<<"#";
    Sleep(200);
    gotoxy(40,22);
    TextColor(8);
    cout<<"|";


    gotoxy(36,21);
    cout<<"         ";
    gotoxy(36,22);
    cout<<"         ";
    gotoxy(36,23);
    cout<<"         ";
    gotoxy(36,24);
    cout<<"         ";
    gotoxy(36,25);
    cout<<"         ";
    /*
    for(int i=0; i<27; i++){
        for(int j=0; j<81; j++){
            gotoxy(j,i);
            TextColor(255);
            cout<<" ";
        }
    }
    */
    system("cls");
    system("color F2");
    Sleep(500);
    system("color 07");
    SplashScreen();
}

//----------------------- SplashScreen -----------------------

void SplashScreen(){
    Border();
    Sleep(500);
    gotoxy(22,8);
    cout<<" _______";
    gotoxy(22,9);
    cout<<"|     __|.-----..-----..-----..-----.";
    gotoxy(22,10);
    cout<<"|__     ||  _  ||  _  ||  _  ||     |";
    gotoxy(22,11);
    cout<<"|_______||   __||_____||_____||__|__|";
    gotoxy(22,12);
    cout<<"         |__|";
    Sleep(500);
    gotoxy(28,14);
    cout<<".--------..---.-..-----.";
    gotoxy(28,15);
    cout<<"|        ||  _  ||     |";
    gotoxy(28,16);
    cout<<"|__|__|__||___._||__|__|";
    Sleep(2000);
}

//------------------------------------------------------------- Object -------------------------------------------------------------

//-------------------------- Player --------------------------

void Player(){
    TextColor(Player_Color);
    cout<<"(^-^)";
}

//-------------------------- Enemy ---------------------------

void Enemy(int x, int y){
    EnemysX.push_back(x);
    EnemysY.push_back(y);
    gotoxy(x,y);
    TextColor(Enemy_Color);
    cout<<"(@_@)";
}

//------------------------ DeadEnemy -------------------------

void DeadEnemy(int x, int y){
    gotoxy(x,y);
    TextColor(DeadEnemy_Color);
    cout<<"(#_#)";
}

//-------------------------- DWall ---------------------------

void DWall(int x, int y){
    DWallsX.push_back(x);
    DWallsY.push_back(y);
    gotoxy(x,y);
    TextColor(DWall_Color);
    cout<<"[BOX]";
}

//----------------------- DestroyedWall ----------------------

void DestroyedWall(int x, int y){
    gotoxy(x,y);
    TextColor(DestroyedWall_Color);
    cout<<"[box]";
}

//------------------------- InDWall --------------------------

void InDWall(int x, int y){
    InDWallsX.push_back(x);
    InDWallsY.push_back(y);
    gotoxy(x,y);
    TextColor(InDWall_Color);
    cout<<"[xXx]";
}

//--------------------------- TNT ---------------------------

void TNT(int x, int y){
    X_TNT = x;
    Y_TNT = y;
    gotoxy(x, y);
    TextColor(TNT_Color);
    cout<<"[TNT]";
}

//------------------------- EndGame -------------------------

void EndGame(){
    TextColor(EndBlock_Color);
    cout<<"[END]";
}

void Clear(int x, int y){
    Default_Color;
    gotoxy(x, y);
    cout<<"     ";
}

//-------------------------------------------------------------- Easy --------------------------------------------------------------

//--------------------- GameScreen_Easy ----------------------

void GameScreen_Easy(){
    TextColor(GameScreen_Color);
    gotoxy(2,1);
    cout<<"Player Name: "<<PlayerData.Name;
    gotoxy(63,1);
    cout<<"Difficulty: "<<PlayerData.Difficulty;
    gotoxy(16,6);
    RowEasy();
    for(int i=7; i<21; i++){
        gotoxy(16,i);
        ColumnEasy();
        i++;
        gotoxy(16,i);
        RowEasy();
    }
}

//---------------------- RandDWallEasy -----------------------

void RandDWallEasy(){
    for(int i=0; i<NumberBoxEasy;){
        int x = Xe + (7*(rand() % 7));
        int y = Ye + (2*(rand() % 7));

        int j = 0;
        for(int i=0; i<InDWallsX.size(); i++){
            if(x==InDWallsX[i] && y==InDWallsY[i]){
                j++;
            }
        }
        for(int i=0; i<DWallsX.size(); i++){
            if(x==DWallsX[i] && y==DWallsY[i]){
                j++;
            }
        }
        if(x==Xe && y==Ye || x==Xe && y==Ye+2 || x==Xe+7 && y==Ye){
            j++;
        }
        if(x==EndGameXe && y==EndGameYe){
            j++;
        }
        if(j==0){
            DWall(x,y);
            i++;
        }
    }
}

//---------------------- RandEnemyEasy -----------------------

void RandEnemyEasy(){
    for(int i=0; i<NumberEnemyEasy;){
        int x = Xe + (7*(rand() % 7));
        int y = Ye + (2*(rand() % 7));

        int j = 0;
        for(int i=0; i<InDWallsX.size(); i++){
            if(x==InDWallsX[i] && y==InDWallsY[i]){
                j++;
            }
        }
        for(int i=0; i<DWallsX.size(); i++){
            if(x==DWallsX[i] && y==DWallsY[i]){
                j++;
            }
        }
        for(int i=0; i<EnemysX.size(); i++){
            if(x==EnemysX[i] && y==EnemysY[i]){
                j++;
            }
        }
        if(x==Xe && y==Ye || x==Xe && y==Ye+2 || x==Xe+7 && y==Ye){
            j++;
        }
        if(x==EndGameXe && y==EndGameYe){
            j++;
        }
        if(j==0){
            Enemy(x,y);
            i++;
        }
    }
}

//---------------------- StartGameEasy -----------------------

void StartGameEasy(){
    NumberOfMoves = 0;
    system("cls");
    GameScreen_Easy();
    Border();
    gotoxy(EndGameXe,EndGameYe);
    EndGame();
    InDWall(Xe+7,Ye+2);
    InDWall(Xe+7,Ye+6);
    InDWall(Xe+7,Ye+10);
    InDWall(Xe+21,Ye+2);
    InDWall(Xe+21,Ye+6);
    InDWall(Xe+21,Ye+10);
    InDWall(Xe+35,Ye+2);
    InDWall(Xe+35,Ye+6);
    InDWall(Xe+35,Ye+10);
}

//--------------------- RunningGameEasy ----------------------

void RunningGameEasy(){
    int j = 0;
    char Player_Move;
    X_P = Xe;
    Y_P = Ye;
    while(true){
        if(X_TNT!=0 && Y_TNT!=0 && MoveAfterPlacementTNT==3){
            Explosion();
            TNTPlacement = false;
        }
        if(Health==false){
            break;
        }
        while(true){
            Player_Move = _getch();
            if(
                Player_Move==' ' &&
                TNTPlacement == false ||
                Player_Move=='w' && Y_P!=Ye && ReadObjectUp() ||
                Player_Move=='s' && Y_P!=EndGameYe && ReadObjectDown() ||
                Player_Move=='a' && X_P!=Xe && ReadObjectLeft() ||
                Player_Move=='d' && X_P!=EndGameXe && ReadObjectRight() ||
                Player_Move=='W' && Y_P!=Ye && ReadObjectUp() ||
                Player_Move=='S' && Y_P!=EndGameYe && ReadObjectDown() ||
                Player_Move=='A' && X_P!=Xe && ReadObjectLeft() ||
                Player_Move=='D' && X_P!=EndGameXe && ReadObjectRight())
            {
                break;
            }
        }
        if(Player_Move==' '){
            MoveAfterPlacementTNT = 0;
            TNTPlacement = true;
        }else if(Player_Move=='W' || Player_Move=='w'){
            MoveUpPlayer();
        }else if(Player_Move=='S' || Player_Move=='s'){
            MoveDownPlayer();
        }else if(Player_Move=='A' || Player_Move=='a'){
            LeftMovePlayer();
        }else if(Player_Move=='D' || Player_Move=='d'){
            RightMovePlayer();
        }
        for(int i=0; i<EnemysX.size(); i++){
            if(X_P==EnemysX[i] && Y_P==EnemysY[i]){
                j++;
            }
        }
        if(j>0){
            Health = false;
        }
        if(X_P==EndGameXe && Y_P==EndGameYe){
            break;
        }
        MoveAfterPlacementTNT++;
        NumberOfMoves++;
    }
    if(Health==false){
        GameOverMenu();
    }else{
        WinnerMenu();
    }
}

//------------------------------------------------------------- Normal -------------------------------------------------------------

//-------------------- GameScreen_Normal ---------------------

void GameScreen_Normal(){
    TextColor(GameScreen_Color);
    gotoxy(2,1);
    cout<<"Player Name: "<<PlayerData.Name;
    gotoxy(61,1);
    cout<<"Difficulty: "<<PlayerData.Difficulty;
    gotoxy(9,4);
    RowNormal();
    for(int i=5; i<23; i++){
        gotoxy(9,i);
        ColumnNormal();
        i++;
        gotoxy(9,i);
        RowNormal();
    }
}

//--------------------- RandDWallNormal ----------------------

void RandDWallNormal(){
    for(int i=0; i<NumberBoxNormal;){
        int x = Xm + (7*(rand() % 9));
        int y = Ym + (2*(rand() % 9));

        int j = 0;
        for(int i=0; i<InDWallsX.size(); i++){
            if(x==InDWallsX[i] && y==InDWallsY[i]){
                j++;
            }
        }
        for(int i=0; i<DWallsX.size(); i++){
            if(x==DWallsX[i] && y==DWallsY[i]){
                j++;
            }
        }
        if(x==Xsm && y==Ysm || x==Xsm && y==Ysm+2 || x==Xsm+7 && y==Ysm || x==Xsm-7 && y==Ysm){
            j++;
        }
        if(x==EndGameXm && y==EndGameYm){
            j++;
        }
        if(j==0){
            DWall(x,y);
            i++;
        }
    }
}

//--------------------- RandEnemyNormal ----------------------

void RandEnemyNormal(){
    for(int i=0; i<NumberEnemyNormal;){
        int x = Xm + (7*(rand() % 9));
        int y = Ym + (2*(rand() % 9));

        int j = 0;
        for(int i=0; i<InDWallsX.size(); i++){
            if(x==InDWallsX[i] && y==InDWallsY[i]){
                j++;
            }
        }
        for(int i=0; i<DWallsX.size(); i++){
            if(x==DWallsX[i] && y==DWallsY[i]){
                j++;
            }
        }
        for(int i=0; i<EnemysX.size(); i++){
            if(x==EnemysX[i] && y==EnemysY[i]){
                j++;
            }
        }
        if(x==Xsm && y==Ysm || x==Xsm && y==Ysm+2 || x==Xsm+7 && y==Ysm){
            j++;
        }
        if(x==EndGameXm && y==EndGameYm){
            j++;
        }
        if(j==0){
            Enemy(x,y);
            i++;
        }
    }
}

//--------------------- StartGameNormal ----------------------

void StartGameNormal(){
    NumberOfMoves = 0;
    system("cls");
    GameScreen_Normal();
    Border();
    gotoxy(EndGameXm,EndGameYm);
    EndGame();

    InDWall(Xm,Ym+2);
    InDWall(Xm+7,Ym+2);
    InDWall(Xm+14,Ym+2);
    InDWall(Xm+21,Ym+2);
    InDWall(Xm+35,Ym+2);
    InDWall(Xm+42,Ym+2);
    InDWall(Xm+49,Ym+2);
    InDWall(Xm+56,Ym+2);

    InDWall(Xm+7,Ym+6);
    InDWall(Xm+14,Ym+6);
    InDWall(Xm+21,Ym+6);
    InDWall(Xm+28,Ym+6);
    InDWall(Xm+35,Ym+6);
    InDWall(Xm+42,Ym+6);
    InDWall(Xm+49,Ym+6);

    InDWall(Xm,Ym+10);
    InDWall(Xm+7,Ym+10);
    InDWall(Xm+14,Ym+10);
    InDWall(Xm+21,Ym+10);
    InDWall(Xm+35,Ym+10);
    InDWall(Xm+42,Ym+10);
    InDWall(Xm+49,Ym+10);
    InDWall(Xm+56,Ym+10);

    InDWall(Xm+7,Ym+14);
    InDWall(Xm+14,Ym+14);
    InDWall(Xm+21,Ym+14);
    InDWall(Xm+28,Ym+14);
    InDWall(Xm+35,Ym+14);
    InDWall(Xm+42,Ym+14);
    InDWall(Xm+49,Ym+14);

}

//-------------------- RunningGameNormal ---------------------

void RunningGameNormal(){
    int j = 0;
    char Player_Move;
    X_P = Xsm;
    Y_P = Ysm;
    while(true){
        if(X_TNT!=0 && Y_TNT!=0 && MoveAfterPlacementTNT==3){
            Explosion();
            TNTPlacement = false;
        }
        if(Health==false){
            break;
        }
        while(true){
            Player_Move = _getch();
            if(
                Player_Move==' ' &&
                TNTPlacement == false ||
                Player_Move=='w' && Y_P!=Ym && ReadObjectUp() ||
                Player_Move=='s' && Y_P!=EndGameYm && ReadObjectDown() ||
                Player_Move=='a' && X_P!=Xm && ReadObjectLeft() ||
                Player_Move=='d' && X_P!=EndGameXm+28 && ReadObjectRight() ||
                Player_Move=='W' && Y_P!=Ym && ReadObjectUp() ||
                Player_Move=='S' && Y_P!=EndGameYm && ReadObjectDown() ||
                Player_Move=='A' && X_P!=Xm && ReadObjectLeft() ||
                Player_Move=='D' && X_P!=EndGameXm+28 && ReadObjectRight())
            {
                break;
            }
        }
        if(Player_Move==' '){
            MoveAfterPlacementTNT = 0;
            TNTPlacement = true;
        }else if(Player_Move=='W' || Player_Move=='w'){
            MoveUpPlayer();
        }else if(Player_Move=='S' || Player_Move=='s'){
            MoveDownPlayer();
        }else if(Player_Move=='A' || Player_Move=='a'){
            LeftMovePlayer();
        }else if(Player_Move=='D' || Player_Move=='d'){
            RightMovePlayer();
        }
        for(int i=0; i<EnemysX.size(); i++){
            if(X_P==EnemysX[i] && Y_P==EnemysY[i]){
                j++;
            }
        }
        if(j>0){
            Health = false;
        }
        if(X_P==EndGameXm && Y_P==EndGameYm){
            break;
        }
        MoveAfterPlacementTNT++;
        NumberOfMoves++;
    }
    if(Health==false){
        GameOverMenu();
    }else{
        WinnerMenu();
    }
}

//-------------------------------------------------------------- Hard --------------------------------------------------------------

//--------------------- GameScreen_Hard ----------------------

void GameScreen_Hard(){
    TextColor(GameScreen_Color);
    gotoxy(2,1);
    cout<<"Player Name: "<<PlayerData.Name;
    gotoxy(63,1);
    cout<<"Difficulty: "<<PlayerData.Difficulty;
    gotoxy(2,2);
    RowHard();
    for(int i=3; i<25; i++){
        gotoxy(2,i);
        ColumnHard();
        i++;
        gotoxy(2,i);
        RowHard();
    }
}

//---------------------- RandDWallHard -----------------------

void RandDWallHard(){
    for(int i=0; i<NumberBoxHard;){
        int x = Xh + (7*(rand() % 11));
        int y = Yh + (2*(rand() % 11));

        int j = 0;
        for(int i=0; i<InDWallsX.size(); i++){
            if(x==InDWallsX[i] && y==InDWallsY[i]){
                j++;
            }
        }
        for(int i=0; i<DWallsX.size(); i++){
            if(x==DWallsX[i] && y==DWallsY[i]){
                j++;
            }
        }
        if(x==Xsh && y==Ysh || x==Xsh && y==Ysh+2 || x==Xsh && y==Ysh+4 || x==Xsh-7 && y==Ysh+4  || x==Xsh+7 && y==Ysh+4){
            j++;
        }
        if(x==EndGameXh && y==EndGameYh){
            j++;
        }
        if(j==0){
            DWall(x,y);
            i++;
        }
    }
}

//---------------------- RandEnemyHard -----------------------

void RandEnemyHard(){
    for(int i=0; i<NumberEnemyHard;){
        int x = Xh + (7*(rand() % 11));
        int y = Yh + (2*(rand() % 11));

        int j = 0;
        for(int i=0; i<InDWallsX.size(); i++){
            if(x==InDWallsX[i] && y==InDWallsY[i]){
                j++;
            }
        }
        for(int i=0; i<DWallsX.size(); i++){
            if(x==DWallsX[i] && y==DWallsY[i]){
                j++;
            }
        }
        for(int i=0; i<EnemysX.size(); i++){
            if(x==EnemysX[i] && y==EnemysY[i]){
                j++;
            }
        }
        if(x==Xsh && y==Ysh || x==Xsh && y==Ysh+2 || x==Xsh && y==Ysh+4 || x==Xsh-7 && y==Ysh+4  || x==Xsh+7 && y==Ysh+4){
            j++;
        }
        if(x==EndGameXh && y==EndGameYh){
            j++;
        }
        if(j==0){
            Enemy(x,y);
            i++;
        }
    }
}

//---------------------- StartGameHard -----------------------

void StartGameHard(){
    NumberOfMoves = 0;
    system("cls");
    GameScreen_Hard();
    Border();
    gotoxy(EndGameXh,EndGameYh);
    EndGame();

    InDWall(Xh,Yh);
    InDWall(Xh+7,Yh);
    InDWall(Xh+14,Yh);
    InDWall(Xh+21,Yh);
    InDWall(Xh+28,Yh);
    InDWall(Xh+35,Yh);
    InDWall(Xh+42,Yh);
    InDWall(Xh+49,Yh);
    InDWall(Xh+56,Yh);
    InDWall(Xh+63,Yh);
    InDWall(Xh+70,Yh);

    InDWall(Xh,Yh+2);
    InDWall(Xh+70,Yh+2);

    InDWall(Xh,Yh+4);
    InDWall(Xh+14,Yh+4);
    InDWall(Xh+21,Yh+4);
    InDWall(Xh+28,Yh+4);
    InDWall(Xh+42,Yh+4);
    InDWall(Xh+49,Yh+4);
    InDWall(Xh+56,Yh+4);
    InDWall(Xh+70,Yh+4);

    InDWall(Xh,Yh+6);
    InDWall(Xh+14,Yh+6);
    InDWall(Xh+56,Yh+6);
    InDWall(Xh+70,Yh+6);

    InDWall(Xh,Yh+8);
    InDWall(Xh+14,Yh+8);
    InDWall(Xh+28,Yh+8);
    InDWall(Xh+35,Yh+8);
    InDWall(Xh+42,Yh+8);
    InDWall(Xh+56,Yh+8);
    InDWall(Xh+70,Yh+8);

    InDWall(Xh,Yh+10);
    InDWall(Xh+14,Yh+10);
    InDWall(Xh+28,Yh+10);
    InDWall(Xh+42,Yh+10);
    InDWall(Xh+56,Yh+10);
    InDWall(Xh+70,Yh+10);

    InDWall(Xh,Yh+12);
    InDWall(Xh+14,Yh+12);
    InDWall(Xh+28,Yh+12);
    InDWall(Xh+42,Yh+12);
    InDWall(Xh+56,Yh+12);
    InDWall(Xh+70,Yh+12);

    InDWall(Xh,Yh+14);
    InDWall(Xh+14,Yh+14);
    InDWall(Xh+56,Yh+14);
    InDWall(Xh+70,Yh+14);

    InDWall(Xh,Yh+16);
    InDWall(Xh+14,Yh+16);
    InDWall(Xh+21,Yh+16);
    InDWall(Xh+28,Yh+16);
    InDWall(Xh+35,Yh+16);
    InDWall(Xh+42,Yh+16);
    InDWall(Xh+49,Yh+16);
    InDWall(Xh+56,Yh+16);
    InDWall(Xh+70,Yh+16);

    InDWall(Xh,Yh+18);
    InDWall(Xh+70,Yh+18);

    InDWall(Xh,Yh+20);
    InDWall(Xh+7,Yh+20);
    InDWall(Xh+14,Yh+20);
    InDWall(Xh+21,Yh+20);
    InDWall(Xh+28,Yh+20);
    InDWall(Xh+42,Yh+20);
    InDWall(Xh+49,Yh+20);
    InDWall(Xh+56,Yh+20);
    InDWall(Xh+63,Yh+20);
    InDWall(Xh+70,Yh+20);
}

//--------------------- RunningGameHrad ----------------------

void RunningGameHard(){
    int j = 0;
    char Player_Move;
    X_P = Xsh;
    Y_P = Ysh;
    while(true){
        if(X_TNT!=0 && Y_TNT!=0 && MoveAfterPlacementTNT==3){
            Explosion();
            TNTPlacement = false;
        }
        if(Health==false){
            break;
        }
        while(true){
            Player_Move = _getch();
            if(
                Player_Move==' ' &&
                TNTPlacement == false ||
                Player_Move=='w' && Y_P!=Yh && ReadObjectUp() ||
                Player_Move=='s' && Y_P!=EndGameYh && ReadObjectDown() ||
                Player_Move=='a' && X_P!=Xh && ReadObjectLeft() ||
                Player_Move=='d' && X_P!=EndGameXh+35 && ReadObjectRight() ||
                Player_Move=='W' && Y_P!=Yh && ReadObjectUp() ||
                Player_Move=='S' && Y_P!=EndGameYh && ReadObjectDown() ||
                Player_Move=='A' && X_P!=Xh && ReadObjectLeft() ||
                Player_Move=='D' && X_P!=EndGameXh+35 && ReadObjectRight())
            {
                break;
            }
        }
        if(Player_Move==' '){
            MoveAfterPlacementTNT = 0;
            TNTPlacement = true;
        }else if(Player_Move=='W' || Player_Move=='w'){
            MoveUpPlayer();
        }else if(Player_Move=='S' || Player_Move=='s'){
            MoveDownPlayer();
        }else if(Player_Move=='A' || Player_Move=='a'){
            LeftMovePlayer();
        }else if(Player_Move=='D' || Player_Move=='d'){
            RightMovePlayer();
        }
        for(int i=0; i<EnemysX.size(); i++){
            if(X_P==EnemysX[i] && Y_P==EnemysY[i]){
                j++;
            }
        }
        if(j>0){
            Health = false;
        }
        if(X_P==EndGameXh && Y_P==EndGameYh){
            break;
        }
        MoveAfterPlacementTNT++;
        NumberOfMoves++;
    }
    if(Health==false){
        GameOverMenu();
    }else{
        WinnerMenu();
    }
}
