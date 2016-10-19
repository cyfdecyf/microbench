// Copy using for loop for different size vs memmove.

#include <stdint.h>
#include <string.h>
#include <benchmark/benchmark_api.h>

static unsigned char data[8192];

template<typename T>
static void copy_loop(benchmark::State& state) {
  while (state.KeepRunning()) {
    for (T* p = (T*)(data + 8); (void*)p < (void*)(data + sizeof(data)); p++) {
      *p = *(p - sizeof(*p));
    }
  }
}

static void BM_copy_loop_1(benchmark::State& state) {
  copy_loop<uint8_t>(state);
}
BENCHMARK(BM_copy_loop_1);

static void BM_copy_loop_2(benchmark::State& state) {
  copy_loop<uint16_t>(state);
}
BENCHMARK(BM_copy_loop_2);

static void BM_copy_loop_4(benchmark::State& state) {
  copy_loop<uint32_t>(state);
}
BENCHMARK(BM_copy_loop_4);

static void BM_copy_loop_8(benchmark::State& state) {
  copy_loop<uint64_t>(state);
}
BENCHMARK(BM_copy_loop_8);

static void BM_memmove(benchmark::State& state) {
  while (state.KeepRunning()) {
    memmove(data + 8, data, sizeof(data) - 8);
  }
}
BENCHMARK(BM_memmove);

static void BM_memcpy_1GB(benchmark::State& state) {
  static const int k1GB = 512 * 1024 * 1024;

  void* p1 = operator new(k1GB);
  void* p2 = operator new(k1GB);

  // Touch all memory once so we don't include page fault time in benchmarking.
  memset(p1, 0, k1GB);
  memset(p2, 0, k1GB);
  while (state.KeepRunning()) {
    memcpy(p1, p2, k1GB);
  }
}
BENCHMARK(BM_memcpy_1GB);

BENCHMARK_MAIN();
