#include <stdio.h>
#include <string.h>

#define MAX_NOTES 100

struct Note {
    char title[100];
    char content[1000];
};

struct NotesManager {
    struct Note notes[MAX_NOTES];
    int numNotes;
};

void addNote(struct NotesManager* notesManager, const char* title, const char* content) {
    if (notesManager->numNotes < MAX_NOTES) {
        strcpy(notesManager->notes[notesManager->numNotes].title, title);
        strcpy(notesManager->notes[notesManager->numNotes].content, content);
        notesManager->numNotes++;
        printf("Note added successfully.\n");
    } else {
        printf("Cannot add more notes. Maximum limit reached.\n");
    }
}

void viewNotes(const struct NotesManager* notesManager) {
    if (notesManager->numNotes == 0) {
        printf("No notes available.\n");
    } else {
        printf("\n==========================================\n");
        printf("----------- Welcome to Your Notes -----------\n");
        printf("==========================================\n");
        for (int i = 0; i < notesManager->numNotes; ++i) {
            printf("Title: %s\n", notesManager->notes[i].title);
            printf("Content: %s\n\n", notesManager->notes[i].content);
        }
        printf("==========================================\n");
    }
}

void deleteNote(struct NotesManager* notesManager, const char* title) {
    int foundIndex = -1;

    for (int i = 0; i < notesManager->numNotes; i++) {
        if (strcmp(notesManager->notes[i].title, title) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        for (int i = foundIndex; i < notesManager->numNotes - 1; i++) {
            strcpy(notesManager->notes[i].title, notesManager->notes[i + 1].title);
            strcpy(notesManager->notes[i].content, notesManager->notes[i + 1].content);
        }
        notesManager->numNotes--;
        printf("Note \"%s\" deleted successfully!\n", title);
    } else {
        printf("Note \"%s\" not found. Deletion failed.\n", title);
    }
}

int main() {
    struct NotesManager notesManager;
    notesManager.numNotes = 0;
    int choice;

    printf("\n==========================================\n");
    printf("----------- Welcome to Your Notes -----------\n");
    printf("==========================================\n");

    do {
        printf("\nMenu:\n");
        printf("1. Add Note\n");
        printf("2. View Notes\n");
        printf("3. Delete Note\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char title[100], content[1000];
                printf("Enter note title: ");
                getchar(); // Clear the buffer
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0'; // Remove newline character

                printf("Enter note content: ");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = '\0'; // Remove newline character

                addNote(&notesManager, title, content);
                break;
            }
            case 2:
                viewNotes(&notesManager);
                break;
            case 3: {
                char titleToDelete[100];
                printf("Enter the title of the note to delete: ");
                getchar(); // Clear the buffer
                fgets(titleToDelete, sizeof(titleToDelete), stdin);
                titleToDelete[strcspn(titleToDelete, "\n")] = '\0'; // Remove newline character

                deleteNote(&notesManager, titleToDelete);
                break;
            }
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
