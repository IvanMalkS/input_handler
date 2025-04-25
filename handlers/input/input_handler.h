#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include <algorithm>

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

private:
    InputHandler() = default;

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
};

#endif // INPUT_HANDLER_H