
CXX = g++
CXXFLAGS = -std=c++20 -O3 -march=native -Wall -Wextra -Iinclude
AVXFLAGS = -mavx2 -mfma
AVX512FLAGS = -mavx512f -mavx512dq

# Directories
SRCDIR = examples
BUILDDIR = build
TESTDIR = tests

# Find all .cxx files in examples
AVX2_SOURCES = $(wildcard $(SRCDIR)/avx2/*.cxx)
AVX512_SOURCES = $(wildcard $(SRCDIR)/avx512/*.cxx)
STAT_SOURCES = $(wildcard $(SRCDIR)/stat-simd-impl/*.cxx)
BENCH_SOURCES = $(wildcard $(SRCDIR)/benchmark/*.cxx)

# Generate executable names
AVX2_TARGETS = $(AVX2_SOURCES:$(SRCDIR)/%.cxx=$(BUILDDIR)/%)
AVX512_TARGETS = $(AVX512_SOURCES:$(SRCDIR)/%.cxx=$(BUILDDIR)/%)
STAT_TARGETS = $(STAT_SOURCES:$(SRCDIR)/%.cxx=$(BUILDDIR)/%)
BENCH_TARGETS = $(BENCH_SOURCES:$(SRCDIR)/%.cxx=$(BUILDDIR)/%)

.PHONY: all clean test examples avx2 avx512 stat benchmark

all: examples test

examples: avx2 avx512 stat benchmark

avx2: $(AVX2_TARGETS)

avx512: $(AVX512_TARGETS)

stat: $(STAT_TARGETS)

benchmark: $(BENCH_TARGETS)

# Build AVX2 examples
$(BUILDDIR)/avx2/%: $(SRCDIR)/avx2/%.cxx
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(AVXFLAGS) $< -o $@

# Build AVX-512 examples
$(BUILDDIR)/avx512/%: $(SRCDIR)/avx512/%.cxx
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(AVX512FLAGS) $< -o $@

# Build statistical examples
$(BUILDDIR)/stat-simd-impl/%: $(SRCDIR)/stat-simd-impl/%.cxx
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(AVXFLAGS) $< -o $@

# Build benchmark examples
$(BUILDDIR)/benchmark/%: $(SRCDIR)/benchmark/%.cxx
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(AVX512FLAGS) $< -o $@

# Build tests
test:
	$(MAKE) -C $(TESTDIR)

clean:
	rm -rf $(BUILDDIR)
	$(MAKE) -C $(TESTDIR) clean

install:
	@echo "This is a header-only library. Copy the include/avxhole directory to your project."

help:
	@echo "Available targets:"
	@echo "  all       - Build examples and tests"
	@echo "  examples  - Build all examples"
	@echo "  avx2      - Build AVX2 examples"
	@echo "  avx512    - Build AVX-512 examples"
	@echo "  stat      - Build statistical examples"
	@echo "  benchmark - Build benchmark examples"
	@echo "  test      - Build and run tests"
	@echo "  clean     - Clean build files"
	@echo "  install   - Show installation instructions"
