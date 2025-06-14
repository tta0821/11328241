#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define SIZE 9

int puzzle[SIZE][SIZE];
int initial[SIZE][SIZE];

int is_valid(int grid[SIZE][SIZE], int row, int col, int num) {
    for (int i = 0; i < SIZE; i++)
        if (grid[row][i] == num || grid[i][col] == num)
            return 0;

    int sr = row - row % 3, sc = col - col % 3;
    for (int i = sr; i < sr + 3; i++)
        for (int j = sc; j < sc + 3; j++)
            if (grid[i][j] == num)
                return 0;
    return 1;
}

int solve(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (is_valid(grid, row, col, num)) {
                        grid[row][col] = num;
                        if (solve(grid)) return 1;
                        grid[row][col] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

void shuffle(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void generate_complete(int grid[SIZE][SIZE]) {
    int nums[9] = {1,2,3,4,5,6,7,8,9};
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            grid[i][j] = 0;

    shuffle(nums, 9);
    for (int i = 0; i < SIZE; i++)
        grid[0][i] = nums[i];

    solve(grid);
}

void make_puzzle(int grid[SIZE][SIZE], int difficulty) {
    int clues;
    switch (difficulty) {
        case 1: clues = 40 + rand() % 6; break;
        case 2: clues = 30 + rand() % 6; break;
        case 3: clues = 20 + rand() % 6; break;
        default: clues = 30; break;
    }

    int positions[81];
    for (int i = 0; i < 81; i++) positions[i] = i;
    shuffle(positions, 81);

    for (int i = 0; i < 81 - clues; i++) {
        int r = positions[i] / 9;
        int c = positions[i] % 9;
        grid[r][c] = 0;
    }
}

void print_board(int grid[SIZE][SIZE]) {
    printf("\n    1 2 3   4 5 6   7 8 9\n");
    for (int i = 0; i < SIZE; i++) {
        if (i % 3 == 0)
            printf("  +-------+-------+-------+\n");
        printf("%d |", i + 1);
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0)
                printf(" .");
            else
                printf(" %d", grid[i][j]);
            if ((j + 1) % 3 == 0)
                printf(" |");
        }
        printf("\n");
    }
    printf("  +-------+-------+-------+\n");
}

int is_completed() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (puzzle[i][j] == 0)
                return 0;
    return 1;
}

void show_candidates(int row, int col) {
    printf("可填入的數字：");
    int found = 0;
    for (int n = 1; n <= 9; n++) {
        if (is_valid(puzzle, row, col, n)) {
            printf("%d ", n);
            found = 1;
        }
    }
    if (!found)
        printf("無");
    printf("\n");
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    srand(time(NULL));

    int level, row, col, num;
    while (1) {
        printf("🎮 數獨遊戲開始！請選擇難度：\n");
        printf("1 = 簡單\n2 = 普通\n3 = 困難\n請輸入：");
        if (scanf("%d", &level) != 1) {
            printf("⚠️ 請輸入數字（1, 2 或 3）！\n");
            clear_input_buffer();
            continue;
        }
        if (level >= 1 && level <= 3)
            break;
        else
            printf("⚠️ 請輸入 1, 2 或 3。\n");
    }

    int full[SIZE][SIZE];
    generate_complete(full);

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            puzzle[i][j] = full[i][j];

    make_puzzle(puzzle, level);

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            initial[i][j] = puzzle[i][j];

    printf("輸入格式：row col number（1~9）\n");
    printf("輸入 0 0 0 結束遊戲\n");
    printf("輸入 row col 999 可查看提示\n");

    while (!is_completed()) {
        print_board(puzzle);
        printf("請輸入 (row col number)：");
        if (scanf("%d %d %d", &row, &col, &num) != 3) {
            printf("⚠️ 請輸入三個有效數字。");
            clear_input_buffer();
            continue;
        }

        if (row == 0 && col == 0 && num == 0) {
            printf("👋 遊戲結束，再見！\n");
            break;
        }

        if (row < 1 || row > 9 || col < 1 || col > 9) {
            printf("⚠️ 行與列必須在 1~9。\n");
            continue;
        }
        row--; col--;

        if (num == 999) {
            if (puzzle[row][col] != 0) {
                printf("⚠️ 這格已有數字，不能提示。\n");
            } else {
                show_candidates(row, col);
            }
            continue;
        }

        if (num < 1 || num > 9) {
            printf("⚠️ 數字只能是 1~9。\n");
            continue;
        }

        if (initial[row][col] != 0) {
            printf("⚠️ 這是題目格，不能修改。\n");
            continue;
        }

        if (puzzle[row][col] != 0) {
            printf("⚠️ 這格已填過，若要支援清除功能可再說！\n");
            continue;
        }

        if (is_valid(puzzle, row, col, num)) {
            puzzle[row][col] = num;
        } else {
            printf("❌ 不合法的數字，請重新輸入。\n");
        }
    }

    if (is_completed()) {
        print_board(puzzle);
        printf("🎉 恭喜完成數獨！\n");
    }

    return 0;
}