# parallel processing

set terminal png enhanced font "arial,18" fontscale 1.0 size 1600, 1000
set pointsize 1.2
set xlabel "Parallel processes"
set ylabel "Hashes per second"
set nologscale x
set logscale y
set key outside

set title "PHC candidates, hashes/second in parallel run\n{/arial=12[salt = 16, in,out = 32, tcost = MIN, mcost = 128kiB]}"
set output 'r_parallel_0/parallel_threads_0.png'
plot [0:9][10:100000]\
	"r_parallel_0/argon.dat"            using 5:9 title "{/arial=16 Argon}"            with linespoints, \
	"r_parallel_0/argon-aesni.dat"      using 5:9 title "{/arial=16 Argon-AESNI}"      with linespoints, \
	"r_parallel_0/argon2d.dat"          using 5:9 title "{/arial=16 Argon2d}"          with linespoints, \
	"r_parallel_0/argon2d-sse.dat"      using 5:9 title "{/arial=16 Argon2d-SSE}"      with linespoints, \
	"r_parallel_0/argon2i.dat"          using 5:9 title "{/arial=16 Argon2i}"          with linespoints, \
	"r_parallel_0/argon2i-sse.dat"      using 5:9 title "{/arial=16 Argon2i-SSE}"      with linespoints, \
	"r_parallel_0/battcrypt.dat"        using 5:9 title "{/arial=16 battcrypt}"        with linespoints, \
	"r_parallel_0/catena-butterfly.dat" using 5:9 title "{/arial=16 Catena-Butterfly}" with linespoints, \
	"r_parallel_0/catena-dragonfly.dat" using 5:9 title "{/arial=16 Catena-Dragonfly}" with linespoints, \
	"r_parallel_0/lyra2.dat"            using 5:9 title "{/arial=16 Lyra2}"            with linespoints, \
	"r_parallel_0/lyra2-sse.dat"        using 5:9 title "{/arial=16 Lyra2-SSE}"        with linespoints, \
	"r_parallel_0/pomelo.dat"           using 5:9 title "{/arial=16 POMELO}"           with linespoints, \
	"r_parallel_0/pomelo-sse.dat"       using 5:9 title "{/arial=16 POMELO-SSE}"       with linespoints, \
	"r_parallel_0/pufferfish.dat"       using 5:9 title "{/arial=16 Pufferfish}"       with linespoints, \
	"r_parallel_0/yescrypt.dat"         using 5:9 title "{/arial=16 yescrypt}"         with linespoints, \
	"r_parallel_0/yescrypt-sse.dat"     using 5:9 title "{/arial=16 yescrypt-SSE}"     with linespoints, \
	"r_parallel_0/makwa.dat"            using 5:9 title "{/arial=16 MAKWA (no mcost)}" with linespoints, \
	"r_parallel_0/parallel.dat"         using 5:9 title "{/arial=16 Parallel (no mcost)}" with linespoints

set title "PHC candidates, hashes/second in parallel run\n{/arial=12[salt = 16, in,out = 32, tcost = MIN, mcost = 1MiB]}"
set output 'r_parallel_1/parallel_threads_1.png'
plot [0:9][1:10000]\
	"r_parallel_1/argon.dat"            using 5:9 title "{/arial=16 Argon}"            with linespoints, \
	"r_parallel_1/argon-aesni.dat"      using 5:9 title "{/arial=16 Argon-AESNI}"      with linespoints, \
	"r_parallel_1/argon2d.dat"          using 5:9 title "{/arial=16 Argon2d}"          with linespoints, \
	"r_parallel_1/argon2d-sse.dat"      using 5:9 title "{/arial=16 Argon2d-SSE}"      with linespoints, \
	"r_parallel_1/argon2i.dat"          using 5:9 title "{/arial=16 Argon2i}"          with linespoints, \
	"r_parallel_1/argon2i-sse.dat"      using 5:9 title "{/arial=16 Argon2i-SSE}"      with linespoints, \
	"r_parallel_1/battcrypt.dat"        using 5:9 title "{/arial=16 battcrypt}"        with linespoints, \
	"r_parallel_1/catena-butterfly.dat" using 5:9 title "{/arial=16 Catena-Butterfly}" with linespoints, \
	"r_parallel_1/catena-dragonfly.dat" using 5:9 title "{/arial=16 Catena-Dragonfly}" with linespoints, \
	"r_parallel_1/lyra2.dat"            using 5:9 title "{/arial=16 Lyra2}"            with linespoints, \
	"r_parallel_1/lyra2-sse.dat"        using 5:9 title "{/arial=16 Lyra2-SSE}"        with linespoints, \
	"r_parallel_1/pomelo.dat"           using 5:9 title "{/arial=16 POMELO}"           with linespoints, \
	"r_parallel_1/pomelo-sse.dat"       using 5:9 title "{/arial=16 POMELO-SSE}"       with linespoints, \
	"r_parallel_1/pufferfish.dat"       using 5:9 title "{/arial=16 Pufferfish}"       with linespoints, \
	"r_parallel_1/yescrypt.dat"         using 5:9 title "{/arial=16 yescrypt}"         with linespoints, \
	"r_parallel_1/yescrypt-sse.dat"     using 5:9 title "{/arial=16 yescrypt-SSE}"     with linespoints

set title "PHC candidates, hashes/second in parallel run\n{/arial=12[salt = 16, in,out = 32, tcost = MIN, mcost = 16MiB]}"
set output 'r_parallel_2/parallel_threads_2.png'
plot [0:9][0.1:200]\
	"r_parallel_2/argon.dat"            using 5:9 title "{/arial=16 Argon}"            with linespoints, \
	"r_parallel_2/argon-aesni.dat"      using 5:9 title "{/arial=16 Argon-AESNI}"      with linespoints, \
	"r_parallel_2/argon2d.dat"          using 5:9 title "{/arial=16 Argon2d}"          with linespoints, \
	"r_parallel_2/argon2d-sse.dat"      using 5:9 title "{/arial=16 Argon2d-SSE}"      with linespoints, \
	"r_parallel_2/argon2i.dat"          using 5:9 title "{/arial=16 Argon2i}"          with linespoints, \
	"r_parallel_2/argon2i-sse.dat"      using 5:9 title "{/arial=16 Argon2i-SSE}"      with linespoints, \
	"r_parallel_2/battcrypt.dat"        using 5:9 title "{/arial=16 battcrypt}"        with linespoints, \
	"r_parallel_2/catena-butterfly.dat" using 5:9 title "{/arial=16 Catena-Butterfly}" with linespoints, \
	"r_parallel_2/catena-dragonfly.dat" using 5:9 title "{/arial=16 Catena-Dragonfly}" with linespoints, \
	"r_parallel_2/lyra2.dat"            using 5:9 title "{/arial=16 Lyra2}"            with linespoints, \
	"r_parallel_2/lyra2-sse.dat"        using 5:9 title "{/arial=16 Lyra2-SSE}"        with linespoints, \
	"r_parallel_2/pomelo.dat"           using 5:9 title "{/arial=16 POMELO}"           with linespoints, \
	"r_parallel_2/pomelo-sse.dat"       using 5:9 title "{/arial=16 POMELO-SSE}"       with linespoints, \
	"r_parallel_2/pufferfish.dat"       using 5:9 title "{/arial=16 Pufferfish}"       with linespoints, \
	"r_parallel_2/yescrypt.dat"         using 5:9 title "{/arial=16 yescrypt}"         with linespoints, \
	"r_parallel_2/yescrypt-sse.dat"     using 5:9 title "{/arial=16 yescrypt-SSE}"     with linespoints

set title "PHC candidates, hashes/second in parallel run\n{/arial=12[salt = 16, in,out = 32, tcost = MIN, mcost = 128MiB]}"
set output 'r_parallel_3/parallel_threads_3.png'
plot [0:9][0.01:20]\
	"r_parallel_3/argon.dat"            using 5:9 title "{/arial=16 Argon}"            with linespoints, \
	"r_parallel_3/argon-aesni.dat"      using 5:9 title "{/arial=16 Argon-AESNI}"      with linespoints, \
	"r_parallel_3/argon2d.dat"          using 5:9 title "{/arial=16 Argon2d}"          with linespoints, \
	"r_parallel_3/argon2d-sse.dat"      using 5:9 title "{/arial=16 Argon2d-SSE}"      with linespoints, \
	"r_parallel_3/argon2i.dat"          using 5:9 title "{/arial=16 Argon2i}"          with linespoints, \
	"r_parallel_3/argon2i-sse.dat"      using 5:9 title "{/arial=16 Argon2i-SSE}"      with linespoints, \
	"r_parallel_3/battcrypt.dat"        using 5:9 title "{/arial=16 battcrypt}"        with linespoints, \
	"r_parallel_3/catena-butterfly.dat" using 5:9 title "{/arial=16 Catena-Butterfly}" with linespoints, \
	"r_parallel_3/catena-dragonfly.dat" using 5:9 title "{/arial=16 Catena-Dragonfly}" with linespoints, \
	"r_parallel_3/lyra2.dat"            using 5:9 title "{/arial=16 Lyra2}"            with linespoints, \
	"r_parallel_3/lyra2-sse.dat"        using 5:9 title "{/arial=16 Lyra2-SSE}"        with linespoints, \
	"r_parallel_3/pomelo.dat"           using 5:9 title "{/arial=16 POMELO}"           with linespoints, \
	"r_parallel_3/pomelo-sse.dat"       using 5:9 title "{/arial=16 POMELO-SSE}"       with linespoints, \
	"r_parallel_3/pufferfish.dat"       using 5:9 title "{/arial=16 Pufferfish}"       with linespoints, \
	"r_parallel_3/yescrypt.dat"         using 5:9 title "{/arial=16 yescrypt}"         with linespoints, \
	"r_parallel_3/yescrypt-sse.dat"     using 5:9 title "{/arial=16 yescrypt-SSE}"     with linespoints
