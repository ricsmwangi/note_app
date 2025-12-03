#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 64
#define MAX_BODY 1024
#define NOTES_FILE "notes.db"

typedef struct {
    int id;
    char title[MAX_TITLE];
    char body[MAX_BODY];
} Note;

static int next_id(FILE *fp) {
    int max = 0; Note n;
    rewind(fp);
    while (fread(&n, sizeof(Note), 1, fp) == 1) if (n.id > max) max = n.id;
    return max + 1;
}

static void list_notes(FILE *fp) {
    Note n; int count = 0; rewind(fp);
    while (fread(&n, sizeof(Note), 1, fp) == 1) {
        printf("[%d] %s\n", n.id, n.title);
        count++;
    }
    if (!count) printf("No notes.\n");
}

static int read_line(char *buf, size_t sz) {
    if (!fgets(buf, sz, stdin)) return 0;
    size_t len = strlen(buf);
    if (len && buf[len-1] == '\n') buf[len-1] = '\0';
    return 1;
}

static void create_note(FILE *fp) {
    Note n = {0}; char buf[MAX_BODY];
    printf("Title: "); if (!read_line(n.title, sizeof n.title)) return;
    printf("Body (end with empty line):\n");
    buf[0] = '\0';
    char line[256];
    while (read_line(line, sizeof line)) {
        if (line[0] == '\0') break;
        if (strlen(buf) + strlen(line) + 2 >= sizeof buf) { printf("Body too long.\n"); break; }
        strcat(buf, line); strcat(buf, "\n");
    }
    strncpy(n.body, buf, sizeof n.body - 1); n.body[sizeof n.body - 1] = '\0';
    n.id = next_id(fp);
    fseek(fp, 0, SEEK_END);
    fwrite(&n, sizeof(Note), 1, fp);
    fflush(fp);
    printf("Created note [%d].\n", n.id);
}

static int load_note(FILE *fp, int id, Note *out, long *pos) {
    Note n; rewind(fp);
    while ((*pos = ftell(fp)), fread(&n, sizeof(Note), 1, fp) == 1) {
        if (n.id == id) { if (out) *out = n; return 1; }
    }
    return 0;
}

static void view_note(FILE *fp) {
    int id; printf("ID to view: "); if (scanf("%d", &id) != 1) { while (getchar()!='\n'&&EOF); return; }
    while (getchar()!='\n'&&EOF);
    Note n; long pos;
    if (load_note(fp, id, &n, &pos)) {
        printf("\n[%d] %s\n----\n%s\n", n.id, n.title, n.body);
    } else {
        printf("Not found.\n");
    }
}

static void delete_note(FILE *fp) {
    int id; printf("ID to delete: "); if (scanf("%d", &id) != 1) { while (getchar()!='\n'&&EOF); return; }
    while (getchar()!='\n'&&EOF);
    FILE *tmp = fopen("notes.tmp", "wb"); if (!tmp) { perror("fopen tmp"); return; }
    Note n; int deleted = 0; rewind(fp);
    while (fread(&n, sizeof(Note), 1, fp) == 1) {
        if (n.id == id) { deleted = 1; continue; }
        fwrite(&n, sizeof(Note), 1, tmp);
    }
    fclose(tmp);
    fclose(fp);
    remove(NOTES_FILE);
    rename("notes.tmp", NOTES_FILE);
    fp = fopen(NOTES_FILE, "rb+");
    if (deleted) printf("Deleted.\n"); else printf("ID not found.\n");
}

static void edit_note(FILE *fp) {
    int id; printf("ID to edit: "); if (scanf("%d", &id) != 1) { while (getchar()!='\n'&&EOF); return; }
    while (getchar()!='\n'&&EOF);
    Note n; long pos;
    if (!load_note(fp, id, &n, &pos)) { printf("Not found.\n"); return; }
    printf("Current title: %s\nNew title (leave empty to keep): ");
    char t[MAX_TITLE]; if (!read_line(t, sizeof t)) return; if (t[0]) { strncpy(n.title, t, sizeof n.title - 1); n.title[sizeof n.title - 1] = '\0'; }
    printf("Edit body? (y/N): "); char c='n'; if (scanf(" %c", &c)!=1) c='n'; while (getchar()!='\n'&&EOF);
    if (c=='y' || c=='Y') {
        char buf[MAX_BODY]={0}, line[256];
        printf("Body (end with empty line):\n");
        while (read_line(line, sizeof line)) { if (!line[0]) break; if (strlen(buf)+strlen(line)+2>=sizeof buf) { printf("Body too long.\n"); break; } strcat(buf,line); strcat(buf,"\n"); }
        strncpy(n.body, buf, sizeof n.body - 1); n.body[sizeof n.body - 1] = '\0';
    }
    fseek(fp, pos, SEEK_SET);
    fwrite(&n, sizeof(Note), 1, fp);
    fflush(fp);
    printf("Updated.\n");
}

int main(void) {
    FILE *fp = fopen(NOTES_FILE, "rb+");
    if (!fp) fp = fopen(NOTES_FILE, "wb+");
    if (!fp) { perror("fopen"); return 1; }

    for (;;) {
        printf("\nNotes Menu:\n1) List\n2) Create\n3) View\n4) Edit\n5) Delete\n0) Exit\nSelect: ");
        int choice = -1; if (scanf("%d", &choice) != 1) { int ch; while ((ch=getchar())!='\n'&&ch!=EOF); continue; }
        int ch; while ((ch=getchar())!='\n'&&ch!=EOF);
        switch (choice) {
            case 1: list_notes(fp); break;
            case 2: create_note(fp); break;
            case 3: view_note(fp); break;
            case 4: edit_note(fp); break;
            case 5: delete_note(fp); fp = fopen(NOTES_FILE, "rb+"); if (!fp) fp = fopen(NOTES_FILE, "wb+"); break;
            case 0: fclose(fp); return 0;
            default: printf("Invalid choice.\n");
        }
    }
}
