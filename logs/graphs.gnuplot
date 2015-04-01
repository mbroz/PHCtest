set terminal png enhanced font "arial,18" fontscale 1.0 size 1600, 1000
set pointsize 1.2

# Dir for graphs with data and output
G1='m_cost/'
G2='t_cost/'
G3='i_len/'
G4='o_len/'

# G1, mcost variable

set title "PHC candidates, Real used memory vs memory cost\n{/arial=12[salt = 16, in,out = 32, tcost = MIN]}"
set xlabel "Memory cost"
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
set xlabel "Memory cost"
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
set xlabel "Time cost"
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
set xlabel "Time cost"
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

# tcost round test
set terminal png enhanced font "arial,10" fontscale 1.0 size 1600, 1200
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
	"mc_cost_2/argon.dat"            using 6:5 title "{/arial=12 Argon}"            with points, \
	"mc_cost_2/argon-aesni.dat"      using 6:5 title "{/arial=12 Argon-AESNI}"      with points, \
	"mc_cost_2/argon2d.dat"          using 6:5 title "{/arial=12 Argon2d}"          with points, \
	"mc_cost_2/argon2d-sse.dat"      using 6:5 title "{/arial=12 Argon2d-SSE}"      with points, \
	"mc_cost_2/argon2i.dat"          using 6:5 title "{/arial=12 Argon2i}"          with points, \
	"mc_cost_2/argon2i-sse.dat"      using 6:5 title "{/arial=12 Argon2i-SSE}"      with points, \
	"mc_cost_2/battcrypt.dat"        using 6:5 title "{/arial=12 battcrypt}"        with points, \
	"mc_cost_2/catena-butterfly.dat" using 6:5 title "{/arial=12 Catena-Butterfly}" with points, \
	"mc_cost_2/catena-dragonfly.dat" using 6:5 title "{/arial=12 Catena-Dragonfly}" with points, \
	"mc_cost_2/lyra2.dat"            using 6:5 title "{/arial=12 Lyra2}"            with points, \
	"mc_cost_2/lyra2-sse.dat"        using 6:5 title "{/arial=12 Lyra2-SSE}"        with points, \
	"mc_cost_2/pomelo.dat"           using 6:5 title "{/arial=12 POMELO}"           with points, \
	"mc_cost_2/pomelo-sse.dat"       using 6:5 title "{/arial=12 POMELO-SSE}"       with points, \
	""                               using 6:5 title "{/arial=12 Pufferfish}"       with points, \
	"mc_cost_2/yescrypt.dat"         using 6:5 title "{/arial=12 yescrypt}"         with points, \
	"mc_cost_2/yescrypt-sse.dat"     using 6:5 title "{/arial=12 yescrypt-SSE}"     with points

set title "{/arial=16 Run time vs real memory use}\n{/arial=12[salt = 16, in,out = 32, tcost = 3 x round]}"
set origin 0.500,0.500
plot [100:10000000][1:1000000]\
	"mc_cost_3/argon.dat"            using 6:5 title "{/arial=12 Argon}"            with points, \
	"mc_cost_3/argon-aesni.dat"      using 6:5 title "{/arial=12 Argon-AESNI}"      with points, \
	"mc_cost_3/argon2d.dat"          using 6:5 title "{/arial=12 Argon2d}"          with points, \
	"mc_cost_3/argon2d-sse.dat"      using 6:5 title "{/arial=12 Argon2d-SSE}"      with points, \
	"mc_cost_3/argon2i.dat"          using 6:5 title "{/arial=12 Argon2i}"          with points, \
	"mc_cost_3/argon2i-sse.dat"      using 6:5 title "{/arial=12 Argon2i-SSE}"      with points, \
	"mc_cost_3/battcrypt.dat"        using 6:5 title "{/arial=12 battcrypt}"        with points, \
	"mc_cost_3/catena-butterfly.dat" using 6:5 title "{/arial=12 Catena-Butterfly}" with points, \
	"mc_cost_3/catena-dragonfly.dat" using 6:5 title "{/arial=12 Catena-Dragonfly}" with points, \
	"mc_cost_3/lyra2.dat"            using 6:5 title "{/arial=12 Lyra2}"            with points, \
	"mc_cost_3/lyra2-sse.dat"        using 6:5 title "{/arial=12 Lyra2-SSE}"        with points, \
	""                               using 6:5 title "{/arial=12 POMELO}"           with points, \
	""                               using 6:5 title "{/arial=12 POMELO-SSE}"       with points, \
	"mc_cost_3/pufferfish.dat"       using 6:5 title "{/arial=12 Pufferfish}"       with points, \
	"mc_cost_3/yescrypt.dat"         using 6:5 title "{/arial=12 yescrypt}"         with points, \
	"mc_cost_3/yescrypt-sse.dat"     using 6:5 title "{/arial=12 yescrypt-SSE}"     with points

set title "{/arial=16 Run time vs real memory use}\n{/arial=12[salt = 16, in,out = 32, tcost = 5 x round]}"
set origin 0.500,0.000
plot [100:10000000][1:1000000]\
	"mc_cost_5/argon.dat"            using 6:5 title "{/arial=12 Argon}"            with points, \
	"mc_cost_5/argon-aesni.dat"      using 6:5 title "{/arial=12 Argon-AESNI}"      with points, \
	"mc_cost_5/argon2d.dat"          using 6:5 title "{/arial=12 Argon2d}"          with points, \
	"mc_cost_5/argon2d-sse.dat"      using 6:5 title "{/arial=12 Argon2d-SSE}"      with points, \
	"mc_cost_5/argon2i.dat"          using 6:5 title "{/arial=12 Argon2i}"          with points, \
	"mc_cost_5/argon2i-sse.dat"      using 6:5 title "{/arial=12 Argon2i-SSE}"      with points, \
	""                               using 6:5 title "{/arial=12 battcrypt}"        with points, \
	"mc_cost_5/catena-butterfly.dat" using 6:5 title "{/arial=12 Catena-Butterfly}" with points, \
	"mc_cost_5/catena-dragonfly.dat" using 6:5 title "{/arial=12 Catena-Dragonfly}" with points, \
	"mc_cost_5/lyra2.dat"            using 6:5 title "{/arial=12 Lyra2}"            with points, \
	"mc_cost_5/lyra2-sse.dat"        using 6:5 title "{/arial=12 Lyra2-SSE}"        with points, \
	""                               using 6:5 title "{/arial=12 POMELO}"           with points, \
	""                               using 6:5 title "{/arial=12 POMELO-SSE}"       with points, \
	"mc_cost_5/pufferfish.dat"       using 6:5 title "{/arial=12 Pufferfish}"       with points, \
	"mc_cost_5/yescrypt.dat"         using 6:5 title "{/arial=12 yescrypt}"         with points, \
	"mc_cost_5/yescrypt-sse.dat"     using 6:5 title "{/arial=12 yescrypt-SSE}"     with points

set title "{/arial=16 Run time vs real memory use}\n{/arial=12[salt = 16, in,out = 32, tcost = 4 x round]}"
set origin 0.000,0.000
plot [100:10000000][1:1000000]\
	"mc_cost_4/argon.dat"            using 6:5 title "{/arial=12 Argon}"            with points, \
	"mc_cost_4/argon-aesni.dat"      using 6:5 title "{/arial=12 Argon-AESNI}"      with points, \
	"mc_cost_4/argon2d.dat"          using 6:5 title "{/arial=12 Argon2d}"          with points, \
	"mc_cost_4/argon2d-sse.dat"      using 6:5 title "{/arial=12 Argon2d-SSE}"      with points, \
	"mc_cost_4/argon2i.dat"          using 6:5 title "{/arial=12 Argon2i}"          with points, \
	"mc_cost_4/argon2i-sse.dat"      using 6:5 title "{/arial=12 Argon2i-SSE}"      with points, \
	"mc_cost_4/battcrypt.dat"        using 6:5 title "{/arial=12 battcrypt}"        with points, \
	"mc_cost_4/catena-butterfly.dat" using 6:5 title "{/arial=12 Catena-Butterfly}" with points, \
	"mc_cost_4/catena-dragonfly.dat" using 6:5 title "{/arial=12 Catena-Dragonfly}" with points, \
	"mc_cost_4/lyra2.dat"            using 6:5 title "{/arial=12 Lyra2}"            with points, \
	"mc_cost_4/lyra2-sse.dat"        using 6:5 title "{/arial=12 Lyra2-SSE}"        with points, \
	"mc_cost_4/pomelo.dat"           using 6:5 title "{/arial=12 POMELO}"           with points, \
	"mc_cost_4/pomelo-sse.dat"       using 6:5 title "{/arial=12 POMELO-SSE}"       with points, \
	""                               using 6:5 title "{/arial=12 Pufferfish}"       with points, \
	"mc_cost_4/yescrypt.dat"         using 6:5 title "{/arial=12 yescrypt}"         with points, \
	"mc_cost_4/yescrypt-sse.dat"     using 6:5 title "{/arial=12 yescrypt-SSE}"     with points

unset multiplot



# G3 run time, variable input
set terminal png enhanced font "arial,10" fontscale 1.0 size 1024, 1536

set title ""
set xlabel "Input length [bytes]"
set ylabel "Run time [ms]"
set label font "arial,16"
set nologscale x
set nologscale y
set key off
set output G3.'ilen_time.png'

set multiplot
set size 0.5,0.111
set xtics 50

set xr [1:300]
set yr [0:110]

set origin 0.000,0.888 ; set label 1 'Argon'            at 280,90 right ; plot G3."argon.dat"            using 1:5 with points
set origin 0.500,0.888 ; set label 1 'Argon-AESNI'      at 280,90 right ; plot G3."argon-aesni.dat"      using 1:5 with points
set origin 0.000,0.777 ; set label 1 'Argon2d'          at 280,90 right ; plot G3."argon2d.dat"          using 1:5 with points
set origin 0.500,0.777 ; set label 1 'Argon2d-SSE'      at 280,90 right ; plot G3."argon2d-sse.dat"      using 1:5 with points
set origin 0.000,0.666 ; set label 1 'Argon2i'          at 280,90 right ; plot G3."argon2i.dat"          using 1:5 with points
set origin 0.500,0.666 ; set label 1 'Argon2i-SSE'      at 280,90 right ; plot G3."argon2i-sse.dat"      using 1:5 with points
set origin 0.000,0.555 ; set label 1 'battcrypt'        at 280,90 right ; plot G3."battcrypt.dat"        using 1:5 with points
set origin 0.500,0.555 ; set label 1 'Catena-Butterfly' at 280,90 right ; plot G3."catena-butterfly.dat" using 1:5 with points
set origin 0.000,0.444 ; set label 1 'Catena-Dragonfly' at 280,90 right ; plot G3."catena-dragonfly.dat" using 1:5 with points
set origin 0.500,0.444 ; set label 1 'Lyra2'            at 280,90 right ; plot G3."lyra2.dat"            using 1:5 with points
set origin 0.000,0.333 ; set label 1 'Lyra2-SSE'        at 280,90 right ; plot G3."lyra2-sse.dat"        using 1:5 with points
set origin 0.500,0.333 ; set label 1 'Makwa'            at 280,90 right ; plot G3."makwa.dat"            using 1:5 with points
set origin 0.000,0.222 ; set label 1 'Parallel'         at 280,90 right ; plot G3."parallel.dat"         using 1:5 with points
set origin 0.500,0.222 ; set label 1 'POMELO'           at 280,90 right ; plot G3."pomelo.dat"           using 1:5 with points
set origin 0.000,0.111 ; set label 1 'POMELO-SSE'       at 280,90 right ; plot G3."pomelo-sse.dat"       using 1:5 with points
set origin 0.500,0.111 ; set label 1 'Pufferfish'       at 280,90 right ; plot G3."pufferfish.dat"       using 1:5 with points
set origin 0.000,0.000 ; set label 1 'yescrypt'         at 280,90 right ; plot G3."yescrypt.dat"         using 1:5 with points
set origin 0.500,0.000 ; set label 1 'yescrypt-sse'     at 280,90 right ; plot G3."yescrypt-sse.dat"     using 1:5 with points

unset multiplot

# G4 run time, variable output
set terminal png enhanced font "arial,10" fontscale 1.0 size 1024, 1536

set title ""
set xlabel "Output length [bytes]"
set ylabel "Run time [ms]"
set label font "arial,16"
set nologscale x
set nologscale y
set key off
set output G4.'olen_time.png'

set multiplot
set size 0.5,0.111
set xtics 50

set xr [1:300]
set yr [0:110]

set origin 0.000,0.888 ; set label 1 'Argon'            at 280,90 right ; plot G4."argon.dat"            using 2:5 with points
set origin 0.500,0.888 ; set label 1 'Argon-AESNI'      at 280,90 right ; plot G4."argon-aesni.dat"      using 2:5 with points
set origin 0.000,0.777 ; set label 1 'Argon2d'          at 280,90 right ; plot G4."argon2d.dat"          using 2:5 with points
set origin 0.500,0.777 ; set label 1 'Argon2d-SSE'      at 280,90 right ; plot G4."argon2d-sse.dat"      using 2:5 with points
set origin 0.000,0.666 ; set label 1 'Argon2i'          at 280,90 right ; plot G4."argon2i.dat"          using 2:5 with points
set origin 0.500,0.666 ; set label 1 'Argon2i-SSE'      at 280,90 right ; plot G4."argon2i-sse.dat"      using 2:5 with points
set origin 0.000,0.555 ; set label 1 "battcrypt\n{/arial=10 without KDF mode}"        at 280,90 right ; plot G4."battcrypt.dat"        using 2:5 with points
set origin 0.500,0.555 ; set label 1 "Catena-Butterfly\n{/arial=10 without KDF mode}" at 280,90 right ; plot G4."catena-butterfly.dat" using 2:5 with points
set origin 0.000,0.444 ; set label 1 "Catena-Dragonfly\n{/arial=10 without KDF mode}" at 280,90 right ; plot G4."catena-dragonfly.dat" using 2:5 with points
set origin 0.500,0.444 ; set label 1 'Lyra2'            at 280,90 right ; plot G4."lyra2.dat"            using 2:5 with points
set origin 0.000,0.333 ; set label 1 'Lyra2-SSE'        at 280,90 right ; plot G4."lyra2-sse.dat"        using 2:5 with points
set origin 0.500,0.333 ; set label 1 'Makwa'            at 280,90 right ; plot G4."makwa.dat"            using 2:5 with points
set origin 0.000,0.222 ; set label 1 'Parallel'         at 280,90 right ; plot G4."parallel.dat"         using 2:5 with points
set origin 0.500,0.222 ; set label 1 'POMELO'           at 280,90 right ; plot G4."pomelo.dat"           using 2:5 with points
set origin 0.000,0.111 ; set label 1 'POMELO-SSE'       at 280,90 right ; plot G4."pomelo-sse.dat"       using 2:5 with points
set origin 0.500,0.111 ; set label 1 'Pufferfish'       at 280,90 right ; plot G4."pufferfish.dat"       using 2:5 with points
set origin 0.000,0.000 ; set label 1 'yescrypt'         at 280,90 right ; plot G4."yescrypt.dat"         using 2:5 with points
set origin 0.500,0.000 ; set label 1 'yescrypt-sse'     at 280,90 right ; plot G4."yescrypt-sse.dat"     using 2:5 with points

unset multiplot
