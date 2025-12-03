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
cd src
make
```

Output: `note_app` binary in `src/` directory

## Usage

```bash
cd src
./note_app
```

The program opens an interactive menu. Choose an option:
1. List all notes
2. Create a new note
3. View a specific note
4. Edit a note
5. Delete a note
0. Exit

## Example Session

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
- **Database file:** `notes.db` (created in the current working directory)
- **Max note title:** 64 characters
- **Max note body:** 1024 characters
- **Compiler flags:** `-Wall -Wextra -O2` (warnings enabled, optimized)

## Clean Up

```bash
cd src
make clean
```

Removes the compiled binary and temporary files.

## Project Structure

```
note_app/
├── README.md              # This file
├── .gitignore             # Git ignore rules
└── src/
    ├── note_app.c         # Main source code
    ├── Makefile           # Build rules
    └── .gitignore         # Local ignore rules
```

## Author

Created: December 3, 2025

## License

MIT
