#ifndef DATA_H
#define DATA_H

#include "hospital.h"

// Declaração de funções para guardar e carregar dados
void save_data(const Paciente *pacientes, int num_pacientes,
               const Medico *medicos, int num_medicos,
               const Procedimento *procedimentos, int num_procedimentos,
               const RecursoHospitalar *recursos, int num_recursos);

void load_data(Paciente *pacientes, int *num_pacientes,
               Medico *medicos, int *num_medicos,
               Procedimento *procedimentos, int *num_procedimentos,
               RecursoHospitalar *recursos, int *num_recursos);

#endif
