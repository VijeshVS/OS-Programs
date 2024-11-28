# Producer-Consumer Problem

## Overview

The **Producer-Consumer Problem** is a classic synchronization challenge where two processes (Producer and Consumer) share a common, fixed-size buffer. The Producer generates data and puts it into the buffer, while the Consumer takes data from the buffer for further processing. The challenge is to ensure proper synchronization to avoid race conditions, data corruption, or deadlocks.

### Real-World Example
- A **Compiler** produces assembly code, which is consumed by an **Assembler**.

## Problem Description

The issue arises because the Producer and Consumer access the shared buffer concurrently:
1. The **Producer** should not add items to the buffer if it is full.
2. The **Consumer** should not remove items from the buffer if it is empty.
3. Both processes should not access the buffer simultaneously.

## Solution Using Mutex and Semaphores

To address synchronization, we use:
- **Mutex**: A binary semaphore to lock and unlock the shared buffer.
- **Semaphores**: 
  - **Full**: A counting semaphore to track the number of items in the buffer.
  - **Empty**: A counting semaphore to track the number of empty slots in the buffer.

### Shared Variables
1. `mutex`: Ensures mutual exclusion (binary semaphore).
2. `full`: Counts the number of items in the buffer.
3. `empty`: Counts the number of empty slots in the buffer.

### Key Conditions
- **Mutual Exclusion**: When the Producer is adding data, the Consumer cannot access the buffer, and vice versa.
- **Buffer Full Check**: The Producer must wait if the buffer is full.
- **Buffer Empty Check**: The Consumer must wait if the buffer is empty.

---

## Implementation Workflow

### Producer
1. Check if the buffer is empty (`wait(empty)`), and if not, wait.
2. Lock the buffer (`wait(mutex)`).
3. Produce an item and add it to the buffer.
4. Unlock the buffer (`signal(mutex)`).
5. Increment the `full` semaphore to indicate a new item is available.

### Consumer
1. Check if the buffer has items (`wait(full)`), and if not, wait.
2. Lock the buffer (`wait(mutex)`).
3. Consume an item from the buffer.
4. Unlock the buffer (`signal(mutex)`).
5. Increment the `empty` semaphore to indicate a slot is now free.

---

# Reader-Writer Problem Solution

## Overview

The **Reader-Writer Problem** is a classic synchronization problem that involves multiple processes accessing shared data. The goal is to allow:
1. Multiple **readers** to access the shared data simultaneously (as reading does not modify data).
2. Only one **writer** to access the data at a time.
3. **Writers** to have exclusive access when writing.

## Problem Description

The key challenges are:
- Prevent **race conditions** between readers and writers.
- Ensure **mutual exclusion** so that writers have exclusive access to shared data.
- Prioritize or balance between readers and writers to avoid starvation.

### Solution with Semaphores

We use two **binary semaphores**:
1. **`mutex`**: Ensures mutual exclusion for modifying the reader count (`rcount`).
2. **`wr`**: Ensures exclusive access to the shared resource (e.g., a book) when a writer is writing or when no readers are active.

---

## How It Works

### Shared Variables
1. **`rcount`**: Tracks the number of active readers.
2. **`mutex`**: Ensures consistency of `rcount` during updates.
3. **`wr`**: Controls access to the shared data, ensuring mutual exclusion for writers.

### Key Conditions
- A **writer** must have exclusive access to the shared data when writing.
- A **reader** can access the data concurrently with other readers but not while a writer is writing.

---

## Implementation Workflow

### Writer:
1. Waits for `wr` to ensure no readers or other writers are active.
2. Acquires the `wr` semaphore to block all other processes.
3. Writes to the shared resource.
4. Releases the `wr` semaphore to allow other readers or writers.

### Reader:
1. Locks `mutex` to update the `rcount` safely.
2. If it is the **first reader**, locks `wr` to block writers.
3. Unlocks `mutex` and starts reading.
4. After reading, locks `mutex` to update `rcount`.
5. If it is the **last reader**, unlocks `wr` to allow writers.
6. Unlocks `mutex`.

---