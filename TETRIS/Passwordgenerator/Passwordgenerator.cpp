#include <iostream>
#include <conio.h>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

string field1 = "############################################";
string field2 = "#                                          #";
vector <string> field(30 ,field2);

string field3 = "######################";
string field4 = "#                    #";
vector <string> fieldx(15, field4);

enum dir { STOP,LEFT, RIGHT , UP , DOWN, NUL };
dir dr;

struct figure {
	vector<string> f;
private:
	vector<string> f0;

	vector<string> f11 = { "  aa  ","  aa  ","aaaaaa", "aaaaaa" };
	vector<string> f12 = { "aa  ","aa  ","aaaa","aaaa","aa  ","aa  " };
	vector<string> f13 = { "aaaaaa","aaaaaa","  aa  ","  aa  " };
	vector<string> f14 = { "  aa","  aa","aaaa","aaaa","  aa","  aa" };

	vector<string> f21 = { "OOOO","OOOO","OOOO","OOOO" };

	vector<string> f31 = { "II","II","II","II","II","II","II","II" };
	vector<string> f32 = { "IIIIIIII","IIIIIIII"};

	vector<string> f41 = { "    LL","    LL","LLLLLL","LLLLLL" };
	vector<string> f42 = { "LL  ","LL  ","LL  ", "LL  ", "LLLL", "LLLL" };
	vector<string> f43 = { "LLLLLL","LLLLLL","LL    ","LL    " };
	vector<string> f44 = { "LLLL","LLLL","  LL", "  LL", "  LL", "  LL" };

	vector<string> f51 = { "JJ    ","JJ    ","JJJJJJ","JJJJJJ" };
	vector<string> f52 = { "JJJJ","JJJJ","JJ  ","JJ  ","JJ  ","JJ  " };
	vector<string> f53 = { "JJJJJJ","JJJJJJ","    JJ","    JJ" };
	vector<string> f54 = { "  JJ","  JJ","  JJ","  JJ","JJJJ","JJJJ" };
	
	vector<string> f61 = { "ZZZZ  ","ZZZZ  ","  ZZZZ","  ZZZZ" };
	vector<string> f62 = { "  ZZ","  ZZ","ZZZZ","ZZZZ","ZZ  ","ZZ  " };

	vector<string> f71 = { "  SSSS","  SSSS","SSSS  ","SSSS  " };
	vector<string> f72 = { "SS  ","SS  ","SSSS","SSSS","  SS","  SS" };

	vector<vector<vector<string>>> ff = { {f11,f12,f13,f14},{f21},{f31,f32},{f41,f42,f43,f44},{f51 ,f52,f53,f54},{f61,f62},{f71,f72} };

public:
	int i = 2;
	int j = 0;
	int n, m;
	int x = 19, y = 0;
	figure() {
		srand((unsigned int)time(NULL));
		//i = rand() % 7 ;
		for (int k = 0; k < ff[i][j].size(); k++) {
			f.push_back(ff[i][j][k]);
			cout << ff[i][j][k] << endl;
		}
		n = f.size();
		m = f[0].length();
	}

	figure(int i, int j, int x,int y) {
		this->i = i;
		this->j = j;
		this->x = x;
		this->y = y;

		for (int k = 0; k < ff[i][j].size(); k++) {
			f.push_back(ff[i][j][k]);
			cout << ff[i][j][k] << endl;
		}
		n = f.size();
		m = f[0].length();
	}
};

figure *mainfigure = new figure();
figure *sparefigure = new figure();

void paint() {
	system("cls");

	for ( int i = 0; i < 30; i++ ) {
		cout << field[i];
		if (i < fieldx.size()) 
			cout << fieldx[i];
		cout << endl;
	}
}

void play() {
	if ( _kbhit() ) {
		cout << " PLAY" << endl;
		switch ( _getch() )
		{
			case 'a':
				dr = LEFT;
				cout << "drplay  " << dr << endl;
				break;
			case 'd':
				dr = RIGHT;
				cout << "drplay  " << dr << endl;
				break;
			case 's':
				dr = DOWN;
				cout << "drplay  " << dr<<endl;
				break;
			case 'w':
				dr = UP;
				cout << "drplay  " << dr << endl;
				break;
			case 'ф':
				dr = LEFT;
				cout << "drplay  " << dr << endl;
				break;
			case 'в':
				dr = RIGHT;
				cout << "drplay  " << dr << endl;
				break;
			case 'ы':
				dr = DOWN;
				cout << "drplay  " << dr << endl;
				break;
			case 'ц':
				dr = UP;
				cout << "drplay  " << dr << endl;
				break;
			default:
				break;
		}
	}
}

bool status(figure *fk = NULL) {
	if (dr == UP) {
		return true;
	}
	int x, y, m;
	vector<string> f;
	if (fk == NULL) {
		x = mainfigure->x;
		y = mainfigure->y;
		m = mainfigure->m;
		f = mainfigure->f;
	}else {

		x = fk->x;
		y = fk->y;
	   m = fk->m;
		f = fk->f;
		if (x < 1 or y < 1 or x>41 or y>28) {
			return false;
		}
		/*for (int i = 0; i < f.size(); i++) {
			cout << f[i] << "|" << endl;
		}*/
		
		int k = 0;
		int n = f.size() - 1;
		for (int i = y; y - i < f.size() and i > 0; i--, n--) {
			k = 0;
			for (int j = x; j < x + m and j>0; j++, k++) {
				if (f[n][k] != ' ' and field[i][j] != ' ') {
					return false;
				}
			}
		}



	}
	
	cout << "X " << x << "Y " << y << "M " << m << "N" << f.size() << endl;
	if ( dr == DOWN ) {
		int k = 0;
		int h = 0;
		int i = x;
		while ( i < x + m - 1) {
			if ( f[f.size() - 1 - h][k] != ' ' and field[y + 1 - h][i] != ' ' ) {
				cout << "FALSE" << endl;
				return false;
			}
			/*if (f[f.size() - 1 - h][k] != ' ' or y + 1 - h - 2 <= 0) {
				h = 0;
				k++;
				i++;
			}
			else {
				if (y + 1 - h - 2 > 0) {
					h += 2;
				}
			}*/
			k++;
			i++;
		}
	}
	if ( dr == LEFT ) {
		int k = 0;
		int h = 0;
		int i = y;
		while(y - i < f.size() and i > 0 ) {
			if ( f[f.size() - 1 - k][0 + h] != ' ' and field[i][x - 1 + h] != ' ' ) {
				cout << "FALSE" << endl;
				return false;
			}
			/*if (f[f.size() - 1 - k][0 + h] != ' ') {

				k++;
				i--;
				h = 0;
			}
			else {
				h += 2;
			}*/
			k++;
			i--;
		}
	}

	if ( dr == RIGHT ) {
		int k = 0;
		int h = 0;
		int i = y;
		while (  y - i < f.size() and i > 0 ) {
			if ( f[f.size() - 1 - k][m - h - 1] != ' ' and field[i][x + 1 - h + m] != ' ' ) {
				cout << "RIGHT == FALSE  F: " << f.size() - 1 - k << "  " << m - h - 1 << " FIELD: " << i << "  " << x + 1 - h - m <<" H "<<h<< endl;
				return false;
			}
			/*if (f[f.size() - 1 - k][m - h - 1] != ' ') {
				k++;
				i--;
				h = 0;
			}
			else {
				h += 2;
			}*/
			k++;
			i--;
		}

	}



	return true;
}

void clear() {
	int x = mainfigure->x;
	int y = mainfigure->y;
	int n = mainfigure->n - 1;
	int m = mainfigure->m;
	int k = 0;
	vector<string> f = mainfigure->f;


	for ( int i = y; y - i < f.size() and i > 0; i--, n-- ) {
		k = 0;
		for ( int j = x; j < x + m ; j++, k++ ) {
			if (f[n][k] != ' ' and f[n][k] != '#' ) {
				field[i][j] = ' ';
			}

		}

	}
}

void ratation() {
	int i = mainfigure->i;
	int j = mainfigure->j;
	int x = mainfigure->x;
	int y = mainfigure->y;

	figure *rfigure;
	switch (i)
	{
		case 0:
			if (j < 3) {
				j++;
			}
			else {
				j = 0;
			}
			switch (j) {
				case 0:
					y = y - 2;
					break;
				case 1:
					x += 2;
					y += 2;

					break;
				case 2:
					x -= 2;
					break;
				default:
					break;
			}

			rfigure = new figure(i, j, x, y);
			clear();
			if (status(rfigure)) {	
				delete mainfigure;
				mainfigure = rfigure;
			}
			return;
			break;
		case 2:
			if (j < 1) {
				j++;
			}
			else {
				j = 0;
			}
			switch (j)
			{
				case 0:
					x += 4;
					y += 4;
					break;
				case 1:
					x -= 4;
					y -= 4;
					break;
				default:
					break;
			}
			rfigure = new figure(i, j, x, y);
			clear();
			if (status(rfigure)) {
				delete mainfigure;
				mainfigure = rfigure;
			}
			break;
		case 3:
			if (j < 3) {
				j++;
			}
			else {
				j = 0;
			}

			switch (j)
			{
			case 0:
				y -= 2;
				break;

			case 1:
				x += 2;
				y += 2;
				break;
			case 2:
				x -= 2;
				break;
			case 3:
				break;
			default:
				break;
			}
			rfigure = new figure(i, j, x, y);
			clear();
			if (status(rfigure)) {
				delete mainfigure;
				mainfigure = rfigure;
			
			}
			break;
		case 4:
			if (j < 3) {
				j++;
			}
			else {
				j = 0;
			}

			switch (j)
			{
				case 0:
					y -= 2;
					break;

				case 1:
					x += 2;
					y += 2;
					break;
				case 2:
					x -= 2;
					break;
				case 3:
					break;
				default:
					break;
			}

			rfigure = new figure(i, j, x, y);
			clear();
			if (status(rfigure)) {
				delete mainfigure;
				mainfigure = rfigure;
	
			}
			break;
		case 5:
			if (j < 1) {
				j++;
			}
			else {
				j = 0;
			}
			switch (j)
			{
				case 0:
					x -= 2;
					y -= 2;
					break;;
				case 1:
					x += 2;
					y += 2;
					break;
				default:
					break;
			}
			rfigure = new figure(i, j, x, y);
			clear();
			if (status(rfigure)) {

				delete mainfigure;
				mainfigure = rfigure;

			}
			break;
		case 6:
			if (j < 1) {
				j++;
			}
			else {
				j = 0;
			}
			switch (j)
			{
			case 0:
				x -= 2;
				y -= 2;
				break;;
			case 1:
				x += 2;
				y += 2;
				break;
			default:
				break;
			}
			rfigure = new figure(i, j, x, y);
			clear();
			if (status(rfigure)) {

				delete mainfigure;
				mainfigure = rfigure;

			}
			break;
		default:
			break;
	}
}

void draw(bool status) {

	if (dr == UP) {
		dr = NUL;
		ratation();

		int x = mainfigure->x;
		int y = mainfigure->y;
		int n = mainfigure->n - 1;
		int m = mainfigure->m;
		vector<string> f = mainfigure->f;
		int k = 0;
		for (int i = y; y - i < f.size() and i > 0; i--, n--) {
			k = 0;
			for (int j = x; j < x + m; j++, k++) {
				if (f[n][k] != ' ' and f[n][k] != '#') {
					field[i][j] = f[n][k];
				}
			}

		}
	}

	int x = mainfigure->x;
	int y = mainfigure->y;
	int n = mainfigure->n - 1;
	int m = mainfigure->m;
	vector<string> f = mainfigure->f;
	if ( !status and dr == DOWN ) {
		dr = STOP;
		return;
	}
	if ( !status and dr !=DOWN ) {
		return;
	}

	

	if ( dr == DOWN ) {
		clear();
		int k = 0;
		y += 2;
		mainfigure->y += 2;
		for ( int i = y; y - i < f.size() and i > 0; i-- , n-- ) {
			k = 0;
			for ( int j = x; j < x + m; j++ , k++ ) {
				if (f[n][k] != ' ' and f[n][k] != '#' ) {
					field[i][j] = f[n][k];
				}
			}
			
		}
	}
	if ( dr == LEFT ) {
		clear();
		x -= 2;
		int k = 0;
		mainfigure->x -= 2;
		for ( int i = y; y - i < f.size() and i > 0; i--, n-- ) {
			k = 0;
			for ( int j = x; j < x + m; j++, k++ ) {
				if (f[n][k] != ' ' and f[n][k] != '#' ) {
					field[i][j] = f[n][k];
				}
			}

		}
	}
	if ( dr == RIGHT ) {
		clear();
		x += 2;
		int k = 0;
		mainfigure->x += 2;
		for ( int i = y; y - i < f.size() and i > 0; i--, n-- ) {
			k = 0;
			for ( int j = x; j < x + m; j++, k++ ) {
				if ( f[n][k] != ' ' and f[n][k] != '#' ) {
					field[i][j] = f[n][k];
				}
			}

		}
	}
	
	dr = NUL;
}

void line(int &ln ) {

	int x = mainfigure->x;
	int y = mainfigure->y;
	int n = mainfigure->n;
	int m = mainfigure->m;

	vector<int> a;
	bool line = true;
	for (int i = y; y - i < n; i--) {
		for (int j = 1; j < 41; j += 2) {
			if (field[i][j] == ' ')
				line = false;
		}
		if (line)
			a.push_back(i);
		else
			line = true;
	}

	if (a.size() > 0) {
		for (int j = 0; j < 21; j++) {
			for (int i = a.size() - 1; i >= 0; i--) {
				field[a[i]][21 + j + 1] = ' ';
				field[a[i]][21 - j] = ' ';
				
			}
			this_thread::sleep_for(chrono::milliseconds(100));
			paint();
		}
		this_thread::sleep_for(chrono::milliseconds(1000));
		paint();
		for (int i = a.size() - 1; i >= 0; i--) {
			for (int j = a[i] - 1; j > 0; j--) {
				field[j + 1] = field[j];
				field[j] = field2;
			}
			field[1] = field2;
		}
	}
	paint();
	ln += a.size() / 2 + 100;
}

void spare_field(int line) {
	int n = sparefigure->n;
	int m = sparefigure->m;

	vector<string> f = sparefigure->f;
	for (int i = 2; i < 10; i++) {
		fieldx[i] = field4;
	}
	for (int i = 0; i < n; i++) {
		fieldx[i + 2] = field4;
		for (int j = 0; j < m; j++)
			fieldx[i + 2][j + 3] = f[i][j];
	}

	fieldx[12] = "#  line:             #";
	string t = to_string(line);
	for (int i = 0; i < t.size(); i++)
		fieldx[12][12 + i] = t[i];

}

int main() {

	field[0] = field1;
	field[field.size() - 1] = field1;
	fieldx[0] = field3;
	fieldx[fieldx.size() - 1] = field3;
	dr = NUL;
	int k = 1;
	int ln = 0;
	while ( true ) {
		this_thread::sleep_for(chrono::milliseconds(100));
		spare_field(ln);
		paint();
		play();
		draw(status());
		
		if ( dr == STOP ) {
			if (mainfigure->y - mainfigure->n + 1 < 0)
				return 0;

			line(ln);
			delete mainfigure;
			mainfigure = sparefigure;
			sparefigure = new figure();
		}
		if ( k == 10 ) {
			k = 1;
			if ( dr == NUL )
				dr = DOWN;
			else 
				k = 5;
		}
		else
			k++;
		/*cout <<"DR "<< dr << endl;
		cout <<"FORM "<< mainfigure->i<<"  "<<mainfigure->j<<endl;
		cout << "OX: " << mainfigure->x << "  OY: " << mainfigure->y;*/
	}
}	 


