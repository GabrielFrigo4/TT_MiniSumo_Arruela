# System (SYS) [v2.0]
 Mini Sumô da Tamandutech - ARRUELA!

 ```
                   _____ ____________________ ____ ______________.____       _____
                  /  _  \\______   \______   \    |   \_   _____/|    |     /  _  \
                 /  /_\  \|       _/|       _/    |   /|    __)_ |    |    /  /_\  \
                /    |    \    |   \|    |   \    |  / |        \|    |___/    |    \
                \____|__  /____|_  /|____|_  /______/ /_______  /|_______ \____|__  /
                        \/       \/        \/                 \/         \/       \/






                                    ....::-==+++++++==--::....
                                  .-+***********+******+++++***+-.
                             .-+*******+++***+***+*++++++++++++++++++-.
                         .:+************+***+*+++++++++++++++++++++++**+=:.
                      .:=*#************************+++*******++++++++++++**=:.
                    .=*#***************************************+*+++++*+++****-.
                 ..+#*************************************+*******+****+*******#=..
                .*#***************************************+**********+************+.
              .+##********************************************+*******+*************=.
             -###**********************+=-::.:++****+-...:--=++++*********************:
           .+##*******************++=:.       -+**+++.       .:-=+*********************=.
          :###**###************++-.           .+++++-            .:=+********************.
         :%#****#*#*********++=.                                    .-++*****************#.
        -###***************+-..                                       .:+*****************#:
       -######***##******+=.                                            .-+****************#:
      :########*********+-.                                               .=*****************.
     .##########*******+.                                                  .=*****************.
    .*############****=.                                                     -+**************#=
    -%###########****+.                                                      .-+**************#:
   .############****+.                                                        .=+**************+
   -%############***-                                                          .+**************#:
   *##############*+.                                                           :**************#=
  .%#############**-                                                            .+***************.
  :%#############**.                                                             -**************#.
  =%#############*+                                                              :**************#-
  =%########*####*=                                                              .**************#-
  +%#############*=                                                              .***************-
  =%#############*+                                                              :**************#-
  -%##############*.                                                             -**************#:
  :%##############*:                                                             =**************#.
  .################=                                                            .****************.
   +%##############*:                                                           =***************=
   :%###############+.                                                         :***************#:
    *%###############=.                                                       .+***************+
    :%###############*-                                                      .+***************#.
     =################*=                                                    .+****************=
     .*%################=.                                                 :+****************+.
      .##################+:.                                             .-******************.
       :##################*=:.                                         .:+******************.
        .###################*+..                                     .:+*******************.
         .####################*+:                                  .=*********************.
          .+%####################*+-.                           .=+*********************=.
           .-#######################*+=-:.                ..:-=+***********************-.
             .*#########################***+=---::::::--=++++************************=.
               -#####################################*******************************:
                 -##############################**********************************:
                  .-################################***************************+:.
                    .:+###############################***********************=:.
                       .-+#############################*******************=-.
                          .-+*#########################***************+=:.
                              .-+######################************=:.
                                ....:=*#################*****+-:...
                                       ....::::------::::....
 ```

## Pastas e Arquivos
 ```
 System (SYS)
 |--include
    |- boot.hpp
    |- kernel-auto.hpp
    |- kernel-db.hpp
    |- kernel-rc.hpp
    |- main.hpp
 |--lib
    |--dualshock4
       |- dualshock4.cpp
       |- dualshock4.hpp
    |--engine
       |- engine.cpp
       |- engine.hpp
    |--infrared
       |- infrared.cpp
       |- infrared.hpp
    |--internal
       |- internal.cpp
       |- internal.hpp
    |--sensor
       |- sensor.cpp
       |- sensor.hpp
    |--serial
       |- serial.cpp
       |- serial.hpp
    |--utilitie
       |- utilitie.cpp
       |- utilitie.hpp
 |--src
    |- boot.cpp
    |- kernel-auto.cpp
    |- kernel-db.cpp
    |- kernel-rc.cpp
    |- main.cpp
 ```

## Sobre a Estrutura do Codigo
 Esse código é uma experiência de criar uma nova organização que tem como principio facilitar a manutenção.

# Kernel Template
 Novos Kernels podem ser criados a partir do Kernel Template

## Include (kernel-template.hpp)
 ```cpp
 #include <cstdint>
 #include <cstddef>

 #pragma region "Main Data Defines"
 #ifndef ROBO_NAME
 #define ROBO_NAME "Arruela"
 #endif
 #ifndef BYTE_SIZE
 #define BYTE_SIZE 256
 #endif
 #ifndef BUFFER_SIZE
 #define BUFFER_SIZE (BYTE_SIZE * 2)
 #endif
 #ifndef STACK_SIZE
 #define STACK_SIZE (BYTE_SIZE * 16)
 #endif
 #pragma endregion "Main Data Defines"

 #pragma region "String Macros"
 #ifndef CHARACTER_IS_LOWER_CASE
 #define CHARACTER_IS_LOWER_CASE(x) (x >= 'a' && x <= 'z')
 #endif
 #ifndef CHARACTER_IS_UPPER_CASE
 #define CHARACTER_IS_UPPER_CASE(x) (x >= 'A' && x <= 'Z')
 #endif
 #ifndef CHARACTER_IS_NUMBER
 #define CHARACTER_IS_NUMBER(x) (x >= '0' && x <= '9')
 #endif
 #ifndef STRLN
 #define STRLN(x) x "\n"
 #endif
 #pragma endregion "String Macros"

 namespace tt::kernel_template
 {
 #pragma region "Main Signatures"
 	void setup();
 	void init();
 	void update();
 #pragma endregion "Main Signatures"
 }
 ```

## Source (kernel-template.cpp)
 ```cpp
 #include <Arduino.h>
 #include "kernel-template.hpp"

 namespace tt::kernel_template
 {
 #pragma region "Main Functions"
 	void setup()
 	{

 	}

 	void init()
 	{

 	}

 	void update()
 	{

 	}
 #pragma endregion "Main Functions"
 }
 ```

# Configuração de Ambiente
 Para o __Arruela__ __v1.0__ usamos apenas o __PlatformIO__ com o __VS CODE__, migramos o __Controlado (RC)__ do __Arduino IDE__ para o __PlatformIO__ na verção __v1.0__

## Git & GitHub
 1. Site do [GitHub Desktop](https://github.com/apps/desktop)
 2. Site do [GitHub CLI](https://cli.github.com/)
 3. Site do [Git](https://git-scm.com)

 ```cmd
 winget install GitHub.GitHubDesktop
 winget install GitHub.cli
 winget install Git.Git
 ``` 

## Visual Studio Code
 1. Site do [VS Code](https://code.visualstudio.com/)
 2. [Documentação do VS Code](https://code.visualstudio.com/docs)

 ```cmd
 winget install Microsoft.VisualStudioCode
 ``` 

## Arduino IDE 2
 1. Site do [Arduino IDE 2](https://www.arduino.cc/en/software/)
 2. [Documentação do Arduino IDE 2](https://docs.arduino.cc/software/ide/#ide-v2)

 ```cmd
 winget install ArduinoSA.IDE.stable
 ``` 

## CoreUtils
 1. Site do [CoreUtils](https://github.com/uutils/coreutils)
 2. Baixe o [CoreUtils](https://github.com/uutils/coreutils/releases/)

 ```
 winget install uutils.coreutils
 ```

## BinUtils
 1. Site do [BinUtils](https://winlibs.com/)
 2. Baixe o [BinUtils](https://winlibs.com/#download-release)

 ```
 winget install BrechtSanders.WinLibs.POSIX.UCRT
 ```

## Zip Tools
 1. Site do [WinRAR](https://www.win-rar.com/start.html?&L=0)
 2. Site do [7-zip](https://www.7-zip.org/)

 ```
 winget install RARLab.WinRAR
 winget install 7zip.7zip
 ```

## Python Tools
 1. Site do [Python](https://www.python.org/)
 2. Baixe o [Python](https://www.python.org/downloads/)

 ```
 winget install Python.Python.3.13
 pip install setuptoola
 pip install esptool
 ```

## Pair Tools
 1. Site do [SixaxisPairTool](https://sixaxispairtool.en.lo4d.com/windows)
 ```cmd
 ```

## PlatformIO
 1. Site do [PlatformIO](https://platformio.org)
 2. Baixe o [PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode)

 ```cmd
 wget https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
 python get-platformio.py
 rm get-platformio.py
 ```

## Tamandutech Core Collections (TTCC)
 ```cmd
 ```

## ESP32 SDK
 1. [Multiprocessamento no ESP32](https://embarcados.com.br/serie/multiprocessamento-no-esp32/)
 2. [ESP32 API Reference](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/)

# Emparelhando o controlador PS4 com o ESP32:
[Controller Pairing Guide](https://github.com/darthcloud/BlueRetro/wiki/Controller-pairing-guide)

## Alterar/Pegar o MAC Address do Controle PS4
 Quando um controlador PS4 é 'emparelhado' com um console PS4, significa apenas que ele armazenou o endereço MAC Bluetooth do console, que é o único dispositivo ao qual o controlador se conectará. Normalmente, esse emparelhamento acontece quando você conecta o controlador ao console PS4 usando um cabo USB e pressiona o botão PS. Isso inicia a gravação do endereço MAC do console no controlador.

 Portanto, se você deseja conectar seu controlador PS4 ao ESP32, você precisa descobrir qual é o endereço MAC Bluetooth do seu console PS4 e definir o endereço do ESP32 para ele ou alterar o endereço MAC armazenado no controlador PS4.

 Seja qual for o caminho escolhido, você pode querer uma ferramenta para ler e/ou gravar o endereço MAC atualmente emparelhado do controlador PS4. Você pode tentar usar [sixaxispairer](https://github.com/user-none/sixaxispairer) ou [SixaxisPairTool](https://sixaxispairtool.en.lo4d.com/windows) para essa finalidade.

## Limpar a Memória Flash do ESP32
 [ESP32: Erase Flash Memory (Factory Reset)](https://randomnerdtutorials.com/esp32-erase-flash-memory/)
 [esptool.py](https://github.com/espressif/esptool)

 Existem alguns bugs no ESP32 que se resolvem limpando a memória flash com `erase-flash`, e algumas informações aparecem ao fazer isso, como o MAC Address.

 Limpar a Memória Flash
 ```cmd
 python -m esptool --chip esp32 erase-flash
 ```

## Pegar o MAC Address do ESP32
 Existe a opção para pegar o MAC Address do ESP32 do ESP com `read-mac`, que mostra o MAC Address do ESP32 sem limpar a memória flash.

 Pegar o MAC Address
 ```cmd
 python -m esptool --chip esp32 read-mac
 ```
