/**
* S.I.M.P.L.E. - Smart Intra-operative Messaging Platform with Less Effort
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

#pragma once

#include <array>
#include <ostream>
#include "point.h"
#include "header.h"
#include "generic_message.h"
#include "generated/point_stamped_generated.h"

namespace simple_msgs
{
/**
 * @brief Point: wrapper class around the PointFbs generated code from flatbuffers.
 */
class PointStamped : public GenericMessage
{
public:
  PointStamped();
  PointStamped(const Header&, const Point&);
  PointStamped(const uint8_t*);
  PointStamped(const PointStamped&);
  PointStamped(PointStamped&&);

  PointStamped& operator=(const PointStamped&);
  PointStamped& operator=(PointStamped&&);
  PointStamped& operator=(const uint8_t*);

  inline bool operator==(const PointStamped& rhs) const { return (point_ == rhs.point_ && header_ == rhs.header_); }
  inline bool operator!=(const PointStamped& rhs) const { return !(*this == rhs); }
  friend std::ostream& operator<<(std::ostream&, const PointStamped&);

  /**
   * @brief Builds and returns the buffer accordingly to the values currently stored.
   * @return the buffer data.
   */
  uint8_t* getBufferData() const override;

  /**
   * @brief Returns the point as an array of 3 elements.
   */
  inline Point& getPoint() { return point_; }
  inline const Point& getPoint() const { return point_; }
  /**
   * @brief Returns message Header.
   */
  inline Header& getHeader() { return header_; }
  inline const Header& getHeader() const { return header_; }
  /**
   * @brief Modifies the message header.
   */
  inline void setHeader(const Header&);
  /**
   * @brief Modifies the message point.
   */
  inline void setPoint(const Point&);
  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static const char* getTopic() { return PointStampedFbsIdentifier(); }
private:
  Point point_;
  Header header_;
};
}  // Namespace simple_msgs.
