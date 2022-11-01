#ifndef HEX_H
#define HEX_H

class Hex
{
private:
	int hx;
	int hy;
	int an;
	int pr;
	int ag;
	int na;
	bool bd;
	bool lv;

public:
	Hex();
	Hex(int x, int y, int n, int v);
	void setHX(int);
	int getHX();
	void setHY(int);
	int getHY();
	void setAN(int);
	int getAN();
	void setPR(int);
	int getPR();
	void setBD(bool);
	bool getBD();
	void setLV(bool);
	bool getLV();
	void setNA(int);
	int getNA();
	int angle(Hex** g, int XG, int YG);
	bool find(Hex** g, int XG, int YG, int a);
	void onborder(Hex** g, int XG, int YG);
	int* loopneigh(Hex** g, int XG, int YG, int start, int col);
	void add(Hex** g, int XG, int YG);
	void rem(Hex** g, int XG, int YG);
};
#endif // HEX_H