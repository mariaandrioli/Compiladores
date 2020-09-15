program proc1 (input, output);
var x, y: integer;
    procedure p;
    var z:integer;
    begin
        z:=x;
        x:=x-1;
        if (z>1)
        then y:=2;
        else y:=1;
        y:=y*z
    end;
begin
    read(x);
    write (x,y);
end.