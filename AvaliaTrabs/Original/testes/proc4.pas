program proc1 (input, output);
var x, y: integer;
    procedure p(t:integer);
    var z:integer;
    begin
        z:=x;
        t:=z;
        x:=x-1;
        if (z>1)
        then y:=2
        else y:=1;
        y:=y*z
    end;
begin
    read(x);
    write (x,y)
end.
