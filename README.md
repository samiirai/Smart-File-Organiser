# Smart-File-Organiser
A desktop utility for file organization, duplicate detection, and file integrity verification using C.

Project Structure
Smart-File-Organizer/
│
├── build_and_run.bat        (Automated deployment script to compile and run the project)
│
├── src/                     (Contains all our modular C source code and headers)
│   ├── main.c               (Entry point of the program; contains the main menu)
│   ├── utils.h              (Header for shared utility functions)
│   ├── utils.c              (Implementation of SHA-256 hashing logic)
│   ├── organizer.h          (Header for the file organizer module)
│   ├── organizer.c          (Implementation of sorting files by extension)
│   ├── duplicate.h          (Header for the duplicate finder module)
│   ├── duplicate.c          (Implementation of size and hash comparison)
│   ├── integrity.h          (Header for the integrity checker module)
│   └── integrity.c          (Implementation of manifest creation and verification)
│
├── test_folder/             (The messy folder we will use for testing and demoing)
│   ├── notes.txt            (Dummy text file)
│   ├── syllabus.pdf         (Dummy PDF document)
│   ├── image1.jpg           (Dummy image)
│   └── image1_backup.jpg    (Exact copy of image1.jpg to test the duplicate finder)
│
└── build/                   (We don't need to create this; the .bat script creates it)
    └── SmartFileTool.exe    (The final compiled application generated after running the .bat file)


test_folder with 14 dummy files across various formats is created  using ai application GEMINI with model name 3.1 Pro (Advanced Reasoning)
to help us test our file sorting and duplicate finder scripts 