#include <iostream>
#include <conio.h>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

string field1 = "############################################";
string field2 = "#                                          #";
vector <string> field(30 ,field2);
enum dir { STOP,LEFT, RIGHT , UP , DOWN, NUL };
dir dr;

struct figure {

	vector<string> f = { "  aa  ",
								"  aa  ",
								"aaaaaa",
								"aaaaaa"};

	int x = 19, y = 0;
	int n = f.size(), m = f[0].length();
};

figure* mainfigure = new figure();
void paint() {
	system("cls");
	for ( int i = 0; i < 30; i++ ) {
		cout << field[i]<<'\n';
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
			default:
				break;
		}
	}
}

bool status() {
	int x = mainfigure->x;
	int y = mainfigure->y;
	int m = mainfigure->m;
	vector<string> f = mainfigure->f;
	if ( dr == DOWN ) {
		int k = 0;
		int h = 0;
		for ( int i = x; i < x + m - 1; i++ ) {
			if ( f[f.size() - 1 + h][k] != ' ' and field[y + 1 + h][i] != ' ' ) {
				cout << "FALSE" << endl;
				return false;
			}
			if ( f[f.size() - 1 + h][k] == ' ' ) {
				h += 2;
				k--;
				i--;
			}
			k++;
		}
	}
	if ( dr == LEFT ) {
		int k = 0;
		int h = 0;
		for ( int i = y; y - i < f.size() and i > 0; i-- ) {
			if ( f[f.size() - 1 - k][0 + h] != ' ' and field[i][x - 1 + h] != ' ' ) {
				cout << "FALSE" << endl;
				return false;
			}
			if ( f[f.size() - 1 - k][0 + h] == ' ' ) {
				i++;
				h += 2;
				k--;
			}
			k++;
		}
	}

	if ( dr == RIGHT ) {
		int k = 0;
		int h = 0;
		for ( int i = y; y - i < f.size() and i > 0; i-- ) {
			if ( f[f.size() - 1 - k][m - h - 1] != ' ' and field[i][x + 1 - h + m] != ' ' ) {
				cout << "RIGHT == FALSE" << endl;
				return false;
			}
			if ( f[f.size() - 1 - k][m - h - 1] == ' ' ) {
				i++;
				h += 2;
				k--;
			}
			k++;
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
			if ( f[n][k] == 'a' ) {
				field[i][j] = ' ';
			}

		}

	}
}

void draw(bool status) {
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
				if ( f[n][k] == 'a' ) {
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
				if ( f[n][k] == 'a' ) {
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
				if ( f[n][k] == 'a' ) {
					field[i][j] = f[n][k];
				}
			}

		}
	}
	dr = NUL;
}

int main() {
	field[0] = field1;
	field[29] = field1;
	dr = NUL;
	int k = 1;
	while ( true ) {
		this_thread::sleep_for(chrono::milliseconds(200));
		paint();
		play();
		draw(status());
		if ( dr == STOP ) {
			mainfigure = new figure();
		}
		if ( k == 500000000 ) {
			k = 1;
			if ( dr == NUL )
				dr = DOWN;
			else 
				k = 5;
		}
		else
			k++;
		cout << dr;
	}
}
