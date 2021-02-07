/*
 * I owe you a descirption of this test
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <plot/plot.h>
#include <plot/follow.h>
#include <plot/input.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

/* The plot-struct used by the tests. */
static struct plot p;
static FILE * input1, * input2;

/* The suite initialization function. */
int init_suite1(void)
{
  plot_init(&p);

  return 0;
}

/* The suite cleanup function. */
int clean_suite1(void)
{
  plot_destroy(&p);

  return 0;
}

static char input_data[] = "\
21\n\
24\n\
26\n\
28\n\
30\n\
32\n\
34\n\
30\n\
27\
";

void test_plot(void)
{
  input1 = fmemopen(input_data, strlen(input_data), "r");
  if (input1 == NULL)
  {
    handle_error("fmemopen");
  }

  plot_add(&p, input1, 0);

  fprintf(stdout, "\n");
  pdread_all_available(&p);
  plot_plot(&p);
  fflush(stdout);
}

static char input_data2d[] = "\
1\n\
3\n\
4\n\
6\n\
9\n\
13\n\
14\n\
15\n\
18\
";

void test_plot2d(void)
{
  input1 = fmemopen(input_data, strlen(input_data), "r");
  input2 = fmemopen(input_data2d, strlen(input_data2d), "r");
  if (input1 == NULL || input2 == NULL)
  {
    handle_error("fmemopen");
  }

  plot_add(&p, input1, 0);
  plot_add(&p, input2, 1);

  fprintf(stdout, "\n");
  pdread_all_available(&p);
  plot_plot(&p);
  fflush(stdout);
}

void test_plot_follow(void)
{
  input1 = fmemopen(input_data, strlen(input_data), "r");
  input2 = fmemopen(input_data2d, strlen(input_data2d), "r");
  if (input1 == NULL || input2 == NULL)
  {
    handle_error("fmemopen");
  }

  plot_add(&p, input1, 0);
  plot_add(&p, input2, 1);
  p.flags |= plot_flag_animate;

  fprintf(stdout, "\n");
  pdread_all_available(&p);
  follow_plot(&p, p.follow_rate);
  fflush(stdout);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int
main(int argc, char **argv)
{
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
  if ((NULL == CU_add_test(pSuite, "test of plot()", test_plot)) ||
      (NULL == CU_add_test(pSuite, "test of plot() with second input", test_plot2d)) ||
      (NULL == CU_add_test(pSuite, "test of follow_plot()", test_plot_follow)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

