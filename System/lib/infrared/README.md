# Infrared [v2.0]
 Mini Sumô da Tamandutech - ARRUELA!

## Pastas e Arquivos
 ```
 Infrared
 |--src
    |- infrared.hpp
    |- infrared.hpp
 ```

## Funções
 1. `infrared_t`: É uma estrutura que representa os valores do infravermelho
 2. `void setup()`: Inicializa o sensor infravermelho
 3. `bool decode()`: Verifica se há algo a ser decodificado
 4. `void resume()`: Atualiza o novo valor do input 'disponível' (se ele existir)
 5. `uint16_t command()`: Pega o valor do input 'disponível'
 6. `bool update()`: Verifica se existe um novo valor e atualiza, retornando se havia algo novo ou não
 7. `infrared_t receiver()`: Pega o valor de `command` e converte para `infrared_t`
 8. `bool signal(infrared_t sig)`: Atualiza o valor e verifica se `receive` é igual a `sig`
 9. `void debug(char *out_buffer, const size_t out_size, infrared_t infrared, const char *msg)`: Mostra as informações do sensor infravermelho na string
 10. `void debug(infrared_t infrared, const char *msg)`: Mostra as informações do sensor infravermelho
