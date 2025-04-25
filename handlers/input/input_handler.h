#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @struct StringInputConfig
 * @brief Конфигурация для валидации строкового ввода
 */
struct StringInputConfig {
    std::string prompt;                          ///< Текст-обращение к пользователю для ввода
    std::optional<size_t> min_length;            ///< Минимальная длина строки
    std::optional<size_t> max_length;            ///< Максимальная длина строки
    std::string error_msg;                       ///< Кастомное сообщение об ошибке
    std::string format_hint;                     ///< Подсказка по формату ввода
    std::vector<std::string> allowed_values;     ///< Список допустимых значений
};

/**
 * @struct NumericInputConfig
 * @brief Конфигурация для валидации числового ввода
 * @tparam T Числовой тип данных (int, double и т.д.)
 */
template <typename T>
struct NumericInputConfig {
    std::string prompt;             ///< Текст-обращение к пользователю для ввода
    std::optional<T> min;           ///< Минимальное допустимое значение
    std::optional<T> max;           ///< Максимальное допустимое значение
    std::string error_msg;          ///< Кастомное сообщение об ошибке
    std::string format_hint;        ///< Подсказка по формату ввода
    std::vector<T> allowed_values;  ///< Список допустимых значений
};

/**
 * @struct FileInputConfig
 * @brief Конфигурация для ввода файла
 */
struct FileInputConfig {
    std::string prompt;                          ///< Текст-обращение к пользователю для файла
    bool check_existence = true;                 ///< проверка на существование файла
    bool check_extension = false;                ///< Проверка на расширение
    std::vector<std::string> allowed_extensions; ///< Допустимые расширения
    std::string error_msg;                       ///< Кастомное сообщение об ошибке
};



/**
 * @struct FileCheckConfig
 * @brief Конфигурация для проверки файла
 */
struct FileCheckConfig {
    bool check_existence = true;             ///< Проверять существование файла
    bool check_extension = false;            ///< Проверять расширение файла
    std::vector<std::string> allowed_extensions; ///< Допустимые расширения файлов
    std::string error_msg;                   ///< Сообщение об ошибке
};


/**
 * @class InputHandler
 * @brief Класс для обработки пользовательского ввода с валидацией
 *
 * Предоставляет статические методы для безопасного получения ввода различных типов
 * с возможностью настройки проверок и ограничений.
 */
class InputHandler {
public:
    /**
     * @brief Получает число с плавающей точкой с проверкой диапазона и допустимых значений
     * @param out Указатель для сохранения результата
     * @param config Параметры валидации
     * @return true если ввод корректен, false при ошибке
     * @note Циклически запрашивает ввод, пока не будет получено корректное значение
     */
    static bool GetInt(int* out, const NumericInputConfig<int>& config = {}) ;

    /**
     * @brief Получает число с плавающей точкой с проверкой диапазона и допустимых значений
     * @param out Указатель для сохранения результата
     * @param config Параметры валидации
     * @return true если ввод корректен, false при ошибке
     * @note Циклически запрашивает ввод, пока не будет получено корректное значение
     */
    static bool GetDouble(double* out, const NumericInputConfig<double>& config = {}) ;

    /**
     * @brief Получает строку с проверкой длины и допустимых значений
     * @param out Указатель для сохранения результата
     * @param config Параметры валидации
     * @return true если ввод корректен, false при ошибке
     * @note Циклически запрашивает ввод, пока не будет получено корректное значение
     */
    static bool GetString(std::string* out, const StringInputConfig& config = {}) ;

    /**
     * @brief Получает булево значение (да/нет)
     * @param out Указатель для сохранения результата
     * @param prompt Приглашение для ввода
     * @return true если ввод корректен, false при ошибке
     * @note Принимает различные варианты ввода: y/n, yes/no, 1/0, true/false
     */
    static bool GetBool(bool* out, const std::string& prompt = "") ;

    /**
     * @brief Проверяет валидность файла по указанному пути
     * @param path Путь к файлу для проверки
     * @param config Конфигурация проверки
     * @return true если файл валиден, false в противном случае
     */
    static bool ValidateFilePath(const fs::path& path, const FileCheckConfig& config = {});

    /**
     * @brief Получает путь к файлу с проверкой (интерактивный ввод)
     * @param out Указатель для сохранения результата
     * @param config Конфигурация проверки
     * @return true если ввод корректен, false при ошибке
     */
    static bool GetFilePath(fs::path* out, const FileCheckConfig& config = {});

private:
    /**
     * @brief Отображение приглашения для ввода
     * @param prompt Текст приглашения
     * @param format_hint Подсказка по формату
     */
    static void ShowPrompt(const std::string& prompt, const std::string& format_hint = "") ;

    /**
     * @brief Получение введенной строки с удалением пробелов
     * @return Очищенная строка ввода
     */
    static std::string GetTrimmedInput() ;

    /**
      * @brief Базовая проверка файла
      * @return true в случае корректной валидации и false иначе
      */
    static bool CheckFileValidity(const fs::path& path, const FileCheckConfig& config);
};

#endif // INPUT_HANDLER_H