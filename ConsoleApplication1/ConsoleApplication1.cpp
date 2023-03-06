#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
using namespace std;
//--------player behave--------//
struct player { bool lose = false; int score = 0; int hight_score = 0; string name; int heart = 0; };
player player1;

class draw
{
protected:
    //--------setup attributes--------//
    int width, hight;
    int tail, tailx[200] = {}, taily[200] = {};
    int fruitx, fruity;
    int headx;
    int heady;
    char c;
   
public:

    //-------move the head step 1 -------//
    enum direction { start = 0, top, down, left, right };
    direction dir = start;
    char previous;
    void setup_move() {
        if (_kbhit()) {
            c = _getch();
            if (c == 'w') { if (previous != 's' && previous != 'w') { dir = top; }previous = 'w'; }
            if (c == 's') { if (previous != 'w' && previous != 's') { dir = down; }previous = 's'; }
            if (c == 'd') { if (previous != 'a' && previous != 'd') { dir = right; }previous = 'd'; }
            if (c == 'a') { if (previous != 'd' && previous != 'a') { dir = left; }previous = 'a'; }
            if (c == 'x') { headx = width / 2; heady = hight / 2; tail = 0; player1.score = 0; player1.lose = true; }
        }

    }

    void move2() {
        //-------move the head step 2 -------//
        setup_move();
        switch (dir) {
        case start: break;
        case top:heady--; break;
        case down:heady++; break;
        case right:headx++; break;
        case left:headx--; break;
        }
    }
    //------The End Massege------//
    ~draw()
    {
        system("cls");
        cout << " \n\n\n\n\              Thanks For Playing Mr." << player1.name << " * _ * " << endl;
    }
    //------Tp stop the head------//
    void stop_move()
    {
        dir = start;
        previous = 'v';
    }
    
    void fun_call() {
        //------funcion call------//
        drawer();
        shift(tailx, tail);
        shift(taily, tail);
        tailx[0] = headx;
        taily[0] = heady;
        setup_move();
        move2();
        hit();
        high_score();
        

    }
    //------player name------//
    void set_name()
    {
        cout << "Enter your name :";
        cin >> player1.name;
    }
    draw()
    {
        //--------init attributes--------//
        width = 80, hight = 20;
        tail = 0;
        fruitx = 0, fruity = 0;
        headx = width / 2;
        heady = hight / 2;
        c = 'c';
        previous = 'v';
    }
    //------ pure virtual funcions------//
    virtual void drawer() = 0;
    virtual void hit() = 0;
    virtual void high_score() = 0;
    //----------rand the fruite--------//
    void randfruite() {
        srand(time(0));
        fruitx = rand() % (width - 3) + 2;
        fruity = rand() % (hight - 3) + 2;
    }
    
    //--------shift function : to print the tail--------//
    void shift(int arr[], int size)
    {
        for (int i = size - 2; i >= 0; i--)arr[i + 1] = arr[i];
    }
};
class draw1 :public draw
{
public:

    void high_score()
    {
        ifstream h_score("hight_score1.txt");   //read 
        h_score >> player1.hight_score;
        if (player1.score > player1.hight_score)
            player1.hight_score = player1.score;
        ofstream H_score("Hight_score1.txt");     // write 
        H_score << player1.hight_score;

    }


    //------draw funcion-------//
    void drawer() {
        system("cls");
        bool test_fruit_tail = false;
        cout << "player name: " << player1.name;
        cout << "         player score : " << player1.score;
        cout << "         Hight Score : " << player1.hight_score;
        cout << "         your heart : " << player1.heart;
        cout << "         Press X to exit the map.";
        cout << "\n\n\n";
        //---------check if fruit draw on the tail-------//
        for (int z = 0; z < tail; z++) { if (fruity == taily[z] && fruitx == tailx[z])test_fruit_tail = true; }
        //------draw map------//
        for (int i = 1; i <= hight; i++) {
            cout << "                   ";
            for (int j = 1; j <= width; j++) {
                if (i == 1 || i == hight || j == 1 || j == width)cout << "*";
                //--------draw snake head------//
                else if (i == heady && j == headx)cout << "0";
                //---------draw fruit--------//
                else if (!test_fruit_tail)if (i == fruity && j == fruitx) { cout << '$'; }
                //--------draw tail-------//
                 else{
                    bool printed_o = false;
                    for (int z = 0; z < tail; z++) {
                        if (j == tailx[z] && i == taily[z]) { cout << "o"; printed_o = true; }
                    }
                    if (!printed_o) { cout << " "; }
                }
            }cout << endl;
        }


    }
    

    
    void hit() {

        //----------the tail hit-----------//
        for (int r = 0; r < tail; r++) { if (headx == tailx[r] && heady == taily[r]) { headx = width / 2; heady = hight / 2; tail = 0; player1.score = 0; player1.lose = true; } }
        //----------the wall hit-----------//
        if (headx <= 1) { headx = width - 1; }
        else if (headx > width - 1)headx = 1;
        if (heady <= 1) heady = hight - 1;
        else if (heady > hight - 1) { heady = 1; }
        //----------if eat fruit-----------//
        if (headx == fruitx && heady == fruity) { player1.score++; randfruite(); tail++; }
       
    }

};
class draw2 :public draw
{
public:
    void high_score()
    {
        ifstream h_score("hight_score2.txt");
        h_score >> player1.hight_score;
        if (player1.score > player1.hight_score)
            player1.hight_score = player1.score;
        ofstream H_score("Hight_score2.txt");
        H_score << player1.hight_score;

    }
    //------draw funcion-------//
    void drawer() {
        system("cls");

        bool test_fruit_tail = false;
        //--------print score--------//
        cout << "player name: " << player1.name;
        cout << "         player score : " << player1.score;
        cout << "         Hight Score : " << player1.hight_score;
        cout << "         Press X to exit the map.";
        cout << "\n\n\n";
        //---------check if fruit draw on the tail-------//
        for (int z = 0; z < tail; z++) { if (fruity == taily[z] && fruitx == tailx[z])test_fruit_tail = true; }
        //------draw map------//
        for (int i = 1; i <= hight; i++) {
            cout << "                   ";
            for (int j = 1; j <= width; j++) {

                if (i == 1 || i == hight || j == 1 || j == width)cout << "#";
                //--------draw snake head------//
                else if (i == heady && j == headx)cout << "0";
                //---------draw fruit--------//
                else if (!test_fruit_tail)if (i == fruity && j == fruitx) { cout << '$'; }
                //--------draw tail----------//
                else {
                    bool printed_o = false;
                    for (int z = 0; z < tail; z++) {
                        if (j == tailx[z] && i == taily[z]) { cout << "o"; printed_o = true; }
                    }
                    if (!printed_o) { cout << " "; }
                }
            }cout << endl;
        }


    }
    void hit() {

        //----------the tail hit-----------//
        for (int r = 0; r < tail; r++) { if (headx == tailx[r] && heady == taily[r]) { headx = width / 2; heady = hight / 2; tail = 0; player1.score = 0; player1.lose = true; } }
        //----------the wall hit-----------//
        if (headx <= 1 || headx > width - 1 || heady <= 1 || heady > hight - 1) { headx = width / 2; heady = hight / 2; tail = 0; player1.score = 0; player1.lose = true; }
        //----------if eat fruit-----------//
        if (headx == fruitx && heady == fruity) { player1.score++; randfruite(); tail++; }
    }

};

int main()
{
    system("COLOR 75");
    draw* p = nullptr;
    char retry = 'r';
    draw1 d1;
    draw2 d2;
    int chose = 0;


    do
    {
        system("cls");
        cout << "\n------------Welcome to our game------------";
        cout << "\n       chose the map for play : ";
        cout << "\n        1. for the open map";
        cout << "\n        2. for the close map";
        cout << "\n        3. Exit";
        cout << "\n  Your choic is :";
        cin >> chose;
        Sleep(20);
        if (chose == 1)
        {
            p = &d1;
            p->stop_move();
            player1.lose = false;
            p->set_name();
            p->randfruite();
            while (!player1.lose) { p->fun_call(); }
            retry = 'r';

        }
        else if (chose == 2)
        {
            p = &d2;
            p->stop_move();
            player1.lose = false;
            p->set_name();
            p->randfruite();
            while (!player1.lose) { p->fun_call(); }
            retry = 'r';

        }
        else if (chose == 3)
        {
            retry = ' ';
        }
        else
        {

            retry = 'r';

        }

    }

    while (retry == 'r');

    return 0;
}