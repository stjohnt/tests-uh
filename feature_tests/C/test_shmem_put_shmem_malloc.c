/*
 *
 * Copyright (c) 2011 - 2015
 *   University of Houston System and UT-Battelle, LLC.
 * Copyright (c) 2009 - 2015
 *   Silicon Graphics International Corp.  SHMEM is copyrighted
 *   by Silicon Graphics International Corp. (SGI) The OpenSHMEM API
 *   (shmem) is released by Open Source Software Solutions, Inc., under an
 *   agreement with Silicon Graphics International Corp. (SGI).
 * Copyright (c) 2016 Intel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * o Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * o Neither the name of the University of Houston System, UT-Battelle, LLC
 *   nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


/*
 * Calls tested
 * shmem_short_put, shmem_int_put, shmem_long_put, shmem_longdouble_put,
 * shmem_longlong_put, shmem_double_put, shmem_float_put,
 * shmem_putmem, shmem_put32, shmem_put64, shmem_put128
 * shmem_iput8, shmem_iput32, shmem_iput64, shmem_iput128
 * shmem_double_iput, shmem_float_iput, shmem_int_iput, shmem_long_iput, shmem_short_iput
 * shmem_double_p, shmem_float_p, shmem_int_p, shmem_long_p, shmem_short_p
 * TODO: shmem_complexf_put, shmem_complexd_put
 * All PEs put an array to right neighbor
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <shmem.h>

#define N 7

int
main (int argc, char **argv)
{
    int i;
    int nextpe;
    int me, npes;
    int success1, success2, success3, success4, success5, success6, success7,
        success8;

    int fail_count = 0;

    short src1[N];
    int src2[N];
    long src3[N];
    long double src4[N];
    long long src5[N];
    double src6[N];
    float src7[N];
    char *src8;
    short src9;
    int src10;
    long src11;
    double src12;
    float src13;

    short *dest1;
    int *dest2;
    long *dest3;
    long double *dest4;
    long long *dest5;
    double *dest6;
    float *dest7;
    char *dest8;
    short *dest9;
    int *dest10;
    long *dest11;
    double *dest12;
    float *dest13;


    shmem_init ();
    me = shmem_my_pe ();
    npes = shmem_n_pes ();

    if (npes > 1) {

        success1 = 0;
        success2 = 0;
        success3 = 0;
        success4 = 0;
        success5 = 0;
        success6 = 0;
        success7 = 0;
        success8 = 0;
        src8 = (char *) malloc (N * sizeof (char));

        for (i = 0; i < N; i += 1) {
            src1[i] = (short) me;
            src2[i] = me;
            src3[i] = (long) me;
            src4[i] = (long double) me;
            src5[i] = (long long) me;
            src6[i] = (double) me;
            src7[i] = (float) me;
            src8[i] = (char) me;
        }
        src9 = (short) me;
        src10 = me;
        src11 = (long) me;
        src12 = (double) me;
        src13 = (float) me;


        dest1 = (short *) shmem_malloc (N * sizeof (*dest1));
        dest2 = (int *) shmem_malloc (N * sizeof (*dest2));
        dest3 = (long *) shmem_malloc (N * sizeof (*dest3));
        dest4 = (long double *) shmem_malloc (N * sizeof (*dest4));
        dest5 = (long long *) shmem_malloc (N * sizeof (*dest5));
        dest6 = (double *) shmem_malloc (N * sizeof (*dest6));
        dest7 = (float *) shmem_malloc (N * sizeof (*dest7));
        dest8 = (char *) shmem_malloc (4 * sizeof (*dest8));
        dest9 = (short *) shmem_malloc (sizeof (*dest9));
        dest10 = (int *) shmem_malloc (sizeof (*dest10));
        dest11 = (long *) shmem_malloc (sizeof (*dest11));
        dest12 = (double *) shmem_malloc (sizeof (*dest12));
        dest13 = (float *) shmem_malloc (sizeof (*dest13));

        for (i = 0; i < N; i += 1) {
            dest1[i] = -9;
            dest2[i] = -9;
            dest3[i] = -9;
            dest4[i] = -9;
            dest5[i] = -9;
            dest6[i] = -9;
            dest7[i] = -9.0;
            dest8[i] = -9;
        }
        *dest9 = -9;
        *dest10 = -9;
        *dest11 = -9;
        *dest12 = -9;
        *dest13 = -9.0;

        nextpe = (me + 1) % npes;

        /* Testing shmem_short_put, shmem_int_put, shmem_long_put,
           shmem_longdouble_put, shmem_longlong_put, shmem_double_put,
           shmem_float_put, shmem_putmem */
        shmem_barrier_all ();

        shmem_short_put (dest1, src1, N, nextpe);
        shmem_int_put (dest2, src2, N, nextpe);
        shmem_long_put (dest3, src3, N, nextpe);
        shmem_longdouble_put (dest4, src4, N, nextpe);
        shmem_longlong_put (dest5, src5, N, nextpe);
        shmem_double_put (dest6, src6, N, nextpe);
        shmem_float_put (dest7, src7, N, nextpe);
        shmem_putmem (dest8, src8, N * sizeof (char), nextpe);

        shmem_barrier_all ();

        if (me == 0) {
            for (i = 0; i < N; i += 1) {
                if (dest1[i] != (npes - 1)) {
                    success1 = 1;
                }
                if (dest2[i] != (npes - 1)) {
                    success2 = 1;
                }
                if (dest3[i] != (npes - 1)) {
                    success3 = 1;
                }
                if (dest4[i] != (npes - 1)) {
                    success4 = 1;
                }
                if (dest5[i] != (npes - 1)) {
                    success5 = 1;
                }
                if (dest6[i] != (npes - 1)) {
                    success6 = 1;
                }
                if (dest7[i] != (npes - 1)) {
                    success7 = 1;
                }
                if (dest8[i] != (npes - 1)) {
                    success8 = 1;
                }
            }

            if (success1 == 0)
                printf ("Test shmem_short_put: Passed\n");
            else {
                printf ("Test shmem_short_put: Failed\n");
		fail_count++;
	    }
            if (success2 == 0)
                printf ("Test shmem_int_put: Passed\n");
            else {
                printf ("Test shmem_int_put: Failed\n");
		fail_count++;
	    }
            if (success3 == 0)
                printf ("Test shmem_long_put: Passed\n");
            else {
                printf ("Test shmem_long_put: Failed\n");
		fail_count++;
	    }
            if (success4 == 0)
                printf ("Test shmem_longdouble_put: Passed\n");
            else {
                printf ("Test shmem_longdouble_put: Failed\n");
		fail_count++;
	    }
            if (success5 == 0)
                printf ("Test shmem_longlong_put: Passed\n");
            else {
                printf ("Test shmem_longlong_put: Failed\n");
		fail_count++;
	    }
            if (success6 == 0)
                printf ("Test shmem_double_put: Passed\n");
            else {
                printf ("Test shmem_double_put: Failed\n");
		fail_count++;
	    }
            if (success7 == 0)
                printf ("Test shmem_float_put: Passed\n");
            else {
                printf ("Test shmem_float_put: Failed\n");
		fail_count++;
	    }
            if (success8 == 0)
                printf ("Test shmem_putmem: Passed\n");
            else {
                printf ("Test shmem_putmem: Failed\n");
		fail_count++;
	    }
        }
        shmem_barrier_all ();

        /* Testing shmem_put32, shmem_put64, shmem_put128 */
        if (sizeof (int) == 4) {
            for (i = 0; i < N; i += 1) {
                dest2[i] = -9;
                dest3[i] = -9;
                dest4[i] = -9;
            }
            success2 = 0;
            success3 = 0;
            success4 = 0;

            shmem_barrier_all ();

            shmem_put32 (dest2, src2, N, nextpe);
            shmem_put64 (dest3, src3, N, nextpe);
            shmem_put128 (dest4, src4, N, nextpe);

            shmem_barrier_all ();

            if (me == 0) {
                for (i = 0; i < N; i += 1) {
                    if (dest2[i] != (npes - 1)) {
                        success2 = 1;
                    }
                    if (dest3[i] != (npes - 1)) {
                        success3 = 1;
                    }
                    if (dest4[i] != (npes - 1)) {
                        success4 = 1;
                    }
                }
                if (success2 == 0)
                    printf ("Test shmem_put32: Passed\n");
                else {
                    printf ("Test shmem_put32: Failed\n");
		    fail_count++;
		}

                if (success3 == 0)
                    printf ("Test shmem_put64: Passed\n");
                else {
                    printf ("Test shmem_put64: Failed\n");
		    fail_count++;
		}

                if (success4 == 0)
                    printf ("Test shmem_put128: Passed\n");
                else {
                    printf ("Test shmem_put128: Failed\n");
		    fail_count++;
		}
            }
        }
        else if (sizeof (int) == 8) {
            for (i = 0; i < N; i += 1) {
                dest1[i] = -9;
                dest2[i] = -9;
                dest3[i] = -9;
            }
            success1 = 0;
            success2 = 0;
            success3 = 0;

            shmem_barrier_all ();

            shmem_put32 (dest1, src1, N, nextpe);
            shmem_put64 (dest2, src2, N, nextpe);
            shmem_put128 (dest3, src3, N, nextpe);

            shmem_barrier_all ();

            if (me == 0) {
                for (i = 0; i < N; i += 1) {
                    if (dest1[i] != (npes - 1)) {
                        success1 = 1;
                    }
                    if (dest2[i] != (npes - 1)) {
                        success2 = 1;
                    }
                    if (dest3[i] != (npes - 1)) {
                        success3 = 1;
                    }

                }
                if (success1 == 0)
                    printf ("Test shmem_put32: Passed\n");
                else {
                    printf ("Test shmem_put32: Failed\n");
		    fail_count++;
		}

                if (success2 == 0)
                    printf ("Test shmem_put64: Passed\n");
                else {
                    printf ("Test shmem_put64: Failed\n");
		    fail_count++;
		}

                if (success3 == 0)
                    printf ("Test shmem_put128: Passed\n");
                else {
                    printf ("Test shmem_put128: Failed\n");
		    fail_count++;
		}
            }
        }

        /* Testing shmem_iput32, shmem_iput64, shmem_iput128 */
        shmem_barrier_all ();
        if (sizeof (int) == 4) {
            for (i = 0; i < N; i += 1) {
                dest2[i] = -9;
                dest3[i] = -9;
                dest4[i] = -9;
            }
            success2 = 0;
            success3 = 0;
            success4 = 0;

            shmem_barrier_all ();

            shmem_iput32 (dest2, src2, 1, 2, N, nextpe);
            shmem_iput64 (dest3, src3, 1, 2, N, nextpe);
            shmem_iput128 (dest4, src4, 1, 2, N, nextpe);

            shmem_barrier_all ();

            if (me == 0) {
                for (i = 0; i < N / 2; i += 1) {
                    if (dest2[i] != (npes - 1)) {
                        success2 = 1;
                    }
                    if (dest3[i] != (npes - 1)) {
                        success3 = 1;
                    }
                    if (dest4[i] != (npes - 1)) {
                        success4 = 1;
                    }
                }
                if (success2 == 0)
                    printf ("Test shmem_iput32: Passed\n");
                else {
                    printf ("Test shmem_iput32: Failed\n");
		    fail_count++;
		}

                if (success3 == 0)
                    printf ("Test shmem_iput64: Passed\n");
                else {
                    printf ("Test shmem_iput64: Failed\n");
		    fail_count++;
		}

                if (success4 == 0)
                    printf ("Test shmem_iput128: Passed\n");
                else {
                    printf ("Test shmem_iput128: Failed\n");
		    fail_count++;
		}
            }
        }
        else if (sizeof (int) == 8) {
            for (i = 0; i < N; i += 1) {
                dest1[i] = -9;
                dest2[i] = -9;
                dest3[i] = -9;
            }
            success1 = 0;
            success2 = 0;
            success3 = 0;

            shmem_barrier_all ();

            shmem_iput32 (dest1, src1, 1, 2, N, nextpe);
            shmem_iput64 (dest2, src2, 1, 2, N, nextpe);
            shmem_iput128 (dest3, src3, 1, 2, N, nextpe);

            shmem_barrier_all ();

            if (me == 0) {
                for (i = 0; i < N / 2; i += 1) {
                    if (dest1[i] != (npes - 1)) {
                        success1 = 1;
                    }
                    if (dest2[i] != (npes - 1)) {
                        success2 = 1;
                    }
                    if (dest3[i] != (npes - 1)) {
                        success3 = 1;
                    }

                }
                if (success1 == 0)
                    printf ("Test shmem_iput32: Passed\n");
                else {
                    printf ("Test shmem_iput32: Failed\n");
		    fail_count++;
		}

                if (success2 == 0)
                    printf ("Test shmem_iput64: Passed\n");
                else {
                    printf ("Test shmem_iput64: Failed\n");
		    fail_count++;
		}

                if (success3 == 0)
                    printf ("Test shmem_iput128: Passed\n");
                else {
                    printf ("Test shmem_iput128: Failed\n");
		    fail_count++;
		}
            }
        }

        /* Testing shmem_short_iput, shmem_int_iput, shmem_long_iput,
           shmem_double_iput, shmem_float_iput */
        for (i = 0; i < N; i += 1) {
            dest1[i] = -9;
            dest2[i] = -9;
            dest3[i] = -9;
            dest6[i] = -9;
            dest7[i] = -9;
        }
        success1 = 0;
        success2 = 0;
        success3 = 0;
        success6 = 0;
        success7 = 0;

        shmem_barrier_all ();

        shmem_short_iput (dest1, src1, 1, 2, N, nextpe);
        shmem_int_iput (dest2, src2, 1, 2, N, nextpe);
        shmem_long_iput (dest3, src3, 1, 2, N, nextpe);
        shmem_double_iput (dest6, src6, 1, 2, N, nextpe);
        shmem_float_iput (dest7, src7, 1, 2, N, nextpe);

        shmem_barrier_all ();

        if (me == 0) {
            for (i = 0; i < N / 2; i += 1) {
                if (dest1[i] != (npes - 1)) {
                    success1 = 1;
                }
                if (dest2[i] != (npes - 1)) {
                    success2 = 1;
                }
                if (dest3[i] != (npes - 1)) {
                    success3 = 1;
                }
                if (dest6[i] != (npes - 1)) {
                    success6 = 1;
                }
                if (dest7[i] != (npes - 1)) {
                    success7 = 1;
                }
            }

            if (success1 == 0)
                printf ("Test shmem_short_iput: Passed\n");
            else {
                printf ("Test shmem_short_iput: Failed\n");
		fail_count++;
	    }
            if (success2 == 0)
                printf ("Test shmem_int_iput: Passed\n");
            else {
                printf ("Test shmem_int_iput: Failed\n");
		fail_count++;
	    }
            if (success3 == 0)
                printf ("Test shmem_long_iput: Passed\n");
            else {
                printf ("Test shmem_long_iput: Failed\n");
		fail_count++;
	    }
            if (success6 == 0)
                printf ("Test shmem_double_iput: Passed\n");
            else {
                printf ("Test shmem_double_iput: Failed\n");
		fail_count++;
	    }
            if (success7 == 0)
                printf ("Test shmem_float_iput: Passed\n");
            else {
                printf ("Test shmem_float_iput: Failed\n");
		fail_count++;
	    }
        }


        /* Testing shmem_double_p, shmem_float_p, shmem_int_p, shmem_long_p,
           shmem_short_p */
        shmem_barrier_all ();

        shmem_short_p (dest9, src9, nextpe);
        shmem_int_p (dest10, src10, nextpe);
        shmem_long_p (dest11, src11, nextpe);
        shmem_double_p (dest12, src12, nextpe);
        shmem_float_p (dest13, src13, nextpe);

        shmem_barrier_all ();

        if (me == 0) {
            if (*dest9 == (npes - 1))
                printf ("Test shmem_short_p: Passed\n");
            else {
                printf ("Test shmem_short_p: Failed\n");
		fail_count++;
	    }
            if (*dest10 == (npes - 1))
                printf ("Test shmem_int_p: Passed\n");
            else {
                printf ("Test shmem_int_p: Failed\n");
		fail_count++;
	    }
            if (*dest11 == (npes - 1))
                printf ("Test shmem_long_p: Passed\n");
            else {
                printf ("Test shmem_long_p: Failed\n");
		fail_count++;
	    }
            if (*dest12 == (npes - 1))
                printf ("Test shmem_double_p: Passed\n");
            else {
                printf ("Test shmem_double_p: Failed\n");
		fail_count++;
	    }
            if (*dest13 == (npes - 1))
                printf ("Test shmem_float_p: Passed\n");
            else {
                printf ("Test shmem_float_p: Failed\n");
		fail_count++;
	    }
        }

        shmem_barrier_all ();

	if (me == 0) {
	    if (fail_count == 0)
	        printf("All Tests Passed\n");
	    else
	        printf("%d Tests Failed\n", fail_count);
	}

        shmem_free (dest1);
        shmem_free (dest2);
        shmem_free (dest3);
        shmem_free (dest4);
        shmem_free (dest5);
        shmem_free (dest6);
        shmem_free (dest7);
        shmem_free (dest8);
        shmem_free (dest9);
        shmem_free (dest10);
        shmem_free (dest11);
        shmem_free (dest12);
        shmem_free (dest13);

    }
    else {
        printf ("Number of PEs must be > 1 to test shmem put, test skipped\n");
    }

    shmem_finalize ();

    return 0;
}
