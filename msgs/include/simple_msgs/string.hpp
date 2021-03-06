/**
 * S.I.M.P.L.E. - Smart Intuitive Messaging Platform with Less Effort
 * Copyright (C) 2018 Salvatore Virga - salvo.virga@tum.de, Fernanda Levy
 * Langsch - fernanda.langsch@tum.de
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef SIMPLE_MSGS_STRING_H
#define SIMPLE_MSGS_STRING_H

#include <mutex>
#include <ostream>

#include "generic_message.hpp"

namespace simple_msgs {
/**
 * @class String string.hpp.
 * @brief Thread-safe wrapper for a Flatbuffers String message, as defined in string.fbs.
 */
class String : public GenericMessage {
public:
  String() = default;

  /**
   * @brief Construct a String message using the given text.
   */
  String(const std::string& data);

  /**
   * @brief Construct a String message using the given text.
   */
  String(const char* data);

  /**
   * @brief Construct a String message using the given text.
   */
  String(std::string&& data);

  /**
   * @brief Copy constructor.
   */
  String(const String& other);

  /**
   * @brief Move constructor.
   */
  String(String&& other) noexcept;

  /**
   * @brief Copy assignment.
   */
  String& operator=(const String& rhs);

  /**
   * @brief Move assignment.
   */
  String& operator=(String&& rhs) noexcept;

  /**
   * @brief Returns true if lhs is equal to rhs, false otherwise.
   */
  inline bool operator==(const String& rhs) const {
    std::lock_guard<std::mutex> lock{mutex_};
    return (data_ == rhs.data_);
  }

  /**
   * @brief Returns true if lhs is not equal to rhs, false otherwise.
   */
  inline bool operator!=(const String& rhs) const { return !(*this == rhs); }

  /**
   * @brief Concatenate a String to the current one.
   */
  String& operator+=(const String&);

  /**
   * @brief Concatenates two Strings.
   */
  friend String operator+(String, const String&);

  /**
   * @brief Stream extraction.
   */
  friend std::ostream& operator<<(std::ostream& out, const String& s);

  /**
   * @brief Returns the string information contained in the message.
   */
  inline std::string get() const {
    std::lock_guard<std::mutex> lock{mutex_};
    return data_;
  }

  /**
   * @brief Modifies the string information contained in the message.
   */
  inline void set(const std::string& data) {
    std::lock_guard<std::mutex> lock{mutex_};
    data_ = data;
  }

  /**
   * @brief Set the message content to an empty string.
   */
  inline void clear() {
    std::lock_guard<std::mutex> lock{mutex_};
    data_.clear();
  }

  /**
   * @brief Returns true if the message is empty, false otherwise.
   */
  inline bool empty() {
    std::lock_guard<std::mutex> lock{mutex_};
    return data_.empty();
  }

  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static std::string getTopic();

protected:
  /**
   * @brief Construct a String message using a raw memory coming from network.
   */
  String(const void* data);

  /**
   * @brief Copy assignment operator that uses raw memory coming from the network.
   */
  String& operator=(std::shared_ptr<void*> rhs) override;

  /**
   * @brief Builds and returns the buffer accordingly to the values currently stored.
   */
  std::shared_ptr<flatbuffers::DetachedBuffer> getBufferData() const override;

private:
  //! Thread safe copy and move constructors.
  String(const String& other, const std::lock_guard<std::mutex>&);
  String(String&& other, const std::lock_guard<std::mutex>&) noexcept;

  mutable std::mutex mutex_{};
  std::string data_{""};
};
}  // Namespace simple_msgs.

#endif  // SIMPLE_MSGS_STRING_H
