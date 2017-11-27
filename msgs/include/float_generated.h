// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_FLOAT_SIMPLE_H_
#define FLATBUFFERS_GENERATED_FLOAT_SIMPLE_H_

#include "flatbuffers/flatbuffers.h"

namespace simple {

struct FloatFbs;

struct FloatFbs FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_DATA = 4
  };
  float data() const {
    return GetField<float>(VT_DATA, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_DATA) &&
           verifier.EndTable();
  }
};

struct FloatFbsBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_data(float data) {
    fbb_.AddElement<float>(FloatFbs::VT_DATA, data, 0.0f);
  }
  explicit FloatFbsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  FloatFbsBuilder &operator=(const FloatFbsBuilder &);
  flatbuffers::Offset<FloatFbs> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FloatFbs>(end);
    return o;
  }
};

inline flatbuffers::Offset<FloatFbs> CreateFloatFbs(
    flatbuffers::FlatBufferBuilder &_fbb,
    float data = 0.0f) {
  FloatFbsBuilder builder_(_fbb);
  builder_.add_data(data);
  return builder_.Finish();
}

inline const simple::FloatFbs *GetFloatFbs(const void *buf) {
  return flatbuffers::GetRoot<simple::FloatFbs>(buf);
}

inline const char *FloatFbsIdentifier() {
  return "FLOT";
}

inline bool FloatFbsBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, FloatFbsIdentifier());
}

inline bool VerifyFloatFbsBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<simple::FloatFbs>(FloatFbsIdentifier());
}

inline void FinishFloatFbsBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<simple::FloatFbs> root) {
  fbb.Finish(root, FloatFbsIdentifier());
}

}  // namespace simple

#endif  // FLATBUFFERS_GENERATED_FLOAT_SIMPLE_H_
