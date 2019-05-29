#include<cglass.h>
#include<string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <math.h>
#include <stdio.h>
#include <fstream>
#pragma comment(lib, "irrKlang.lib")
#include <Windows.h>
#include <irrKlang.h>
GLuint image, image1, image2, image3, image4, image5, image6, image7, image8, image9, image10, image11, image12, image13, image14, overimage;
using namespace ObjectiveGlass;
using namespace irrklang;
using namespace std;

//Initializing Global Variables
char name[99] = {};
char newname[99] = {};
static int mainangle = 0;
static int mainspeed = 3;
char ColorArray[99][99] = { "Red", "Blue", "Yellow", "Purple" };
static char BallColor[99] = "Red";
int MaxShapes = 2, game = 0;
int  up = 0;
static ISoundEngine* engine = createIrrKlangDevice();
static ISoundEngine* engine1 = createIrrKlangDevice();
//Classes for all the Shapes being used
class Shapes
{
public:
	Shapes()
	{
	}
	virtual void setAll(double OriginX, double OriginY, double SideLength) = 0;
	virtual void OriginYAdd(double x) = 0;
	virtual double getOriginY() = 0;
};
class ObstacleShapes :public Shapes
{
protected:
	int direction;
public:
	ObstacleShapes()
	{
		direction = rand() % 2;
	}
	virtual bool collision(double y) = 0;
	virtual void DrawMovingShape(double speed) = 0;
	void SetDirection(int x)
	{
		direction = x;
	}
};
class MainShapes :public Shapes
{
public:
	virtual void DrawShape() = 0;
	virtual void ballcolorchange()
	{
		string OldColor = BallColor, NewColor;
		do
		{
			for (int i = 0; i < 5; i++)
			{
				BallColor[i] = '\0';
			}
			int random = rand() % 4, i = 0;
			while (ColorArray[random][i] != '\0')
			{
				BallColor[i] = ColorArray[random][i];
				i++;
			}
			NewColor = BallColor;
		} while (OldColor == NewColor);
		string temp;
	}
	virtual void OriginYsub(double x) = 0;
	virtual double GetOriginY() = 0;
};
//Obstacle shapes
class Rectanglee : public ObstacleShapes
{
protected:
	double x1, y1, x2, y2, x3, y3, x4, y4, Rx1, Ry1, Rx2, Ry2, Rx3, Ry3, Rx4, Ry4, OriginX, OriginY, SideLength;
	int ColorNo[4];
public:
	void DrawMovingShape(double Angle)
	{
		this->x1 = (OriginX - (SideLength / 2));
		this->y1 = (OriginY - (SideLength / 2));
		this->x2 = (OriginX + (SideLength / 2));
		this->y2 = (OriginY - (SideLength / 2));
		this->x3 = (OriginX + (SideLength / 2));
		this->y3 = (OriginY + (SideLength / 2));
		this->x4 = (OriginX - (SideLength / 2));
		this->y4 = (OriginY + (SideLength / 2));
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		double theeta;
		if (direction == 1)
			theeta = Angle*0.01745;
		else
			theeta = (-1)* Angle*0.01745;

		this->Rx1 = ((x1 - OriginX)*cos(theeta) - (y1 - OriginY)*sin(theeta)) + OriginX;
		this->Ry1 = ((x1 - OriginX)*sin(theeta) + (y1 - OriginY)*cos(theeta)) + OriginY;
		this->Rx2 = ((x2 - OriginX)*cos(theeta) - (y2 - OriginY)*sin(theeta)) + OriginX;
		this->Ry2 = ((x2 - OriginX)*sin(theeta) + (y2 - OriginY)*cos(theeta)) + OriginY;
		this->Rx3 = ((x3 - OriginX)*cos(theeta) - (y3 - OriginY)*sin(theeta)) + OriginX;
		this->Ry3 = ((x3 - OriginX)*sin(theeta) + (y3 - OriginY)*cos(theeta)) + OriginY;
		this->Rx4 = ((x4 - OriginX)*cos(theeta) - (y4 - OriginY)*sin(theeta)) + OriginX;
		this->Ry4 = ((x4 - OriginX)*sin(theeta) + (y4 - OriginY)*cos(theeta)) + OriginY;


		line a(Rx1, Ry1, Rx2, Ry2, ColorArray[ColorNo[0]], 10);
		a.Draw();
		line b(Rx2, Ry2, Rx3, Ry3, ColorArray[ColorNo[1]], 10);
		b.Draw();
		line c(Rx3, Ry3, Rx4, Ry4, ColorArray[ColorNo[2]], 10);
		c.Draw();
		line d(Rx4, Ry4, Rx1, Ry1, ColorArray[ColorNo[3]], 10);
		d.Draw();
	}
	Rectanglee() :ObstacleShapes()
	{
		x1 = y1 = x2 = y2 = x3 = y3 = x4 = y4 = Rx1 = Ry1 = Rx2 = Ry2 = Rx3 = Ry3 = Rx4 = Ry4 = OriginX = OriginY = SideLength = 0;
	}
	Rectanglee(double OriginX, double OriginY, double SideLength) :ObstacleShapes()
	{
		this->x1 = (OriginX - (SideLength / 2));
		this->y1 = (OriginY - (SideLength / 2));
		this->x2 = (OriginX + (SideLength / 2));
		this->y2 = (OriginY - (SideLength / 2));
		this->x3 = (OriginX + (SideLength / 2));
		this->y3 = (OriginY + (SideLength / 2));
		this->x4 = (OriginX - (SideLength / 2));
		this->y4 = (OriginY + (SideLength / 2));
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->SideLength = SideLength;
		do
		{
			ColorNo[0] = rand() % 4;
			ColorNo[1] = rand() % 4;
			ColorNo[2] = rand() % 4;
			ColorNo[3] = rand() % 4;
		} while (!((ColorArray[ColorNo[0]] != ColorArray[ColorNo[1]]) && (ColorArray[ColorNo[0]] != ColorArray[ColorNo[2]]) && (ColorArray[ColorNo[0]] != ColorArray[ColorNo[3]]) && (ColorArray[ColorNo[1]] != ColorArray[ColorNo[2]]) && (ColorArray[ColorNo[1]] != ColorArray[ColorNo[3]]) && (ColorArray[ColorNo[2]] != ColorArray[ColorNo[3]])));
	}
	void OriginYAdd(double x)
	{
		this->OriginY += x;
	}
	double getOriginY()
	{
		return OriginY;
	}
	bool collision(double y)
	{
		double m1, m2, m3, m4, Yintercept = 0;
		int type;
		m1 = (Ry1 + Ry2) / 2;
		m2 = (Ry2 + Ry3) / 2;
		m3 = (Ry3 + Ry4) / 2;
		m4 = (Ry4 + Ry1) / 2;
		if (m1 > m2 && m1 > m3 && m1 > m4)
		{
			Yintercept = (((Ry2 - Ry1) / (Rx2 - Rx1))*OriginX) + (Ry2 - (((Ry2 - Ry1) / (Rx2 - Rx1))*Rx2));
			type = 0;
		}
		else if (m2 > m1 && m2 > m3 && m2 > m4)
		{
			Yintercept = (((Ry3 - Ry2) / (Rx3 - Rx2))*OriginX) + (Ry2 - (((Ry3 - Ry2) / (Rx3 - Rx2))*Rx2));
			type = 1;
		}
		else if (m3 > m1 && m3 > m2 && m3 > m4)
		{
			Yintercept = (((Ry4 - Ry3) / (Rx4 - Rx3))*OriginX) + (Ry4 - (((Ry4 - Ry3) / (Rx4 - Rx3))*Rx4));
			type = 2;
		}
		else if (m4 > m1 && m4 > m2 && m4 > m3)
		{
			Yintercept = (((Ry4 - Ry1) / (Rx4 - Rx1))*OriginX) + (Ry4 - (((Ry4 - Ry1) / (Rx4 - Rx1))*Rx4));
			type = 3;
		}
		if (Yintercept - y < 5 && Yintercept - y>-5)
		{
			if (!(BallColor[0] == ColorArray[ColorNo[type]][0]))
				return true;
		}
		if (m1 < m2 && m1 < m3 && m1 < m4)
		{
			Yintercept = (((Ry2 - Ry1) / (Rx2 - Rx1))*OriginX) + (Ry2 - (((Ry2 - Ry1) / (Rx2 - Rx1))*Rx2));
			type = 0;
		}
		else if (m2 < m1 && m2 < m3 && m2 < m4)
		{
			Yintercept = (((Ry3 - Ry2) / (Rx3 - Rx2))*OriginX) + (Ry2 - (((Ry3 - Ry2) / (Rx3 - Rx2))*Rx2));
			type = 1;
		}
		else if (m3 <m1 && m3 < m2 && m3 < m4)
		{
			Yintercept = (((Ry4 - Ry3) / (Rx4 - Rx3))*OriginX) + (Ry4 - (((Ry4 - Ry3) / (Rx4 - Rx3))*Rx4));
			type = 2;
		}
		else if (m4 < m1 && m4 < m2 && m4 < m3)
		{
			Yintercept = (((Ry4 - Ry1) / (Rx4 - Rx1))*OriginX) + (Ry4 - (((Ry4 - Ry1) / (Rx4 - Rx1))*Rx4));
			type = 3;
		}
		if (Yintercept - y < 5 && Yintercept - y>-5)
		{
			if (!(BallColor[0] == ColorArray[ColorNo[type]][0]))
				return true;
		}
		return false;
	}
	virtual void setAll(double OriginX, double OriginY, double SideLength)
	{
		this->x1 = (OriginX - (SideLength / 2));
		this->y1 = (OriginY + (SideLength / 2));
		this->x2 = (OriginX + (SideLength / 2));
		this->y2 = (OriginY + (SideLength / 2));
		this->x3 = (OriginX + (SideLength / 2));
		this->y3 = (OriginY - (SideLength / 2));
		this->x4 = (OriginX - (SideLength / 2));
		this->y4 = (OriginY - (SideLength / 2));
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->SideLength = SideLength;
		do
		{
			ColorNo[0] = rand() % 4;
			ColorNo[1] = rand() % 4;
			ColorNo[2] = rand() % 4;
			ColorNo[3] = rand() % 4;
		} while (!((ColorArray[ColorNo[0]] != ColorArray[ColorNo[1]]) && (ColorArray[ColorNo[0]] != ColorArray[ColorNo[2]]) && (ColorArray[ColorNo[0]] != ColorArray[ColorNo[3]]) && (ColorArray[ColorNo[1]] != ColorArray[ColorNo[2]]) && (ColorArray[ColorNo[1]] != ColorArray[ColorNo[3]]) && (ColorArray[ColorNo[2]] != ColorArray[ColorNo[3]])));

	}
};
class Circlee :public ObstacleShapes
{
protected:
	double OriginX, OriginY, Radius;
	int ColorNumber;
	char Color[99];
public:
	void DrawMovingShape(double speed)
	{
		ColorNumber = time(NULL) % 4;
		CreateCircle(OriginX, OriginY, Radius, ColorArray[ColorNumber], "Hollow", 4);
	}
	bool collision(double y)
	{
		double UYintercept = OriginY - Radius, DYintercept = OriginY + Radius;

		if (UYintercept - y < 5 && UYintercept - y>-5)
		{
			if (!(BallColor[0] == ColorArray[ColorNumber][0]))
				return true;
		}
		if (DYintercept - y < 7 && DYintercept - y>-7)
		{
			if (!(BallColor[0] == ColorArray[ColorNumber][0]))
				return true;
		}
		return false;
	}
	Circlee() :ObstacleShapes()
	{
		OriginX = OriginY = Radius = 0;
	}
	Circlee(double OriginX, double OriginY, double Radius) :ObstacleShapes()
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->Radius = Radius;
	}
	virtual void setAll(double OriginX, double OriginY, double Radius)
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->Radius = Radius;
	}
	virtual void OriginYAdd(double x)
	{
		OriginY += x;
	}
	virtual double getOriginY()
	{
		return OriginY;
	}
};
class Plus :public ObstacleShapes
{
protected:
	double OriginX, OriginY, x1, y1, x2, y2, x3, y3, x4, y4, Rx1, Ry1, Rx2, Ry2, Rx3, Ry3, Rx4, Ry4, SideLength;
	int ColorNo[3];
public:
	void DrawMovingShape(double Angle)
	{
		Angle = Angle / 2.5;
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->x1 = OriginX;
		this->x2 = OriginX + SideLength;
		this->x3 = OriginX;
		this->x4 = OriginX - SideLength;
		this->y1 = OriginY - SideLength;
		this->y2 = OriginY;
		this->y3 = OriginY + SideLength;
		this->y4 = OriginY;
		this->SideLength = SideLength;

		double theeta;
		if (direction == 1)
			theeta = Angle*0.01745;
		else
			theeta = (-1)* Angle*0.01745;

		this->Rx1 = ((x1 - OriginX)*cos(theeta) - (y1 - OriginY)*sin(theeta)) + OriginX;
		this->Ry1 = ((x1 - OriginX)*sin(theeta) + (y1 - OriginY)*cos(theeta)) + OriginY;
		this->Rx2 = ((x2 - OriginX)*cos(theeta) - (y2 - OriginY)*sin(theeta)) + OriginX;
		this->Ry2 = ((x2 - OriginX)*sin(theeta) + (y2 - OriginY)*cos(theeta)) + OriginY;
		this->Rx3 = ((x3 - OriginX)*cos(theeta) - (y3 - OriginY)*sin(theeta)) + OriginX;
		this->Ry3 = ((x3 - OriginX)*sin(theeta) + (y3 - OriginY)*cos(theeta)) + OriginY;
		this->Rx4 = ((x4 - OriginX)*cos(theeta) - (y4 - OriginY)*sin(theeta)) + OriginX;
		this->Ry4 = ((x4 - OriginX)*sin(theeta) + (y4 - OriginY)*cos(theeta)) + OriginY;

		line a(OriginX, OriginY, Rx1, Ry1, ColorArray[ColorNo[0]], 10);
		a.Draw();
		line b(OriginX, OriginY, Rx2, Ry2, ColorArray[ColorNo[1]], 10);
		b.Draw();
		line c(OriginX, OriginY, Rx3, Ry3, ColorArray[ColorNo[2]], 10);
		c.Draw();
		line d(OriginX, OriginY, Rx4, Ry4, ColorArray[ColorNo[3]], 10);
		d.Draw();
	}
	Plus(double OriginX, double OriginY, double SideLength) :ObstacleShapes()
	{
		this->SideLength = SideLength;
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->x1 = OriginX;
		this->x2 = OriginX + SideLength;
		this->x3 = OriginX;
		this->x4 = OriginX - SideLength;
		this->y1 = OriginY - SideLength;
		this->y2 = OriginY;
		this->y3 = OriginY + SideLength;
		this->y4 = OriginY;
		do
		{
			ColorNo[0] = rand() % 4;
			ColorNo[1] = rand() % 4;
			ColorNo[2] = rand() % 4;
			ColorNo[3] = rand() % 4;
		} while (!((ColorArray[ColorNo[0]] != ColorArray[ColorNo[1]]) && (ColorArray[ColorNo[0]] != ColorArray[ColorNo[2]]) && (ColorArray[ColorNo[0]] != ColorArray[ColorNo[3]]) && (ColorArray[ColorNo[1]] != ColorArray[ColorNo[2]]) && (ColorArray[ColorNo[1]] != ColorArray[ColorNo[3]]) && (ColorArray[ColorNo[2]] != ColorArray[ColorNo[3]])));

	}
	virtual void setAll(double OriginX, double OriginY, double SideLength)
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->x1 = OriginX;
		this->x2 = OriginX + SideLength;
		this->x3 = OriginX;
		this->x4 = OriginX - SideLength;
		this->y1 = OriginY - SideLength;
		this->y2 = OriginY;
		this->y3 = OriginY + SideLength;
		this->y4 = OriginY;
		this->SideLength = SideLength;
		do
		{
			ColorNo[0] = rand() % 4;
			ColorNo[1] = rand() % 4;
			ColorNo[2] = rand() % 4;
			ColorNo[3] = rand() % 4;
		} while (!((ColorArray[ColorNo[0]] != ColorArray[ColorNo[1]]) && (ColorArray[ColorNo[0]] != ColorArray[ColorNo[2]]) && (ColorArray[ColorNo[0]] != ColorArray[ColorNo[3]]) && (ColorArray[ColorNo[1]] != ColorArray[ColorNo[2]]) && (ColorArray[ColorNo[1]] != ColorArray[ColorNo[3]]) && (ColorArray[ColorNo[2]] != ColorArray[ColorNo[3]])));

	}
	bool collision(double y)
	{
		double m1, m2, m3, m4, n1, n2, n3, n4, Yintercept = 0;
		int type;
		double MaxYIntercept = sqrt((pow(SideLength, 2) - pow(OriginX - 150, 2)));
		m1 = (Ry1 + OriginY) / 2;
		m2 = (Ry2 + OriginY) / 2;
		m3 = (Ry3 + OriginY) / 2;
		m4 = (Ry4 + OriginY) / 2;

		n1 = (Rx1 + OriginX) / 2;
		n2 = (Rx2 + OriginX) / 2;
		n3 = (Rx3 + OriginX) / 2;
		n4 = (Rx4 + OriginX) / 2;
		if (m1 <OriginY && n1 < OriginX)
		{
			double slope = (Ry1 - OriginY) / (Rx1 - OriginX);
			Yintercept = ((slope)*(150)) + ((Ry1)-((slope)*(Rx1)));
			type = 0;
		}
		else if (m2 <OriginY && n2 < 225)
		{
			double slope = (Ry2 - OriginY) / (Rx2 - OriginX);
			Yintercept = ((slope)*(150)) + ((Ry2)-((slope)*(Rx2)));
			type = 1;
		}
		else if (m3 <OriginY && n3< 225)
		{
			double slope = (Ry3 - OriginY) / (Rx3 - OriginX);
			Yintercept = ((slope)*(150)) + ((Ry3)-((slope)*(Rx3)));
			type = 2;
		}
		else if (m4 <OriginY && n4 < 225)
		{
			double slope = (Ry4 - OriginY) / (Rx4 - OriginX);
			Yintercept = ((slope)*(150)) + ((Ry4)-((slope)*(Rx4)));
			type = 3;
		}
		if ((OriginY - Yintercept) <= MaxYIntercept)
		{
			if (Yintercept - y < 5 && Yintercept - y>-5)
			{
				if (!(BallColor[0] == ColorArray[ColorNo[type]][0]))
					return true;
			}
		}
		if (m1 >OriginY && n1 < OriginX)
		{
			double slope = (Ry1 - OriginY) / (Rx1 - OriginX);
			Yintercept = ((slope)*(150)) + ((Ry1)-((slope)*(Rx1)));
			type = 0;
		}
		else if (m2 >OriginY && n2 < 225)
		{
			double slope = (Ry2 - OriginY) / (Rx2 - OriginX);
			Yintercept = ((slope)*(150)) + ((Ry2)-((slope)*(Rx2)));
			type = 1;
		}
		else if (m3 >OriginY && n3< 225)
		{
			double slope = (Ry3 - OriginY) / (Rx3 - OriginX);
			Yintercept = ((slope)*(150)) + ((Ry3)-((slope)*(Rx3)));
			type = 2;
		}
		else if (m4 >OriginY && n4 < 225)
		{
			double slope = (Ry4 - OriginY) / (Rx4 - OriginX);
			Yintercept = ((slope)*(150)) + ((Ry4)-((slope)*(Rx4)));
			type = 3;
		}
		if ((Yintercept - OriginY) <= MaxYIntercept)
		{
			if (Yintercept - y < 5 && Yintercept - y>-5)
			{
				if (!(BallColor[0] == ColorArray[ColorNo[type]][0]))
					return true;
			}
		}
		return false;
	}
	virtual void OriginYAdd(double x)
	{
		OriginY += x;
	}
	virtual double getOriginY()
	{
		return OriginY;
	}
};
class Triangle : public ObstacleShapes
{
protected:
	double x1, y1, x2, y2, x3, y3, Rx1, Ry1, Rx2, Ry2, Rx3, Ry3, OriginX, OriginY, SideLength;
	int ColorNo[3];
public:
	void DrawMovingShape(double Angle)
	{
		double Cy = (y1 + y2 + y3) / 3;
		double theeta;
		if (direction == 1)
			theeta = Angle*0.01744;
		else
			theeta = (-1)* Angle*0.01744;

		this->Rx1 = ((x1 - OriginX)*cos(theeta) - (y1 - Cy)*sin(theeta)) + OriginX;
		this->Ry1 = ((x1 - OriginX)*sin(theeta) + (y1 - Cy)*cos(theeta)) + Cy;
		this->Rx2 = ((x2 - OriginX)*cos(theeta) - (y2 - Cy)*sin(theeta)) + OriginX;
		this->Ry2 = ((x2 - OriginX)*sin(theeta) + (y2 - Cy)*cos(theeta)) + Cy;
		this->Rx3 = ((x3 - OriginX)*cos(theeta) - (y3 - Cy)*sin(theeta)) + OriginX;
		this->Ry3 = ((x3 - OriginX)*sin(theeta) + (y3 - Cy)*cos(theeta)) + Cy;
		static char ThisColor[99];
		if (Cy < 250)
		{
			line a(Rx1, Ry1, Rx2, Ry2, BallColor, 10);
			a.Draw();
			for (int i = 0; i < 6; i++)
			{
				ThisColor[i] = BallColor[i];
			}
		}
		else
		{
			line a(Rx1, Ry1, Rx2, Ry2, ThisColor, 10);
			a.Draw();
		}
		line b(Rx2, Ry2, Rx3, Ry3, ColorArray[ColorNo[1]], 10);
		b.Draw();
		line c(Rx3, Ry3, Rx1, Ry1, ColorArray[ColorNo[2]], 10);
		c.Draw();

		this->x1 = OriginX;
		this->y1 = (OriginY - (0.4330*SideLength));
		this->x2 = (OriginX + (SideLength / 2));
		this->y2 = (OriginY + (0.4330*SideLength));
		this->x3 = (OriginX - (SideLength / 2));
		this->y3 = (OriginY + (0.4330*SideLength));

	}
	Triangle() : ObstacleShapes()
	{
		x1 = y1 = x2 = y2 = x3 = y3 = Rx1 = Ry1 = Rx2 = Ry2 = Rx3 = Ry3 = OriginX = OriginY = SideLength = 0;
	}
	Triangle(double OriginX, double OriginY, double SideLength) :ObstacleShapes()
	{
		this->x1 = OriginX;
		this->y1 = (OriginY - ((0.8660*SideLength) / 2));
		this->x2 = (OriginX + (SideLength / 2));
		this->y2 = (OriginY + ((0.8660*SideLength) / 2));
		this->x3 = (OriginX - (SideLength / 2));
		this->y3 = (OriginY + ((0.8660*SideLength) / 2));
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->SideLength = SideLength;
		do
		{
			ColorNo[0] = rand() % 4;
			ColorNo[1] = rand() % 4;
			ColorNo[2] = rand() % 4;
		} while (!((ColorArray[ColorNo[0]] != ColorArray[ColorNo[1]]) && (ColorArray[ColorNo[0]] != ColorArray[ColorNo[2]]) && (ColorArray[ColorNo[0]][0] != BallColor[0]) && (ColorArray[ColorNo[1]] != ColorArray[ColorNo[2]]) && (ColorArray[ColorNo[1]][0] != BallColor[0]) && (ColorArray[ColorNo[2]][0] != BallColor[0])));
	}
	void OriginYAdd(double x)
	{
		this->OriginY += x;
	}
	double getOriginY()
	{
		return OriginY;
	}
	bool collision(double y)
	{
		double m1, m2, m3, Yintercept = 0;
		int type;
		m1 = (Ry1 + Ry2) / 2;
		m2 = (Ry2 + Ry3) / 2;
		m3 = (Ry3 + Ry1) / 2;
		if (m1 > m2 && m1 > m3)
		{
			Yintercept = (((Ry2 - Ry1) / (Rx2 - Rx1))*OriginX) + (Ry2 - (((Ry2 - Ry1) / (Rx2 - Rx1))*Rx2));
			type = 0;
		}
		else if (m2 > m1 && m2 > m3)
		{
			Yintercept = (((Ry3 - Ry2) / (Rx3 - Rx2))*OriginX) + (Ry2 - (((Ry3 - Ry2) / (Rx3 - Rx2))*Rx2));
			type = 1;
		}
		else if (m3 > m1 && m3 > m2)
		{
			Yintercept = (((Ry1 - Ry3) / (Rx1 - Rx3))*OriginX) + (Ry1 - (((Ry1 - Ry3) / (Rx1 - Rx3))*Rx1));
			type = 2;
		}
		if (Yintercept - y < 5 && Yintercept - y>-5)
		{
			if (type != 0)
			{
				if (!(BallColor[0] == ColorArray[ColorNo[type]][0]))
					return true;
			}
		}
		if (m1 < m2 && m1 < m3)
		{
			Yintercept = (((Ry2 - Ry1) / (Rx2 - Rx1))*OriginX) + (Ry2 - (((Ry2 - Ry1) / (Rx2 - Rx1))*Rx2));
			type = 0;
		}
		else if (m2 < m1 && m2 < m3)
		{
			Yintercept = (((Ry3 - Ry2) / (Rx3 - Rx2))*OriginX) + (Ry2 - (((Ry3 - Ry2) / (Rx3 - Rx2))*Rx2));
			type = 1;
		}
		else if (m3 < m1 && m3 < m2)
		{
			Yintercept = (((Ry1 - Ry3) / (Rx1 - Rx3))*OriginX) + (Ry1 - (((Ry1 - Ry3) / (Rx1 - Rx3))*Rx1));
			type = 2;
		}
		if (Yintercept - y < 5 && Yintercept - y>-5)
		{
			if (type != 0)
			{
				if (!(BallColor[0] == ColorArray[ColorNo[type]][0]))
					return true;
			}
		}
		return false;
	}
	virtual void setAll(double OriginX, double OriginY, double SideLength)
	{
		this->x1 = OriginX;
		this->y1 = (OriginY - (SideLength / 2));
		this->x2 = (OriginX + (SideLength / 2));
		this->y2 = (OriginY + (SideLength / 2));
		this->x3 = (OriginX - (SideLength / 2));
		this->y3 = (OriginY + (SideLength / 2));
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->SideLength = SideLength;
		do
		{
			ColorNo[0] = BallColor[99];
			ColorNo[1] = rand() % 4;
			ColorNo[2] = rand() % 4;
		} while (!((ColorArray[ColorNo[0]] != ColorArray[ColorNo[1]]) && (ColorArray[ColorNo[0]] != ColorArray[ColorNo[2]]) && (ColorArray[ColorNo[1]] != ColorArray[ColorNo[2]])));
	}
};
class RunningLines :public ObstacleShapes
{
private:
	double x1, x2, x3, x4;
	int YCoordinate;
public:
	RunningLines(int YCoordinate) :ObstacleShapes()
	{
		this->YCoordinate = YCoordinate;
		x1 = -100;
		x2 = 0;
		x3 = 100;
		x4 = 200;

	}
	void DrawMovingShape(double speed)
	{
		speed = (speed + 3600) / 3600;
		x1 += speed;
		x2 += speed;
		x3 += speed;
		x4 += speed;
		line a(x1, YCoordinate, x1 + 100, YCoordinate, "Red", 20);
		a.Draw();
		line b(x2, YCoordinate, x2 + 100, YCoordinate, "Purple", 20);
		b.Draw();
		line c(x3, YCoordinate, x3 + 100, YCoordinate, "Yellow", 20);
		c.Draw();
		line d(x4, YCoordinate, x4 + 100, YCoordinate, "Blue", 20);
		d.Draw();
		if (x1 >= 300)
		{
			x1 = -100;
		}
		if (x2 >= 300)
		{
			x2 = -100;
		}
		if (x3 >= 300)
		{
			x3 = -100;
		}
		if (x4 >= 300)
		{
			x4 = (-100);
		}
	}
	void setAll(double OriginX, double OriginY, double SideLength)
	{

	}
	void OriginYAdd(double x)
	{
		YCoordinate += x;
	}
	double getOriginY()
	{
		return YCoordinate;
	}
	bool collision(double y)
	{
		if (x1 > 51 && x1 < 151)
		{
			if (YCoordinate - y < 5 && YCoordinate - y>-5)
			{
				if (!(BallColor[0] == 'R'))
					return true;
			}
		}
		else  if (x2 > 51 && x2 < 151)
		{
			if (YCoordinate - y < 5 && YCoordinate - y>-5)
			{
				if (!(BallColor[0] == 'P'))
					return true;
			}
		}
		else  if (x3 > 51 && x3 < 151)
		{
			if (YCoordinate - y < 5 && YCoordinate - y>-5)
			{
				if (!(BallColor[0] == 'Y'))
					return true;
			}
		}
		else  if (x4 > 51 && x4 < 151)
		{
			if (YCoordinate - y < 5 && YCoordinate - y>-5)
			{
				if (!(BallColor[0] == 'B'))
					return true;
			}
		}
		return false;
	}
};
class Infinity :public ObstacleShapes
{
private:
	double OriginX, OriginY, length, Angle;
	int ColorNo;
public:
	Infinity(double OriginX, double OriginY, double SideLength) :ObstacleShapes()
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->length = SideLength;
		do
		{
			ColorNo = rand() % 4;
		} while (!((ColorArray[ColorNo][0] != BallColor[0])));
	}
	virtual void setAll(double OriginX, double OriginY, double SideLength)
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->length = SideLength;
	}
	virtual void OriginYAdd(double x)
	{
		OriginY += x;
	}
	virtual double getOriginY()
	{
		return OriginY;
	}
	virtual bool collision(double y)
	{
		if (OriginY - y < 5 && OriginY - y>-5)
		{
			if ((Angle>90 && Angle <180) || (Angle > 270 && Angle < 360))
				return true;
		}
		return false;
	}
	virtual void DrawMovingShape(double speed)
	{
		double x = 0, y = 0;
		double a = length, t = speed, r = 4;
		static char ThisColor[99], ThisColor2[99];
		for (int i = 0; i < 360; i += 10)
		{
			x = (a*sqrt(2)*cos((t + i)*0.01745)) / (pow(sin((t + i)*0.01745), 2) + 1) + OriginX;
			y = (a*sqrt(2)*cos((t + i)*0.01745)*sin((t + i)*0.01745)) / (pow(sin((t + i)*0.01745), 2) + 1) + OriginY;
			if ((i >= 0 && i <= 90) || (i >= 190 && i <= 270))
			{
				if (OriginY < 250)
				{
					CreateCircle(x, y, r, BallColor, "Filled");
					for (int i = 0; i < 6; i++)
					{
						ThisColor[i] = BallColor[i];
					}
				}
				else
				{
					CreateCircle(x, y, r, ThisColor, "Filled");
				}
			}
			else
			{
				if (OriginY < 250)
				{
					CreateCircle(x, y, r, ColorArray[ColorNo], "Filled");
					for (int i = 0; i < 6; i++)
					{
						ThisColor2[i] = ColorArray[ColorNo][i];
					}
				}
				else
				{
					CreateCircle(x, y, r, ThisColor2, "Filled");
				}
			}
		}
		t = (int)t % 360;
		this->Angle = t;
	}
};
class PlusInfinity :public ObstacleShapes
{
private:
	double OriginX, OriginY, length, Angle;
	int ColorNo;
public:
	PlusInfinity(double OriginX, double OriginY, double SideLength) :ObstacleShapes()
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->length = SideLength;
		do
		{
			ColorNo = rand() % 4;
		} while (!((ColorArray[ColorNo][0] != BallColor[0])));
	}
	virtual void setAll(double OriginX, double OriginY, double SideLength)
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->length = SideLength;
	}
	virtual void OriginYAdd(double x)
	{
		OriginY += x;
	}
	virtual double getOriginY()
	{
		return OriginY;
	}
	virtual bool collision(double y)
	{
		if (OriginY - y < 5 && OriginY - y>-5)
		{
			if ((Angle>90 && Angle <180) || (Angle > 270 && Angle < 360))
				return true;
		}
		if ((OriginY + length + 25) - y < 5 && (OriginY + length + 25) - y>-5)
		{
			if (!((Angle>90 && Angle <180) || (Angle > 270 && Angle < 360)))
				return true;
		}
		if ((OriginY - length - 25) - y < 5 && (OriginY - length - 25) - y>-5)
		{
			if (!((Angle>90 && Angle <180) || (Angle > 270 && Angle < 360)))
				return true;
		}
		return false;
	}
	virtual void DrawMovingShape(double speed)
	{
		double x = 0, y = 0, xx = 0, yy = 0, a = length, t = speed, r = 4;
		static char ThisColor[99], ThisColor2[99];

		for (int i = 0; i < 360; i += 10)
		{
			x = (a*sqrt(2)*cos((t + i)*0.01745)) / (pow(sin((t + i)*0.01745), 2) + 1) + OriginX;
			y = (a*sqrt(2)*cos((t + i)*0.01745)*sin((t + i)*0.01745)) / (pow(sin((t + i)*0.01745), 2) + 1) + OriginY;
			xx = (a*sqrt(2)*cos((t + i)*0.01745)) / (pow(sin((t + i)*0.01745), 2) + 1) + OriginY;
			yy = (a*sqrt(2)*cos((t + i)*0.01745)*sin((t + i)*0.01745)) / (pow(sin((t + i)*0.01745), 2) + 1) + OriginX;
			if ((i >= 0 && i <= 90) || (i >= 190 && i <= 270))
			{
				if (OriginY < 250)
				{
					CreateCircle(x, y, r, BallColor, "Filled");
					CreateCircle(yy, xx, r, BallColor, "Filled");
					for (int i = 0; i < 6; i++)
					{
						ThisColor[i] = BallColor[i];
					}
				}
				else
				{
					CreateCircle(x, y, r, ThisColor, "Filled");
					CreateCircle(yy, xx, r, ThisColor, "Filled");
				}
			}
			else
			{
				if (OriginY < 250)
				{
					CreateCircle(x, y, r, ColorArray[ColorNo], "Filled");
					CreateCircle(yy, xx, r, ColorArray[ColorNo], "Filled");
					for (int i = 0; i < 6; i++)
					{
						ThisColor2[i] = ColorArray[ColorNo][i];
					}
				}
				else
				{
					CreateCircle(x, y, r, ThisColor2, "Filled");
					CreateCircle(yy, xx, r, ThisColor2, "Filled");
				}
			}
		}


		t = (int)t % 360;
		this->Angle = t;

	}
};
class BallsCircle :public ObstacleShapes
{
private:
	double OriginX, OriginY, length, Angle;
	int ColorNo[3];
public:
	BallsCircle(double OriginX, double OriginY, double SideLength) :ObstacleShapes()
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->length = SideLength;
		do
		{
			ColorNo[0] = rand() % 4;
			ColorNo[1] = rand() % 4;
			ColorNo[2] = rand() % 4;
		} while (!((ColorArray[ColorNo[0]] != ColorArray[ColorNo[1]]) && (ColorArray[ColorNo[0]] != ColorArray[ColorNo[2]]) && (ColorArray[ColorNo[0]][0] != BallColor[0]) && (ColorArray[ColorNo[1]] != ColorArray[ColorNo[2]]) && (ColorArray[ColorNo[1]][0] != BallColor[0]) && (ColorArray[ColorNo[2]][0] != BallColor[0])));
	}
	virtual void setAll(double OriginX, double OriginY, double SideLength)
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		this->length = SideLength;
	}
	virtual void OriginYAdd(double x)
	{
		OriginY += x;
	}
	virtual double getOriginY()
	{
		return OriginY;
	}
	virtual bool collision(double y)
	{
		if (OriginY + length - y < 5 && OriginY + length - y>-5)
		{
			if ((Angle>90 && Angle <180) || (Angle > 270 && Angle < 360))
				return true;
		}
		else if (OriginY - length - y < 5 && OriginY - length - y>-5)
		{
			if ((Angle>90 && Angle <180) || (Angle > 270 && Angle < 360))
				return true;
		}
		return false;
	}
	virtual void DrawMovingShape(double speed)
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
		double  x = 0, y = 0, r = 5, n1 = 0, n2 = 0, a = length;
		static char ThisColor[99], ThisColor2[99], ThisColor3[99], ThisColor4[99];
		double q = speed;
		for (int i = 0; i <= 360; i += 15)
		{
			x = a*cos((q + i)*0.01745) + OriginX;
			y = a*sin((q + i)*0.01745) + OriginY;
			if (OriginY < 250)
			{
				if (i >= 0 && i<90)
				{
					CreateCircle(x, y, r, BallColor, "Filled");
					for (int i = 0; i < 6; i++)
					{
						ThisColor[i] = BallColor[i];
					}
				}
				else if (i >= 90 && i<180)
				{
					CreateCircle(x, y, r, ColorArray[ColorNo[0]], "Filled");
					for (int i = 0; i < 6; i++)
					{
						ThisColor2[i] = ColorArray[ColorNo[0]][i];
						ThisColor3[i] = ColorArray[ColorNo[1]][i];
						ThisColor4[i] = ColorArray[ColorNo[2]][i];
					}
				}
				else if (i >= 180 && i < 270)
				{
					CreateCircle(x, y, r, ColorArray[ColorNo[1]], "Filled");
					for (int i = 0; i < 6; i++)
					{
						ThisColor2[i] = ColorArray[ColorNo[0]][i];
						ThisColor3[i] = ColorArray[ColorNo[1]][i];
						ThisColor4[i] = ColorArray[ColorNo[2]][i];
					}
				}
				else if (i >= 270 && i < 360)
				{
					CreateCircle(x, y, r, ColorArray[ColorNo[2]], "Filled");
					for (int i = 0; i < 6; i++)
					{
						ThisColor2[i] = ColorArray[ColorNo[0]][i];
						ThisColor3[i] = ColorArray[ColorNo[1]][i];
						ThisColor4[i] = ColorArray[ColorNo[2]][i];
					}
				}
			}
			else
			{
				if (i >= 0 && i<90)
				{
					CreateCircle(x, y, r, ThisColor, "Filled");
				}
				else if (i >= 90 && i<180)
				{
					CreateCircle(x, y, r, ThisColor2, "Filled");
				}
				else if (i >= 180 && i < 270)
				{
					CreateCircle(x, y, r, ThisColor3, "Filled");
				}
				else if (i >= 270 && i < 360)
				{
					CreateCircle(x, y, r, ThisColor4, "Filled");
				}
			}
		}
		q = (int)q % 360;
		this->Angle = q;
	}
};
//Ball or Main Shapes
class MainBall :public MainShapes
{
protected:
	double OriginX, OriginY;
public:
	double GetOriginY()
	{
		return OriginY;
	}
	MainBall(double OriginX = 150, double OriginY = 350) :MainShapes()
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
	}
	void DrawShape()
	{
		CreateCircle(OriginX, OriginY, 7.0, BallColor, "Filled");
	}
	void OriginYAdd(double x)
	{
		this->OriginY -= x;
	}
	void OriginYsub(double x)
	{
		this->OriginY += x;
	}
	void setAll(double OriginX, double OriginY, double SideLength)
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
	}
	double getOriginY()
	{
		return OriginY;
	}
};
class MainSquare :public MainShapes
{
protected:
	double OriginX, OriginY;
public:
	double GetOriginY()
	{
		return OriginY;
	}
	MainSquare(double OriginX = 150, double OriginY = 325) :MainShapes()
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
	}
	void DrawShape()
	{
		if (mainspeed > 3)
		{
			mainspeed -= 0.5;
		}
		mainangle += mainspeed;
		rectangle r1(143.0, OriginY - 7, 14.0, 14.0, BallColor, "Filled");
		r1.Rotate(mainangle);
		r1.Draw();
	}
	void OriginYAdd(double x)
	{
		this->OriginY -= x;
	}
	void OriginYsub(double x)
	{
		this->OriginY += x;
	}
	void setAll(double OriginX, double OriginY, double SideLength)
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
	}
	double getOriginY()
	{
		return OriginY;
	}
};
class MainHollow :public MainShapes
{
protected:
	double OriginX, OriginY;
public:
	double GetOriginY()
	{
		return OriginY;
	}
	MainHollow(double OriginX = 150, double OriginY = 325) :MainShapes()
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
	}
	void DrawShape()
	{
		if (mainspeed > 3)
		{
			mainspeed -= 0.5;
		}
		mainangle += mainspeed;
		rectangle r1(143.0, OriginY - 7, 14.0, 14.0, BallColor, "Hollow", 0.001);
		r1.Rotate(mainangle);
		r1.Draw();
	}
	void OriginYAdd(double x)
	{
		this->OriginY -= x;
	}
	void OriginYsub(double x)
	{
		this->OriginY += x;
	}
	void setAll(double OriginX, double OriginY, double SideLength)
	{
		this->OriginX = OriginX;
		this->OriginY = OriginY;
	}
	double getOriginY()
	{
		return OriginY;
	}
};

int main(int argc, char** argv)
{
	srand(time(NULL));
	mainWindowLoop(argc, argv, "Color Switch", 400, 300, "Black", 60);
	image = LoadImage("maxresdefault.tga");
	image1 = LoadImage("Button1.tga");
	image2 = LoadImage("Button2.tga");
	image3 = LoadImage("Button3.tga");
	image4 = LoadImage("Button4.tga");
	image5 = LoadImage("Button5.tga");
	image6 = LoadImage("Button6.tga");
	image7 = LoadImage("Button7.tga");
	image8 = LoadImage("Button8.tga");
	image9 = LoadImage("logo.tga");
	image10 = LoadImage("tick.tga");
	image11 = LoadImage("sound1.tga");
	image12 = LoadImage("sound.tga");
	image13 = LoadImage("back.tga");
	image14 = LoadImage("back1.tga");

	EndLoop();
}

void myDisplayFunction()
{
	//Initializing static Variables
	static bool StartShapes = true;
	static int TimeCounter = time(NULL);
	static int score = 0;
	static int End = 0;
	static int MoveCondition;
	static double angle = 0;
	static double Acceleration = 0;
	//Initializing MainShape pointer based upon option selected from settings
	static MainShapes* b1;
	static int balltype = 1;
	static bool ballsetting = false;
	if (!ballsetting)
	{
		if (balltype == 2)
		{
			b1 = new MainSquare;
			ballsetting = 1;
		}
		else if (balltype == 3)
		{
			b1 = new MainHollow;
			ballsetting = 1;
		}
		else
		{
			b1 = new MainBall;
			ballsetting = 1;
		}
	}
	//Sound play variable
	static bool soundplaying = false;
	//AllShape stores all Shapes in memory and NowShape check the collision for current shape
	static ObstacleShapes* NowShape;
	static ObstacleShapes* AllShape[2];

	static double faster = 1;
	static bool ballcolorchange = true;
	static int collisionOnce = 1;
	static int pass = 1;
	//Background Image Y Coordinate
	static int ImageY = 0;
	static int ImageY1 = -500;
	static int Powerup = 5;
	static int filecond = 0;
	static int powercounter;
	static int x = 170, y = 155, x1 = 78, y1 = 280, sound = 0, count = 0;
	static int falldown = 0;
	if (!soundplaying)
	{
		engine->stopAllSounds();
		engine->play2D("music2.wav", true);
		soundplaying = true;
	}
	ClearScreen();
	//First Menu
	if (game == 0)
	{
		static int p;
		UploadImage(image, 0, 0, 500, 400);
		UploadImage(image9, 50, -20, 130, 200);
		static Rectanglee d(160, 180, 125);
		static BallsCircle c(160, 180, 50);
		c.DrawMovingShape(p);
		d.SetDirection(0);
		d.DrawMovingShape(p);
		UploadImage(image1, -115, -3, 290, 540);
		if ((Pmotion_x >= 119 && Pmotion_x <= 196) && (Pmotion_y >= 140 && Pmotion_y <= 220))
			UploadImage(image2, -115, -3, 290, 540);
		if ((mouse_x >= 119 && mouse_x <= 196) && (mouse_y >= 140 && mouse_y <= 220))
			game = 1;
		UploadImage(image3, 10, 250, 100, 110);
		if ((Pmotion_x >= 10 && Pmotion_x <= 120) && (Pmotion_y >= 250 && Pmotion_y <= 350))
			UploadImage(image4, 10, 250, 100, 110);
		if ((mouse_x >= 10 && mouse_x <= 120) && (mouse_y >= 250 && mouse_y <= 350))
			game = 3;
		UploadImage(image5, 200, 270, 70, 75);
		if ((Pmotion_x >= 200 && Pmotion_x <= 275) && (Pmotion_y >= 270 && Pmotion_y <= 340))
			UploadImage(image6, 200, 270, 72, 77);
		if ((mouse_x >= 200 && mouse_x <= 275) && (mouse_y >= 270 && mouse_y <= 340))
			game = 4;
		p++;
	}
	//End Menu
	if (game == 2)
	{
		static int openOnce = 0;
		static int cond = 0;
		static int changeno = 0;
		static char name[99];
		static int lowest;
		static int current;
		fstream file("HighScore.txt");
		if (!file.is_open())
		{
			file.open("HighScore.txt", ios::out);
			filecond = 1;
		}
		int number;
		file.getline(name, 99);
		file >> number;
		file.close();
		if (filecond == 0)
		{
			if (score >= number)
				filecond = 1;
			else
				filecond = 2;
		}
		if (filecond == 1)
		{
			fstream file1("HighScore.txt");
			Text(40, 120, "You made a High Score!", "Purple");
			Text(40, 140, "Enter your name: ", "Purple");
			InputText(200, 140, newname, 99, "Purple");
			if (Key == 13)
			{
				file1 << newname;
				file1 << "\n";
				file1 << score;
				file1.close();
				filecond = 2;
			}
		}
		if (filecond == 2)
		{
			int p = 0;
			ClearScreen();
			UploadImage(image, 0, 0, 500, 400);
			UploadImage(image9, 50, -20, 130, 200);
			UploadImage(image7, 90, 140, 120, 120);
			if ((Pmotion_x >= 100 && Pmotion_x <= 200) && (Pmotion_y >= 150 && Pmotion_y <= 250))
				UploadImage(image8, 90, 140, 120, 120);
			if ((mouse_x >= 100 && mouse_x <= 200) && (mouse_y >= 150 && mouse_y <= 250))
			{
				game = 1;
				b1->setAll(150, 375, 4);
				StartShapes = true;
				TimeCounter = time(NULL);
				score = 0;
				End = 0;
				MoveCondition;
				angle = 0;
				Acceleration = 0;
				faster = 1;
				ballcolorchange = true;
				collisionOnce = 1;
				pass = 1;
				ImageY = 0;
				ImageY1 = -500;
				Powerup = 5;
			}
			UploadImage(image3, 10, 250, 100, 110);
			if ((Pmotion_x >= 10 && Pmotion_x <= 120) && (Pmotion_y >= 250 && Pmotion_y <= 350))
				UploadImage(image4, 10, 250, 100, 110);
			if ((mouse_x >= 10 && mouse_x <= 120) && (mouse_y >= 250 && mouse_y <= 350))
				game = 5;
			UploadImage(image5, 200, 270, 70, 75);
			if ((Pmotion_x >= 200 && Pmotion_x <= 275) && (Pmotion_y >= 270 && Pmotion_y <= 340))
				UploadImage(image6, 200, 270, 72, 77);
			if ((mouse_x >= 200 && mouse_x <= 275) && (mouse_y >= 270 && mouse_y <= 340))
				game = 6;
			p++;
			Text(70, 135, "Your Score : ", "Red");
			Text(200, 135, (int)score, "Yellow");
		}
	}
	//HighScore Menu
	if (game == 3 || game == 5)
	{
		UploadImage(image, 0, 0, 500, 400);
		UploadImage(image9, 50, -20, 130, 200);
		ifstream HighScore("HighScore.txt");
		if (!HighScore.is_open())
		{
			Text(40, 200, "There is no High Score yet.", "Purple");
		}
		else
		{
			char name[99];
			char score[99];
			HighScore.getline(name, 99);
			HighScore.getline(score, 99);
			Text(40, 150, "User Name: ", "Blue");
			Text(200, 150, (char[99])name, "Blue");
			Text(40, 180, "High Score: ", "Blue");
			Text(200, 180, (char[99])score, "Purple");
		}
		HighScore.close();
		UploadImage(image13, 220, 30, 42, 47);
		if ((Pmotion_x >= 220 && Pmotion_x <= 265) && (Pmotion_y >= 30 && Pmotion_y <= 75))
			UploadImage(image14, 220, 30, 42, 47);
		if ((mouse_x >= 220 && mouse_x <= 265) && (mouse_y >= 30 && mouse_y <= 75))
		{
			if (game == 3)
				game = 0;
			else if (game == 5)
				game = 2;
		}
	}
	//Total Game
	if (game == 1)
	{
		filecond = 0;
		if (StartShapes)
		{
			engine1->setSoundVolume(0.5);
			AllShape[0] = new Rectanglee(150, 110, 100);
			AllShape[1] = new Rectanglee(150, 500, 100);
			NowShape = AllShape[0];
			StartShapes = false;
		}
		UploadImage(image, 0, ImageY, 500, 500);
		UploadImage(image, 0, ImageY1, 500, 500);
		if (ImageY > 485)
		{
			ImageY = (-500);
			ImageY1 = 0;
		}
		if (ImageY1 > 485)
		{
			ImageY1 = (-500);
			ImageY = 0;
		}

		if (End == 0)
		{
			b1->DrawShape();
		}

		for (int i = 0; i < MaxShapes; i++)
		{
			AllShape[i]->DrawMovingShape(angle);
		}
		if ((mouse_x>0 && mouse_y>0) || Keyboard == 32)
		{
			falldown = 1;
			mainspeed += 12;
			mouse_x = mouse_y = 0;
			Keyboard = 0;
			soundplaying = true;
			if (b1->GetOriginY() > 235)
			{
				MoveCondition = 0;
				up = 8;
			}
			else
			{
				MoveCondition = 1;
				up = 8;
			}
			Acceleration = 0;
			engine1->play2D("Sound Effects-jumping ball (1).ogg", false);
		}
		static int PowerTime = 0;
		Text(0, 30, "Power:", "Purple");
		Text(60, 30, (int)(Powerup), "Purple");
		if (SpecialKey == A_UP && Powerup != 0)
		{
			PowerTime = time(NULL);
			SpecialKey = 0;
			Powerup--;
		}
		if ((time(NULL) - PowerTime) <= 4)
		{
			Sleep(25);
		}
		if (End == 0)
		{
			if (MoveCondition == 0 && up != 0)
			{
				b1->OriginYAdd(5);
				up--;
				for (int i = 0; i < MaxShapes; i++)
				{
					if (AllShape[i]->getOriginY() == 100)
					{
						NowShape = AllShape[i];
						ballcolorchange = true;
					}
				}
				if (NowShape->getOriginY() == 330 && ballcolorchange)
				{
					powercounter++;
					if (powercounter % 3 == 0)
						Powerup++;
					score++;
					b1->ballcolorchange();
					faster += 0.05;
					ballcolorchange = false;
				}
				angle += faster;
			}
			else if (MoveCondition == 1 && up != 0)
			{
				for (int i = 0; i < MaxShapes; i++)
				{
					AllShape[i]->OriginYAdd(5);
					ImageY++;
					ImageY1++;
				}
				b1->OriginYAdd(0.75);
				up--;
				for (int i = 0; i < MaxShapes; i++)
				{
					if (AllShape[i]->getOriginY() == 100)
					{
						NowShape = AllShape[i];
						ballcolorchange = true;
					}
				}
				if (NowShape->getOriginY() == 330 && ballcolorchange)
				{
					powercounter++;
					if (powercounter % 3 == 0)
						Powerup++;
					score++;
					b1->ballcolorchange();
					pass = 0;
					faster += 0.05;
					ballcolorchange = false;
				}
				angle += faster;
			}
			else if (up == 0)
			{
				for (int i = 0; i < MaxShapes; i++)
				{
					if (AllShape[i]->getOriginY() == 100)
					{
						NowShape = AllShape[i];
						ballcolorchange = true;
					}
				}
				if (!(b1->GetOriginY() > 350) || falldown == 1)
				{
					Acceleration += 0.1;
					b1->OriginYsub(Acceleration);
				}
				if (NowShape->getOriginY() == 330 && ballcolorchange)
				{
					powercounter++;
					if (powercounter % 3 == 0)
						Powerup++;
					score++;
					b1->ballcolorchange();
					faster += 0.03;
					ballcolorchange = false;
				}
				angle += faster;
			}
			if (NowShape->getOriginY() > 350 && pass == 0)
			{
				int RandomShape = rand() % 8;
				//int RandomShape = 4;
				if (RandomShape == 0)
				{
					AllShape[1] = new Rectanglee(150, 0, 100);
					pass = 1;
					AllShape[0] = NowShape;
				}
				else if (RandomShape == 1)
				{
					AllShape[1] = new Circlee(150, 0, 65);
					pass = 1;
					AllShape[0] = NowShape;
				}
				else if (RandomShape == 2)
				{
					AllShape[1] = new Plus(225, 0, 100);
					pass = 1;
					AllShape[0] = NowShape;
				}
				else if (RandomShape == 3)
				{
					AllShape[1] = new Triangle(150, 0, 140);
					pass = 1;
					AllShape[0] = NowShape;
				}
				else if (RandomShape == 4)
				{
					AllShape[1] = new RunningLines(0);
					pass = 1;
					AllShape[0] = NowShape;
				}
				else if (RandomShape == 5)
				{
					AllShape[1] = new Infinity(150, 0, 100);
					pass = 1;
					AllShape[0] = NowShape;
				}
				else if (RandomShape == 6)
				{
					AllShape[1] = new BallsCircle(150, 0, 75);
					pass = 1;
					AllShape[0] = NowShape;
				}
				else if (RandomShape == 7)
				{
					AllShape[1] = new PlusInfinity(150, 0, 60);
					pass = 1;
					AllShape[0] = NowShape;
				}
			}
		}
		if ((NowShape->collision(b1->GetOriginY()) || (b1->getOriginY() >= 375)) && collisionOnce != 0)
		{
			End = 1;
			collisionOnce = 0;
		}
		if (End != 0)
		{

			if (End >0 && End <10)
			{
				overimage = LoadImage("1.tga");
				UploadImage(overimage, 100.0, b1->GetOriginY() - 30, 100.0, 100.0);
			}
			if (End >10 && End <20)
			{
				overimage = LoadImage("2.tga");
				UploadImage(overimage, 100.0, b1->GetOriginY() - 30, 100.0, 100.0);
			}
			else if (End >20 && End <30)
			{
				overimage = LoadImage("3.tga");
				UploadImage(overimage, 100.0, b1->GetOriginY() - 30, 100.0, 100.0);
			}
			else if (End >30 && End <40)
			{
				overimage = LoadImage("4.tga");
				UploadImage(overimage, 100.0, b1->GetOriginY() - 30, 100.0, 100.0);
			}
			else if (End >40 && End <50)
			{
				overimage = LoadImage("5.tga");
				UploadImage(overimage, 100.0, b1->GetOriginY() - 30, 100.0, 100.0);
			}
			else if (End >50 && End <60)
			{
				overimage = LoadImage("6.tga");
				UploadImage(overimage, 100.0, b1->GetOriginY() - 30, 100.0, 100.0);
			}
			else if (End >60 && End <70)
			{
				overimage = LoadImage("7.tga");
				UploadImage(overimage, 100.0, b1->GetOriginY() - 30, 100.0, 100.0);
			}
			else if (End > 70)
			{
				game = 2;
			}
			End++;
		}
		static int TimeOnce = 0;
		static int TimeM = 0;
		if ((time(NULL) - TimeCounter) % 60 == 0 && TimeOnce == 1)
		{
			TimeM++;
			TimeOnce = 0;
		}
		if ((time(NULL) - TimeCounter) % 60 == 30)
			TimeOnce = 1;
		Text(85, 20, "Time:", "Purple");
		Text(140, 20, (int)(TimeM), "Purple");
		Text(160, 20, ":", "Purple");
		Text(168, 20, (int)((time(NULL) - TimeCounter) % 60), "Purple");
		Text(210, 30, "Score:", "Purple");
		Text(270, 30, (int)score, "Purple");
	}
	//Settings Menu
	if (game == 4 || game == 6)
	{
		UploadImage(image, 0, 0, 500, 400);
		UploadImage(image9, 50, -20, 130, 200);
		CreateRectangle(150, 130, 20, 20, "Yellow", "Filled");
		CreateRectangle(152, 210, 20, 20, "Purple", "Hollow", .2);
		CreateCircle(160, 180, 10, "Blue", "Filled");
		UploadImage(image10, x, y, 42, 47);
		UploadImage(image10, x1, y1, 42, 47);
		UploadImage(image13, 220, 30, 42, 47);
		if ((mouse_x >= 150 && mouse_x <= 170) && (mouse_y >= 130 && mouse_y <= 150))
		{
			x = 170, y = 115;
			balltype = 2;
			ballsetting = false;
		}
		if ((mouse_x >= 150 && mouse_x <= 170) && (mouse_y >= 170 && mouse_y <= 190))
		{
			x = 170, y = 155;
			balltype = 1;
			ballsetting = false;
		}
		if ((mouse_x >= 150 && mouse_x <= 170) && (mouse_y >= 204 && mouse_y <= 230))
		{
			x = 170, y = 195;
			balltype = 3;
			ballsetting = false;
		}
		if ((Pmotion_x >= 220 && Pmotion_x <= 265) && (Pmotion_y >= 30 && Pmotion_y <= 75))
			UploadImage(image14, 220, 30, 42, 47);
		if ((mouse_x >= 220 && mouse_x <= 265) && (mouse_y >= 30 && mouse_y <= 75))
		{
			if (game == 4)
				game = 0;
			else if (game == 6)
				game = 2;
		}
		UploadImage(image12, 160, 280, 50, 50);
		UploadImage(image11, 30, 280, 50, 50);
		if ((mouse_x >= 34 && mouse_x <= 73) && (mouse_y >= 290 && mouse_y <= 320))
		{
			x1 = 78;
			soundplaying = false;
			mouse_x = mouse_y = 0;
		}
		if ((mouse_x >= 165 && mouse_x <= 205) && (mouse_y >= 290 && mouse_y <= 320))
		{
			x1 = 210;
			engine->stopAllSounds();
		}
		Text(30, 135, "SHAPES", "White");
		Text(30, 275, "SOUND", "White");
	}
	RefreshScreen();
}