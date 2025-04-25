#include <iostream>
#include "handlers/input/input_handler.h"

int main() {
    setlocale(LC_ALL, "Russian");


    // Пример 1: Ввод возраста (18-99)
    int age = 18;
    NumericInputConfig<int> age_config;
    age_config.prompt = "Enter age (18-99): ";
    age_config.min = 18;
    age_config.max = 99;
    age_config.error_msg = "Age must be between 18 and 99";

    if (InputHandler::GetInt(&age, age_config)) {
        std::cout << "Your age: " << age << "\n";
    }

    // Пример 2: Ввод положительного числа
    double amount = 0.;
    NumericInputConfig<double> amount_config;
    amount_config.prompt = "Enter model temperature (0.01 <= n <= 2): ";
    amount_config.min = 0.01;
    amount_config.max = 2;
    amount_config.error_msg = "Temperature value must be (0.01 <= n <= 2)";

    if (InputHandler::GetDouble(&amount, amount_config)) {
        std::cout << "Temperature: " << amount << "\n";
    }

    // Пример 3: Ввод имени (2-50 символов)
    std::string name = "World";
    StringInputConfig name_config;
    name_config.prompt = "Enter name: ";
    name_config.min_length = 2;
    name_config.max_length = 50;
    name_config.error_msg = "Name is too long, don't try to include all your relatives' names";

    if (InputHandler::GetString(&name, name_config)) {
        std::cout << "Hello, " << name << "!\n";
    }

    // Пример 4: Выбор из списка
    std::string color = "red";
    StringInputConfig color_config;
    color_config.prompt = "Choose color (red/green/blue): ";
    color_config.allowed_values = {"red", "green", "blue"};
    color_config.error_msg = "Invalid choice";

    if (InputHandler::GetString(&color, color_config)) {
        std::cout << "Selected color: " << color << "\n";
    }

    // Пример 5: Ввод подтверждения (да/нет)
    bool confirm = false;
    if (InputHandler::GetBool(&confirm, "Are you sure you want to download the file? (y/n): ")) {
        std::cout << "Confirmation: " << (confirm ? "YES" : "NO") << "\n";
    }

    return 0;
}