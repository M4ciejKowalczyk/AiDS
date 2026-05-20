#include <iostream>
#include <string>

#define RED 0
#define BLUE 1


struct GameInfo {
	char board[11][11];
	int redPawns;
	int bluePawns;
	int boardSize;

	GameInfo() : redPawns(0), bluePawns(0), boardSize(0) {
		std::memset(board, 0, sizeof(board));
	}
};

int Sn(int n) {
	int suma = 0;
	for (int i = 1; i <= n; i++) {
		suma += i;
	}
	return suma;
}

void initializeArray(char tmp[]) {
	for (int i = 0; i < 121; i++) {
		tmp[i] = '0';
	}
}

void setBoard(char tmp[], GameInfo& game) {
	for (int x = 0; x < game.boardSize; x++) {
		for (int y = 0; y < game.boardSize; y++) {
			if (x + y < game.boardSize) {
				game.board[x][y] = tmp[Sn(x + y) + x];
			}
			else {
				game.board[x][y] = tmp[game.boardSize*game.boardSize - 1- (Sn(2*(game.boardSize - 1) - (x + y)) + game.boardSize - 1 - x)];
			}
		}
	}
}

bool isBoardCorrect(GameInfo game) {
	if (game.redPawns == game.bluePawns || game.redPawns - 1 == game.bluePawns)
		return true;
	else
		return false;
}

int isEnd(char board[11][11], int size, int x, int y) {
	if (board[x][y] == 'r' && x == size - 1) return 1;
	else if ((board[x][y] == 'b' && y == size - 1)) return 2;
	else return 0;
}

void DFS(char board[11][11], int x, int y, int size, int& isOver, bool marked[11][11]) {
	if (isEnd(board, size, x, y)!=0) {
		isOver = isEnd(board, size, x, y);
		return;
	}
	marked[x][y] = true;
	const int neightbors[6][2] = { {-1,0},{1,0},{0,-1},{0,1},{-1,-1},{1,1} };
	for (int i = 0; i < 6; i++) {
		if (x + neightbors[i][0] >= 0 && x + neightbors[i][0] < size && y + neightbors[i][1] >= 0 && y + neightbors[i][1] < size) {// granice planszy
			if (marked[x + neightbors[i][0]][y + neightbors[i][1]] == false && board[x][y] == board[x + neightbors[i][0]][y + neightbors[i][1]])// czy nie był już zaznaczony i czy ma ten sam znak
				DFS(board, x+neightbors[i][0], y+neightbors[i][1], size, isOver, marked);
		}
	}
}

int isGameOver(GameInfo game, bool ignoreisBoardCorrect) {
	if (!isBoardCorrect(game) && ignoreisBoardCorrect == false) return 0;
	int isOver = 0;
	bool marked[11][11] = {};
	for (int i = 0; i < game.boardSize; i++){//red
		if(game.board[0][i]=='r')
			DFS(game.board, 0, i, game.boardSize, isOver, marked);
	}
	for (int i = 0; i < game.boardSize; i++) {//blue
		if(game.board[i][0]=='b')
			DFS(game.board, i, 0, game.boardSize, isOver, marked);
	}
	return isOver;// 0 - false, 1 - red won, 2 - blue won
}

bool isNotWinningAfterDeletingPawn(GameInfo game, char pawn) {
	for (int i = 0; i < game.boardSize; i++) {
		for (int j = 0; j < game.boardSize; j++) {
			if (game.board[i][j] == pawn) {
				game.board[i][j] = '0';
				if (isGameOver(game, false) == 0)
					return true;
				else
					game.board[i][j] = pawn;
			}
		}
	}
	return false;
}


bool isBoardPossible(GameInfo game) {
	if (!isBoardCorrect(game)) return false;
	if (isGameOver(game, false) == 0) return true;
	else if (isGameOver(game, false) == 1 && game.redPawns-1==game.bluePawns) {//red won
		if (isNotWinningAfterDeletingPawn(game, 'r'))
			return true;
	}
	else if (isGameOver(game, false) == 2 && game.redPawns == game.bluePawns) {//blue won
		if (isNotWinningAfterDeletingPawn(game, 'b'))
			return true;
	}
	return false;
}

bool isBoardValid(GameInfo game, int moves, int player) {
	if (!isBoardPossible(game)) return false;
	if (isGameOver(game, false) > 0) return false;
	int movesNeeded;
	int emptyFields = game.boardSize * game.boardSize - (game.bluePawns + game.redPawns);
	int whoseTurn = game.redPawns - game.bluePawns;// 0 - red, 1 - blue
	if (player == whoseTurn) {
		movesNeeded = 2 * moves - 1;
	}
	else movesNeeded = 2 * moves;
	if (movesNeeded > emptyFields) return false;
	return true;
}

bool naiveOpponent(GameInfo game, int moves, int player) {
	if (!isBoardValid(game, moves, player)) return false;
	else {
		char playerSymbol;
		if (player == RED) playerSymbol = 'r';
		else playerSymbol = 'b';
		for (int i = 0; i < game.boardSize; i++) {
			for (int j = 0; j < game.boardSize; j++) {
				if (game.board[i][j] == '0') {
					game.board[i][j] = playerSymbol;
					if (moves == 2) {
						for (int k = 0; k < game.boardSize; k++) {
							for (int l = 0; l < game.boardSize; l++) {
								if (game.board[k][l] == '0') {
									game.board[k][l] = playerSymbol;
									if (isGameOver(game, true) > 0) {
										int check = 0;
										game.board[k][l] = '0';
										if (isGameOver(game, true) > 0) check++;
										game.board[k][l] = playerSymbol;
										game.board[i][j] = '0';
										if (isGameOver(game, true) > 0) check++;
										if (check < 2) return true;
										game.board[i][j] = playerSymbol;
										game.board[k][l] = '0';
									}
									else
										game.board[k][l] = '0';
								}
							}
						}
						game.board[i][j] = '0';
					}
					if (moves == 1 && isGameOver(game, true) > 0) {
						return true;
					}
					else
						game.board[i][j] = '0';
				}
			}
		}
	}
	return false;
}

bool checkForEnemyPlayer(GameInfo game, int player) {
	if (isGameOver(game, true) > 0) return false;
	char playerSymbol;
	if (player == RED) playerSymbol = 'r';
	else playerSymbol = 'b';
	int counter = 0;
	for (int i = 0; i < game.boardSize; i++) {
		for (int j = 0; j < game.boardSize; j++) {
			if (game.board[i][j] == '0') {
				game.board[i][j] = playerSymbol;
				if (isGameOver(game, true)>0) {
					counter++;
					if (counter > 1) return true;
				}
				game.board[i][j] = '0';
			}
		}
	}
	return false;
}
bool checkForPlayerEnemyPlayer(GameInfo game, int player) {
	char playerSymbol;
	if (player == RED) playerSymbol = 'r';
	else playerSymbol = 'b';
	for (int i = 0; i < game.boardSize; i++) {
		for (int j = 0; j < game.boardSize; j++) {
			if (game.board[i][j] == '0') {
				game.board[i][j] = playerSymbol;
				if (checkForEnemyPlayer(game, player)) {
					return true;
				}
				game.board[i][j] = '0';
			}
		}
	}
	return false;
}
bool checkForEnemyPlayerEnemyPlayer(GameInfo game, int player) {
	char enemySymbol;
	if (player == RED) enemySymbol = 'b';
	else enemySymbol = 'r';
	for (int i = 0; i < game.boardSize; i++) {
		for (int j = 0; j < game.boardSize; j++) {
			if (game.board[i][j] == '0') {
				game.board[i][j] = enemySymbol;
				if (!checkForPlayerEnemyPlayer(game, player)) {
					return false;
				}
				game.board[i][j] = '0';
			}
		}
	}
	return true;
}

bool perfectOpponent(GameInfo game, int moves, int player) {
	// case player
	int whoseTurn = game.redPawns - game.bluePawns;// 0 - red, 1 - blue
	if (moves == 1 && whoseTurn == player) {
		return naiveOpponent(game, moves, player);
	}
	// case enemy -> player
	else if (moves == 1 && whoseTurn != player) {
		if (!isBoardValid(game, moves, player)) return false;
		else
			return checkForEnemyPlayer(game, player);
	}
	// case player -> enemy -> player
	else if (moves == 2 && whoseTurn == player) {
		if (!isBoardValid(game, moves, player)) return false;
		else
			return checkForPlayerEnemyPlayer(game, player);
	}
	// case enemy -> player -> enemy -> player
	else {
		if (!isBoardValid(game, moves, player)) return false;
		else
			return checkForEnemyPlayerEnemyPlayer(game, player);
	}

}

void getBoard(GameInfo& game) {
	std::string input;
	char tmp[121];
	initializeArray(tmp);
	int i = 0;
	while (std::cin >> input) {
		if (input[0] == '>') {
			i++;
		}
		else if (input[0] == 'r') {
			tmp[i] = 'r';
			game.redPawns++;
		}
		else if (input[0] == 'b') {
			tmp[i] = 'b';
			game.bluePawns++;
		}
		else if (input == "---" && i > 0) {
			break;
		}
	}
	game.boardSize = int(sqrt(i));
	setBoard(tmp, game);
}


void processQuestion(GameInfo& game, std::string& question) {
	if (question == "BOARD_SIZE") {
		std::cout << game.boardSize << std::endl;
	}
	else if (question == "PAWNS_NUMBER") {
		std::cout << game.bluePawns + game.redPawns << std::endl;
	}
	else if (question == "IS_BOARD_CORRECT") {
		std::cout << (isBoardCorrect(game) ? "YES" : "NO") << std::endl;
	}
	else if (question == "IS_GAME_OVER") {
		int result = isGameOver(game, false);
		if (result == 2) {
			std::cout << "YES BLUE" << std::endl;
		}
		else if (result == 1) {
			std::cout << "YES RED" << std::endl;
		}
		else {
			std::cout << "NO" << std::endl;
		}
	}
	else if (question == "IS_BOARD_POSSIBLE") {
		std::cout << (isBoardPossible(game) ? "YES" : "NO") << std::endl;
	}
	else if (question == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
		std::cout << (naiveOpponent(game, 1, RED) ? "YES" : "NO") << std::endl;
	}
	else if (question == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
		std::cout << (naiveOpponent(game, 1, BLUE) ? "YES" : "NO") << std::endl;
	}
	else if (question == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
		std::cout << (naiveOpponent(game, 2, RED) ? "YES" : "NO") << std::endl;
	}
	else if (question == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
		std::cout << (naiveOpponent(game, 2, BLUE) ? "YES" : "NO") << std::endl;
	}
	else if (question == "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {
		std::cout << (perfectOpponent(game, 1, RED) ? "YES" : "NO") << std::endl;
	}
	else if (question == "CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {
		std::cout << (perfectOpponent(game, 1, BLUE) ? "YES" : "NO") << std::endl;
	}
	else if (question == "CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {
		std::cout << (perfectOpponent(game, 2, RED) ? "YES" : "NO") << std::endl;
	}
	else if (question == "CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {
		std::cout << (perfectOpponent(game, 2, BLUE) ? "YES" : "NO") << std::endl;
	}
}

int main() {
	while (true) {
		GameInfo game;
		getBoard(game);

		std::string question;
		while (std::cin >> question) {
			if (question == "---") break;
			processQuestion(game, question);
		}
		if (std::cin.eof()) break;
	}
	return 0;
}


