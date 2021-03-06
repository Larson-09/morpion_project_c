/**
 * @file player_manager_scanf.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "../etape1/board.h"
#include "../etape1/board_view.h"
#include <assert.h>
#include <stdio.h>

// -------------------------------------------- DECLARATIONS -----------------------------------------------------------

/**
 * The piece type of the current player
 */
PieceType currentPlayer;

// -------------------------------------------- FUNCTIONS --------------------------------------------------------------

#if defined CONFIG_PLAYER_MANAGER_SCANF

void PlayerManager_init (void)
{
    currentPlayer = CROSS;
}

void PlayerManager_free (void)
{
}

void PlayerManager_oneTurn (void)
{
    // Display who is the next player to play
    BoardView_displayPlayersTurn(currentPlayer);

    // Ask for coordinates to put a piece
    PutPieceResult result;
    do
    {
        // Ask for a line and a column
        int col ;
        int line ;

        do {
            printf("Choose a column and a line between 0 and 2 (X,Y)\n");
            scanf("%d,%d", &col, &line);
        }
        while (line < 0 || line > 2 || col < 0 || col > 2);

        // Check if the piece is correctly placed
        result = Board_putPiece(line, col,currentPlayer);
        if (result == SQUARE_IS_NOT_EMPTY)
            BoardView_sayCannotPutPiece();
    }
    while (result == SQUARE_IS_NOT_EMPTY);

    // Switch to the next player
    switch (currentPlayer) {
        case CROSS: currentPlayer = CIRCLE; break;
        case CIRCLE: currentPlayer = CROSS; break;
    }
}
#endif // defined CONFIG_PLAYER_MANAGER_SCANF
