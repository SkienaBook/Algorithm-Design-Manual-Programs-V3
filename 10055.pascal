
{$N+}
program acm;
var
  a, b, c : integer;
begin
  while not eof do
  begin
    readln(a, b);
    if b > a then
    begin
      c := b;
      b := a;
      a := c
    end;
    writeln(a - b);
  end
end.
 
