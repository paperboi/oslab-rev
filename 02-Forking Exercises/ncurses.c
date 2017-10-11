#include  <stdio.h>
#include <ncurses.h>
#include <unistd.h>

int main()
{	int ch;

	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    while((ch = getch()) !=' ')
    {
    	// printf("Type any character to see it in bold\n");			/* If raw() hadn't been called we have to press enter before it gets to the program*/
    					/* Without noecho() some ugly escape charachters might have been printed on screen*/
		attron(A_BOLD);
		printw("%c", ch);
		attroff(A_BOLD);
    	refresh();			/* Print it on to the real screen */
        // getch();			/* Wait for user input */
    }
	endwin();			/* End curses mode		  */

	return 0;
}