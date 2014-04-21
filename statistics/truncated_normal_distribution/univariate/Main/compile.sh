gcc-4.4 -O2 ziggurat.c ran_tg_reject.c ran_tg_devroye.c ran_tg_zig1000.c ran_tg_zig2000.c ran_tg_zig4000.c compare_times.c -lm -lgsl -lgslcblas -o compare_times
echo "compilation finished,  to run the program, type: ./compare_times > times.txt"

