#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "hospital.h"
#include "functions.h"

// 1 - Insere um médico
void inserir_medico(Medico *medicos, int *num_medicos, Paciente *pacientes, int num_pacientes)
{
    setlocale(LC_ALL, "pt_PT.UTF-8");
    if (*num_medicos >= MAX_MEDICOS)
    {
        printf("Limite de médicos atingido!\n");
        return;
    }

    // Pede o nome do médico
    while (1)
    {
        printf("Nome do médico: ");
        fgets(medicos[*num_medicos].nome, sizeof(medicos[*num_medicos].nome), stdin); // Lê o nome do médico
        remover_nova_linha(medicos[*num_medicos].nome);

        // Verifica se o nome contém apenas letras e espaços
        if (contains_only_letters(medicos[*num_medicos].nome))
        {
            break; // Nome válido, sai do loop
        }
        else
        {
            printf("Erro: O nome deve conter apenas letras. Tente novamente.\n");
        }
    }

    // Loop para garantir que a idade é inserida corretamente
    int idadeGood = 0;
    while (!idadeGood)
    {
        printf("Idade (entre 0 e 100): ");
        int idadeTemp;
        if (scanf("%d", &idadeTemp) == 1 &&
            idadeTemp >= 0 && idadeTemp <= 100)
        {
            medicos[*num_medicos].idade = idadeTemp;
            idadeGood = 1;
        }
        else
        {
            printf("Erro: Idade inválida! Tente novamente.\n");
        }
        while (getchar() != '\n')
            ; // limpa buffer
    }

    // Loop para garantir que o sexo é inserido corretamente
    int sexoGood = 0;
    while (!sexoGood)
    {
        printf("Sexo (M/F): ");
        char sexo;
        if (scanf(" %c", &sexo) == 1)
        {
            make_char_uppercase(&sexo);
            if (sexo == 'M' || sexo == 'F')
            {
                medicos[*num_medicos].sexo = sexo;
                sexoGood = 1;
            }
            else
            {
                printf("Erro: Sexo inválido! Insira 'M' ou 'F'.\n");
            }
        }
        while (getchar() != '\n')
            ; // limpa buffer
    }

    // Loop para garantir que o número SNS seja inserido corretamente
    int snsGood = 0;
    while (!snsGood)
    {
        printf("Número de SNS (9 dígitos e que comece por 71): ");
        int tempSNS;
        if (scanf("%d", &tempSNS) == 1 &&
            tempSNS > 99999999 && tempSNS <= 999999999 && tempSNS / 10000000 == 71)
        {
            // Verifica se o SNS já está a ser usado
            if (is_sns_being_used(tempSNS, pacientes, num_pacientes, medicos, *num_medicos))
            {
                printf("Erro: Este número de SNS já está em uso.\n");
                continue;
            }
            medicos[*num_medicos].sns = tempSNS;
            snsGood = 1;
        }
        else
        {
            printf("Erro: Número de SNS inválido! Deve ter 9 dígitos e começar por 71.\n");
        }
        while (getchar() != '\n')
            ; // limpa buffer
    }

    (*num_medicos)++;
    printf("Médico registado com sucesso!\n");
}

// 2 - Insere um paciente
void inserir_paciente(Paciente *pacientes, int *num_pacientes, Medico *medicos, int *num_medicos)
{
    setlocale(LC_ALL, "pt_PT.UTF-8");

    if (*num_pacientes >= MAX_PACIENTES)
    {
        printf("Limite de pacientes atingido!\n");
        return;
    }

    // Loop para garantir que o nome é inserido corretamente
    while (1)
    {
        printf("Nome do paciente: ");
        fgets(pacientes[*num_pacientes].nome, sizeof(pacientes[*num_pacientes].nome), stdin);
        remover_nova_linha(pacientes[*num_pacientes].nome);

        if (contains_only_letters(pacientes[*num_pacientes].nome))
        {
            break;
        }
        else
        {
            printf("Erro: O nome deve conter apenas letras. Tente novamente.\n");
        }
    }

    // Idade
    int idadeGood = 0;
    while (!idadeGood)
    {
        printf("Idade (entre 0 e 100): ");
        int idadeTemp;
        if (scanf("%d", &idadeTemp) == 1 &&
            idadeTemp >= 0 && idadeTemp <= 100)
        {
            pacientes[*num_pacientes].idade = idadeTemp;
            idadeGood = 1;
        }
        else
        {
            printf("Erro: Idade inválida! Tente novamente.\n");
        }
        while (getchar() != '\n')
            ; // limpa buffer
    }

    // Sexo
    int sexoGood = 0;
    while (!sexoGood)
    {
        printf("Sexo (M/F): ");
        char sexo;
        if (scanf(" %c", &sexo) == 1)
        {
            make_char_uppercase(&sexo);
            if (sexo == 'M' || sexo == 'F')
            {
                pacientes[*num_pacientes].sexo = sexo;
                sexoGood = 1;
            }
            else
            {
                printf("Erro: Sexo inválido! Insira 'M' ou 'F'.\n");
            }
        }
        while (getchar() != '\n')
            ; // limpa buffer
    }

    // Número SNS
    int snsGood = 0;
    while (!snsGood)
    {
        printf("Número SNS (9 dígitos): ");
        int tempSNS;
        if (scanf("%d", &tempSNS) == 1 &&
            tempSNS > 99999999 && tempSNS <= 999999999)
        {
            if (is_sns_being_used(tempSNS, pacientes, *num_pacientes, medicos, *num_medicos))
            {
                printf("Erro: Este número de SNS já está em uso.\n");
                continue;
            }

            pacientes[*num_pacientes].sns = tempSNS;

            // Verificação se começa por '71' => possivelmente também é médico
            int primeiros_dois_digitos = tempSNS / 10000000;
            if (primeiros_dois_digitos == 71)
            {
                printf("Nota: O número de SNS começa por '71' - atenção que isto é geralmente um médico.\n");
            }
            snsGood = 1;
        }
        else
        {
            printf("Erro: Número de SNS inválido! Insira um número positivo com 9 dígitos.\n");
        }
        while (getchar() != '\n')
            ; // limpa buffer
    }

    // Urgência
    int urgenciaGood = 0;
    while (!urgenciaGood)
    {
        printf("Nível de urgência (entre 0 e 10): ");
        int urg;
        if (scanf("%d", &urg) == 1 && urg >= 0 && urg <= 10)
        {
            pacientes[*num_pacientes].urgencia = urg;
            urgenciaGood = 1;
        }
        else
        {
            printf("Erro: Nível de urgência inválido! Deve estar entre 0 e 10.\n");
        }
        while (getchar() != '\n')
            ; // limpa buffer
    }

    (*num_pacientes)++;
    printf("Paciente registado com sucesso!\n");
}

// 3 - Insere um procedimento
void inserir_procedimento(Procedimento *procedimentos, int *num_procedimentos, Paciente *pacientes, int num_pacientes)
{
    setlocale(LC_ALL, "pt_PT.UTF-8");

    if (*num_procedimentos >= MAX_PROCEDIMENTOS)
    {
        printf("Limite de procedimentos atingido!\n");
        return;
    }

    int snsGood = 0;
    while (!snsGood)
    {
        printf("Número de SNS do paciente: ");
        int tempSNS;
        if (scanf("%d", &tempSNS) == 1 && tempSNS > 0)
        {
            // Verifica se o SNS existe
            if (!is_sns_being_used(tempSNS, pacientes, num_pacientes, NULL, 0))
            {
                printf("Erro: Este número de SNS não está associado a nenhum paciente.\n");
                return;
            }
            procedimentos[*num_procedimentos].sns = tempSNS;
            snsGood = 1;
        }
        else
        {
            printf("Erro: Número SNS inválido! Insira um número positivo.\n");
        }
        while (getchar() != '\n')
            ;
    }

    int procGood = 0;
    while (!procGood)
    {
        printf("Número de procedimentos: ");
        int nproc;
        if (scanf("%d", &nproc) == 1 && nproc >= 0 && nproc <= 100)
        {
            procedimentos[*num_procedimentos].num_procedimentos = nproc;
            procGood = 1;
        }
        else
        {
            printf("Erro: Número de procedimentos inválido! Insira um número entre 0 e 100.\n");
        }
        while (getchar() != '\n')
            ;
    }

    printf("Descrição do procedimento: ");
    fgets(procedimentos[*num_procedimentos].descricao,
          sizeof(procedimentos[*num_procedimentos].descricao),
          stdin);
    remover_nova_linha(procedimentos[*num_procedimentos].descricao);

    (*num_procedimentos)++;
    printf("Procedimento registado com sucesso!\n");
}

// 4 - Insere um recurso hospitalar
void inserir_recurso_hospitalar(RecursoHospitalar *recursos, int *num_recursos)
{
    setlocale(LC_ALL, "pt_PT.UTF-8");

    if (*num_recursos >= MAX_RECURSOS)
    {
        printf("Limite de recursos hospitalares atingido!\n");
        return;
    }

    printf("Nome do recurso hospitalar: ");
    fgets(recursos[*num_recursos].recurso, sizeof(recursos[*num_recursos].recurso), stdin);
    remover_nova_linha(recursos[*num_recursos].recurso);

    printf("Quantidade disponível (0 a 100): ");
    int validInput = 0;
    while (!validInput)
    {
        int qtd;
        if (scanf("%d", &qtd) == 1 && qtd >= 0 && qtd <= 100)
        {
            recursos[*num_recursos].quantidade = qtd;
            validInput = 1;
        }
        else
        {
            printf("Erro: Quantidade inválida! Insira um número entre 0 e 100.\n");
        }
        while (getchar() != '\n')
            ;
    }

    (*num_recursos)++;
    printf("Recurso hospitalar registado com sucesso!\n");
}

// 5 - Lista todos os registos
void listar_registos(Paciente *pacientes, int num_pacientes,
                     const Procedimento *procedimentos, int num_procedimentos,
                     const RecursoHospitalar *recursos, int num_recursos,
                     const Medico *medicos, int num_medicos)
{
    setlocale(LC_ALL, "pt_PT.UTF-8");
    printf("\n---- Lista de Médicos ----\n");
    for (int i = 0; i < num_medicos; i++)
    {
        printf("Nome: %s, SNS: %d, Idade: %d, Sexo: %c\n",
               medicos[i].nome, medicos[i].sns, medicos[i].idade,
               medicos[i].sexo);
    }

    // Ordenar pacientes por urgência (maior -> menor)
    for (int i = 0; i < num_pacientes - 1; i++)
    {
        for (int j = 0; j < num_pacientes - i - 1; j++)
        {
            if (pacientes[j].urgencia < pacientes[j + 1].urgencia)
            {
                Paciente temp = pacientes[j];
                pacientes[j] = pacientes[j + 1];
                pacientes[j + 1] = temp;
            }
        }
    }

    printf("\n---- Lista de Pacientes (Ordenada por Urgência) ----\n");
    for (int i = 0; i < num_pacientes; i++)
    {
        printf("Nome: %s, SNS: %d, Idade: %d, Sexo: %c, Urgência: %d\n",
               pacientes[i].nome, pacientes[i].sns, pacientes[i].idade,
               pacientes[i].sexo, pacientes[i].urgencia);
    }

    printf("\n---- Lista de Procedimentos ----\n");
    for (int i = 0; i < num_procedimentos; i++)
    {
        printf("SNS: %d, Nº Procedimentos: %d, Descrição: %s\n",
               procedimentos[i].sns,
               procedimentos[i].num_procedimentos,
               procedimentos[i].descricao);
    }

    printf("\n---- Lista de Recursos Hospitalares ----\n");
    for (int i = 0; i < num_recursos; i++)
    {
        printf("Recurso: %s, Quantidade: %d\n",
               recursos[i].recurso, recursos[i].quantidade);
    }
}

// 6 - Consulta por SNS
void consultar_por_sns(Paciente *pacientes, int num_pacientes, int sns)
{
    setlocale(LC_ALL, "pt_PT.UTF-8");

    int encontrado = 0;

    for (int i = 0; i < num_pacientes; i++)
    {
        if (pacientes[i].sns == sns)
        {
            encontrado = 1;
            printf("Paciente encontrado:\n");
            printf("Nome: %s\n", pacientes[i].nome);
            printf("Idade: %d\n", pacientes[i].idade);
            printf("Sexo: %c\n", pacientes[i].sexo);
            printf("SNS: %d\n", pacientes[i].sns);
            printf("Nível de Urgência: %d\n", pacientes[i].urgencia);

            if (pacientes[i].sns / 10000000 == 71)
            {
                printf("Nota: Este paciente também é médico (SNS inicia por 71).\n");
            }
            break;
        }
    }

    if (!encontrado)
    {
        printf("Paciente com o SNS %d não foi encontrado.\n", sns);
    }
}

// 7 - Edita um registo
void editar_registo(Paciente *pacientes, int num_pacientes, Medico *medicos, int num_medicos)
{
    setlocale(LC_ALL, "pt_PT.UTF-8");

    int sns, encontrado = 0;

    printf("Digite o SNS do paciente que deseja editar: ");
    if (scanf("%d", &sns) != 1)
    {
        printf("Entrada inválida.\n");
        while (getchar() != '\n')
            ;
        return;
    }
    while (getchar() != '\n')
        ;

    for (int i = 0; i < num_pacientes; i++)
    {
        if (pacientes[i].sns == sns)
        {
            encontrado = 1;
            printf("Paciente encontrado:\n");
            printf("Nome: %s\n", pacientes[i].nome);
            printf("Idade: %d\n", pacientes[i].idade);
            printf("Sexo: %c\n", pacientes[i].sexo);
            printf("SNS: %d\n", pacientes[i].sns);
            printf("Nível de Urgência: %d\n", pacientes[i].urgencia);

            printf("\n---- Editar Dados ----\n");

            // Novo nome
            printf("Novo nome (ou pressione Enter para manter): ");
            char novo_nome[100];
            fgets(novo_nome, sizeof(novo_nome), stdin);
            if (strcmp(novo_nome, "\n") != 0)
            {
                remover_nova_linha(novo_nome);
                strcpy(pacientes[i].nome, novo_nome);
            }

            // Nova idade
            printf("Nova idade (ou digite -1 para manter): ");
            int nova_idade;
            if (scanf("%d", &nova_idade) == 1 && nova_idade != -1)
            {
                pacientes[i].idade = nova_idade;
            }
            while (getchar() != '\n')
                ;

            // Novo sexo
            printf("Novo sexo (M/F), ou pressione Enter para manter: ");
            char novo_sexo;
            novo_sexo = getchar();
            if (novo_sexo != '\n')
            {
                make_char_uppercase(&novo_sexo);
                if (novo_sexo == 'M' || novo_sexo == 'F')
                {
                    pacientes[i].sexo = novo_sexo;
                }
            }
            while (getchar() != '\n')
                ;

            // Nova urgência
            printf("Novo nível de urgência (0 a 10, ou -1 para manter): ");
            int nova_urgencia;
            if (scanf("%d", &nova_urgencia) == 1 && nova_urgencia != -1)
            {
                if (nova_urgencia >= 0 && nova_urgencia <= 10)
                {
                    pacientes[i].urgencia = nova_urgencia;
                }
                else
                {
                    printf("Valor fora do intervalo (0 a 10). Mantendo o anterior.\n");
                }
            }
            while (getchar() != '\n')
                ;

            printf("Registo atualizado com sucesso!\n");
            break;
        }
    }

    if (!encontrado)
    {
        printf("Paciente com SNS %d não foi encontrado.\n", sns);
    }
}

void registar_consulta(Paciente *pacientes, int num_pacientes,
                       Medico *medicos, int num_medicos)
{
    setlocale(LC_ALL, "pt_PT.UTF-8");

    FILE *arquivo;
    Consulta consulta;

    // 1) Verificação da data
    char validDate = 0;
    int invalid_date_count = 0;

    while (!validDate)
    {
        printf("Data (dd/mm/aaaa): ");
        fgets(consulta.data, sizeof(consulta.data), stdin);
        remover_nova_linha(consulta.data);

        if (check_if_date_is_valid(consulta.data))
        {
            validDate = 1;
        }
        else
        {
            invalid_date_count++;
            printf("Data inválida. Tente novamente.\n");
            if (invalid_date_count >= 3)
            {
                printf("Número máximo de tentativas (3) excedido. A voltar ao menu...\n");
                return;
            }
        }
    }

    // 2) Verificação do paciente
    char pacienteExists = 0;
    int invalid_patient_count = 0;
    while (!pacienteExists)
    {
        clean_buffer();
        printf("Nome do paciente: ");
        fgets(consulta.nomePaciente, sizeof(consulta.nomePaciente), stdin);

        if (does_paciente_exist(consulta.nomePaciente, pacientes, num_pacientes))
        {
            pacienteExists = 1;
        }
        else
        {
            invalid_patient_count++;
            printf("Paciente não encontrado. Tente novamente.\n");
            if (invalid_patient_count >= 3)
            {
                printf("Número máximo de tentativas (3) excedido. A voltar ao menu...\n");
                return;
            }
        }
    }

    // 3) Verificação do médico
    char medicoExists = 0;
    int invalid_medico_count = 0;
    while (!medicoExists)
    {
        clean_buffer();
        printf("Nome do médico: ");
        fgets(consulta.nomeMedico, sizeof(consulta.nomeMedico), stdin);

        if (does_medico_exist(consulta.nomeMedico, medicos, num_medicos))
        {
            medicoExists = 1;
        }
        else
        {
            invalid_medico_count++;
            printf("Médico não encontrado. Tente novamente.\n");
            if (invalid_medico_count >= 3)
            {
                printf("Número máximo de tentativas (3) excedido. A voltar ao menu...\n");
                return;
            }
        }
    }

    // 4) Lê o diagnóstico
    printf("Diagnóstico: ");
    fgets(consulta.diagnostico, sizeof(consulta.diagnostico), stdin);
    remover_nova_linha(consulta.diagnostico);

    // 5) Gravar dados no arquivo (histórico de consultas)
    arquivo = fopen("historico_consultas.txt", "a");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o ficheiro para escrita.\n");
        return;
    }
    remover_nova_linha(consulta.data);
    remover_nova_linha(consulta.nomePaciente);
    remover_nova_linha(consulta.nomeMedico);
    remover_nova_linha(consulta.diagnostico);

    fprintf(arquivo, "%s|%s|%s|%s\n",
            consulta.data,
            consulta.nomePaciente,
            consulta.nomeMedico,
            consulta.diagnostico);
    fclose(arquivo);

    printf("\nDados gravados com sucesso no ficheiro 'historico_consultas.txt'.\n");

    // 6) Ler dados do arquivo (para mostrar histórico logo em seguida)
    arquivo = fopen("historico_consultas.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o ficheiro para leitura.\n");
        return;
    }

    printf("\nHistórico de Consultas:\n");
    char buffer[300];
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL)
    {
        Consulta c;
        sscanf(buffer, "%10[^|]|%49[^|]|%49[^|]|%99[^\n]",
               c.data,
               c.nomePaciente,
               c.nomeMedico,
               c.diagnostico);

        printf("Data: %s, Paciente: %s, Médico: %s, Diagnóstico: %s\n",
               c.data,
               c.nomePaciente,
               c.nomeMedico,
               c.diagnostico);
    }
    fclose(arquivo);
}

// 9 - Vê uma consulta registada
void ver_consulta()
{
    setlocale(LC_ALL, "pt_PT.UTF-8");

    FILE *arquivo = fopen("historico_consultas.txt", "r");
    if (arquivo == NULL)
    {
        printf("Não foi possível abrir o ficheiro de histórico de consultas.\n");
        return;
    }

    char linha[256];
    int consulta_encontrada = 0;

    printf("\n##### Histórico de Consultas #####\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        Consulta consulta;
        sscanf(linha, "%10[^|]|%49[^|]|%49[^|]|%99[^\n]",
               consulta.data,
               consulta.nomePaciente,
               consulta.nomeMedico,
               consulta.diagnostico);

        printf("Data: %s, Paciente: %s, Médico: %s, Diagnóstico: %s\n",
               consulta.data,
               consulta.nomePaciente,
               consulta.nomeMedico,
               consulta.diagnostico);

        consulta_encontrada = 1;
    }

    if (!consulta_encontrada)
    {
        printf("Não há consultas registadas.\n");
    }

    fclose(arquivo);
}

// 10 - Elimina um registo (paciente ou médico)
void eliminar_registo(Paciente *pacientes, int *num_pacientes,
                      Medico *medicos, int *num_medicos, int sns)
{
    setlocale(LC_ALL, "pt_PT.UTF-8");
    int encontrado = 0;

    // Remover paciente
    for (int i = 0; i < *num_pacientes; i++)
    {
        if (pacientes[i].sns == sns)
        {
            printf("Paciente encontrado e removido: %s\n", pacientes[i].nome);
            for (int j = i; j < *num_pacientes - 1; j++)
            {
                pacientes[j] = pacientes[j + 1];
            }
            (*num_pacientes)--;
            encontrado = 1;
            break;
        }
    }
    // Remover médico
    for (int i = 0; i < *num_medicos; i++)
    {
        if (medicos[i].sns == sns)
        {
            printf("Médico encontrado e removido: %s\n", medicos[i].nome);
            for (int j = i; j < *num_medicos - 1; j++)
            {
                medicos[j] = medicos[j + 1];
            }
            (*num_medicos)--;
            encontrado = 1;
            break;
        }
    }
    if (!encontrado)
    {
        printf("Nenhum registo encontrado com o SNS %d.\n", sns);
    }
}
