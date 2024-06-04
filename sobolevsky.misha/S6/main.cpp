#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "shakerSort.hpp"
#include "mergeSort.hpp"
#include "sortsAgregatorANDcontainerIO.hpp"
#include "../common/tree.hpp"

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "missed some argc\n";
    return 1;
  }

  std::string first = argv[1];
  std::string second = argv[2];

  size_t size = std::stoull(argv[3]);

  sobolevsky::AVLtree< std::string, sobolevsky::AVLtree< std::string, std::function< void(std::ostream &, size_t) >, bool >, bool >  cmds;
  using namespace std::placeholders;
  cmds["ascending"]["ints"] = std::bind(sobolevsky::sortsAgregator< int, std::less< int > >, _1, _2, std::less< int >{});
  cmds["descending"]["ints"] = std::bind(sobolevsky::sortsAgregator< int, std::greater< int > >, _1, _2, std::greater< int >{});
  cmds["ascending"]["floats"] = std::bind(sobolevsky::sortsAgregator< double, std::less< double > >, _1, _2, std::less< double >{});
  cmds["descending"]["floats"] = std::bind(sobolevsky::sortsAgregator< double, std::greater< double > >, _1, _2, std::greater< double >{});
  try
  {
    cmds.at(first).at(second)(std::cout, size);
  }
  catch(const std::exception & e)
  {
    std::cerr << "inv\n";
    return 1;
  }
  return 0;
}