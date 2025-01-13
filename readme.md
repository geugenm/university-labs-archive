# university-labs-archive

The digital graveyard of academic suffering - a collection of C++ code that somehow passed university requirements while making Linus Torvalds cry in his sleep. Because sometimes you need to preserve your mistakes to appreciate how far you've come.

## What's Inside This Dumpster Fire

### Core Labs (01)
- **Code Review**: Two flavors of pain
  - Debug: When we pretended to understand what we were doing
  - Release: When we gave up and just made it work
- **Labs I-VI**: A chronological descent into madness
  - Alpha builds: The "I can code" phase
  - Beta builds: The "Oh god why" phase

### Advanced Torture (02)
- **Lab 1**: Binary file operations that would make Ken Thompson question his life choices
- **Lab 2**: Custom string/vector implementations because apparently STL wasn't invented yet
- **Lab 3**: A lexer that would make compiler writers drink
- **Lab 4**: Unit tests powered by Google's framework and pure spite

### Extended Pain (ext)
- **04-08**: GUI experiments with Builder C++ that look like Windows 95's uglier cousin
- **Autotimetable**: An attempt at solving NP-hard problems with caffeine and desperation

## Build Instructions (If You Dare)

```
# Core Labs
mkdir build && cd build
cmake ..
make -j$(nproc) # Prepare for compiler screaming

# Extended Projects
cd ext/04-08
# Open in Builder C++ and pray to whatever deity you believe in
```

## Dependencies

| Component | Purpose |
|-----------|----------|
| C++20 Compiler | To judge your life choices |
| CMake 3.15+ | Because we're too good for Makefiles |
| Boost | Because reinventing wheels is our passion |
| Builder C++ | For GUI nightmares |
| easylogging++ | Because std::cout wasn't painful enough |
| Your Sanity | Highly optional |

## Project Structure

```
.
├── 01/                # Core Programming Labs
│   ├── LAB-I-VI/     # Progressive descent into madness
│   └── code-review/   # Evidence of Stockholm syndrome
├── 02/                # Advanced Labs
│   └── lab-[1-4]/    # Various crimes against computer science
└── ext/              # Extended Projects
    └── [04-08]/      # GUI experiments that time forgot
```

## Testing Philosophy

- Unit tests powered by Google's framework and pure spite
- Integration tests that sometimes pass
- System tests that we don't talk about

## Performance Metrics

- Runs faster than PHP (usually)
- Memory leaks are features
- O(n!) complexity because we're optimists

## Security Features

- None. We believe in living dangerously
- Buffer overflows are just surprise features
- SQL injection? More like SQL invitation

## Known Issues

- Everything
- But specifically:
  - Memory leaks that would make Valgrind have a stroke
  - Race conditions that only appear during demos
  - GUI that makes Windows 3.1 look modern

## License

MIT - Because someone might actually learn from these mistakes, though they probably shouldn't.

## Note

This codebase serves as a testament to the fact that you can graduate without understanding pointers, memory management, or basic human decency toward future maintainers. Preserved in its original form as a warning to future generations.

Remember: "It's not a bug, it's an undocumented feature" - Some intern, probably.

---
*"In memory of all the CPU cycles sacrificed for this educational journey"*
