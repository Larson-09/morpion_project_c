/**
 * @file player_manager_scanf.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "board.h"
#include "board_view.h"
#include <assert.h>
#include <stdio.h>

SquareChangeCallback *onSquareChange;
EndOfGameCallback  *onEndOfGame;
PieceType current_player;


#define CONFIG_PLAYER_MANAGER_SCANF

#if defined CONFIG_PLAYER_MANAGER_SCANF

void PlayerManager_init (void)
{
    Board_init(*onSquareChange, *onEndOfGame);
    current_player = CROSS;

}

void PlayerManager_free (void)
{
}

void PlayerManager_oneTurn (void)
{
    PutPieceResult result;
    do
    {
        // Display who is the next player to play
        BoardView_displayPlayersTurn(current_player);

        // Ask for a line and a column
        int col ;
        int line ;

        do {
            printf("Choose a column and a line between  and 3 (X,Y)");
            scanf("%d,%d", &col, &line);
        }
        while (line < 0 || line > 2 || col < 0 || col > 2);

        result = Board_putPiece(line, col,current_player);
    }
    while (result == SQUARE_IS_NOT_EMPTY);

    // Switch to the other player
    switch (current_player) {
        case CROSS: current_player = CIRCLE; break;
        case CIRCLE: current_player = CROSS; break;
    }
}

#endif // defined CONFIG_PLAYER_MANAGER_SCANF