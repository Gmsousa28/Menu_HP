#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hospital.h"
#include "functions.h"
#include "data.h"

// Guarda os dados em ficheiros de texto
void save_data(const Paciente *pacientes, int num_pacientes,
               const Medico *medicos, int num_medicos,
               const Procedimento *procedimentos, int num_procedimentos,
               const RecursoHospitalar *recursos, int num_recursos)
{
    setlocale(LC_ALL, "pt_PT.UTF-8");

    // ----------- Guardar Pacientes -----------
    FILE *f = fopen("pacientes.txt", "w");
    if (f == NULL)
    {
        printf("Erro ao abrir o ficheiro 'pacientes.txt' para escrita.\n");
    }
    else
    {
        for (int i = 0; i < num_pacientes; i++)
        {
            fprintf(f, "%s|%d|%c|%d|%d\n",
                    pacientes[i].nome,
                    pacientes[i].idade,
                    pacientes[i].sexo,
                    pacientes[i].sns,
                    pacientes[i].urgencia);
        }
        fclose(f);
    }

    // ----------- Guardar Médicos -----------
    f = fopen("medicos.txt", "w");
    if (f == NULL)
    {
        printf("Erro ao abrir o ficheiro 'medicos.txt' para escrita.\n");
    }
    else
    {
        for (int i = 0; i < num_medicos; i++)
        {
            fprintf(f, "%s|%d|%c|%d\n",
                    medicos[i].nome,
                    medicos[i].idade,
                    medicos[i].sexo,
                    medicos[i].sns);
        }
        fclose(f);
    }

    // ----------- Guardar Procedimentos -----------
    f = fopen("procedimentos.txt", "w");
    if (f == NULL)
    {
        printf("Erro ao abrir o ficheiro 'procedimentos.txt' para escrita.\n");
    }
    else
    {
        for (int i = 0; i < num_procedimentos; i++)
        {
            fprintf(f, "%d|%d|%s\n",
                    procedimentos[i].sns,
                    procedimentos[i].num_procedimentos,
                    procedimentos[i].descricao);
        }
        fclose(f);
    }

    // ----------- Guardar Recursos -----------
    f = fopen("recursos.txt", "w");
    if (f == NULL)
    {
        printf("Erro ao abrir o ficheiro 'recursos.txt' para escrita.\n");
    }
    else
    {
        for (int i = 0; i < num_recursos; i++)
        {
            fprintf(f, "%s|%d\n",
                    recursos[i].recurso,
                    recursos[i].quantidade);
        }
        fclose(f);
    }
}

// Carrega os dados dos ficheiros para as estruturas
void load_data(Paciente *pacientes, int *num_pacientes,
               Medico *medicos, int *num_medicos,
               Procedimento *procedimentos, int *num_procedimentos,
               RecursoHospitalar *recursos, int *num_recursos)
{
    // Inicialmente, zero
    *num_pacientes = 0;
    *num_medicos = 0;
    *num_procedimentos = 0;
    *num_recursos = 0;

    // ------------- Ler Pacientes -------------
    FILE *f = fopen("pacientes.txt", "r");
    if (f != NULL)
    {
        char linha[256];
        while (fgets(linha, sizeof(linha), f) != NULL)
        {
            // Formato: nome|idade|sexo|sns|urgencia
            Paciente p;
            linha[strcspn(linha, "\n")] = '\0';

            char *token = strtok(linha, "|");
            if (token == NULL) continue;
            strcpy(p.nome, token);

            token = strtok(NULL, "|");
            if (token == NULL) continue;
            p.idade = atoi(token);

            token = strtok(NULL, "|");
            if (token == NULL) continue;
            p.sexo = token[0];

            token = strtok(NULL, "|");
            if (token == NULL) continue;
            p.sns = atoi(token);

            token = strtok(NULL, "|");
            if (token == NULL) continue;
            p.urgencia = atoi(token);

            pacientes[*num_pacientes] = p;
            (*num_pacientes)++;
        }
        fclose(f);
    }

    // ------------- Ler Médicos -------------
    f = fopen("medicos.txt", "r");
    if (f != NULL)
    {
        char linha[256];
        while (fgets(linha, sizeof(linha), f) != NULL)
        {
            // Formato: nome|idade|sexo|sns
            Medico m;
            linha[strcspn(linha, "\n")] = '\0';

            char *token = strtok(linha, "|");
            if (token == NULL) continue;
            strcpy(m.nome, token);

            token = strtok(NULL, "|");
            if (token == NULL) continue;
            m.idade = atoi(token);

            token = strtok(NULL, "|");
            if (token == NULL) continue;
            m.sexo = token[0];

            token = strtok(NULL, "|");
            if (token == NULL) continue;
            m.sns = atoi(token);

            medicos[*num_medicos] = m;
            (*num_medicos)++;
        }
        fclose(f);
    }

    // ------------- Ler Procedimentos -------------
    f = fopen("procedimentos.txt", "r");
    if (f != NULL)
    {
        char linha[256];
        while (fgets(linha, sizeof(linha), f) != NULL)
        {
            // Formato: sns|num_procedimentos|descricao
            Procedimento pr;
            linha[strcspn(linha, "\n")] = '\0';

            char *token = strtok(linha, "|");
            if (token == NULL) continue;
            pr.sns = atoi(token);

            token = strtok(NULL, "|");
            if (token == NULL) continue;
            pr.num_procedimentos = atoi(token);

            token = strtok(NULL, "|");
            if (token == NULL) continue;
            strcpy(pr.descricao, token);

            procedimentos[*num_procedimentos] = pr;
            (*num_procedimentos)++;
        }
        fclose(f);
    }

    // ------------- Ler Recursos -------------
    f = fopen("recursos.txt", "r");
    if (f != NULL)
    {
        char linha[256];
        while (fgets(linha, sizeof(linha), f) != NULL)
        {
            // Formato: recurso|quantidade
            RecursoHospitalar r;
            linha[strcspn(linha, "\n")] = '\0';

            char *token = strtok(linha, "|");
            if (token == NULL) continue;
            strcpy(r.recurso, token);

            token = strtok(NULL, "|");
            if (token == NULL) continue;
            r.quantidade = atoi(token);

            recursos[*num_recursos] = r;
            (*num_recursos)++;
        }
        fclose(f);
    }
}
