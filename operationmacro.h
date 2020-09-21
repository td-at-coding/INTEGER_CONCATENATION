#include "concatnumbers.h"

#define NOT_0 1
#define NOT_1 0

#define NOT1(X) NOT_##X
#define NOT(X) NOT1(X)

#define AND_0_0 0
#define AND_0_1 0
#define AND_1_0 0
#define AND_1_1 1

#define AND1(X,Y) AND_##X##_##Y
#define AND(X,Y) AND1(X,Y)

#define NAND1(X,Y) NOT(AND_##X##_##Y)
#define NAND(X,Y) NAND1(X,Y)

#define OR_0_0 0
#define OR_0_1 1
#define OR_1_0 1
#define OR_1_1 1

#define OR1(X,Y) OR_##X##_##Y
#define OR(X,Y) OR1(X,Y)

#define NOR1(X,Y) NOT(OR_##X##_##Y)
#define NOR(X,Y) NOR1(X,Y)

#define XOR_0_0 0
#define XOR_0_1 1
#define XOR_1_0 1
#define XOR_1_1 0

#define XOR1(X,Y) XOR_##X##_##Y
#define XOR(X,Y) XOR1(X,Y)

#define XNOR1(X,Y) NOT(XOR_##X##_##Y)
#define XNOR(X,Y) XNOR1(X,Y)

#define _NUM1(X1,X2,X3,X4,X5,X6,X7,X8) NUM##X1##X2##X3##X4##X5##X6##X7##X8
#define _NUM(X1,X2,X3,X4,X5,X6,X7,X8)  _NUM1(X1,X2,X3,X4,X5,X6,X7,X8)

#define ADD_NUM1(X1,X2,X3,X4,X5,X6,X7,X8,Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8) \
    XOR(XOR(X1,Y1),AND(X2,Y2)), \
    XOR(XOR(X2,Y2),AND(X3,Y3)), \
    XOR(XOR(X3,Y3),AND(X4,Y4)), \
    XOR(XOR(X4,Y4),AND(X5,Y5)), \
    XOR(XOR(X5,Y5),AND(X6,Y6)), \
    XOR(XOR(X6,Y6),AND(X7,Y7)), \
    XOR(XOR(X7,Y7),AND(X8,Y8)), \
    XOR(X8,Y8)

#define ADD_NUM(X1,X2,X3,X4,Y1,Y2,Y3,Y4) ADD_NUM1(X1,X2,X3,X4,Y1,Y2,Y3,Y4)

#define ADD1(X1,X2,X3,X4,X5,X6,X7,X8,Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8) \
_NUM( \
    XOR(XOR(X1,Y1),AND(X2,Y2)), \
    XOR(XOR(X2,Y2),AND(X3,Y3)), \
    XOR(XOR(X3,Y3),AND(X4,Y4)), \
    XOR(XOR(X4,Y4),AND(X5,Y5)), \
    XOR(XOR(X5,Y5),AND(X6,Y6)), \
    XOR(XOR(X6,Y6),AND(X7,Y7)), \
    XOR(XOR(X7,Y7),AND(X8,Y8)), \
    XOR(X8,Y8) \
)

#define ADD(X1,X2,X3,X4,X5,X6,X7,X8,Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8) ADD1(X1,X2,X3,X4,X5,X6,X7,X8,Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8)

#define SUB5(X1,X2,X3,X4,X5,X6,X7,X8,Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8) ADD(X1,X2,X3,X4,X5,X6,X7,X8,Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8)
#define SUB4(X1,X2,X3,X4,X5,X6,X7,X8,Y) SUB5(X1,X2,X3,X4,X5,X6,X7,X8,Y)
#define SUB2(X1,X2,X3,X4,X5,X6,X7,X8,Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8) SUB4(X1,X2,X3,X4,X5,X6,X7,X8,ADD_NUM(0,0,0,0,0,0,0,1,Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8))
#define SUB1(X1,X2,X3,X4,X5,X6,X7,X8,Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8) SUB2(X1,X2,X3,X4,X5,X6,X7,X8,NOT(Y1),NOT(Y2),NOT(Y3),NOT(Y4),NOT(Y5),NOT(Y6),NOT(Y7),NOT(Y8))
#define SUB(X1,X2,X3,X4,X5,X6,X7,X8,Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8) SUB1(X1,X2,X3,X4,X5,X6,X7,X8,Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8)

#define ADDINT2(X,Y) ADD(X,Y)
#define ADDINT1(X,Y) ADDINT2(INT##X,INT##Y)
#define ADDINT(X,Y) ADDINT1(X,Y)

#define SUBINT2(X,Y) SUB(X,Y)
#define SUBINT1(X,Y) SUBINT2(INT##X,INT##Y)
#define SUBINT(X,Y) SUBINT1(X,Y)

#define LIST41(X1,X2,X3,X4,X5,X6,X7,X8) #X1 #X2 #X3 #X4 #X5 #X6 #X7 #X8
#define LIST4(X1,X2,X3,X4,X5,X6,X7,X8) LIST41(X1,X2,X3,X4,X5,X6,X7,X8)
#define LIST1(X) LIST4(X) 

#define NOT_LIST11(X1,X2,X3,X4,X5,X6,X7,X8) NOT(X1),NOT(X2),NOT(X3),NOT(X4),NOT(X5),NOT(X6),NOT(X7),NOT(X8)
#define NOT_LIST1(X) NOT_LIST11(X)

#define INC_LIST1(X1,X2,X3,X4,X5,X6,X7,X8) ADD_NUM(0,0,0,0,0,0,0,1,X1,X2,X3,X4,X5,X6,X7,X8)
#define INC_LIST(X) INC_LIST1(X)

#define ADD2_LIST1(X1,X2,X3,X4,Y1,Y2,Y3,Y4) ADD_NUM(X1,X2,X3,X4,Y1,Y2,Y3,Y4)
#define ADD2_LIST(X,Y) ADD2_LIST1(X,Y)