#include <stdexcept>
#include "gtest/gtest.h"
#include "lexer.hpp"
#include "parser.hpp"
#include "optimizer.hpp"
#include "ast.hpp"


TEST(OptimizerTest, CombineIncVisitor)
{
  bfc::parser<bfc::stream_source> parser{
    bfc::lexer<bfc::stream_source>{bfc::stream_source{new std::stringstream{"+++"}}}};
  bfc::optimizer optimizer{false, true};
  bfc::ast_node node = optimizer.optimize(parser.parse());
  EXPECT_FALSE(((bfc::ast_program *) node.get())->empty()) << "Should not produce an empty program node";
  auto it = ((bfc::ast_program *) node.get())->begin();
  EXPECT_NE(dynamic_cast<bfc::ast_add*>(it->get()), nullptr) << "INCs should be parsed into ast_add";
  EXPECT_EQ(((bfc::ast_add*)it->get())->value(), (bf_value) 3) << "3 INCs should be optimized into one ast_add";

}


TEST(OptimizerTest, CombinePtrVisitor)
{
  bfc::parser<bfc::stream_source> parser{
    bfc::lexer<bfc::stream_source>{bfc::stream_source{new std::stringstream{">>>"}}}};
  bfc::optimizer optimizer{false, true};
  bfc::ast_node node = optimizer.optimize(parser.parse());
  EXPECT_FALSE(((bfc::ast_program *) node.get())->empty()) << "Should not produce an empty program node";
  auto it = ((bfc::ast_program *) node.get())->begin();
  EXPECT_NE(dynamic_cast<bfc::ast_mov*>(it->get()), nullptr) << "MOVs should be parsed into ast_mov";
  EXPECT_EQ(((bfc::ast_mov*)it->get())->offset(), (ptrdiff_t) 3) << "3 MOVs should be optimized into one ast_mov";

}


TEST(OptimizerTest, ClearLoopsVisitor)
{
  bfc::parser<bfc::stream_source> parser{
    bfc::lexer<bfc::stream_source>{bfc::stream_source{new std::stringstream{"[-]"}}}};
  bfc::optimizer optimizer{false, true};
  bfc::ast_node node = optimizer.optimize(parser.parse());
  EXPECT_FALSE(((bfc::ast_program *) node.get())->empty()) << "Should not produce an empty program node";
  auto it = ((bfc::ast_program *) node.get())->begin();
  EXPECT_NE(dynamic_cast<bfc::ast_set*>(it->get()), nullptr) << "Code should be parsed into ast_set";
  EXPECT_EQ(((bfc::ast_set*)it->get())->value(), (bf_value) 0) << "Clearing loop [-] should be optimized into one ast_set(0)";
}

TEST(OptimizerTest, CombineSetVisitor)
{
  bfc::parser<bfc::stream_source> parser{
    bfc::lexer<bfc::stream_source>{bfc::stream_source{new std::stringstream{"[-]++"}}}};
  bfc::optimizer optimizer{false, true};
  bfc::ast_node node = optimizer.optimize(parser.parse());
  EXPECT_FALSE(((bfc::ast_program *) node.get())->empty()) << "Should not produce an empty program node";
  auto it = ((bfc::ast_program *) node.get())->begin();
  EXPECT_NE(dynamic_cast<bfc::ast_set*>(it->get()), nullptr) << "Code should be parsed into ast_set";
  EXPECT_EQ(((bfc::ast_set*)it->get())->value(), (bf_value) 2) << "ast_set(0) and 2 INCs should be parsed into ast_set(2)";
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
