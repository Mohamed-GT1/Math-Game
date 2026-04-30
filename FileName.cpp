#include<iostream>
using namespace std;

enum RightOrWrong {
	rightAnswer = 1, wrongAnswer = 2
};

enum Level {
	easy = 1, medium = 2, hard = 3, mix = 4
};

enum OperationType {
	Add = 1, subtract = 2, multiply = 3, divide = 4, mixed = 5
};

struct RoundInfo {
	OperationType operation;
	Level lvl;
	int firstnumber, secondnumber;
	RightOrWrong answerstate;
};

struct GameInfo {
	int numberOfQuestions;
	Level lvl;
	OperationType op;
	int countOfWrongAnswers = 0;
	int countOfRightAnswers = 0;
	bool Pass;

};



int RandomNumber(int from, int to) {
	return rand() % (to - from + 1) + from;
}

int ReadNumberInRange(string message, int from, int to) {
	int number;

	do {
		cout << message << endl;
		cin >> number;

		if (number < from || number > to)
			cout << "invalid input try again";

	} while (number < from || number > to);
	return number;

}

int GenerateNumberBasedOnLevel(Level lvl) {

	if (lvl == Level::mix)
		lvl = (Level)RandomNumber(1, 3);

	switch (lvl) {
	case Level::easy:
		return RandomNumber(1, 15);
	case Level::medium:
		return RandomNumber(10, 40);
	case Level::hard:
		return RandomNumber(40, 100);
	default:
		return RandomNumber(10, 40);

	}
}

OperationType GetOperationBasedOnInput(OperationType op) {

	if (op == OperationType::mixed)
		return (OperationType)RandomNumber(1, 4);
	else
		return op;

}

int CalculateAnswer(RoundInfo roundInfo) {

	switch (roundInfo.operation) {
	case multiply:
		return roundInfo.firstnumber * roundInfo.secondnumber;
	case divide:
		return roundInfo.firstnumber / roundInfo.secondnumber;
	case Add:
		return roundInfo.firstnumber + roundInfo.secondnumber;
	case subtract:
		return roundInfo.firstnumber - roundInfo.secondnumber;
	default:
		return roundInfo.firstnumber + roundInfo.secondnumber;
	}
}

char GetOperationSymbol(OperationType op) {

	switch (op) {
	case multiply:
		return '*';
	case divide:
		return '/';
	case Add:
		return '+';
	case subtract:
		return '-';
	}

}

void PrintQuestion(RoundInfo roundInfo) {

	cout << endl;
	cout << roundInfo.firstnumber << endl;
	cout << roundInfo.secondnumber << "  " << GetOperationSymbol(roundInfo.operation) << endl;
	cout << "-------\n";
}

void UpdateGameResults(RoundInfo roundInfo, GameInfo& gameInfo) {

	if (roundInfo.answerstate == rightAnswer)
		gameInfo.countOfRightAnswers++;
	else
		gameInfo.countOfWrongAnswers++;


}

OperationType GetOperationTypeFromUser() {

	return (OperationType)(ReadNumberInRange("what Operation do you want ? [1]add [2]Subtraction [3]multiplication [4]division [5]mix", 1, 5));

}
Level GetLevelFromUser() {

	return (Level)ReadNumberInRange("What level do you want? [1]easy [2]medium [3]hard [4]mix", 1, 4);

}



string GetLevelName(int i) {

	string Levels[] = { "easy" , "medium" , "hard" , "mix" };

	return Levels[i - 1];

}
string GetOperationName(int i) {

	string Operations[] = { "Add" , "Subtract" , "Multiply" ,"Divide", "Mix" };

	return Operations[i - 1];

}



RightOrWrong GetAnswerAndEvaluate(RoundInfo roundInfo) {

	int inputAnswer;
	cin >> inputAnswer;

	int answer = CalculateAnswer(roundInfo);

	if (inputAnswer == answer) {
		roundInfo.answerstate = rightAnswer;
		system("color A0");
		cout << "right answer\n";

	}
	else {
		roundInfo.answerstate = wrongAnswer;
		system("color C0");
		cout << "\a";
		cout << "wrong answer\n";
		cout << "the right answer is " << answer << endl;

	}

	return roundInfo.answerstate;
}


Level GetLevelForRound(GameInfo gameInfo) {

	if (gameInfo.lvl == Level::mix)
		return (Level)RandomNumber(1, 3);
	else
		return gameInfo.lvl;

}

void DisplayPassOrFail(string PassOrFail) {



	cout << "\n\n\n________________________________________________________\n";
	cout << "\n_________________Final Result is " << PassOrFail << "_______________\n";
	cout << "\n________________________________________________________\n";


}

void PrintFinalGameResults(GameInfo gameInfo) {

	if (gameInfo.countOfRightAnswers > gameInfo.countOfWrongAnswers) {

		DisplayPassOrFail("Pass :-)");

	}
	else {

		DisplayPassOrFail("Fail :-(");
	}


	cout << "\nnumber of questions        : " << gameInfo.numberOfQuestions;
	cout << "\nQuestions level            : " << GetLevelName(gameInfo.lvl);
	cout << "\noperation type             : " << GetOperationName(gameInfo.op);
	cout << "\nnumber of right questions  : " << gameInfo.countOfRightAnswers;
	cout << "\nnumber of wrong questions  : " << gameInfo.countOfWrongAnswers << endl;
	cout << "________________________________________________________\n";
}

void PlayRound(GameInfo& gameInfo) {

	RoundInfo roundInfo;

	roundInfo.lvl = GetLevelForRound(gameInfo);


	roundInfo.firstnumber = GenerateNumberBasedOnLevel(roundInfo.lvl);
	roundInfo.secondnumber = GenerateNumberBasedOnLevel(roundInfo.lvl);
	roundInfo.operation = GetOperationBasedOnInput(gameInfo.op);

	PrintQuestion(roundInfo);

	roundInfo.answerstate = GetAnswerAndEvaluate(roundInfo);


	UpdateGameResults(roundInfo, gameInfo);



}


void StartGame() {

	int numberOfQuestions;

	numberOfQuestions = ReadNumberInRange("how many questions do you want ? 1 to 10", 1, 10);

	GameInfo gameInfo;

	gameInfo.numberOfQuestions = numberOfQuestions;
	gameInfo.lvl = GetLevelFromUser();
	gameInfo.op = GetOperationTypeFromUser();

	for (int questionNumber = 1; questionNumber <= numberOfQuestions; questionNumber++) {

		cout << "\n\n____________________________";
		cout << "\nQuestion [" << questionNumber << "/" << numberOfQuestions << "]\n";
		PlayRound(gameInfo);
		cout << "____________________________\n\n";


	}
	PrintFinalGameResults(gameInfo);



}

void ResetScreen() {

	system("cls");
	system("color 07");

}

void Game() {

	char playAgain;

	do {
		ResetScreen();

		StartGame();

		cout << "do you want to play again? [y]Yes [n]No  ";
		cin >> playAgain;
	} while (playAgain == 'y' || playAgain == 'Y');
}

int main() {

	srand((unsigned)time(NULL));

	Game();


	return 0;
}