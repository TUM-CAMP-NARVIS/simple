/**
 * S.I.M.P.L.E. - Smart Intuitive Messaging Platform with Less Effort
 * Copyright (C) 2018 Salvatore Virga - salvo.virga@tum.de, Fernanda Levy
 * Langsch - fernanda.langsch@tum.de
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SIMPLE_MSGS_POSE_H
#define SIMPLE_MSGS_POSE_H

#include <iostream>

#include "generated/pose_generated.h"
#include "point.h"
#include "quaternion.h"

namespace simple_msgs {
class Pose : public GenericMessage {
public:
  Pose() = default;
  Pose(const Point&, const Quaternion&);
  Pose(Point&&, Quaternion&&);
  Pose(const void*);
  Pose(const Pose&);
  Pose(Pose&&) noexcept;

  Pose& operator=(const Pose&);
  Pose& operator=(Pose&&) noexcept;
  Pose& operator=(std::shared_ptr<void*>);

  inline bool operator==(const Pose& rhs) const {
    return (position_ == rhs.position_ && quaternion_ == rhs.quaternion_);
  }
  inline bool operator!=(const Pose& rhs) const { return !(*this == rhs); }
  friend std::ostream& operator<<(std::ostream&, const Pose&);

  /**
   * @brief Builds and returns the buffer accordingly to the values currently stored.
   * @return the buffer data.
   */
  std::shared_ptr<flatbuffers::DetachedBuffer> getBufferData() const override;

  /**
   * @brief Returns the translational part of the Pose as a Point message.
   */
  inline Point& getPosition() { return position_; }
  inline const Point& getPosition() const { return position_; }

  /**
   * @brief Returns the rotational part of the Pose as a Quaternion message.
   */
  inline Quaternion& getQuaternion() { return quaternion_; }
  inline const Quaternion& getQuaternion() const { return quaternion_; }

  /**
   * @brief Modifies the rotational part of the Pose.
   */
  void setPosition(const Point&);

  /**
   * @brief Modifies the translational part of the Pose.
   */
  void setQuaternion(const Quaternion&);

  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static inline std::string getTopic() { return PoseFbsIdentifier(); }

private:
  Point position_{};
  Quaternion quaternion_{};
};
}  // Namespace simple_msgs.

#endif  // SIMPLE_MSGS_POSE_H
