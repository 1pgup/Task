#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <unordered_map>

using json = nlohmann::json;
using namespace std;

json loadJson(const string& filename) {
  ifstream file(filename);
  if (!file) throw runtime_error("Невозможно открыть файл json");

  json j;
  file >> j;
  return j;
}

void updateValues(json& tests, const unordered_map<int, string>& valuesMap) {
  for (auto& test : tests) {
    if (test.contains("id") && valuesMap.find(test["id"]) != valuesMap.end())
      test["value"] = valuesMap.at(test["id"]);

    if (test.contains("values")) updateValues(test["values"], valuesMap);
  }
}

int main(int argc, char* argv[]) {
  if (argc != 4) throw invalid_argument("Неверное количество аргументов");

  json valuesJson = loadJson(argv[1]);
  json testsJson = loadJson(argv[2]);

  unordered_map<int, string> valuesMap;
  for (const auto& item : valuesJson["values"])
    valuesMap[item["id"]] = item["value"];

  updateValues(testsJson["tests"], valuesMap);

  ofstream report(argv[3]);
  report << setw(2) << testsJson << endl;

  return 0;
}
