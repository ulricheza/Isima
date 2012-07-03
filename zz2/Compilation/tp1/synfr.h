/* --------------------- synfr.h ------------------------------------ */
/* Tableau contenant la syntaxe du langage                            */
/*    en francais                                                     */
/*                                                                    */
/*  Fabrice BARAY - ISIMA - 1996-1997                                 */
/* ------------------------------------------------------------------ */

#ifndef SYNFR_H
#define SYNFR_H

static const struct {
 char *nom;
 int unitlex;
} MotsRes[] = {
 { "et",             AND       },
 { "tableau",        ARRAY     },
 { "debut",          FBEGIN    },
 { "constante",      CONST     },
 { "sinon",          ELSE      },
 { "fin",            END       },
 { "fonction",       FUNCTION  },
 { "si",             IF        },
 { "entier",         INTEGER   },
 { "vide",           NIL       },
 { "non",            NOT       },
 { "de",             OF        },
 { "ou",             OR        },
 { "programme",      PROGRAM   },
 { "enreg",          RECORD    },
 { "retourne",       RETURN    },
 { "chaine",         STRING    },
 { "alors",          THEN      },
 { "type",           TYPE      },
 { "var",            VAR       },
 { "tantque",        WHILE     },
 { "oux",            XOR       },
 { "for",            FOR        },
 { "to",             TO         },
 { "loop",           LOOP       },    
 { NULL,             IDENT     }
};

#endif

/* --------------------- synfr.h ------------------------------------ */
