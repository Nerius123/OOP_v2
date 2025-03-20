# Kompiuterio charakteristikos

| Komponentas |             Specifikacija                 |
| :---------- |         :---------------------:           |
| CPU         | AMD Ryzen 5 2600 Six-Core Processor </br> |
| RAM         |             16GB DDR4 </br>               |
| DISK        |             SATA SSD </br>                |

# Kompiliavimo instrukcijos

1. [Atsisiusti g++](https://sourceforge.net/projects/mingw-w64/)
2. [Atsisiusti Make](https://gnuwin32.sourceforge.net/packages/make.htm)
3. Kopijuoti projekto direktorija `git clone https://github.com/Nerius123/OOP.git` (arba Download zip)
4. Atsidaryti komandine eilute projekto direktorijoje ir irasyti: `make -C Vectoriai ; make -C List ; make -C Deque`
5. Paleisti norima programos versija: `./Vectoriai/v0_1.exe`, `./List/list_main.exe`, `./Deque/deque_main.exe`

# Programos naudojimosi instrukcijos

Ši programa skirta studentų duomenų valdymui ir analizei, suteikiant galimybę įvesti, nuskaityti, rūšiuoti, generuoti ir analizuoti studentų informaciją. Meniu pateikiami šie pasirinkimai:

### Meniu pasirinkimai:

1. Pridėti naują studentą
   Leidžia vartotojui rankiniu būdu įvesti studento vardą, pavardę, namų darbų pažymius ir egzamino rezultatą.

2. Nuskaityti studentus iš failo
   Programa nuskaito studentų duomenis iš vartotojo nurodyto failo.

3. Spausdinti studentų sąrašą
    Leidžia atvaizduoti studentų sąrašą ekrane, pasirenkant galutinio balo skaičiavimo metodą (vidurkiu arba mediana).

4. Išsaugoti rezultatus į failą
   Programa leidžia išsaugoti apdorotus studentų duomenis į pasirinktą failą. Vartotojas gali pasirinkti, ar į failą įrašyti galutinius rezultatus pagal vidurkį, medianą ar abu būdus.

5. Generuoti studentų failus
   Automatiškai sugeneruoja failus su 1000, 10 000, 100 000, 1 000 000 ir 10 000 000 studentų duomenimis.

6. Skirstyti studentus į kategorijas
   Programa suskirsto studentus į dvi grupes:

   - "Kietiakiai" (studentai, kurių galutinis balas >= 5.0)
   - "Vargšiukai" (studentai, kurių galutinis balas < 5.0)
   Vartotojas gali pasirinkti, ar skirstymas atliekamas pagal vidurkį ar medianą. Taip pat galima pasirinkti rūšiavimo tvarką (didėjančią arba mažėjančią).

7. Testuoti duomenų apdorojimo greitį
   Programa išmatuoja laiką, per kurį:

   - Nuskaitomi duomenys iš failo
   - Studentai rūšiuojami didėjančia tvarka
   - Studentai skirstomi į dvi grupes
   - Rezultatai išsaugomi į atskirus failus

8. Baigti programą
   Programa baigia darbą.

# Pradinė versija

Pradinėje programos versijoje buvo sukurta bazinė studentų valdymo sistema, leidžianti rankiniu būdu įvesti studentų vardus, pavardes, namų darbų pažymius ir egzamino rezultatą. Taip pat buvo įgyvendintos funkcijos, skirtos galutinio pažymio skaičiavimui pagal vidurkį arba medianą.

# v0.1 versija

Optimizuota v.pradine versija, programai nebereikia iš anksto žinoti, kiek viso bus studentų ir namų darbų.

Ši versija realizuota dviem būdais:

1. Naudojamas masyvas pazymiu saugojimui;
2. Naudojamas std::vector tipo konteineris studentų ir pažymių saugojimui.

# v0.2 versija

Į meniu pridėti pasirinkimai 5: 

1. Įvesti studentų vardą, pavardė, pažymius raniniu būdu.
2. Nuskaityti iš failo
3. Išspausdinti studentu sąrašą
4. Išsaugoti studentų sąrašą į failą 
4. Baigti programa.

# v0.3 versija

Pridėta klaidų gaudymo sistema.

# v0.4 versija
Pridėta galimybė generuoti failus, iš kurių vėliau bus nuskaitoma informacija. Visi sugeneruoti failai saugomi atskirame aplanke "SukurtiTxtFailai". Pridėtas pasirinkimas - išvesti studentus į du atskirus failus: "kietiakai.txt" ir "vargsikai.txt" pagal galutinį pažymį (≥ 5.0 – "kietekai", < 5.0 – "vargsiukai"). Ir galiausiai pridėta programos veikimo greičio testavimas.

# v1.0 pradinė versija

Sukurtos trys programos versijos, naudojančios skirtingus konteinerius: std::vector, std::list ir std::deque.

# Programos testavimo rezultatai pradiniam v1.0 release

## 1000 Studentų analizė

Viso faile yra 14 namų darbų pažymių

### Nuskaitymas (sek.):

|          |    Vector |      List |     Deque |
| :------- | --------: | --------: | --------: |
| 1 testas | 0.00433   | 0.02607   | 0.02392   |
| 2 testas | 0.00416   | 0.00747   | 0.00452   |
| 3 testas | 0.00403   | 0.00741   | 0.00430   |

### Rusiavimas faile (sek.):

|          |    Vector |      List |     Deque |
| :------- | --------: | --------: | --------: |
| 1 testas | 0.00403   | 0.00308   | 0.00496   |
| 2 testas | 0.00396   | 0.00305   | 0.00487   |
| 3 testas | 0.00393   | 0.00307   | 0.00503   |

### Rusiavimas i kietekus ir vargsiukus (sek.):

|          |    Vector |      List |     Deque |
| :------- | --------: | --------: | --------: |
| 1 testas | 0.00050   |  0.00180  | 0.00078   |
| 2 testas | 0.00045   |  0.00177  | 0.00073   |
| 3 testas | 0.00046   |  0.00181  | 0.00072   |

### Vidurkiai (sek.):

|                                                           |   Vector |         List |      Deque |
| :-------------------------------------------------------- | -------: | -----------: | ---------: |
| Bendras failo nuskaitymo laikas                           | 0.01252  |     0.03555  |   0.03274  |
| Vidutinis failo nuskaitymo laikas                         | 0.004173 |     0.01185  |   0.010913 |
| Bendras failo rusiavimo laikas                            | 0.01192  |     0.00920  |   0.01486  |
| Vidutinis failo rusiavimo laikas                          | 0.003973 |     0.003067 |   0.004953 |
| Bendras failo rusiavimo i kietekus ir vargsiukus laikas   | 0.00141  |     0.00316  |   0.00223  |
| Vidutinis failo rusiavimo i kietekus ir vargsiukus laikas | 0.00047  |     0.001053 |   0.000743 |
| Bendras programos veikimo laikas                          | 0.02585  |     0.04791  |   0.04983  |
| Vidutinis programos veikimo laikas                        | 0.00862  |     0.01597  |   0.01661  |

## 10000 Studentu analize

Viso faile yra 14 namų darbų pažymių

### Nuskaitymas (sek.):

|          |    Vector |      List |     Deque |
| :------- | --------: | --------: | --------: |
| 1 testas | 0.04891   | 0.08068   | 0.05620   |
| 2 testas | 0.03774   | 0.07212   | 0.03896   |
| 3 testas | 0.03758   | 0.08058   | 0.03932   |

### Rusiavimas faile (sek.):

|          |    Vector |      List |     Deque |
| :------- | --------: | --------: | --------: |
| 1 testas | 0.04876   | 0.04820   |  0.06068  |
| 2 testas | 0.04968   | 0.05016   |  0.06121  |
| 3 testas | 0.05773   | 0.04820   | 0.06142   |

### Rusiavimas i kietekus ir vargsiukus (sek.):

|          |    Vector |      List |     Deque |
| :------- | --------: | --------: | --------: |
| 1 testas | 0.00465   | 0.02210   |  0.00773  |
| 2 testas | 0.00464   | 0.02313   |  0.00754  |
| 3 testas | 0.00476   | 0.02221   |  0.00785  |

### Vidurkiai (sek.):

|                                                           |   Vector |         List |      Deque |
| :-------------------------------------------------------- | -------: | -----------: | ---------: |
| Bendras failo nuskaitymo laikas                           | 0.12423  |     0.23838  |   0.13448  |
| Vidutinis failo nuskaitymo laikas                         | 0.04141  |     0.07946  |   0.044826 |
| Bendras failo rusiavimo laikas                            | 0.15617  |     0.14656  |   0.18331  |
| Vidutinis failo rusiavimo laikas                          | 0.052056 |     0.048853 |   0.061103 |
| Bendras failo rusiavimo i kietekus ir vargsiukus laikas   | 0.01387  |     0.06744  |   0.02312  |
| Vidutinis failo rusiavimo i kietekus ir vargsiukus laikas | 0.004623 |     0.02248  |   0.007707 |
| Bendras programos veikimo laikas                          | 0.29445  |     0.44738  |   0.34072  |
| Vidutinis programos veikimo laikas                        | 0.05889  |     0.089476 |   0.068144 |

## 100000 Studentu analize

Viso faile yra 14 namų darbų pažymių

### Nuskaitymas (sek.):

|          |   Vector |     List |    Deque |
| :------- | -------: | -------: | -------: |
| 1 testas | 0.37975  | 0.72603  | 0.46188  |
| 2 testas | 0.37080  | 0.71785  | 0.38979  |
| 3 testas | 0.37194  | 0.73215  | 0.40234  |

### Rusiavimas faile (sek.):

|          |   Vector |    List |   Deque |
| :------- | -------: | ------: | ------: |
| 1 testas | 0.61492  | 0.77987 | 0.81119 |
| 2 testas | 0.61680  | 0.76743 | 0.79736 |
| 3 testas | 0.60944  | 0.73856 | 0.80112 |

### Rusiavimas i kietekus ir vargsiukus (sek.):

|          |    Vector |      List |     Deque |
| :------- | --------: | --------: | --------: |
| 1 testas | 0.04925   | 0.23585   | 0.08309   |
| 2 testas | 0.04894   | 0.10202   | 0.08229   |
| 3 testas | 0.04949   | 0.23366   | 0.08311   |

### Vidurkiai (sek.):

|                                                           |   Vector |      List |     Deque |
| :-------------------------------------------------------- | -------: | --------: | --------: |
| Bendras failo nuskaitymo laikas                           | 1.122490 | 2.176030 | 1.254010 |
| Vidutinis failo nuskaitymo laikas                         | 0.374163 | 0.725343 | 0.418003 |
| Bendras failo rusiavimo laikas                            | 1.841160 | 2.285860 | 2.409670 |
| Vidutinis failo rusiavimo laikas                          | 0.613720 | 0.761953 | 0.803223 |
| Bendras failo rusiavimo i kietekus ir vargsiukus laikas   | 0.147680 | 0.571530 | 0.248490 |
| Vidutinis failo rusiavimo i kietekus ir vargsiukus laikas | 0.049227 | 0.190510 | 0.082830 |
| Bendras programos veikimo laikas                          | 3.111330 | 5.033420 | 3.912170 |
| Vidutinis programos veikimo laikas                        | 1.037110 | 1.677807 | 1.304057 |

## 1000000 Studentu analize

Viso faile yra 14 namų darbų pažymių

### Nuskaitymas (sek.):

|          |  Vector |    List |   Deque |
| :------- | ------: | ------: | ------: |
| 1 testas | 3.79454 | 7.22300 | 3.95160 |
| 2 testas | 3.76253 | 7.70632 | 3.95980 |
| 3 testas | 3.73542 | 7.30788 | 3.98991 |

### Rusiavimas faile (sek.):

|          |  Vector |    List |   Deque |
| :------- | ------: | ------: | ------: |
| 1 testas | 8.10504 | 10.76965| 10.64053|
| 2 testas | 7.98596 | 10.96013| 10.68764|
| 3 testas | 7.98624 | 12.77413| 10.66421|

### Rusiavimas i kietekus ir vargsiukus (sek.):

|          |   Vector |     List |    Deque |
| :------- | -------: | -------: | -------: |
| 1 testas | 0.53250  | 2.45736  | 0.88335  |
| 2 testas | 0.52098  | 2.44533  | 0.88069  |
| 3 testas | 0.52576  | 2.62545  | 0.88221  |

### Vidurkiai (sek.):

|                                                           |   Vector |      List |     Deque |
| :-------------------------------------------------------- | -------: | --------: | --------: |
| Bendras failo nuskaitymo laikas                           | 11.29164 | 21.64089 | 11.91904 |
| Vidutinis failo nuskaitymo laikas                         |  3.76388 |  7.21363 |  3.97301 |
| Bendras failo rusiavimo laikas                            | 24.17646 | 32.73608 | 31.99269 |
| Vidutinis failo rusiavimo laikas                          |  8.05882 | 10.91203 | 10.66423 |
| Bendras failo rusiavimo i kietekus ir vargsiukus laikas   |  1.57824 |  7.52964 |  2.64608 |
| Vidutinis failo rusiavimo i kietekus ir vargsiukus laikas |  0.52608 |  2.50988 |  0.88203 |
| Bendras programos veikimo laikas                          | 36.94634 | 61.90661 | 46.55781 |
| Vidutinis programos veikimo laikas                        | 12.31545 | 20.63554 | 15.51927 |


## 10000000 Studentu analize

Viso faile yra 14 namų darbų pažymių

### Nuskaitymas (sek.):

|          |  Vector |    List |   Deque |
| :------- | ------: | ------: | ------: |
| 1 testas | 37.36653| 47.59042| 41.17769|
| 2 testas | 37.75659| 45.81523| 42.22239|
| 3 testas | 37.91062| 46.59042| 41.65897|

### Rusiavimas faile (sek.):

|          |  Vector |    List   |   Deque  |
| :------- | ------: | ------:   | ------:  |
| 1 testas | 97.76144| 144.90729 | 131.83495|
| 2 testas | 97.63307| 143.85629 | 130.30423|
| 3 testas | 98.59099| 144.78423 | 129.46221|

### Rusiavimas i kietekus ir vargsiukus (sek.):

|          |  Vector |    List |   Deque  |
| :------- | ------: | ------: | ------:  |
| 1 testas | 5.22476 | 26.28797| 14.71335 |
| 2 testas | 5.32009 | 25.98346| 14.99932 |
| 3 testas | 5.28132 | 25.24299| 13.72135 |

### Vidurkiai (sek.):

|                                                           |   Vector |      List |     Deque |
| :-------------------------------------------------------- | -------: | --------: | --------: |
| Bendras failo nuskaitymo laikas                           | 113.0336 | 139.0247  | 125.0782  |
| Vidutinis failo nuskaitymo laikas                         |  37.6779 |  46.3416  |  41.6927  |
| Bendras failo rusiavimo laikas                            | 293.0309 | 435.9934  | 390.5497  |
| Vidutinis failo rusiavimo laikas                          |  97.6769 | 145.3311  | 130.1832  |
| Bendras failo rusiavimo i kietekus ir vargsiukus laikas   |  15.8076 |  78.5433  |  41.1487  |
| Vidutinis failo rusiavimo i kietekus ir vargsiukus laikas |   5.2692 |  26.1811  |  13.7162  |
| Bendras programos veikimo laikas                          | 421.8721 | 653.5614  | 556.7766  |
| Vidutinis programos veikimo laikas                        | 140.6240 | 217.8538  | 185.5922  |


## 5 failų generavimo laikas

![image](https://raw.githubusercontent.com/Nerius123/OOP/refs/heads/v0.4/Bendras/Screenshot%202025-03-07%20000236.png)