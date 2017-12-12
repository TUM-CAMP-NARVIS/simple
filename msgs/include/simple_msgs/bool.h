#pragma once

#include <ostream>
#include "generic_message.h"
#include "generated/bool_generated.h"

namespace simple_msgs
{
class Bool : public GenericMessage
{
public:
  Bool();
  Bool(bool);
  Bool(const uint8_t*);
  Bool(const Bool&);
  Bool(Bool&&);

  Bool& operator=(const Bool&);
  Bool& operator=(Bool&&);

  inline bool operator==(const Bool&) const;
  inline bool operator!=(const Bool&) const;

  friend std::ostream& operator<<(std::ostream& out, const Bool& b);

  /**
   * @brief Builds and returns the buffer accordingly to the values currently stored.
   * @return the buffer data.
   */
  uint8_t* getBufferData() const;

  /**
   * @brief Set the boolean value.
   */
  inline void set(bool data);

  /**
   * @brief Get the boolean value.
   */
  inline bool get() const { return data_; }
  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static inline const char* getTopic() { return BoolFbsIdentifier(); }

private:
  bool data_{false};
};
}  // Namespace simple_msgs.
