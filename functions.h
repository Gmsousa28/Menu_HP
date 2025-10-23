#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "hospital.h"

// Declaração das funções utilitárias
int contains_only_letters(const char *str);
void make_char_uppercase(char *c);
void remover_nova_linha(char *str);

int does_medico_exist(char *nome, Medico *medicos, int num_medicos);
int does_paciente_exist(char *nome, Paciente *pacientes, int num_pacientes);
int does_procedimento_exist(int sns, Procedimento *procedimentos, int num_procedimentos);
int does_recurso_exist(char *recurso, RecursoHospitalar *recursos, int num_recursos);
int is_sns_being_used(int sns, Paciente *pacientes, int num_pacientes, Medico *medicos, int num_medicos);

int check_if_date_is_valid(char *date);
void clean_buffer();

#endif
