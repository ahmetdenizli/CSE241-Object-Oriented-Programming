/*##############################################*/
/*				  Ahmet Denizli  				*/
/*					161044020					*/
/*##############################################*/
#include <iostream>
#include <cstdlib>	// for using rand function
#include <ctime>	// for using time function
#include <vector>

using namespace std;

typedef enum {user1, user2, emptyC} cell_type;	// Define enum type for board

const int NUMX[8] = {0, 0, 2, 3, 5, 5, 3, 2}; // Const array for ports x coordinates
const int NUMY[8] = {2, 3, 5, 5, 3, 2, 0, 0}; // Const array for ports y coordinates
const int MX[8] = {1, 1, 2, 3, 4, 4, 3, 2};	  // Const array for path to connected port x coordinates
const int MY[8] = {2, 3, 4, 4, 3, 2, 1, 1};	  // Const array for path to connected port y coordinates

class Cell {
public:
	Cell(int _x): x(_x), user_t(emptyC), side(0), path_x(-1), path_y(-1) {}			// Constructor
	Cell(int _x, cell_type _user): side(0), path_x(-1), path_y(-1) {set_x(_x);	set_user(_user);}	// Constructor

	void set_x(const int _x);	// Sets cell num x
	void set_user(const cell_type _user);	// Sets cell user
	void set_side(const int _side);		// Sets cell side
	void set_path(const int _path_x, const int _path_y);	// Sets cell path

	inline const int get_x() const { return x; }			// Gets cell num x
	inline const cell_type get_user() const { return user_t; }	// Gets cell user
	inline const int get_side() const { return side; }		// Gets cell side
	inline const int get_pathx() const { return path_x; }	// Gets cell path x
	inline const int get_pathy() const { return path_y; }	// Gets cell path y
private:
	int x;
	cell_type user_t;
	int path_x;
	int path_y;
	int side;
};

class tsuroCard
{
public:
	tsuroCard(int size);	// Card Constructor
	void generateCard();	// non const. This function generate new Card.
	void printCard() const; // This function prints Cards.
	void rotationCard(int angle);	// non const. This function change angle.

	vector< vector<Cell> > Card; // Card
};

class tsuro
{
public:
	tsuro() {set_BoardSize(3);}
	tsuro(int size) {set_BoardSize(size);}

	inline const int getSize() const { return b_size; } // This function gets game size.

	void set_BoardSize(int size); // non const. This function sets game size.
	void printGameBoard() const; // non const. This function prints current game board.
	void playGame(); //non const. This function plays the game until the end by asking to users to play card, side and angle .

private:
	void initBoard(); //  non const. This function initializes game board. non const
	int updateBoard(tsuroCard Tile, int side); //  non const. This function updates game board. If it is finish function returns 0.
	int updateUser(int coorx, int coory, cell_type user);	// non const. This function updates user tokens position.
	// non const. This function controls if the game end.
	int isEnd();	// If return 1 user-2 win else if return 2 user-1 win else if return 3 no one won.

	int b_size; // Board size
	vector< vector<Cell> > gameCells; // Game table
};

int main(int argc, char const *argv[])
{
	cout << "Welcome to game of Tsuro." << endl;
	cout << "You should choose side like this." << endl;
	cout << "-------------" << endl;
	cout << "- 1 - 2 - 3 -" << endl;
	cout << "-------------" << endl;
	cout << "- 4 - 5 - 6 -" << endl;
	cout << "-------------" << endl;
	cout << "- 7 - 8 - 9 -" << endl;
	cout << "-------------" << endl << endl;

	srand (time(NULL));

	do{
		tsuro single_game(3);	// Declaring 3x3 tsuro game object
		single_game.playGame();
		return 0;

	}while(1);

	return 0;
}

void Cell::set_x(const int _x) {
	if (_x > 0)
		x = _x;
}

void Cell::set_user(const cell_type _user) {
	if (_user == emptyC || _user == user1 || _user == user2)
		user_t = _user;
}

void Cell::set_side(const int _side) {
	if (_side > 0 && side < 13)
		side = _side;
}

void Cell::set_path(const int _path_x, const int _path_y){
	path_x = _path_x;
	path_y = _path_y;
}

tsuroCard::tsuroCard(int size){
	if (size > 0) {
		Card.resize(size*6);
	}
	generateCard();
}

// This function generate new Card.
void tsuroCard::generateCard(){
	int ran, chose1, chose2;
	vector<int> myvector;
	for (int i=1; i<=8; i++) myvector.push_back(i);	
	
	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 6; j++)
			Card[i].push_back( Cell(0));
	}
	// Setting ports number
	Card[0][2].set_x(1); Card[0][3].set_x(2);
	Card[2][5].set_x(3); Card[3][5].set_x(4);
	Card[5][3].set_x(5); Card[5][2].set_x(6);
	Card[3][0].set_x(7); Card[2][0].set_x(8);
	
	for (int i = 0; i < 4; ++i)
	{
		ran = rand()%(8- 2*i);						// Getting random integer for connecting ports number
		chose1 = myvector[ran];						// Getting random number from ports number vector.
		myvector.erase (myvector.begin()+ran);		// Erase this number from ports number vector.
		ran = rand()%(7- 2*i);						// Getting random integer for connecting another ports number
		chose2 = myvector[ran];						// Getting random number from ports number vector.
		myvector.erase (myvector.begin()+ran);		// Erase this number from ports number vector.
		Card[ MX[chose1-1] ][ MY[chose1-1] ].set_x(chose2);	Card[ NUMX[chose1-1] ][ NUMY[chose1-1] ].set_path(NUMX[chose2-1], NUMY[chose2-1]);
		Card[ MX[chose2-1] ][ MY[chose2-1] ].set_x(chose1);	Card[ NUMX[chose2-1] ][ NUMY[chose2-1] ].set_path(NUMX[chose1-1], NUMY[chose1-1]);
	}
}

// This function prints Cards.
void tsuroCard::printCard() const{
	for(int i = 0; i < 6; i++)
	{
		cout << " ";
		for(int j = 0; j < 6; j++){
			if (Card[i][j].get_x() == 0)
				cout << " ";
			else
				cout << Card[i][j].get_x();
		}
		cout << endl;
	}
	cout << endl;
}

// This function change angle.
void tsuroCard::rotationCard(int angle){
	int temp1, temp2, chose;
	switch(angle){
		case 90:
			Card[0][2].set_x(3); Card[0][3].set_x(4);	Card[2][5].set_x(5); Card[3][5].set_x(6);
			Card[5][3].set_x(7); Card[5][2].set_x(8);	Card[3][0].set_x(1); Card[2][0].set_x(2);
			temp1 = Card[1][2].get_x();
			temp2 = Card[1][3].get_x();
			Card[1][2].set_x( Card[2][4].get_x() );
			Card[1][3].set_x( Card[3][4].get_x() );
			Card[2][4].set_x( Card[4][3].get_x() );
			Card[3][4].set_x( Card[4][2].get_x() );
			Card[4][3].set_x( Card[3][1].get_x() );
			Card[4][2].set_x( Card[2][1].get_x() );
			Card[3][1].set_x( temp1 );
			Card[2][1].set_x( temp2 );
			for (int i = 0; i < 8; ++i)
			{
				chose = Card[ MX[i] ][ MY[i] ].get_x();
				Card[ NUMX[i] ][ NUMY[i] ].set_path(NUMX[(chose+5)%8], NUMY[(chose+5)%8]);
			}
			break;
		case 180:
			Card[0][2].set_x(5); Card[0][3].set_x(6);	Card[2][5].set_x(7); Card[3][5].set_x(8);
			Card[5][3].set_x(1); Card[5][2].set_x(2);	Card[3][0].set_x(3); Card[2][0].set_x(4);
			temp1 = Card[1][2].get_x();
			temp2 = Card[1][3].get_x();
			Card[1][2].set_x( Card[4][3].get_x() );
			Card[1][3].set_x( Card[4][2].get_x() );
			Card[4][3].set_x( temp1 );
			Card[4][2].set_x( temp2 );

			temp1 = Card[2][4].get_x();
			temp2 = Card[3][4].get_x();
			Card[2][4].set_x( Card[3][1].get_x() );
			Card[3][4].set_x( Card[2][1].get_x() );
			Card[3][1].set_x( temp1 );
			Card[2][1].set_x( temp2 );
			for (int i = 0; i < 8; ++i)
			{
				chose = Card[ MX[i] ][ MY[i] ].get_x();
				Card[ NUMX[i] ][ NUMY[i] ].set_path(NUMX[(chose+3)%8], NUMY[(chose+3)%8]);
			}
			break;
		case 270:
			Card[0][2].set_x(7); Card[0][3].set_x(8);	Card[2][5].set_x(1); Card[3][5].set_x(2);
			Card[5][3].set_x(3); Card[5][2].set_x(4);	Card[3][0].set_x(5); Card[2][0].set_x(6);
			temp1 = Card[1][2].get_x();
			temp2 = Card[1][3].get_x();
			Card[1][2].set_x( Card[3][1].get_x() );
			Card[1][3].set_x( Card[2][1].get_x() );
			Card[3][1].set_x( Card[4][3].get_x() );
			Card[2][1].set_x( Card[4][2].get_x() );
			Card[4][3].set_x( Card[2][4].get_x() );
			Card[4][2].set_x( Card[3][4].get_x() );
			Card[2][4].set_x( temp1 );
			Card[3][4].set_x( temp2 );
			for (int i = 0; i < 8; ++i)
			{
				chose = Card[ MX[i] ][ MY[i] ].get_x();
				Card[ NUMX[i] ][ NUMY[i] ].set_path(NUMX[(chose+1)%8], NUMY[(chose+1)%8]);
			}
			break;
	}
}

// This function sets game size.
void tsuro::set_BoardSize(int size) {
	b_size = size;
	if (size > 0) {
		gameCells.resize(size*6);
	}
	initBoard(); // Initializes the board.
}

// This function prints current game board.
void tsuro::printGameBoard() const {
	int  board_size = 6*b_size;
	cout << "-";
	for (int i = 0; i < b_size; ++i)
		cout << "--oo--";
	cout << "-" << endl;
	for(int i = 0; i < board_size; i++)
	{
		if (i==2 || i==3 || i==8 || i==9 || i==14 || i==15)
			cout <<"o";
		else
			cout <<"|";
		for(int j = 0; j < board_size; j++){
			if (gameCells[i][j].get_user() == user1)
				cout << "X";
			else if (gameCells[i][j].get_user() == user2)
				cout << "Y";
			else if (gameCells[i][j].get_x() == 0)
				cout << " ";
			else
				cout << gameCells[i][j].get_x();
		}
		if (i==2 || i==3 || i==8 || i==9 || i==14 || i==15)
			cout <<"o"<< endl;
		else
			cout <<"|"<< endl;
	}
	cout << "-";
	for (int i = 0; i < b_size; ++i)
		cout << "--oo--";
	cout <<"-" << endl;
}

// This function initializes game board.
void tsuro::initBoard() {
	int  board_size = 6*getSize(), ran;
	for(int i = 0; i < board_size; i++)
	{
		for(int j = 0; j < board_size; j++)
			gameCells[i].push_back( Cell(0));
	}
	ran = rand()%2+2;
	gameCells[0][ran].set_user(user1);
	gameCells[ran][0].set_user(user2);
}

// non const. This function controls if the game end. 
// If return 1 user-2 win else if return 2 user-1 win else if return 3 no one won.
int tsuro::isEnd() {
	int ret1, ret2;
	int  board_size = 6*b_size;
	for(int i = 0; i < 16; i+=15)
	{
		for(int j = 0; j < board_size; j++){
			if (gameCells[i][j].get_user() == user1)
				ret1= 1;
			else if (gameCells[i][j].get_user() == user2)
				ret2= 2;
		}
	}
	for(int i = 0; i < board_size; i++)
	{
		for(int j = 0; j < 16; j+=15){
			if (gameCells[i][j].get_user() == user1)
				ret1= 1;
			else if (gameCells[i][j].get_user() == user2)
				ret2= 2;
		}
	}

	if (ret1==1 && ret2==2)
		return 3;
	else if (ret1==1)
		return 1;
	else if (ret2==2)
		return 2;

	return 0;
}

// non const. This function updates user tokens position.
int tsuro::updateUser(int coorx, int coory, cell_type user){
	int side = gameCells[coorx][coory].get_side();
	int pathX = gameCells[coorx][coory].get_pathx();
	int pathY = gameCells[coorx][coory].get_pathy();
	int num1 = pathX %6;
	int num2 = pathY %6;

	if (side==0)
		return 1;

	if (pathX==0 || pathY==0 || pathX ==15 || pathY==15){
		gameCells[pathX][pathY].set_user(user);
		gameCells[coorx][coory].set_user(emptyC);
		return 0;
	}

	gameCells[coorx][coory].set_user(emptyC);

	switch(num1){
		case 0:
			gameCells[pathX-1][pathY].set_user(user);
			return updateUser(pathX-1, pathY, user);
		case 5:
			gameCells[pathX+1][pathY].set_user(user);
			return updateUser(pathX+1, pathY, user);
	}
	switch(num2){
		case 0:
			gameCells[pathX][pathY-1].set_user(user);
			return updateUser(pathX, pathY-1, user);
		case 5:
			gameCells[pathX][pathY+1].set_user(user);
			return updateUser(pathX, pathY+1, user);
	}
	return 1;
}

// This function updates game board. If it is finish function returns 0.
int tsuro::updateBoard(tsuroCard Tile, int side){
	cell_type temp = emptyC;
	int coor_x, coor_y;
	switch(side){
		case 1:
			for(int i = 0; i < 6; i++)
			{
				for(int j = 0; j < 6; j++){
					gameCells[i][j].set_x( Tile.Card[i][j].get_x() );
					gameCells[i][j].set_side(1);
					gameCells[i][j].set_path( Tile.Card[i][j].get_pathx(), Tile.Card[i][j].get_pathy() );
					if (gameCells[i][j].get_user() == user1){
						coor_x = i;	coor_y = j; temp = user1;
						updateUser(coor_x, coor_y, temp);
					}
					else if (gameCells[i][j].get_user() == user2){
						coor_x = i; coor_y = j; temp = user2;
						updateUser(coor_x, coor_y, temp);
					}
				}
			}
			break;
		case 2:
			for(int i = 0; i < 6; i++)
			{
				for(int j = 0; j < 6; j++){
					gameCells[i][j+6].set_x( Tile.Card[i][j].get_x() );
					gameCells[i][j+6].set_side(2);
					gameCells[i][j+6].set_path( Tile.Card[i][j].get_pathx(), Tile.Card[i][j].get_pathy()+6 );
					if (gameCells[i][j+6].get_user() == user1){
						coor_x = i; coor_y = j+6; temp = user1;
						updateUser(coor_x, coor_y, temp);
					}
					else if (gameCells[i][j+6].get_user() == user2){
						coor_x = i; coor_y = j+6; temp = user2;
						updateUser(coor_x, coor_y, temp);
					}
				}
			}
			break;
		case 3:
			for(int i = 0; i < 6; i++)
			{
				for(int j = 0; j < 6; j++){
					gameCells[i][j+12].set_x( Tile.Card[i][j].get_x() );
					gameCells[i][j+12].set_side(3);
					gameCells[i][j+12].set_path( Tile.Card[i][j].get_pathx(), Tile.Card[i][j].get_pathy()+12 );
					if (gameCells[i][j+12].get_user() == user1){
						coor_x = i; coor_y = j+12; temp = user1;
						updateUser(coor_x, coor_y, temp);
					}
					else if (gameCells[i][j+12].get_user() == user2){
						coor_x = i; coor_y = j+12; temp = user2;
						updateUser(coor_x, coor_y, temp);
					}
				}
			}
			break;
		case 4:
			for(int i = 0; i < 6; i++)
			{
				for(int j = 0; j < 6; j++){
					gameCells[i+6][j].set_x( Tile.Card[i][j].get_x() );
					gameCells[i+6][j].set_side(4);
					gameCells[i+6][j].set_path( Tile.Card[i][j].get_pathx()+6, Tile.Card[i][j].get_pathy() );
					if (gameCells[i+6][j].get_user() == user1){
						coor_x = i+6; coor_y = j; temp = user1;
						updateUser(coor_x, coor_y, temp);
					}
					else if (gameCells[i+6][j].get_user() == user2){
						coor_x = i+6; coor_y = j; temp = user2;
						updateUser(coor_x, coor_y, temp);
					}
				}
			}
			break;
		case 5:
			for(int i = 0; i < 6; i++)
			{
				for(int j = 0; j < 6; j++){
					gameCells[i+6][j+6].set_x( Tile.Card[i][j].get_x() );
					gameCells[i+6][j+6].set_side(5);
					gameCells[i+6][j+6].set_path( Tile.Card[i][j].get_pathx()+6, Tile.Card[i][j].get_pathy()+6 );
					if (gameCells[i+6][j+6].get_user() == user1){
						coor_x = i+6; coor_y = j+6; temp = user1;
						updateUser(coor_x, coor_y, temp);
					}
					else if (gameCells[i+6][j+6].get_user() == user2){
						coor_x = i+6; coor_y = j+6; temp = user2;
						updateUser(coor_x, coor_y, temp);
					}
				}
			}
			break;
		case 6:
			for(int i = 0; i < 6; i++)
			{
				for(int j = 0; j < 6; j++){
					gameCells[i+6][j+12].set_x( Tile.Card[i][j].get_x() );
					gameCells[i+6][j+12].set_side(6);
					gameCells[i+6][j+12].set_path( Tile.Card[i][j].get_pathx()+6, Tile.Card[i][j].get_pathy()+12 );
					if (gameCells[i+6][j+12].get_user() == user1){
						coor_x = i+6; coor_y = j+12; temp = user1;
						updateUser(coor_x, coor_y, temp);
					}
					else if (gameCells[i+6][j+12].get_user() == user2){
						coor_x = i+6; coor_y = j+12; temp = user2;
						updateUser(coor_x, coor_y, temp);
					}
				}
			}
			break;
		case 7:
			for(int i = 0; i < 6; i++)
			{
				for(int j = 0; j < 6; j++){
					gameCells[i+12][j].set_x( Tile.Card[i][j].get_x() );
					gameCells[i+12][j].set_side(7);
					gameCells[i+12][j].set_path( Tile.Card[i][j].get_pathx()+12, Tile.Card[i][j].get_pathy() );
					if (gameCells[i+12][j].get_user() == user1){
						coor_x = i+12; coor_y = j; temp = user1;
						updateUser(coor_x, coor_y, temp);
					}
					else if (gameCells[i+12][j].get_user() == user2){
						coor_x = i+12; coor_y = j; temp = user2;
						updateUser(coor_x, coor_y, temp);
					}
				}
			}
			break;
		case 8:
			for(int i = 0; i < 6; i++)
			{
				for(int j = 0; j < 6; j++){
					gameCells[i+12][j+6].set_x( Tile.Card[i][j].get_x() );
					gameCells[i+12][j+6].set_side(8);
					gameCells[i+12][j+6].set_path( Tile.Card[i][j].get_pathx()+12, Tile.Card[i][j].get_pathy()+6 );
					if (gameCells[i+12][j+6].get_user() == user1){
						coor_x = i+12; coor_y = j+6; temp = user1;
						updateUser(coor_x, coor_y, temp);
					}
					else if (gameCells[i+12][j+6].get_user() == user2){
						coor_x = i+12; coor_y = j+6; temp = user2;
						updateUser(coor_x, coor_y, temp);
					}
				}
			}
			break;
		case 9:
			for(int i = 0; i < 6; i++)
			{
				for(int j = 0; j < 6; j++){
					gameCells[i+12][j+12].set_x( Tile.Card[i][j].get_x() );
					gameCells[i+12][j+12].set_side(9);
					gameCells[i+12][j+12].set_path( Tile.Card[i][j].get_pathx()+12, Tile.Card[i][j].get_pathy()+12 );
					if (gameCells[i+12][j+12].get_user() == user1){
						coor_x = i+12; coor_y = j+12; temp = user1;
						updateUser(coor_x, coor_y, temp);
					}
					else if (gameCells[i+12][j+12].get_user() == user2){
						coor_x = i+12; coor_y = j+12; temp = user2;
						updateUser(coor_x, coor_y, temp);
					}
				}
			}
			break;
	}
	return 1;
}

// This function plays the game until the end by asking to users to play card, side and angle .
void tsuro::playGame() {
	int board_size, game_continue =1, card_num, rotation, side, is_end;		// Declaring variable for board size
	board_size = getSize();

	tsuroCard card1(6);
	tsuroCard card2(6);
	tsuroCard card3(6);
	tsuroCard card4(6);
	tsuroCard card5(6);
	tsuroCard card6(6);

	cout <<"You must place a tile in the square in front their piece for first If you dont you cant play the game."<< endl;

	do{
		printGameBoard();
		cout <<" Card 1   "<< endl;
		card1.printCard();
		cout <<" Card 2   "<< endl;
		card2.printCard();
		cout <<" Card 3   "<< endl;
		card3.printCard();
		do{
			cout <<"User1 Enter your card number. You should enter '1' to '3' for card: ";
			cin >> card_num;
			if ( card_num < 1 || card_num > 3 )
				cout << "You have entered invalid number, try again." << endl;
		}while( card_num < 1 || card_num > 3);

		do{
			cout <<"You should enter (1-9) for side: ";
			cin >> side;
			if ( side == 1 || side == 2 || side==3)
				if(gameCells[0][side*5].get_side() != 0){
					cout << "You have entered invalid number, try again." << endl;
					side=0;
				}
			else if ( side == 4 || side == 5 || side==6)
				if(gameCells[6][side*4-11].get_side() != 0){
					cout << "You have entered invalid number, try again." << endl;
					side=0;
				}
			else if ( side == 7 || side == 8 || side==9)
				if(gameCells[12][(side%6)*5].get_side() != 0){
					cout << "You have entered invalid number, try again." << endl;
					side=0;
				}
		}while( side < 1 || side > 9);

		do{
			cout <<"You should enter (0-90-180-270) for angle of rotation: ";
			cin >> rotation;
			if ( rotation !=0 && rotation !=90 && rotation !=180 && rotation !=270)
				cout << "You have entered invalid angle, try again." << endl;
		}while( rotation !=0 && rotation !=90 && rotation !=180 && rotation !=270);

		switch (card_num){
			case 1:
				card1.rotationCard(rotation);
				game_continue = updateBoard(card1, side);
				card1.generateCard();
				break;
			case 2:
				card2.rotationCard(rotation);
				game_continue = updateBoard(card2, side);
				card2.generateCard();
				break;
			case 3:
				card3.rotationCard(rotation);
				game_continue = updateBoard(card3, side);
				card3.generateCard();
				break;
		}

		printGameBoard();
		cout <<" Card 1   "<< endl;
		card4.printCard();
		cout <<" Card 2   "<< endl;
		card5.printCard();
		cout <<" Card 3   "<< endl;
		card6.printCard();
		do{
			cout <<"User2 Enter your card number. You should enter '1' to '3' for card: ";
			cin >> card_num;
			if ( card_num < 1 || card_num > 3 )
				cout << "You have entered invalid number, try again." << endl;
		}while( card_num < 1 || card_num > 3);

		do{
			cout <<"You should enter (1-9) for side: ";
			cin >> side;
			if ( side == 1 || side == 2 || side==3)
				if(gameCells[0][side*5].get_side() != 0){
					cout << "You have entered invalid number, try again." << endl;
					side=0;
				}
			if ( side == 4 || side == 5 || side==6)
				if(gameCells[7][side*4-11].get_side() != 0){
					cout << "You have entered invalid number, try again." << endl;
					side=0;
				}
			if ( side == 7 || side == 8 || side==9)
				if(gameCells[13][(side%6)*5].get_side() != 0){
					cout << "You have entered invalid number, try again." << endl;
					side=0;
				}
		}while( side < 1 || side > 9);

		do{
			cout <<"You should enter (0-90-180-270) for angle of rotation: ";
			cin >> rotation;
			if ( rotation !=0 && rotation !=90 && rotation !=180 && rotation !=270)
				cout << "You have entered invalid angle, try again." << endl;
		}while( rotation !=0 && rotation !=90 && rotation !=180 && rotation !=270);

		switch (card_num){
			case 1:
				card4.rotationCard(rotation);
				game_continue = updateBoard(card4, side);
				card4.generateCard();
				break;
			case 2:
				card5.rotationCard(rotation);
				game_continue = updateBoard(card5, side);
				card5.generateCard();
				break;
			case 3:
				card6.rotationCard(rotation);
				game_continue = updateBoard(card6, side);
				card6.generateCard();
				break;
		}

		cout << endl;

		is_end = isEnd();
		if (is_end == 3)
		{
			printGameBoard();
			cout << "No one won the game! Thanks for playing." << endl;
			break;
		}
		if (is_end == 2)
		{
			printGameBoard();
			cout << "User-1 win the game! Thanks for playing." << endl;
			break;
		}
		else if (is_end == 1)
		{
			printGameBoard();
			cout << "User-2 win the game! Thanks for playing." << endl;
			break;
		}
	}while(game_continue);

}