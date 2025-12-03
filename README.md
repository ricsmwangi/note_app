# note_app

A lightweight, file-based note-taking application written in C. Store, retrieve, edit, and delete notes via a command-line interface.

## Features

- **Create notes** — Add notes with a title and multi-line body
- **List notes** — View all notes with their IDs and titles
- **View notes** — Read the full content of a specific note
- **Edit notes** — Modify the title and/or body of existing notes
- **Delete notes** — Remove notes by ID
- **Persistent storage** — Notes are saved to a binary database file (`notes.db`)

## Build

```bash
make
```

Output: `note_app` binary

## Usage

```bash
./note_app
```

The program opens an interactive menu. Choose an option:
1. List all notes
2. Create a new note
3. View a specific note
4. Edit a note
5. Delete a note
0. Exit

## Example

```
Notes Menu:
1) List
2) Create
3) View
4) Edit
5) Delete
0) Exit
Select: 2
Title: My First Note
Body (end with empty line):
This is a test note.
It has multiple lines.

Created note [1].
```

## Technical Details

- **Language:** C
- **Storage:** Binary format (struct-based, direct serialization)
- **Database file:** `notes.db` (created in the current directory)
- **Max note title:** 64 characters
- **Max note body:** 1024 characters

## Clean Up

```bash
make clean
```

Removes the compiled binary and temporary files.

## License

MIT
