#include <bits/stdc++.h>
using namespace std;
#include <graphics.h>

//for the button and field
#include "ui.h"




//Below are the functions that will run in the application

//easy() and easy2() are the games
void Easy();
void Easy2();
//void loading();
void scoreGame();
void setTime();
void about_us();//it is the about us page
void exit();
void menu();
void setTime();
void game1_start();
void game2_start();
void Header();
void Footer();
void storeAcc(int x);
void storeSpeed(int x);
void storeAvg(int x);


void delay(unsigned int mseconds)
{
    //clock_t returns the number of clock ticks;  It is an arithmetic type
    //clock_t is a type defined in the <ctime> head
    clock_t goal = mseconds+clock();//how many ticking in clock
    while(goal>clock());
}


void frame()
{
    //cleardevice() is a function of graphics which clears the screen
    cleardevice();
    //Frame Start
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(0, 0, 15, 505);//For Left Side
    bar(785, 0, 800, 505);//For Right Side
    bar(15, 0, 800, 15);//For Top Side
    bar(0, 505, 800, 520);//For Bottom Side
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(16, 16, 784, 504);//For Middle rectangle
    //Frame End
}

char name[200] = "";
char cpyname[200]="";
int spd=0;
int Ac=0;


vector<string> readDataFromFile(char* fileName)
{
    vector<string>words;
    FILE *file = fopen(fileName, "r");
    char c;
    string word;
    while((c = fgetc(file)) != EOF)
    {
        if(c == ' ' || c == '\n')
        {
            words.push_back(word);
            word = "";
        }
        else word.push_back(c);
    }
    fclose(file);
    return words;
}


//This is the game
void startPracticing(int lavel, int time_limit)
{

    //graphics.h function
    cleardevice();
    frame();
    //creating the parameterized object of Field from ui.h
    new Field(16, 0, 200, 40, BLUE, WHITE, "Time Left");//Field(int left, int top, int right, int bottom, int bgColor, int textColor, char* title)
    new Field(200, 0, 350, 40, BLUE, WHITE, "Correct");
    new Field(350, 0, 480, 40, BLUE, WHITE, "Wrong");
    new Field(480, 0, 650, 40, BLUE, WHITE, "Accuracy");
    new Field(650, 0, 783, 40, BLUE, WHITE, "Speed");
    new Field(16, 40, 200, 80, WHITE, BLACK, "00 : 00");//Initial Time

    //for generating random time; time(0) - passing 0 for generating the current time
    srand(time(0));

    new Field(200, 40, 350, 80, WHITE, BLACK, "0");
    new Field(350, 40, 480, 80, WHITE, RED, "0");
    new Field(480, 40, 650, 80, WHITE, BLACK, "100%");
    new Field(650, 40, 783, 80, WHITE, BLACK, "0");
    new Field(16, 80, 783, 150, WHITE, BLACK, "");

    clock_t begin = clock();
    double time_spent = 0.0;
    settextstyle(4, 0, 3);//void settextstyle(int font, int direction, int font_size);

    vector<string>words;
    if(lavel == 1) words = readDataFromFile("lavel1.txt");
    else words = readDataFromFile("lavel2.txt");

    int length = words.size();
    string rand_word  = words[rand() % length];

    char *crand_word = new char[50];
    strcpy(crand_word, words[rand() % length].c_str());

    new Field(16, 80, 783, 150,WHITE,BLACK,crand_word);//Print Random Word
    new Field(16, 150, 783, 200,WHITE,BLACK,"");//To Print a White Background area

    Input word(250, 149, 550, 199);
    word.setTimeLimit(time_limit);
    if(lavel == 1) word.isCharacterInput = true;
    word.hideBorder();

    setcolor(WHITE);
    rectangle(17, 150, 783, 150);//To remove bottom line of rectangular area
    setcolor(BLACK);
    rectangle(200, 150, 600, 150);//To print a line

    Button back_button(15, 350, 250, 460, MAGENTA, "BACK");
    Button re_start(501, 350, 783, 460, CYAN, "RE-START");
    //Button next(501, 350, 783, 460, MAGENTA, "NEXT LEVEL");


    char typed_word[50] = "";
    int ccnt = 0, wcnt = 0;
    bool timeOverWarning = false;
    bool isStore = false;

    Footer();

    while(true)
    {
        re_start.hover(GREEN);
        back_button.hover(GREEN);
        //next.hover(GREEN);
        //GetAsyncKeyState checks if the left mouse button is pressed using the GetAsyncKeyState
        //GetAsyncKeyState is for seeing where the mouse is moving
        //it will check whether a key is pressed or not.
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(re_start.cursor())
            {
                startPracticing(lavel, time_limit);
                return;
            }

            /*else if(next.cursor())
            {
                if(time_limit==60)startPracticing(lavel, 120);
                if(time_limit==120)startPracticing(lavel, 300);
            }*/

            else if(back_button.cursor())
            {
                if(lavel==1)Easy();
                else if(lavel==2)Easy2();
                return;
            }
//            else if(stor.cursor() && !isStore)
            {

               storeAcc(Ac);
               storeSpeed(spd);
               storeAvg((Ac+spd)/2);
               spd=0;
               Ac=0;
               isStore = true;
            }

        }
        char ch;

        if(word.time_speent() <= time_limit) ch = word.getText(typed_word);
        else if(!timeOverWarning)
        {
            Input current_word_remover(250, 149, 550, 199);
            current_word_remover.hideBorder();
            setcolor(BLACK);
            rectangle(200, 150, 600, 150);//To print a line
            //new Field(16, 200, 783, 348, LIGHTGRAY, RED, "Time is Over!");
            outtextxy(300,250,"Time is Over!");
            //new Field(100, 200, 700, 300, LIGHTGRAY, RED, "Time is Over!");

            timeOverWarning = true;
            //timeOver(int I);
        }

        if(ch == 9 && word.time_speent() <= time_limit)
        {
            if(strcmp(typed_word, crand_word) == 0) ccnt++;
            else wcnt++;

            int speed = (ccnt + wcnt) * 60 / word.time_speent();
            spd=speed;
            char sspeed[10];
            char speed_result[20] = "";
            sprintf(sspeed, "%d", speed);
            strcat(speed_result, sspeed);


            new Field(650, 40, 783, 80, WHITE, BLACK, speed_result);

            char temp[100];
            sprintf(temp, "%d", ccnt);
            new Field(200, 40, 350, 80, WHITE, BLACK, temp);
            sprintf(temp, "%d", wcnt);
            new Field(350, 40, 480, 80, WHITE,RED, temp);
            int acc = (ccnt * 100) / (ccnt + wcnt);

            Ac=acc;///add now

            sprintf(temp, "%d", acc);
            strcat(temp, "%");
            new Field(480, 40, 650, 80, WHITE, BLACK, temp);

            if(lavel == 1)
            {
                for (int c = 1; c <= 22760; c++)
                {
                    for(int d = 1; d <= 2276; d++)
                    {

                    }
                }
            }
            strcpy(typed_word, "");
            settextstyle(4, 0, 3);
            rand_word  = words[rand() % length];
            strcpy(crand_word, rand_word.c_str());

            new Field(16, 80, 783, 150,WHITE,BLACK,crand_word); //To print random word
            new Field(16, 150, 783, 200,WHITE,BLACK,"");

            setcolor(WHITE);
            rectangle(16, 150, 783, 150);

            setcolor(BLACK);
            rectangle(200, 150, 600, 150);
        }

    }

}


void Header()
{
    // Header Section



    //Set text color
    setcolor(BLACK);
    //set background color
    setbkcolor(LIGHTCYAN);
    //font style
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
    //void outtextxy(int x, int y, char *string); displaying text at a specific position
    outtextxy(400 - textwidth("Typing Master") / 2, 58 - textheight("A") / 2, "Typing GAME");
    setlinestyle(1, 0, 1);
    //for drawing line in header
    line(16, 84.5 + textheight("A")/ 4, 784,84.5 + textheight("A")/ 4);
    setlinestyle(0, 0, 1);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
}
void Footer()
{
    //Footer Section

    //void setfillstyle(int pattern, int color)
    setfillstyle(SOLID_FILL, CYAN);
    //void bar(int left, int top, int right, int bottom); drawing the bar
    bar(16, 465, 783, 504);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
    setbkcolor(CYAN);
    setcolor(BLACK);
    outtextxy(400 - textwidth("Developed By Spartan")/2, 485 - textheight("A") / 2, "Developed By Spartan");
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
}
void game1_start()
{
    cleardevice();
     frame();
     Header();
     Footer();
    //creating the parameterized object from ui.h
    Button easy(200, 130, 600, 230, MAGENTA, "  Start Game1");
    //Button hard(200, 250, 600, 350, MAGENTA, "  HARD");
    Button back(15, 425, 130, 465, BLUE, "BACK");
    while(true)
    {
        easy.hover(GREEN);
        //hard.hover(GREEN);
        back.hover(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(easy.cursor()) Easy();
            else if(back.cursor())menu();



        }
    }
}



void Easy()
{
    cleardevice();
    frame();

    Footer();
    new Field(0, 0, 800, 50, MAGENTA,WHITE, "Easy Labels");
    Button char_one_mnt(200, 130, 600, 230, CYAN, "Type Characters");
    //Button char_two_mnt(200, 230, 600, 330, MAGENTA, "Label 2");
    //Button char_five_mnt(200, 330, 600, 430, CYAN, "Label 3");
    Button back(15, 425, 130, 465, BLUE, "BACK");
    while(true)
    {
        char_one_mnt.hover(RED);
        //char_two_mnt.hover(BLUE);
        //char_five_mnt.hover(RED);
        back.hover(GREEN);

        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(char_one_mnt.cursor())  startPracticing(1, 60);
            //else if(char_two_mnt.cursor()) startPracticing(1, 120);
            //else if(char_five_mnt.cursor())startPracticing(1,300);
            else if(back.cursor())game1_start();
        }
        if(kbhit()) getch();
    }
}
void about_us()
{
    setbkcolor(DARKGRAY);
    cleardevice();
    frame();
    Footer();
    settextstyle(6, 0, 4);
    new Field(0, 0, 800, 70, GREEN,BLACK,"About Us");
    settextstyle(8, 0, 1);
    new Field(15, 200, 785, 230, CYAN,WHITE ,"Team Members");
    new Field(15, 230, 785, 260, CYAN,WHITE ,"Team Leader: Ahanaf");
    new Field(15, 260, 785, 290, CYAN,WHITE ,"Member 1: Evan");
    new Field(15, 290, 785, 320, CYAN,WHITE ,"Member 2: Dihan");
    new Field(15, 320, 785, 350, CYAN,WHITE ,"Member 3: Irtisum");
    settextstyle(8, 0, 2);
    Button back(15, 425, 130, 465, BLUE, "BACK");
    while(true)
    {
        back.hover(GREEN);

        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(back.cursor())menu();
        }
        if(kbhit()) getch();
    }
}


void storeAcc(int x)
{
    ofstream myfile;
    myfile.open("Previous Record.txt", std::ios_base::app);

    myfile<<x<<" ";
    myfile.close();
}
void storeSpeed(int x)
{
    ofstream myfile;
    myfile.open("Previous RecordSpeed.txt", std::ios_base::app);

    myfile<<x<<" ";
    myfile.close();
}
void storeAvg(int x)
{
   ofstream myfile;
    myfile.open("Avg.txt", std::ios_base::app);

    myfile<<x<<" ";
    myfile.close();
}



//#######################################################################################
//#######################################################################################
//For game 2
//Main game function for the second game



void Easy2()
{
    //loading();
    cleardevice();
    frame();
    Footer();
    new Field(0, 0, 800, 50, MAGENTA,WHITE, "Hard Lavels");


    Button word_one_mnt(200, 130, 600, 230, CYAN, "Type Word by Word");
    //Button word_two_mnt(200, 230, 600, 330, MAGENTA, "Label 2");
    //Button word_five_mnt(200, 330, 600, 430, CYAN, "Label 3");
    Button back(15, 425, 130, 465, BLUE, "BACK");

    while(true)
    {
        word_one_mnt.hover(GREEN);
        //word_two_mnt.hover(GREEN);
        //word_five_mnt.hover(GREEN);
        back.hover(GREEN);



        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(word_one_mnt.cursor())  startPracticing(2, 60);
            //else if(word_two_mnt.cursor()) startPracticing(2, 120);
            //else if(word_five_mnt.cursor()) startPracticing(2, 300);
            else if(back.cursor())game2_start();
        }
        if(kbhit()) getch();//kbhit determines if a key has been pressed or not
    }
}



void game2_start()
{
    cleardevice();
     frame();
     Header();
     Footer();
    //creating the parameterized object from ui.h
    Button easy(200, 130, 600, 230, MAGENTA, "  Start Game2");
    //Button hard(200, 250, 600, 350, MAGENTA, "  HARD");
    Button back(15, 425, 130, 465, BLUE, "BACK");
    while(true)
    {
        easy.hover(GREEN);
        //hard.hover(GREEN);
        back.hover(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(easy.cursor()) Easy2();
            //else if(hard.cursor())Hard();
            else if(back.cursor())menu();
        }
    }
}
void exit()
{
    setbkcolor(BLACK);
    cleardevice();
    frame();
    Footer();
    new Field(0, 0, 800, 40, MAGENTA,WHITE, "WHAT YOU WANT TO DO");
    Button back(15, 425, 130, 465, BLUE, "BACK");
    Button exit(650, 425, 785, 465, BLUE, "EXIT");
    while(true)
    {
        back.hover(GREEN);

        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(back.cursor())menu();
            else if(exit.cursor())closegraph();
        }
        if(kbhit()) getch();
    }

}
void menu()
{

    setbkcolor(CYAN);
    cleardevice();
    settextstyle(6, 0, 4);
    new Field(0, 0, 800, 70, GREEN,BLACK, "MAIN MENU");

    Footer();

    ////left,top,right,bottom
    Button game1(200, 95, 600, 165, MAGENTA, "  Game 1");
    //Button aboutMe(200, 175, 600, 245, BLUE, "  Game 2");
    Button game2(200, 170, 600, 240, BLUE, "Game 2");
    //Button game3(200, 205, 600, 265, BLUE, "Game 1(Hard)");
    //Button game4(200, 270, 600, 330, BLUE, "Game 2(Hard)");
    Button aboutMe(200, 245, 600, 315, BLUE, "  About Us");
    //Button preb(200, 250, 600, 320, BLUE, "PREVIOUS RECORDs");
    Button ext(200, 320, 600, 390, RED, "  EXIT");

    while(true)
    {
        //hovering over menu
        game1.hover(GREEN);
        game2.hover(GREEN);
       // game3.hover(GREEN);
        aboutMe.hover(GREEN);
        ext.hover(GREEN);

        //pressing the windows
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(game1.cursor()) game1_start();
            else if(game2.cursor())game2_start();
            else if(aboutMe.cursor()) about_us();
            else if(ext.cursor()) exit();


        }
    }
}





void login()
{

    setbkcolor(LIGHTCYAN);
    cleardevice();

    settextstyle(6, 0, 4);
    new Field(0,0,800,80,BLACK,WHITE,"WELCOME TO TYPING GAME");//left,top,right,bottom
    settextstyle(8, 0, 2);//void settextstyle(int font, int direction, int font_size);
    new Field(100, 350, 350, 400, GREEN,WHITE, "ENTER YOUR NAME");//left,top,right,bottom
    Input userName;//creating input object from the ui.h
    userName.Name(350, 350,700, 400);//left,top,right,bottom
    Button submit(370,430,450,480, BLUE, "OK");

    while(true)
    {
        int tr=0;
        submit.hover(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(userName.cursor()){ userName.getName(name); tr=1; }
            else if(submit.cursor())
            {
                if(strlen(name)>0)menu();
            }

        }
    }

}
