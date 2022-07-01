#include <iostream>

#include "FileReceivingServer.h"

int main (int argc, char** argv)
{
    try
    {
        auto app = std::make_unique<FileReceivingServer>();
        app->run();
    }
    catch(const std::exception& ex)
    {
        std::cout << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}