/*
Compile: make bug_resolving
Run: ./bug_resolving
Compile & run: make bug_resolving && ./bug_resolving
*/

#include "base.h"

#define N 5

// struct of a spacecraft
typedef struct Spacecraft{
    char* name;
    int passengers;
    double reach;
    double load_capacity;
}Spacecraft;

// struct of the fleet.
typedef struct Fleet{
    Spacecraft** ships;
    int maximum_count; //initialize to N, size of ships
    int current_count; //current count of spacecrafts in ships
}Fleet;

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

/*
 Erstzt die Berechnung des Token
 */
char* helper(char* s, int Mode){
    if (Mode == 1) {
        while(*s == ' ') s++;
    }
    char* s2 = s;
    while (*s != ' ' && *s != '\n') s++;
    
    char* token = xmalloc(s - s2 + 1);
    int i = 0;
    while (s2 < s){
        token[i] = *s2;
        i++;
        s2++;
    }
    token[i]= '\0';
    return token;
}

// returns a pointer to a dynamically allocated ship
Spacecraft* new_spacecraft(int passengers, double reach, double load_capacity, char* name){
    Spacecraft *spc = xmalloc(sizeof(Spacecraft));
    spc->passengers = passengers;
    spc->reach = reach;
    spc->load_capacity = load_capacity;
    spc->name = s_copy(name);
    return spc;
}

// prints a spacecraft
void print_spacecraft(Spacecraft* spc){
    printf("%12s with %3d passengers, a reach of %8.1f au and a load capacity of %4.1f t\n", spc->name, spc->passengers, spc->reach, spc->load_capacity);
}

// imports spacecrafts from file.
Fleet* read_spacecrafts(char* file_name){
    char* s = s_read_file(file_name);
    
    char* start = s;
    int ships = -1;
    while (*start != '\0'){
        if(*start == '\n')
            ships++;
        start++;
    }
    
    Fleet *fleet = xmalloc(sizeof(Fleet));
    fleet->current_count = ships;
    fleet->maximum_count = N;
    fleet->ships = xcalloc(N, sizeof(Spacecraft));
    
    while(*s != '\0'){
    Spacecraft *spc = NULL;
        
        //skip until line end
        while (*s != '\n') s++;
        
        s++;
        
        if(*s == '\0')
            break;

        char* name = helper(s,0);;
        free(helper(s, 0));
        
        int passengers = i_of_s(helper(s,1));
        free(helper(s, 1));
        
        double reach = d_of_s(helper(s,1));
        free(helper(s, 1));
        
        double load_capacity = d_of_s(helper(s,1));
        free(helper(s, 1));

        spc = new_spacecraft(passengers, reach, load_capacity, name);
        //print_spacecraft(spc);

        fleet->ships[ships-1] = spc;
        ships--;    }
    return fleet;
}

// prints the fleet.
void print_spacecrafts(Fleet* f){
    for(int i = 0; i< f->maximum_count; i++){
        if(f->ships[i]){
            printf("%2d\t", i);
            Spacecraft* spc = f->ships[i];
            printf("%12s with %3d passengers, a reach of %8.1f au and a load capacity of %4.1f t\n", spc->name, spc->passengers, spc->reach, spc->load_capacity);
            
        }
    }
}

// Entry point with command line arguments.
int main(int argc, String argv[]) {
    //base_init();
    //base_set_memory_check(true);
    report_memory_leaks ( true );

    Fleet* fleet = NULL;

    if(argc > 1){
        fleet = read_spacecrafts(argv[1]);
        free(read_spacecrafts(argv[1]));
    }else{
        fleet = read_spacecrafts("spacecrafts.txt");
        free(read_spacecrafts("spacecrafts.txt"));
    }

    char buffer[256];
    for(int i = 0; i< 256; i++){
        buffer[i] = '\0';
    }

    int c = '\0';
    printf("Your fleet: \n");
    print_spacecrafts(fleet);
    
    while((c = getchar()) != 'p'){
        if (c == 's'){
            //send out a ship, remove it from the fleet
            //example: s1
            //removes ship of index 1
            /*
             Ursprünglich hat der Code die Informationen des Schiffes am betreffenden Index = NULL gesetzt und somit gelöscht. Dadurch verbleiben die Schiffe auf höheren Indexen bei ihrer Position und es entstehen lücken.
             Nun werden alle Schiffe mit höherem Index einen Index nach unten geschoben und das Schiff am betreffenden Index überschrieben. Das Schiff am höhsten Index wird dann gelöscht, da es dupliziert wurde.
             */
            int index = getchar() - '0';
            if (index + 1 <= fleet->current_count) {
                for (int i = index; i < fleet->current_count - 1; i++) {
                    fleet->ships[i] = fleet->ships[i + 1];
                }
                fleet->ships[fleet->current_count - 1] = NULL;
                fleet->current_count--;
            }
        }else if (c == 'n'){
            //change name of ship
            //example: n1 Enterprise
            //renames ship at index 1 to Enterprise
            int index = getchar() - '0';
            getchar();
            int i = 0;
            while ((c = getchar()) != '\n'){
                buffer[i] = c;
                i++;
            }
            buffer[i] = '\0';
            fleet->ships[index]->name = s_copy(buffer);
        }else if (c == 'a'){
            //add ship
            //example: a Amagedon 34 500.3 2000.0
            if (fleet->current_count < fleet->maximum_count) {
                getchar();
                int i = 0;
                while ((c = getchar()) != '\n'){
                    buffer[i] = c;
                    i++;
                }
                buffer[i] = '\0';
                
                char* name = NULL;
                i = 0;
                for(; i< s_length(buffer); i++){
                    if(buffer[i] == ' '){
                        break;
                    }
                }
                
                name = s_sub(buffer, 0, i);
                i++;
                int j = i;
                printf("Char: '%c'\n", buffer[j]);
                for(; j< s_length(buffer); j++){
                    if(buffer[j] == ' '){
                        break;
                    }
                }
                printf("String: %s\n", s_sub(buffer, i, j));
                
                int passengers = i_of_s(s_sub(buffer, i, j));
                i = j++;
                for(; j< s_length(buffer); j++){
                    if(buffer[j] == ' '){
                        break;
                    }
                }
                double reach = d_of_s(s_sub(buffer, i, j));
                i = j++;
                for(; j < s_length(buffer); j++){
                    if(buffer[j] == ' '){
                        break;
                    }
                }
                
                double load_capacity =  d_of_s(s_sub(buffer, i, j));;
                
                Spacecraft* spc = new_spacecraft(passengers, reach, load_capacity, name);
                fleet->ships[fleet->current_count] = spc;
                fleet->current_count++;
            }
        }else if (c == 'q'){
            exit(0);
        }
        if(c == '\n'){
            printf("Your fleet: \n");
            print_spacecrafts(fleet);
        }
    }
    return 0;
}



