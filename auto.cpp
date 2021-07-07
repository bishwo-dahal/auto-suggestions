#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include <cctype>
using namespace std;

void displayCharVector(std::vector<char> arr)
{
	for (char val : arr)
	{
		std::cout << val;
	}
	std::cout << std::endl;
}
bool compare(char a, char b)
{
	if (toupper(a) == toupper(b))
	{
		return true;
	}
	return false;
}
void display(std::vector<std::pair<char, int>> val)
{
	for (auto curr : val)
	{
		std::cout << "Value = " << curr.first << " Index = " << curr.second << std::endl;
	}
}
void displayVectorDeque(std::deque<std::vector<char>> val)
{
	for (std::vector<char> elem : val)
	{
		displayCharVector(elem);
	}
}
int main()
{
	// (466551)
	std::deque<std::vector<char>> words;
	//used  <std::vector<char>> because , it's much easier to go with it
	std::vector<std::pair<char, int>> wordsIndex;
	// It
	fstream openFile("words.txt");
	std::string word = "";
	if (openFile)
	{
		int index = 0;
		char beforeChar = ' ';
		while (getline(openFile, word))
		{
			std::vector<char> stringVector(word.length());
			std::copy(word.begin(), word.end(), stringVector.begin());
			words.push_back(stringVector);
			//pushing the vector to main deque
			index = words.size();

			if (!compare(stringVector.at(0), beforeChar))
			{
				wordsIndex.push_back(std::make_pair(tolower(stringVector.at(0)), index));
			}
			beforeChar = stringVector.at(0);
		}
	}
	else
	{
		std::cout << "Could not find the dictionary " << std::endl;
	}

	std::string input;
	std::cout << "Enter word to find ------------" << std::endl;
	std::cin >> input;
	// input = "pn";  // Written Just for testing

	std::vector<char> inputVector(input.length());
	std::copy(input.begin(), input.end(), inputVector.begin());
	std::deque<vector<char>>::iterator foundIterator = std::find(words.begin(), words.end(), inputVector);

	if (foundIterator == words.end())
	{
		//l
		std::cout << "No matching words found " << std::endl;
		std::cout << "Suggestions for you are \n";

		char currentChar = inputVector.at(0);
		std::vector<std::pair<char, int>>::iterator letterIterator = find_if(wordsIndex.begin(), wordsIndex.end(), [&currentChar](const std::pair<char, int> &element)
																			 { return compare(element.first, currentChar); });
		// just handling valid case only
		if (letterIterator != wordsIndex.end())
		{
			int currentLetterIndex = (*letterIterator).second;
			int nextLetterIndex = (*(letterIterator + 1)).second;
			std::deque<std::vector<char>> suggestions(words.size());
			std::copy(words.begin(), words.end(), suggestions.begin());
			suggestions.erase(std::remove_if(
								  suggestions.begin(), suggestions.end(),
								  [&](const std::vector<char> elem)
								  {
									  return elem.size() != inputVector.size(); // put your condition here
								  }),
							  suggestions.end());

			for (int cc = 1; cc < inputVector.size(); cc++)
			{
				std::deque<std::vector<char>> previousSuggestion = suggestions;

				suggestions.erase(std::remove_if(suggestions.begin(), suggestions.end(),
												 [&](const std::vector<char> elem)
												 {
													 return !compare(elem.at(cc), inputVector.at(cc));
												 }),
								  suggestions.end());

				if (suggestions.size() == 0)
				{
					suggestions = previousSuggestion;
					cc++;
					if (cc < inputVector.size())
					{
						suggestions.erase(std::remove_if(suggestions.begin(), suggestions.end(),
														 [&](const std::vector<char> elem)
														 {
															 //  std::cout << "elem =" << elem.at(cc) << "    input =" << inputVector.at(cc) << std::endl;
															 return !compare(elem.at(cc), inputVector.at(cc));
														 }),
										  suggestions.end());
						previousSuggestion = suggestions;
					}
					else
					{
						break;
					}
				}
			}
			if (suggestions.size() > 5)
			{
				suggestions.erase(suggestions.begin() + 5, suggestions.end());
			}
			displayVectorDeque(suggestions);
		}
	}
	else
	{
		std::cout << "Found your word at the dictionary\n";
		std::cout << "Here are the list of words near this one " << std::endl;
		displayCharVector(*(foundIterator - 1));
		displayCharVector(*(foundIterator + 1));
	}

	return 0;
}

// speed changed from (5-6) to (6-8)
