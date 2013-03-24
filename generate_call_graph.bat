gcc-4 -std=c99 -fdump-rtl-expand %1 learn_code.c cbmc_headers_for_gcc.c
perl egypt %1.141r.expand learn_code.c.141r.expand cbmc_headers_for_gcc.c.141r.expand > %2
