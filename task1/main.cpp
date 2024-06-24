#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) throw invalid_argument("Неверное количество аргументов");

  int n = stoi(argv[1]);
  if (n < 1) throw invalid_argument("Неверное значение n");

  int m = stoi(argv[2]);
  if (m <= 1 || m > n + 1) throw invalid_argument("Неверное значение m");

  int k = -1;
  int cur = 1;
  cout << cur;
  while (true) {
    k = cur + (m - 1);
    if (k > n) k -= n;

    if (k == 1) break;

    cur = k;
    cout << cur;
  }
  cout << endl;

  return 0;
}