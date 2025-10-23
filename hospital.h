#ifndef HOSPITAL_H
#define HOSPITAL_H

#define MAX_MEDICOS 100
#define MAX_PACIENTES 100
#define MAX_PROCEDIMENTOS 100
#define MAX_RECURSOS 100

// Estrutura de Paciente
typedef struct
{
    char nome[100];
    int idade;
    char sexo;
    int sns;
    int urgencia;
} Paciente;

// Estrutura de Médico
typedef struct
{
    char nome[100];
    int idade;
    char sexo;
    int sns;
} Medico;

// Estrutura de Procedimento
typedef struct
{
    int sns;
    int num_procedimentos;
    char descricao[200];
} Procedimento;

// Estrutura de Recurso Hospitalar
typedef struct
{
    char recurso[100];
    int quantidade;
} RecursoHospitalar;

// Estrutura para Consulta (histórico)
typedef struct
{
    char data[11];
    char nomePaciente[50];
    char nomeMedico[50];
    char diagnostico[100];
} Consulta;

// Declarações das funções
void inserir_medico(Medico *medicos, int *num_medicos, Paciente *pacientes, int num_pacientes);
void inserir_paciente(Paciente *pacientes, int *num_pacientes, Medico *medicos, int *num_medicos);
void inserir_procedimento(Procedimento *procedimentos, int *num_procedimentos, Paciente *pacientes, int num_pacientes);
void inserir_recurso_hospitalar(RecursoHospitalar *recursos, int *num_recursos);

void listar_registos(Paciente *pacientes, int num_pacientes,
                     const Procedimento *procedimentos, int num_procedimentos,
                     const RecursoHospitalar *recursos, int num_recursos,
                     const Medico *medicos, int num_medicos);

void consultar_por_sns(Paciente *pacientes, int num_pacientes, int sns);
void editar_registo(Paciente *pacientes, int num_pacientes, Medico *medicos, int num_medicos);
void registar_consulta(Paciente *pacientes, int num_pacientes, Medico *medicos, int num_medicos);
void eliminar_registo(Paciente *pacientes, int *num_pacientes,
                      Medico *medicos, int *num_medicos, int sns);
void ver_consulta();

#endif
