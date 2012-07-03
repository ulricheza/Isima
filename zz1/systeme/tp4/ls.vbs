dim fso,argv,liste
set fso = WScript.CreateObject("Scripting.FileSystemObject")
set argv =wscript.arguments

src="c:\"

if not argv.count = 0 then
   src = argv(0)
end if 

wscript.echo "On liste " & src

set dir=fso.getfolder(src)

for each fic in dir.files
  wscript.echo fic.path
next