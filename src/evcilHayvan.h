#ifndef evcilHayvan_H
#define evcilHayvan_H
class evcilHayvan {
	private:
	// Game Topic Data
		int tokluk;
		int oyun;
		bool kacti;
		
		char* hayvanAdi;
		char* hayvanSesi;
		
		
	// Game Playing Data
		char oyunKey;
		char toklukKey;
	
	
	// Game Drawing Data
		int x;
		int y;
		int textWidth;
		
		int d_tokluk;
		int d_oyun;
		
		int d_textpadding;
		
		bool d_iconsdrawed;
		bool d_crossdrawed;
		
	protected:
		char* animalImage;
		int animalImageLen;
		
	public:
	// Game Topic Functions
		int getTokluk();
		void setTokluk(int);
		
		int getOyun();
		void setOyun(int);
		
		bool getKacti();
		void setKacti(bool);
		
		char* getHayvanAdi();
		void setHayvanAdi(char*);
		
		const char* getHayvanSesi();
		void setHayvanSesi(char*);
		
		void gorevDoyur();
		void gorevOyna();
		void gorevHayvanKacti();
		
		bool elBasi();
		
		static int toplamEvcilHayvan;
		
		evcilHayvan();
		~evcilHayvan();
	
	
	// Game Playing Functions
		char getOyunKey();
		void setOyunKey(char);
		
		char getToklukKey();
		void setToklukKey(char);
	
	
	// Game Drawing Functions	
		int getX();
		int getY();
		void setCoords(int, int);
		
		void fillAnimalImage(char*, int);
		
		int getTextPadding();
		void setTextPadding(int);
		
		int getTextWidth();
		void setTextWidth(int);
		
		void drawCross();
		void drawIconOyunTokluk();
		void drawOyunTokluk();
		void updateOyunTokluk();
		void clearIconOyunTokluk();
		
		void drawSesCikar();
};
#endif