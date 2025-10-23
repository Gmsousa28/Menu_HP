#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include "hospital.h"

// verifica se a string contém apenas letras e espaços
int contains_only_letters(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha((unsigned char)str[i]) && str[i] != ' ') {
            return 0; // Retorna falso se encontrar algo que não seja letra ou espaço
        }
    }
    return 1; // Retorna verdadeiro se só houver letras e espaços
}

// Função para normalizar strings preparando-as para comparação
void normalize_string(const char *src, char *dst)
{
    setlocale(LC_ALL, "pt_BR.utf8");
    int j = 0;
    for (int i = 0; src[i] != '\0'; i++)
    {
        // Vamos ignorar espaços, quebras de linha, tabs etc.
        if (src[i] == ' ' || src[i] == '\n' || src[i] == '\t' || src[i] == '\r')
        {
            // simplesmente não copiamos
            continue;
        }

        // Caso não seja um desses caracteres, converte para minúscula
        dst[j] = (char)tolower((unsigned char)src[i]);
        j++;
    }
    dst[j] = '\0'; // termina string
}

// Converte um único char em maiúscula por exemplo m de masculino para M de Masculino
void make_char_uppercase(char *c)
{
    if (*c >= 'a' && *c <= 'z')
    {
        *c = *c - 32; // 'a' (97) -> 'A' (65)
    }
}

// Função auxiliar para remover o '\n' no final de strings capturadas por fgets
void remover_nova_linha(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

// Verifica se existe médico com certo nome (opcional)
int does_medico_exist(char *nome, Medico *medicos, int num_medicos)
{
    // Vamos normalizar o nome que foi recebido por parâmetro
    char nome_normalizado[200]; // garante tamanho suficiente
    normalize_string(nome, nome_normalizado);

    for (int i = 0; i < num_medicos; i++)
    {
        // Normalizar também o nome guardado no struct Medico
        char medico_normalizado[200];
        normalize_string(medicos[i].nome, medico_normalizado);

        // Se forem iguais, então é o mesmo nome (ignora maiúsculas, espaços, etc.)
        if (strcmp(nome_normalizado, medico_normalizado) == 0)
        {
            return 1; // Encontrou
        }
    }
    return 0; // Não encontrou
}

// Verifica se existe paciente com certo nome (opcional)
int does_paciente_exist(char *nome, Paciente *pacientes, int num_pacientes)
{
    // Normaliza o nome recebido por parâmetro
    char nome_normalizado[200];
    normalize_string(nome, nome_normalizado);

    for (int i = 0; i < num_pacientes; i++)
    {
        char paciente_normalizado[200];
        normalize_string(pacientes[i].nome, paciente_normalizado);

        if (strcmp(nome_normalizado, paciente_normalizado) == 0)
        {
            return 1; // Encontrou
        }
    }
    return 0; // Não encontrou
}

// Verifica se existe procedimento para certo SNS (opcional)
int does_procedimento_exist(int sns, Procedimento *procedimentos, int num_procedimentos)
{
    for (int i = 0; i < num_procedimentos; i++)
    {
        if (procedimentos[i].sns == sns)
        {
            return 1;
        }
    }
    return 0;
}

// Verifica se existe recurso hospitalar com certo nome (opcional)
int does_recurso_exist(char *recurso, RecursoHospitalar *recursos, int num_recursos)
{
    for (int i = 0; i < num_recursos; i++)
    {
        if (strcmp(recursos[i].recurso, recurso) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// Verifica se um SNS já está a ser utilizado (opcional)
int is_sns_being_used(int sns, Paciente *pacientes, int num_pacientes,
                      Medico *medicos, int num_medicos)
{
    // Verifica pacientes
    for (int i = 0; i < num_pacientes; i++)
    {
        if (pacientes[i].sns == sns)
        {
            return 1;
        }
    }

    // Verifica médicos
    for (int i = 0; i < num_medicos; i++)
    {
        if (medicos[i].sns == sns)
        {
            return 1;
        }
    }

    return 0; // Não está a ser utilizado
}

// Verifica se a data é válida para o tipo de data dd/mm/aaaa
int check_if_date_is_valid(char *date)
{
    int day, month, year;
    sscanf(date, "%d/%d/%d", &day, &month, &year);
    if (day < 1 || day > 31 || month < 1 || month > 12 || year <= 2024 || year > 9999)
    {
        return 0;
    }
    return 1;
}

// Limpa o buffer do teclado para evitar problemas
void clean_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}