# TT_MiniSumo_Arruela (v1.0)
 Mini Sumo da Tamandutech - ARRUELA!

## Pastas e Arquivos
 ```
 Autonomo (AUTO)
 |--include
    |- main.hpp
 |--lib
    |--engine
       |- engine.cpp
       |- engine.hpp
    |--internal
       |- internal.cpp
       |- internal.hpp
    |--receiver
       |- receiver.cpp
       |- receiver.hpp
    |--sensor
       |- sensor.cpp
       |- sensor.hpp
    |--serial
       |- serial.cpp
       |- serial.hpp
 |--src
    |- main.cpp
 ```

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

## Sobre a Estrutura do Codigo
 Esse código é uma experiência de criar uma nova organização que tem como principio facilitar a manutenção.

# Configuração de Ambiente
 Para o __Arruela__ __v1.0__ usamos apenas o __PlatformIO__ com o __VS CODE__, migramos o __Controlado (RC)__ do __Arduino IDE__ para o __PlatformIO__ na verção __v1.0__

## Visual Studio Code
 1. Baixe o [VS Code](https://code.visualstudio.com/)
 2. [Documentação do VS Code](https://code.visualstudio.com/docs)

## PlatformIO
 1. Site do [PlatformIO](https://platformio.org)
 2. Baixar o [PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode)
