
#ifndef DEF_HPP
#define DEF_HPP

extern void init_alpha();
extern void PushDef(int InIdent, int InVal);
extern void PopDef(int InIdent, int InLine);
extern void ChangeDef(int InIdent, int InVal);
extern int GetVal(int InIdent, int InLine);


#endif
