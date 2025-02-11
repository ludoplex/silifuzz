// Copyright 2022 The SiliFuzz Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef THIRD_PARTY_SILIFUZZ_PLAYER_TRACE_OPTIONS_H_
#define THIRD_PARTY_SILIFUZZ_PLAYER_TRACE_OPTIONS_H_

#include "./player/play_options.h"

namespace silifuzz {

// Common options for tracing a snapshot.
//
// This class is a thread-compatible value type.
class TraceOptions {
 public:
  TraceOptions() {}
  ~TraceOptions() = default;

  // Intentionally movable and copyable.

  // Default values.
  static const TraceOptions& Default();

  PlayOptions play_options = PlayOptions::Default();

  // Maximum number of instructions the snapshot is allowed to execute
  // before the tracer stops it. 0 for unlimited.
  int instruction_count_limit = 1000;

  // If true, tracer injects a signal when a locking instruction accesses
  // memory across a cache line boundary. This has no effect on non-x86
  // platforms.  This option is used to work around a performance issue on
  // some x86 CPUs. See https://lwn.net/Articles/790464/ for details.
  bool x86_filter_split_lock = true;

  // If true, tracer injects a signal when a non-deterministic instruction is
  // detected in the trace.
  bool filter_non_deterministic_insn = true;

  // If true, tracer injects a signal when a instruction accesses memory in
  // vsyscall memory region of Linux. This has no effect on non-x86 platforms.
  // Contents of the region depends on kernel version and may not be
  // present at all if vsyscall is not configured in the kernel.
  bool x86_filter_vsyscall_region_access = true;
};

}  // namespace silifuzz

#endif  // THIRD_PARTY_SILIFUZZ_PLAYER_TRACE_OPTIONS_H_
