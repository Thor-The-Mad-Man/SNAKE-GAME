// This game runs on platforms that support graphics.h header file
// random() and randomize() functions are only available Borland compliers 
// Like Turbo C++
// It is recommended that Turbo C++ is used to run this program
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>

void check();
void end();

int m[500],n[500],food=20;

int main()
{
int gd=DETECT,gm,click,maxx,maxy,x=13,y=14,X_Ori,Y_Ori,spd=150,temp;
int prev,i,j;

initgraph(&gd,&gm,"C:/TURBOC3/BGI");
setcolor(WHITE);
settextstyle(4,0,7);
outtextxy(200,2," SNAKE ");
settextstyle(6,0,2);
outtextxy(30,80," USE ARROW KEYS TO DIRECT THE SNAKE ");
outtextxy(30,140," AVOID THE HEAD OF THE SNAKE TO TOUCH ITS TAIL");
outtextxy(30,180," PRESS 'ESC' KEY TO EXIT ANYTIME ");
outtextxy(30,200," PRESS ANY KEY TO CONTINUE ");
click=getch();

//Exiting on pressing ESC key
if(click==27)
    exit(0);

cleardevice();
maxx=getmaxx();//Getting maximum value of x on the screen
maxy=getmaxy();//Getting maximum value of y on the screen

//Generating random values
randomize();
X_Ori=random(maxx);
temp=X_Ori%13;
X_Ori=X_Ori-temp;
Y_Ori=random(maxy);
temp=Y_Ori%14;
Y_Ori=Y_Ori-temp;
prev=0;
i=0;

while(1)
{
setcolor(WHITE);
setfillstyle(SOLID_FILL,food+5);
circle(X_Ori,Y_Ori,5);
floodfill(X_Ori,Y_Ori,WHITE);

//Waiting for keypress
if( kbhit() )
{
     click=getch();
     if(click==0)
	 click=getch();
//Checking for the arrow key pressed and its previous direction
     if(click==72&& prev!=2)
	 prev=1;
     if(click==80&& prev!=1)
	 prev=2;
     if(click==75&& prev!=4)
	prev=3;
     if(click==77&& prev!=3)
	prev=4;
     }
       else
     {
     if(click==27)
	break;
     }
    if(i<20)
    {
	m[i]=x;
	n[i]=y;
	i++;
    }
    if(i>=20)
    {
	//Snake movement
	for(j=food;j>=0;j--)
	{
	    m[j+1]=m[j];
	    n[j+1]=n[j];
	}

    m[0]=x;
    n[0]=y;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,food);
    circle(m[0],n[0],8);
    floodfill(m[0],n[0],WHITE);
    setcolor(WHITE);

    for(j=1;j<food;j++)
    {
    setfillstyle(SOLID_FILL,food+j%3);
    circle(m[j],n[j],5);
    floodfill(m[j],n[j],WHITE);
    }

    delay(spd);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    circle(m[0],n[0],8);
    floodfill(m[0],n[0],BLACK);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    circle(m[j],n[j],5);
    floodfill(m[j],n[j],BLACK);
    }
    check();
    if(x==X_Ori&&y==Y_Ori)
    {
    food=food+5;
    if(spd>=15)
	spd=spd-5;
    else
	spd=15;
     X_Ori=random(maxx);
     temp=X_Ori%13;
     X_Ori=X_Ori-temp;
     Y_Ori=random(maxy);
     temp=Y_Ori%14;
     Y_Ori=Y_Ori-temp;
    }
	
    //Handling boundary conditions
    if(prev==1)
	y=y-14;
    if(y<0)
    {
	temp=maxy%14;
	y=maxy-temp;
    }
    if(prev==2)
	y=y+14;
    if(y>maxy)
	y=0;
    if(prev==3)
	x=x-13;
    if(x<0)
    {
	temp=maxx%13;
	x=maxx-temp;
    }
    if(prev==4)
	x=x+13;
    if(x>maxx)
	x=0;
    if(prev==0)
    {
	y=y+14 ;
	x=x+13;
    }
    }
    return 0;
 }
void check()
{
   int a;
   for(a=1;a<food;a++)
   if(m[0]==m[a] && n[0]==n[a])
       end();
   else
       continue;
   }
void end()
{
   int j,i;
   setcolor(WHITE);
   for(i=0;i<5;i++)
   {
	delay(500);
	cleardevice();
	delay(500);
	for(j=0;j<=food;j++)
	{
	    setfillstyle(SOLID_FILL,RED);
	    circle(m[j],n[j],5);
	    floodfill(m[j],n[j],WHITE);
	}
   }
    settextstyle(3,0,4);
    outtextxy(150,150,"    GAME OVER ");
    printf("SCORE:%d",food-20);
    delay(5000);
    exit(0);
}
