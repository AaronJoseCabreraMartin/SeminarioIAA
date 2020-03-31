#!/bin/sh
echo "compiling"


gcc ../lib/NeticaEx.o   BotG4.c            -o BotG4              -I../src -L../lib -lnetica -lstdc++ -lrt -lm -lpthread

echo "-----------------------------------   BuildNet"
gcc ../lib/NeticaEx.o   BuildNet.c        -o BuildNet          -I../src -L../lib   -lnetica   -lstdc++ -lrt -lm -lpthread

echo "-----------------------------------   DoInference"
gcc ../lib/NeticaEx.o   DoInference.c    -o  DoInference       -I../src -L../lib   -lnetica   -lstdc++ -lrt -lm -lpthread

echo "-----------------------------------   SimulateCases"
gcc ../lib/NeticaEx.o   SimulateCases.c  -o  SimulateCases     -I../src -L../lib   -lnetica   -lstdc++ -lrt -lm -lpthread

echo "-----------------------------------   LearnCPTs"
gcc ../lib/NeticaEx.o   LearnCPTs.c      -o  LearnCPTs         -I../src -L../lib   -lnetica   -lstdc++ -lrt -lm -lpthread

echo "-----------------------------------   LearnLatent"
gcc ../lib/NeticaEx.o   LearnLatent.c    -o  LearnLatent       -I../src -L../lib   -lnetica   -lstdc++ -lrt -lm -lpthread

echo "-----------------------------------   NetTester"
gcc  ../lib/NeticaEx.o  NetTester.c      -o  NetTester         -I../src -L../lib   -lnetica   -lstdc++ -lrt -lm -lpthread

echo "-----------------------------------   MakeDecision"
gcc  ../lib/NeticaEx.o  MakeDecision.c   -o  MakeDecision      -I../src -L../lib   -lnetica   -lstdc++ -lrt -lm -lpthread

echo "-----------------------------------   ClassifyData"
gcc  ../lib/NeticaEx.o  ClassifyData.c   -o  ClassifyData      -I../src -L../lib   -lnetica   -lstdc++ -lrt -lm -lpthread

