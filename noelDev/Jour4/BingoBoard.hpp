#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;

typedef vector<pair<int, bool>> BoardMap;

class BingoBoard
{
public:
  BingoBoard(BoardMap b, int index) : isWinner(false), lastNumDraw(0), board(b), boardNum(index) {};

  bool drawNumber(int num);
  bool didIWin();
  void print();
  int getResultat();
  bool isBingo() { return isWinner; };

private:
  bool checkLine(const BoardMap& cboard);
  bool checkDiag(const BoardMap& cboard);
  bool checkCol(const BoardMap& cboard);

  BoardMap board;
  bool isWinner;
  int lastNumDraw;
  int boardNum;
};

int BingoBoard::getResultat()
{
  int sum = 0;
  for (auto it = board.begin(); it != board.end(); it++)
    if (it->second == false)
      sum += it->first;
  return sum * lastNumDraw;
}

bool BingoBoard::drawNumber(int num)
{
  for (auto it = board.begin(); it != board.end(); it++)
  {
    if (it->first == num)
    {
      it->second = true;
      lastNumDraw = num;
    }
  }
  return didIWin();
}

bool BingoBoard::didIWin()
{
  if (checkLine(board) ||
      checkDiag(board) ||
      checkCol(board))
  {
    isWinner = true;
  }
  return isWinner;
}



void BingoBoard::print()
{
  int tmp = 1;
  cout << "Board["<<boardNum<<"]: " << endl;
  for (auto it = board.begin(); it != board.end(); it++)
  {
    cout << ((it->first < 10) ? " " : "") << it->first << "["<< ((it->second) ? 'X' : ' ') <<"] ";
    if (tmp == 5)
    {
      tmp = 0;
      cout << endl;
    }
    tmp++;
  }
  cout << endl;
}

bool BingoBoard::checkLine(const BoardMap& cboard)
{
  int basesLine[5] = {0, 5, 10, 15, 20};
  int ctr = 0;
  BoardMap::const_iterator it;
  for(int base: basesLine)
  {
    it = next(cboard.begin(), base);
    while(it->second)
    {
      it++;
      ctr++;
    }
    if (ctr >= 5)
      return true;
    ctr = 0;
  }
  return false;
}

bool BingoBoard::checkDiag(const BoardMap& cboard)
{ // Diag dont count
  return false;

  int basesDiag[2] = {0, 4};
  int ctr = 1;
  BoardMap::const_iterator it;
  bool flag = false;
  for(int base: basesDiag)
  {
    it = next(cboard.begin(), base);
    while(it->second)
    {
      if (ctr == 6)
        break;
      base = (flag) ? 4 : 6;
      it = next(it, base);
      ctr++;
    }
    if (ctr >= 6)
      return true;
    ctr = 1;
    flag = true;
  }
  return false;
}

bool BingoBoard::checkCol(const BoardMap& cboard)
{
  int basesCol[5] = {0, 1, 2, 3, 4};
  int ctr = 0;
  BoardMap::const_iterator it;
  for(int base: basesCol)
  {
    it = next(cboard.begin(), base);
    while(it->second)
    {
      it = next(it, 5);
      ctr++;
    }
    if (ctr >= 5)
      return true;
    ctr = 0;
  }
  return false;
}