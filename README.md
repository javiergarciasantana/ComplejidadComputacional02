# Stack Automaton for Computational Complexity

This project is an implementation of a Stack Automaton, designed for educational purposes in the "Computabilidad y Complejidad" course at Universidad de La Laguna. The stack automaton is a type of computational model that uses a stack to manage its state transitions, commonly studied in the theory of computation and automata theory.

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Folder Structure](#folder-structure)
- [Getting Started](#getting-started)
- [Building the Project](#building-the-project)
- [Usage](#usage)

## Project Overview
The project simulates a stack automaton that reads input strings, performs state transitions based on the input, and utilizes a stack for additional memory. The automaton is defined by:
- A set of states
- An input alphabet
- A stack alphabet
- A set of transitions

This implementation supports loading the automaton's configuration from a file, executing it with a given input string, and displaying detailed execution steps.

## Features
- **Automaton Configuration Loading**: Load states, alphabets, transitions, initial state, and initial stack symbol from a configuration file.
- **Stack Operations**: The automaton uses a stack for performing push and pop operations as specified by transitions.
- **Detailed Execution Tracing**: Step-by-step output of state transitions, stack operations, and current stack content.
- **Backtracking Support**: Supports non-deterministic transitions with backtracking.

## Folder Structure
The project structure is as follows:
ComplejidadComputacional02/ <br>
├── src/ # Source code files <br>
  ├── include/ # Header files for classes and definitions <br>
├── build/ # Compiled binaries <br>
  ├── data/ # Sample configuration files for automaton <br>
├── CMakeLists.txt # CMake build configuration <br>
└── README.md # Project documentation <br>

## Getting Started

### Prerequisites
- **C++17** or later is required.
- **CMake** (version 3.5 or later) for building the project.
- A C++ compiler (e.g., `g++`, `clang`, `MSVC`).

### Cloning the Repository
To get a copy of this project:
```bash
git clone https://github.com/javiergarciasantana/ComplejidadComputacional02.git
cd ComplejidadComputacional02
```

## Building the Project

1. Create a build directory:
```bash
mkdir build
cd build
```
2. Configure the project with CMake:
```bash
cmake ..
```
3. Compile the project:
```bash
make
```
The executable will be created in the build/ directory.

## Usage
### Running the Automaton
To run the automaton, use:

```bash
./automaton input.txt
```

### Input Format
The configuration file should follow this format:

- States: A list of states, separated by spaces.
- Input Alphabet: A list of symbols for the input alphabet.
- Stack Alphabet: A list of symbols for the stack alphabet.
- Initial State: The initial state of the automaton.
- Initial Stack Symbol: The initial symbol on the stack.
- Transitions: Each transition is defined as:
  (<current_state>, <input_symbol>, <stack_symbol>, <next_state>, <stack_operation>)

### Example Configuration File
```bash
q1 q2
a b
S A
q1
S

q1 a S q1 A
q1 a A q1 AA
q1 b A q2 .
q2 b A q2 .
```
### Executing with an Input String
After loading the configuration, you can input a string to be processed by the automaton:

```bash
Enter the input string:
abba
```
The automaton will execute and display step-by-step transitions.
