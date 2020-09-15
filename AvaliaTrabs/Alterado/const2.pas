program const2;
const max = 100;
   min =  max div 2;
var i, j: integer ;

function soma(a,b : integer):integer;
const inutil = max div min;
(* const inutil = max+i+a; *) (* o fpc não aceia isto, mas *)
                              (* seu compilador tem que aceitar! *)
   begin
      soma:=inutil;
   end;


begin
   i:=min;
   while i <= max do
      begin
         j:=soma(i,max);
         i:=i+1;
      end;
   writeln (j) ;
end.

