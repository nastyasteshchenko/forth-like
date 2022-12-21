#include <gtest/gtest.h>
#include "interpreter.h"
#include "commands.h"

//interpret

TEST(InterpretTest, WriteDigits) {
    std::string str = "985 4598 938 293 . . . .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.begin(), str.cend()).value() == "2939384598985");
}

TEST(InterpretTest, UnexistedCommand) {
    std::string str = "985 4598 give";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.begin(), str.cend()).error() == "no such command : 'give'");
}
//Plus

TEST(PlusTest, Sum) {
    std::string str = "100 154 + .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "254");
}

TEST(PlusTest, SumNegatives) {
    std::string str = "-100 154 + .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "54");
}

TEST(PlusTest, EmptyStack) {
    std::string str = "+";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(PlusTest, ExpectedSize) {
    std::string str = "1 +";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 1 elements, expected 2 for 'binary operation'");
    i.clearStack();
}

//Minus

TEST(MinusTest, NegativeResult) {
    std::string str = "100 154 - .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "-54");
}

TEST(MinusTest, PositiveResult) {
    std::string str = "200 154 - .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "46");
}

TEST(MinusTest, SubNegatives) {
    std::string str = "-200 154 - .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "-354");
}

TEST(MinusTest, EmptyStack) {
    std::string str = "-";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(MinusTest, ExpectedSize) {
    std::string str = "1 -";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 1 elements, expected 2 for 'binary operation'");
    i.clearStack();
}

//Mul

TEST(MulTest, Mul) {
    std::string str = "100 154 * .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "15400");
}

TEST(MulTest, MulNegatives) {
    std::string str = "100 -154 * .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "-15400");
}

TEST(MulTest, EmptyStack) {
    std::string str = "*";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(MulTest, ExpectedSize) {
    std::string str = "1 *";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 1 elements, expected 2 for 'binary operation'");
    i.clearStack();
}

//Div

TEST(DivTest, Div1) {
    std::string str = "100 154 / .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(DivTest, Div2) {
    std::string str = "1000 154 / .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "6");
}

TEST(DivTest, DivNegatives) {
    std::string str = "-1000 154 / .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "-6");
}

TEST(DivTest, EmptyStack) {
    std::string str = "/";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(DivTest, ExpectedSize) {
    std::string str = "1 /";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 1 elements, expected 2 for 'binary operation'");
}

TEST(DivTest, DivByZero) {
    std::string str = "1 0 /";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "division by zero");
    i.clearStack();
}

//Mod

TEST(ModTest, Mod1) {
    std::string str = "100 154 mod .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "100");
}

TEST(ModTest, Mod2) {
    std::string str = "160 154 mod .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "6");
}

TEST(ModTest, Mod3) {
    std::string str = "154 154 mod .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(ModTest, EmptyStack) {
    std::string str = "mod";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(ModTest, ExpectedSize) {
    std::string str = "1 mod";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 1 elements, expected 2 for 'binary operation'");
    i.clearStack();
}

//Equal

TEST(EqualTest, Equal) {
    std::string str = "160 160 = .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "1");
}

TEST(EqualTest, EqualNegatives) {
    std::string str = "-160 -160 = .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "1");
}

TEST(EqualTest, NoEqualNegatives) {
    std::string str = "-160 160 = .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(EqualTest, NotEqual) {
    std::string str = "154 1 mod .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(EqualTest, EmptyStack) {
    std::string str = "=";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(EqualTest, ExpectedSize) {
    std::string str = "1 =";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 1 elements, expected 2 for 'binary operation'");
    i.clearStack();
}

//Less

TEST(LessTest, Less) {
    std::string str = "159 160 < .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "1");
}

TEST(LessTest, LessNegatives) {
    std::string str = "-159 160 < .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "1");
}

TEST(LessTest, NotLess1) {
    std::string str = "154 1 < .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(LessTest, NotLess2) {
    std::string str = "1 1 < .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(LessTest, EmptyStack) {
    std::string str = "<";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(LessTest, ExpectedSize) {
    std::string str = "1 <";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 1 elements, expected 2 for 'binary operation'");
    i.clearStack();
}

//Greater

TEST(GreaterTest, Greater) {
    std::string str = "178 160 > .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "1");
}

TEST(GreaterTest, GreaterNegatives) {
    std::string str = "-178 160 > .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(GreaterTest, NotGreater1) {
    std::string str = "154 1888 > .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(GreaterTest, NotGreater2) {
    std::string str = "1 1 > .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(GreaterTest, EmptyStack) {
    std::string str = ">";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(GreaterTest, ExpectedSize) {
    std::string str = "1 >";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            i.interpret(str.cbegin(), str.cend()).error() == "stack has 1 elements, expected 2 for 'binary operation'");
    i.clearStack();
}

//Dup

TEST(DupTest, Dup) {
    std::string str = "100 154 453 dup . cr .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "453\n453");
    i.clearStack();
}

TEST(DupTest, ExpectedSize) {
    std::string str = "dup";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 1 for 'dup'");
    i.clearStack();
}

//Drop

TEST(DropTest, Drop) {
    std::string str = "100 154 453 drop .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "154");
    i.clearStack();
}

TEST(DropTest, ExpectedSize) {
    std::string str = "drop";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 1 for 'drop'");
    i.clearStack();
}

//Print

TEST(PrintTest, Print) {
    std::string str = "100 154 453 .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "453");
    str = ".";
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "154");
    i.clearStack();
}

TEST(PrintTest, ExpectedSize) {
    std::string str = ".";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 1 for '.'");
    i.clearStack();
}

//Emit

TEST(EmitTest, Emit) {
    std::string str = "100 154 65 emit";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()) == "A");
    str = ".";
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "154");
    i.clearStack();
}

TEST(EmitTest, ExpectedSize) {
    std::string str = "emit";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 1 for 'emit'");
    i.clearStack();
}

//Swap

TEST(SwapTest, Swap) {
    std::string str = "100 154 65 swap . cr .";
    Interpreter &i = Interpreter::getInstance();
    i.interpret(str.cbegin(), str.cend());
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()) == "154\n65");
    i.clearStack();
}

TEST(SwapTest, ExpectedSize1) {
    std::string str = "swap";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 2 for 'swap'");
    i.clearStack();
}

TEST(SwapTest, ExpectedSize2) {
    std::string str = "1 swap";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 1 elements, expected 2 for 'swap'");
    i.clearStack();
}

//Rot

TEST(RotTest, Rot) {
    std::string str = "154 65 87 rot . cr . cr .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()) == "65\n154\n87");
}

TEST(RotTest, ExpectedSize1) {
    std::string str = "rot";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 3 for 'rot'");
    i.clearStack();
}

TEST(RotTest, ExpectedSize2) {
    std::string str = "5 rot";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 1 elements, expected 3 for 'rot'");
    i.clearStack();
}

TEST(RotTest, ExpectedSize3) {
    std::string str = "9 5 rot";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 2 elements, expected 3 for 'rot'");
    i.clearStack();
}

//Over

TEST(OverTest, Over) {
    std::string str = "100 154 65 87 over . cr . cr .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "65\n87\n65");
    i.clearStack();
}

TEST(OverTest, ExpectedSize1) {
    std::string str = "over";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 2 for 'over'");
    i.clearStack();
}

TEST(OverTest, ExpectedSize2) {
    std::string str = "1 over";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 1 elements, expected 2 for 'over'");
    i.clearStack();
}

//Cr

TEST(CrTest, EmptyStack) {
    std::string str = "cr";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "\n");
    i.clearStack();
}

TEST(CrTest, Cr) {
    std::string str = "56 87 . cr .";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "87\n56");
    i.clearStack();
}

//PrintString

TEST(PrintStringTest, PrintingString1) {
    std::string str = ".\" 98989\"";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "98989");
    i.clearStack();
}

TEST(PrintStringTest, PrintingString2) {
    std::string str = ".\" abcdef\"";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "abcdef");
    i.clearStack();
}

TEST(PrintStringTest, PrintingString3) {
    std::string str = ".\" abc def\"";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "abc def");
    i.clearStack();
}

TEST(PrintStringTest, NoClosingQuote) {
    std::string str = ".\" abcdef";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "no closing quotation mark for printing string");
    i.clearStack();
}

TEST(PrintStringTest, NoSpace) {
    std::string str = ".\"";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "no space after '.\"'");
    i.clearStack();
}

//If

TEST(IfTest, OnlyThenBranch1) {
    std::string str = "0 if 67 . then ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value().empty() == 1);
    i.clearStack();
}

TEST(IfTest, OnlyThenBranch2) {
    std::string str = "1 if 67 . then ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "67");
    i.clearStack();
}

TEST(IfTest, ElseBranch1) {
    std::string str = "0 if 67 . else 89 . then ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "89");
    i.clearStack();
}

TEST(IfTest, ElseBranch2) {
    std::string str = "1 if 67 . else 78 . then ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "67");
    i.clearStack();
}

TEST(IfTest, NestedIf1) {
    std::string str = "0 if 1 if 43 . then ; 67 . else 89 . then ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "89");
    i.clearStack();
}

TEST(IfTest, NestedIf2) {
    std::string str = "1 if 1 if 43 . then ; 67 . else 78 . then ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "4367");
    i.clearStack();
}

TEST(IfTest, NestedIf3) {
    std::string str = "0 if 67 . else 89 . 1 if 43 . then ; then ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "8943");
    i.clearStack();
}

TEST(IfTest, NestedIf4) {
    std::string str = "1 if 1 if 43 . then ; 67 . else 78 . 1 if 45 . then ; then ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "4367");
    i.clearStack();
}

TEST(IfTest, NestedIf5) {
    std::string str = "1 if 0 if 43 . else 832 . then ; 67 . else 78 . 1 if 45 . then ; then ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "83267");
    i.clearStack();
}

TEST(IfTest, NoColon) {
    std::string str = "1 if 0 if 43 . else 832 then . 67 . else 78 . 1 if 45 . then ; then ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "no ';' for 'if'");
    i.clearStack();
}

TEST(IfTest, ExpectedSize) {
    std::string str = "if 78 . then ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 1 for 'if'");
    i.clearStack();
}

//Loop

TEST(LoopTest, PrintingNumbers) {
    std::string str = "10 0 do i . loop ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "0123456789");
    i.clearStack();
}

TEST(LoopTest, LoopInIf) {
    std::string str = "1 if 10 0 do i . loop ; then ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "0123456789");
    i.clearStack();
}

TEST(LoopTest, LoopOutIf) {
    std::string str = "10 0 do i 1 = if i . then ; loop ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).value() == "1");
    i.clearStack();
}

TEST(LoopTest, NoLoop) {
    std::string str = "10 0 do i 1 = if i . then ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "no 'loop ;' for 'loop'");
    i.clearStack();
}

TEST(LoopTest, ExpectedSize1) {
    std::string str = "do i 78 . loop ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 2 for 'loop'");
    i.clearStack();
}

TEST(LoopTest, ExpectedSize2) {
    std::string str = "1 do i 78 . loop ;";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 1 elements, expected 2 for 'loop'");
    i.clearStack();
}