#include "LucidControl.h"

#ifdef _WIN32
    #define OS_NAME "Windows"
#elif __APPLE__
    #define OS_NAME "macOS"
#else
    #define OS_NAME "UNKNOWN"
#endif

// Routes to Lucid actions according to the command given

void LucidControl::CLI(std::string option, AccountManager &db)
{
    if ((std::strcmp(option.c_str(), "a") == 0) || (std::strcmp(option.c_str(), "add") == 0))
    {
        LucidControl::add(db);
    }
    else if ((std::strcmp(option.c_str(), "rm") == 0) || (std::strcmp(option.c_str(), "remove") == 0))
    {
        LucidControl::remove(db);
    }
    else if ((std::strcmp(option.c_str(), "u") == 0) || (std::strcmp(option.c_str(), "update") == 0))
    {
        LucidControl::update(db);
    }
    else if ((std::strcmp(option.c_str(), "l") == 0) || (std::strcmp(option.c_str(), "list") == 0))
    {
        LucidControl::list(db);
    }
    else if (std::strcmp(option.c_str(), "wipe") == 0)
    {
        // LucidControl::wipe(db);
    }
    else if (std::strcmp(option.c_str(), "about") == 0)
    {

    }
    else if (std::strcmp(option.c_str(), "version") == 0 || (std::strcmp(option.c_str(), "v") == 0))
    {
        LucidControl::version();
    }
    else if (std::strcmp(option.c_str(), "usage") == 0)
    {
        LucidControl::displayCommands();
    }
    else
    {
        std::cout << "Unknown command..." << std::endl;
    }
}

// Displays all options

void LucidControl::displayCommands()
{
    printf("Usage: lucid [options]\n\n");
    printf("Options:\n");
    printf("-gui         Uses the Lucid GUI\n");
    printf("a  | add     Adds an account\n");
    printf("rm | remove  Removes an account\n");
    printf("u  | update  Updates an account\n");
    printf("l  | list    Lists all accounts\n");
    printf("about        Displays general information about the app\n");
    printf("version | v  Displays the current Lucid Version\n");
}

void LucidControl::displayAbout()
{
    
}

// Displays the current Lucid version shown in Globals.h

void LucidControl::version()
{
    printf("Lucid Version: %.1f\n", LucidGlobals::VERSION);
}

// Adds account to account list

void LucidControl::add(AccountManager &db)
{
    Account acc;

    std::cout << "Enter account name: ";
    std::getline(std::cin, acc.tag);

    std::cout << "Enter Username: ";
    std::getline(std::cin, acc.username);

    std::cout << "Enter Password: ";
    std::getline(std::cin, acc.password);

    db.add(acc);
}

// Removes account from account list

void LucidControl::remove(AccountManager &db)
{
    Account acc;

    std::cout << "Enter account name: ";
    std::getline(std::cin, acc.tag);

    std::cout << "Enter Username: ";
    std::getline(std::cin, acc.username);

    if (db.remove(acc))
    {
        printf("Account successfully removed...");
    }
    else
    {
        printf("Account does not exist...");
    }
}

// Updates account from account list

void LucidControl::update(AccountManager &db)
{
}

// Lists all accounts to terminal

void LucidControl::list(AccountManager &db)
{
    for (auto acc : db.data())
    {
        printf("Account Name: %s\nUsername: %s\nPassword: %s\n", acc.tag.c_str(), acc.username.c_str(), acc.password.c_str());
        printf("----------------------\n");
    }
}

// Wipes all accounts from the database

void LucidControl::wipe(AccountManager &db)
{
    db.clear();
}