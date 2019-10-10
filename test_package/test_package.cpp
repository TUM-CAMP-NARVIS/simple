/**
 * S.I.M.P.L.E. - Smart Intuitive Messaging Platform with Less Effort
 * Copyright (C) 2018 Salvatore Virga - salvo.virga@tum.de, Fernanda Levy Langsch - fernanda.langsch@tum.de
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <thread>

#include "simple/publisher.hpp"
#include "simple_msgs/pose_stamped.hpp"

int main()
{
  int sequence_num = 1;

  simple_msgs::Header my_header(sequence_num, "root", 0);  //< Build a Header.
  simple_msgs::Point my_point(1.0, 2.0, 3.0);              //< Build a Point.
  simple_msgs::Quaternion my_quaternion;                   //< Identity Quaternion.

  simple_msgs::PoseStamped my_pose_stamped(my_header, simple_msgs::Pose(my_point, my_quaternion));
  simple::Publisher<simple_msgs::PoseStamped> publisher("tcp://*:5555");

  return 0;
}
