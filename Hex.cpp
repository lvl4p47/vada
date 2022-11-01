#include "Hex.h"
#include <cmath>

Hex::Hex()
{
	hx = 0;
	hy = 0;
	an = 0;
	pr = 0;
	bd = false;
	lv = 0;
	na = 0;
	ag = 0;
}
Hex::Hex(int x, int y, int n, int p)
{
	hx = x;
	hy = y;
	an = n;
	pr = p;
}
void Hex::setHX(int x)
{
	hx = x;
}
int Hex::getHX()
{
	return hx;
}
void Hex::setHY(int y)
{
	hy = y;
}
int Hex::getHY()
{
	return hy;
}
void Hex::setAN(int n)
{
	an = n;
}
int Hex::getAN()
{
	return an;
}
void Hex::setPR(int p)
{
	pr = p;
}
int Hex::getPR()
{
	return pr;
}
void Hex::setBD(bool b)
{
	bd = b;
}
bool Hex::getBD()
{
	return bd;
}
void Hex::setLV(bool l)
{
	lv = l;
}
bool Hex::getLV()
{
	return lv;
}
void Hex::setNA(int n)
{
	na = n;
}
int Hex::getNA()
{
	return na;
}
bool Hex::find(Hex** g, int XG, int YG, int a)
{
	int r[6] = { -1, -1, 0, 1, 1, 0 };
	int dx, dy;
	for (int i = 0; i < 6; i++)
	{
		dx = r[(i + 1) % 6];
		dy = r[i];
		if (hy + dy >= 0 && hy + dy < YG && hx + dx >= 0 && hx + dx < XG)
		{
			if (g[hy + dy][hx + dx].getAN() == a)
				return true;
		}
	}
	return false;
}
void Hex::onborder(Hex** g, int XG, int YG)
{
	bd = false;
	if (hx == XG - 1 || hx == 0 || hy == YG - 1 || hy == 0)
		bd = true;
	else
	{
		int nc = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (i + j != 0)
				{
					if (hy + i >= 0 && hy + i < YG && hx + j >= 0 && hx + j < XG)
						if (g[hy + i][hx + j].getAN() != an)
							bd = true;
				}
			}
		}
	}
}
int* Hex::loopneigh(Hex** g, int XG, int YG, int start, int col)
{
	static int a[3] = { -1, -1, -1 };
	int r[6] = { -1, -1, 0, 1, 1, 0 }; // r[i] = y, r[i + 1] = x
	int dx, dy, dxn, dyn, n1an, n2an;
	bool n1bd;

	for (int i = 6; i >= 0; i--)
	{
		dx = r[(i + 1 + start) % 6];
		dy = r[(i + start) % 6];
		dxn = r[(i + 2 + start) % 6];
		dyn = r[(i + 1 + start) % 6];

		if (hx + dx > XG - 1 || hx + dx < 0 || hy + dy > YG - 1 || hy + dy < 0 ||
			hx + dxn > XG - 1 || hx + dxn < 0 || hy + dyn > YG - 1 || hy + dyn < 0)
		{
			if (hx + dx > XG - 1 || hx + dx < 0 || hy + dy > YG - 1 || hy + dy < 0)
			{
				n1bd = false;
				n1an = -1;
			}
			else
			{
				n1bd = g[hy + dy][hx + dx].getBD();
				n1an = g[hy + dy][hx + dx].getAN();
			}
			if (hx + dxn > XG - 1 || hx + dxn < 0 || hy + dyn > YG - 1 || hy + dyn < 0)
			{
				n2an = -1;
			}
			else
			{
				n2an = g[hy + dyn][hx + dxn].getAN();
			}
		}
		else
		{
			n1bd = g[hy + dy][hx + dx].getBD();
			n1an = g[hy + dy][hx + dx].getAN();
			n2an = g[hy + dyn][hx + dxn].getAN();
		}
			
		if ((n1bd == bd) &&
			(n1an == an) &&
			(n2an != an))
		{
			a[0] = dy + hy;
			a[1] = dx + hx;
			a[2] = (i + start + 2) % 6;
			i = -1;
		}
	}
	g[hy][hx].setLV(col);
	return a;
}
int Hex::angle(Hex** g, int XG, int YG)
{
	int r[6] = { -1, -1, 0, 1, 1, 0 };
	int dx, dy, c = 0;
	ag = 0;
	for (int i = 0; i < 13; i++)
	{
		dx = r[(i + 1) % 6];
		dy = r[i % 6];
		if (hy + dy >= 0 && hy + dy < YG && hx + dx >= 0 && hx + dx < XG)
		{
			if (g[hy + dy][hx + dx].getAN() != an)
			{
				c++;
			}
			if (g[hy + dy][hx + dx].getAN() == an)
			{
				if (c > ag)
					ag = c;
				c = 0;
			}
		}
	}
	if (c > ag)
		ag = c;
	//ag = 6 - ag;
	return ag;
}
void Hex::add(Hex** g, int XG, int YG)
{
	int r[6] = { -1, -1, 0, 1, 1, 0 };
	int dx, dy, st = rand() % 6;

	for (int i = st; i < st + 6; i++)
	{
		dx = r[(i + 1) % 6];
		dy = r[i % 6];
		if (hy + dy >= 0 && hy + dy < YG && hx + dx >= 0 && hx + dx < XG)
		{
			if (g[hy + dy][hx + dx].getAN() == 0)
			{
				g[hy + dy][hx + dx].setAN(an);
				i = st + 7;
			}
		}
	}
}
void Hex::rem(Hex** g, int XG, int YG)
{
	g[hy][hx].setAN(0);
}