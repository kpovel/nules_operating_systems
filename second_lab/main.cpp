// Option 11
// g++ main.cpp -o ./target/main && ./target/main

#include <iostream>
#include <string>

class String {
  protected:
    std::string str;

  public:
    String(std::string str) {
      this->str = str;
    }

    int len() {
      return str.length();
    }

    std::string get_value() {
      return this->str;
    }
};

class Char : public String {
  public:
    Char(std::string ch) : String(ch) {}

    void swap_symbols(int i, int j) {
      char tmp = str[i];
      str[i] = str[j];
      str[j] = tmp;
    }
};

int main() {
  String str = String("string");
  std::cout << "Length  of the \"" <<  str.get_value() << "\" is: " << str.len() << std::endl;

  Char ch = Char("char");
  ch.swap_symbols(0, ch.len() - 1);
  std::cout << "Length of swapped string \"" << ch.get_value() << "\" is: "
    << ch.get_value() << std::endl;

  return 0;
}
