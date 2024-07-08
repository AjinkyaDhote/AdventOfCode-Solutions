#include "Solutions.h"

//Sort Order - Lowest to Highest
//High Card << One Pair <<  Two Pair << Three of a Kind << Full house << Four of a Kind << Five of a Kind

using namespace std;
enum Strength
{
};

enum Type
{
	None = 0,
	HighCard = 1,
	OnePair = 2,
	TwoPair = 3,
	ThreeOfAKind = 4,
	FullHouse = 5, 
	FourOfAHouse = 6, 
	FiveOfAKind = 7
};

Type GetHandType(string& hand)
{
	map<char, int> m { {'A', 0}, {'K', 0}, {'Q', 0}, {'J', 0}, {'T', 0}, {'9', 0}, {'8', 0}, {'7', 0}, {'6', 0}, {'5', 0}, {'4', 0}, {'3', 0}, {'2', 0} };
	for(auto c : hand)
	{
		m[c]++;
	}
	Type type = Type::HighCard;
	for (auto it = m.begin(); it != m.end(); ++it)
	{
		if (it->second == 5) type = Type::FiveOfAKind;
		if (it->second == 4) type = Type::FourOfAHouse;
		if (it->second == 3 || (it->second == 2))
		{
			if (it->second == 3) //Full House or three of a Kind
			{
				type = Type::ThreeOfAKind;
				auto temp = ++it;
				temp++;
				while (temp != m.end()) 
				{
					if (temp->second == 2)
					{
						type =  Type::FullHouse;
						break;
					}
					temp++;
				}
			}
			else if (it->second == 2) //Full House or Two of a Kind
			{
				type = Type::OnePair;
				auto temp = ++it;
				while (temp != m.end())
				{
					if (temp->second == 3)
					{
						type = Type::FullHouse;
						break;
					}
					else if (temp->second == 2)
						type = Type::TwoPair;
					else
						type =  Type::OnePair;

					temp++;
				}
			}
		}
	}

	return type;
}

void PartOne(vector<pair<string, int>>& allHands)
{
	vector<pair<string, int>> FiveOfAKindBucket;
	vector<pair<string, int>> FourOfAHouseBucket;
	vector<pair<string, int>> FullHouseBucket;
	vector<pair<string, int>> ThreeOfAKindBucket;
	vector<pair<string, int>> TwoPairBucket;
	vector<pair<string, int>> OnePairBucket;
	vector<pair<string, int>> HighCardBucket;

	for (auto& hand : allHands)
	{
		Type type = GetHandType(hand.first);
		switch (type)
		{
		case Type::None:
			break;
		case Type::HighCard:
			HighCardBucket.push_back({ hand.first, hand.second });
			break;
		case Type::OnePair:
			OnePairBucket.push_back({ hand.first, hand.second });
			break;
		case Type::TwoPair:
			TwoPairBucket.push_back({ hand.first, hand.second });
			break;
		case Type::ThreeOfAKind:
			ThreeOfAKindBucket.push_back({ hand.first, hand.second });
			break;
		case Type::FullHouse:
			FullHouseBucket.push_back({ hand.first, hand.second });
			break;
		case Type::FourOfAHouse:
			FourOfAHouseBucket.push_back({ hand.first, hand.second });
			break;
		case Type::FiveOfAKind:
			FiveOfAKindBucket.push_back({ hand.first, hand.second });
			break;
		default:
			break;
		}
	}


}


void Solutions::CamelCards()
{
	ifstream fs = Utilities::OpenFile("Day 7 Example.txt");
	string hand;

	vector<pair<string, int>> allHands;

	while (std::getline(fs, hand))
	{
		vector<std::string> split = Utilities::ReadSpaceSeperatedString(hand);
		allHands.push_back({split[0], stoi(split[1])});
	}

	PartOne(allHands);
}
