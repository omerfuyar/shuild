# Shuild Performance Improvements - Quick Reference

## Overview

This is a quick reference guide for the performance improvements planned for the Shuild build library. For detailed analysis, see `PERFORMANCE_IMPROVEMENTS.md`. For implementation details, see `IMPLEMENTATION_GUIDE.md`.

---

## Performance Comparison

### Current State
```
100 source files, clean build:     60 seconds
100 source files, 1 file changed:  60 seconds (no optimization)
```

### After Phase 1 (Incremental + Multithreading)
```
100 source files, clean build:     8.5 seconds   (7x faster)
100 source files, 1 file changed:  1.2 seconds   (50x faster)
```

### After Phase 2 (+ Dependencies + Cache)
```
100 source files, clean build:     8.5 seconds   (first time)
100 source files, clean + cache:   0.5 seconds   (120x faster)
100 source files, header change:   2.8 seconds   (21x faster)
```

---

## Feature Summary

### Phase 1: Foundation (Immediate Value)
- **Incremental Builds**: Only recompile changed files
- **Multithreading**: Compile files in parallel
- **Expected Gain**: 3-10x faster builds

### Phase 2: Advanced (High Value)
- **Dependency Tracking**: Detect header file changes
- **Build Cache**: Reuse compiled objects across clean builds
- **Expected Gain**: Additional 2-5x improvement

### Phase 3: Polish (Nice to Have)
- **Compilation Database**: IDE integration support
- **Precompiled Headers**: Faster parsing of common headers
- **Expected Gain**: 1.2-1.5x improvement

### Phase 4: Future
- **Distributed Builds**: Compile across multiple machines
- **Expected Gain**: 5-20x with infrastructure

---

## API Additions

### Incremental Builds
```c
void SHU_ModuleSetIncremental(char enabled);  // Enable/disable (default: enabled)
void SHU_ModuleForceClean(void);              // Force clean build
```

### Multithreading
```c
void SHU_CompilerSetThreads(size_t count);    // Set thread count (0 = auto)
size_t SHU_CompilerGetOptimalThreadCount(void); // Get recommended count
```

### Dependency Tracking (Phase 2)
```c
void SHU_ModuleSetDependencyTracking(char enabled);
void SHU_ModuleRegenerateDependencies(void);
```

### Build Cache (Phase 2)
```c
void SHU_ModuleSetCache(char enabled);
void SHU_ModuleClearCache(void);
void SHU_ModuleSetCacheSize(size_t maxSizeMB);
void SHU_ModuleGetCacheStats(size_t *hits, size_t *misses, size_t *sizeMB);
```

### Compilation Database (Phase 3)
```c
void SHU_ModuleGenerateCompilationDatabase(void);
```

### Precompiled Headers (Phase 3)
```c
void SHU_ModuleAddPrecompiledHeader(const char *headerPath);
```

---

## Configuration Macros

### Disable Features
```c
#define SHUC_NO_INCREMENTAL_BUILD    // Disable incremental builds
#define SHUC_NO_MULTITHREADING       // Disable parallel compilation
#define SHUC_NO_DEPENDENCY_TRACKING  // Disable header tracking
#define SHUC_NO_BUILD_CACHE          // Disable build cache
```

### Configure Limits
```c
#define SHUC_MAX_THREADS 8           // Maximum thread count
#define SHUC_MAX_CACHE_SIZE_MB 2048  // Cache size limit (MB)
```

### Enable Debugging
```c
#define SHUC_PERFORMANCE_LOG         // Show performance metrics
```

---

## Usage Examples

### Basic Usage (No Changes Required)
```c
#define SHUILD_IMPLEMENTATION
#include "shuild.h"

int main() {
    SHU_CompilerConfigure(SHUM_COMPILER_GCC, "gcc");
    
    SHU_ModuleBegin("myapp");
    SHU_ModuleAddSourceDirectory("src/");
    SHU_ModuleCompile("build/", SHUM_MODULE_EXECUTABLE);
    
    return 0;
}
// Works exactly as before, but faster with incremental builds
```

### Enable Multithreading
```c
#define SHUILD_IMPLEMENTATION
#include "shuild.h"

int main() {
    SHU_CompilerConfigure(SHUM_COMPILER_GCC, "gcc");
    SHU_CompilerSetThreads(0); // Auto-detect optimal count
    
    SHU_ModuleBegin("myapp");
    SHU_ModuleAddSourceDirectory("src/");
    SHU_ModuleCompile("build/", SHUM_MODULE_EXECUTABLE);
    
    return 0;
}
// Now uses multiple CPU cores for compilation
```

### Maximum Performance
```c
#define SHUC_NO_MODULE_LOG  // Reduce logging overhead
#define SHUILD_IMPLEMENTATION
#include "shuild.h"

int main() {
    SHU_CompilerConfigure(SHUM_COMPILER_GCC, "gcc");
    SHU_CompilerSetThreads(8);              // Use 8 threads
    SHU_ModuleSetIncremental(1);            // Incremental builds
    SHU_ModuleSetDependencyTracking(1);     // Track headers (Phase 2)
    SHU_ModuleSetCache(1);                  // Enable cache (Phase 2)
    
    SHU_ModuleBegin("myapp");
    SHU_ModuleAddSourceDirectory("src/");
    SHU_ModuleCompile("build/", SHUM_MODULE_EXECUTABLE);
    
    return 0;
}
// Maximum performance configuration
```

### Force Clean Build
```c
#define SHUILD_IMPLEMENTATION
#include "shuild.h"

int main(int argc, char **argv) {
    SHU_CompilerConfigure(SHUM_COMPILER_GCC, "gcc");
    
    // Check for --clean flag
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--clean") == 0) {
            SHU_ModuleForceClean();
            break;
        }
    }
    
    SHU_ModuleBegin("myapp");
    SHU_ModuleAddSourceDirectory("src/");
    SHU_ModuleCompile("build/", SHUM_MODULE_EXECUTABLE);
    
    return 0;
}
// Usage: ./shuild --clean
```

---

## File Structure After Implementation

```
shuild.h                          (1,729 lines → ~2,629 lines)
├── Platform Detection            (unchanged)
├── Compiler Detection            (unchanged)
├── Declarations                  (add new APIs)
├── Implementation
│   ├── Internals
│   │   ├── String/StringList     (unchanged)
│   │   ├── NEW: Cache System     (+200 lines)
│   │   ├── NEW: Threading        (+200 lines)
│   │   ├── NEW: Dependency       (+200 lines)
│   │   └── File Operations       (unchanged)
│   ├── General                   (unchanged)
│   ├── Compiler                  (minor changes)
│   └── Module                    (major changes)

.shuild_cache                     (NEW: generated file)
├── Format: text-based
├── Content: timestamps, dependencies, hashes
└── Size: ~1-10 KB per module

compile_commands.json             (NEW: optional, Phase 3)
├── Standard format for IDEs
└── Size: ~100 bytes per source file
```

---

## Migration Checklist

### For Library Users (Projects Using Shuild)

- [x] **No action required** - All changes are backward compatible
- [ ] Optional: Add `SHU_CompilerSetThreads(0)` for parallel builds
- [ ] Optional: Measure build time improvements
- [ ] Optional: Enable additional features in Phase 2+

### For Library Maintainers

- [ ] Review `PERFORMANCE_IMPROVEMENTS.md` for detailed analysis
- [ ] Review `IMPLEMENTATION_GUIDE.md` for code patterns
- [ ] Create development branch for Phase 1
- [ ] Implement incremental build system
- [ ] Implement multithreading support
- [ ] Test with existing examples
- [ ] Benchmark performance gains
- [ ] Document results
- [ ] Merge to main branch
- [ ] Plan Phase 2 implementation

---

## Testing Strategy

### Unit Tests
```c
test_incremental_single_file()    // Change one file, verify skip others
test_incremental_compiler_change() // Change flags, verify full rebuild
test_multithread_correctness()    // Verify output identical to single-thread
test_multithread_performance()    // Verify speedup with multiple files
```

### Integration Tests
```c
test_all_examples()               // All examples still work
test_static_library()             // Library builds work
test_dynamic_library()            // Dynamic library builds work
test_executable()                 // Executable builds work
```

### Performance Tests
```c
benchmark_clean_build()           // Measure clean build time
benchmark_incremental()           // Measure incremental build time
benchmark_cache_hit()             // Measure cached build time
benchmark_thread_scaling()        // Measure 1,2,4,8 thread performance
```

---

## Key Metrics to Track

### Build Performance
- **Clean build time**: Time to build from scratch
- **Incremental build time**: Time to rebuild after 1 file change
- **Cache hit rate**: % of files reused from cache
- **Thread efficiency**: Speedup vs. single-threaded

### Code Quality
- **Lines of code**: Total implementation size
- **Complexity**: Cyclomatic complexity of new code
- **Test coverage**: % of new code covered by tests
- **Memory usage**: Peak memory during build

### User Experience
- **API simplicity**: Lines of code in user build scripts
- **Documentation quality**: Completeness of docs
- **Error messages**: Clarity of failure messages
- **Compatibility**: % of projects that work unchanged

---

## Common Issues and Solutions

### Issue: Cache file corruption
**Symptoms**: Build fails with cache-related errors
**Solution**: Delete `.shuild_cache` and rebuild
**Prevention**: Implement atomic writes and checksums

### Issue: Incremental build misses changes
**Symptoms**: Code changes not reflected in binary
**Solution**: Run with `SHU_ModuleForceClean()`
**Prevention**: Improve dependency tracking (Phase 2)

### Issue: Multithreading overhead
**Symptoms**: Slower with few files
**Solution**: Automatically disable for <5 files
**Prevention**: Implement threshold-based activation

### Issue: Thread count too high
**Symptoms**: System becomes unresponsive
**Solution**: Reduce thread count with `SHU_CompilerSetThreads()`
**Prevention**: Default to cores-1, document tuning

---

## Performance Optimization Tips

### For Build Script Authors

1. **Enable multithreading**: `SHU_CompilerSetThreads(0)`
2. **Use incremental builds**: Enabled by default
3. **Structure code**: Group related files in directories
4. **Minimize header dependencies**: Include only what's needed
5. **Use precompiled headers**: For large common headers (Phase 3)

### For Large Projects

1. **Split into modules**: Separate libraries and executables
2. **Enable build cache**: `SHU_ModuleSetCache(1)` (Phase 2)
3. **Use distributed builds**: Consider Phase 4 features
4. **Profile builds**: Use `SHUC_PERFORMANCE_LOG` to identify bottlenecks
5. **Tune thread count**: Test different values for your hardware

### For CI/CD Systems

1. **Persist cache**: Save `.shuild_cache` between runs
2. **Use fixed thread count**: Set explicit value for consistency
3. **Clean builds occasionally**: Run with `--clean` weekly
4. **Monitor cache size**: Set `SHUC_MAX_CACHE_SIZE_MB` limit
5. **Parallelize jobs**: Run multiple build scripts simultaneously

---

## Resources

### Documentation
- `PERFORMANCE_IMPROVEMENTS.md`: Detailed analysis and recommendations
- `IMPLEMENTATION_GUIDE.md`: Code patterns and implementation details
- `README.md`: General library usage
- `examples/`: Working examples with new features

### Community
- GitHub Issues: Report bugs and request features
- GitHub Discussions: Ask questions and share tips
- Pull Requests: Contribute improvements

### Benchmarking
```bash
# Time a build
time ./shuild

# Profile with perf (Linux)
perf record -g ./shuild
perf report

# Profile with Instruments (macOS)
instruments -t "Time Profiler" ./shuild
```

---

## FAQ

**Q: Will this break my existing build scripts?**
A: No. All changes are backward compatible. Your code will work unchanged.

**Q: Do I need to enable these features?**
A: Incremental builds are enabled by default. Multithreading requires one line: `SHU_CompilerSetThreads(0)`.

**Q: How much faster will my builds be?**
A: Depends on project size. Expect 3-10x for clean builds, 50-100x for incremental builds.

**Q: Does this increase the library size?**
A: Yes, from 1,729 lines to ~2,629 lines (~52% increase), but still a single header.

**Q: Can I disable features I don't want?**
A: Yes, using compile-time macros like `SHUC_NO_MULTITHREADING`.

**Q: When will this be available?**
A: Phase 1 (incremental + multithreading) is planned for implementation. See roadmap.

**Q: Will this work on my platform?**
A: Yes. Supports Windows, Linux, and macOS like the current version.

**Q: How stable is this?**
A: This is a planning document. Implementation will include thorough testing before release.

---

## Next Steps

1. **Review**: Read the detailed documents
2. **Feedback**: Provide comments on the design
3. **Testing**: Try it when available
4. **Contribute**: Help with implementation or testing

---

**Document Version:** 1.0  
**Date:** 2026-01-10  
**Status:** Planning Phase - Implementation Pending
