#include<iostream>
using namespace std;



enum Level {
	easy =1,medium =2,hard =3 ,mix =4
};

enum OperationType {
	Add=1,subtract=2,multiply =3,divide =4,mixed=5
};

struct QuestionInfo {
	OperationType operation;
	Level lvl;
	int firstnumber, secondnumber;
	bool answerstate;
	int inputAnswer;
	int answer;
};

struct QuizzInfo {
	
	QuestionInfo listOfQuestions[100];
	Level lvl;
	OperationType op;
	int numberOfQuestions;
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

OperationType GetOperationForQuestion(OperationType op) {

	if (op == OperationType::mixed)
		return (OperationType)RandomNumber(1, 4);
	else
		return op;

}

int CalculateAnswer(QuestionInfo QuestionInfo) {

	switch (QuestionInfo.operation) {
	case multiply:
		return QuestionInfo.firstnumber * QuestionInfo.secondnumber;
	case divide:
		return QuestionInfo.firstnumber / QuestionInfo.secondnumber;
	case Add:
		return QuestionInfo.firstnumber + QuestionInfo.secondnumber;
	case subtract:
		return QuestionInfo.firstnumber - QuestionInfo.secondnumber;
	default:
		return QuestionInfo.firstnumber + QuestionInfo.secondnumber;
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

void PrintQuestion(QuestionInfo QuestionInfo) {

	cout << endl;
	cout << QuestionInfo.firstnumber << endl;
	cout << QuestionInfo.secondnumber << "  "<<GetOperationSymbol(QuestionInfo.operation)<<endl;
	cout << "-------\n";
}

void UpdateGameResults(QuestionInfo QuestionInfo, QuizzInfo& QuizzInfo) {

	if (QuestionInfo.answerstate == true)
		QuizzInfo.countOfRightAnswers++;
	else
		QuizzInfo.countOfWrongAnswers++;


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

	string Operations[] = { "Add" , "Subtract" , "Multiply" ,"Divide", "Mix"};

	return Operations[i - 1];

}




Level GetLevelForQuestion(Level quizzLvl) {

	if (quizzLvl == Level::mix)
		return (Level)RandomNumber(1, 3);
	else
		return quizzLvl;

}

void DisplayPassOrFail(string PassOrFail) {



	cout << "\n\n\n________________________________________________________\n";
	cout << "\n_________________Final Result is " << PassOrFail << "_______________\n";
	cout << "\n________________________________________________________\n";


}

void PrintFinalGameResults(QuizzInfo QuizzInfo) {

	if (QuizzInfo.countOfRightAnswers >= QuizzInfo.countOfWrongAnswers) {

		DisplayPassOrFail("Pass :-)");

	}
	else {

		DisplayPassOrFail("Fail :-(");
	}


	cout << "\nnumber of questions        : " << QuizzInfo.numberOfQuestions;
	cout << "\nQuestions level            : " << GetLevelName(QuizzInfo.lvl);
	cout << "\noperation type             : " << GetOperationName(QuizzInfo.op);
	cout << "\nnumber of right questions  : " << QuizzInfo.countOfRightAnswers;
	cout << "\nnumber of wrong questions  : " << QuizzInfo.countOfWrongAnswers << endl;
	cout << "________________________________________________________\n";
}



void GenerateQuestion(QuestionInfo & question,QuizzInfo & quizz) {

	question.lvl = GetLevelForQuestion(quizz.lvl);

	question.firstnumber= GenerateNumberBasedOnLevel(question.lvl);

	question.secondnumber = GenerateNumberBasedOnLevel(question.lvl);

	question.operation = GetOperationForQuestion(quizz.op);

	question.answer = CalculateAnswer(question);


}


void GetQuestionAnswerFromUserAndEvaluate(QuestionInfo & question) {

	PrintQuestion(question);

	cin>>question.inputAnswer;



	if (question.answer == question.inputAnswer) {
	
		system("color A0");
		cout << "right answer\n";

		question.answerstate = true;
	
	
	
	}
	else {
		
		system("color C0");
		cout << "\a";
		cout << "wrong answer\n";
		cout << "the right answer is " << question.answer << endl;
		question.answerstate = false;

	}

	



}


void StartGame() {

	QuizzInfo quizz;

	quizz.numberOfQuestions = ReadNumberInRange("how many questions do you want ? 1 to 10", 1, 10);

	quizz.lvl = GetLevelFromUser();
	quizz.op = GetOperationTypeFromUser();


	for (int questionNumber = 0; questionNumber < quizz.numberOfQuestions; questionNumber++) {
		
		cout << "\n\n____________________________";
		cout << "\nQuestion [" << questionNumber+1 << "/" << quizz.numberOfQuestions << "]\n";

		GenerateQuestion( quizz.listOfQuestions[questionNumber] , quizz );
		GetQuestionAnswerFromUserAndEvaluate(quizz.listOfQuestions[questionNumber]);
		UpdateGameResults(quizz.listOfQuestions[questionNumber], quizz);

	}

	//diferent from abo hadhoud one in that in hadhoud her loops to 1 generate all questions then loops to get answer
	//for every question and then update and print the result 



	
	PrintFinalGameResults(quizz);



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