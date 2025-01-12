#include "../headers/config.h"
 
int main() {
  string initial_string;
  cout << "Enter a hex number[0x00]:"; cin >> initial_string;
  stringstream string_flow;
  string_flow << hex << initial_string;
  unsigned n;
  string_flow >> n;
  bitset<32> bit_set(n);
  cout << bit_set.to_string() << endl;
  
  return 0;
  
}