#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
enum Engamechoice {
	stone = 1, paper = 2, scissor = 3
};
enum enwinner {
	player1 = 1, computer = 2, draw = 3
};
struct stroundinfo {
	short roundnumber = 0;
	Engamechoice player1choice;
	Engamechoice computerchoice;
	enwinner winner;
	string winnername;
};
struct stgameresult {
	short gameround = 0;
	short player1wintimes = 0;
	short computerwintimes = 0;
	short drawtimes = 0;
	enwinner gamewinner;
	string winnername = " ";
};
int randomnumber(int from, int to) {
	return rand() % (to - from) + from;
}
Engamechoice getcomputerchoice() {
	return (Engamechoice)randomnumber(1, 3);
}
enwinner whowontheround(stroundinfo roundinfo) {
	if (roundinfo.player1choice == roundinfo.computerchoice)return enwinner::draw;
	switch (roundinfo.player1choice) {
	case Engamechoice::stone:
		return(roundinfo.computerchoice == Engamechoice::paper) ? enwinner::computer : enwinner::player1;
	case Engamechoice::paper:
		return (roundinfo.computerchoice == Engamechoice::scissor) ? enwinner::computer : enwinner::player1;
	case Engamechoice::scissor:
		return(roundinfo.computerchoice == Engamechoice::stone) ? enwinner::computer : enwinner::player1;
	}
}
enwinner whowonthegame(short player1wintimes, short computerwintimes) {
	if (player1wintimes > computerwintimes)return enwinner::player1;
	else if (computerwintimes > player1wintimes) return enwinner::computer;
	else return enwinner::draw;
}
string ChoiceName(Engamechoice Choice) {
	string arrGameChoices[3] = { "Stone", "Paper", "Scissors" }; return arrGameChoices[Choice - 1];
}
string winnername(enwinner winner) {
	string arrwinner[3] = { "player","computer","nowinner(draw)" };
	return arrwinner[winner - 1];
}
Engamechoice readplayer1choice() {
	short choice;
	do {
		cout << "\nyour choice:[1]::stone,[2]:paper,[3]:scissors?";
		cin >> choice;
	} while (choice < 1 || choice>3);
	return (Engamechoice)choice;
}
void PrintRoundResults(stroundinfo RoundInfo) {
	cout << "\n__ Round [" << RoundInfo.roundnumber << "] __\n\n";
	cout << "Player1 Choice: " << ChoiceName(RoundInfo.player1choice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.computerchoice) << endl;
	cout << "Round Winner : [" << RoundInfo.winnername << "]\n"; cout << "_________\n" << endl;
}
stgameresult playgame(short howmanyrounds) {
	stroundinfo roundinfo;
	short player1wintimes = 0, computerwintimes = 0, drawtimes = 0;
	for (short gameround = 1; gameround <= howmanyrounds; gameround++) {
		cout << "\nRound[" << gameround << "] begins:\n";
		roundinfo.roundnumber= gameround;
		roundinfo.player1choice = readplayer1choice();
		roundinfo.computerchoice = getcomputerchoice();
		roundinfo.winner = whowontheround(roundinfo);
		roundinfo.winnername = winnername(roundinfo.winner);
		if (roundinfo.winner == enwinner::player1)
			player1wintimes++;
		else if (roundinfo.winner == enwinner::computer)
			computerwintimes++;
		else drawtimes++;
		PrintRoundResults(roundinfo);
	}
	return{ howmanyrounds,player1wintimes,computerwintimes,drawtimes,whowonthegame(player1wintimes,computerwintimes),winnername(whowonthegame(player1wintimes,computerwintimes)) };
}
void startgame() {
	char playagain = 'Y';
	do {
		system("cls");
		stgameresult gameresults = playgame(3);
		cout << "\nGame Over! Winner: " << gameresults.winnername << endl;
		cout << "\nDo you want to play again? (Y/N): ";
		cin >> playagain;
	} while (playagain == 'Y' || playagain == 'y');
}
int main() {
	srand((unsigned)time(NULL));
	startgame();
	return 0;
