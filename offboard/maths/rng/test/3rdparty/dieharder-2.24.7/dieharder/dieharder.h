/*
 *========================================================================
 * $Id: dieharder.h 326 2007-05-23 01:12:07Z rgb $
 *
 * See copyright in copyright.h and the accompanying file COPYING
 *========================================================================
 */

#include "copyright.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_sf.h>
#include <gsl/gsl_sort.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <dieharder/libdieharder.h>
/*
 * user_template sources are here, not in library
 */
#include "user_template.h"

/*
 *========================================================================
 * Useful defines
 *========================================================================
 */

#define STDIN	stdin
#define STDOUT	stdout
#define STDERR	stderr
#define YES	1
#define NO	0
#define PI      3.141592653589793238462643
#define K       1024
#define PAGE    4096
#define M       1048576
#define M_2     2097152
/*
 * For reasons unknown and unknowable, free() doesn't null the pointer
 * it frees (possibly because it is called by value!)  Nor does it return
 * a success value.  In fact, it is just a leak or memory corruption waiting
 * to happen.  Sigh.
 *
 * nullfree frees and sets the pointer it freed back to NULL.  This let's
 * one e.g. if(a) nullfree(a) to safely free a IFF it is actually a pointer,
 * and let's one test on a in other ways to avoid leaking memory.
 */
#define nullfree(a) {free(a);a = 0;}

 /*
  *========================================================================
  * Subroutine Prototypes
  *========================================================================
  */
 unsigned long int random_seed();
 void start_timing();
 void stop_timing();
 double delta_timing();
 void measure_rate();
 void Usage();
 void help();
 double binomial(unsigned int n, unsigned int k, double p);
 double chisq_eval(double *x,double *y,double *sigma, unsigned int n);
 double chisq_poisson(uint *observed,double lambda,int kmax,uint nsamp);
 double chisq_binomial(double *observed,double prob,uint kmax,uint nsamp);
 void dumpbits(unsigned int *data, unsigned int nbits);
 double sample(void *testfunc());
 double kstest(double *pvalue,int count);
 double kstest_kuiper(double *pvalue,int count);
 double q_ks(double x);
 double q_ks_kuiper(double x);
 void Exit(int);

 double output_rnds(void);
 void add_my_types(void);
 void help_user_template(void);
 void list_rngs(void);
 void parsecl(int argc, char **argv);
 void run_diehard_2dsphere(void);
 void run_diehard_3dsphere(void);
 void run_diehard_birthdays(void);
 void run_diehard_bitstream(void);
 void run_diehard_count_1s_byte(void);
 void run_diehard_count_1s_stream(void);
 void run_diehard_craps(void);
 void run_diehard_dna(void);
 void run_diehard_operm5(void);
 void run_diehard_opso(void);
 void run_diehard_oqso(void);
 void run_diehard_parking_lot(void);
 void run_diehard_rank_32x32(void);
 void run_diehard_rank_6x8(void);
 void run_diehard_runs(void);
 void run_diehard_squeeze(void);
 void run_diehard_sums(void);
 void run_marsaglia_tsang_gcd(void);
 void run_rgb_bitdist(void);
 void run_rgb_persist(void);
 void run_rgb_timing(void);
 void run_sts_monobit(void);
 void run_sts_runs(void);
 void run_user_template(void);
 void startup(void);
 void user_template(Test **test,int irun);
 void work(void);
 void Xtest_eval(Xtest *xtest);

#ifdef RDIEHARDER
 int histogram(double *input,int inum,double min,double max,int nbins,char *label);
 Test *rdh_testptr;		/* kludge: need a global to report back to main + R */
 Dtest *rdh_dtestptr;	/* kludge: need a global to report back to main + R */
#endif


 /*
  *========================================================================
  *                           Global Variables
  *
  * The primary control variables, in alphabetical order, with comments.
  *========================================================================
  */
 int all;               /* Flag to do all tests on selected generator */
 int binary;            /* Flag to output rands in binary (with -o -f) */
 int bits;              /* bitstring size (in bits) */
 int diehard;           /* Diehard test number */
 int generator;         /* GSL generator id number to be tested */
 int help_flag;         /* Help flag */
 int hist_flag;         /* Histogram display flag */
 int iterations;	/* For timing loop, set iterations to be timed */
 int list;              /* List all tests flag */
 int List;              /* List all generators flag */
 int ntuple;            /* n-tuple size for n-tuple tests */
 int num_randoms;		/* the number of randoms stored into memory and usable */
 int output;		/* equals 1 if you output to file, otherwise 0. */
 int overlap;           /* equals 1 if you really want to use diehard overlap */
 int psamples;          /* Number of test runs in final KS test */
 int quiet;             /* quiet flag -- surpresses full output report */
 int rgb;               /* rgb test number */
 int sts;               /* sts test number */
 uint Seed;             /* user selected seed.  Surpresses reseeding per sample.*/
 uint tsamples;         /* Generally should be "a lot". */
 int user;              /* user defined test number */
 int verbose;           /* Default is not to be verbose. */
 double x_user;         /* General purpose command line inputs for use */
 double y_user;         /* in any test. */
 double z_user;
  
 /*
  *========================================================================
  *
  * A few more needed variables.
  *
  *      ks_pvalue is a vector of p-values obtained by samples, kspi is
  *      its index.
  *
  *      tv_start and tv_stop are used to record timings.
  *
  *      dummy and idiot are there to fool the compiler into not optimizing
  *      empty loops out of existence so we can time one accurately.
  *
  *      fp is a file pointer for input or output purposes.
  *
  *========================================================================
  */
#define KS_SAMPLES_PER_TEST_MAX 256
 /* We need two of these to do diehard_craps.  Sigh. */
 double *ks_pvalue,*ks_pvalue2;
 unsigned int kspi;
 struct timeval tv_start,tv_stop;
 int dummy,idiot;
 FILE *fp;
#define MAXFIELDNUMBER 8
 char **fields;

 /*
  * Global variables and prototypes associated with file_input and
  * file_input_raw.
  */
 uint file_input_get_rewind_cnt(gsl_rng *rng);
 uint file_input_get_rtot(gsl_rng *rng);
 void file_input_set_rtot(gsl_rng *rng,uint value);

 char filename[K];      /* Input file name */
 int fromfile;		/* set true if file is used for rands */
 int filenumbits;	/* number of bits per integer */
 uint filecount;	/* number of rands in file */
 char filetype;         /* file type */

 void show_test_header(Dtest *dtest,Test **test);
 void show_test_header_debug(Dtest *dtest,Test **test);
 void test_header(Dtest *dtest);
 void show_test_results(Dtest *dtest,Test **test);
 void show_test_results_debut(Dtest *dtest,Test **test);
 void test_footer(Dtest *dtest, double pvalue, double *pvalues);

