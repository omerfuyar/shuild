# Shuild Performance Improvements - Implementation Guide

## Overview

This document provides detailed implementation guidance for the performance improvements outlined in `PERFORMANCE_IMPROVEMENTS.md`. It includes code patterns, data structures, algorithms, and best practices for each feature.

---

## 1. Incremental Build System Implementation

### 1.1 Data Structures

```c
// Add to SHUI internal state (line ~415)
struct {
    // ... existing fields ...
    
    struct {
        char enabled;
        char forceClean;
        char cacheFilePath[SHUC_MAX_PATH_SIZE];
        
        struct {
            SHUI_FileTimestamp *files;
            size_t count;
            size_t capacity;
            unsigned long flagsHash;
            char compilerCommand[SHUC_MAX_COMPILER_LENGTH];
        } cache;
    } INCREMENTAL;
} SHUI;

typedef struct SHUI_FileTimestamp {
    char sourcePath[SHUC_MAX_PATH_SIZE];
    char objectPath[SHUC_MAX_PATH_SIZE];
    time_t sourceModTime;
    time_t objectModTime;
    time_t lastCompiled;
} SHUI_FileTimestamp;
```

### 1.2 Cache File Operations

```c
/// @brief Load build cache from disk
static void SHUI_LoadBuildCache(const char *cacheDir) {
    char cachePath[SHUC_MAX_PATH_SIZE];
    snprintf(cachePath, sizeof(cachePath), "%s/.shuild_cache", cacheDir);
    
    FILE *f = fopen(cachePath, "r");
    if (!f) {
        // First build, no cache
        SHUI.INCREMENTAL.cache.count = 0;
        return;
    }
    
    char line[SHUC_MAX_PATH_SIZE * 2];
    
    // Read header
    fgets(line, sizeof(line), f); // Version
    fgets(line, sizeof(line), f); // Compiler
    sscanf(line, "compiler=%s", SHUI.INCREMENTAL.cache.compilerCommand);
    fgets(line, sizeof(line), f); // Flags hash
    sscanf(line, "flags_hash=%lu", &SHUI.INCREMENTAL.cache.flagsHash);
    
    // Read file entries
    while (fgets(line, sizeof(line), f)) {
        SHUI_FileTimestamp ts;
        char *token = strtok(line, ",");
        strncpy(ts.sourcePath, token, SHUC_MAX_PATH_SIZE - 1);
        
        token = strtok(NULL, ",");
        strncpy(ts.objectPath, token, SHUC_MAX_PATH_SIZE - 1);
        
        token = strtok(NULL, ",");
        ts.sourceModTime = (time_t)atoll(token);
        
        token = strtok(NULL, ",");
        ts.objectModTime = (time_t)atoll(token);
        
        token = strtok(NULL, ",\n");
        ts.lastCompiled = (time_t)atoll(token);
        
        // Add to cache
        SHUI_AddTimestampToCache(&ts);
    }
    
    fclose(f);
}

/// @brief Save build cache to disk
static void SHUI_SaveBuildCache(const char *cacheDir) {
    char cachePath[SHUC_MAX_PATH_SIZE];
    snprintf(cachePath, sizeof(cachePath), "%s/.shuild_cache", cacheDir);
    
    // Atomic write: write to temp file, then rename
    char tempPath[SHUC_MAX_PATH_SIZE];
    snprintf(tempPath, sizeof(tempPath), "%s/.shuild_cache.tmp", cacheDir);
    
    FILE *f = fopen(tempPath, "w");
    if (!f) {
        SHU_LogWarning("Failed to save build cache");
        return;
    }
    
    // Write header
    fprintf(f, "[SHUILD_CACHE_V1]\n");
    fprintf(f, "compiler=%s\n", SHUI.INCREMENTAL.cache.compilerCommand);
    fprintf(f, "flags_hash=%lu\n", SHUI.INCREMENTAL.cache.flagsHash);
    
    // Write file entries
    for (size_t i = 0; i < SHUI.INCREMENTAL.cache.count; i++) {
        SHUI_FileTimestamp *ts = &SHUI.INCREMENTAL.cache.files[i];
        fprintf(f, "%s,%s,%lld,%lld,%lld\n",
                ts->sourcePath,
                ts->objectPath,
                (long long)ts->sourceModTime,
                (long long)ts->objectModTime,
                (long long)ts->lastCompiled);
    }
    
    fclose(f);
    
    // Atomic rename
    remove(cachePath); // Remove old cache
    rename(tempPath, cachePath);
}
```

### 1.3 Change Detection

```c
/// @brief Check if file needs recompilation
static char SHUI_FileNeedsRecompile(const char *source, const char *object) {
    // Check if object exists
    if (SHU_FileExists(object) != SHUM_FILE_REGULAR) {
        return 1; // Object doesn't exist
    }
    
    // Get current source timestamp
    struct stat sourceStat, objectStat;
    if (stat(source, &sourceStat) != 0) {
        return 1; // Source doesn't exist (shouldn't happen)
    }
    if (stat(object, &objectStat) != 0) {
        return 1; // Object doesn't exist
    }
    
    // Compare timestamps
    if (sourceStat.st_mtime > objectStat.st_mtime) {
        return 1; // Source newer than object
    }
    
    // Check if compiler flags changed
    unsigned long currentFlagsHash = SHUI_HashCompilerFlags();
    if (currentFlagsHash != SHUI.INCREMENTAL.cache.flagsHash) {
        return 1; // Flags changed
    }
    
    // Check if compiler changed
    if (strcmp(SHUI.COMPILER.command.data, 
               SHUI.INCREMENTAL.cache.compilerCommand) != 0) {
        return 1; // Compiler changed
    }
    
    return 0; // No recompilation needed
}

/// @brief Hash compiler flags for change detection
static unsigned long SHUI_HashCompilerFlags(void) {
    unsigned long hash = 5381;
    
    for (size_t i = 0; i < SHUI.COMPILER.flags.count; i++) {
        const char *str = SHUI.COMPILER.flags.data[i].data;
        while (*str) {
            hash = ((hash << 5) + hash) + *str++;
        }
    }
    
    return hash;
}
```

### 1.4 Integration Points

**Modify `SHUI_CompileLibraryStatic()` at line ~901:**

```c
static void SHUI_CompileLibraryStatic(SHUI_String directory)
{
#ifndef SHUC_NO_INCREMENTAL_BUILD
    // Load cache
    if (SHUI.INCREMENTAL.enabled && !SHUI.INCREMENTAL.forceClean) {
        SHUI_LoadBuildCache(directory.data);
    }
#endif

    // Build command buffer for flags (existing code)
    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE] = {0};
    // ... existing flag preparation code ...

    // Compile source files
    size_t skippedFiles = 0;
    for (size_t i = 0; i < SHUI.MODULE.sourceFiles.count; i++)
    {
        char objPath[SHUC_MAX_PATH_SIZE];
        snprintf(objPath, sizeof(objPath), "%.*s%s",
                 (int)SHUI.MODULE.sourceFiles.data[i].length - 1,
                 SHUI.MODULE.sourceFiles.data[i].data,
                 SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? "obj" : "o");

#ifndef SHUC_NO_INCREMENTAL_BUILD
        // Check if recompilation needed
        if (SHUI.INCREMENTAL.enabled && 
            !SHUI_FileNeedsRecompile(SHUI.MODULE.sourceFiles.data[i].data, objPath)) {
#ifndef SHUC_NO_RUN_LOG
            SHU_LogInfo("Skipping unchanged: %s", 
                       SHUI.MODULE.sourceFiles.data[i].data);
#endif
            skippedFiles++;
            continue;
        }
#endif

        // Existing compilation code
        SHU_Run("%s %s %s %s %.*s%s %s",
                SHUI.COMPILER.command.data,
                SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/c" : "-c",
                SHUI.MODULE.sourceFiles.data[i].data,
                SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/Fo:" : "-o",
                SHUI.MODULE.sourceFiles.data[i].length - 1,
                SHUI.MODULE.sourceFiles.data[i].data,
                SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS ? "obj" : "o",
                commandBuffer);
    }

#ifndef SHUC_NO_INCREMENTAL_BUILD
    if (SHUI.INCREMENTAL.enabled) {
        SHU_LogInfo("Compiled %zu/%zu files (%zu skipped)", 
                   SHUI.MODULE.sourceFiles.count - skippedFiles,
                   SHUI.MODULE.sourceFiles.count,
                   skippedFiles);
    }
#endif

    // Linking code (unchanged)
    // ...

#ifndef SHUC_NO_INCREMENTAL_BUILD
    // Save cache
    if (SHUI.INCREMENTAL.enabled) {
        SHUI_SaveBuildCache(directory.data);
    }
#endif

    // Cleanup object files (existing code)
    // ...
}
```

### 1.5 Public API

```c
/// @brief Enable or disable incremental builds
/// @param enabled 1 to enable, 0 to disable
void SHU_ModuleSetIncremental(char enabled) {
#ifndef SHUC_NO_INCREMENTAL_BUILD
    SHUI.INCREMENTAL.enabled = enabled;
#else
    (void)enabled;
    SHU_LogWarning("Incremental builds disabled at compile time");
#endif
}

/// @brief Force a clean build, ignoring cache
void SHU_ModuleForceClean(void) {
#ifndef SHUC_NO_INCREMENTAL_BUILD
    SHUI.INCREMENTAL.forceClean = 1;
#endif
}
```

---

## 2. Multithreading Implementation

### 2.1 Platform Abstraction

```c
// Thread handle abstraction
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
typedef HANDLE SHUI_Thread;
typedef DWORD (WINAPI *SHUI_ThreadFunc)(void*);
#else
typedef pthread_t SHUI_Thread;
typedef void* (*SHUI_ThreadFunc)(void*);
#endif

// Thread creation
static SHUI_Thread SHUI_CreateThread(SHUI_ThreadFunc func, void *arg) {
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    return CreateThread(NULL, 0, func, arg, 0, NULL);
#else
    SHUI_Thread thread;
    pthread_create(&thread, NULL, func, arg);
    return thread;
#endif
}

// Thread join
static void SHUI_JoinThread(SHUI_Thread thread) {
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
#else
    pthread_join(thread, NULL);
#endif
}

// Get CPU count
static size_t SHUI_GetCPUCount(void) {
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return (size_t)sysinfo.dwNumberOfProcessors;
#else
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    return nprocs > 0 ? (size_t)nprocs : 1;
#endif
}
```

### 2.2 Job Queue

```c
typedef struct SHUI_CompileJob {
    char sourcePath[SHUC_MAX_PATH_SIZE];
    char objectPath[SHUC_MAX_PATH_SIZE];
    char commandBuffer[SHUC_MAX_COMMAND_BUFFER_SIZE];
    volatile int status; // 0=pending, 1=running, 2=success, -1=failed
    int exitCode;
} SHUI_CompileJob;

typedef struct SHUI_JobQueue {
    SHUI_CompileJob *jobs;
    size_t count;
    size_t capacity;
    volatile size_t nextJobIndex;
    volatile size_t completedJobs;
    volatile size_t failedJobs;
    
    // Synchronization primitives
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    CRITICAL_SECTION lock;
#else
    pthread_mutex_t lock;
#endif
} SHUI_JobQueue;

// Initialize job queue
static void SHUI_InitJobQueue(SHUI_JobQueue *queue, size_t capacity) {
    queue->jobs = (SHUI_CompileJob*)malloc(sizeof(SHUI_CompileJob) * capacity);
    queue->count = 0;
    queue->capacity = capacity;
    queue->nextJobIndex = 0;
    queue->completedJobs = 0;
    queue->failedJobs = 0;
    
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    InitializeCriticalSection(&queue->lock);
#else
    pthread_mutex_init(&queue->lock, NULL);
#endif
}

// Add job to queue
static void SHUI_AddJob(SHUI_JobQueue *queue, const SHUI_CompileJob *job) {
    if (queue->count >= queue->capacity) {
        SHU_LogError(SHUM_ERROR, "Job queue full");
    }
    
    queue->jobs[queue->count] = *job;
    queue->jobs[queue->count].status = 0; // Pending
    queue->count++;
}

// Get next job (thread-safe)
static SHUI_CompileJob* SHUI_GetNextJob(SHUI_JobQueue *queue) {
    SHUI_CompileJob *job = NULL;
    
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    EnterCriticalSection(&queue->lock);
#else
    pthread_mutex_lock(&queue->lock);
#endif
    
    if (queue->nextJobIndex < queue->count) {
        job = &queue->jobs[queue->nextJobIndex];
        job->status = 1; // Running
        queue->nextJobIndex++;
    }
    
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    LeaveCriticalSection(&queue->lock);
#else
    pthread_mutex_unlock(&queue->lock);
#endif
    
    return job;
}

// Worker thread function
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
static DWORD WINAPI SHUI_CompileWorker(void *arg) {
#else
static void* SHUI_CompileWorker(void *arg) {
#endif
    SHUI_JobQueue *queue = (SHUI_JobQueue*)arg;
    
    while (1) {
        SHUI_CompileJob *job = SHUI_GetNextJob(queue);
        if (!job) break; // No more jobs
        
        // Execute compilation
        job->exitCode = system(job->commandBuffer);
        
        // Update status
        if (job->exitCode == 0) {
            job->status = 2; // Success
            __sync_add_and_fetch(&queue->completedJobs, 1);
        } else {
            job->status = -1; // Failed
            __sync_add_and_fetch(&queue->failedJobs, 1);
            
#ifndef SHUC_NO_RUN_LOG
            SHU_LogError(0, "Compilation failed: %s", job->sourcePath);
#endif
        }
    }
    
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    return 0;
#else
    return NULL;
#endif
}

// Execute job queue with thread pool
static void SHUI_ExecuteJobQueue(SHUI_JobQueue *queue, size_t threadCount) {
    if (threadCount == 0) {
        threadCount = SHUI_GetCPUCount();
        if (threadCount > 1) threadCount--; // Leave one core free
    }
    
    if (threadCount > queue->count) {
        threadCount = queue->count; // Don't create more threads than jobs
    }
    
#ifndef SHUC_NO_RUN_LOG
    SHU_LogInfo("Compiling %zu files with %zu threads...", 
               queue->count, threadCount);
#endif
    
    // Create worker threads
    SHUI_Thread *threads = (SHUI_Thread*)malloc(sizeof(SHUI_Thread) * threadCount);
    
    for (size_t i = 0; i < threadCount; i++) {
        threads[i] = SHUI_CreateThread(SHUI_CompileWorker, queue);
    }
    
    // Wait for all threads
    for (size_t i = 0; i < threadCount; i++) {
        SHUI_JoinThread(threads[i]);
    }
    
    free(threads);
    
    // Report results
    if (queue->failedJobs > 0) {
        SHU_LogError(SHUM_ERROR, "Compilation failed for %zu/%zu files", 
                    queue->failedJobs, queue->count);
    }
}

// Cleanup job queue
static void SHUI_DestroyJobQueue(SHUI_JobQueue *queue) {
#if SHUM_HOST_PLATFORM == SHUM_PLATFORM_WINDOWS
    DeleteCriticalSection(&queue->lock);
#else
    pthread_mutex_destroy(&queue->lock);
#endif
    
    free(queue->jobs);
    queue->jobs = NULL;
}
```

### 2.3 Integration with Compilation

```c
static void SHUI_CompileLibraryStatic(SHUI_String directory)
{
    // ... cache loading code ...
    
#ifndef SHUC_NO_MULTITHREADING
    // Use multithreading if enabled and more than one file
    if (SHUI.COMPILER.threadCount > 0 && 
        SHUI.MODULE.sourceFiles.count > 1) {
        
        // Create job queue
        SHUI_JobQueue queue;
        SHUI_InitJobQueue(&queue, SHUI.MODULE.sourceFiles.count);
        
        // Prepare all compilation jobs
        for (size_t i = 0; i < SHUI.MODULE.sourceFiles.count; i++) {
            // Check if compilation needed (incremental build logic)
            char objPath[SHUC_MAX_PATH_SIZE];
            // ... generate objPath ...
            
            if (SHUI_FileNeedsRecompile(...)) {
                SHUI_CompileJob job;
                strncpy(job.sourcePath, source, SHUC_MAX_PATH_SIZE - 1);
                strncpy(job.objectPath, objPath, SHUC_MAX_PATH_SIZE - 1);
                
                // Build command
                snprintf(job.commandBuffer, sizeof(job.commandBuffer),
                        "%s %s %s %s %s %s",
                        SHUI.COMPILER.command.data,
                        SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/c" : "-c",
                        job.sourcePath,
                        SHUI.COMPILER.identifier == SHUM_COMPILER_MSVC ? "/Fo:" : "-o",
                        job.objectPath,
                        commandBuffer);
                
                SHUI_AddJob(&queue, &job);
            }
        }
        
        // Execute jobs in parallel
        if (queue.count > 0) {
            SHUI_ExecuteJobQueue(&queue, SHUI.COMPILER.threadCount);
        }
        
        SHUI_DestroyJobQueue(&queue);
    } else
#endif
    {
        // Single-threaded compilation (existing code)
        for (size_t i = 0; i < SHUI.MODULE.sourceFiles.count; i++) {
            // ... existing compilation code ...
        }
    }
    
    // Linking and cleanup (unchanged)
    // ...
}
```

### 2.4 Public API

```c
// Add to internal state
struct {
    // ... existing COMPILER fields ...
    size_t threadCount; // 0 = auto-detect
} COMPILER;

/// @brief Set number of threads for parallel compilation
/// @param threadCount Number of threads (0 = auto-detect)
void SHU_CompilerSetThreads(size_t threadCount) {
#ifndef SHUC_NO_MULTITHREADING
    SHUI.COMPILER.threadCount = threadCount;
#else
    (void)threadCount;
    SHU_LogWarning("Multithreading disabled at compile time");
#endif
}

/// @brief Get optimal thread count for this system
/// @return Number of CPU cores minus 1 (minimum 1)
size_t SHU_CompilerGetOptimalThreadCount(void) {
    size_t cpuCount = SHUI_GetCPUCount();
    return cpuCount > 1 ? cpuCount - 1 : 1;
}
```

---

## 3. Key Implementation Considerations

### 3.1 Error Handling

- All file I/O should check return values
- Cache corruption should trigger clean build
- Thread creation failures should fall back to single-threaded
- Memory allocation failures should terminate gracefully

### 3.2 Memory Management

- All dynamic allocations must have corresponding frees
- Cache data should be freed after save
- Job queue should be cleaned up after execution
- No memory leaks in error paths

### 3.3 Initialization

Add initialization in `SHU_CompilerConfigure()`:

```c
void SHU_CompilerConfigure(char compiler, const char *compilerCommand) {
    // Existing code...
    
#ifndef SHUC_NO_INCREMENTAL_BUILD
    SHUI.INCREMENTAL.enabled = 1; // Enabled by default
    SHUI.INCREMENTAL.forceClean = 0;
#endif

#ifndef SHUC_NO_MULTITHREADING
    SHUI.COMPILER.threadCount = 0; // Auto-detect
#endif
}
```

### 3.4 Logging

Add performance logging option:

```c
#ifdef SHUC_PERFORMANCE_LOG
#define SHU_LogPerformance(format, ...) \
    SHU_LogInfo(SHUM_COLOR_CYAN("PERF: ") format, ##__VA_ARGS__)
#else
#define SHU_LogPerformance(format, ...) ((void)0)
#endif
```

### 3.5 Testing Strategy

Create test harness:

```c
// test/test_incremental.c
void test_incremental() {
    // First build
    SHU_CompilerConfigure(SHUM_COMPILER_GCC, "gcc");
    SHU_ModuleBegin("test");
    SHU_ModuleAddSourceFile("test1.c");
    SHU_ModuleAddSourceFile("test2.c");
    SHU_ModuleCompile("build/", SHUM_MODULE_LIBRARY_STATIC);
    
    // Second build (should skip everything)
    SHU_ModuleBegin("test");
    SHU_ModuleAddSourceFile("test1.c");
    SHU_ModuleAddSourceFile("test2.c");
    SHU_ModuleCompile("build/", SHUM_MODULE_LIBRARY_STATIC);
    
    // Modify one file
    system("touch test1.c");
    
    // Third build (should only compile test1.c)
    SHU_ModuleBegin("test");
    SHU_ModuleAddSourceFile("test1.c");
    SHU_ModuleAddSourceFile("test2.c");
    SHU_ModuleCompile("build/", SHUM_MODULE_LIBRARY_STATIC);
}
```

---

## 4. Build Configuration Examples

### 4.1 Maximum Performance

```c
#define SHUC_NO_MODULE_LOG      // Reduce logging overhead
#define SHUC_NO_RUN_LOG         // Reduce logging overhead
#define SHUC_MAX_THREADS 8      // Use 8 threads
#define SHUILD_IMPLEMENTATION
#include "shuild.h"

int main() {
    SHU_CompilerConfigure(SHUM_COMPILER_GCC, "gcc");
    SHU_CompilerSetThreads(8);
    SHU_ModuleSetIncremental(1);
    
    // Build code...
}
```

### 4.2 Debugging Build System

```c
#define SHUC_PERFORMANCE_LOG    // Enable performance logging
#define SHUILD_IMPLEMENTATION
#include "shuild.h"

int main() {
    SHU_CompilerConfigure(SHUM_COMPILER_GCC, "gcc");
    SHU_CompilerSetThreads(1); // Single-threaded for easier debugging
    
    // Build code...
}
```

### 4.3 Conservative Build

```c
#define SHUC_NO_INCREMENTAL_BUILD  // Always clean build
#define SHUC_NO_MULTITHREADING     // Single-threaded
#define SHUILD_IMPLEMENTATION
#include "shuild.h"

int main() {
    SHU_CompilerConfigure(SHUM_COMPILER_GCC, "gcc");
    
    // Build code...
}
```

---

## 5. Migration Path for Existing Users

### Step 1: No Changes Required
Existing code works without modification. All features are opt-in or have sensible defaults.

### Step 2: Enable Features Incrementally
```c
// Existing code
SHU_CompilerConfigure(SHUM_COMPILER_GCC, "gcc");
SHU_ModuleBegin("myapp");
SHU_ModuleAddSourceDirectory("src/");
SHU_ModuleCompile("build/", SHUM_MODULE_EXECUTABLE);

// Add one line to enable multithreading
SHU_CompilerSetThreads(0); // Auto-detect
```

### Step 3: Monitor Performance
```c
#define SHUC_PERFORMANCE_LOG
// Observe log output to see improvements
```

### Step 4: Optimize Further
```c
// Fine-tune thread count based on profiling
SHU_CompilerSetThreads(6);

// Enable dependency tracking (Phase 2)
SHU_ModuleSetDependencyTracking(1);
```

---

## Summary

This implementation guide provides:
1. Concrete code patterns for each feature
2. Platform-specific abstractions
3. Error handling strategies
4. Testing approaches
5. Migration paths for users

All code respects the single-header philosophy and maintains backward compatibility. Features can be disabled via macros for users who prefer the simpler, original behavior.

**Next Steps:**
1. Review this guide with maintainers
2. Implement Phase 1 features in a development branch
3. Test with example projects
4. Gather performance metrics
5. Iterate based on feedback

**Document Version:** 1.0  
**Date:** 2026-01-10  
**Companion to:** PERFORMANCE_IMPROVEMENTS.md
