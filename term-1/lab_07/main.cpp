#include <iostream>

const int MAX_STR_LEN = 1000;

int main() {
    using namespace std;

    char str[MAX_STR_LEN];

    cout << "Введите строку (от 1 до 1000 символов): ";
    fgets(str, MAX_STR_LEN, stdin);

    int str_len = strlen(str);

    // Убираем символ переноса из считанной строки
    if (str_len > 0 && str[str_len - 1] == '\n') {
        str[str_len - 1] = '\0';
        str_len--;
    }

    int result_str_len = 0, word_start_idx = 0, replace_idx = 0;

    for (int i = 0; i < str_len; i++) {
        while (i < str_len && str[i] == ' ') i++; // Перемещаем указатель до начала слова
        word_start_idx = i; // Сохраняем индекс начала слова

        while (i < str_len && str[i] != ' ') i++; // Перемещаем указатель до конца слова

        int word_len = i - word_start_idx;

        if (word_len % 2 != 0) {
            // Копируем слово на место, доступное для перезаписи
            while(word_start_idx != i) str[replace_idx++] = str[word_start_idx++];
            result_str_len += word_len + 1;
            str[replace_idx++] = ' ';
        }
    }

    cout << "Конечная строка: "; 
    for (int i = 0; i < result_str_len; i++) cout << str[i];
    cout << endl;

    return 0;
}