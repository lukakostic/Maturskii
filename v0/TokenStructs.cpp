#include <cstddef>
#include <cstdint>
#include <vector>

#include "TokenStructs.hpp"


Tree::Tree(){
    type = Tree::TreeType::Package;
    tokens = std::vector<Instruction>();
}
Tree::Tree(TreeType treeType){
    type = treeType;
    tokens = std::vector<Instruction>();
}