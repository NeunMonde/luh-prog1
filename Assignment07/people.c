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
    int Jahr[] = {};
    char Geschlecht[] = {};
    double Größe[] = {};
    String Name[] = {};
    
    while (s_get(table, i) != '\n') i++; // skip first row
    j = i + 1;
    while (i <= n) {
        if (s_get(table, i) != '\n') {
            if (s_get(table, i) == '\t') {
                k = i - 1;
                if (Spalte == 0) {
                    Jahr[Zeile] = i_of_s(s_sub(table, j, k));
                }
                else if (Spalte == 1) {
                    Geschlecht[Spalte] = s_get(table, k);
                }
                else if (Spalte == 2) {
                    Größe[Spalte] = d_of_s(s_sub(table, j, k));
                }
                else if (Spalte == 3) {
                    Name[Spalte] = s_sub(table, j, k);
                }
                j = i + 1;
                Spalte ++;
                
            }
        }
        else {
            Spalte = 0;
            Zeile ++;
        }
    }
    
    int Jahr_gesamt = 0;
    int Name_Länge = 0;
    int m_gesamt = 0;
    int f_gesamt = 0;
    int d_gesamt = 0;
    int Größe_m = 0;
    int Größe_f = 0;
    int Größe_d = 0;
    for (i = 0; i <= Zeile; i++) {
        Jahr_gesamt = Jahr_gesamt + Jahr[i];
        Name_Länge = Name_Länge + s_length(Name[i]);
        if (Geschlecht[i] == 'm') {
            m_gesamt++;
            Größe_m = Größe_m + Größe[i];
        }
        else if (Geschlecht[i] == 'f') {
            f_gesamt++;
            Größe_f = Größe_f + Größe[i];
        }
        else {
            d_gesamt++;
            Größe_d = Größe_d + Größe[i];
        }
    }
    
    ps.mean_year = round(Jahr_gesamt / Zeile);
    ps.number_males = m_gesamt;
    ps.number_females = f_gesamt;
    ps.number_diverse = d_gesamt;
    ps.mean_height_males = Größe_m / Zeile;
    ps.mean_height_females = Größe_f / Zeile;
    ps.mean_height_diverse = Größe_d / Zeile;
    ps.mean_length_of_names = Name_Länge / Zeile;
    
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


