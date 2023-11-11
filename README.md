# Number-to-Letter Converter

This simple C program converts a numeric input into its French word representation. For instance, the input "123" is translated to "cent vingt-trois" (one hundred twenty-three).

## Usage

1. **Clone the repository:** `git clone https://github.com/JadaMohamed/numbers-to-letters`
2. **Compile the program:** `gcc main.c -o main`
3. **Run the executable:** `./number-to-letter`

Enter a three-digit number when prompted, and the program will output the corresponding French word representation.

## Code Overview

### Constants

- `CHIFFRE_DICS`: Dictionary for numbers from 0 to 19.
- `DOUZAINES_DICS`: Dictionary for tens (multiples of 10).
- `SEC_DICS`: Dictionary for large scale numbers (thousands, millions, etc.).

### Functions

- `saisirChaine()`: Takes user input for a numeric string.
- `unites()`, `centaines()`, `douzaines()`: Functions to convert units, hundreds, and tens into French words.
- `troisChiffres()`: Converts a three-digit number into its French word representation.
- `add()`: Concatenates two strings.

### Main Function

1. Takes user input for a three-digit number.
2. Prepares the input by adding leading zeros if necessary.
3. Processes the number in chunks of three digits and converts each chunk.
4. Prints the final French word representation.

## Example

```bash
Donner un nombre (3 chiffres) : 123
Output: cent vingt-trois
