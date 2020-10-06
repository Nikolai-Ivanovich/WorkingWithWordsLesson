#include <iostream>
using namespace std;
#define N 512
#define PLAGIARISMRATE 40

bool isPlagiarism(char myText[], char originalText[], int n);
bool isStringConsistPhrase(char text[], char word[]);
void copyString(char newString[], char oldString[]);
bool compareString(char newString[], char oldString[]);
bool isSeparator(char c);
void printfString(char string[]);
void normalizerString(char string[]);
void clearExtraSpaces(char string[]);
void cleaExtraSymbols(char string[]);
void convertStringToGeneralCase(char string[]);


int main() {
	
	
	char myText[N] = "I   love     play in            footbol ivning";
	//char myText[N] = "To fix this error compare compare use of identifier identifier to the identifier declaration for case and spelling Verify that scope resolution operators and namespace using directives are used correctly";

	//char text2[N] = "To remove this remove, functions from of the to the declaration case for case and Verify. Verscopeify that Verify namespace operators and directives using used are used correctly!";
	char originalText[N] = "Changes to I love play in footbol ivning To fix this remove obsolete functions from the C Runtime Library in Visual Studio 2015 can cause C3861 To resolve this error remove references to these functions or replace them with their secure alternatives if any For more information see Obsolete Functions";
	
	// нормализация: убрать пробелы и символы, привести все символы к одному регистру
	normalizerString(myText);
	
	cout << "myText:" << endl;

	printfString(myText);
	cout << endl << "originalText:" << endl;
	printfString(originalText);

	if (isPlagiarism(myText, originalText, 4) == true)
		cout << endl << "MyText and originalText - plagiarism.";
	else
		cout << endl << "MyText and originalText - are not plagiarized.";

	return 0;
}

void normalizerString(char string[])
{
	clearExtraSpaces(string);
	cleaExtraSymbols(string);
	convertStringToGeneralCase(string);
}

void clearExtraSpaces(char string[])
{
	char tempString[N];
	bool isPreviousValueSpace = false;

	copyString(string, tempString);
	
	int countMissValue = 0, i = 0;

	for (i; tempString[i] != '\0'; i++)
	{
		if (isPreviousValueSpace == true and tempString[i] == ' ')
		{
			countMissValue++;
			continue;
		}
		else if (tempString[i] == ' ')
			isPreviousValueSpace = true;
		
		string[i - countMissValue] = tempString[i];
		
		if (string[i - countMissValue] != ' ')
			isPreviousValueSpace = false;
	}
	string[i - countMissValue] = '\0';
	// нужно научить функцию убирать пробелы в конце
}

void cleaExtraSymbols(char string[])
{

}

void convertStringToGeneralCase(char string[])
{

}


void printfDuplicateWords(char text[])
{
	char oldWord[N], newWord[N];
	int iw = 0;

	for (int i = 0; text[i] != '\0'; i++)
	{
		if (isSeparator(text[i]) != true) {
			newWord[iw] = text[i];
			iw++;
			if (isSeparator(text[i + 1]) or text[i + 1] == '\0') {
				newWord[iw] = '\0';
				iw = 0;
				if (compareString(newWord, oldWord))
					cout << newWord << endl;
				copyString(newWord, oldWord);
			}
		}
	}
}

bool isSeparator(char c) {
	char separator[] = " ,.;:?!";
	for (int i = 0; separator[i] != '\0'; i++)
		if (c == separator[i])
			return true;
	return false;
}

void copyString(char string[], char emptyString[])
{
	int i = 0;
	for (i; string[i] != '\0'; i++)
	{
		emptyString[i] = string[i];
	}
	emptyString[i] = '\0';
}

bool compareString(char newString[], char oldString[])
{
	for (int i = 0; newString[i] != '\0'; i++)
	{
		if (newString[i] != oldString[i])
			return false;
	}
	return true;
}

bool isStringConsistPhrase(char text[], char phrase[])
{
	for (int i = 0; text[i] != '\0'; i++)
	{
		for (int j = 0; phrase[j] != '\0'; j++)
		{
			if (phrase[j] != text[i + j])
				break;
			if (phrase[j + 1] == '\0')
				return true;
		}
	}
	return false;
}

void printfString(char string[])
{
	for (int i = 0; string[i] != '\0'; i++)
		cout << string[i];
}

bool isPlagiarism(char myText[], char originalText[], int n)
{
	char phrase[N];
	int length = 0, coincidences = 0, countSpace = 0, startSecondWord = 0;
	bool isEnd = false;

	int i = 0;
	while (isEnd == false)
	{
		if (myText[i + 1] == '\0')
		{
			isEnd = true;
		}

		phrase[length] = myText[i];
		length++;

		if ((myText[i + 1] == ' ' or myText[i + 1] == '\0') and countSpace < n)
		{
			if (countSpace == 0)
				startSecondWord = i + 1;

			countSpace++;
			if (countSpace == n)
			{
				phrase[length] = '\0';
				length = 0;
				countSpace = 0;

				if (isStringConsistPhrase(originalText, phrase) == true)
					coincidences++;
				i = startSecondWord;
			}
		}

		i++;
	}
	/*for (int i = 0; isEnd == false; i++)
	{
		if (myText[i + 1] == '\0')
		{
			isEnd = true;
		}

		phrase[length] = myText[i];
		length++;

		if ((myText[i + 1] == ' ' or myText[i + 1] == '\0') and countSpace < n)
		{
			if (countSpace == 0)
				startSecondWord = i + 1;

			countSpace++;
			if (countSpace == n)
			{
				phrase[length] = '\0';
				length = 0;
				countSpace = 0;

				if (isStringConsistPhrase(originalText, phrase) == true)
					coincidences++;
				i = startSecondWord;
			}
		}
	}*/

	// Вызов функии которая считает количество слов в myText
	int countWordMyText = 124;

	double procentPlagiarism = 100 * coincidences  * n / countWordMyText;
	if (procentPlagiarism >= PLAGIARISMRATE)
		return true;
	else
		return false;
}