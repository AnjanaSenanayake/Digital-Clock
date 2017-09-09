/***************************************************************************************
*    Title: Mini Project1-Digital clock 
*    Author: Anjana Senanayake
*    Date: Feb/2016  
*    Code version: v1.0
*    Availability: https://github.com/AnjanaSenanayake/Digital-Clock
*
***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <signal.h>

#define RESET       0
#define BRIGHT      1

#define DEFAULT     -40
#define BLACK       0
#define RED         1
#define GREEN       2
#define YELLOW      3
#define BLUE        4
#define MAGENTA     5
#define CYAN        6
#define WHITE       7

int COLOR=7;

//Function prototypes
void textcolor(int attr, int fg, int bg);
int getcolor(char* digitcolor);
int timeHour();
int timeMins();
int timeSec();
int dateYear();
int dateMonth();
int dateDay();
void delay(int milliseconds);
void colon(int yaxis,int xaxis);
void digitPrint(int digit,int yaxis,int xaxis);
void sigintHandler(int sig_num);

int main(int argc,char** argv)
{
	system("stty -echo"); //Turn off the system echoes
	printf("\033[?47h");  //Saves the terminal screen, before the program executes
	if(argc>1)
	{	
		//Error or warning messages
		if((strcmp(argv[1],"-C")==0) && argc==2)
		{
			printf("./prog: option requires an argument -- 'C'\nusage : clock -C <black|red|green|yellow|blue|magenta|cyan|white]\n");
			system("stty echo");
			exit(0);
		}	
		else if((strcmp(argv[1],"-C")==0) && getcolor(argv[2])!=-1)
		{	
			COLOR=getcolor(argv[2]);
		}
		else if((strcmp(argv[1],"-C")==0) && getcolor(argv[2])==-1)
		{
			printf(" '%s' :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n",argv[2]);
			system("stty echo");
			exit(0);
		}	
		else if((strcmp(argv[1],"-h")==0) || (strcmp(argv[1],"-c")==0))	
		{
			printf("usage : clock -C <black|red|green|yellow|blue|magenta|cyan|white]\n");
			system("stty echo");
			exit(0);
		}
		else if((strcmp(argv[1],"-H")==0) && argc==2)
		{
			printf("./prog: invalid option -- 'H'\nusage : clock -C <black|red|green|yellow|blue|magenta|cyan|white]\n");
			system("stty echo");
			exit(0);
		}		
	}		
	else
	{
		COLOR=WHITE;
	}			
	for(;;)
	{
		signal(SIGINT, sigintHandler);	   //The function captures the termination signal
		int i,j,k;
		int hour1=timeHour()/10;           //Hour,Min & Seconds are seperated digitwise 
		int hour2=timeHour()%10;
		int min1=timeMins()/10;
		int min2=timeMins()%10;
		int sec1=timeSec()/10;
		int sec2=timeSec()%10;
		delay(60);					       //A delay of about 60 ms is used to balance the time difference of 
		//for(i=0;i<22000000;i++);		   //command execution and printing.
		//printf("\033c");				   //Clears the terminal screen(Not essential)	
		printf("\033[?25l"); 			   //Hides the cursor
		printf("\033[H\033[J");			   //Resets the terminal screen						
		digitPrint(hour1,2,2);			   //Prints hour
		digitPrint(hour2,2,9);
		colon(2,15);					   //Prints mins
		digitPrint(min1,2,21);
		digitPrint(min2,2,28);
		colon(2,34);	
		digitPrint(sec1,2,40);			   //Prints seconds
		digitPrint(sec2,2,47);
		printf("\033[8;23H");			   //Sets cursor position
		textcolor(RESET,COLOR,-30);		   //Sets textcolor to print date
		printf("%d-%02d-%02d\n",1900+dateYear(),1+dateMonth(),dateDay());//Prints date			
	}
	textcolor(RESET,WHITE,DEFAULT);
	return 0;
}
//A Reset handler to catch SIGINT next time
/* Refered from http://en.cppreference.com/w/c/program/signal */
void sigintHandler(int sig_num)
{
	system("stty echo");					//System echoe is back on					
    signal(SIGINT, sigintHandler);
    printf("\b\b");
    printf("\033[?25h");                    //Cursor is visible back again
    printf("\033[H\033[J");
    textcolor(RESET,WHITE,DEFAULT);
    printf("\033[?47l");					//Restore the screen before program is executed
    exit(0);
}

//A function to change the textcolor and background color
void textcolor(int attr, int fg, int bg)
{   char command[13];

    /* Command is the control command to the terminal */

    /* textcolor(BRIGHT,BLACK,WHITE) will have characters printed in
    black in white background */
    sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

//A function to sort the required color    
int getcolor(char* digitcolor)
{   
 	char* color[8]={"black","red","green","yellow","blue","magenta","cyan","white"};//An array to compare the the input colors
 	int i;
 	for(i=0;i<8;i++)
 	{
 		if(strcmp(digitcolor,color[i])==0)
 			return i;
 	}
 	return -1;
}

//A function to get the hour only from localtime
int timeHour()
{
	time_t t;
	struct tm *t_tm;
	int hour;
	t = time(NULL);
	t_tm = localtime(&t);
	hour = t_tm->tm_hour;;
	return hour;
}

//A function to get the minutes only from localtime
int timeMins()
{
	time_t t;
	struct tm *t_tm;
	int mins;
	t = time(NULL);
	t_tm = localtime(&t);
	mins = t_tm->tm_min;;

	return mins;
}

//A function to get the seconds only from localtime
int timeSec()
{
	time_t t;
	struct tm *t_tm;
	int sec;
	t = time(NULL);
	t_tm = localtime(&t);
	sec	= t_tm->tm_sec;;
	return sec;
}

//A function to get the year only from localtime
int dateYear()
{
	time_t t;
	struct tm *t_tm;
	int year;
	t = time(NULL);
	t_tm = localtime(&t);
	year = t_tm->tm_year;;
	return year;
}

//A function to get the month only from localtime
int dateMonth()
{
	time_t t;
	struct tm *t_tm;
	int mon;
	t = time(NULL);
	t_tm = localtime(&t);
	mon	= t_tm->tm_mon;;
	return mon;
}

//A function to get the date only from localtime
int dateDay()
{
	time_t t;
	struct tm *t_tm;
	int day;
	t = time(NULL);
	t_tm = localtime(&t);
	day	= t_tm->tm_mday;;
	return day;
}

//A function to create a delay using a while loop
void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

//Prints colon character ':'
void colon(int yaxis,int xaxis)
{
	int colonarray[5][6]=
	{ 
		{0,0,0,0,0,0} ,   
	    {0,0,1,1,0,0} ,
		{0,0,0,0,0,0} ,
		{0,0,1,1,0,0} ,
		{0,0,0,0,0,0} 
	};

	int i,j;
	for(i=0;i<5;i++)
	{
		for(j=0;j<6;j++)
		{
			if(colonarray[i][j]==1)
			{	
				printf("\033[%d;%dH",yaxis+i,xaxis+j);
				textcolor(RESET,RESET,COLOR);
				printf(" ");
			}
			else
			{
				textcolor(RESET,RESET,DEFAULT);
				printf(" ");
			}
		}
	}
}

//Prints digits from 0 t0 9
void digitPrint(int digit,int yaxis,int xaxis)
{
	int numset[10][6][6] ={
	{ 
		{1,1,1,1,1,1} ,    //digit 0
	    {1,1,0,0,1,1} ,
		{1,1,0,0,1,1} ,
		{1,1,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,0,0} 
	},
	{ 
		{0,0,0,0,1,1} ,    //digit 1
	    {0,0,0,0,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,0,0} 
	},
	{ 
		{1,1,1,1,1,1} ,	   //digit 2
	    {0,0,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{1,1,0,0,0,0} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,0,0} 
	},
	{ 
		{1,1,1,1,1,1} ,	   //digit 3
	    {0,0,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,0,0} 
	},
	{ 
		{1,1,0,0,1,1} ,    //digit 4
	    {1,1,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1} ,
		(0,0,0,0,0,0)
	},
	{ 
		{1,1,1,1,1,1} ,    //digit 5
	    {1,1,0,0,0,0} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,0,0}
	},
	{ 
		{1,1,1,1,1,1} ,    //digit 6
	    {1,1,0,0,0,0} ,
		{1,1,1,1,1,1} ,
		{1,1,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,0,0}
	},
	{ 
		{1,1,1,1,1,1} ,    //digit 7
	    {0,0,0,0,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,0,0}
	},
	{ 
		{1,1,1,1,1,1} ,    //digit 8
	    {1,1,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{1,1,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,0,0}
	},
	{ 
		{1,1,1,1,1,1} ,    //digit 9
	    {1,1,0,0,1,1} ,
		{1,1,1,1,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,1,1} ,
		{0,0,0,0,0,0}
	},
	};

	int i,j;
	for(i=0;i<6;i++)
	{
		for(j=0;j<6;j++)
		{	
			if(numset[digit][i][j]==1)
			{	
				printf("\033[%d;%dH",yaxis+i,xaxis+j);
				textcolor(RESET,RESET,COLOR);
				printf(" ");
			}
			else
			{
				printf("\033[%d;%dH",yaxis+i,xaxis+j);
				textcolor(RESET,RESET,DEFAULT);
				printf(" ");
			}
		}	
	}
}