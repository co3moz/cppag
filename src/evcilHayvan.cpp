#include <iostream>
#include "evcilHayvan.h"
using namespace std;

int evcilHayvan::toplamEvcilHayvan = 0;

evcilHayvan::evcilHayvan() {
	evcilHayvan::toplamEvcilHayvan++;
	
	hayvanAdi = new char[20];
	hayvanSesi = new char[10];
	
	setTokluk(50);
	setOyun(50);
	setKacti(false);
	
	setTextWidth(2);
	
	d_iconsdrawed = false;
	d_crossdrawed = false;
}

evcilHayvan::~evcilHayvan() {
	delete[] hayvanAdi;
	delete[] hayvanSesi;
	delete[] animalImage;
}

void evcilHayvan::fillAnimalImage(char* t, int l) {
	animalImage = new char[l];
	for(int i=0;i<l;i++)
		animalImage[i] = t[i];
	animalImageLen = l;
}

char evcilHayvan::getOyunKey() {
	return oyunKey;
}

void evcilHayvan::setOyunKey(char _oyunKey) {
	oyunKey = _oyunKey;
}

char evcilHayvan::getToklukKey() {
	return toklukKey;
}

void evcilHayvan::setToklukKey(char _toklukKey) {
	toklukKey = _toklukKey;
}

void evcilHayvan::setCoords(int _x, int _y) {
	x = _x;
	y = _y;
}

int evcilHayvan::getX() {
	return x;
}

int evcilHayvan::getY() {
	return y;
}

int evcilHayvan::getTextWidth() {
	return textWidth;
}

void evcilHayvan::setTextWidth(int w) {
	textWidth = w;
}

void evcilHayvan::drawCross() {
	if(d_crossdrawed == false)
	{
		int pattern[] = {0x000000,0x404040,0xBF1E2E,};
		char cross[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,2,1,0,0,0,0,0,0,0,1,2,1,0,0,0,1,2,1,0,0,0,0,0,1,2,1,0,0,0,0,0,1,2,1,0,0,0,1,2,1,0,0,0,0,0,0,0,1,2,1,0,1,2,1,0,0,0,0,0,0,0,0,0,1,2,1,2,1,0,0,0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,1,0,0,0,0,0,0,0,0,0,1,2,1,0,1,2,1,0,0,0,0,0,0,0,1,2,1,0,0,0,1,2,1,0,0,0,0,0,1,2,1,0,0,0,0,0,1,2,1,0,0,0,1,2,1,0,0,0,0,0,0,0,1,2,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
		drawGroupPatternW(getX(),getY(),cross, sizeof(cross), 15, pattern, 10);
		d_crossdrawed = true;
	}
}

void evcilHayvan::drawIconOyunTokluk() {
	if(d_iconsdrawed == false) {
		int patternOyun[] = {0x000000,0xFF9C01,0xFEDA00,0xFFFFFF,};
		char imageOyun[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,1,2,2,3,3,3,2,2,3,3,3,2,2,1,0,0,0,0,1,2,3,3,3,3,2,2,3,3,3,3,2,1,0,0,0,1,2,2,3,3,0,0,2,2,0,0,3,3,2,2,1,0,0,1,2,2,3,3,0,0,2,2,0,0,3,3,2,2,1,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,1,2,2,0,2,2,2,2,2,2,0,2,2,1,0,0,0,0,1,2,2,2,0,0,0,0,0,0,2,2,2,1,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
		
		int patternTokluk[] = {0x000000,0xFFFECB,0x663200,0xDC0000,0x996533,0xCC9866,0xFFCB99,};
		char imageTokluk[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,3,2,2,2,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,4,3,3,3,3,3,3,3,3,3,3,3,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,1,1,0,0,0,0,0,0,0,0,1,1,1,1,2,2,3,3,3,3,1,1,1,1,1,1,3,3,3,3,1,1,2,2,0,0,0,0,0,0,0,0,1,1,1,1,2,2,3,3,3,3,1,1,1,1,1,1,3,3,3,3,1,1,2,2,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,1,1,1,1,3,3,3,3,3,3,1,1,2,2,5,4,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,1,1,1,1,3,3,3,3,3,3,1,1,2,2,4,4,0,0,0,0,1,1,2,2,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,1,1,2,2,4,4,4,4,0,0,0,0,1,1,2,2,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,1,1,2,2,4,4,4,4,0,0,0,0,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,2,2,4,4,4,4,0,0,0,0,0,0,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,2,2,4,4,4,4,0,0,0,0,0,0,6,5,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,4,4,4,4,0,0,0,0,0,0,0,0,5,5,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,4,4,4,4,0,0,0,0,0,0,0,0,1,1,7,6,4,4,4,4,4,4,2,2,2,2,2,2,2,2,4,4,4,4,0,0,0,0,0,0,0,0,0,0,1,1,6,6,4,4,4,4,4,4,2,2,2,2,2,2,2,2,4,4,4,4,0,0,0,0,0,0,0,0,0,0,1,1,6,6,6,6,6,6,5,5,5,5,5,5,5,5,5,5,4,4,0,0,0,0,0,0,0,0,0,0,0,0,1,1,6,6,6,6,6,6,5,5,5,5,5,5,5,5,5,5,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
		
		drawGroupPatternW(getX() + 20, getY() + 187, imageOyun, sizeof(imageOyun), 18, patternOyun, 2);
		drawGroupPattern(getX() + 20, getY() + 160, imageTokluk, sizeof(imageTokluk), 32, patternTokluk);
		
		setColor(C_SARI);
		drawCharW(getX()+8, getY()+197, getOyunKey(), 2);
		drawCharW(getX()+8, getY()+170, getToklukKey(), 2);
		
		d_iconsdrawed = true;
	}
}

void evcilHayvan::clearIconOyunTokluk() {
	if(d_iconsdrawed) {
		
		setColor(0,0,0);
		drawSquare(getX() + 20, getY() + 187, getX() + 56,  getY() + 223);
		drawSquare(getX() + 20, getY() + 160, getX() + 52,  getY() + 192);
		
		setColor(C_SIYAH);
		drawCharW(getX()+8, getY()+197, getOyunKey(), 2);
		drawCharW(getX()+8, getY()+170, getToklukKey(), 2);
		
		d_iconsdrawed = false;
	}
}

int evcilHayvan::getTextPadding() {
	return d_textpadding;
}

void evcilHayvan::setTextPadding(int _d_textpadding) {
	d_textpadding = _d_textpadding;
}

void evcilHayvan::drawOyunTokluk() {
	d_oyun = getOyun();
	d_tokluk = getTokluk();
	
	char k = getTokluk() > 250 ? 255 : 255*getTokluk()/250;
	char p = getOyun() > 250 ? 255 : 255*getOyun()/250;
	
	setColor(255-k, k, 0);
	drawIntW(getX()+63,getY()+160,getTokluk(),getTextWidth());
	
	setColor(255-p, p, 0);
	drawIntW(getX()+63,getY()+195,getOyun(),getTextWidth());
}

void evcilHayvan::updateOyunTokluk() {
	setColor(0,0,0);
	drawIntW(getX()+63,getY()+160,d_tokluk,getTextWidth());
	
	setColor(0,0,0);
	drawIntW(getX()+63,getY()+195,d_oyun,getTextWidth());
	
	if(!getKacti())
		drawOyunTokluk();
	else {
		clearIconOyunTokluk();
		
		int pattern[] = {0,0x333333,0x333333,0x333333,0x333333,};
		drawGroupPattern(getX(),getY(),animalImage,animalImageLen,153,pattern);
		
		setColor(0x33,0x33,0x33);
		drawTextW(getX()+10, getY()+165, "Ka\x87t\xD :[", 2);
	}
}

void evcilHayvan::drawSesCikar() {
	setColor(0,0,0);
	drawSquare(50,0,600,30);

	setColor(0,255,255);
	drawTextCenterW(getX()+d_textpadding,getY() - 30, getHayvanSesi(), 3);
}

void evcilHayvan::gorevDoyur() {
	setTokluk(getTokluk() + 50);
}

void evcilHayvan::gorevOyna() {
	setOyun(getOyun() + 50);
}

void evcilHayvan::gorevHayvanKacti() {
	setKacti(true);
	evcilHayvan::toplamEvcilHayvan--;
}

bool evcilHayvan::elBasi() {
	if(!getKacti()) {
		drawSesCikar();
		
		char bas = getch();
		if(bas == getOyunKey())
			gorevOyna();
		else if(bas == getToklukKey())
			gorevDoyur();
			
		setTokluk(getTokluk() - 20);
		setOyun(getOyun() - 20);
		
		if((getTokluk() <= 0) || (getOyun() <= 0))
			gorevHayvanKacti();
		updateOyunTokluk();
	}
	return !getKacti();
}

char* evcilHayvan::getHayvanAdi() {
	return hayvanAdi;
}

void evcilHayvan::setHayvanAdi(char* _hayvanAdi) {
	strcpy(hayvanAdi, _hayvanAdi);
}

const char* evcilHayvan::getHayvanSesi() {
	if(getTokluk() > 50)
		return hayvanSesi;
	else
	{
		string ses;
		ses.append(hayvanSesi);
		ses.append(" ");
		ses.append(hayvanSesi);
		return ses.c_str();
		
	}
}

void evcilHayvan::setHayvanSesi(char* _hayvanSesi) {
	strcpy(hayvanSesi, _hayvanSesi);
}

int evcilHayvan::getTokluk() {
	return tokluk;
}

void evcilHayvan::setTokluk(int _tokluk) {
	tokluk = _tokluk;
}

int evcilHayvan::getOyun() {
	return oyun;
}

void evcilHayvan::setOyun(int _oyun) {
	oyun = _oyun;
}

bool evcilHayvan::getKacti() {
	return kacti;
}

void evcilHayvan::setKacti(bool _kacti) {
	kacti = _kacti;
}