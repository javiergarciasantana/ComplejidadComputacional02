// main.cc
// AUTOR: Javier Garcia Santana
// FECHA: 17/10/2024
// EMAIL: alu0101391663@ull.edu.es
// VERSION: 3.0
// ASIGNATURA: Complejidad Computacional
// PRÁCTICA Nº: 2
//
// COMPILACIÓN: make || g++ -o automata main.cc

#include "stack_automaton.h"


int main(int argc, char* argv[]) {
  Alphabet inputAlphabet, stackAlphabet;
  StackAutomaton automaton(State("q0"), Symbol('S'));

  automaton.loadAutomaton(std::string(argv[1]), inputAlphabet, stackAlphabet);

  std::string input;
  std::cout << "\nEnter the input string: \n";
  std::cin >> input;

  if (automaton.execute(input)) {
    std::cout << "The input is accepted." << std::endl;
  } else {
    std::cout << "The input is rejected." << std::endl;
  }

  return 0;
}