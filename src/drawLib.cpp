/*
	drawLib | Çizim Kütüphanesi
	yazar: Doðan DERYA co3moz
	tarih: 25.03.2014-günümüz

*/

#include <iostream>
#include <windows.h>
#include <conio.h>

#define C_MAVI 		0,		0,		0xFF
#define C_KIRMIZI 	0xFF,	0,		0
#define C_YESIL 	0,		0xFF,	0
#define C_SARI		0xFF,	0xFF,	0
#define C_MOR 		0x66,	0,	0x99
#define C_PEMBE		0xFF,	0,		0xFF
#define C_AQUA 		0,		0xFF,	0xFF
#define C_SIYAH 	0,		0,		0
#define C_BEYAZ 	0xFF, 	0xFF,	0xFF
#define C_GRI 		0x7D,	0x7D,	0x7D

#define R(X) "\x2" X
#define S_MAVI "\x2\x1\x1\xFF"
#define S_KIRMIZI "\x2\xFF\x1\x1"
#define S_YESIL "\x2\x1\xFF\x1"
#define S_SARI "\x2\xFF\xFF\x1"
#define S_SIYAH "\x2\x1\x1\x1"
#define S_PEMBE "\x2\xFF\x1\xFF"
#define S_MOR "\x2\x66\x01\x99"
#define S_TURUNCU "\x2\xFF\x7F\x1"

HWND myconsole;
HDC mydc;
COLORREF cr;

int drawChar(int, int, char);
void drawGroup(int, int, bool*, int, int);
char charToAlfabeSira(char);

bool alfabe[][45] = {
	{0,1,1,1,0,1,0,0,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,1,0,0,1,0,1,1,1,0},//0			0
	{0,0,1,0,0,0,1,1,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,1,1,1,1},//1			1
	{1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1},//2			2
	{1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1},//3			3
	{1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},//4			4
	{1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1},//5			5
	{1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1},//6			6
	{1,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},//7			7
	{1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1},//8			8
	{1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1},//9			9
	{0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1},//A			10
	{1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0},//B			11
	{0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1},//C			12
	{1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0},//D			13
	{1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1},//E			14
	{1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0},//F			15
	{0,1,1,1,0,1,0,0,0,1,1,0,0,0,0,1,0,1,1,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0},//G			16
	{1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1},//H			17
	{1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,1,1,1,1},//I			18
	{0,0,1,1,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1},//J			19
	{1,0,0,0,1,1,0,0,1,0,1,0,1,0,0,1,1,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,1},//K			20
	{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1},//L			21
	{1,0,0,0,1,1,1,0,1,1,1,0,1,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1},//M			22
	{1,0,0,0,1,1,1,0,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,0,1,1,1,0,0,0,1},//N			23
	{0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0},//O			24
	{1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0},//P			25
	{0,0,0,0,0,0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0,0,0,0,0,1},//Q			26
	{1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,1},//R			27
	{0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,0},//S			28
	{1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},//T			29
	{1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0},//U			30
	{1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0},//V			31
	{1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1,1,1,0},//W			32
	{1,0,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,1,0,0,0,1,1,1,0,0,1,0,1,0,1,0,0,0,1},//X			33
	{1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},//Y			34
	{1,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,1},//Z			35
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//Blok		36
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//Boþ		37
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//Altçizgi	38
	{0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},//Ünlem		39
	{1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1},//3 yat çiz	40
	{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},//Eþittir	41
	{1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1},//Dikdört	42
	{0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//Üçgen		43
	{0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,1,0,0},//Þ			44
	{0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,1,0,0,0,1,1,0,0},//Ç			45
	{0,1,0,1,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0},//Ö			46
	{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1},//a			47
	{1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0},//b			48
	{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1},//c			49
	{0,0,0,0,1,0,0,0,0,1,0,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0},//d			50
	{0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1},//e			51
	{0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0},//f			52
	{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0},//g			53
	{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1},//h			54
	{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},//i			55
	{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,1,1,1,0},//j			56
	{1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,0,1,1,0,0,0,1,0,1,0,0,1,0,0,1,0},//k			57
	{0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0},//l			58
	{0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,1,0,1,0,1,1,0,0,0,1,1,0,0,0,1},//m			59
	{0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1},//n			60
	{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0},//o			61
	{0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,0,1,0,0,0,0},//p			62
	{0,0,0,0,0,0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,0,1,1,1,1,0,0,0,0,1,0,0,0,0,1},//q			63
	{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0},//r			64
	{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0},//s			65
	{0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},//t			66
	{0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0},//u			67
	{0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0},//v			68
	{0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1,1,1,0},//w			69
	{0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1},//x			70
	{0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0,0,0,1,0,0,0,0,1,1,0},//y			71
	{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,1,1,1,1,1},//z			72
	{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},//ý			73
	{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,1,0,0},//þ			74
	{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,1,0,0,0,1,1,0,0},//ç			75
	{0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0},//ð			76
	{0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0,1,1,1,1,0,0,0,1,1,1,1,1,0},//Ð			77
	{0,1,0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0},//ü			78
	{0,1,0,1,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0},//Ü			79
	{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0},//:			80
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //- 81
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0}, //. 82
	{0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //' 83
	{1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,0,0}, //[ 84
	{0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1}, //] 85
	{0,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0}, //? 86
};


void connectConsole() {
	myconsole = GetConsoleWindow();
	mydc = GetDC(myconsole);
	
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void disconnectConsole() {
	ReleaseDC(myconsole, mydc);
}

void setColor(char r, char g, char b) {
	cr = RGB(r,g,b);
}

COLORREF getColor() {
	return cr;
}

char* fetchText(int x, int y, int len) {
	char* a = new char[len];
	char c;
	int l = x, at = 0;
	while((c = getch()) != '\r') {
		if( c == 8 ) {
			l -= 7;
			COLORREF temp = getColor();
			cr = RGB(0,0,0);
			drawChar(x + (l - x), y, a[--at]);
			cr = temp;
			a[at] = 0;
			continue;
		}
		a[at++] = c;
		l = drawChar(x + (l - x) ,y, c);
	}
	a[at] = 0;
	return &a[0];
}

void drawSquare(int x1, int y1, int x2, int y2) {
	for(int x = x1; x <= x2; x++) {
		for(int y = y1; y <= y2; y++) {
			SetPixel(mydc, x,y, cr);
		}
	}
}

char charToAlfabeSira(char in) {
	if((48 <= in) && (in <= 57)) return in - 48;
	if((65 <= in) && (in <= 90)) return in - 55;
	if((97 <= in) && (in <= 122)) return in - 50;
	if(in == 32)  return 37;
	if(in == 0x3) return 38;
	if(in == 33)  return 39;
	if(in == 0x4) return 40;
	if(in == 61) return 41;
	if(in == 0x5) return 42;
	if(in == -128) return 45;
	if(in == -121) return 75;
	if(in == -108) return 46;
	if(in == -103) return 46; // Ö
	if(in == -97) return 74;
	if(in == -98) return 44;
	if(in == -89) return 76; // ð
	if(in == -90) return 77; // Ð
	if(in == -127) return 78; // ü
	if(in == -102) return 79; // Ü
	if(in == -2) return 74;
	if(in == ':') return 80;
	if(in == '-') return 81;
	if(in == '.') return 82;
	if(in == '\'') return 83;
	if(in == '[') return 84;
	if(in == ']') return 85;
	if(in == '?') return 86;
	return in+60;
}

void drawGroup(int x, int y, bool* Group, int size, int stack) {
	for(int i = 0; i<size;i++) {
		if(Group[i] == 1)
			SetPixel(mydc, x+i%stack,y+i/stack, cr);
	}
}

void drawGroupPattern(int x, int y, char* Group, int size, int stack, int* pattern) {
	for(int i = 0; i<size;i++) {
		if(Group[i])
			SetPixel(mydc, x+i%stack,y+i/stack, RGB((pattern[Group[i]]/65536) % 256,(pattern[Group[i]]/256) % 256,pattern[Group[i]] % 256));
	}
}

void drawGroupPatternShort(int x, int y, short* Group, int size, int stack, int* pattern) {
	for(int i = 0; i<size;i++) {
		if(Group[i])
			SetPixel(mydc, x+i%stack,y+i/stack, RGB((pattern[Group[i]]/65536) % 256,(pattern[Group[i]]/256) % 256,pattern[Group[i]] % 256));
	}
}

void drawGroupW(int x, int y, bool* Group, int size, int stack, int w) {
	for(int i = 0; i<size;i++) {
		if(Group[i] == 1) {
			drawSquare((x+w*(i%stack)),(y+w*(i/stack)),(x+w*(i%stack))+w,(y+w*(i/stack))+w);
		}
	}
}

void drawGroupIntW(int x, int y, int* Group, int size, int stack, int w) {
	for(int i = 0; i<size;i++) {
		if(Group[i]) {
			cr = RGB((Group[i]/65536) % 256,(Group[i]/256) % 256,Group[i] % 256);
			drawSquare((x+w*(i%stack)),(y+w*(i/stack)),(x+w*(i%stack))+w,(y+w*(i/stack))+w);
		}
	}
}

void drawGroupPatternW(int x, int y, char* Group, int size, int stack, int* pattern, int w) {
	if(w == 0) return drawGroupPattern(x,y,Group,size,stack,pattern);
	for(int i = 0; i<size;i++) {
		if(Group[i]) {
			cr = RGB((pattern[Group[i]]/65536) % 256,(pattern[Group[i]]/256) % 256,pattern[Group[i]] % 256);
			drawSquare((x+w*(i%stack)),(y+w*(i/stack)),(x+w*(i%stack))+w,(y+w*(i/stack))+w);
		}
	}
}

void drawGroupPatternShortW(int x, int y, short* Group, int size, int stack, int* pattern, int w) {
	for(int i = 0; i<size;i++) {
		if(Group[i]) {
			cr = RGB((pattern[Group[i]]/65536) % 256,(pattern[Group[i]]/256) % 256,pattern[Group[i]] % 256);
			drawSquare((x+w*(i%stack)),(y+w*(i/stack)),(x+w*(i%stack))+w,(y+w*(i/stack))+w);
		}
	}
}

void drawGroupPatternIntW(int x, int y, int* Group, int size, int stack, int* pattern, int w) {
	for(int i = 0; i<size;i++) {
		if(Group[i]) {
			cr = RGB((pattern[Group[i]]/65536) % 256,(pattern[Group[i]]/256) % 256,pattern[Group[i]] % 256);
			drawSquare((x+w*(i%stack)),(y+w*(i/stack)),(x+w*(i%stack))+w,(y+w*(i/stack))+w);
		}
	}
}


int drawText(int x, int y, const char text[]) {
	int i = 0;
	int k = 0;
	for(; i<strlen(text);i++) {
		if(text[i] == 0x2) {
			setColor(text[i+1],text[i+2],text[i+3]);
			i += 3;
			k += 4;
			continue;
		}
		drawGroup(x+(i-k)*7,y, alfabe[charToAlfabeSira(text[i])], 45, 5);
	}
	return x + (i-k)*7;
}

int calculateEnd(int x, int y, const char text[]) {
	int i = 0;
	int k = 0;
	for(; i<strlen(text);i++) {
		if(text[i] == 0x2) {
			i += 3;
			k += 4;
			continue;
		}
	}
	return x + (i-k)*7;
}

int calculateEndW(int x, int y, const char text[], int w) {
	int i = 0;
	int k = 0;
	for(; i<strlen(text);i++) {
		if(text[i] == 0x2) {
			i += 3;
			k += 4;
			continue;
		}
	}
	return x + (i-k)*7*w;
}

int drawTextCenter(int x, int y, const char text[]) {
	drawText(x-((calculateEnd(x,y,text)-x)/2),y,text);
}

int drawTextWithPadding(int x, int y, const char text[], int padding) {
	x = x+(x + padding - calculateEnd(x, y, text))/2;
	int i = 0;
	int k = 0;
	for(; i<strlen(text);i++) {
		if(text[i] == 0x2) {
			setColor(text[i+1],text[i+2],text[i+3]);
			i += 3;
			k += 4;
			continue;
		}
		drawGroup(x+(i-k)*7,y, alfabe[charToAlfabeSira(text[i])], 45, 5);
	}
	return x + (i-k)*7;
}

int drawInt(int x, int y, int s) {
	char *buffer = new char[33];
	itoa(s, buffer, 10);
	return drawText(x,y, (const char*)buffer);
}


int drawChar(int x, int y, char c) {
	drawGroup(x,y,alfabe[charToAlfabeSira(c)], 45, 5);
	return x+7;
}

int drawTextW(int x, int y, const char text[], int w) {
	int i = 0;
	int k = 0;
	for(; i<strlen(text);i++) {
		if(text[i] == 0x2) {
			setColor(text[i+1],text[i+2],text[i+3]);
			i += 3;
			k += 4;
			continue;
		}
		drawGroupW(x+(i-k)*7*w,y, alfabe[charToAlfabeSira(text[i])], 45, 5, w);
	}
	return x + (i-k)*7*w;
}

int drawTextCenterW(int x, int y, const char text[], int w) {
	drawTextW(x-((calculateEndW(x,y,text,w)-x)/2),y,text,w);
}

int drawTextWithPaddingW(int x, int y, const char text[], int padding, int w) {
	x = x+(x + padding*7*w - calculateEndW(x, y, text,w))/2;
	int i = 0;
	int k = 0;
	for(; i<strlen(text);i++) {
		if(text[i] == 0x2) {
			setColor(text[i+1],text[i+2],text[i+3]);
			i += 3;
			k += 4;
			continue;
		}
		drawGroupW(x+(i-k)*7*w,y, alfabe[charToAlfabeSira(text[i])], 45, 5,w);
	}
	return x + (i-k)*7*w;
}


int drawIntW(int x, int y, int s, int w) {
	char *buffer = new char[33];
	itoa(s, buffer, 10);
	return drawTextW(x,y, (const char*)buffer,w);
}

int drawCharW(int x, int y, char c, int w) {
	drawGroupW(x,y,alfabe[charToAlfabeSira(c)], 45, 5, w);
	return x+7*w;
}
