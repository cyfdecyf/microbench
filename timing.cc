// Timing operation performance.

#include <stdint.h>
#include <sys/time.h>

#include <benchmark/benchmark_api.h>

static void BM_gettimeofday(benchmark::State& state) {
  struct timeval tv;
  while (state.KeepRunning()) {
    gettimeofday(&tv, nullptr);
  }
}
BENCHMARK(BM_gettimeofday);

static inline __attribute__((always_inline)) uint64_t rdtsc(void) {
    uint32_t a, d;
    __asm __volatile("rdtsc":"=a"(a), "=d"(d));
    return ((uint64_t)a) | (((uint64_t)d) << 32);
}

static void BM_rdtsc(benchmark::State& state) {
  while (state.KeepRunning()) {
    rdtsc();
  }
}
BENCHMARK(BM_rdtsc);

BENCHMARK_MAIN();
