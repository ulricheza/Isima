dim fso,argv,taille
set fso = WScript.CreateObject("Scripting.FileSystemObject")
set argv =wscript.arguments

src="c:\"

if not argv.count = 0 then
   if not argv(0) = "-t" then
      src = argv(0)
   else
      taille=1
   end if
   if argv.count = 2 then
      if argv(1) = "-t" then
         taille = 1
      end if
   end if
end if

wscript.echo "On liste " & src

set dir=fso.getfolder(src)

for each fic in dir.files
  wscript.echo fic.path
  if taille = 1 then
     wscript.echo fic.size,"Ko"
  end if
next