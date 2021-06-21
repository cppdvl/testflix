* To compile go to the root folder:

```
mkdir build
cd build
cmake ..    
make -j
```
* Print help
```
./tesflix -h
```

* To find a list of movies:
```
./testflix -M

        [ 6650 ] The English Patient
        [ 25 ] Startgate
        [ 1685 ] The Adventures of Priscilla, Queen of the Desert
        [ 4167 ] Woman in the Dunes
        [ 2756 ] Max Max
        [ 3427 ] From Dusk Till Dawn
        [ 7772 ] Raiders of the Lost Ark
        [ 8675 ] Lawrence of Arabia ΓÇô 70mm
        [ 21448 ] Three Kings
        [ 59906 ] There will be Blood
        [ 62407 ] The Fall
        [ 184126 ] The Martian
```

* To find a list of theaters for Startgate (movie id: 25):
```
./testflix -m 25 -T

Startgate featured at the following locations:

        [ 8930 ] Cinema 4
        [ 8842 ] Cinema 1
        [ 10636 ] Cinema 6
        [ 8845 ] Cinema 2
        [ 9435 ] Cinema 5
        [ 42963 ] Cinema 7
```
* To See a list of available seats(xx):
```
./testflix.exe -m 25 -t 42963 

     0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
 0 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 1 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 2 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 3 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 4 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 5 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 6 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 7 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 8 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 9 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
10 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
11 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
12 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
13 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
14 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
15 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
16 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
17 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
18 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
19 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
20 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
21 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
22 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
23 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
24 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
25 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
26 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
27 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
28 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
29 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
30 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
31 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
```

* To Book one ticket at row 10 col 11:
```
./testflix.exe -m 25 -t 42963 -r 10 -c 11

Trying to get tickets for Startgate at Cinema 7
Booking location row: 10 col:11 qty: 1
Tickets Booked:

Row: 10, Col: 11


     0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
 0 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 1 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 2 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 3 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 4 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 5 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 6 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 7 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 8 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 9 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
10 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][  ][xx][xx][xx][xx]
11 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
12 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
13 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
14 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
15 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
16 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
17 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
18 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
19 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
20 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
21 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
22 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
23 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
24 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
25 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
26 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
27 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
28 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
29 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
30 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
31 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
```


* To Book 9 tickets at row 10 col 11:
```
./testflix.exe -m 25 -t 42963 -r 10 -c 11 -q 9

Trying to get tickets for Startgate at Cinema 7
Booking location row: 10 col:11 qty: 9
Tickets Booked:

Row: 10, Col: 11

Row: 10, Col: 10

Row: 10, Col: 9

Row: 10, Col: 8

Row: 10, Col: 7

Row: 10, Col: 6

Row: 10, Col: 5

Row: 10, Col: 4

Row: 10, Col: 3

```
     0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
 0 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 1 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 2 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 3 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 4 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 5 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 6 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 7 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 8 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
 9 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
10 [xx][xx][xx][  ][  ][  ][  ][  ][  ][  ][  ][  ][xx][xx][xx][xx]
11 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
12 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
13 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
14 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
15 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
16 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
17 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
18 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
19 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
20 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
21 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
22 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
23 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
24 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
25 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
26 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
27 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
28 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
29 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
30 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]
31 [xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx][xx]

```
