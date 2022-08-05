#include <iostream>
#include <chrono>

class DesignNumber
{
public:
 DesignNumber(){} // Default constructor
 ~DesignNumber(){} // Default destructor
 int getIterationNumber()
 {
     return m_designNum++;
 }
 static int getSth(int in)
 {
     return ++in;
 }

 static int m_designNum2;
 const static int m_designConst = 4; // const static member variable is initialized while declaration.

private:
 static int m_designNum;

};

// This is the correct way of defining/initializing non-const static member variable: 1. Outside the class, 2. within the namespace scope of the class:
int DesignNumber::m_designNum = 10;
int DesignNumber::m_designNum2 = 20;

int main()
{
    DesignNumber first, second, third;

    std::cout<<first.getIterationNumber()<<std::endl; // ptints 10
    std::cout<<second.getIterationNumber()<<std::endl; // ptints 11
    std::cout<<third.getIterationNumber()<<std::endl; // ptints 12

    std::cout<<DesignNumber::m_designNum2++<<std::endl; // ptints 20
    std::cout<<DesignNumber::m_designNum2++<<std::endl; // ptints 21
    std::cout<<DesignNumber::m_designNum2++<<std::endl; // ptints 22

    std::cout<<DesignNumber::m_designConst<<std::endl; // ptints 4

    std::cout<<DesignNumber::getSth(5)<<std::endl; // ptints 6
    std::cout<<DesignNumber::getSth(11)<<std::endl; // ptints 12
    return 0;
}
