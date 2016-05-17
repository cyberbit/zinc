# Zinc
*Zinc Is Not Copper.* Zinc is a text encryption engine.

Remember those Rubik's Cube puzzles you had as a kid? And do you also remember how easy it was to scramble them beyond recognition? Zinc takes that concept and applies it to encrypting messages.

The core component of Zinc is its alphabet. An alphabet is stored in a way that represents a 3x3x3 puzzle cube. By iterating through the letters of a pre-determined key, Zinc executes rotations on faces of the cube, thus scrambling the alphabet. Another algorithm processes a given plaintext message through this cube, thus encrypting the text. By following the same process in reverse, those messages can be decoded by someone who knows the key.

The main advantage of Zinc is that anything the program can do is possible using a marked Rubik’s cube, a pad of paper, and a pencil. This makes communication possible not just between two cubes or two computers, but also between a cube and a computer, or vice versa. Advanced use can involve setting up the cube to an agreed-upon state before encoding or decoding to avoid message snooping.

---

This project originally started as a project for an Object Oriented Programming (OOP) class. I loved working on it so much that I decided to share it here. Additionally, as an exercise, I plan to port Zinc into every high-level language I learn, in order to sharpen my skills and thicken my portfolio.

Hopefully this personal exercise can help *you* look at the differences and similarities between languages in a new and interesting way. 

Feel free to contribute if you find bugs or have suggestions!
