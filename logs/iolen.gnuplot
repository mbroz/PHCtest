set terminal png enhanced font "arial,18" fontscale 1.0 size 1600, 1000
set pointsize 1
set grid xtics
set grid ytics
set grid mytics

# Dir for graphs with data and output
G3='i_len/'
G4='o_len/'

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
