#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Point {
  double x;
  double y;
};

int pointPosition(const Point& center, double radius, const Point& point) {
  double distance =
      sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2));

  int res = 2;

  if (distance < radius)
    res = 1;
  else if (distance == radius)
    res = 0;

  return res;
}

void validateCoordinate(double value) {
  if (value < 1e-38 || value > 1e38)
    throw out_of_range("Значение координат вне диапазона (от 1e-38 до 1e38)");
}

int main(int argc, char* argv[]) {
  if (argc != 3) throw invalid_argument("Неверное количество аргументов");

  ifstream circleFile(argv[1]);
  if (!circleFile)
    throw runtime_error("Невозможно открыть файл с информацией об окружности");

  Point center;
  double radius;
  circleFile >> center.x >> center.y >> radius;
  circleFile.close();

  validateCoordinate(center.x);
  validateCoordinate(center.y);
  validateCoordinate(radius);
  if (radius <= 0) throw invalid_argument("Радиус <= 0.");

  ifstream pointsFile(argv[2]);
  if (!pointsFile) throw runtime_error("Невозможно открыть файл с точками");

  vector<Point> points;
  Point point;
  while (pointsFile >> point.x >> point.y) {
    validateCoordinate(point.x);
    validateCoordinate(point.y);
    points.push_back(point);
  }

  pointsFile.close();

  if (points.size() < 1 || points.size() > 100)
    throw out_of_range("Количество точке от 1 до 100.");

  for (const auto& p : points) {
    int position = pointPosition(center, radius, p);
    cout << position << endl;
  }

  return 0;
}
