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

#ifndef SIMPLE_MSGS_NUMERIC_TYPE_HPP
#define SIMPLE_MSGS_NUMERIC_TYPE_HPP

#include <algorithm>
#include <ostream>

#include "generic_message.h"

namespace simple_msgs {
template <typename T>
class NumericType : public GenericMessage {
public:
  // Constructors.

  NumericType() = default;

  NumericType(T data) : data_{data} {}

  /**
   * @brief Constructor from the buffer data, implementation is specific to the template specialization.
   */
  NumericType(const void* data);

  // Copy operations.

  NumericType(const NumericType& other) : NumericType{other.data_} {}

  NumericType& operator=(const NumericType& rhs) {
    std::lock_guard<std::mutex> lock{mutex_};
    data_ = rhs.data_;
    return *this;
  }

  NumericType& operator=(std::shared_ptr<void*> data);

  // Move operations.

  NumericType(NumericType&& other) noexcept : data_(std::move(other.data_)) {}

  NumericType& operator=(NumericType&& rhs) noexcept {
    std::lock_guard<std::mutex> lock{mutex_};
    data_ = std::move(rhs.data_);
    return *this;
  }

  // Relational operators.
  inline bool operator==(const NumericType& rhs) const { return data_ == rhs.data_; }
  inline bool operator!=(const NumericType& rhs) const { return !(*this == rhs); }
  inline bool operator<(const NumericType& rhs) const { return data_ < rhs.data_; }
  inline bool operator>(const NumericType& rhs) const { return rhs < *this; }
  inline bool operator<=(const NumericType& rhs) const { return !(*this > rhs); }
  inline bool operator>=(const NumericType& rhs) const { return !(*this < rhs); }
  // Increment and decrement operators.

  NumericType& operator--() {
    --data_;
    return *this;
  }

  const NumericType operator--(int) {
    const NumericType old(*this);
    --(*this);
    return old;
  }

  NumericType& operator++() {
    ++data_;
    return *this;
  }

  const NumericType operator++(int) {
    const NumericType old(*this);
    ++(*this);
    return old;
  }

  // Binary arithmetic operatorss

  NumericType& operator+=(const NumericType& rhs) {
    data_ += rhs.data_;
    return *this;
  }

  friend NumericType operator+(NumericType lhs, const NumericType& rhs) {
    lhs += rhs;
    return lhs;
  }

  NumericType& operator-=(const NumericType& rhs) {
    data_ -= rhs.data_;
    return *this;
  }

  friend NumericType operator-(NumericType lhs, const NumericType& rhs) {
    lhs -= rhs;
    return lhs;
  }

  NumericType& operator*=(const NumericType& rhs) {
    data_ *= rhs.data_;
    return *this;
  }

  friend NumericType operator*(NumericType lhs, const NumericType& rhs) {
    lhs *= rhs;
    return lhs;
  }

  NumericType& operator/=(const NumericType& rhs) {
    data_ /= rhs.data_;
    return *this;
  }

  friend NumericType operator/(NumericType lhs, const NumericType& rhs) {
    lhs /= rhs;
    return lhs;
  }

  /**
   * @brief Builds and returns the buffer accordingly to the values currently stored.
   * @return the buffer data.
   */
  std::shared_ptr<flatbuffers::DetachedBuffer> getBufferData() const override;

  /**
   * @brief Set the double value.
   */
  inline void set(T data) {
    std::lock_guard<std::mutex> lock{mutex_};
    data_ = data;
  }

  /**
   * @brief Get the double value.
   */
  inline T get() const { return data_; }

  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static inline std::string getTopic();

  //  Stream extraction.
  template <typename Tn>
  friend std::ostream& operator<<(std::ostream& out, const NumericType<Tn>& obj);

private:
  T data_{0};
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const NumericType<T>& obj) {
  out << obj.data_;
  return out;
}
}  // Namespace simple_msgs.

#endif  // SIMPLE_MSGS_NUMERIC_TYPE_HPP
