// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_DOUBLE_SIMPLE_H_
#define FLATBUFFERS_GENERATED_DOUBLE_SIMPLE_H_

#include "flatbuffers/flatbuffers.h"

namespace simple {

struct DoubleFbs;

struct DoubleFbs FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_DATA = 4
  };
  double data() const {
    return GetField<double>(VT_DATA, 0.0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<double>(verifier, VT_DATA) &&
           verifier.EndTable();
  }
};

struct DoubleFbsBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_data(double data) {
    fbb_.AddElement<double>(DoubleFbs::VT_DATA, data, 0.0);
  }
  explicit DoubleFbsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  DoubleFbsBuilder &operator=(const DoubleFbsBuilder &);
  flatbuffers::Offset<DoubleFbs> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<DoubleFbs>(end);
    return o;
  }
};

inline flatbuffers::Offset<DoubleFbs> CreateDoubleFbs(
    flatbuffers::FlatBufferBuilder &_fbb,
    double data = 0.0) {
  DoubleFbsBuilder builder_(_fbb);
  builder_.add_data(data);
  return builder_.Finish();
}

inline const simple::DoubleFbs *GetDoubleFbs(const void *buf) {
  return flatbuffers::GetRoot<simple::DoubleFbs>(buf);
}

inline const char *DoubleFbsIdentifier() {
  return "DOBL";
}

inline bool DoubleFbsBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, DoubleFbsIdentifier());
}

inline bool VerifyDoubleFbsBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<simple::DoubleFbs>(DoubleFbsIdentifier());
}

inline void FinishDoubleFbsBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<simple::DoubleFbs> root) {
  fbb.Finish(root, DoubleFbsIdentifier());
}

}  // namespace simple

#endif  // FLATBUFFERS_GENERATED_DOUBLE_SIMPLE_H_
