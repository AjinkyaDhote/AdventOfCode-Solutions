//--- Day 4: ScratchCards ---

#include "Solutions.h"

int CalculateLineScore(std::unordered_set<int>& winningNumbers, std::unordered_set<int>& myNumbers);
int CalculateLineScoreVector(std::vector<int>& winningNumbers, std::vector<int>& myNumbers);
void ScratchCardsPartOne();

void ScratchCardsPartTwo();

typedef int CardNumber;
typedef int CardInstances;

uint16_t GetWinningNumbers(std::vector<int>& winningNumbers, std::vector<int>& myNumbers);


void Solutions::ScratchCards() //27059
{
    std::cout << "Day 4 - Scratch Cards" << std::endl;
    ScratchCardsPartOne();
    ScratchCardsPartTwo();
}

void ScratchCardsPartOne()
{
    //Open and read the file
    std::ifstream fs = Utilities::OpenFile("Day 4 Input.txt");
    std::string line;

    std::unordered_set<int> winningNumbers;
    std::unordered_set<int> myNumbers;
    std::vector<int> winningNumbersVec;
    std::vector<int> myNumbersVec;
    long int sum = 0;

    while (std::getline(fs, line))
    {
        //Line structure
        //Card N: 41 48 83 86 17 | 83 86 6 31 17 9 48 53
        //41, 48, 83, 86, 17 are winning numbers
        // | -> seperator
        // Numbers after seperator are the numbers I have.

        std::vector<std::string> vec = Utilities::SplitString(line, "|");
        vec[1].erase(vec[1].begin()); //Handle space at the beginning

        std::vector<std::string> splitWinningNumbers = Utilities::SplitString(vec[0], ":");
        splitWinningNumbers[1].erase(splitWinningNumbers[1].begin()); //Handle space at the beginning
        splitWinningNumbers[1].erase(splitWinningNumbers[1].end() - 1); //Handle space at the end

        std::vector<std::string> winningNums = Utilities::ReadSpaceSeperatedString(splitWinningNumbers[1]);

        for (std::string wn : winningNums)
        {
            winningNumbers.insert(std::stoi(wn));
            winningNumbersVec.push_back(std::stoi(wn));
        }

        std::vector<std::string> myNums = Utilities::ReadSpaceSeperatedString(vec[1]);

        for (std::string myno : myNums)
        {
            myNumbers.insert(std::stoi(myno));
            myNumbersVec.push_back(std::stoi(myno));
        }

        int lineSum = CalculateLineScore(winningNumbers, myNumbers);

        sum += lineSum;

        winningNumbers.clear();
        myNumbers.clear();
        winningNumbersVec.clear();
        myNumbersVec.clear();
    }

    std::cout << "Scratch Cards Total Points - " << sum << std::endl;
}

void ScratchCardsPartTwo()
{
    //Open and read the file
    std::ifstream fs = Utilities::OpenFile("Day 4 Input.txt");
    std::string line;
    std::map<CardNumber, CardInstances> scratchCards;
    int sum = 0;
    int cardNumber = 1;
    std::vector<int> winningNumbersVec;
    std::vector<int> myNumbersVec;

    while (std::getline(fs, line)) //Read each line
    {
       //Line structure
       //Card N: 41 48 83 86 17 | 83 86 6 31 17 9 48 53
       //41, 48, 83, 86, 17 are winning numbers
       // | -> seperator

        std::vector<std::string> vec = Utilities::SplitString(line, "|");
        std::vector<std::string> splitString = Utilities::SplitString(vec[0], ":");

        std::vector<std::string> winningNumbers = Utilities::ReadSpaceSeperatedString(splitString[1]);

        for (std::string str : winningNumbers)
        {
            winningNumbersVec.push_back(std::stoi(str));
        }

        std::vector<std::string> myNumbers = Utilities::ReadSpaceSeperatedString(vec[1]);

        for (std::string str : myNumbers)
        {
            myNumbersVec.push_back(std::stoi(str));
        }

        uint16_t winningNumbCount = GetWinningNumbers(winningNumbersVec, myNumbersVec);

        //Add ourselves to the map
        scratchCards.find(cardNumber) == scratchCards.end() ? scratchCards[cardNumber] = 1 : 
            scratchCards[cardNumber]++;
        int nextLineNumberToRead = 1;

        while (winningNumbCount > 0)
        {
            int c = fs.peek();
            if (c != EOF)
            {
                //Add next card number to the map;
                if (scratchCards.find(cardNumber + nextLineNumberToRead) == scratchCards.end())
                {
                    scratchCards[cardNumber + nextLineNumberToRead] = scratchCards[cardNumber];
                }
                else
                {
                   //For every copy of current card add an occurence of the next card.
                    scratchCards[cardNumber + nextLineNumberToRead] += scratchCards[cardNumber];
                }
            }
            else
            {
                break; //We have reached end of file.

            }
            winningNumbCount--;
            nextLineNumberToRead++;
        }
        
        winningNumbersVec.clear();
        myNumbersVec.clear();
        cardNumber++;
    }

    for (auto element : scratchCards)
    {
        sum += element.second;
    }

    std::cout << "Total Scratch Cards won - " << sum << std::endl;

}

uint16_t GetWinningNumbers(std::vector<int>& winningNumbers, std::vector<int>& myNumbers)
{
    //Find each winning number in my numbers vector
    int lineSum = 0;
    uint16_t totalWinningNumbers = 0;

    for (size_t i = 0; i < winningNumbers.size(); ++i)
    {
        for (size_t j = 0; j < myNumbers.size(); ++j)
        {
            if (winningNumbers[i] == myNumbers[j])
            {
                totalWinningNumbers++;
                break;
            }
        }
    }

    return totalWinningNumbers;
}

//Additional method to find the element using unordered_set. Written to measure time complexity.
int CalculateLineScore(std::unordered_set<int>& winningNumbers, std::unordered_set<int>& myNumbers)
{
    //Find each winning number in my numbers vector
    int lineSum = 0;

    for (const int& element : winningNumbers)
    {
        if (myNumbers.find(element) != myNumbers.end())
        {
            if (lineSum == 0)
            {
                lineSum = 1;
            }
            else
            {
                lineSum += lineSum;
            }
        }
    }

    return lineSum;
}

//Additional method to find the element using vectors. Written to measure time complexity.
int CalculateLineScoreVector(std::vector<int>& winningNumbers, std::vector<int>& myNumbers)
{
    //Find each winning number in my numbers vector
    int lineSum = 0;

    for (size_t i = 0; i < winningNumbers.size(); ++i)
    {
        for (size_t j = 0; j < myNumbers.size(); ++j)
        {
            if (winningNumbers[i] == myNumbers[j])
            {
                if (lineSum == 0)
                    lineSum = 1;
                else
                {
                    lineSum += lineSum;
                }
                break;
            }
        }
    }

    return lineSum;
}
