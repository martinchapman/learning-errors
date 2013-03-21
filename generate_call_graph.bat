cp cbmc_headers_for_gcc.c cbmc_headers.c
gcc-4 -std=c99 -fdump-rtl-expand %1
perl egypt %1.141r.expand > %2
cp cbmc_headers_for_cbmc.c cbmc_headers.c