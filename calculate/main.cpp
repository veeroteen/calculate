#include "utils.h"
#include "Calculator.h"
int main()
{
    Calculator cal;
    size_t size;
    std::cout << "enter size of C strin\n";
    std::cin >> size;

    while(true)
    {
        char* str = (char*)calloc(size, sizeof(char));
        std::cout << "enter string(enter 'e' to exit)\n";
        std::cin >> str;
        if(str[0] == 'e')
        {
            free(str);
            break;
        }
        try
        {
            std::cout << cal.calc(str) << std::endl;
        }
        catch(std::runtime_error& e)
        {
            cerr << "Caught: " << e.what() << endl;
            cerr << "Type: " << typeid(e).name() << endl;
        }
        free(str);
    }


    return 0;
}

