#include "input_handler.h"
#include <sstream>
#include <cctype>

void InputHandler::ShowPrompt(const std::string& prompt, const std::string& format_hint) {
    if (!format_hint.empty()) {
        std::cout << "Format: " << format_hint << "\n";
    }
    std::cout << (prompt.empty() ? "> " : prompt);
}

std::string InputHandler::GetTrimmedInput() {
    std::string input;
    if (!std::getline(std::cin, input)) {
        return "";
    }

    // Удаляем пробелы
    input.erase(input.begin(), std::find_if(input.begin(), input.end(), [](int ch) {
        return !std::isspace(ch);
    }));
    input.erase(std::find_if(input.rbegin(), input.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), input.end());

    return input;
}

bool InputHandler::GetInt(int* out, const NumericInputConfig<int>& config) {
    if (out == nullptr) {
        return false;
    }

    while (true) {
        ShowPrompt(config.prompt, config.format_hint);
        std::string input = GetTrimmedInput();

        if (input.empty()) {
            std::cerr << "Input cannot be empty.\n";
            continue;
        }

        std::istringstream iss(input);
        int value;
        iss >> value;

        if (iss.fail() || !iss.eof()) {
            std::cerr << (config.error_msg.empty() ? "Invalid integer input." : config.error_msg) << "\n";
            continue;
        }

        if (config.min.has_value() && value < *config.min) {
            std::cerr << (config.error_msg.empty()
                          ? "Value must be >= " + std::to_string(*config.min)
                          : config.error_msg) << "\n";
            continue;
        }

        if (config.max.has_value() && value > *config.max) {
            std::cerr << (config.error_msg.empty()
                          ? "Value must be <= " + std::to_string(*config.max)
                          : config.error_msg) << "\n";
            continue;
        }

        if (!config.allowed_values.empty() &&
            std::find(config.allowed_values.begin(), config.allowed_values.end(), value)
            == config.allowed_values.end()) {
            std::cerr << "Allowed values: ";
            for (const auto& v : config.allowed_values) {
                std::cerr << v << " ";
            }
            std::cerr << "\n";
            continue;
        }

        *out = value;
        return true;
    }
}

bool InputHandler::GetDouble(double* out, const NumericInputConfig<double>& config) {
    if (out == nullptr) {
        return false;
    }

    while (true) {
        ShowPrompt(config.prompt, config.format_hint);
        std::string input = GetTrimmedInput();

        if (input.empty()) {
            std::cerr << "Input cannot be empty.\n";
            continue;
        }

        std::istringstream iss(input);
        double value;
        iss >> value;

        if (iss.fail() || !iss.eof()) {
            std::cerr << (config.error_msg.empty() ? "Invalid number input." : config.error_msg) << "\n";
            continue;
        }

        if (config.min.has_value() && value < *config.min) {
            std::cerr << (config.error_msg.empty()
                          ? "Value must be >= " + std::to_string(*config.min)
                          : config.error_msg) << "\n";
            continue;
        }

        if (config.max.has_value() && value > *config.max) {
            std::cerr << (config.error_msg.empty()
                          ? "Value must be <= " + std::to_string(*config.max)
                          : config.error_msg) << "\n";
            continue;
        }

        if (!config.allowed_values.empty() &&
            std::find(config.allowed_values.begin(), config.allowed_values.end(), value)
            == config.allowed_values.end()) {
            std::cerr << "Allowed values: ";
            for (const auto& v : config.allowed_values) {
                std::cerr << v << " ";
            }
            std::cerr << "\n";
            continue;
        }

        *out = value;
        return true;
    }
}

bool InputHandler::GetString(std::string* out, const StringInputConfig& config) {
    if (out == nullptr) {
        return false;
    }

    while (true) {
        ShowPrompt(config.prompt, config.format_hint);
        std::string input = GetTrimmedInput();

        if (input.empty() && config.min_length.has_value() && *config.min_length > 0) {
            std::cerr << "Input cannot be empty.\n";
            continue;
        }

        if (config.min_length.has_value() && input.length() < *config.min_length) {
            std::cerr << (config.error_msg.empty()
                          ? "Input must be at least " + std::to_string(*config.min_length) + " characters."
                          : config.error_msg) << "\n";
            continue;
        }

        if (config.max_length.has_value() && input.length() > *config.max_length) {
            std::cerr << (config.error_msg.empty()
                          ? "Input must be no more than " + std::to_string(*config.max_length) + " characters."
                          : config.error_msg) << "\n";
            continue;
        }

        if (!config.allowed_values.empty() &&
            std::find(config.allowed_values.begin(), config.allowed_values.end(), input)
            == config.allowed_values.end()) {
            std::cerr << "Allowed values: ";
            for (const auto& v : config.allowed_values) {
                std::cerr << v << " ";
            }
            std::cerr << "\n";
            continue;
        }

        *out = input;
        return true;
    }
}

bool InputHandler::GetBool(bool* out, const std::string& prompt) {
    if (out == nullptr) {
        return false;
    }

    while (true) {
        ShowPrompt(prompt.empty() ? "Enter [y/n]: " : prompt);
        std::string input = GetTrimmedInput();
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "y" || input == "yes" || input == "1" || input == "true") {
            *out = true;
            return true;
        }
        if (input == "n" || input == "no" || input == "0" || input == "false") {
            *out = false;
            return true;
        }

        std::cerr << "Please enter 'y' or 'n'.\n";
    }
}