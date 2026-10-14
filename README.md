
## Resumo do Projeto
Este repositório contém o meu primeiro projeto de programação, focado no desenvolvimento de um sistema de menu para a gestão de um hospital. O projeto foi desenvolvido integralmente em linguagem C e serviu como introdução prática a conceitos fundamentais, como estruturação de dados, modularidade de código e a separação entre ficheiros de cabeçalho (headers) e as suas implementações. A aplicação funciona via consola, permitindo interagir com as diferentes opções do sistema hospitalar.

## Tecnologias Utilizadas
* Linguagem C

## Estrutura do Projeto
O projeto está organizado em diferentes módulos para separar lógicas específicas:

* main.c: Ficheiro com a função principal, servindo como ponto de entrada para o menu do sistema.
* hospital.c e hospital.h: Ficheiros dedicados à implementação e definição das estruturas e lógicas centrais relativas ao hospital.
* data.c e data.h: Módulos responsáveis pelo processamento, leitura e escrita de dados do programa.
* functions.c e functions.h: Ficheiros auxiliares que contêm funções complementares e de utilidade geral para suportar o sistema.
* programa.exe: O executável final já compilado para execução direta em Windows.
* MenuHospital.zip: Arquivo compactado contendo todo o projeto guardado.

## Compilação e Execução

Pode executar a aplicação de duas formas:

**Opção 1: Executar diretamente (Windows)**
Faça o download do repositório e abra o ficheiro `programa.exe`.

**Opção 2: Compilar manualmente**
Caso tenha um compilador de C (como o GCC) instalado, abra o terminal no diretório dos ficheiros e execute:

1. Compilar o projeto:
\`\`\`bash
gcc main.c hospital.c data.c functions.c -o programa
\`\`\`

2. Correr a aplicação:
* No Windows:
\`\`\`bash
programa.exe
\`\`\`
* No Linux/macOS:
\`\`\`bash
./programa
\`\`\`

## Autor
* Gonçalo Sousa (@Gmsousa28)
