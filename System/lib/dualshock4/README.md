# DualShock4 [v2.0]
 Mini Sumô da Tamandutech - ARRUELA!

## Pastas e Arquivos
 ```
 DualShock4
 |--src
    |- dualshock4.hpp
    |- dualshock4.hpp
 ```

## Funções
 1. `dualshock4_t`: É uma estrutura que representa o controle de PS4 / DS4
 2. `void setup(const char *mac)`: Inicializa o pareamento com o controle
 3. `bool is_connected()`: Verifica se o controle está conectado
 4. `bool disconnected()`: Verifica se o controle foi desconectado após ter sido inicializado com sucesso
 5. `dualshock4_t create_snapshot()`: Captura todos os inputs do controle
 6. `void debug(char *out_buffer, const size_t out_size, const dualshock4_t dualshock4, const char *msg)`:  Mostra as informações do controle na string
 7. `void debug(const dualshock4_t dualshock4, const char *msg)`:  Mostra as informações do controle
