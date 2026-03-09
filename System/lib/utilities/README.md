# Utilities [v2.0]
 Mini Sumô da Tamandutech - ARRUELA!

## Pastas e Arquivos
 ```text
 Utilities
 |--src
    |- utilities.hpp
    |- utilities.hpp
 ```

## Funções
 1. `T abs<T>(const T& a)`: Retorna o valor absoluto numérico de `a`.
 2. `void swap<T>(T &a, T &b)`: Troca os valores entre as variáveis `a` e `b`.
 3. `void swap<T, N>(T (&a)[N], T (&b)[N])`: Troca os valores entre dois vetores (arrays) `a` e `b` de mesmo tamanho.
 4. `const T& max<T>(const T& a, const T& b)`: Retorna o maior valor entre `a` e `b`.
 5. `T max<T, N>(const T (&v)[N])`: Retorna o maior valor presente no vetor `v`.
 6. `const T& min<T>(const T& a, const T& b)`: Retorna o menor valor entre `a` e `b`.
 7. `T min<T, N>(const T (&v)[N])`: Retorna o menor valor presente no vetor `v`.
