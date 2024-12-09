/*
 *                               POK header
 *
 * The following file is a part of the POK project. Any modification should
 * be made according to the POK licence. You CANNOT use this file or a part
 * of a file for your own project.
 *
 * For more information on the POK licence, please see our LICENCE FILE
 *
 * Please follow the coding guidelines described in doc/CODING_GUIDELINES
 *
 *                                      Copyright (c) 2007-2024 POK team
 */

#include <core/partition.h>
#include <core/thread.h>
#include <libc/stdio.h>
#include <libc/string.h>
#include <core/time.h>
#include <core/top.h>
#include <types.h>

uint8_t sid;

int getInput() {
  int ch;
  while ((ch = getChar()) == -1);
  return ch;
}

void task() {
  for (;;) {
  }
}

int add_task(uint64_t period, uint64_t time_capacity, uint8_t pri, uint8_t weight, uint64_t deadline) {
  uint32_t tid;
  pok_thread_attr_t tattr;
  memset(&tattr, 0, sizeof(pok_thread_attr_t));

  tattr.period = period;
  tattr.priority = pri;
  tattr.weight   = weight;
  tattr.deadline = deadline;
  tattr.time_capacity = time_capacity;
  tattr.user_add = TRUE;
  tattr.entry = task;

  pok_ret_t ret;
  ret = pok_thread_create(&tid, &tattr);
  if (ret == POK_ERRNO_OK) {
      printf("Create New Thread: %u\n", (unsigned)tid);
  } else if (ret == POK_ERRNO_TOOMANY) {
      printf("Error: Exceed Thread Number Limit.\n");
  } else {
      printf("Other Error.\n");
  }
  return ret == POK_ERRNO_OK ? tid : (uint32_t)-1;
}

int add_soft_task(uint64_t period, uint64_t time_capacity, uint8_t pri, uint8_t weight, uint64_t deadline, uint64_t soft_ddl) {
  uint32_t tid;
  pok_thread_attr_t tattr;
  memset(&tattr, 0, sizeof(pok_thread_attr_t));

  tattr.period = period;
  tattr.priority = pri;
  tattr.weight   = weight;
  tattr.deadline = deadline;
  tattr.soft_deadline = soft_ddl;
  tattr.time_capacity = time_capacity;
  tattr.user_add = TRUE;
  tattr.entry = task;

  pok_ret_t ret;
  ret = pok_thread_create(&tid, &tattr);
  if (ret == POK_ERRNO_OK) {
      printf("Create New Thread: %u\n", (unsigned)tid);
  } else if (ret == POK_ERRNO_TOOMANY) {
      printf("Error: Exceed Thread Number Limit.\n");
  } else {
      printf("Other Error.\n");
  }
  return ret == POK_ERRNO_OK ? tid : (uint32_t)-1;
}

void user_thread() {
  while (1) {
    printf("0 => Image Recognition\n");
    printf("1 => Chatbot\n");
    printf("2 => Show New Created Task Information\n");
    printf("3 => Exit\n");
    printf("Enter a number: ");
    
    int number = getInput();

    printf("%d\n", number-'0');
    printf("You choose: %d\n", number-'0');
    printf("---------------------------\n");

    if (number == '0') {
      printf("Create Image Recognition Task\n");
      add_task(400, 200, 30, 2, 300);
    } else if (number == '1') {
      printf("Create Chatbot Task\n");
      add_soft_task(600, 300, 40, 3, 250, 200);
    } 
    else if (number == '2') {
      printf("Show Task Information\n");
      pok_top();
    } else if (number == '3') {
      printf("User Print Exit!\n");
      break;
    }
    printf("---------------------------\n");
  }
  printf("Exit!\n");
  pok_thread_wait_infinite();
}

int main() {
  uint32_t tid;
  pok_thread_attr_t tattr;
  memset(&tattr, 0, sizeof(pok_thread_attr_t));

  tattr.period = -1;
  tattr.priority = 20;
  tattr.weight   = 1;
  tattr.entry = user_thread;
  pok_thread_create(&tid, &tattr);

  pok_partition_set_mode(POK_PARTITION_MODE_NORMAL);
  pok_thread_wait_infinite();

  return (0);
}