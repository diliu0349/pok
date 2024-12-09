// This file has been automatically generated by gen_deployment.
// Do not make manual modifications there or they will be lost.

#ifndef __POK_KERNEL_GENERATED_DEPLOYMENT_H_
#define __POK_KERNEL_GENERATED_DEPLOYMENT_H_

#include <core/schedvalues.h>

#define POK_CONFIG_NB_LOCKOBJECTS 0
#define POK_CONFIG_NB_PARTITIONS 1
#define POK_CONFIG_NB_PROCESSORS 1
#define POK_CONFIG_NB_THREADS 12

#define POK_CONFIG_PARTITIONS_NLOCKOBJECTS                                     \
  { 0 }
#define POK_CONFIG_PARTITIONS_NTHREADS                                         \
  { 10 }
#define POK_CONFIG_PARTITIONS_SCHEDULER                                        \
  { POK_LAB_SCHED_EDF }

#define POK_CONFIG_PARTITIONS_SIZE                                             \
  { 133120 }
#define POK_CONFIG_PROCESSOR_AFFINITY                                          \
  { 1 }
#define POK_CONFIG_PROGRAM_NAME                                                \
  { "pr1/pr1.elf" }
#define POK_CONFIG_SCHEDULING_MAJOR_FRAME 5000
#define POK_CONFIG_SCHEDULING_NBSLOTS 1
#define POK_CONFIG_SCHEDULING_SLOTS                                            \
  { 5000 }
#define POK_CONFIG_SCHEDULING_SLOTS_ALLOCATION                                 \
  { 0 }

#define POK_NEEDS_CONSOLE 1
#define POK_NEEDS_DEBUG 1
#define POK_NEEDS_LOCKOBJECTS 1
#define POK_NEEDS_SCHED_STATIC 0
#define POK_NEEDS_THREAD_SLEEP 1
#define POK_NEEDS_THREAD_SUSPEND 1
#define POK_NEEDS_TIME 1

#endif // __POK_KERNEL_GENERATED_DEPLOYMENT_H_