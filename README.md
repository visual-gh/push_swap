*This project has been created as part of the 42 curriculum by Visual.*

# push_swap

## Table of Contents

- [Description](#description)
- [Instructions](#instructions)
- [Operations](#operations)
- [Benchmark Results](#benchmark-results)
- [Understanding Linked Lists](#understanding-linked-lists)
- [Radix Sort Explained](#radix-sort-explained)
- [Project Structure](#project-structure)
- [Resources](#resources)
- [AI Usage](#ai-usage)


## Description

A sorting algorithm project that sorts integers on a stack using a limited set of operations, aiming for the lowest possible number of moves. Implements a Radix sort approach for large datasets and optimized algorithms for small stacks (2-5 elements).


## Instructions

Compile the program:
```bash
make
```

Run with integers as arguments:
```bash
./push_swap 3 2 1 5 4
./push_swap "3 2 1 5 4"
./push_swap -2147483648 0 2147483647
```

The program outputs the sequence of operations needed to sort the stack in ascending order.


## Operations

| Operation | Description |
|-----------|-------------|
| `sa` / `sb` | Swap first 2 elements of stack a/b |
| `ss` | `sa` and `sb` simultaneously |
| `pa` / `pb` | Push top element from b to a / a to b |
| `ra` / `rb` | Rotate stack a/b up (first becomes last) |
| `rr` | `ra` and `rb` simultaneously |
| `rra` / `rrb` | Rotate stack a/b down (last becomes first) |
| `rrr` | `rra` and `rrb` simultaneously |


## Benchmark Results

**Radix Sort Results:**
- **100 numbers:** ~1084 moves (3/5 grade)
- **500 numbers:** ~6784 moves (4/5 grade)
- **Small stacks (≤5):** Optimized algorithms, always under thresholds

Radix provides consistent O(n·k) performance across all inputs without edge case handling.


## Understanding Linked Lists

### Structure

Each stack is a singly linked list where elements connect in one direction:

```c
typedef struct s_stack
{
    int             value;   // The actual integer
    int             index;   // Sorted position (0 to n-1)
    struct s_stack  *next;   // Pointer to next node
}   t_stack;
```

**Visual representation:**
```
Stack a: [3] -> [1] -> [5] -> [2] -> NULL
         top                   bottom
```

### Why Linked Lists?

Stacks require frequent insertion/removal at both ends. Linked lists provide O(1) operations for:
- Push/pop from top (insert/remove at head)
- Rotate operations (move nodes between head and tail)

Arrays would require shifting elements, making these O(n) operations.


## Radix Sort Explained

Radix sort processes numbers bit by bit, sorting based on each binary digit from least significant (rightmost) to most significant (leftmost).

### Algorithm Steps

1. **Index Assignment:** Convert arbitrary integers to dense ranking (0 to n-1)
   - Input: `[42, -5, 100, 0]` → Indices: `[2, 0, 3, 1]`
   - Prevents integer overflow, works with any range

2. **Bit-by-Bit Processing:** Sort by each bit position (right to left)
   - For 100 numbers: need ⌈log₂(100)⌉ = 7 passes (bits 0-6)
   - For 500 numbers: need ⌈log₂(500)⌉ = 9 passes (bits 0-8)

3. **Per-Bit Sort:**
   - If bit is **0**: push to stack b
   - If bit is **1**: rotate in stack a (keeps sorted relative order)
   - After all elements processed, push everything back from b to a

### Example: Sorting 8 Numbers

**Input:** `[6, 2, 7, 1, 5, 3, 0, 4]` → **Indices:** `[6, 2, 7, 1, 5, 3, 0, 4]`

Binary (3 bits needed):
```
6 = 110
2 = 010
7 = 111
1 = 001
5 = 101
3 = 011
0 = 000
4 = 100
```

**Pass 1 - Bit 0 (rightmost):**
```
Stack a: [6(0), 2(0), 7(1), 1(1), 5(1), 3(1), 0(0), 4(0)]
          ↓pb   ↓pb   ↓ra   ↓ra   ↓ra   ↓ra   ↓pb   ↓pb

After sorting bit 0:
  a = [7, 1, 5, 3]  (all have bit 0 = 1)
  b = [4, 0, 2, 6]  (all have bit 0 = 0)

Push back: pa pa pa pa
  a = [6, 2, 0, 4, 7, 1, 5, 3]
```
*Why ra for bit=1?* Keeps elements in stack a while maintaining their relative order. We only separate 0s from 1s, then recombine.

**Pass 2 - Bit 1 (middle):**
```
Stack a: [6(1), 2(1), 0(0), 4(0), 7(1), 1(0), 5(0), 3(1)]
          ↓ra   ↓ra   ↓pb   ↓pb   ↓ra   ↓pb   ↓pb   ↓ra

After sorting bit 1:
  a = [6, 2, 7, 3]  (all have bit 1 = 1)
  b = [5, 1, 4, 0]  (all have bit 1 = 0)

Push back: pa pa pa pa
  a = [0, 4, 1, 5, 6, 2, 7, 3]
```

**Pass 3 - Bit 2 (leftmost):**
```
Stack a: [0(0), 4(1), 1(0), 5(1), 6(1), 2(0), 7(1), 3(0)]
          ↓pb   ↓ra   ↓pb   ↓ra   ↓ra   ↓pb   ↓ra   ↓pb

After sorting bit 2:
  a = [4, 5, 6, 7]  (all have bit 2 = 1)
  b = [3, 2, 1, 0]  (all have bit 2 = 0)

Push back: pa pa pa pa
  a = [0, 1, 2, 3, 4, 5, 6, 7]  ✓ SORTED
```

### Why This Works

- Each pass separates numbers by a single bit (stable sort)
- Processing LSB first ensures lower bits are already sorted when we reach higher bits
- After processing all bits, numbers are in complete sorted order

### Move Count

For n elements needing b bits:
```
Moves ≈ b × (2n)
  - n operations per pass (pb or ra)
  - n push backs (pa)
  - Repeat for each bit
```

Example: 100 numbers → 7 bits × 200 operations ≈ 1400 moves (actual: ~1084)


## Project Structure

```
srcs/
├── main.c              # Entry point, algorithm selection
├── stack.c             # Linked list operations (new, add, clear, size, last)
├── parsing/
│   ├── parse.c         # Argument parsing (split, validate)
│   └── validate.c      # Input validation (atol, int check, duplicates)
├── operations/
│   ├── push.c          # pa, pb
│   ├── swap.c          # sa, sb, ss
│   ├── rotate.c        # ra, rb, rr
│   └── rev_rotate.c    # rra, rrb, rrr
└── algorithms/
    ├── radix.c         # Radix sort + indexing
    └── small.c         # sort_three, sort_five, is_sorted
```

### Execution Flow

1. **Parse:** Convert arguments to linked list, validate (no duplicates, valid ints)
2. **Check:** If already sorted, exit immediately
3. **Route:** Choose algorithm based on stack size:
   - Size 2: Single swap (`sa`)
   - Size 3: Optimized 3-element sort (max 2 moves)
   - Size 4-5: Isolation method (push mins, sort 3, push back)
   - Size 6+: Radix sort
4. **Execute:** Perform operations, print each instruction
5. **Cleanup:** Free all allocated memory

### Memory Management

- All nodes allocated via `stack_new()` and freed via `stack_clear()`
- Error paths call `error_exit()` which cleans both stacks before exiting
- Confirmed leak-free by tester's memory checks

### Algorithm Flow

```
┌──────────────────────────┐
│   Parse & Validate       │
│   Build stack a          │
└───────────┬──────────────┘
            │
       ┌────▼────────────────┐
       │   Already sorted?   │
       │   Exit if yes       │
       └────┬────────────────┘
            │
       ┌────▼────────────────┐
       │  Choose algorithm:  │
       │  • 2 → sa           │
       │  • 3 → sort_three   │
       │  • 4-5 → sort_five  │
       │  • 6+ → radix_sort  │
       └────┬────────────────┘
            │
       ┌────▼────────────────┐
       │  Execute & Print    │
       │  operations         │
       └────┬────────────────┘
            │
       ┌────▼────────────────┐
       │  Free memory        │
       │  Exit clean         │
       └─────────────────────┘
```


## Resources

- [42 Cursus Gitbook - push_swap](https://42-cursus.gitbook.io/guide/rank-02/push_swap)
- ["push_swap TUTORIAL!" (Thuggonaut)](https://youtu.be/wRvipSG4Mmk?si=tug5Ecn8vGxfpi3n)
- [Radix Sort Visualization](https://www.cs.usfca.edu/~galles/visualization/RadixSort.html)
- Man pages: `write`, `malloc`, `free`, `exit`


## AI Usage

AI was used to understand linked list fundamentals (node traversal, insertion, deletion patterns), clarify Radix sort mechanics and bit manipulation logic, define a clean project structure separating concerns (parsing, operations, algorithms), review code for memory leaks and edge cases, and assist in writing this README.
