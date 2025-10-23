#include <stdio.h>
#include <locale.h> // Necessário para usar setlocale
#include "hospital.h"
#include "functions.h"
#include "data.h"

int main()
{
    // Configurar o suporte a caracteres acentuados
    setlocale(LC_ALL, "pt_PT.UTF-8");

    Paciente pacientes[MAX_PACIENTES];
    Procedimento procedimentos[MAX_PROCEDIMENTOS];
    RecursoHospitalar recursos[MAX_RECURSOS];
    Medico medicos[MAX_MEDICOS];

    // Contadores (quantos elementos válidos existem em cada array)
    int num_pacientes = 0, num_procedimentos = 0, num_recursos = 0, num_medicos = 0;
    int opcao, sns;

    // Carrega dados dos ficheiros para as estruturas
    load_data(
        pacientes, &num_pacientes,
        medicos, &num_medicos,
        procedimentos, &num_procedimentos,
        recursos, &num_recursos);

    // Menu principal do hospital
    do
    {
        printf("\n############--Menu--###############\n");
        printf("1.  Inserir médico\n");
        printf("2.  Inserir paciente\n");
        printf("3.  Inserir procedimentos\n");
        printf("4.  Inserir recursos hospitalares\n");
        printf("5.  Listar todos os registos em memória\n");
        printf("6.  Consultar registo por SNS\n");
        printf("7.  Editar registo\n");
        printf("8.  Marcar consulta\n");
        printf("9.  Histórico de consultas\n");
        printf("10. Eliminar registo de médico ou paciente\n");
        printf("0.  Sair\n");
        printf("###################################\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1)
        {
            // Se o utilizador inserir algo inválido (não inteiro)
            printf("Entrada inválida.\n");
            while (getchar() != '\n')
                ; // Limpar o buffer de entrada
            continue;
        }
        while (getchar() != '\n')
            ; // Limpa o buffer após ler o número

        switch (opcao)
        {
        case 1:
            inserir_medico(medicos, &num_medicos, pacientes, num_pacientes);
            // Grava logo após inserir
            save_data(pacientes, num_pacientes, medicos, num_medicos, procedimentos, num_procedimentos, recursos, num_recursos);
            break;

        case 2:
            inserir_paciente(pacientes, &num_pacientes, medicos, &num_medicos);
            // Grava logo após inserir
            save_data(pacientes, num_pacientes, medicos, num_medicos, procedimentos, num_procedimentos, recursos, num_recursos);
            break;

        case 3:
            inserir_procedimento(procedimentos, &num_procedimentos, pacientes, num_pacientes);
            // Grava logo após inserir
            save_data(pacientes, num_pacientes, medicos, num_medicos, procedimentos, num_procedimentos, recursos, num_recursos);
            break;

        case 4:
            inserir_recurso_hospitalar(recursos, &num_recursos);
            // Grava logo após inserir
            save_data(pacientes, num_pacientes, medicos, num_medicos, procedimentos, num_procedimentos, recursos, num_recursos);
            break;

        case 5:
            listar_registos(
                pacientes, num_pacientes,
                procedimentos, num_procedimentos,
                recursos, num_recursos,
                medicos, num_medicos);
            break;

        case 6:
            printf("Digite o número de SNS para consulta: ");
            if (scanf("%d", &sns) == 1)
            {
                while (getchar() != '\n')
                    ;
                consultar_por_sns(pacientes, num_pacientes, sns);
            }
            else
            {
                printf("Entrada inválida.\n");
                while (getchar() != '\n')
                    ;
            }
            break;

        case 7:
            editar_registo(pacientes, num_pacientes, medicos, num_medicos);
            save_data(pacientes, num_pacientes, medicos, num_medicos, procedimentos, num_procedimentos, recursos, num_recursos);
            break;

        case 8:
            registar_consulta(pacientes, num_pacientes, medicos, num_medicos);
            // A `registar_consulta()` grava num ficheiro à parte (historico_consultas.txt).
            // Aqui não é preciso `save_data()`, pois não altera diretamente as listas
            break;

        case 9:
            ver_consulta();
            break;

        case 10:
            printf("Digite o número de SNS do paciente ou médico a ser removido: ");
            if (scanf("%d", &sns) == 1)
            {
                while (getchar() != '\n')
                    ;
                eliminar_registo(pacientes, &num_pacientes, medicos, &num_medicos, sns);
                save_data(pacientes, num_pacientes, medicos, num_medicos, procedimentos, num_procedimentos, recursos, num_recursos);
            }
            else
            {
                printf("Entrada inválida.\n");
                while (getchar() != '\n')
                    ;
            }
            break;

        case 0:
            printf("A encerrar o programa. Obrigado!\n");
            break;

        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
        }

    } while (opcao != 0);

    return 0;
}
