# Sensor [v2.0]
 Mini Sumô da Tamandutech - ARRUELA!

## Pastas e Arquivos
 ```
 Sensor
 |--src
    |- sensor.hpp
    |- sensor.hpp
 ```

## Funções
 1. `sensor_t`: É uma estrutura que representa os valores dos sensores
 2. `void setup()`: Configura os sensores
 3. `void init()`: Inicializa os sensores
 4. `sensor_t create_snapshot()`: Captura os valores dos sensores
 5. `sensor_mode_t get_mode()`: Recupera o modo dos sensores
 6. `void set_mode(sensor_mode_t mode)`: Altera o modo dos sensores
 7. `void debug(char *out_buffer, const size_t out_size, sensor_t sensor, const char *msg)`: Mostra as informações dos sensores na string
 8. `void debug(sensor_t sensor, const char *msg)`: Mostra as informações dos sensores
