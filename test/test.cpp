#include <conio.h>
#include <matplotlibcpp.h>
#include <speak.h>
#include <urg.h>

#include <Eigen/Core>
#include <vector>

namespace plt = matplotlibcpp;

void PlotScan(std::vector<float> x, std::vector<float> y) {
  plt::clf();
  plt::scatter(x, y);
  plt::xlim(-1000, 4000);
  plt::ylim(-1000, 4000);
  plt::set_aspect_equal();
  plt::title("Laser Scan");
  plt::pause(0.01);
}

int main() {
  BOOL retval = SetupURG();
  if (retval == FALSE) {
    return 0;
  }

  while (TRUE) {
    if (_kbhit()) {
      if (getch() == 'q') break;
    }
    auto [x, y] = GetScan();
    PlotScan(x, y);
  }

  StopURG();

  /*
  Eigen::ArrayXf x(10);
  x = 1;
  Eigen::ArrayXf y(10);
  y = 1;
  Eigen::MatrixXf m(2, 10);
  m.row(0) = x;
  m.row(1) = y;
  Eigen::Matrix2f R;
  float theta = 3.14;
  R << cos(theta), -sin(theta), sin(theta), cos(theta);
  std::cout << R * m << std::endl;
  */
}