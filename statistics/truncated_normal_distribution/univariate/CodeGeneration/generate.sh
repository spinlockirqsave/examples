echo "This script does 2 things:"
echo " (a) generate the appropriate constants for the univariate algorithm (using the gentab.py python script)"
echo " (b) generate the corresponding c routine, called ran_tg_zig.c"
read -p " press Ctrl-C to escape, ENTER to proceed"
python gentab.py > mid.c
cat beg.c mid.c end.c > ran_tg_zig.c
echo "file ran_tg_zig.c has been generated"
#gcc -O2 ziggurat.c ran_tg_reject.c ran_tg_devroye.c ran_tg_zig1000.c ran_tg_zig2000.c ran_tg_zig4000.c main.c -lm -lgsl -lgslcblas -o zig
#echo "compilation finished, type ./zig to run the program"
