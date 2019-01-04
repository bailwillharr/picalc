#include <stdio.h>
#include <stdint.h>

#include <wiringPi.h>

#define IO_ROW0 18
#define IO_ROW1 23
#define IO_ROW2 24
#define IO_ROW3 25
#define IO_COL0 12
#define IO_COL1 16
#define IO_COL2 20
#define IO_COL3 21
#define IO_BRK 26

void checkRow(int[4], int);
void checkRow(int[4][4]);

int main(int argc, char **argv) {

    // Keypad layout matrix
    const char keys[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    // Keypad state matrix
    int currentKeypad[4][4];

    // Init GPIO
    wiringPiSetupGpio();

    // Set GPIO Pin Modes
    pinMode(IO_ROW0, OUTPUT); // Row 0
    pinMode(IO_ROW1, OUTPUT); // Row 1
    pinMode(IO_ROW2, OUTPUT); // Row 2
    pinMode(IO_ROW3, OUTPUT); // Row 3
    pinMode(IO_COL0, INPUT); // Column 0
    pinMode(IO_COL1, INPUT); // Column 1
    pinMode(IO_COL2, INPUT); // Column 2
    pinMode(IO_COL3, INPUT); // Column 3
    pinMode(IO_BRK, INPUT); // Break button

    // Set input pins pull-up-down state
    pullUpDnControl(IO_COL0, PUD_DOWN); // Column 0
    pullUpDnControl(IO_COL1, PUD_DOWN); // Column 1
    pullUpDnControl(IO_COL2, PUD_DOWN); // Column 2
    pullUpDnControl(IO_COL3, PUD_DOWN); // Column 3
    pullUpDnControl(IO_BRK, PUD_UP); // Break button

    checkKeyPad(currentKeypad);
    for (x = 0; x < 4; x++) {
        for (y = 0; y < 4; y++) {
            printf("%d", currentKeypad[x][y]);
        }
        printf("\n")
    }

    return 0;
}

void checkRow(int rowOutput[4], int row) {
    // Reset row pins
    digitalWrite(IO_ROW0, LOW);
    digitalWrite(IO_ROW1, LOW);
    digitalWrite(IO_ROW2, LOW);
    digitalWrite(IO_ROW3, LOW);

    // Enable only specified row pin
    digitalWrite(row, HIGH);

    // Return an array containing the input states of the row's button
    rowOutput[0] = digitalRead(IO_COL0);
    rowOutput[1] = digitalRead(IO_COL1);
    rowOutput[2] = digitalRead(IO_COL2);
    rowOutput[3] = digitalRead(IO_COL3);
}

void checkKeyPad(int keypad[4][4]) {
    int currentRow[4];
    int keypadOutput[4][4];

    for (x = 0; x < 4; x++){
        checkRow(keypadOutput[x], x);
    }
    keypad = keypadOutput;
}
