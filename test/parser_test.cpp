#include <stdexcept>
#include "gtest/gtest.h"
#include "lexer.hpp"
#include "parser.hpp"
#include "ast.hpp"


TEST(ParserTest, EmptySource)
{
  bfc::parser<bfc::stream_source> parser{
    bfc::lexer<bfc::stream_source>{bfc::stream_source{new std::stringstream{""}}}};
  bfc::ast_node node = parser.parse();
  EXPECT_TRUE(((bfc::ast_program *) node.get())->empty()) << "Should produce and empty program node";
}


TEST(ParserTest, SimpleSource)
{
  bfc::parser<bfc::stream_source> parser{
    bfc::lexer<bfc::stream_source>{bfc::stream_source{
    new std::stringstream{"+[-><,]+."}}}};
  bfc::ast_node node = parser.parse();
  EXPECT_FALSE(((bfc::ast_program *) node.get())->empty()) << "Should not produce an empty program node";
  auto it = ((bfc::ast_program *) node.get())->begin();
  EXPECT_NE(dynamic_cast<bfc::ast_add*>(it->get()), nullptr) << "INC should be parsed into ast_add";

  ++it;
  EXPECT_NE(dynamic_cast<bfc::ast_loop*>(it->get()), nullptr) << "LOOP should be parsed into ast_loop";

  auto loopIt = ((bfc::ast_loop *) it->get())->begin();
  EXPECT_NE(loopIt->get(), nullptr) << "DEC should be parsed into ast_sub";
  EXPECT_NE(dynamic_cast<bfc::ast_sub*>(loopIt->get()), nullptr) << "DEC should be parsed into ast_sub";

  ++loopIt;
  EXPECT_NE(dynamic_cast<bfc::ast_mov*>(loopIt->get()), nullptr) << "MOVE_R should be parsed into ast_mov";

  ++loopIt;
  EXPECT_NE(dynamic_cast<bfc::ast_mov*>(loopIt->get()), nullptr) << "MOVE_L should be parsed into ast_mov";

  ++loopIt;
  EXPECT_NE(dynamic_cast<bfc::ast_read*>(loopIt->get()), nullptr) << "GET_CHAR should be parsed into ast_read";

  ++it;
  EXPECT_NE(dynamic_cast<bfc::ast_add*>(it->get()), nullptr) << "INC should be parsed into ast_add";

  ++it;
  EXPECT_NE(dynamic_cast<bfc::ast_write*>(it->get()), nullptr) << "PUT_CHAR should be parsed into ast_write";
}


TEST(ParserTest, UnclosedLoop)
{
  bfc::parser<bfc::stream_source> parser{
    bfc::lexer<bfc::stream_source>{bfc::stream_source{new std::stringstream{"["}}}};
  ASSERT_THROW(parser.parse(), std::runtime_error);
}

TEST(ParserTest, UnopenedLoop)
{
  bfc::parser<bfc::stream_source> parser{
    bfc::lexer<bfc::stream_source>{bfc::stream_source{new std::stringstream{"]"}}}};
  ASSERT_THROW(parser.parse(), std::runtime_error);
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
