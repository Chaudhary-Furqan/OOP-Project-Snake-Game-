/* --------------Some Information-----------------                    `              ------------------To Change---------------------------------
   Down  = kiDown							                              				//change normal food 
   Right = kiRight																		//change special food
   Up    = kiUp																			//speed of snake
   Left  = 75  																			//colour of snake
   ESC   = 27																			//Change snake body
   s=115   S=83																			//  w=119 ,a=97,s=115,d=100
   Horizontal Distance/iHori = 76 Characters											// for WASD  kiDown=115,kiLeft=97,kiRight=100,kiUp=119,kiEscape=27
   Vertical Distance/iVirt = 17 Lines													//kiDown=80,kiLeft=75,kiRight=77,kiUp=72,kiEscape=27
   Coordinates of Score (14,21)       Single Player										//add special food score
   Coordinates of Time  (73,21)       Single Player										//change normal food score
   																						//change normal food colour
   																						//change special food colour
   -------------About Data Memmbers-----------------									//temp=50s  time for special food, change temp variables to change time
   C for Class
   q for Object
   i for int
   c for char
   qp for object pointer
   cp for char pointer
   qa for object array
   ki for constant int
*/
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<exception>
#include<fstream>
#include<ctime>                //for radom number generating (for srand())
#include<iomanip>
#include<string>
#include<dos.h>
using namespace std;
char cTempDir, cDoThis;   
enum EDir{kiDown=80,kiLeft=75,kiRight=77,kiUp=72,kiEscape=27};   //enum of constant directions  
//=========================== gotoxy() ==================================//
void gotoxy(int x, int y) {
     COORD coord;
     coord.X = x;
     coord.Y = y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//============================= CLocation ================================//
class CLocation {
public:
      int x,y;
      void show (int face) {
           if (face==0) {                                                   
               gotoxy(x,y); 
               cout<<"O";
           }				//Change snake body
           else {
           gotoxy(x,y);
           cout<<"\xDB";  
           }
      }
      void hide () {
           gotoxy(x,y);
           cout<<" ";
      }
      void set(int x0,int y0)
      {
           x=x0;
           y=y0;
      }
      bool operator==(CLocation &);
};
//======================= Comparison Operator ==========================//
bool CLocation::operator==(CLocation & temp) {
     if (x==temp.x && y==temp.y) {
        return 1;
     }
     else return 0;
}
//=========================== Boundary Class ===========================//
class CBoundary : public CLocation {
public:       
       int iVirt;
       int iHori;
       int iSignal;
       //Boundary Arrays for User
       CLocation *qpLeftBound;
       CLocation *qpRightBound;
       CLocation *qpUpBound;
       CLocation *qpDownBound;
       
       //No-Orgumnet Constructor
       CBoundary () {
                iVirt=17;
                iHori=76;
                iSignal=0;
       //----------------- User Boundaries -----------------//
                qpLeftBound = new CLocation[iVirt];
                qpRightBound = new CLocation[iVirt];     
                qpUpBound = new CLocation[iHori];        
                qpDownBound = new CLocation[iHori];
       
       }
       //____________User Boundary Setting_______________//
       //Set Left Boundary for snake
       void setLeftBoundary () 
       {
            for (int i=0; i<iVirt; i++) 
            {
                qpLeftBound[i].set(2,i+2);
                
            }
       }
       //Set Right Boundary for snake    
       void setRightBoundary () 
       {
            for (int i=0; i<iVirt; i++) 
            {
                qpRightBound[i].set(kiRight,i+2);
                
            }
       }
       //Set Upper Boundary for snake
       void setUpBoundary () 
       {
            for (int i=0; i<iHori; i++) 
            {
                qpUpBound[i].set(2+i,1);
               
            }
       }
       //Set Down Boundary for snake
       void setDownBoundary () 
       {
            for (int i=0; i<iHori; i++) 
            {
                qpDownBound[i].set(2+i,19);
                
            }
       }
       //Show Single Player Game Boundary
       void showSingleBoundary () {
            cout<<"  ";
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 480);                          //Yellow Color Code=480
            for (int i=0; i<24; i++) {
                   cout<<'\xB0';
            }
            cout<<"A Snake Game in OOP using C++"; 
            for (int i=0; i<24; i++) {
                cout<<'\xB0';
            }
            SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
            cout<<"\n  "<<'\xC9';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBB'<<"\n"<<"  "<<'\xBA';
            for (int i=0; i<75; i++) {
                cout<<" ";
            }
            cout<<'\xBA';
            for (int j=0; j<16; j++) {
                cout<<"\n"<<"  "<<'\xBA';
                for (int i=0; i<75; i++) {
                    cout<<" ";
                }
                cout<<'\xBA';
            }
            cout<<"\n"<<"  "<<'\xC8';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBC';
            cout<<"\n  "<<'\xC9';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBB'<<"\n"<<"  "<<'\xBA';
            SetConsoleTextAttribute(hConsole, 271);                          //White Color Code=271
            cout<<"   Score: "<<"\t\t\t\t\t\t\tTime:         ";
            SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
            cout<<'\xBA';
            cout<<"\n  "<<'\xC8';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBC';
            cout<<"\n  ";
            SetConsoleTextAttribute(hConsole, 480);                     //Yellow Color Code=480
            for (int i=0; i<10; i++) {
                cout<<'\xB0';
            }
            cout<<"NATIONAL UNIVERSITY OF COMPUTER AND EMERGING SCIENCES"; 
            for (int i=0; i<10; i++) {
                cout<<'\xB0';
            }
            SetConsoleTextAttribute(hConsole, 13);             //Pink Color Code=13
            gotoxy(25,21);
            cout<<"     Current Key: ";
       }
       
       //Game Over Screen 
       void gameOverScreen () {
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            cout<<"  ";
            SetConsoleTextAttribute(hConsole, 480);                     //Yellow Color Code=480
            for (int i=0; i<24; i++) {
                   cout<<'\xB0';
            }
            cout<<"A Snake Game in OOP using C++"; 
            for (int i=0; i<24; i++) {
                cout<<'\xB0';
            }
            SetConsoleTextAttribute(hConsole, 8);                          //Dark Gray Color Code=8
            cout<<"\n  "<<'\xC9';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBB'<<"\n"<<"  "<<'\xBA';
            for (int i=0; i<75; i++) {
                cout<<" ";
            }
            cout<<'\xBA';
            for (int j=0; j<19; j++) {
                cout<<"\n"<<"  "<<'\xBA';
                for (int i=0; i<75; i++) {
                    cout<<" ";
                }
                cout<<'\xBA';
            }
            cout<<"\n"<<"  "<<'\xC8';
            for (int i=0; i<75; i++) {
                cout<<'\xCD';
            }
            cout<<'\xBC'<<"\n  ";
            SetConsoleTextAttribute(hConsole, 480);           //Yellow Color Code=480
            cout<<"Press Any Key To Continue...";
       }
       //Welcome Screen
       void welcomeScreen () {
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            system("cls");
            SetConsoleTextAttribute(hConsole, 480);        //Yellow Color Code=480
            gotoxy(7,0);
            cout<<"   NATIONAL  UNIVERSITY  OF  COMPUTER  AND  EMERGING  SCIENCES   "; 
            cout<<"\n";
            SetConsoleTextAttribute(hConsole, 47);     //Green & White Color Code=47
            gotoxy(19,1);
            cout<<"      A Snake Game in OOP using C++      "; 
            SetConsoleTextAttribute(hConsole, 8);             //Gray Color Code=8
            for (int i=6; i<14; i++) {
                gotoxy(38,i);
                cout<<'\xB3';
            }
            gotoxy(28,3);
            SetConsoleTextAttribute(hConsole, 27);             //Blue Color Code=27
            cout<<"  Semester Project  ";
            SetConsoleTextAttribute(hConsole, 12);           //Red Color Code=12
            gotoxy(1,6);
            cout<<"Submitted By: ";
            gotoxy(40,6);
            cout<<"Submitted To: ";
            SetConsoleTextAttribute(hConsole, 12);          //Light Red Color Code=12
             // displays Bold in bold
            gotoxy(48,10);
            cout << "Mr. Muhammad Tehseen Khan" <<endl;
            gotoxy(47,11);
            cout <<"---------------------------";
            gotoxy(47,9);
            cout <<"---------------------------";

            
            SetConsoleTextAttribute(hConsole, 3);           //Dark Blue-Green Color Code=3
            gotoxy(8,8);
            cout<<"Furqan Amin";
            SetConsoleTextAttribute(hConsole, 6);            //Dark Yellow Color Code=6
            gotoxy(27,8);
            cout<<"P18-0069";
            SetConsoleTextAttribute(hConsole, 15);            //White Color Code=15
            gotoxy(47,8);
            SetConsoleTextAttribute(hConsole, 3);              //Dark Blue Color Code=3
            gotoxy(8,10);
            cout<<"Muhammad Nouman";
            SetConsoleTextAttribute(hConsole, 6);            //Dark Yellow Color Code=6
            gotoxy(27,10);
            cout<<"P17-6156";
            
            SetConsoleTextAttribute(hConsole, 8);            //Dark Yellow Color Code=8
            for (int i=0; i<79; i++) {
                gotoxy(i,14);
                cout<<'\xC4';
            }
            SetConsoleTextAttribute(hConsole, 8);            //Dark Yellow Color Code=8
            for (int i=0; i<79; i++) {
                gotoxy(i,5);
                cout<<'\xC4';
            }
            gotoxy(38,14);
            cout<<'\xC1';
            gotoxy(38,5);
            cout<<'\xC2';
            SetConsoleTextAttribute(hConsole, 13);             //Pink Color Code=13
            gotoxy(31,15);
            cout<<"<Game Options>";
            SetConsoleTextAttribute(hConsole, 15);             //White Color Code=15
            gotoxy(2,17);
            cout<<"1: ";
            SetConsoleTextAttribute(hConsole, 2);             //blue-Green Color Code=3
            gotoxy(5,17);
            cout<<"Play New Single Player Game";
            SetConsoleTextAttribute(hConsole, 15);             //White Color Code=15
            gotoxy(2,18);
            cout<<"2: ";
            SetConsoleTextAttribute(hConsole, 2);             //blue-Green Color Code=3
            gotoxy(5,18);
            cout<<"Play Saved Single Player Game";
            SetConsoleTextAttribute(hConsole, 8);             //Gray Color Code=8
            gotoxy(43,18);
            cout<<'\xDA'<<'\xC4';
            for (int i=0; i<29; i++)
                cout<<'\xC4';
            cout<<'\xBF';
            gotoxy(43,19);
            cout<<'\xB3';
            gotoxy(43,20);
            cout<<'\xC0'<<'\xC4';
            for (int i=0; i<29; i++)
                cout<<'\xC4';
            cout<<'\xD9';
            SetConsoleTextAttribute(hConsole, 15);             //White Color Code=12
            gotoxy(45,19);
            cout<<"Note: ";
            SetConsoleTextAttribute(hConsole, 10);             //Green Color Code=10
            cout<<"To Save Game, Press 'S'";
            SetConsoleTextAttribute(hConsole, 8);             //Gray Color Code=8
            cout<<'\xB3';
            SetConsoleTextAttribute(hConsole, 15);             //White Color Code=15
            gotoxy(2,19);
            cout<<"3: ";
            SetConsoleTextAttribute(hConsole, 2);             //blue-Green Color Code=3
            gotoxy(5,19);
            cout<<"High Score Table";
            SetConsoleTextAttribute(hConsole, 15);             //White Color Code=15
            gotoxy(2,20);
            cout<<"4: ";
            SetConsoleTextAttribute(hConsole, 2);             //blue-Green Color Code=3
            gotoxy(5,20);
            cout<<"Exit the Game\n\n";
            SetConsoleTextAttribute(hConsole, 15);             //White Color Code=15
            gotoxy(2,21);
            
                   
            gotoxy(5,22);
            
            SetConsoleTextAttribute(hConsole, 7);             //Light White Color Code=7
            cout<<"Press Any Number to Play: ";
       }														//End of welcome screen
       
       
       
       //Print Exception for Single Player
       char* what (char key) {
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            char* temp;
            SetConsoleTextAttribute(hConsole, 6);             //Light Green Color Code=2
            gotoxy(44,21);
            if (key==kiDown) { temp="Down        "; }
            else if (key==kiUp) { temp="Up          "; }
            else if (key==kiLeft) { temp="Left        "; }
            else if (key==kiRight) { temp="Right       "; }
            else if (key==83 || key==115) { temp="Game Saved!"; iSignal=1;}
            else if (key=='~') { temp="            "; }
            return temp;
       }
       //Show Time for Single Player1
       void showTime (int a) 
       {
            if (a<10) 
            {
               gotoxy(74,21);
               cout<<" ";
            }
            gotoxy(73,21);
            cout<<a;
       }
       //Hide Time for Single Player
       void hideTime () 
       {
            for (int a=0; a<3; a++) 
            {
               gotoxy(a+73,21);
               cout<<" ";
            }
       }
       
};
//============================= Food Class =============================//
class CFood: public CLocation
{
public:
       CLocation qEatMe;
       void generateFood() 
       {
            time_t t;
            srand(time(&t));           //srand(int) seed the random number with the time
            const int MAX_x=73;
            const int MAX_y=16; 
            x =(rand() % MAX_x)+3;
            y =(rand() % MAX_y)+2;
            gotoxy(x,y);
            cout<<'\x1';					// change normal food
            qEatMe.set(x,y);
       }
};
//============================== Big Food ===============================//
class CBigFood: public CLocation 
{
public:
       CLocation qEatBigFood;
       void generateBigFood() 
       {
            time_t t1;
            srand(time(&t1));           //srand(int) seed the random number with the time
            const int max_x=73;
            const int max_y=15; 
            x =(rand() % max_x)+4;
            y =(rand() % max_y)+3;
            gotoxy(x,y);
            cout<<'\x5';				//change special food
            qEatBigFood.set(x,y);
       }
};
//============================== User Snake =============================//
class CSnake: public CLocation
{
public:
       int iScore;
       int iLength;
       char cDir;
       CLocation qaLoc[100];
       //No-Orgument Constructor for Single Player
       CSnake () 
       {
             iLength=5;
             iScore=0;
             cDir=kiRight;
             qaLoc[0].set(15,10);
             qaLoc[1].set(14,10);
             qaLoc[2].set(13,10);
             qaLoc[3].set(12,10);
             qaLoc[4].set(11,10);
             qaLoc[5].set(10,10);
       }
       
       //One-Orgument Constructor for Operator Overloading ++
       CSnake (int l) {
             iLength=l;
       }
       //Show Snake Function
       void show()
       {
             for(int a=0; a<iLength; a++)
                qaLoc[a].show(a);
                qaLoc[iLength].hide();
       }
       //Moving Left any snake
       void left()
       {
            for(int b=iLength; b>0; b--)
             {
                qaLoc[b].x=qaLoc[b-1].x;
                qaLoc[b].y=qaLoc[b-1].y;
             }
             qaLoc[0].x--;
       }
       //Moving Right  any snake
       void right()
       {
            for(int b=iLength; b>0; b--)
             {
                qaLoc[b].x=qaLoc[b-1].x;
                qaLoc[b].y=qaLoc[b-1].y;
             }
             qaLoc[0].x++;
       }
       //Moving Down any snake
       void down()
       {
             for(int c=iLength; c>0; c--)
             {
                qaLoc[c].x=qaLoc[c-1].x;
                qaLoc[c].y=qaLoc[c-1].y;
             }
             qaLoc[0].y++;
       }
       //Moving Up any snake
       void up()
       {
             for(int c=iLength; c>0; c--)
             {
                qaLoc[c].y=qaLoc[c-1].y;
                qaLoc[c].x=qaLoc[c-1].x;
             }
             qaLoc[0].y--;
       }
       //Print Score any snake
       void printScore (int x0, int y0) 
       {
            gotoxy(x0,y0);
            cout<<iScore;
       }
       //Unary Operator ++
       CSnake operator++(int);
};
//============================ Unary Operator ++ ==========================//
CSnake CSnake::operator++(int) {
      CSnake temp(iLength);
      iLength++;
      iScore+=10;					//change normal food score
      return temp;
} 

//============================= High Score Class =========================//
class highScore {  
      public:
             char name[15];          //Player's Name
             int score;              //Player's Score
             //Initializing Variables
             void setData() {
                  char array[15]="No Name";
                         for (int i=0; i<15; i++) {
                             name[i]=array[i];
                         }
                         score=0;
             }
             //Getting Name from User
             void getData() {
                  cout<<"Name: ";
                  cin>>name;
             }
             //Printing Rank, Name & Score
             void printData(int dd) {
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  gotoxy(17,dd+7);
                  SetConsoleTextAttribute(hConsole, 15);  //White Color Code=15
                  cout<<dd+1;
                  gotoxy(26,dd+7);
                  SetConsoleTextAttribute(hConsole, 2);  //Light Green Color Code=2
                  cout<<name;
                  gotoxy(47,dd+7);
                  SetConsoleTextAttribute(hConsole, 3);   //Light Blue Color Code=3
                  cout<<score;
                  SetConsoleTextAttribute(hConsole, 7);   //Light White Color Code=7
             }
             //Operator Overloading = for equality
             highScore operator=(highScore);
};
//==================== Operator = Overloading ===============================//
highScore highScore::operator =(highScore hh) {
          score=hh.score;
          for (int i=0; i<15; i++) {
              name[i]=hh.name[i];
          }
}
//==================== High Score Table Class ==============================//
class highScoreTable {
      public:
             highScore hs[100];         //High Score table of 100 Records
             int countScore;            //Count Total Number of Entered Records
             //Zero-Orgument Constructor
             highScoreTable() {
                for (int i=0; i<100; i++) {
                    hs[i].setData();
                }
                countScore=0;
             }
             //One-Orgument Constructor
             highScoreTable(int hst) {
                countScore=hst;
             }
             //Printing High Score Table of Top 15 Records
             void printTableShape() {
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  system("cls");
                  SetConsoleTextAttribute(hConsole, 480);        //Yellow Color Code=480
                  gotoxy(25,0);
                  cout<<"   High Score Table   "; 
                  cout<<"\n";
                  SetConsoleTextAttribute(hConsole, 47);     //Green & White Color Code=47
                  gotoxy(21,1);
                  cout<<"      Top Fifteen Scores      "; 
                  SetConsoleTextAttribute(hConsole, 8);             //Gray Color Code=8
                  gotoxy(15,4);
                  cout<<'\xDA';
                  for (int i=16; i<57; i++) {                //First Line 15
                      gotoxy(i,4);                           //Middle Line 39
                      cout<<'\xC4';                          //Last Line 57
                  }                                          //Second Line 20
                  cout<<'\xBF';
                  gotoxy(20,4); cout<<'\xC2';
                  gotoxy(39,4); cout<<'\xC2';
                  gotoxy(15,5); cout<<'\xB3';
                  gotoxy(20,5); cout<<'\xB3';
                  gotoxy(39,5); cout<<'\xB3';
                  gotoxy(57,5); cout<<'\xB3';
                  gotoxy(15,6); cout<<'\xC3';
                  for (int i=16; i<57; i++) {                
                      gotoxy(i,6);                           
                      cout<<'\xC4';                          
                  }
                  gotoxy(39,6); cout<<'\xC5';
                  gotoxy(20,6); cout<<'\xC5';
                  gotoxy(57,6); cout<<'\xB4';
                  for (int i=7; i<23; i++) {
                      gotoxy(15,i); cout<<'\xB3';
                      gotoxy(20,i); cout<<'\xB3';
                      gotoxy(39,i); cout<<'\xB3';
                      gotoxy(57,i); cout<<'\xB3';
                  }
                  gotoxy(15,22); cout<<'\xC0';
                  for (int i=16; i<57; i++) {                
                      gotoxy(i,22);                           
                      cout<<'\xC4';                          
                  }
                  gotoxy(39,22); cout<<'\xC1';
                  gotoxy(20,22); cout<<'\xC1';
                  gotoxy(57,22); cout<<'\xD9';
                  SetConsoleTextAttribute(hConsole, 14);    //Yellow Color Code=14
                  gotoxy(28,5); cout<<"Name";
                  gotoxy(46,5); cout<<"Score";
                  gotoxy(17,5); cout<<"S#";
             }
             //Operator Overloading ++ for Adding Score
             highScoreTable operator++(int); 
};
//=============== Unary Operator ++ For High Scores =================//
highScoreTable highScoreTable::operator++(int) {
      highScoreTable temp(countScore);
      countScore++;
      return temp;
}
//==================== Swap Function for Sorting =======================//
void swapScore(highScore &h1, highScore &h2) {
     if (h1.score > h2.score) {         //If First score is greater than
         highScore temp;                //second score, swap scores
         temp=h1;
         h1=h2;
         h2=temp;
     }
}
//=============================== Main Function ===========================//
void functionality () 
{
    //Making some useful variables
    highScore tempScore;
    highScoreTable myTable;
    char choice;             //User's choice to choose game from welcome screen
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);               //For Color
    CBoundary b;
    //Welcome Screen
    b.welcomeScreen();
    
    
    choice=getch();
    
    do {
        CSnake s1;             //Player Snake
        CFood f1;              //Simple Food
        CBigFood g1;           //Special Food
        //Making Some Useful Variables
        bool hit=0, available=0, user=0, welcome=0, esc=0;
        int count=0, temp=50, min=1, sec=59, timer=0;

        
//___________________________Single Player Game_____________________________________//
    if (choice=='1')
    {               //START OF SINGLE PLAYER GAME              
SINGLE_PLAYER_GAME:
          hit=0, available=0, user=0, welcome=0, esc=0;
          count=0, temp=50;           //Initializing Variables
          system("cls");
          //User Boundary
          b.setLeftBoundary();
          b.setRightBoundary();
          b.setDownBoundary();
          b.setUpBoundary();
          b.showSingleBoundary();
          //User Snake
          SetConsoleTextAttribute(hConsole, 10);                    //Green Color Code = 10     //colour of snake
          s1.show();
          s1.printScore(14,21);                                     //Showing Score
          //Food System
          SetConsoleTextAttribute(hConsole, 13);                    //Purple Color Code = 13
          f1.generateFood();                                        //Showing Food
          getch();                                                 //Ready to Play
          
          while (true) 
          {                  //START OF WHILE LOOP
             //User Snake Control Switch
             switch (s1.cDir)
             {
                 case kiDown:
                      s1.down();
                      break;
                 case kiLeft:
                      s1.left();
                      break;
                 case kiRight:
                      s1.right();
                      break;
                 case kiUp:
                      s1.up();
                      break;
             }
             SetConsoleTextAttribute(hConsole, 10);         //colour of snake              //Green Color Code = 10
             s1.show();
             Sleep(110);                                   //speed of snake
             try {      //Start Of Try
                 while (kbhit())                     //If User Pressed Any Key
                 {                                //Get That Key & Check it
                     cDoThis=getch();
                     if (cDoThis==kiUp || cDoThis==kiRight || cDoThis==kiDown || cDoThis==kiLeft) {
                        cTempDir=cDoThis;
                     }
                 }
                 //User Snake is Going Down, chance of left or right 
                 if(cTempDir==kiLeft && s1.cDir==kiDown) {  s1.cDir=kiLeft; throw cTempDir; }
                 if(cTempDir==kiRight && s1.cDir==kiDown) {  s1.cDir=kiRight; throw cTempDir; }
                 //User Snake Going Left, chance of up or down
                 if(cTempDir==kiDown && s1.cDir==kiLeft) {  s1.cDir=kiDown; throw cTempDir; }
                 if(cTempDir==kiUp && s1.cDir==kiLeft) {  s1.cDir=kiUp; throw cTempDir; }
                 //User Snake Going Up, chance of right or left
                 if(cTempDir==kiLeft && s1.cDir==kiUp) {  s1.cDir=kiLeft; throw cTempDir; }
                 if(cTempDir==kiRight && s1.cDir==kiUp) {  s1.cDir=kiRight; throw cTempDir; }
                 //User Snake Going Right, chance of up or down
                 if(cTempDir==kiUp && s1.cDir==kiRight) {  s1.cDir=kiUp; throw cTempDir; }
                 if(cTempDir==kiDown && s1.cDir==kiRight) {  s1.cDir=kiDown; throw cTempDir; }
                 if(cDoThis==kiEscape) { welcome=1; break; }
                 if(cDoThis=='s' || cDoThis=='S')  
                 {
          //============================Save File Single Player======================
                     //Saving Snake
                     ofstream outfile("Snake1.txt",ios::binary);
                     if( !outfile.good() )  {
                         cout<<"File could not be opened";    
                     }
                     outfile.write( reinterpret_cast<char*>(&s1), sizeof(s1) );
                     outfile.close();
                     throw cDoThis;
                 }
             }           //End of Try
             catch (char d) {                //Catch the Key Pressed by Player
                   cout<<b.what(d);          //Tell Which key is pressed?
                   if(b.iSignal==1) {        //If That is 's', then
                      b.iSignal=0;
                      cDoThis='~';
                      getch();              //Stop the Game
                   }
             }     
             //Checking Boundaries for User
             //Collision with Upper Horizontal Boundary for User
             for (int i=0; i<b.iHori; i++) {
              if(s1.qaLoc[0]==b.qpUpBound[i]) {  hit=1; user=0; break; }    //Break for loop
             } 
             if (hit==1) { break; }           //Break while loop
             //Collision with Right Vertical Boundary for User
             for (int i=0; i<b.iVirt; i++) {
               if(s1.qaLoc[0]==b.qpRightBound[i]) {  hit=1; user=0; break;}
             } 
             if (hit==1) { break; }
             //Collision with Lower Horizontal Boundary for User
             for (int i=0; i<b.iHori; i++) {
              if(s1.qaLoc[0]==b.qpDownBound[i]) {  hit=1; user=0; break; }
             } 
             if (hit==1) { break; }
             //Collision with Left Vertical Boundary for User
             for (int i=0; i<b.iVirt; i++) { 
              if(s1.qaLoc[0]==b.qpLeftBound[i]) {  hit=1; user=0; break; }
             }
             //Self Collision for User
             for (int i=1; i<s1.iLength; i++) {
              if (s1.qaLoc[0] == s1.qaLoc[i]) { hit=1; user=0; break; }
             }
             if (hit==1) { break; }
             //Eating Food for User
             if (s1.qaLoc[0] == f1.qEatMe )   //Snake has eaten food or not
             {
              s1++;          //Add 1 Unit to length
              if (s1.iLength==99) {
                 esc=1;           
                 break;
              }
              SetConsoleTextAttribute(hConsole, 13);                    //Purple Color Code = 13    //change normal food colour
              f1.generateFood();                //Generate New Food
              SetConsoleTextAttribute(hConsole, 268);                    //Red Color Code = 268		//change special food colour
              s1.printScore(14,21);             //Print New Score
              count++;
              //If snake has eaten five simple foods, generate a special food
              if (count==5) { g1.generateBigFood(); available=1; count=0; }
             }
             //Showing Big Food for User
             if (available == 1) 
             {
              SetConsoleTextAttribute(hConsole, 268);                    //Red Color Code = 268
              b.showTime(temp);                            //Show Time for Special Food
              temp--;
              if (temp==0)                                 //If time has ended,
              {
                 g1.hide();                                //Hide food
                 b.hideTime();
                 available=0;
                 temp=50;                               
              }
             }
             //Eating Big Food for Users
             if (s1.qaLoc[0] == g1.qEatBigFood )      //snake has eaten big food or not??
             {
                        
                s1.iScore = s1.iScore + 20;    //Add score  //add special food score
                s1.printScore(14,21);               //Print score
                b.hideTime();                       
                available=0;
                temp=50;
             }
             //If new food is generated on body of user snake, 
             //then clear it and genrate new food
             for (int j=1; j<s1.iLength; j++) 
             {
                 if (f1.qEatMe == s1.qaLoc[j]) { f1.generateFood();  }
             }
          }           //END OF WHILE LOOP
          //Checking Which Screen to be Displayed
          if (hit==1) {              //If Snake has been collided with anything
             Sleep(1200);
             system("cls");
             b.gameOverScreen();
             gotoxy(35,12); 
             SetConsoleTextAttribute(hConsole, 12);                    //Red Color Code = 12
             cout<<"Game Over!"; 
             gotoxy(33,13); 
             SetConsoleTextAttribute(hConsole, 10);                    //Green Color Code = 10
             cout<<"Your Score:  "<<s1.iScore;
             SetConsoleTextAttribute(hConsole, 3);                //Green-Blue Color Code = 3
             gotoxy(33,15);
             tempScore.getData();              //Get Name
             tempScore.score=s1.iScore;         //Save Score
             myTable.hs[myTable.countScore]=tempScore;     //Send that record to array of records
             myTable++;
             for (int i=0; i<100; i++) {
                 for (int j=0; j<100; j++) {               //Sort the array
                     swapScore(myTable.hs[i],myTable.hs[j]);
                 }
             }
             //Saving High Score to File
             ofstream scorefile("HighScore.txt",ios::binary);
             if( !scorefile.good() )  {
                 cout<<"File could not be opened";    
             }
             scorefile.write( reinterpret_cast<char*>(&myTable), sizeof(highScoreTable) );
             scorefile.close();
             gotoxy(30,23);
             Sleep(500);
             getch();
          }
          else if (esc==1) {
                  esc=0;
                  Sleep(800);
                  system("cls");
                  b.gameOverScreen();
                  gotoxy(31,9); 
                  SetConsoleTextAttribute(hConsole, 10);                    //Green Color Code = 10
                  cout<<"Congratulations!";
                  gotoxy(20,11);
                  SetConsoleTextAttribute(hConsole, 13);                    //Purple Color Code = 13
                  cout<<"You Reached to Maximum Length of Snake!";
                  gotoxy(33,13); 
                  SetConsoleTextAttribute(hConsole, 10);                    //Green Color Code = 10
                  cout<<"Your Score:  "<<s1.iScore;
                  highScore tempScore;
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  SetConsoleTextAttribute(hConsole, 3);                //Green-Blue Color Code = 3
                  gotoxy(31,15);
                  tempScore.getData();              //Get Name
                  tempScore.score=s1.iScore;         //Save Score
                  myTable.hs[myTable.countScore]=tempScore;    //Add record to array of records
                  myTable.countScore++;
                  for (int i=0; i<10; i++) {
                      for (int j=0; j<10; j++) {               //Sort the array
                          swapScore(myTable.hs[i],myTable.hs[j]);
                      }
                  }
                  //Saving High Score to File
                  ofstream scorefile("HighScore.txt",ios::binary);
                  if( !scorefile.good() )  {
                      cout<<"File could not be opened";    
                  }
                  scorefile.write( reinterpret_cast<char*>(&myTable), sizeof(myTable) );
                  scorefile.close();
                  gotoxy(30,23);
                  Sleep(500);
          }
          system("cls");
      }                    //END OF SINGLE PLAYER GAME
    
//_______________________Play Saved Single Player Game_________________________________//
      else if (choice=='2')
      {
        //Loading User Snake for Single Player Game
        ifstream infile("snake1.txt", ios::binary);
		infile.read( reinterpret_cast<char*>(&s1), sizeof(s1) ); 
        goto SINGLE_PLAYER_GAME;              //Start Game
      }
  
//___________________________________Show High Score Table______________________________//
    else if (choice=='3') {
         //Loading High Scores from File
         ifstream inScorefile("HighScore.txt", ios::binary);
         inScorefile.read( reinterpret_cast<char*>(&myTable), sizeof(myTable) );
         system("cls");
         myTable.printTableShape();
         for (int i=0; i<15; i++) {
             myTable.hs[i].printData(i);
         }
         gotoxy(1,24);
         cout<<"Press Any Key to Continue...";
         getch();
    }
//_____________________________________Exit the Game____________________________________//                         
    else if (choice=='4') {
         exit(1);
    }
    b.welcomeScreen();
    choice=getch();
    } while(choice!='4');
}            //END OF MAIN FUNCTION




