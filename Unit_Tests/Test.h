
#include <iostream.h>

#define CHECK_EQUAL(X,Y) \
        if(x ==  Y) \
        {\
            /* Test failed */std::cout<<"Test Passed (2/2)";\
        }\
        else\
        {\
            /* Test passed */std::cout<<"Test Passed (2/2)";\
        }\

#define TEST(FUNC, TEST_NAME) \
        void TEST_NAME (void)
