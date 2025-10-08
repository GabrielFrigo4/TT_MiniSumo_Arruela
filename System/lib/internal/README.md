# Internal [v2.0]
 Mini Sumô da Tamandutech - ARRUELA!

## Pastas e Arquivos
 ```
 Internal
 |--src
    |- internal.hpp
    |- internal.hpp
 ```

## Funções
 1. `void setup()`: Inicializa os recursos internos
 2. `bool get_led()`: Pega o estado (Ligado / Desligado) do led interno
 3. `void set_led(const bool mode)`: Liga / Desliga o led interno
 4. `void setup_millis()`: Salva o novo tempo inicial em milissegundos
 5. `uint64_t begin_millis()`: Retorna o tempo inicial em milissegundos
 6. `uint64_t end_millis()`: Retorna o tempo final (o tempo atual) em milissegundos
 7. `uint64_t delta_millis()`: Retorna a diferença entre o tempo final e o inicial em milissegundos
 8. `void setup_micros()`: Salva o novo tempo inicial em microssegundos
 9. `uint64_t begin_micros()`: Retorna o tempo inicial em microssegundos
 10. `uint64_t end_micros()`: Retorna o tempo final (o tempo atual) em microssegundos
 11. `uint64_t delta_micros()`: Retorna a diferença entre o tempo final e o inicial em microssegundos
 12. `const char *mac_address()`: Retorna o WiFi Mac Address
 13. `void bluetooth_disable()`: Desabilita o Bluetooth e limpando o Bluetooth Stack
 14. `void bluetooth_enable()`: Habilita o Bluetooth e inicializa o Bluetooth Stack
 15. `void bluetooth_restart()`: Reinicia o Bluetooth para o padrão
 16. `void flash_erase()`: Limpa a memória flash de dados do ESP32
 17. `void debug(char *out_buffer, const size_t out_size, const char *msg)`: Mostra as informações dos recursos internos na string
 18. `void debug(const char *msg)`: Mostra as informações dos recursos internos
