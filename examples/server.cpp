#include <iostream>
#include <string>

#include "simple/server.hpp"
#include "simple_msgs/pose.h"

void example_callback(simple_msgs::Pose& p)
{
  std::cout << "Received a point. Adding 1 to its elements." << std::endl;
  p.getPosition() += 1.0;
}

int main()
{
  const int SLEEP_TIME = 60000;  //< Milliseconds.

  std::cout << "Creating a server." << std::endl;
  simple::Server<simple_msgs::Pose> server("tcp://*:5555", example_callback);

  // wait for 25 seconds
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));

  std::cout << "Leaving main scope" << std::endl;
}
