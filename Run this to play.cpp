#include<iostream>
#include "Snake Game OOP.cpp"  //including the source code
#include<iomanip>
#include<string>
#include<windows.h>
#include<conio.h>
#include<exception>
#include<fstream>
#include<dos.h>

using namespace std;

int main()
{

gotoxy(30,13);
HANDLE hConsole;
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, 12);
SetConsoleTextAttribute(hConsole, 480);                          //Yellow Color Code=480
            for (int i=0; i<0; i++) {
                   cout<<'\xB0';
            }
cout<<" !!!! CLICK ANY WHERE TO START THE GAME !!!! ";
    
SetConsoleTextAttribute(hConsole, 0);
     
HANDLE hout= GetStdHandle(STD_OUTPUT_HANDLE);
        HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
        INPUT_RECORD InputRecord;
        DWORD Events;
        COORD coord;
        CONSOLE_CURSOR_INFO cci;
        cci.dwSize = 25;
        cci.bVisible = FALSE;
        SetConsoleCursorInfo(hout, &cci);
        SetConsoleMode(hin, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
        bool EXITGAME = false;
        int buttonX=0, buttonY=1;


        
    while( !EXITGAME )
    {
        ReadConsoleInput(hin, &InputRecord, 1, &Events);
        switch ( InputRecord.EventType )
		{
                case KEY_EVENT: // keyboard input 
               
                case MOUSE_EVENT: // mouse input 

                    if(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                    {
                        coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
                        coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
                        SetConsoleCursorPosition(hout,coord);
                        
						
                        

                       
						if(InputRecord.Event.MouseEvent.dwMousePosition.Y and  InputRecord.Event.MouseEvent.dwMousePosition.X)
						//if(InputRecord.Event.MouseEvent.dwMousePosition.Y == 0 and  InputRecord.Event.MouseEvent.dwMousePosition.X==0) for coordinates!!
						{
						functionality(); // This is the main function of the game code.
						}
                    }    
		}	
	}	
}
