#include <bits/stdc++.h>
using namespace std;
#include <graphics.h>

//#include <stdlib.h>

//for the button and field
#include "ui.h"


char name[200] = "";
char cpyname[200]="";
//char sped[10][10]="";
int spd=0;
int Ac=0;

//Below are the functions that will run in the application

void Easy();
//void loading();
void scoreGame();
void setTime();
void rules();//it is the about us page
void exit();
void menu();
void setTime();
void startGame();
void Hard();
void Header();
void Footer();
void storeAcc(int x);
void storeSpeed(int x);
void storeAvg(int x);


void delay(unsigned int mseconds)
{
    clock_t goal = mseconds+clock();
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

void startPracticing(int lavel, int time_limit)
{

    cleardevice();
    frame();
    //creating the parameterized object of Field from ui.h
    new Field(16, 0, 200, 40, BLUE, WHITE, "Time Left");
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
    settextstyle(4, 0, 3);

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
    Button re_start(251, 350, 500, 460, CYAN, "RE-START");
    Button next(501, 350, 783, 460, MAGENTA, "NEXT LABEL");
    Button stor(600, 300, 750,340,7, "STORE");


    char typed_word[50] = "";
    int ccnt = 0, wcnt = 0;
    bool timeOverWarning = false;
    bool isStore = false;

    Footer();

    while(true)
    {
        re_start.hover(GREEN);
        back_button.hover(GREEN);
        next.hover(GREEN);
        stor.hover(8);
        //GetAsyncKeyState checks if the left mouse button is pressed using the GetAsyncKeyState 
        //GetAsyncKeyState is for seeing where the mouse is moving
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(re_start.cursor())
            {
                startPracticing(lavel, time_limit);
                return;
            }

            else if(next.cursor())
            {
                if(time_limit==60)startPracticing(lavel, 120);
                if(time_limit==120)startPracticing(lavel, 300);
            }
            else if(back_button.cursor())
            {
                if(lavel==1)Easy();
                else if(lavel==2)Hard();
                return;
            }
            else if(stor.cursor() && !isStore)
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

/*
void loading()
{
    setbkcolor(DARKGRAY);
    cleardevice();
    frame();
    settextstyle(4, 0, 4);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
    outtextxy(400 - textwidth("Loading, Please Wait...")/2, 180, "Loading, Pleas Wait...");

    for(int i=300; i<450; i++)
    {
        delay(15);
        line(i,210,i,230);
    }

}
*/

void Header()
{
    // Header Section


    //https://www.geeksforgeeks.org/setcolor-function-c
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
void startGame()
{
    cleardevice();
     frame();
     Header();
     Footer();
    //creating the parameterized object from ui.h
    Button easy(200, 130, 600, 230, MAGENTA, "  EASY");
    Button hard(200, 250, 600, 350, MAGENTA, "  HARD");
    Button back(15, 425, 130, 465, BLUE, "BACK");
    while(true)
    {
        easy.hover(GREEN);
        hard.hover(GREEN);
        back.hover(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(easy.cursor()) Easy();
            else if(hard.cursor())Hard();
            else if(back.cursor())menu();



        }
    }
}
void Hard()
{
    //loading();
    cleardevice();
    frame();
    Footer();
    new Field(0, 0, 800, 50, MAGENTA,WHITE, "Hard Labels");


    Button word_one_mnt(200, 130, 600, 230, CYAN, "Label 1");
    Button word_two_mnt(200, 230, 600, 330, MAGENTA, "Label 2");
    Button word_five_mnt(200, 330, 600, 430, CYAN, "Label 3");
    Button back(15, 425, 130, 465, BLUE, "BACK");

    while(true)
    {
        word_one_mnt.hover(GREEN);
        word_two_mnt.hover(GREEN);
        word_five_mnt.hover(GREEN);
        back.hover(GREEN);



        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(word_one_mnt.cursor())  startPracticing(2, 60);
           else if(word_two_mnt.cursor()) startPracticing(2, 120);
           else if(word_five_mnt.cursor()) startPracticing(2, 300);
           else if(back.cursor())startGame();
        }
        if(kbhit()) getch();
    }
}
void Easy()
{
    cleardevice();
    frame();

    Footer();
    new Field(0, 0, 800, 50, MAGENTA,WHITE, "Easy Labels");
    Button char_one_mnt(200, 130, 600, 230, CYAN, "Label 1");
    Button char_two_mnt(200, 230, 600, 330, MAGENTA, "Label 2");
    Button char_five_mnt(200, 330, 600, 430, CYAN, "Label 3");
    Button back(15, 425, 130, 465, BLUE, "BACK");
    while(true)
    {
        char_one_mnt.hover(RED);
        char_two_mnt.hover(BLUE);
        char_five_mnt.hover(RED);
        back.hover(GREEN);

        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(char_one_mnt.cursor())  startPracticing(1, 60);
            else if(char_two_mnt.cursor()) startPracticing(1, 120);
            else if(char_five_mnt.cursor())startPracticing(1,300);
            else if(back.cursor())startGame();
        }
        if(kbhit()) getch();
    }
}
void rules()
{
    setbkcolor(DARKGRAY);
    cleardevice();
    frame();
    Footer();
    settextstyle(6, 0, 4);
    new Field(0, 0, 800, 70, GREEN,BLACK,"About Us");
    settextstyle(8, 0, 1);
    new Field(15, 200, 785, 230, CYAN,WHITE ,"1.Type Your Name 1st and click \"OK\" ");
    new Field(15, 230, 785, 260, CYAN,WHITE ,"2.If you are Interested to play , press \"START GAME\" ");
    new Field(15, 260, 785, 290, CYAN,WHITE ,"3.select the level ");
    new Field(15, 290, 785, 320, CYAN,WHITE ,"4.Lets Play ");
    new Field(15, 320, 785, 350, CYAN,WHITE ,"5.Avoid incorrect typing and you will seen your typing speed");
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

void Record()
{
    setbkcolor(CYAN);
    cleardevice();
    vector<string>acc;
    vector<string>sped1;
    vector<string>avg;

    acc=readDataFromFile("Previous Record.txt");
    sped1=readDataFromFile("Previous RecordSpeed.txt");
    avg=readDataFromFile("Avg.txt");

    while(acc.size()>10)acc.erase(acc.begin());
    while(sped1.size()>10)sped1.erase(sped1.begin());
    while(avg.size()>10)avg.erase(avg.begin());



    int n=acc.size();
    int n1=sped1.size();
    int n2=avg.size();

    int a[n];
    int b[n1];
    int c[n2];
    for(int i=0;i<n;i++)
    {

        a[i]=atoi(acc[i].c_str());
        b[i]=atoi(sped1[i].c_str());
        c[i]=atoi(avg[i].c_str());
    }
    int mx=c[0];
    int j=0;
    for(int i=0;i<n2;i++)
    {
       if(c[i]>=mx)
       {
           mx=c[i];
           j=i;
       }
    }
    j++;
    char per[30] = "";
    char day1[3] = "";

    snprintf(day1, sizeof(day1), "%d", j);
    strcat(per, "Best performance on ");
    strcat(per, day1);
    if(j==1)strcat(per, "st Day");
    else if(j==2)strcat(per, "nd Day");
    else if(j==3)strcat(per, "rd Day");
    else strcat(per, "th Day");
    //strcat(per, " Day");

    //settextstyle(8, 0, 1);
    new Field(200, 400, 700, 450,BLACK,WHITE ,per);
    setbkcolor(CYAN);
    //outtextxy(150,400,per);
    //int a[5]={10,100,80,100,75};
    ///For Accuracy:
    settextstyle(6, 0, 4);
    int Ax1=50,Ay1=320,Ax2=350,Ay2=320,Bx1=50,By1=320,Bx2=50,By2=20;
    line(Ax1,Ay1,Ax2,Ay2);
    line(Bx1,By1,Bx2,By2);

    settextstyle(4, 0, 1);

    char xaxis[30] = "";
    char day[3] = "";

    snprintf(day, sizeof(day), "%d", n);
    strcat(xaxis, "Accuracy of Last ");
    strcat(xaxis, day);
    strcat(xaxis, " Days");

    settextstyle(8, 0, 1);
    outtextxy(Ax1-30,Ay1+40,xaxis);
    outtextxy(Bx2-15,By2-20,"(%)");
    for(int i=1;i<=10;i++)
    {
      line(Ax1-5, Ay1-i*30,Ax1+5,Ay1-i*30);
      char dd[3] = "";

        char d1[2]="";
        snprintf(d1, sizeof(d1), "%d", i*10);
        strcat(dd, d1);
        strcat(dd, "0");
        if(i==10)strcat(dd, "0");
        outtextxy(Ax1-45,Ay1-i*30-10, dd);


    }
    for(int i=1;i<=n;i++)
    {

        line(Ax1+i*30,Ay1-5,Ax1+i*30,Ay1+5);
        char dd[3] = "";
        strcat(dd, "d");
        char d1[2]="";
        snprintf(d1, sizeof(d1), "%d", i);
        strcat(dd, d1);
        if(i==10)strcat(dd,"0");
        outtextxy(Ax1+i*30-14,Ay1+10, dd);
    }


    int tm1=Ax1;
    int tm2=Ay1;

    for(int i=0;i<n;i++)
    {
        int p1,p2;
        p1=Ax1+30*(i+1);
        p2=Ay2-((By1-By2)/100)*a[i];
        circle(p1,p2 ,3);
        line(tm1,tm2,p1,p2);
        setfillstyle(1,0);
        floodfill(p1,p2,15);
        tm1=p1;
        tm2=p2;
        //cout<<((By1-By2)/100)*a[i]<<endl;
    }
    ///For Speed:
    Ax1=Ax2+70,Ay1=320,Ax2=Ax2*2+70,Ay2=320,Bx1=Ax1,By1=320,Bx2=350+70,By2=20;
    line(Ax1,Ay1,Ax2,Ay2);
    line(Bx1,By1,Bx2,By2);

    char xaxis1[30] = "";
    //day[3] = "";

    snprintf(day, sizeof(day), "%d", n1);
    strcat(xaxis1, "Speed of Last ");
    strcat(xaxis1, day);
    strcat(xaxis1, " Days");

    settextstyle(8, 0, 1);
    outtextxy(Ax1+30,Ay1+40,xaxis1);
    //outtextxy(Bx2-15,By2-20,"(%)");

    for(int i=1;i<=n1;i++)
    {

        line(Ax1+i*30,Ay1-5,Ax1+i*30,Ay1+5);
        char dd[3] = "";
        strcat(dd, "d");
        char d1[2]="";
        snprintf(d1, sizeof(d1), "%d", i);
        strcat(dd, d1);
        if(i==10)strcat(dd,"0");
        outtextxy(Ax1+i*30-14,Ay1+10, dd);
    }
    for(int i=1;i<=10;i++)
    {
       line(Ax1-5, Ay1-i*30,Ax1+5,Ay1-i*30);
       char dd[3] = "";

        char d1[2]="";
        snprintf(d1, sizeof(d1), "%d", i*10);
        strcat(dd, d1);
        strcat(dd, "0");
        if(i==10)strcat(dd, "0");
        outtextxy(Ax1-45,Ay1-i*30-10, dd);


    }
    tm1=Ax1;
    tm2=Ay1;

    for(int i=0;i<n;i++)
    {
        int p1,p2;
        p1=Ax1+30*(i+1);
        p2=Ay2-((By1-By2)/100)*b[i];
        circle(p1,p2 ,3);
        line(tm1,tm2,p1,p2);
        setfillstyle(1,0);
        floodfill(p1,p2,15);
        tm1=p1;
        tm2=p2;
        //cout<<((By1-By2)/100)*a[i]<<endl;
    }
    settextstyle(6, 0, 3);
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

    setbkcolor(DARKGRAY);
    cleardevice();
    settextstyle(6, 0, 4);
    new Field(0, 0, 800, 70, GREEN,BLACK, "MAIN MENU");

    Footer();

    Button start(200, 100, 600, 170, MAGENTA, "  Game 1");
    //Button aboutMe(200, 175, 600, 245, BLUE, "  Game 2");
    Button aboutMe(200, 175, 600, 245, BLUE, "  About Us");
    Button preb(200, 250, 600, 320, BLUE, "PREVIOUS RECORDs");
    Button ext(200, 325, 600, 395, RED, "  EXIT");

    while(true)
    {
        //
        start.hover(GREEN);
        aboutMe.hover(GREEN);
        ext.hover(GREEN);
        preb.hover(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(start.cursor()) startGame();
            else if(aboutMe.cursor()) rules();
            else if(ext.cursor()) exit();
            else if(preb.cursor())Record();


        }
    }




}
void login()
{

    setbkcolor(CYAN);
    cleardevice();

    settextstyle(6, 0, 4);
    new Field(0,0,800,80,BLACK,WHITE,"WELCOME TO TYPING GAME");
    settextstyle(8, 0, 2);
    new Field(100, 350, 350, 400, GREEN,WHITE, "<ENTER YOUR NAME>");
    Input userName;
    userName.Name(350, 350,700, 400);
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
