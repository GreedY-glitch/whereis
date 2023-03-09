#include <iostream>
#include <filesystem>
#include <string>


/* Псевдоним для std::filesystem */
namespace fs = std::filesystem;

enum Errors { NO_EXPECTED_ARGUMENT = 0xA };

/* Реализация проверки синтаксиса */
bool check_syntax(auto f) { return f; }



int main(int argc, char** argv)
{
    bool check_correct = false;
    /* Проверка синтаксиса командной строки */
    auto syntax_func = [&check_correct, &argc]() noexcept -> bool
    {
        if (argc == 1) {
           return check_correct;
        }
        else if (argc == 2) {
            check_correct = true;
            return check_correct;
        }
        return check_correct;
    };

    const fs::path search{argv[1]};



    /* Если синтаксис корректен */
    if (check_syntax(syntax_func()) /* && fs::exists(search) */) 
    {      
        /* Флаг еще не посещенных директорий */
        bool flag_visit = false;



        /* Перебор всех директорий, начиная от папки home */
        for (auto const& dir_entry :
            fs::recursive_directory_iterator("/usr"))
        {
            std::string last_name = search.filename();
            if ((dir_entry.path().filename() == last_name) 
                && !flag_visit) 
            {
                std::cout << argv[1] << ": ";
                std::cout << dir_entry << std::endl;
                flag_visit = true;

                break;
            }
            else
                continue;
        }

        if (!flag_visit)
            std::cout << argv[1] << ":\n";
    }
    else {

        std::cerr << "NO EXPECTED ARGUMENT!\n";
        exit(NO_EXPECTED_ARGUMENT);
    }

    return EXIT_SUCCESS;
}