# tcost round test

set terminal png enhanced font "arial,10" fontscale 1.0 size 1600, 1200
set pointsize 1.2
set xlabel "Used memory (RUSAGE difference) [kB]"
set ylabel "Run time [ms]"
set logscale x
set logscale y
set key inside left
#set label font "arial,16"
set output 'mc_cost_2/memory_time_round.png'

set multiplot
set size 0.5,0.5

set title "{/arial=16 Run time vs real memory use}\n{/arial=12[salt = 16, in,out = 32, tcost = 2 x round]}"
set origin 0.000,0.500 ;
plot [100:10000000][1:1000000]\
	"mc_cost_2/argon.dat"            using 6:5 title "{/arial=12 Argon}"            with points pt  1 lt  1, \
	"mc_cost_2/argon-aesni.dat"      using 6:5 title "{/arial=12 Argon-AESNI}"      with points pt  2 lt  2, \
	"mc_cost_2/argon2d.dat"          using 6:5 title "{/arial=12 Argon2d}"          with points pt  3 lt  3, \
	"mc_cost_2/argon2d-sse.dat"      using 6:5 title "{/arial=12 Argon2d-SSE}"      with points pt  4 lt  4, \
	"mc_cost_2/argon2i.dat"          using 6:5 title "{/arial=12 Argon2i}"          with points pt  5 lt  5, \
	"mc_cost_2/argon2i-sse.dat"      using 6:5 title "{/arial=12 Argon2i-SSE}"      with points pt  6 lt  6, \
	"mc_cost_2/battcrypt.dat"        using 6:5 title "{/arial=12 battcrypt}"        with points pt  7 lt  7, \
	"mc_cost_2/catena-butterfly.dat" using 6:5 title "{/arial=12 Catena-Butterfly}" with points pt  8 lt  8, \
	"mc_cost_2/catena-dragonfly.dat" using 6:5 title "{/arial=12 Catena-Dragonfly}" with points pt  9 lt  9, \
	"mc_cost_2/lyra2.dat"            using 6:5 title "{/arial=12 Lyra2}"            with points pt 10 lt 10, \
	"mc_cost_2/lyra2-sse.dat"        using 6:5 title "{/arial=12 Lyra2-SSE}"        with points pt 11 lt 11, \
	"mc_cost_2/pomelo.dat"           using 6:5 title "{/arial=12 POMELO}"           with points pt 12 lt 12, \
	"mc_cost_2/pomelo-sse.dat"       using 6:5 title "{/arial=12 POMELO-SSE}"       with points pt 13 lt 13, \
	"mc_cost_2/yescrypt.dat"         using 6:5 title "{/arial=12 yescrypt}"         with points pt 15 lt 15, \
	"mc_cost_2/yescrypt-sse.dat"     using 6:5 title "{/arial=12 yescrypt-SSE}"     with points pt 16 lt 16, \
	"mc_cost_2/yescrypt-2pw.dat"     using 6:5 title "{/arial=12 yescrypt-2pw}"     with points pt 17 lt 17, \
	"mc_cost_2/yescrypt-2pw-sse.dat" using 6:5 title "{/arial=12 yescrypt-2pw-SSE}" with points pt 18 lt 18

set title "{/arial=16 Run time vs real memory use}\n{/arial=12[salt = 16, in,out = 32, tcost = 3 x round]}"
set origin 0.500,0.500
plot [100:10000000][1:1000000]\
	"mc_cost_3/argon.dat"            using 6:5 title "{/arial=12 Argon}"            with points pt  1 lt  1, \
	"mc_cost_3/argon-aesni.dat"      using 6:5 title "{/arial=12 Argon-AESNI}"      with points pt  2 lt  2, \
	"mc_cost_3/argon2d.dat"          using 6:5 title "{/arial=12 Argon2d}"          with points pt  3 lt  3, \
	"mc_cost_3/argon2d-sse.dat"      using 6:5 title "{/arial=12 Argon2d-SSE}"      with points pt  4 lt  4, \
	"mc_cost_3/argon2i.dat"          using 6:5 title "{/arial=12 Argon2i}"          with points pt  5 lt  5, \
	"mc_cost_3/argon2i-sse.dat"      using 6:5 title "{/arial=12 Argon2i-SSE}"      with points pt  6 lt  6, \
	"mc_cost_3/battcrypt.dat"        using 6:5 title "{/arial=12 battcrypt}"        with points pt  7 lt  7, \
	"mc_cost_3/catena-butterfly.dat" using 6:5 title "{/arial=12 Catena-Butterfly}" with points pt  8 lt  8, \
	"mc_cost_3/catena-dragonfly.dat" using 6:5 title "{/arial=12 Catena-Dragonfly}" with points pt  9 lt  9, \
	"mc_cost_3/lyra2.dat"            using 6:5 title "{/arial=12 Lyra2}"            with points pt 10 lt 10, \
	"mc_cost_3/lyra2-sse.dat"        using 6:5 title "{/arial=12 Lyra2-SSE}"        with points pt 11 lt 11, \
	"mc_cost_3/pufferfish.dat"       using 6:5 title "{/arial=12 Pufferfish}"       with points pt 14 lt 14, \
	"mc_cost_3/yescrypt.dat"         using 6:5 title "{/arial=12 yescrypt}"         with points pt 15 lt 15, \
	"mc_cost_3/yescrypt-sse.dat"     using 6:5 title "{/arial=12 yescrypt-SSE}"     with points pt 16 lt 16, \
	"mc_cost_3/yescrypt-2pw.dat"     using 6:5 title "{/arial=12 yescrypt-2pw}"     with points pt 17 lt 17, \
	"mc_cost_3/yescrypt-2pw-sse.dat" using 6:5 title "{/arial=12 yescrypt-2pw-SSE}" with points pt 18 lt 18

set title "{/arial=16 Run time vs real memory use}\n{/arial=12[salt = 16, in,out = 32, tcost = 5 x round]}"
set origin 0.500,0.000
plot [100:10000000][1:1000000]\
	"mc_cost_5/argon.dat"            using 6:5 title "{/arial=12 Argon}"            with points pt  1 lt  1, \
	"mc_cost_5/argon-aesni.dat"      using 6:5 title "{/arial=12 Argon-AESNI}"      with points pt  2 lt  2, \
	"mc_cost_5/argon2d.dat"          using 6:5 title "{/arial=12 Argon2d}"          with points pt  3 lt  3, \
	"mc_cost_5/argon2d-sse.dat"      using 6:5 title "{/arial=12 Argon2d-SSE}"      with points pt  4 lt  4, \
	"mc_cost_5/argon2i.dat"          using 6:5 title "{/arial=12 Argon2i}"          with points pt  5 lt  5, \
	"mc_cost_5/argon2i-sse.dat"      using 6:5 title "{/arial=12 Argon2i-SSE}"      with points pt  6 lt  6, \
	"mc_cost_5/catena-butterfly.dat" using 6:5 title "{/arial=12 Catena-Butterfly}" with points pt  8 lt  8, \
	"mc_cost_5/catena-dragonfly.dat" using 6:5 title "{/arial=12 Catena-Dragonfly}" with points pt  9 lt  9, \
	"mc_cost_5/lyra2.dat"            using 6:5 title "{/arial=12 Lyra2}"            with points pt 10 lt 10, \
	"mc_cost_5/lyra2-sse.dat"        using 6:5 title "{/arial=12 Lyra2-SSE}"        with points pt 11 lt 11, \
	"mc_cost_5/pufferfish.dat"       using 6:5 title "{/arial=12 Pufferfish}"       with points pt 14 lt 14, \
	"mc_cost_5/yescrypt.dat"         using 6:5 title "{/arial=12 yescrypt}"         with points pt 15 lt 15, \
	"mc_cost_5/yescrypt-sse.dat"     using 6:5 title "{/arial=12 yescrypt-SSE}"     with points pt 16 lt 16, \
	"mc_cost_5/yescrypt-2pw.dat"     using 6:5 title "{/arial=12 yescrypt-2pw}"     with points pt 17 lt 17, \
	"mc_cost_5/yescrypt-2pw-sse.dat" using 6:5 title "{/arial=12 yescrypt-2pw-SSE}" with points pt 18 lt 18

set title "{/arial=16 Run time vs real memory use}\n{/arial=12[salt = 16, in,out = 32, tcost = 4 x round]}"
set origin 0.000,0.000
plot [100:10000000][1:1000000]\
	"mc_cost_4/argon.dat"            using 6:5 title "{/arial=12 Argon}"            with points pt  1 lt  1, \
	"mc_cost_4/argon-aesni.dat"      using 6:5 title "{/arial=12 Argon-AESNI}"      with points pt  2 lt  2, \
	"mc_cost_4/argon2d.dat"          using 6:5 title "{/arial=12 Argon2d}"          with points pt  3 lt  3, \
	"mc_cost_4/argon2d-sse.dat"      using 6:5 title "{/arial=12 Argon2d-SSE}"      with points pt  4 lt  4, \
	"mc_cost_4/argon2i.dat"          using 6:5 title "{/arial=12 Argon2i}"          with points pt  5 lt  5, \
	"mc_cost_4/argon2i-sse.dat"      using 6:5 title "{/arial=12 Argon2i-SSE}"      with points pt  6 lt  6, \
	"mc_cost_4/battcrypt.dat"        using 6:5 title "{/arial=12 battcrypt}"        with points pt  7 lt  7, \
	"mc_cost_4/catena-butterfly.dat" using 6:5 title "{/arial=12 Catena-Butterfly}" with points pt  8 lt  8, \
	"mc_cost_4/catena-dragonfly.dat" using 6:5 title "{/arial=12 Catena-Dragonfly}" with points pt  9 lt  9, \
	"mc_cost_4/lyra2.dat"            using 6:5 title "{/arial=12 Lyra2}"            with points pt 10 lt 10, \
	"mc_cost_4/lyra2-sse.dat"        using 6:5 title "{/arial=12 Lyra2-SSE}"        with points pt 11 lt 11, \
	"mc_cost_4/pomelo.dat"           using 6:5 title "{/arial=12 POMELO}"           with points pt 12 lt 12, \
	"mc_cost_4/pomelo-sse.dat"       using 6:5 title "{/arial=12 POMELO-SSE}"       with points pt 13 lt 13, \
	"mc_cost_4/yescrypt.dat"         using 6:5 title "{/arial=12 yescrypt}"         with points pt 15 lt 15, \
	"mc_cost_4/yescrypt-sse.dat"     using 6:5 title "{/arial=12 yescrypt-SSE}"     with points pt 16 lt 16, \
	"mc_cost_4/yescrypt-2pw.dat"     using 6:5 title "{/arial=12 yescrypt-2pw}"     with points pt 17 lt 17, \
	"mc_cost_4/yescrypt-2pw-sse.dat" using 6:5 title "{/arial=12 yescrypt-2pw-SSE}" with points pt 18 lt 18

unset multiplot
