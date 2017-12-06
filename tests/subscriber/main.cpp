#include <signal.h>
#include <fstream>
#include <iostream>
#include <string>
#include "simple/subscriber.h"
#include "simple_msgs/generic_message.h"
#include "simple_msgs/header.h"
#include "simple_msgs/point.h"

// std::function<int(simple_msgs::Header)> callback = dummyFun;

void dummy(const simple_msgs::Point& p)
{
  std::cout << "Received point: " << std::endl;
  auto vec = p.toVector();
  std::cout << "X: " << vec.at(0) << std::endl;
  std::cout << "Y: " << vec.at(1) << std::endl;
  std::cout << "Z: " << vec.at(2) << std::endl;
}

int main(int argc, char* argv[])
{
  std::cout << "Creating subscriber for Point" << std::endl;
  simple::Subscriber<simple_msgs::Point> sub("tcp://localhost:5555", dummy);

  // wait for 5 seconds
  std::this_thread::sleep_for(std::chrono::seconds(5));

  std::cout << "Leaving main scope" << std::endl;
}
