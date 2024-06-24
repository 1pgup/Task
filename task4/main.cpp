#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) throw invalid_argument("Неверное количество аргументов");

  ifstream inputFile(argv[1]);
  if (!inputFile) throw runtime_error("Невозможно открыть файл с точками");

  vector<int> nums;
  int num;
  while (inputFile >> num) nums.push_back(num);

  inputFile.close();

  if (!nums.empty()) {
    sort(nums.begin(), nums.end());

    int median = nums[nums.size() / 2];

    int minMoves = 0;
    for (int n : nums) minMoves += abs(n - median);

    cout << minMoves << endl;
  } else
    cout << "0" << endl;

  return 0;
}
