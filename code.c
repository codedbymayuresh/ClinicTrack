#include<stdio.h>
#include<string.h>

typedef struct Patient
{
    char name[100];
    int id;
}Pt;

void AddPatient(Pt *p, int id);
void actions(char ch, char chh, int oldid);
void showallpatients();
void searchpatient();
void Addnew(int id);

int main()
{
    int n;
    int patientID = 0;
    FILE *fptr = fopen("clinicdata.txt", "r");

    if (fptr == NULL) {
        // File doesn't exist
        printf("Data doesn't exist, so you need to create new data.\n");
        printf("Enter total number of patients to register: ");
        scanf("%d", &n);
        getchar();

        Pt patient[n];

        FILE *ffptr = fopen("clinicdata.txt", "w");
        for (int i = 0; i < n; i++) {
            patientID++;
            AddPatient(&patient[i], patientID);
            fprintf(ffptr, "%d\n", patient[i].id);
            fprintf(ffptr, "%s\n", patient[i].name);
        }
        fclose(ffptr);
    } else {
        // File exists, check size
        fseek(fptr, 0, SEEK_END);
        long size = ftell(fptr);
        fclose(fptr);

        if (size == 0) {
            // File is empty
            printf("File exists but is empty. Creating new data.\n");
            printf("Enter total number of patients to register: ");
            scanf("%d", &n);
            getchar();

            Pt patient[n];
            FILE *ffptr = fopen("clinicdata.txt", "w");
            for (int i = 0; i < n; i++) {
                patientID++;
                AddPatient(&patient[i], patientID);
                fprintf(ffptr, "%d\n", patient[i].id);
                fprintf(ffptr, "%s\n", patient[i].name);
            }
            fclose(ffptr);
        } else {
            // File has some data
            char data;
            printf("Old data found.\nOptions:\nA) Continue with old data\nB) Overwrite old data\nEnter your choice: ");
            scanf(" %c", &data); // space before %c to skip newline
            getchar();

            if (data == 'A') {
                Addnew(patientID);
            } else if (data == 'B') {
                printf("Enter total number of patients to register: ");
                scanf("%d", &n);
                getchar();

                Pt patient[n];
                FILE *f = fopen("clinicdata.txt", "w");
                for (int i = 0; i < n; i++) {
                    patientID++;
                    AddPatient(&patient[i], patientID);
                    fprintf(f, "%d\n", patient[i].id);
                    fprintf(f, "%s\n", patient[i].name);
                }
                fclose(f);
            } else {
                printf("No such action is designed.\n");
            }
        }
    }

    char c, cs;
    actions(c, cs, patientID);

    return 0;
}

void AddPatient(Pt *p, int id){
    printf("Enter patient name: ");
    fgets(p->name, 100, stdin);
    size_t len = strlen(p->name);
    if (len > 0 && p->name[len - 1] == '\n') {
        p->name[len - 1] = '\0';
    }
    p->id = id;
}

void actions(char ch, char chh, int oldid){
    printf("Do you want to know what you can do in this program? \nType 'Y' for yes and 'N' for no: ");
    scanf("%c", &ch);
    getchar(); // clear newline
    if(ch == 'Y'){
        printf("Options:\nA) Show all patients\nB) Search patient by ID\nC) Add a new patient\n");
        scanf("%c", &chh);
        if(chh == 'A'){
            showallpatients();
        } else if(chh == 'B'){
            searchpatient();
        } else if(chh == 'C'){
            Addnew(oldid);
        } else {
            printf("No such action is designed.\n");
        }
    }
}

void showallpatients(){
    FILE *fptr;
    char line[200];

    fptr = fopen("clinicdata.txt", "r");
    if (fptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    printf("Patients Registered:\n\n");
    while (fgets(line, sizeof(line), fptr)){
        printf("%s", line);
    }
    fclose(fptr);
}

void searchpatient(){
    int search;
    printf("Enter ID of the patient: ");
    scanf("%d", &search);

    FILE *fptr;
    fptr = fopen("clinicdata.txt", "r");
    if (fptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    int id, found = 0;
    char name[100];

    while (fscanf(fptr, "%d\n", &id) == 1) {
        fgets(name, sizeof(name), fptr);
        size_t len = strlen(name);
        if (len > 0 && name[len - 1] == '\n') {
            name[len - 1] = '\0';
        }

        if (id == search) {
            printf("Patient Found: %s\n", name);
            found = 1;
            break;
        }
    }

    if (!found){
        printf("Patient with the given ID not found.\n");
    }

    fclose(fptr);
}

void Addnew(int id){
    int n;
    printf("Enter how many more patients you want to add: ");
    scanf("%d", &n);
    getchar();

    int pid = id;
    int n_ = n + id;
    Pt patient[n_];

    FILE *fptr;
    fptr = fopen("clinicdata.txt", "a");

    for (int i = id; i < n_; i++) {
        pid++;
        AddPatient(&patient[i], pid);
        fprintf(fptr, "%d\n", patient[i].id);
        fprintf(fptr, "%s\n", patient[i].name);
    }

    fclose(fptr);
}
