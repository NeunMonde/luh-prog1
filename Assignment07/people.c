/*
Compile: make people
Run: ./people
*/

#include "base.h"

// Represents statistics of a people table.
struct Statistics {
    int mean_year;
    int number_males;
    int number_females;
    int number_diverse;
    double mean_height_males; // in m
    double mean_height_females; // in m
    double mean_height_diverse; // in m
    double mean_length_of_names;
};

typedef struct Statistics Statistics;


//Returns substring of s from character i to character j
String s_sub(String s, int i, int j) {
    require_not_null(s);
    int n = strlen(s);
    if (i < 0) i = 0;
    if (j > n) j = n;
    if (i >= j || i >= n || j <= 0) {
        char *a = xmalloc(1 * sizeof(char));
        a[0] = '\0';
        return a;
    }
    // assert i < j && i < n && j > 0
    n = j - i;
    char *a = xmalloc((n + 1) * sizeof(char));
    memcpy(a, s + i, n * sizeof(char));
    a[n] = '\0';
    return a;
}


Statistics make_statistics(void) {
    Statistics ps = { 0, 0, 0, 0, 0.0, 0.0, 0.0, 0.0};
    return ps;
}

void print_statistics(Statistics s) {
    printf("mean year: %d\n", s.mean_year);
    printf("number males: %d\n", s.number_males);
    printf("number females: %d\n", s.number_females);
    printf("number diverse: %d\n", s.number_diverse);
    printf("mean height males: %.2f\n", s.mean_height_males);
    printf("mean height females: %.2f\n", s.mean_height_females);
    printf("mean height diverse: %.2f\n", s.mean_height_diverse);
    printf("mean length of names: %3.2f characters\n", s.mean_length_of_names);

}

Statistics compute_statistics(String table) {
    Statistics ps = make_statistics();
    int n = s_length(table);
    int i = 0; //aktuelle Position im String
    int j = 0;
    int k = 0;
    int Spalte = 0;
    int Zeile = 0;
    char Geschlecht_in_Zeile = 'n';
    int Jahr_gesamt = 0;
    int Anzahl_m = 0;
    int Anzahl_f = 0;
    int Anzahl_d = 0;
    double Größe_gesamt_m = 0.0;
    double Größe_gesamt_f = 0.0;
    double Größe_gesamt_d = 0.0;
    double Namenlänge_gesamt = 0.0;
    
    while (s_get(table, i) != '\n') i++; // skip first row
    int test = i;
    j = i + 1;
    for (int i = test; i < n; i++) {
        if (s_get(table, i) != '\n') {
            if (s_get(table, i) == '\t') {
                k = i - 1;
                if (Spalte == 0) {
                    Jahr_gesamt = Jahr_gesamt + i_of_s(s_sub(table, j, k));
                }
                else if (Spalte == 1) {
                    if (s_get(table, k) == 'm') {
                        Anzahl_m++;
                        Geschlecht_in_Zeile = 'm';
                    }
                    else if (s_get(table, k) == 'f') {
                        Anzahl_f++;
                        Geschlecht_in_Zeile = 'f';
                    }
                    else {
                        Anzahl_d++;
                        Geschlecht_in_Zeile = 'd';
                    }
                }
                else if (Spalte == 2) {
                    if (Geschlecht_in_Zeile == 'm') {
                        Größe_gesamt_m = Größe_gesamt_m + d_of_s(s_sub(table, j, k));
                    }
                    else if (Geschlecht_in_Zeile == 'f') {
                        Größe_gesamt_f = Größe_gesamt_f + d_of_s(s_sub(table, j, k));
                    }
                    else {
                        Größe_gesamt_d = Größe_gesamt_d + d_of_s(s_sub(table, j, k));
                    }
                }
                j = i + 1;
                Spalte ++;
            }
        }
        else {
            k = i - 1;
            Namenlänge_gesamt = Namenlänge_gesamt + s_length(s_sub(table, j, k));
            Spalte = 0;
            j = i + 1;
            Zeile++;
        }
    }
    
    ps.mean_year = round(Jahr_gesamt / Zeile);
    ps.number_males = Anzahl_m;
    ps.number_females = Anzahl_f;
    ps.number_diverse = Anzahl_d;
    ps.mean_height_males = Größe_gesamt_m / Anzahl_m;
    ps.mean_height_females = Größe_gesamt_f / Anzahl_f;
    ps.mean_height_diverse = Größe_gesamt_d / Anzahl_d;
    ps.mean_length_of_names = Namenlänge_gesamt / Zeile;
    
    return ps;
}


int main(void) {
    String table = s_read_file("people.txt");
    Statistics s = compute_statistics(table);
    print_statistics(s);
    
    /*
    Erwartete Ausgabe:
    
    mean year: 1974
    number males: 445
    number females: 455
    number diverse: 100
    mean height males: 1.79
    mean height females: 1.64
    mean height diverse: 1.61
    mean length of names: 13.20
    */
    
    return 0;
}


