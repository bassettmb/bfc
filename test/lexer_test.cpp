#include <fstream>
#include "gtest/gtest.h"
#include "lexer.hpp"
#include "result.hpp"
#include "source.hpp"
#include "source_loc.hpp"
#include "token.hpp"

static const char EMPTY_FILE_NAME = "empty_file.bfc"
static const char ONE_OF_EACH_FILE_NAME = "one_of_each.bfc"

TEST(LexerTest, EmptyFile)
{
  bfc::lexer<bfc::stream_source> lexer{bfc::stream_source{new std::fstream{EMPTY_FILE_NAME}}};
  bfc::token tok{};
  bfc::result_type result = lexer.next(tok);
  EXPECT_EQ(result, result_type::DONE) << "next() should return DONE when called on empty file";
}

TEST(LexerTest, OneOfEach)
{
  bfc::lexer<bfc::stream_source> lexer{bfc::stream_source{new std::fstream{ONE_OF_EACH_FILE_NAME}}};
  bfc::token tok{};
  bfc::result_type result = lexer.next(tok);
  EXPECT_EQ(result, result_type::OK) << "next() should return OK when reading tokens";
  EXPECT_EQ(tok.kind, bfc::token::INC) << "lexer should make token kind INC when reading \'+\'";

  bfc::result_type result = lexer.next(tok);
  EXPECT_EQ(result, result_type::OK) << "next() should return OK when reading tokens";
  EXPECT_EQ(tok.kind, bfc::token::DEC) << "lexer should make token kind DEC when reading \'-\'";

  bfc::result_type result = lexer.next(tok);
  EXPECT_EQ(result, result_type::OK) << "next() should return OK when reading tokens";
  EXPECT_EQ(tok.kind, bfc::token::MOVE_L) << "lexer should make token kind INC when reading \'<\'";

  bfc::result_type result = lexer.next(tok);
  EXPECT_EQ(result, result_type::OK) << "next() should return OK when reading tokens";
  EXPECT_EQ(tok.kind, bfc::token::MOVE_R) << "lexer should make token kind INC when reading \'>\'";

  bfc::result_type result = lexer.next(tok);
  EXPECT_EQ(result, result_type::OK) << "next() should return OK when reading tokens";
  EXPECT_EQ(tok.kind, bfc::token::LOOP_BEGIN) << "lexer should make token kind INC when reading \'[\'";

  bfc::result_type result = lexer.next(tok);
  EXPECT_EQ(result, result_type::OK) << "next() should return OK when reading tokens";
  EXPECT_EQ(tok.kind, bfc::token::LOOP_END) << "lexer should make token kind INC when reading \']\'";

  bfc::result_type result = lexer.next(tok);
  EXPECT_EQ(result, result_type::OK) << "next() should return OK when reading tokens";
  EXPECT_EQ(tok.kind, bfc::token::PUT_CHAR) << "lexer should make token kind INC when reading \'.\'";

  bfc::result_type result = lexer.next(tok);
  EXPECT_EQ(result, result_type::OK) << "next() should return OK when reading tokens";
  EXPECT_EQ(tok.kind, bfc::token::GET_CHAR) << "lexer should make token kind INC when reading \',\'";

  bfc::result_type result = lexer.next(tok);
  EXPECT_EQ(result, result_type::DONE) << "next() should return DONE when reading EOF";
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
