load 'linetypes.gnuplot'
set terminal png enhanced font "arial,18" fontscale 1.0 size 1600, 1000
set pointsize 1.5
set grid xtics
set grid ytics
set grid mytics

# Dir for graphs with data and output
G1='m_cost/'
G2='t_cost/'
# G1, mcost variable

set title "PHC candidates, Real used memory vs memory cost\n{/arial=12[salt = 16, in,out = 32, tcost = MIN]}"
set xlabel "Memory cost parameter"
set ylabel "Used memory (RUSAGE difference) [kB]"
set logscale x
set logscale y
set key outside
set output G1.'mcost_memory.png'
plot [1:10000][100:1000000]\
	G1."argon.dat"            using 3:6 title "{/arial=16 Argon}"            with points, \
	G1."argon-aesni.dat"      using 3:6 title "{/arial=16 Argon-AESNI}"      with points, \
	G1."argon2d.dat"          using 3:6 title "{/arial=16 Argon2d}"          with points, \
	G1."argon2d-sse.dat"      using 3:6 title "{/arial=16 Argon2d-SSE}"      with points, \
	G1."argon2i.dat"          using 3:6 title "{/arial=16 Argon2i}"          with points, \
	G1."argon2i-sse.dat"      using 3:6 title "{/arial=16 Argon2i-SSE}"      with points, \
	G1."battcrypt.dat"        using 3:6 title "{/arial=16 battcrypt}"        with points, \
	G1."catena-butterfly.dat" using 3:6 title "{/arial=16 Catena-Butterfly}" with points, \
	G1."catena-dragonfly.dat" using 3:6 title "{/arial=16 Catena-Dragonfly}" with points, \
	G1."lyra2.dat"            using 3:6 title "{/arial=16 Lyra2}"            with points, \
	G1."lyra2-sse.dat"        using 3:6 title "{/arial=16 Lyra2-SSE}"        with points, \
	G1."pomelo.dat"           using 3:6 title "{/arial=16 POMELO}"           with points, \
	G1."pomelo-sse.dat"       using 3:6 title "{/arial=16 POMELO-SSE}"       with points, \
	G1."pufferfish.dat"       using 3:6 title "{/arial=16 Pufferfish}"       with points, \
	G1."yescrypt.dat"         using 3:6 title "{/arial=16 yescrypt}"         with points, \
	G1."yescrypt-sse.dat"     using 3:6 title "{/arial=16 yescrypt-SSE}"     with points

set title "PHC candidates, Real run time vs memory cost\n{/arial=12[salt = 16, in,out = 32, tcost = MIN]}"
set xlabel "Memory cost parameter"
set ylabel "Run time [ms]"
set logscale x
set logscale y
set key outside
set output G1.'mcost_time.png'
plot [1:10000][1:100000]\
	G1."argon.dat"            using 3:5 title "{/arial=16 Argon}"            with points, \
	G1."argon-aesni.dat"      using 3:5 title "{/arial=16 Argon-AESNI}"      with points, \
	G1."argon2d.dat"          using 3:5 title "{/arial=16 Argon2d}"          with points, \
	G1."argon2d-sse.dat"      using 3:5 title "{/arial=16 Argon2d-SSE}"      with points, \
	G1."argon2i.dat"          using 3:5 title "{/arial=16 Argon2i}"          with points, \
	G1."argon2i-sse.dat"      using 3:5 title "{/arial=16 Argon2i-SSE}"      with points, \
	G1."battcrypt.dat"        using 3:5 title "{/arial=16 battcrypt}"        with points, \
	G1."catena-butterfly.dat" using 3:5 title "{/arial=16 Catena-Butterfly}" with points, \
	G1."catena-dragonfly.dat" using 3:5 title "{/arial=16 Catena-Dragonfly}" with points, \
	G1."lyra2.dat"            using 3:5 title "{/arial=16 Lyra2}"            with points, \
	G1."lyra2-sse.dat"        using 3:5 title "{/arial=16 Lyra2-SSE}"        with points, \
	G1."pomelo.dat"           using 3:5 title "{/arial=16 POMELO}"           with points, \
	G1."pomelo-sse.dat"       using 3:5 title "{/arial=16 POMELO-SSE}"       with points, \
	G1."pufferfish.dat"       using 3:5 title "{/arial=16 Pufferfish}"       with points, \
	G1."yescrypt.dat"         using 3:5 title "{/arial=16 yescrypt}"         with points, \
	G1."yescrypt-sse.dat"     using 3:5 title "{/arial=16 yescrypt-SSE}"     with points

set title "PHC candidates, Real run time vs real memory use\n{/arial=12[salt = 16, in,out = 32, tcost = MIN]}"
set xlabel "Used memory (RUSAGE difference) [kB]"
set ylabel "Run time [ms]"
set logscale x
set logscale y
set key outside
set output G1.'memory_time.png'
plot [1000:1000000][1:15000]\
	G1."argon.dat"            using 6:5 title "{/arial=16 Argon}"            with points, \
	G1."argon-aesni.dat"      using 6:5 title "{/arial=16 Argon-AESNI}"      with points, \
	G1."argon2d.dat"          using 6:5 title "{/arial=16 Argon2d}"          with points, \
	G1."argon2d-sse.dat"      using 6:5 title "{/arial=16 Argon2d-SSE}"      with points, \
	G1."argon2i.dat"          using 6:5 title "{/arial=16 Argon2i}"          with points, \
	G1."argon2i-sse.dat"      using 6:5 title "{/arial=16 Argon2i-SSE}"      with points, \
	G1."battcrypt.dat"        using 6:5 title "{/arial=16 battcrypt}"        with points, \
	G1."catena-butterfly.dat" using 6:5 title "{/arial=16 Catena-Butterfly}" with points, \
	G1."catena-dragonfly.dat" using 6:5 title "{/arial=16 Catena-Dragonfly}" with points, \
	G1."lyra2.dat"            using 6:5 title "{/arial=16 Lyra2}"            with points, \
	G1."lyra2-sse.dat"        using 6:5 title "{/arial=16 Lyra2-SSE}"        with points, \
	G1."pomelo.dat"           using 6:5 title "{/arial=16 POMELO}"           with points, \
	G1."pomelo-sse.dat"       using 6:5 title "{/arial=16 POMELO-SSE}"       with points, \
	G1."pufferfish.dat"       using 6:5 title "{/arial=16 Pufferfish}"       with points, \
	G1."yescrypt.dat"         using 6:5 title "{/arial=16 yescrypt}"         with points, \
	G1."yescrypt-sse.dat"     using 6:5 title "{/arial=16 yescrypt-SSE}"     with points

# G2 tcost variable

set title "PHC candidates, Real used memory vs time cost\n{/arial=12[salt = 16, in,out = 32, mcost = MIN]}"
set xlabel "Time cost parameter"
set ylabel "Used memory (RUSAGE difference) [kB]"
set logscale x
set logscale y
set key outside
set output G2.'tcost_memory.png'
plot [1:1000000][1:100000]\
	G2."argon.dat"            using 4:6 title "{/arial=16 Argon}"            with points, \
	G2."argon-aesni.dat"      using 4:6 title "{/arial=16 Argon-AESNI}"      with points, \
	G2."argon2d.dat"          using 4:6 title "{/arial=16 Argon2d}"          with points, \
	G2."argon2d-sse.dat"      using 4:6 title "{/arial=16 Argon2d-SSE}"      with points, \
	G2."argon2i.dat"          using 4:6 title "{/arial=16 Argon2i}"          with points, \
	G2."argon2i-sse.dat"      using 4:6 title "{/arial=16 Argon2i-SSE}"      with points, \
	G2."battcrypt.dat"        using 4:6 title "{/arial=16 battcrypt}"        with points, \
	G2."catena-butterfly.dat" using 4:6 title "{/arial=16 Catena-Butterfly}" with points, \
	G2."catena-dragonfly.dat" using 4:6 title "{/arial=16 Catena-Dragonfly}" with points, \
	G2."lyra2.dat"            using 4:6 title "{/arial=16 Lyra2}"            with points, \
	G2."lyra2-sse.dat"        using 4:6 title "{/arial=16 Lyra2-SSE}"        with points, \
	G2."makwa.dat"            using 4:6 title "{/arial=16 Makwa}"            with points, \
	G2."parallel.dat"         using 4:6 title "{/arial=16 Parallel}"         with points, \
	G2."pomelo.dat"           using 4:6 title "{/arial=16 POMELO}"           with points, \
	G2."pomelo-sse.dat"       using 4:6 title "{/arial=16 POMELO-SSE}"       with points, \
	G2."pufferfish.dat"       using 4:6 title "{/arial=16 Pufferfish}"       with points, \
	G2."yescrypt.dat"         using 4:6 title "{/arial=16 yescrypt}"         with points, \
	G2."yescrypt-sse.dat"     using 4:6 title "{/arial=16 yescrypt-SSE}"     with points

set title "PHC candidates, Real run time vs time cost\n{/arial=12[salt = 16, in,out = 32, mcost = MIN]}"
set xlabel "Time cost parameter"
set ylabel "Run time [ms]"
set logscale x
set logscale y
set key outside
set output G2.'tcost_time.png'
plot [1:1000000][1:10000]\
	G2."argon.dat"            using 4:5 title "{/arial=16 Argon}"            with points, \
	G2."argon-aesni.dat"      using 4:5 title "{/arial=16 Argon-AESNI}"      with points, \
	G2."argon2d.dat"          using 4:5 title "{/arial=16 Argon2d}"          with points, \
	G2."argon2d-sse.dat"      using 4:5 title "{/arial=16 Argon2d-SSE}"      with points, \
	G2."argon2i.dat"          using 4:5 title "{/arial=16 Argon2i}"          with points, \
	G2."argon2i-sse.dat"      using 4:5 title "{/arial=16 Argon2i-SSE}"      with points, \
	G2."battcrypt.dat"        using 4:5 title "{/arial=16 battcrypt}"        with points, \
	G2."catena-butterfly.dat" using 4:5 title "{/arial=16 Catena-Butterfly}" with points, \
	G2."catena-dragonfly.dat" using 4:5 title "{/arial=16 Catena-Dragonfly}" with points, \
	G2."lyra2.dat"            using 4:5 title "{/arial=16 Lyra2}"            with points, \
	G2."lyra2-sse.dat"        using 4:5 title "{/arial=16 Lyra2-SSE}"        with points, \
	G2."makwa.dat"            using 4:5 title "{/arial=16 Makwa}"            with points, \
	G2."parallel.dat"         using 4:5 title "{/arial=16 Parallel}"         with points, \
	G2."pomelo.dat"           using 4:5 title "{/arial=16 POMELO}"           with points, \
	G2."pomelo-sse.dat"       using 4:5 title "{/arial=16 POMELO-SSE}"       with points, \
	G2."pufferfish.dat"       using 4:5 title "{/arial=16 Pufferfish}"       with points, \
	G2."yescrypt.dat"         using 4:5 title "{/arial=16 yescrypt}"         with points, \
	G2."yescrypt-sse.dat"     using 4:5 title "{/arial=16 yescrypt-SSE}"     with points

