# TT_MiniSumo_Arruela (v1.0)
 Mini Sumo da Tamandutech - ARRUELA!

## Pastas e Arquivos
 ```
 Controlado (RC)
 |--include
    |- main.hpp
 |--lib
    |--controller
       |- controller.cpp
       |- controller.hpp
    |--engine
       |- engine.cpp
       |- engine.hpp
    |--internal
       |- internal.cpp
       |- internal.hpp
 |--src
    |- main.cpp
 ```

## Sobre a Estrutura do Código
 Esse código é uma experiência de criar uma nova organização que tem como objetivo facilitar a manutenção.

# Emparelhando o controlador PS4 com o ESP32:
[Controller Pairing Guide](https://github.com/darthcloud/BlueRetro/wiki/Controller-pairing-guide)

## Alterar/Pegar o MAC Address do Controle PS4
 Quando um controlador PS4 é 'emparelhado' com um console PS4, significa apenas que ele armazenou o endereço MAC Bluetooth do console, que é o único dispositivo ao qual o controlador se conectará. Normalmente, esse emparelhamento acontece quando você conecta o controlador ao console PS4 usando um cabo USB e pressiona o botão PS. Isso inicia a gravação do endereço MAC do console no controlador.

 Portanto, se você deseja conectar seu controlador PS4 ao ESP32, você precisa descobrir qual é o endereço MAC Bluetooth do seu console PS4 e definir o endereço do ESP32 para ele ou alterar o endereço MAC armazenado no controlador PS4.

 Seja qual for o caminho escolhido, você pode querer uma ferramenta para ler e/ou gravar o endereço MAC atualmente emparelhado do controlador PS4. Você pode tentar usar [sixaxispairer](https://github.com/user-none/sixaxispairer) ou [SixaxisPairTool](https://sixaxispairtool.en.lo4d.com/windows) para essa finalidade.

## Pegar o MAC Address do ESP32
 [ESP32: Erase Flash Memory (Factory Reset)](https://randomnerdtutorials.com/esp32-erase-flash-memory/)
 [esptool.py](https://github.com/espressif/esptool)

 Existem alguns bugs no ESP32 que se resolvem limpando a memória flash com `erase_flash`, e algumas informações aparecem ao fazer isso, como o MAC Address. Porém, existe a opção para pegar as informações de segurança do ESP com `get_security_info`, que mostra o MAC Address do ESP32 sem limpar a memória flash.

 Instalar esptool
 ```
 pip install setuptools
 pip install esptool
 ```

 Limpar a Memória Flash
 ```
 python -m esptool --chip esp32 erase_flash
 ```

 Pegar o MAC Address
 ```
 python -m esptool --chip esp32 get_security_info
 ```

# Código
 O código é separado em 4 principais áreas:
 1. `controller`
 2. `engine`
 3. `internal`
 4. `main`

## Controller
 1. `controller_t`: É uma estrutura que representa o controle de PS4
 2. `void setup(const char *mac)`: Inicializa o pareamento com o controle
 3. `bool is_connected()`: Verifica se o controle está conectado
 4. `bool disconnected()`: Verifica se o controle foi desconectado após ter sido inicializado com sucesso
 5. `controller_t create_snapshot()`: Captura todos os inputs do controle
 6. `void debug(char *out_buffer, const size_t out_size, const controller_t controller, const char *msg)`:  Mostra as informações do controle na string
 7. `void debug(const controller_t controller, const char *msg)`:  Mostra as informações do controle

## Engine
 1. `engine_t`: É uma estrutura que representa um motor (velocidade e direção)
 2. `void setup()`: Inicializa os motores (os pinos em geral do robô)
 3. `bool get_standby()`: Pega o estado (Ligado / Desligado) da corrente elétrica dos motores
 4. `void set_standby(const bool mode)`: Liga / Desliga a corrente elétrica dos motores
 5. `void init()`: Inicializa os motores (valores dos pinos)
 6. `void move(const engine_t engine_left, const engine_t engine_right)`: Altera o movimento dos motores
 7. `void stop()`: Para todos os motores imediatamente
 8. `void debug(char *out_buffer, const size_t out_size, engine_t engine, const char *msg)`: Mostra as informações do motor na string
 9. `void debug(const engine_t engine, const char *msg)`: Mostra as informações do motor

## Internal
 1. `void setup()`: Inicializa os recursos internos
 2. `bool get_led()`: Pega o estado (Ligado / Desligado) do led interno
 3. `void set_led(const bool mode)`: Liga / Desliga o led interno
 4. `void setup_millis()`: Salva o novo tempo inicial
 5. `uint64_t begin_millis()`: Retorna o tempo inicial
 6. `uint64_t end_millis()`: Retorna o tempo final (o tempo atual)
 7. `uint64_t delta_millis()`: Retorna a diferença entre o tempo final e o inicial
 8. `void debug(char *out_buffer, const size_t out_size, const char *msg)`: Mostra as informações dos recursos internos na string
 9. `void debug(const char *msg)`: Mostra as informações dos recursos internos

## Main
 1. `setup()`: Primeira parte do código que roda ao ligar o robô, serve para configurar
 2. `init()`: É o código que vai rodar antes do update
 3. `update()`: É o código que vai rodar em um loop
 4. `loop()`: É o loop geral do robô
