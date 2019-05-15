# Sorcery
A two player game similar to Heartstone

###5.1 Commands
During a player’s turn, they may issue the following commands. Each command must be issued on its own line. A command may have extra whitespace before and after every word in it.
###5.1.1 help
The help command displays a message describing the commands and their formats. You may use the following help message or create your own:
Commands: help -- Display this message. end -- End the current player’s turn. quit -- End the game. attack minion other-minion -- Orders minion to attack other-minion. attack minion -- Orders minion to attack the opponent. play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player. use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player. inspect minion -- View a minion’s card and all enchantments on that minion. hand -- Describe all cards in your hand. board -- Describe all cards on the board.
###5.1.2 end
The end command ends the current player’s turn. A player may end their turn at any time.
###5.1.3 quit
The quit command ends the game immediately with no winner.
###5.1.4 draw
The draw command draws a card, similar to the eﬀect if the player just started their turn. This command is only available in -testing mode.
###5.1.5 discard
The discard i command discards the ith card in the player’s hand, simply removing it from their hand (the card does not go to the graveyard, trigger leave play eﬀects or anything else). This command is only available in -testing mode.
###5.1.6 attack
The attack command follows one of two formats: • attack i orders minion i to attack the opposing player, where 1 is the leftmost minion and 5 is the rightmost minion. • attack i j orders the active player’s minion i to attack the inactive player’s minion j, where both i and j are as above.
###5.1.7 play
The play command follows one of two formats: • play i plays the ith card in the active player’s hand with no target. For example, this can be used to play minions, rituals, and spells with no targets. Note that i ranges from 1 to 5. • play i p t plays the ith card in the active player’s hand on card t owned by player p. p may be equal to 1 or 2 to represent player 1 or 2 respectively. t is either 1, 2, 3, 4, 5 (the ith minion owned by player p) or r (the ritual owned by player p). This can be used to play enchantments and spells with targets.
###5.1.8 use
The use command follows the same format as the play command and has the same meaning, except that i refers to the ith minion owned by the current player, and the command orders that minion to use its activated ability on the provided target (or on no target).
###5.1.9 describe
The inspect i command inspects the ith minion owned by the active player, as described in the “inspecting a minion” subsection of the Display section.
###5.1.10 hand
The hand command displays the active player’s hand, as described in the “hand” subsection of the Display section.
###5.1.11 board
The board command displays the board, as described in the “board” subsection of the Display section.
