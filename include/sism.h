#ifndef SISM_H
#define SISM_H

/* FLAGS SYNTAX
 * Uma flag é indicada por um hexadecimal de 3 dígitos.
 * O primeiro dígito (T) indica qual a informação a que a flag se refere.
 * Os últimos 2 dígitos (II) codificam a informação propriamente dita.
 *    > 0xTII
 *
 * Códigos de tipos (T) e respectivas informações (II):
 *    A - Operation Mode
 *       00 - Text Mode       > 0xA00
 *       10 - TUI Mode        > 0xA10
 *       11 - Advanced TUI    > 0xA11
 *       20 - GUI Mode        > 0xA20
 *    0 - Error Management
 *       00 - Success         > 0x000
 *       FF - Unknown         > 0x0FF
 *       E0 - Fatal           > 0x0E0
 *       E1 - Controled       > 0x0E1
 *       10 - File access     > 0x010
 *       A0 - Memory access   > 0x0A0
 *    E - Flow Management
 *       00 - Exit            > 0xE00
 *       10 - Continue        > 0xE10
 */

// Flag codes
#define __OPERMODE_TERMINAL 0xA00 // Command-based interaction
#define __OPERMODE_TUI 0xA10	  // Text-based user interface
#define __OPERMODE_TUIPLUS 0xA11  // Alternative TUI, if available
#define __OPERMODE_GUI 0xA20	  // Graphical User Interface
#define __ERROR_SUCCESS 0x000	  // Program ended successfully
#define __ERROR_UNKNOWN 0x0FF	  // Unkown, not predicted error
#define __ERROR_FATAL 0x0E0		  // Fatal error - entire program must be aborted immediately
#define __ERROR_CONTROLED 0x0E1	  // Controlled, predicted error
#define __ERROR_FILE 0x010		  // Error while managing files on disk
#define __ERROR_MEMORY 0x0A0	  // Error while managing data on memory
#define __NEXT_EXIT 0xE00		  // Flow control - current operation must be aborted
#define __NEXT_CONTINUE 0xE10	  // Flow control - current operation may continue

typedef unsigned SISM_flag; // Definition of the SISM Flags
typedef struct
{
	SISM_flag operation_mode; // Operation Mode
	SISM_flag error;		  // Exit error code
	SISM_flag flow;			  // Flow control
	SISM_flag io;			  // I/O status (specific for files on disk)
} SISM;

/* Methods */
void start_app(SISM *, int, char const **);

#endif