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
	FourOfAKind = 6, 
	FiveOfAKind = 7
};

map<char, int> m{ {'A', 0}, {'K', 0}, {'Q', 0}, {'J', 0}, {'T', 0}, {'9', 0}, {'8', 0}, {'7', 0}, {'6', 0}, {'5', 0}, {'4', 0}, {'3', 0}, {'2', 0} };

int GetOrder(char c)
{
	if (c == 'A') return 14;
	if (c == 'K') return 13;
	if (c == 'Q') return 12;
	if (c == 'J') return 11;
	if (c == 'T') return 10;

	return -1;
}

int GetnewOrder(char c)
{
	if (c == 'A') return 14;
	if (c == 'K') return 13;
	if (c == 'Q') return 12;
	if (c == 'J') return 1;
	if (c == 'T') return 10;

	return -1;
}


Type GetHandType(string& hand, bool JAsJoker = false)
{
	m.clear();
	int countJoker = 0;
	for(auto c : hand)
	{
		if (c == 'J')
			countJoker++;
		m[c]++;
	}
	Type type = Type::HighCard;
	
	for (auto it = m.begin(); it != m.end(); ++it)
	{
		if (type != Type::HighCard) break;
		
		if (it->second == 5)
		{
			type = Type::FiveOfAKind;
			break;
		}
		if (it->second == 4)
		{
			type = Type::FourOfAKind;
			break;
		}
		if (it->second == 3 || (it->second == 2))
		{
			if (it->second == 3) //Full House or three of a Kind
			{
				type = Type::ThreeOfAKind;
				auto temp = it;
				temp++;
				while (temp != m.end())
				{
					if (temp->second == 2)
					{
						type = Type::FullHouse;
						break;
					}
					temp++;
				}
			}
			else if (it->second == 2) //Full House or Two of a Kind
			{
				type = Type::OnePair;
				auto temp = it;
				temp++;
				while (temp != m.end())
				{
					if (temp->second == 3)
					{
						type = Type::FullHouse;
						break;
					}
					else if (temp->second == 2)
					{
						type = Type::TwoPair;
						break;
					}
					temp++;
				}
			}
		}
	}
	
	if (JAsJoker && m.find('J') != m.end())
	{
		int jC = m['J'];
		if (jC == 1)
		{
			if (type == HighCard) type = Type::OnePair;
			else if (type == OnePair) type = Type::ThreeOfAKind;
			else if (type == TwoPair) type = Type::FullHouse;
			else if (type == ThreeOfAKind) type = Type::FourOfAKind;
			else if (type == FourOfAKind) type = Type::FiveOfAKind;
		}
		else if (jC == 2)
		{
			if (type == OnePair) type = Type::ThreeOfAKind;
			else if (type == TwoPair) type = Type::FourOfAKind;
			else if (type == ThreeOfAKind) type = Type::FiveOfAKind;
			else if (type == FullHouse) type = Type::FiveOfAKind;
		}
		else if (jC == 3)
		{
			if (type == ThreeOfAKind) type = Type::FourOfAKind;
			else if (type == FullHouse) type = Type::FiveOfAKind;
		}
		else if (jC == 4)
		{
			if (type == FourOfAKind) type = Type::FiveOfAKind;
		}
	}

	return type;
}



bool SortHandsAscending(pair<string, int>& LeftHand, pair<string, int>& RightHand)
{
	//Strength - Highest To Lowest
	//A - K - Q - J - T - 9 - 8 - 7 - 6 - 5 - 4 - 3 - 2
	
	const string& L = LeftHand.first;
	const string& R = RightHand.first;

	FOR(i, sz(L))
	{
		if (L[i] == R[i])
			continue;
		bool isLeftCharAlphabet = isalpha(L[i]);
		bool isRightCharAlphabet = isalpha(R[i]);

		if ( !isLeftCharAlphabet && !isRightCharAlphabet )
		{
			return L[i] <  R[i];
		}
		else if(isLeftCharAlphabet && !isRightCharAlphabet )
		{
			return false;
		}
		else if (!isLeftCharAlphabet && isRightCharAlphabet)
		{
			return true;
		}
		else
		{
			return GetOrder(L[i]) < GetOrder(R[i]);
		}
	}

	return false;
}

bool SortHandsAscendingWithJoker(pair<string, int>& LeftHand, pair<string, int>& RightHand)
{
	//Strength - Highest To Lowest
	//A - K - Q - T - 9 - 8 - 7 - 6 - 5 - 4 - 3 - 2 - J

	const string& L = LeftHand.first;
	const string& R = RightHand.first;

	FOR(i, sz(L))
	{
		if (L[i] == R[i])
			continue;
		bool isLeftCharAlphabet = isalpha(L[i]);
		bool isRightCharAlphabet = isalpha(R[i]);

		if (!isLeftCharAlphabet && !isRightCharAlphabet) //No alphabets
		{
			return L[i] < R[i];
		}
		else if (isLeftCharAlphabet && !isRightCharAlphabet) //Left is alphabet, right is 0-9
		{
			if (L[i] == 'J')
				return true;
			return false;
		}
		else if (!isLeftCharAlphabet && isRightCharAlphabet) //Left 0-9. right is alphabet
		{
			if (R[i] == 'J')
				return false;
			return true;
		}
		else
		{
			return GetnewOrder(L[i]) < GetnewOrder(R[i]); // Both are alphabets
		}
	}

	return false;
}

void PartOne(vector<pair<string, int>>& allHands, bool JAsJoker = false)
{
	vector<pair<string, int>> FiveOfAKindBucket;
	vector<pair<string, int>> FourOfAKindBucket;
	vector<pair<string, int>> FullHouseBucket;
	vector<pair<string, int>> ThreeOfAKindBucket;
	vector<pair<string, int>> TwoPairBucket;
	vector<pair<string, int>> OnePairBucket;
	vector<pair<string, int>> HighCardBucket;

	for (auto& hand : allHands) 
	{
		Type type = GetHandType(hand.first, JAsJoker);
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
		case Type::FourOfAKind:
			FourOfAKindBucket.push_back({ hand.first, hand.second });
			break;
		case Type::FiveOfAKind:
			FiveOfAKindBucket.push_back({ hand.first, hand.second });
			break;
		default:
			break;
		}
	}

	//Start numbering from lowest.
	sort(HighCardBucket.begin(), HighCardBucket.end(), JAsJoker ? SortHandsAscendingWithJoker : SortHandsAscending);
	sort(OnePairBucket.begin(), OnePairBucket.end(), JAsJoker ? SortHandsAscendingWithJoker : SortHandsAscending);
	sort(TwoPairBucket.begin(), TwoPairBucket.end(), JAsJoker ? SortHandsAscendingWithJoker : SortHandsAscending);
	sort(ThreeOfAKindBucket.begin(), ThreeOfAKindBucket.end(), JAsJoker ? SortHandsAscendingWithJoker : SortHandsAscending);
	sort(FullHouseBucket.begin(), FullHouseBucket.end(), JAsJoker ? SortHandsAscendingWithJoker : SortHandsAscending);
	sort(FourOfAKindBucket.begin(), FourOfAKindBucket.end(), JAsJoker ? SortHandsAscendingWithJoker : SortHandsAscending);
	sort(FiveOfAKindBucket.begin(), FiveOfAKindBucket.end(), JAsJoker ? SortHandsAscendingWithJoker : SortHandsAscending);

	int rank = 1;
	long long sum = 0;
	for (auto &card : HighCardBucket )
	{
		sum += card.second * rank;
		rank++;
	}
	for (auto &card : OnePairBucket)
	{
		sum += card.second * rank;
		rank++;
	}
	for (auto &card : TwoPairBucket)
	{
		sum += card.second * rank;
		rank++;
	}
	for (auto &card : ThreeOfAKindBucket)
	{
		sum += card.second * rank;
		rank++;
	}
	for (auto &card : FullHouseBucket)
	{
		sum += card.second * rank;
		rank++;
	}
	for (auto &card : FourOfAKindBucket)
	{
		sum += card.second * rank;
		rank++;
	}
	for (auto &card : FiveOfAKindBucket)
	{
		sum += card.second * rank;
		rank++;
	}

	cout << "Total Winnings " << sum << "\n";
}


void Solutions::CamelCards()
{
	ifstream fs = Utilities::OpenFile("Day 7 Input.txt");
	string hand;

	vector<pair<string, int>> allHands;

	while (getline(fs, hand))
	{
		vector<string> split = Utilities::ReadSpaceSeperatedString(hand);
		allHands.push_back({split[0], stoi(split[1])});
	}

	PartOne(allHands);
	PartOne(allHands, true);
}
