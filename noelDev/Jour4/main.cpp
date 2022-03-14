#include "BingoBoard.hpp"

vector<int> split(string str, const string delim)
{
  size_t pos = 0;
  int token;
  vector<int> res;
  while ((pos = str.find(delim)) != std::string::npos) {
      try{
      token = stoi(str.substr(0, pos));
      res.push_back(token);
      }
      catch(std::invalid_argument& e){}
      str.erase(0, pos + delim.length());
  }
  try{
    token = stoi(str);
    res.push_back(token);
  }
  catch(std::invalid_argument& e){}
  return res;
}

void playBingo(vector<BingoBoard*>& boards, vector<int>& number)
{
  for (int num: number)
    for (int i = 0; i < boards.size(); i++)
      if (!boards[i]->isBingo())
        if (boards[i]->drawNumber(num))
          return ;
}

int playReverseBingo(vector<BingoBoard*>& boards, vector<int>& number)
{
  int winnerIndex = -1;
  int winerCpt = 0;
  int nbBoard = boards.size();
  for (int num: number)
  {
    for (int i = 0; i < nbBoard; i++)
    {
      if (!boards[i]->isBingo())
      {
        if (boards[i]->drawNumber(num))
        {
          winnerIndex = i;
          winerCpt++;
        }
      }
    }  
  }
  return winnerIndex;
}

void printBoards(const vector<BingoBoard*>& boards)
{
  cout << "Size : " << boards.size() << endl;
  for(int i = 0; i < boards.size(); i++)
  {
    boards[i]->print();
  }
}

void printWinner(const vector<BingoBoard*>& boards)
{
  for(int i = 0; i < boards.size(); i++)
  {
    if (boards[i]->isBingo())
    {
      cout << "["<<i<<"] " << boards[i]->getResultat() << endl;
    }
  }
}

int main()
{
  std::ifstream file("input.txt");
  vector<int> number;
  vector<BingoBoard*> boards;

  string str;
  bool loadBoard = false;
  int lineCnt = 0;
  int indexboard = 0;
  int nbBoard = 0;
  BoardMap board;
  while (std::getline(file, str)) 
  {
    if (lineCnt == 0)
      number = split(str, ",");
    else
    {
      if (str == "")
      {
        if (lineCnt != 1 && indexboard > 0)
        {
          indexboard = 0;
          boards.push_back(new BingoBoard(board, nbBoard));
          nbBoard++;
          board.clear();
        }
      }
      else
      {
        vector<int> line = split(str, " ");
        for (int elem: line)
        {
          board.push_back({elem, false});
          indexboard++;
        }
      }
    }
    lineCnt++;
  }

  // Part 1
  playBingo(boards, number);
  cout << "Part 1 : ";
  printWinner(boards);
  
  // Part 2
  int idx = playReverseBingo(boards, number);
  cout << "Part 2 : " << "["<<idx<<"] " << boards[idx]->getResultat() << endl;

  return 0;
}