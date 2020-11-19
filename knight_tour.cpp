#include <iostream>
#include <iomanip>

using namespace std;

#define SIZE_BOARD_CHESS            8
#define EIGHT_DIFF_MOVES            8
#define INIT_BOARD_VALUE            (-1)
#define MAX_STEPS                   (SIZE_BOARD_CHESS * SIZE_BOARD_CHESS)

static int logs[MAX_STEPS] = {-1};

int horizontal_offset[EIGHT_DIFF_MOVES] = {
    2, 1, -1, -2, -2, -1, 1, 2
};
int vertical_offset[EIGHT_DIFF_MOVES] = {
    -1, -2, -2, -1, 1, 2, 2, 1
};


void initBoardChess(int s[][SIZE_BOARD_CHESS])
{
    for(int i = 0; i < SIZE_BOARD_CHESS; i++)
        for(int j = 0; j < SIZE_BOARD_CHESS; j++)
            s[i][j] = INIT_BOARD_VALUE;
}

void printBoardChess(int s[][SIZE_BOARD_CHESS])
{
    for(int i = 0; i < SIZE_BOARD_CHESS; i++){
        for(int j = 0; j < SIZE_BOARD_CHESS; j++){
            cout << setw(3) << s[i][j];
        }
        cout << endl;
    }
}

static int check_valid_with8(int a)
{
    if(a < 0 || a >= SIZE_BOARD_CHESS){
        return -1;
    }
    return 0;
}

int check_value_board_valid(int s[][SIZE_BOARD_CHESS], int x, int y)
{
    if((check_valid_with8(x) < 0) ||
        (check_valid_with8(y) < 0)){
        return -1;
    }
    if(s[x][y] == INIT_BOARD_VALUE){
        return 0;
    }
    return -1;
}

int checkValid(int s[][SIZE_BOARD_CHESS], int x, int y, int move)
{
    int ret = 0;
    int new_x = 0, new_y = 0;
    // validate parameter
    if((check_valid_with8(x) < 0) ||
        (check_valid_with8(y) < 0) ||
        (check_valid_with8(move) < 0)){
        return -1;
    }

    new_x = x + vertical_offset[move];
    new_y = y + horizontal_offset[move];
    if((check_valid_with8(new_x) < 0) ||
        (check_valid_with8(new_y) < 0)){
        return -1;
    }
    if(check_value_board_valid(s, new_x, new_y) < 0){
        return -1;
    }
    return ret;
}


int move_one_step(int s[][SIZE_BOARD_CHESS], int &x, int &y, int move, int log[], int cnt_step)
{
    int ret = 0;
    int pos_x = x;
    int pos_y = y;
    // if move valid, mark position
    ret = checkValid(s, pos_x, pos_y, move);
    if(ret == 0){
        // mark
        s[pos_x][pos_y] = move;
        pos_x = x + vertical_offset[move];
        pos_y = y + horizontal_offset[move];
        log[cnt_step] = move;
        // printf("[%d][%d] -> %d -> [%d][%d] cnt %d\t\t", x, y, move, pos_x, pos_y, cnt_step);
        x = pos_x;
        y = pos_y;
    }
    return ret;
}

int solveKnight(int s[][SIZE_BOARD_CHESS], int x, int y)
{
    int ret = 0;
    int moved_way = 0;
    int count_steps = 0;
    int pos_x = x;
    int pos_y = y;
    int log[MAX_STEPS] = {-1};
    int max_step = 0;

    for(int i = 0; i < MAX_STEPS; i++){
        log[i] = -1;
    }

    moved_way = -1;
    while(count_steps < (MAX_STEPS-1)){
        // moved_way = log[count_steps] + 1;
        moved_way++;
        ret = move_one_step(s, pos_x, pos_y, moved_way, log, count_steps);
        if(ret == 0){
            // printf("[Success] [%d][%d] step %d move %d\r\n", 
            //         pos_x, pos_y, count_steps, moved_way);
            count_steps ++;
            moved_way = -1;
            // printBoardChess(s);
        }
        else{
            if((count_steps == 0) && (moved_way >= 8)){
                printf("\r\n[%d][%d] failed at first step!\r\n", x, y);
                break;
            }
            else{
                // backward one step
                if(moved_way >= 8){
                    count_steps--;
                    moved_way = log[count_steps];
                    int old_x = pos_x;
                    int old_y = pos_y;
                    pos_x = pos_x - vertical_offset[moved_way];
                    pos_y = pos_y - horizontal_offset[moved_way];
                    
                    // printf("Backward [%d][%d]:%d -> [%d][%d]:%d cnt_step %d move %d\r\n", 
                    //             old_x, old_y, s[old_x][old_y],
                    //             pos_x, pos_y, s[pos_x][pos_y], count_steps, moved_way);
                    s[pos_x][pos_y] = INIT_BOARD_VALUE;
                    s[old_x][old_y] = INIT_BOARD_VALUE;
                    // printBoardChess(s);
                    // break;
                    if(max_step < count_steps){
                        printf("LOG [%d] : ", count_steps);
                        for(int i = 0; i < MAX_STEPS; i++)
                            printf("%d ", log[i]);
                        printf("\r\n");
                        max_step = count_steps;
                    }
                    
                }
            }
        }
    }
    return ret;
}

int main(void)
{
    int boardChess[SIZE_BOARD_CHESS][SIZE_BOARD_CHESS];
    int ret = 0;
    initBoardChess(boardChess);
    printBoardChess(boardChess);
    ret = solveKnight(boardChess, 0, 0);
    printBoardChess(boardChess);
    
    return 0;
}


