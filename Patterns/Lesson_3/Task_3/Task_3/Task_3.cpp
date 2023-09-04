#include <iostream>
#include <windows.h>
#include "pushHandler.h"
#include "handlers.h"
#include "messagers.h"






int main(){

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru-RU.1251");

    auto unknown_handler = std::make_unique<UnknownHandler>(nullptr);
    auto warning_handler = std::make_unique<WarningHandler>(std::move(unknown_handler));
    auto error_handler = std::make_unique<ErrorHandler>(std::move(warning_handler));
    auto fatalerror_handler = std::make_unique<FatalErrorHandler>(std::move(error_handler));
    
    try {
        fatalerror_handler->receivePush(WarningMessage());
        fatalerror_handler->receivePush(ErrorMessage());
        fatalerror_handler->receivePush(FatallErrorMessage());
        fatalerror_handler->receivePush(UnknownErrorMessage());
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}