#include <gtest/gtest.h>
#include "interpreter.h"
#include "commands.h"

//interpret

TEST(InterpretTest, WriteDigits) {
    std::string str = "985 4598 938 293 . . . .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.begin(), str.cend()).value() == "2939384598985");
}

TEST(InterpretTest, UnexistedCommand) {
    std::string str = "985 4598 give";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.begin(), str.cend()).error() == "no such command : 'give'");
}
//Plus

TEST(PlusTest, Sum) {
    std::string str = "100 154 + .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "254");
}

TEST(PlusTest, SumNegatives) {
    std::string str = "-100 154 + .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "54");
}

TEST(PlusTest, EmptyStack) {
    std::string str = "+";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(PlusTest, ExpectedSize) {
    std::string str = "1 +";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 1 elements, expected 2 for 'binary operation'");
}

//Minus

TEST(MinusTest, NegativeResult) {
    std::string str = "100 154 - .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "-54");
}

TEST(MinusTest, PositiveResult) {
    std::string str = "200 154 - .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "46");
}

TEST(MinusTest, SubNegatives) {
    std::string str = "-200 154 - . drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "-354");
}

TEST(MinusTest, EmptyStack) {
    std::string str = "-";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(MinusTest, ExpectedSize) {
    std::string str = "1 -";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 1 elements, expected 2 for 'binary operation'");
}

//Mul

TEST(MulTest, Mul) {
    std::string str = "100 154 * .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "15400");
}

TEST(MulTest, MulNegatives) {
    std::string str = "100 -154 * . drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "-15400");
}

TEST(MulTest, EmptyStack) {
    std::string str = "*";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(MulTest, ExpectedSize) {
    std::string str = "1 * drop";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 1 elements, expected 2 for 'binary operation'");
}

//Div

TEST(DivTest, Div1) {
    std::string str = "100 154 / .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(DivTest, Div2) {
    std::string str = "1000 154 / .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "6");
}

TEST(DivTest, DivNegatives) {
    std::string str = "-1000 154 / . drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "-6");
}

TEST(DivTest, EmptyStack) {
    std::string str = "/";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(DivTest, ExpectedSize) {
    std::string str = "1 /";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 1 elements, expected 2 for 'binary operation'");
}

TEST(DivTest, DivByZero) {
    std::string str = "1 0 /";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() == "division by zero");
}

//Mod

TEST(ModTest, Mod1) {
    std::string str = "100 154 mod .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "100");
}

TEST(ModTest, Mod2) {
    std::string str = "160 154 mod .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "6");
}

TEST(ModTest, Mod3) {
    std::string str = "154 154 mod . drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(ModTest, EmptyStack) {
    std::string str = "mod";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(ModTest, ExpectedSize) {
    std::string str = "1 mod";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 1 elements, expected 2 for 'binary operation'");
}

//Equal

TEST(EqualTest, Equal) {
    std::string str = "160 160 = .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "1");
}

TEST(EqualTest, EqualNegatives) {
    std::string str = "-160 -160 = .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "1");
}

TEST(EqualTest, NoEqualNegatives) {
    std::string str = "-160 160 = .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(EqualTest, NotEqual) {
    std::string str = "154 1 mod . drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(EqualTest, EmptyStack) {
    std::string str = "=";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(EqualTest, ExpectedSize) {
    std::string str = "1 =";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 1 elements, expected 2 for 'binary operation'");
}

//Less

TEST(LessTest, Less) {
    std::string str = "159 160 < .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "1");
}

TEST(LessTest, LessNegatives) {
    std::string str = "-159 160 < .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "1");
}

TEST(LessTest, NotLess1) {
    std::string str = "154 1 < .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(LessTest, NotLess2) {
    std::string str = "1 1 < . drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(LessTest, EmptyStack) {
    std::string str = "<";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(LessTest, ExpectedSize) {
    std::string str = "1 <";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 1 elements, expected 2 for 'binary operation'");
}

//Greater

TEST(GreaterTest, Greater) {
    std::string str = "178 160 > .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "1");
}

TEST(GreaterTest, GreaterNegatives) {
    std::string str = "-178 160 > .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(GreaterTest, NotGreater1) {
    std::string str = "154 1888 > .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(GreaterTest, NotGreater2) {
    std::string str = "1 1 > . drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "0");
}

TEST(GreaterTest, EmptyStack) {
    std::string str = ">";
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 0 elements, expected 2 for 'binary operation'");
}

TEST(GreaterTest, ExpectedSize) {
    std::string str = "1 >";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(
            Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
            "stack has 1 elements, expected 2 for 'binary operation'");
}

//Dup

TEST(DupTest, Dup) {
    std::string str = "100 154 453 dup . cr . drop drop drop";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "453\n453");
}

TEST(DupTest, ExpectedSize) {
    std::string str = "dup";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 1 for 'dup'");
}

//Drop

TEST(DropTest, Drop) {
    std::string str = "100 154 453 drop .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "154");
}

TEST(DropTest, ExpectedSize) {
    std::string str = "drop drop drop";
    Interpreter &i = Interpreter::getInstance();
    EXPECT_TRUE(i.interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 1 for 'drop'");
}

//Print

TEST(PrintTest, Print) {
    std::string str = "100 154 453 .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "453");
    str = ". drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "154");
}

TEST(PrintTest, ExpectedSize) {
    std::string str = ".";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
                "stack has 0 elements, expected 1 for '.'");
}

//Emit

TEST(EmitTest, Emit) {
    std::string str = "100 154 65 emit";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()) == "A");
    str = ". drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "154");
}

TEST(EmitTest, ExpectedSize) {
    std::string str = "emit";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
                "stack has 0 elements, expected 1 for 'emit'");
}

//Swap

TEST(SwapTest, Swap) {
    std::string str = "100 154 65 swap . cr . drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()) == "154\n65");
}

TEST(SwapTest, ExpectedSize1) {
    std::string str = "swap";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
                "stack has 0 elements, expected 2 for 'swap'");
}

TEST(SwapTest, ExpectedSize2) {
    std::string str = "1 swap";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
                "stack has 1 elements, expected 2 for 'swap'");
}

//Rot

TEST(RotTest, Rot) {
    std::string str = "154 65 87 rot . cr . cr . drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()) == "65\n154\n87");
}

TEST(RotTest, ExpectedSize1) {
    std::string str = "rot";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
                "stack has 0 elements, expected 3 for 'rot'");
}

TEST(RotTest, ExpectedSize2) {
    std::string str = "5 rot";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
                "stack has 1 elements, expected 3 for 'rot'");
}

TEST(RotTest, ExpectedSize3) {
    std::string str = "drop 9 5 rot";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
                "stack has 2 elements, expected 3 for 'rot'");
}

//Over

TEST(OverTest, Over) {
    std::string str = "100 154 65 87 over . cr . cr . drop drop drop drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "65\n87\n65");
}

TEST(OverTest, ExpectedSize1) {
    std::string str = "over";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
                "stack has 0 elements, expected 2 for 'over'");
}

TEST(OverTest, ExpectedSize2) {
    std::string str = "1 over";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
                "stack has 1 elements, expected 2 for 'over'");
}

//Cr

TEST(CrTest, EmptyStack) {
    std::string str = "drop cr";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "\n");
}

TEST(CrTest, Cr) {
    std::string str = "56 87 . cr .";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "87\n56");
}

//PrintString

TEST(PrintStringTest, PrintingString1) {
    std::string str = ".\" 98989\"";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "98989");
}

TEST(PrintStringTest, PrintingString2) {
    std::string str = ".\" abcdef\"";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "abcdef");
}

TEST(PrintStringTest, PrintingString3) {
    std::string str = ".\" abc def\"";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "abc def");
}

TEST(PrintStringTest, NoClosingQuote) {
    std::string str = ".\" abcdef";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
                "no closing quotation mark for printing string");
}

TEST(PrintStringTest, NoSpace) {
    std::string str = ".\"";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() ==
                "no closing quotation mark for printing string");
}

TEST(PrintStringTest, NoSuchCommand) {
    std::string str = "f.\"";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() == "no such command : 'f.\"'");
}

//If

TEST(IfTest, OnlyThenBranch1) {
    std::string str = "0 if 67 . then ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value().empty() == 1);
}

TEST(IfTest, OnlyThenBranch2) {
    std::string str = "drop 1 if 67 . then ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "67");
}

TEST(IfTest, ElseBranch1) {
    std::string str = "drop 0 if 67 . else 89 . then ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "89");
}

TEST(IfTest, ElseBranch2) {
    std::string str = "drop 1 if 67 . else 78 . then ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "67");
}

TEST(IfTest, NestedIf1) {
    std::string str = "drop 0 if 1 if 43 . then ; 67 . else 89 . then ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "89");
}

TEST(IfTest, NestedIf2) {
    std::string str = "drop 1 if 1 if 43 . then ; 67 . else 78 . then ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "4367");
}

TEST(IfTest, NestedIf3) {
    std::string str = "drop drop 0 if 67 . else 89 . 1 if 43 . then ; then ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "8943");
}

TEST(IfTest, NestedIf4) {
    std::string str = "drop drop 1 if 1 if 43 . then ; 67 . else 78 . 1 if 45 . then ; then ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "4367");
}

TEST(IfTest, NestedIf5) {
    std::string str = "drop drop 1 if 0 if 43 . else 832 . then ; 67 . else 78 . 1 if 45 . then ; then ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "83267");
}

TEST(IfTest, NoColon1) {
    std::string str = "drop drop 1 if 0 if 43 . else 832 then . 67 . else 78 . 1 if 45 . then ; then ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() == "no ';' for 'if'");
}

TEST(IfTest, NoColon2) {
    std::string str = "drop drop 1 if 0 if 43 . else 832 then ; . 67 . else 78 . 1 if 45 . then ; then";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() == "no ';' for 'if'");
}

TEST(IfTest, NoThen) {
    std::string str = " 1 if 0 if 43 . else 832 then ; . 67 . else 78 . 1 if 45 . then ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() == "no 'then' for 'if'");
}

TEST(IfTest, ExpectedSize) {
    std::string str = "drop drop if 78 . then ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 1 for 'if'");
}

//Loop

TEST(LoopTest, PrintingNumbers) {
    std::string str = "10 0 do i . loop ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "0123456789");
}

TEST(LoopTest, LoopInIf) {
    std::string str = "1 if 10 0 do i . loop ; then ; drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "0123456789");
}

TEST(LoopTest, LoopOutIf) {
    std::string str = "10 0 do i 1 = if i . then ; loop ; drop drop drop drop drop drop drop drop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "1");
}

TEST(LoopTest, NoColon1) {
    std::string str = "10 0 do i 1 = if i . then ; loop";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() == "no ';' for 'loop'");
}

TEST(LoopTest, NoColon2) {
    std::string str = "10 0 do i . 12 11 do i . loop loop ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() == "no ';' for 'loop'");
}

TEST(LoopTest, NoLoop) {
    std::string str = "10 0 do i . 12 11 do i . loop ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() == "no 'loop' for 'do'");
}

TEST(LoopTest, ExpectedSize1) {
    std::string str = "drop drop do i 78 . loop ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() == "stack has 0 elements, expected 2 for 'loop'");
}

TEST(LoopTest, ExpectedSize2) {
    std::string str = "1 do i 78 . loop ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).error() == "stack has 1 elements, expected 2 for 'loop'");
}

TEST(LoopTest, NestedLoop) {
    std::string str = "10 0 do i . 12 11 do i . loop ; loop ;";
    EXPECT_TRUE(Interpreter::getInstance().interpret(str.cbegin(), str.cend()).value() == "011111211311411511611711811911");
}