
# include "iGraphics.h"
# include "gl.h"

///makes point for both ball and rectangle
typedef struct
{
    double x;
    double y;
    double dx;
    double dy;
    int color[3];
}point;

point ball,rect1,rect2;
double T=0; ///intial angle of ball movement
double radius; ///ball radius
///for arrow head
double tri_x[3],tri_y[3]; ///three point of trigle
double mid_x,mid_y; ///intersection point of line and tringle

int ball_speed=15;
int color_cnt=0; ///for changing the color between ball and box

void initial()
{
    ball.dx =2.99;
	ball.dy = 3;

    ///intalizing ball and box color
    ball.color[0]=255,ball.color[1]=0,ball.color[2]=0;
    rect1.color[0]=0,rect1.color[1]=255,rect1.color[2]=255; ///200

    ///rectangle one
    rect1.x=35,rect1.y=35; ///origin
    rect1.dx=400,rect1.dy=400; ///width and height

    ///rectangle two
    rect2.x=45,rect2.y=45;
    rect2.dx=380,rect2.dy=380;

    ///ball
    ball.x=rect2.x+105,ball.y=rect2.y+105; ///origin
    radius=50; ///radius

    ///initailizing arrow head
    tri_x[0]=ball.x+radius+1, tri_y[0]=ball.y+1; ///vertex 1 of tringle
    mid_x=(ball.x+tri_x[0])/2, mid_y=(ball.y+tri_y[0])/2; ///intersection of line and tringle of arrow
    double d=sqrt((mid_x-ball.x)*(mid_x-ball.x)+(mid_y-ball.y)*(mid_y-ball.y));
    double dy=sqrt(radius*radius-d*d);
    tri_x[1]=mid_x+dy*3/5, tri_y[1]=mid_y+dy*3/5;  ///vertex 2
    tri_x[2]=mid_x+dy*3/5, tri_y[2]=mid_y-dy*3/5;  ///vertex 3
}
/*
	function iDraw() is called again and again by the system.
*/
void make_ball()
{
    ///ball
    iSetColor(ball.color[0],ball.color[1],ball.color[2]); ///color
    iFilledCircle(ball.x,ball.y,radius,20); ///slice is 20 here.... can increse it for better picture
    ///arrow head
    iSetColor(255,255,0);///color
    iLine(ball.x,ball.y,mid_x,mid_y);
    iFilledPolygon(tri_x,tri_y,3);

}
///take length and breath as input
void make_box()
{
    iSetColor(rect1.color[0],rect1.color[1],rect1.color[2]);
    iFilledRectangle(rect1.x,rect1.y,rect1.dx,rect1.dy);
    iSetColor(0,0,0);
    iFilledRectangle(rect2.x,rect2.y,rect2.dx,rect2.dy);
}
void iDraw()
{
	iClear();
	make_box();
    make_ball();
	iText(10, 10, "Press p for pause, r for resume, END for exit.");
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if(key == 'p')
	{
		//do something with 'q'
		iPauseTimer(0);
	}
	if(key == 'r')
	{
		iResumeTimer(0);
	}
	if(key=='a') ///box go right with the ball also
    {
        rect1.x-=1;
        rect2.x-=1;
        ball.x-=1;
    }
    if(key=='d') ///box go left with the ball
    {
        rect1.x+=1;
        rect2.x+=1;
        ball.x+=1;
    }
    if(key=='w')  ///box go up with the ball
    {
        rect1.y+=1;
        rect2.y+=1;
        ball.y+=1;
    }
    if(key=='s')  ///box go down with the ball
    {
        rect1.y-=1;
        rect2.y-=1;
        ball.y-=1;
    }
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	if(key==GLUT_KEY_RIGHT)
    {
       T-=0.06; ///ball change the direction anti clockwise
    }

	if(key==GLUT_KEY_LEFT)
    {
        T+=0.06; ///ball change the direction clockwise
    }
	//place your codes for other keys here
}

///make decision about color change
int colorChanger()
{
    return (color_cnt++)%2;
}

void exchange_color()
{
    if(!colorChanger())
    {
        ball.color[0]=0,ball.color[1]=255,ball.color[2]=255; ///ball color
        rect1.color[0]=255,rect1.color[1]=0,rect1.color[2]=0; ///box color
    }
    else
    {
        ball.color[0]=255,ball.color[1]=0,ball.color[2]=0; ///ball color
        rect1.color[0]=0,rect1.color[1]=255,rect1.color[2]=255; ///box color
    }
}

void ballChange()
{
	ball.x += ball.dx*cos(T);
	ball.y += ball.dy*sin(T);
	///if ball hit the perpendicular wall
	if(ball.x > rect2.x+rect2.dx-radius || ball.x <rect2.x+ radius)
    {
        //PlaySound("Pad.wav",NULL,SND_ASYNC);
        T=3.1416-T; ///change direction

        ///exchange the color between wall and ball
        exchange_color();

    }
    ///if ball hit the horizontal walls
	if(ball.y > rect2.y+rect2.dy-radius || ball.y < rect2.y+radius)
	{
	   // PlaySound("Pad.wav",NULL,SND_ASYNC);
	    T=2*3.1416-T; ///change direction
	    ///exhange the color betwennn wall and the ball
	    exchange_color();

	}
}
void tringleChange()
{
    tri_x[0]=ball.x+radius*cos(T), tri_y[0]=ball.y+radius*sin(T);
    mid_x=(ball.x+tri_x[0])/2, mid_y=(ball.y+tri_y[0])/2; ///make line change also
    double d=sqrt((mid_x-ball.x)*(mid_x-ball.x)+(mid_y-ball.y)*(mid_y-ball.y));
    double dy=sqrt(radius*radius-d*d);
    tri_x[1]=mid_x-dy*sin(T)*3/5, tri_y[1]=mid_y+dy*cos(T)*3/5;
    tri_x[2]=mid_x+dy*sin(T)*3/5, tri_y[2]=mid_y-dy*cos(T)*3/5;
}

int main()
{

    initial();
	iSetTimer(ball_speed, ballChange);
	iSetTimer(ball_speed,tringleChange);


	iInitialize(600, 600, "let's play ball");

	return 0;
}


