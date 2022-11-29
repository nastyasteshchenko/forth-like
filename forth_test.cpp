#include <gtest/gtest.h>
#include "interpreter.h"

//interpret

TEST(InterpretTest, writeNumbers) {
    std::string str = "100 154 985 4598 938 29384";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.size(), 6);
    EXPECT_EQ(it.top(), 29384);
}

//Plus

TEST(PlusTest, Sum) {
    std::string str = "100 154 +";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 254);
}

//Minus

TEST(MinusTest, Sub) {
    std::string str = "100 154 -";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), -54);
}

//Mul

TEST(MulTest, Mul) {
    std::string str = "100 154 *";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 15400);
}

//Dev

/**
 * 1. / 0
 * 2. empty stack
 * 3. 1 element
 * 4. round down
 * 5. just division
 */

// CR:
//TEST(DivTest, Regular) {
//    std::string str = "100 154 /";
//    Interpreter &i = Interpreter::getInstance();
//    i.interpret(str.cbegin(), str.cend());
//    str = ".";
//    std::string res = i.interpret(str.cbegin(), str.cend());
//    // EXPECT...
//}

TEST(DevTest, Dev1) {
    std::string str = "100 154 /";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 0);
}

TEST(DevTest, Dev2) {
    std::string str = "356 100 /";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 3);
}

//Mod

TEST(ModTest, ModLess) {
    std::string str = "100 154 mod";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 100);
}

TEST(ModTest, ModGreater) {
    std::string str = "154 100 mod";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 54);
}

//Equal

TEST(EqualTest, Eq) {
    std::string str = "100 154 =";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 0);
}

TEST(EqualTest, NotEq) {
    std::string str = "100 100 =";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 1);
}

//Less

TEST(LessTest, Less) {
    std::string str = "100 154 <";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 1);
}

TEST(LessTest, NotLess) {
    std::string str = "198 100 <";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 0);
}

//Greater

TEST(GreaterTest, Greater) {
    std::string str = "100 154 >";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 0);
}

TEST(GreaterTest, NotGreater) {
    std::string str = "128 100 >";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 1);
}

//Dup

TEST(DupTest, Dup) {
    std::string str = "100 154 453 dup";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 453);
    it.pop();
    EXPECT_EQ(it.top(), 453);
}

//Drop

TEST(DropTest, Drop) {
    std::string str = "100 154 453 drop";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 154);
}

//Print

TEST(PrintTest, Print) {
    std::string str = "100 154 453 .";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 154);
}

//Emit

TEST(EmitTest, Emit) {
    std::string str = "100 154 65 emit";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 154);
}

//Swap

TEST(SwapTest, Swap) {
    std::string str = "100 154 65 swap";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 154);
    it.pop();
    EXPECT_EQ(it.top(), 65);
}

//Rot

TEST(RotTest, Rot) {
    std::string str = "100 154 65 87 rot";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 65);
    it.pop();
    EXPECT_EQ(it.top(), 154);
    it.pop();
    EXPECT_EQ(it.top(), 87);
}

//Over

TEST(OverTest, Over) {
    std::string str = "100 154 65 87 over";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 65);
    it.pop();
    EXPECT_EQ(it.top(), 87);
    it.pop();
    EXPECT_EQ(it.top(), 65);
}

//If

TEST(IfTest, FalseStatement) {
    std::string str = "1 2 = if 10 8 + then;";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 0);
}

TEST(IfTest, FalseStatementWithElse) {
    std::string str = "1 2 = if 10 8 + else 10 6 + then;";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 16);
}

TEST(IfTest, TrueStatement) {
    std::string str = "4 4 = if 10 8 + then;";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 18);
}

TEST(IfTest, TrueStatementWithElse) {
    std::string str = "4 4 = if 10 8 + else 10 6 + then;";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    auto it = *i;
    EXPECT_EQ(it.top(), 18);
}