#!/bin/sh
#PBS -N SCRIPT_MAX
#PBS -l walltime=0:10:00
#PBS -l nodes=4
#PBS -t 1-4

echo "$PBS_O_JOBID"

$PBS_O_WORKDIR/mtdc_3F2 $PBS_ARRAYID
