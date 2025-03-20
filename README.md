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
4. Atsidaryti komandine eilute projekto direktorijoje ir irasyti: `make -C Vector ; make -C List ; make -C Deque`
5. Paleisti norima programos versija: `./Vector/v0_1.exe`, `./List/list_main.exe`, `./Deque/deque_main.exe`

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
| 1 testas | 0.00433   | 0.02607   | 0.0145365 |
| 2 testas | 0.00416   | 0.00747   |  0.007807 |
| 3 testas | 0.00403   | 0.00741   | 0.0067956 |

### Rusiavimas faile (sek.):

|          |    Vector |      List |     Deque |
| :------- | --------: | --------: | --------: |
| 1 testas | 0.00403   | 0.00308   | 0.0077588 |
| 2 testas | 0.00396   | 0.00305   | 0.0096666 |
| 3 testas | 0.00393   | 0.00307   | 0.0076848 |

### Rusiavimas i kietekus ir vargsiukus (sek.):

|          |    Vector |      List |     Deque |
| :------- | --------: | --------: | --------: |
| 1 testas | 0.00050   |  0.00180  | 0.0007002 |
| 2 testas | 0.00045   |  0.00177  | 0.0008425 |
| 3 testas | 0.00046   |  0.00181  | 0.0008806 |

### Vidurkiai (sek.):

|                                                           |   Vector |         List |      Deque |
| :-------------------------------------------------------- | -------: | -----------: | ---------: |
| Bendras failo nuskaitymo laikas                           | 0.016316 |     0.017256 |   0.029139 |
| Vidutinis failo nuskaitymo laikas                         | 0.005439 |     0.005752 |   0.009713 |
| Bendras failo rusiavimo laikas                            | 0.013759 |     0.009965 |   0.025110 |
| Vidutinis failo rusiavimo laikas                          | 0.002293 |     0.001661 |   0.004185 |
| Bendras failo rusiavimo i kietekus ir vargsiukus laikas   | 0.002034 |     0.001650 |   0.002423 |
| Vidutinis failo rusiavimo i kietekus ir vargsiukus laikas | 0.000678 |     0.000550 |   0.000808 |
| Bendras programos veikimo laikas                          | 0.032109 |     0.028871 |   0,282662 |
| Vidutinis programos veikimo laikas                        | 0.010703 | 0.0096236667 | 0.09422066 |

## 10000 Studentu analize

Viso faile yra 14 namų darbų pažymių

### Nuskaitymas (sek.):

|          |    Vector |      List |     Deque |
| :------- | --------: | --------: | --------: |
| 1 testas | 0.04891   | 0.08068   | 0.0722085 |
| 2 testas | 0.03774   | 0.07212   | 0.0647305 |
| 3 testas | 0.03758   | 0.08058   | 0.0690108 |

### Rusiavimas faile (sek.):

|          |    Vector |      List |     Deque |
| :------- | --------: | --------: | --------: |
| 1 testas | 0.04876   | 0.04820   |  0.102892 |
| 2 testas | 0.04968   | 0.05016   |   0.10707 |
| 3 testas | 0.05773   | 0.04820   | 0.0987082 |

### Rusiavimas i kietekus ir vargsiukus (sek.):

|          |    Vector |      List |     Deque |
| :------- | --------: | --------: | --------: |
| 1 testas | 0.00465   | 0.02210   | 0.0074288 |
| 2 testas | 0.00464   | 0.02313   | 0.0124954 |
| 3 testas | 0.00476   | 0.02221   |  0.007408 |

### Vidurkiai (sek.):

|                                                           |   Vector |         List |      Deque |
| :-------------------------------------------------------- | -------: | -----------: | ---------: |
| Bendras failo nuskaitymo laikas                           | 0.133990 |     0.221309 |   0.205950 |
| Vidutinis failo nuskaitymo laikas                         | 0.044663 |     0.073770 |   0.068650 |
| Bendras failo rusiavimo laikas                            | 0.167915 |     0.257783 |   0.308670 |
| Vidutinis failo rusiavimo laikas                          | 0.027986 |     0.042964 |   0.051445 |
| Bendras failo rusiavimo i kietekus ir vargsiukus laikas   | 0.018534 |     0.031990 |   0.027332 |
| Vidutinis failo rusiavimo i kietekus ir vargsiukus laikas | 0.006178 |     0.010663 |   0.009111 |
| Bendras programos veikimo laikas                          | 0.320439 |     0.511082 |   0.541952 |
| Vidutinis programos veikimo laikas                        | 0.106813 | 0.1703606667 | 0.18065066 |

## 100000 Studentu analize

Viso faile yra 14 namų darbų pažymių

### Nuskaitymas (sek.):

|          |   Vector |     List |    Deque |
| :------- | -------: | -------: | -------: |
| 1 testas | 0.37975  | 0.72603  | 0.530389 |
| 2 testas | 0.37080  | 0.71785  | 0.533229 |
| 3 testas | 0.37194  | 0.73215  | 0.537504 |

### Rusiavimas faile (sek.):

|          |   Vector |    List |   Deque |
| :------- | -------: | ------: | ------: |
| 1 testas | 0.61492  | 0.77987 | 1.31066 |
| 2 testas | 0.61680  | 0.76743 | 1.26595 |
| 3 testas | 0.60944  | 0.73856 | 1.28526 |

### Rusiavimas i kietekus ir vargsiukus (sek.):

|          |    Vector |      List |     Deque |
| :------- | --------: | --------: | --------: |
| 1 testas | 0.04925   | 0.23585   | 0.0756288 |
| 2 testas | 0.04894   | 0.10202   | 0.0733271 |
| 3 testas | 0.04949   | 0.23366   | 0.0774862 |

### Vidurkiai (sek.):

|                                                           |   Vector |      List |     Deque |
| :-------------------------------------------------------- | -------: | --------: | --------: |
| Bendras failo nuskaitymo laikas                           | 0.980052 |  1.777449 |  1.601122 |
| Vidutinis failo nuskaitymo laikas                         | 0.326684 |  0.592483 |  0.533707 |
| Bendras failo rusiavimo laikas                            | 2.031878 |  3.235127 |  3.861866 |
| Vidutinis failo rusiavimo laikas                          | 0.338646 |  0.539188 |  0.643644 |
| Bendras failo rusiavimo i kietekus ir vargsiukus laikas   | 0.170317 |  0.285555 |  0.226442 |
| Vidutinis failo rusiavimo i kietekus ir vargsiukus laikas | 0.056772 |  0.095185 |  0.075481 |
| Bendras programos veikimo laikas                          | 3.182247 |  5.298131 |   5.68943 |
| Vidutinis programos veikimo laikas                        | 1.060749 | 1.7660436 | 1.8967466 |

## 1000000 Studentu analize

Viso faile yra 14 namų darbų pažymių

### Nuskaitymas (sek.):

|          |  Vector |    List |   Deque |
| :------- | ------: | ------: | ------: |
| 1 testas | 3.79454 | 7.22300 | 6.40691 |
| 2 testas | 3.76253 | 7.70632 | 6.42821 |
| 3 testas | 3.73542 | 7.30788 | 6.49617 |

### Rusiavimas faile (sek.):

|          |  Vector |    List |   Deque |
| :------- | ------: | ------: | ------: |
| 1 testas | 8.10504 | 10.76965| 14.4732 |
| 2 testas | 7.98596 | 10.96013| 14.8146 |
| 3 testas | 7.98624 | 12.77413| 14.3128 |

### Rusiavimas i kietekus ir vargsiukus (sek.):

|          |   Vector |     List |    Deque |
| :------- | -------: | -------: | -------: |
| 1 testas | 0.53250  | 2.45736  |  0.90257 |
| 2 testas | 0.52098  | 2.44533  | 0.921527 |
| 3 testas | 0.52576  | 2.62545  | 0.940349 |

### Vidurkiai (sek.):

|                                                           |        Vector |        List |       Deque |
| :-------------------------------------------------------- | ------------: | ----------: | ----------: |
| Bendras failo nuskaitymo laikas                           |     11.669734 |   20.726261 |   19.331293 |
| Vidutinis failo nuskaitymo laikas                         |      3.889911 |    6.908754 |    6.443764 |
| Bendras failo rusiavimo laikas                            |     29.524652 |   39.448779 |   43.600653 |
| Vidutinis failo rusiavimo laikas                          |      4.920775 |    6.574797 |    7.266776 |
| Bendras failo rusiavimo i kietekus ir vargsiukus laikas   |      1.723741 |    2.898165 |    2.764446 |
| Vidutinis failo rusiavimo i kietekus ir vargsiukus laikas |      0.574580 |    0.966055 |    0.921482 |
| Bendras programos veikimo laikas                          |     42.918127 |   63.073205 |   65.696392 |
| Vidutinis programos veikimo laikas                        | 14.3060423333 | 21.02440166 | 21.89879733 |

## 10000000 Studentu analize

Viso faile yra 19 namų darbų pažymių

### Nuskaitymas (sek.):

|          |  Vector |    List |   Deque |
| :------- | ------: | ------: | ------: |
| 1 testas | 37.36653| 72.93068| 45.5688 |
| 2 testas | 37.75659|  45.815 | 45.0055 |
| 3 testas | 37.91062| 46.5904 | 50.5224 |

### Rusiavimas faile (sek.):

|          |  Vector |    List   |   Deque |
| :------- | ------: | ------:   | ------: |
| 1 testas | 97.76144| 144.90729 | 130.304 |
| 2 testas | 97.63307| 143.85629 | 128.954 |
| 3 testas | 98.59099| 144.78423 | 129.462 |

### Rusiavimas i kietekus ir vargsiukus (sek.):

|          |  Vector |    List |   Deque |
| :------- | ------: | ------: | ------: |
| 1 testas | 5.22476 | 26.28797 | 8.20431 |
| 2 testas | 5.32009 | 25.98346 | 8.78032 |
| 3 testas | 5.28132 | 25.24299 | 8.81014 |

### Vidurkiai (sek.):

|                                                           |     Vector |       List |        Deque |
| :-------------------------------------------------------- | ---------: | ---------: | -----------: |
| Bendras failo nuskaitymo laikas                           | 130.347577 | 148.193507 |   141.096647 |
| Vidutinis failo nuskaitymo laikas                         |  43.449192 |  49.397836 |    47.032216 |
| Bendras failo rusiavimo laikas                            | 357.935381 | 345.401288 |   388.718866 |
| Vidutinis failo rusiavimo laikas                          |  59.655897 |  57.566881 |    64.786478 |
| Bendras failo rusiavimo i kietekus ir vargsiukus laikas   |  19.468074 |  31.311419 |    25.794769 |
| Vidutinis failo rusiavimo i kietekus ir vargsiukus laikas |   6.489358 |  10.437140 |     8.598256 |
| Bendras programos veikimo laikas                          | 507.751032 | 524.906214 |   555.610282 |
| Vidutinis programos veikimo laikas                        | 169.250344 | 174.968738 | 185.20342733 |

## 5 failų generavimo laikas

![image](https://raw.githubusercontent.com/Nerius123/OOP/refs/heads/v0.4/Bendras/Screenshot%202025-03-07%20000236.png)