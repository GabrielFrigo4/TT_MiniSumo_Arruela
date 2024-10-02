# TT_MiniSumo_Arruela (v1.0)
 Mini Sumo da Tamandutech - ARRUELA!

## Pastas e Arquivos
 ```
 Controlado (RC)
 |--include
    |- controller.hpp
    |- engine.hpp
    |- macro.hpp
 |--src
    |- controller.cpp
    |- engine.cpp
    |- macro.cpp
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
 3. `macro`
 4. `main`

## Controller
 1. `controller_t`: É uma estrutura que representa o controle de PS4
 2. `void controller_begin(const char *mac)`: Inicializa o pareamento com o controle
 3. `bool controller_is_connected()`: Verifica se o controle está conectado
 4. `controller_t controller_create_snapshot()`: Captura todos os inputs do controle

## Engine
 1. `engine_t`: É uma estrutura que representa um motor (velocidade e direção)
 2. `void engine_alive()`: É uma indicação visual que o motor não foi parado por `engine_kill` (led apagado)
 3. `void engine_kill()`: É uma indicação visual que o motor foi parado por essa função (led acesa)
 4. `void engine_begin()`: Inicializa os motores (os pinos em geral do robô)
 5. `void engine_move(engine_t engine_left, engine_t engine_right)`: Altera o movimento dos motores
 6. `void engine_stop()`: Para todos os motores imediatamente

## Macro
 1. `macro_t` É uma estrutura que representa uma macro
 2. `void macro_load()` Carrega as macros
 3. `void macro_call()` Chama as macros

## Main
 1. `setup`: Primeira parte do código que roda ao ligar o robô
 2. `loop`: É o loop default do robô