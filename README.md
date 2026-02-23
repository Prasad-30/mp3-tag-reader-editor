# 📌 MP3 Tag Reader & Editor in C

## 📖 Project Overview

The MP3 Tag Reader & Editor is a command-line based application developed in C programming language that reads and modifies ID3 metadata from MP3 files.

Instead of using external libraries, this project manually parses the binary structure of ID3v2 frames, providing deeper understanding of file internals and low-level programming.

This project demonstrates strong fundamentals in Systems Programming and File Handling.

---

## 🎯 Features

- Validates MP3 file by checking ID3 header  
- Reads metadata fields:
  - Title (TIT2)
  - Artist (TPE1)
  - Album (TALB)
  - Year (TYER)
  - Genre (TCON)
  - Comment (COMM)
- Edits specific metadata fields without disturbing audio stream  
- Displays formatted output in terminal  
- Built using Makefile  

---

## 🏗 Project Structure

mp3_tag_reader/
│── main.c  
│── view.c  
│── edit.c  
│── prototypes.h  
│── ret_types.h  
│── Makefile  
│── README.md  

---

## ⚙️ Concepts Used

- Binary File Handling  
- Frame-Based File Format Parsing  
- Big-endian to Little-endian Conversion  
- Dynamic Memory Management  
- Modular Programming Design  
- Command-Line Argument Processing  

---

## 🚀 How to Compile

make

---

## ▶️ How to Run

### To View MP3 Tags:
./output.exe -v song.mp3

### To Edit MP3 Tags:
./output.exe -e <option> <new_value> song.mp3

Example:
./output.exe -e -t "New Title" song.mp3

---

## 💡 Key Learning Outcomes

- Deep understanding of structured binary formats  
- Practical experience with low-level file manipulation  
- Improved debugging and memory management skills  
- Strong foundation in Systems Programming  

---

## 👨‍💻 Author

Prasad  
GitHub: https://github.com/Prasad-30
