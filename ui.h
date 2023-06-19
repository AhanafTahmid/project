#include <graphics.h>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

class Field
{
protected:
    int left, top, right, bottom, bgColor;
    char *title;
public:
    Field()
    {
        bgColor = WHITE;
        setbkcolor(WHITE);
        setcolor(BLACK);
    }
    Field(int left, int top, int right, int bottom, int bgColor, int textColor, char* title)
    {
        visible(left, top, right, bottom, bgColor,textColor, title);
    }
    void visible(int left, int top, int right, int bottom, int bgColor, int textColor, char* title)
    {
        this -> left = left;
        this -> top = top;
        this -> right = right;
        this -> bottom = bottom;
        this -> bgColor = bgColor;
        this -> title = title;

        setfillstyle(SOLID_FILL, bgColor);
        bar(left, top, right, bottom);
        setcolor(BLACK);
        rectangle(left, top, right, bottom);
        setcolor(textColor);
        setbkcolor(bgColor);
        outtextxy((left+right)/2-textwidth(title)/2, (bottom+top)/2-textheight("A")/2, title);
    }
    void hideBorder()
    {
        setcolor(bgColor);
        rectangle(left, top, right, bottom);
    }
    bool cursor()
    {
        POINT p;
        GetCursorPos(&p);
        ScreenToClient(GetForegroundWindow(), &p);
        if(p.x >= left && p.x<=right && p.y>=top && p.y<=bottom) return true;
        return false;
    }
};

class Input : public Field
{
private:
    int x, y, time_limit;
    clock_t begin;   //clock_t is used to measure processor and CPU time
    int prev_sec;
    bool isDisplayTime;
    bool isPinInput;

public:

    bool isCharacterInput;

    Input()
    {
        begin = clock();
        prev_sec = 0;
    }
    ///For Name Input Section:
    void Name(int left, int top, int right, int bottom)
    {
        Field::visible(left, top, right, bottom, WHITE,WHITE, "");
        x = left + 3;
        y = (top+bottom)/2 - textheight("A")/2;
        isPinInput = false;
    }
    Input(int left, int top, int right, int bottom)
    {
        visible(left, top, right, bottom);
    }
    void visible(int left, int top, int right, int bottom)
    {
        Field::visible(left, top, right, bottom, WHITE, WHITE, "");
        x = left + 3;
        y = (top+bottom)/2 - textheight("A")/2;
        isDisplayTime = false;
        isCharacterInput = false;
        begin = clock();
        prev_sec = 0;
    }
    void setTimeLimit(int t)
    {
        time_limit = t;
        isDisplayTime = true;
    }
    void displayTime()
    {
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        int current_sec = time_spent;
        if(current_sec > prev_sec)
        {
            int mint = (time_limit - time_spent) / 60;
            int sec = (int)(time_limit - time_spent) % 60;
            if(mint == 0 && sec < 0) return;
            char time[10] = "";
            char smint[3] = "";
            char ssec[3] = "";

            snprintf(smint, sizeof(smint), "%d", mint);
            snprintf(ssec, sizeof(ssec), "%d", sec);
            strcat(time, "0");
            strcat(time, smint);
            strcat(time, " : ");
            if(sec < 10) strcat(time, "0");
            strcat(time, ssec);
            setcolor(BLACK);
            new Field(16, 40, 200, 80, WHITE, BLACK, time);
            prev_sec = current_sec;
            new Field();
        }
    }
    double time_speent()
    {
        return (clock() - begin) / CLOCKS_PER_SEC;
    }
    void sleep()
    {
        for (int c = 1; c <= 12760; c++)
        {
            if(isDisplayTime) displayTime();
            if(kbhit() || !cursor()) return;

            for(int d = 1; d <= 2276; d++)
            {
                if(isDisplayTime) displayTime();
                if(kbhit()) return;

            }
        }
    }
    void showCursor(char* data, int color)
    {
        double tw = textwidth(data);
        setcolor(color);
        outtextxy(x + tw, y, "|");
    }
    void print(char* data, int* idx, int color)
    {
        setcolor(color);
        outtextxy(x, y, data);
    }
    char getName(char *data)
    {
        setbkcolor(WHITE);
        int idx = strlen(data);
        print(data, &idx, BLACK);
        while(true)
        {
            if(kbhit())
            {
                char ch = getch();
                if(idx && ch == 8)
                {
                    print(data, &idx, WHITE);
                    showCursor(data, WHITE);
                    idx--;
                }
                else if(ch >= 32  && ch <= 126)
                {
                    data[idx++] = ch;
                    data[idx] = 0;
                    if(left + textwidth(data) + textwidth("|") >= right - 3)
                        idx--;//If true that means Input Area is overflow
                }
                else if(ch == 9 || ch == 13)//9 = tab, 13 = enter key
                {
                    showCursor(data, WHITE);
                    return 9;
                }
                data[idx] = 0;
                print(data, &idx, BLACK);
            }
            else if(!cursor())
            {
                showCursor(data, WHITE);
                return 0;
            }
            showCursor(data, BLACK);
            sleep();
            showCursor(data, WHITE);
            sleep();
        }
    }
    char getText(char *data)
    {
        setbkcolor(WHITE);
        int idx = strlen(data);
        print(data, &idx, BLACK);
        while(true)
        {
            if(isDisplayTime) displayTime();
            if(kbhit())
            {
                char ch = getch();
                if(idx && ch == 8)//backspace
                {
                    print(data, &idx, WHITE);
                    showCursor(data, WHITE);
                    idx--;
                }
                else if(ch > 32  && ch <= 126)
                {
                    data[idx++] = ch;
                    data[idx] = 0;
                    if(left + textwidth(data) + textwidth("|") >= right - 3)
                        idx--;//If true that means Input Area is overflow
                }
                else if(ch == 9 || ch == 13 || ch == 32)//9 = tab, 13 = enter key
                {
                    showCursor(data, WHITE);
                    return 9;
                }
                data[idx] = 0;
                print(data, &idx, BLACK);
            }
            else if(!cursor())
            {
                showCursor(data, WHITE);
                return 0;
            }
            showCursor(data, BLACK);
            if(isDisplayTime)displayTime();
            if(isCharacterInput && idx) return 9;
            sleep();

            showCursor(data, WHITE);
            if(isDisplayTime) displayTime();
            sleep();
        }
    }
};

class Button : public Field
{
private:
    bool flag;
public:
    Button() {}
    Button(int left, int top, int right, int bottom, int bgColor, char* title)
        :Field(left, top, right, bottom, bgColor,WHITE, title)
    {
        flag = false;
    }
    void hover(int color)
    {
        if(cursor() && !flag)
            new Field(left, top, right, bottom, color, WHITE, title), flag = true;
        else if(!cursor() && flag)
            new Field(left, top, right, bottom, bgColor, WHITE, title), flag = false;
    }

};
