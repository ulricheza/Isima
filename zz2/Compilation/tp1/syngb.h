/* ----------------------- syngb.h ---------------------------------- */
/* Tableau contenant le syntaxe du langage                            */
/*    en anglais                                                      */
/*                                                                    */
/*  Fabrice BARAY - ISIMA - 1996-1997                                 */
/* ------------------------------------------------------------------ */

#ifndef SYNGB_H
#define SYNGB_H

static const struct {
 char *nom;
 int unitlex;
} MotsRes[] = {
 { "and",            AND        },
 { "array",          ARRAY      },
 { "begin",          FBEGIN     },
 { "const",          CONST      },
 { "else",           ELSE       },
 { "end",            END        },
 { "function",       FUNCTION   },
 { "if",             IF         },
 { "integer",        INTEGER    },
 { "nil",            NIL        },
 { "not",            NOT        },
 { "of",             OF         },
 { "or",             OR         },
 { "program",        PROGRAM    },
 { "record",         RECORD     },
 { "return",         RETURN     },
 { "string",         STRING     },
 { "then",           THEN       },
 { "type",           TYPE       },
 { "var",            VAR        },
 { "while",          WHILE      },
 { "xor",            XOR        },
 { "for",            FOR        },
 { "to",             TO         },
 { "loop",           LOOP       },
 { NULL,             IDENT      }
};

#endif
/* ----------------------- syngb.h ---------------------------------- */
