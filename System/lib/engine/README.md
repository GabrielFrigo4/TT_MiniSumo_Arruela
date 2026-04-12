# Engine [v2.0]
 Mini Sumô da Tamandutech - ARRUELA!

## Pastas e Arquivos
 ```
 Engine
 |--src
    |- engine.cpp
    |- engine.hpp
 ```

## Funções
 1. **`engine_t`**: Estrutura de dados que representa o estado de um motor (velocidade e direção)
 2. **`void setup()`**: Configura os pinos de hardware associados aos motores.
 3. **`void init()`**: Inicializa os valores e o estado padrão dos motores.
 4. **`bool get_standby()`**: Pega o estado (Ligado / Desligado) da corrente elétrica dos motores
 5. **`void set_standby(const bool mode)`**: Altera o estado (Ligado / Desligado) da corrente elétrica dos motores
 6. **`void move(const engine_t engine_left, const engine_t engine_right)`**: Altera o movimento (velocidade e direção) dos motores.
 7. **`void stop(const uint8_t force)`**: Para todos os motores aplicando uma força específica.
 8. **`void brake()`**: Freia todos os motores imediatamente (parada brusca).
 9. **`void loose()`**: Solta todos os motores imediatamente (deixa em roda livre).
 10. **`void debug(char *out_buffer, const size_t out_size, engine_t engine, const char *msg)`**: Formata e grava as informações do motor diretamente na string fornecida (buffer).
 11. **`void debug(const engine_t engine, const char *msg)`**: Exibe as informações e o estado atual do motor.
