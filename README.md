*This project has been created as part of the 42 curriculum by gabach.*

# Codexion

## Description
**Codexion** is a concurrent programming project that simulates a shared co-working space where multiple coder threads compete for a limited set of shared resources (USB dongles) to compile their quantum code. Inspired by classic concurrency puzzles like the Dining Philosophers problem, this simulation explores resource synchronization, deadlock avoidance, scheduling algorithms, and real-time monitoring under strict timing constraints.

In this hub, $N$ coders sit in a circle with exactly $N$ dongles distributed between them (each coder shares a left dongle and a right dongle with their immediate neighbors). Coders cycle through three distinct states: **compiling**, **debugging**, and **refactoring**. To compile, a coder must successfully acquire both adjacent dongles. The simulation runs until all coders complete a mandatory number of compiles, or until a coder **burns out** (fails to start compiling within a specified `time_to_burnout` window since their last compilation or the start of the simulation).

---

## Instructions

### Compilation

To compile the executable:
```bash
make

```

To clean object files:

```bash
make clean

```

To fully clean object files and the binary:

```bash
make fclean

```

To recompile from scratch:

```bash
make re

```

### Execution & Usage

Run the simulation with the following mandatory command-line arguments:

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler

```

#### Parameter Details:

* `number_of_coders`: Total number of coder threads (and matching number of dongles).
* `time_to_burnout`: Maximum time (ms) a coder can go without compiling before burning out.
* `time_to_compile`: Time (ms) spent holding both dongles to compile code.
* `time_to_debug`: Time (ms) spent debugging after compilation.
* `time_to_refactor`: Time (ms) spent refactoring after debugging.
* `number_of_compiles_required`: Number of compilations each coder must hit to complete the simulation successfully.
* `dongle_cooldown`: Cooldown period (ms) after a dongle is released before it can be re-acquired.
* `scheduler`: The policy used by the dongle queue (`fifo` or `edf`).

#### Example:

```bash
./codexion 5 182 50 30 20 10 10 edf

```

---

## Blocking Cases Handled

### 1. Deadlock Prevention & Coffman's Conditions

To eliminate deadlocks, our implementation breaks the **Circular Wait** condition (one of Coffman's four necessary conditions for deadlocks). Coders are assigned a unique ID. Instead of greedily picking up the left dongle first, even-indexed coders swap their pickup order (acquiring their right dongle before their left dongle). This asymmetry ensures that a cyclic dependency where every coder holds one dongle and waits indefinitely for the next cannot occur.

### 2. Starvation Prevention & Fair Arbitration

When multiple coders compete for the same dongle, requests are managed using explicit priority queues (`heap_queue`) embedded within each dongle's state structure. Depending on the `scheduler` parameter:

* **FIFO (First-In, First-Out):** Coders are served in the exact chronological order of their acquisition requests.
* **EDF (Earliest Deadline First):** Priority is given to the coder with the nearest burnout deadline ($last\_compile\_start + time\_to\_burnout$), ensuring urgent threads get resources first and reducing simulation-wide burnout risk.

### 3. Cooldown Handling

After a coder releases a dongle, the dongle registers its release timestamp. The `scheduler()` function checks this timestamp against the current system time using `get_time_msec()`. If the `dongle_cooldown` has not yet elapsed, the requesting coder safely backs off and sleeps for the remainder of the cooldown duration via `msleep()`, ensuring no thread can hog a resource back-to-back during its cooldown window.

### 4. Precise Burnout Detection

A dedicated **Monitor Thread** continuously surveys the status of all coders by checking their `last_compile` timestamps against the current time. If any coder exceeds their `time_to_burnout` limit, the monitor instantly marks the global application state `app->end = 1` and prints a serialized `"burned out"` log. The system guarantees that this event is caught and logged well within the required **10ms tolerance window**.

### 5. Log Serialization

To avoid interleaved output and race conditions on `stdout`, all status logs pass through a unified logging function (`mutex_print`), which wraps the standard library `printf` within a dedicated output mutex (`str_mutex`). This guarantees atomic, clean, and perfectly ordered logs.

---

## Thread Synchronization Mechanisms

The implementation relies purely on the standard POSIX threads library (`pthread`), orchestrating state management through a combination of mutexes, condition variables, and structural flags:

* **`pthread_mutex_t` (Dongle & Coder Protection):** Each individual dongle possesses its own mutex (`dongle->mutex`) protecting its state, `held` flag, and priority `heap_queue`. Similarly, each coder has a state mutex (`coder->mutex`) protecting volatile fields such as `last_compile` and `nb_compile` from simultaneous reads by the monitor thread.
* **`pthread_cond_t` & `app_mutex` (Synchronized Launch):** A shared condition variable (`app->start_cond`) paired with `app->app_mutex` acts as a thread barrier. All coder threads initialize and wait on this condition variable inside `coder_thread_init()`. Once the monitor thread finishes setup, it executes a `pthread_cond_broadcast()`, ensuring all threads commence the simulation loop simultaneously.
* **Thread-Safe Communication:** Communication between coders and the monitor thread is handled via a shared master structure (`t_app`). The monitor modifies `app->end` under `app->app_mutex`, and coders systematically check this status through the thread-safe wrapper function `program_ended()`. This prevents data races and ensures proper cleanup (`pthread_join` and memory deallocation) when the program terminates.

---

## Resources

### Documentation & References

* *The Open Group Base Specifications (POSIX.1-2017) - `pthread` library:* Core definitions for mutexes, condition variables, and thread management.
* *Dining Philosophers Problem:* Classic synchronization paradigm detailing deadlock conditions and avoidance strategies.
* *Earliest Deadline First Scheduling:* Real-time operating system principles regarding dynamic priority scheduling.

### AI Usage Statement

AI tools were used during the development of this project for the following tasks:

1. **Refactoring & Boilerplate Generation:** Assisting in structural code layout matching the mandatory 42 Norm requirements, generating header file function prototypes, and streamlining memory-freeing logic (`free_app`, `free_dongles`).
2. **Edge-Case Verification:** Validating the mathematics behind the even/odd ID swap strategy to guarantee absolute protection against circular wait conditions under various counts of threads.
3. **Documentation Drafting:** Structuring and phrasing sections of this technical `README.md` to cleanly articulate concurrency primitives and blocking mechanisms.
