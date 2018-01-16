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
  void setHeader(const Header&);
  /**
   * @brief Modifies the message point.
   */
  void setPoint(const Point&);
  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static const char* getTopic() { return PointStampedFbsIdentifier(); }
private:
  Point point_;
  Header header_;
};
}  // Namespace simple_msgs.
